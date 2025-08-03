#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include <platform.h>

#include <serial.h>

#include <log.h>

// Buffer.
static __xdata char l_logBuffer[512];

// Buffer position.
static __xdata char *l_bufferPos;

// Flush flag.
static __xdata bool l_flushing;

/**
 * @brief       Initialize log.
 */
void initLog(void)
{
    l_bufferPos = l_logBuffer;
    l_flushing  = false;
}

/**
 * @brief       Flush buffer.
 */
static inline void flushBuffer(void)
{
    l_flushing = true;
    startWritingSerial(l_logBuffer, l_bufferPos - l_logBuffer);
}

/**
 * @brief       Wait for flush.
 */
static inline void waitForFlush(void)
{
    if (l_flushing) {
        while (l_flushing) {
            if (! isSerialBusy()) {
                l_flushing = false;
            }
        }
        l_bufferPos = l_logBuffer;
    }
}

/**
 * @brief       Write buffer.
 *
 * @param[in]   data    Data to write.
 * @param[in]   size    Size to write.
 */
static inline void writeBuffer(const char *data, uint16_t size)
{
    static __xdata uint16_t bufferRemain;
    static __xdata uint16_t sizeToWrite;
    static __xdata uint16_t sizeWritten;

    if (size == 0) {
        return;
    }

    sizeWritten = 0;
    while (sizeWritten < size) {
        // Wait for flush.
        waitForFlush();

        // Get size to write.
        bufferRemain = sizeof(l_logBuffer) - (l_bufferPos - l_logBuffer);
        sizeToWrite  = size - sizeWritten;
        if (sizeToWrite > bufferRemain) {
            sizeToWrite = bufferRemain;
        }

        // Write buffer.
        memcpy(l_bufferPos, data + sizeWritten, sizeToWrite);

        // Update.
        sizeWritten += sizeToWrite;
        bufferRemain -= sizeToWrite;
        l_bufferPos += sizeToWrite;

        // Flush.
        if (bufferRemain <= 0) {
            flushBuffer();
        }
    }
}

static __xdata char l_parseBuffer[20];

#define WRITE_INT_IMPL(bit)                                            \
    inline void writeInt##bit(int##bit##_t value)                      \
    {                                                                  \
        uint8_t count = 0;                                             \
        if (value < 0) {                                               \
            value = -value;                                            \
            writeBuffer("-", 1);                                       \
        }                                                              \
        while (value > 0) {                                            \
            l_parseBuffer[count] = value % 10 + '0';                   \
            ++count;                                                   \
            value /= 10;                                               \
        }                                                              \
        uint8_t index = 0;                                             \
        while (true) {                                                 \
            uint8_t reverseIndex = count - index - 1;                  \
            if (reverseIndex <= index) {                               \
                break;                                                 \
            }                                                          \
            char tmp                    = l_parseBuffer[index];        \
            l_parseBuffer[index]        = l_parseBuffer[reverseIndex]; \
            l_parseBuffer[reverseIndex] = tmp;                         \
            ++index;                                                   \
        }                                                              \
        writeBuffer(l_parseBuffer, count);                             \
    }

WRITE_INT_IMPL(8)
WRITE_INT_IMPL(16)
WRITE_INT_IMPL(32)
WRITE_INT_IMPL(64)

#undef WRITE_INT_IMPL

#define WRITE_UINT_IMPL(bit)                                           \
    inline void writeUint##bit(uint##bit##_t value)                    \
    {                                                                  \
        uint8_t count = 0;                                             \
        while (value > 0) {                                            \
            l_parseBuffer[count] = value % 10 + '0';                   \
            ++count;                                                   \
            value /= 10;                                               \
        }                                                              \
        uint8_t index = 0;                                             \
        while (true) {                                                 \
            uint8_t reverseIndex = count - index - 1;                  \
            if (reverseIndex <= index) {                               \
                break;                                                 \
            }                                                          \
            char tmp                    = l_parseBuffer[index];        \
            l_parseBuffer[index]        = l_parseBuffer[reverseIndex]; \
            l_parseBuffer[reverseIndex] = tmp;                         \
            ++index;                                                   \
        }                                                              \
        writeBuffer(l_parseBuffer, count);                             \
    }

WRITE_UINT_IMPL(8)
WRITE_UINT_IMPL(16)
WRITE_UINT_IMPL(32)
WRITE_UINT_IMPL(64)

#undef WRITE_UINT_IMPL

/**
 * @brief       Format log.
 */
void printLog(const char *file, uint16_t line, const char *fmt, ...)
{
    // Variable arguments.
    va_list pArgs;
    va_start(pArgs, fmt);

    // File, line.
    writeBuffer("[", 1);
    writeBuffer(file, strlen(file));
    writeBuffer(":  ", 2);
    writeUint16(line);
    writeBuffer("]: ", 3);

    // Parse format.
    const char *pFmt   = fmt;
    const char *pBegin = fmt;
    while (true) {
        if (*pFmt == '\0') {
            // Write skipped characters.
            writeBuffer(pBegin, pFmt - pBegin);
            break;
        } else {
            ++pFmt;
        }
    }

    writeBuffer("\r\n", 2);
    flushBuffer();

    return;
}
