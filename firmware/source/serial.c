#include <stdbool.h>
#include <stddef.h>

#include <clock.h>
#include <platform.h>

#include <serial.h>

#define GPIO_TX P3_1
#define GPIO_RX P3_0

#define GPIO_BIT_TX       1
#define GPIO_BIT_RX       0
#define GPIO_MODE1_SERIAL P3M1
#define GPIO_MODE0_SERIAL P3M0

#define MODE_MASK ((uint8_t)(1 << GPIO_BIT_TX) | (uint8_t)(1 << GPIO_BIT_RX))

#define BAUDRATE         115200L
#define l_timerInitValue ((uint16_t)(65536L - (IRC_FEQ / (4 * BAUDRATE))))

/// Busy flag.
static volatile __xdata bool           l_busy;       ///< Busy flag.
static volatile __xdata const uint8_t *l_data;       ///< Data to send.
static volatile __xdata uint16_t       l_sizeRemain; ///< Size remian.

/**
 * @brief       Initialize serial.
 */
void initSerial(void)
{
    // Set GPIO port value.
    GPIO_TX = 1;
    GPIO_RX = 1;

    // Set GPIO mode.
    P_SW2 |= 0x80;
    GPIO_MODE1_SERIAL &= ~MODE_MASK;
    GPIO_MODE0_SERIAL &= ~MODE_MASK;
    P_SW2 &= ~(uint8_t)0x80;

    // Set serial config.
    // 8bit.
    SCON = 0x50;

    // Use timer 2.
    AUXR |= 0x01;

    // 1T
    AUXR |= 0x04;

    // Initial value.
    T2L = l_timerInitValue & 0xFF;
    T2H = (l_timerInitValue & 0xFF00) >> 8;

    // Enable uart 1 interrupt.
    ES = 1;

    l_busy = false;
}

/**
 * @brief       Start serial.
 */
void startSerial(void)
{
    // Start timer 2.
    AUXR |= 0x10;
}

/**
 * @brief       Check if the serial is busy.
 */
bool isSerialBusy(void)
{
    return l_busy;
}

/**
 * @brief       Start writing serial.
 */
void startWritingSerial(const void *data, uint16_t size)
{
    if (l_busy || size == 0) {
        return;
    }

    l_data       = data;
    l_sizeRemain = size;

    EA     = 0;
    l_busy = true;
    SBUF   = *l_data;
    EA     = 1;
}

/**
 * @brief       Timer0 ISR.
 */
void uart1ISR(void) __interrupt(INT_UART1)
{
    EA = 0;
    if (TI) {
        ++l_data;
        --l_sizeRemain;
        if (l_sizeRemain == 0) {
            l_busy = false;
        } else {
            SBUF = *l_data;
        }
        TI = 0;
    }
    if (RI) {
        RI = 0;
    }
    EA = 1;
}

/**
 * @brief       Task to test serial.
 */
void testSerialTask(void)
{
    static __xdata uint32_t oldCount     = 0;
    static __xdata uint8_t  testCount    = 0;
    static __xdata uint8_t  oldTestCount = 9;
    static __xdata char     buffer[]     = "A:Hello world!\r\n";
    __xdata uint32_t        currentCount = getSystemClock() / (500L * 1000);

    if (testCount != oldTestCount && ! isSerialBusy()) {
        oldTestCount = testCount;
        buffer[0]    = 'A' + testCount;
        startWritingSerial(buffer, sizeof(buffer));
    }
    if (currentCount != oldCount) {
        testCount += 1;
        if (testCount >= 26) {
            testCount = 0;
        }
        oldCount = currentCount;
    }
}
