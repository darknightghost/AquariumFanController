#include <platform.h>

#include <eeprom.h>

#define IAP_TPS_VALUE (IRC_FEQ / 1000000)

#define IAP_COMMAND_EMPTY 0x00
#define IAP_COMMAND_READ  0x01
#define IAP_COMMAND_WRITE 0x02
#define IAP_COMMAND_WIPE  0x03

/**
 * @brief   Status.
 */
enum Status {
    Ready,   ///< Operation ready.
    Error,   ///< Operation error.
    Reading, ///< Reading data.
    Writing, ///< Writing data.
    Wiping,  ///< Wiping page.
};

static __xdata enum Status l_status; ///< Status.

static __xdata uint16_t       l_IAPAddress;   ///< IAP address to operate.
static __xdata uint16_t       l_counter;      ///< Operation counter.
static __xdata uint8_t       *l_readPointer;  ///< Read output pointer.
static __xdata const uint8_t *l_writePointer; ///< Write input pointer.

/**
 * @brief       Initialize EEPROM.
 */
void initEEPROM(void)
{
    IAP_TPS   = IAP_TPS_VALUE;
    IAP_CONTR = 0xC0;

    l_status = Ready;
}

/**
 * @brief       Get EEPROM operation status.
 */
enum EEPROMOpStatus getEEPROMOperationStatus(void)
{
    switch ((l_status)) {
        case Ready:
            return EEPROMReady;
        case Error:
            return EEPROMError;
        default:
            return EEPROMBusy;
    }
}

/**
 * @brief       Start reading bytes.
 */
void startReadingEEPROM(uint16_t addr, void *buffer, uint16_t size)
{
    if (l_status != Ready && l_status != Error) {
        return;
    }

    // Copy arguments.
    l_IAPAddress  = addr;
    l_readPointer = buffer;
    l_counter     = size;

    // Change status.
    l_status = Reading;
}

/**
 * @brief       Start write bytes.
 */
void startWritingEEPROM(const void *data, uint16_t size, uint16_t addr)
{
    if (l_status != Ready && l_status != Error) {
        return;
    }

    // Copy arguments.
    l_IAPAddress   = addr;
    l_writePointer = data;
    l_counter      = size;

    // Change status.
    l_status = Writing;
}

/**
 * @brief       Wipe.
 */
void wipeEEPROM(uint16_t addr)
{
    if (l_status != Ready && l_status != Error) {
        return;
    }

    // Copy arguments.
    l_IAPAddress = addr;

    // Change status.
    l_status = Wiping;
}

/**
 * @brief   Status `Reading` handler.
 */
static void onReading(void)
{
    if (l_counter == 0) {
        l_status = Ready;
        IAP_CMD  = IAP_COMMAND_EMPTY;
        return;
    }

    // Adddress to operate.
    IAP_ADDRL = l_IAPAddress & 0xFF;
    IAP_ADDRH = (l_IAPAddress & 0xFF00 >> 8);

    // Command.
    IAP_CMD = IAP_COMMAND_READ;

    // Trigger.
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;
    __asm__("nop\r\n");

    // Check.
    if (IAP_CONTR & 0x10) {
        IAP_CONTR &= 0xEF;
        IAP_CMD  = IAP_COMMAND_EMPTY;
        l_status = Error;
    } else {
        *l_readPointer = IAP_DATA;
        --l_counter;
        ++l_readPointer;
        ++l_IAPAddress;
    }
}

/**
 * @brief   Status `Writing` handler.
 */
static void onWriting(void)
{
    if (l_counter == 0) {
        l_status = Ready;
        IAP_CMD  = IAP_COMMAND_EMPTY;
        return;
    }

    // Adddress to operate.
    IAP_ADDRL = l_IAPAddress & 0xFF;
    IAP_ADDRH = (l_IAPAddress & 0xFF00 >> 8);

    // Data to write.
    IAP_DATA = *l_writePointer;

    // Command.
    IAP_CMD = IAP_COMMAND_WRITE;

    // Trigger.
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;
    __asm__("nop\r\n");

    // Check.
    if (IAP_CONTR & 0x10) {
        IAP_CONTR &= 0xEF;
        IAP_CMD  = IAP_COMMAND_EMPTY;
        l_status = Error;
    } else {
        --l_counter;
        ++l_writePointer;
        ++l_IAPAddress;
    }
}

/**
 * @brief   Status `Wiping` handler.
 */
static void onWiping(void)
{
    // Adddress to wipe.
    IAP_ADDRL = l_IAPAddress & 0xFF;
    IAP_ADDRH = (l_IAPAddress & 0xFF00 >> 8);

    // Command.
    IAP_CMD = IAP_COMMAND_WIPE;

    // Trigger.
    IAP_TRIG = 0x5A;
    IAP_TRIG = 0xA5;
    __asm__("nop\r\n");

    // Check.
    if (IAP_CONTR & 0x10) {
        IAP_CONTR &= 0xEF;
        IAP_CMD  = IAP_COMMAND_EMPTY;
        l_status = Error;
    } else {
        l_status = Ready;
        IAP_CMD  = IAP_COMMAND_EMPTY;
    }
}

/**
 * @brief       EEPROM task.
 */
void eepromTask(void)
{
    switch ((l_status)) {
#define DISPATCH_STATUS(__status) \
    case __status: {              \
        on##__status();           \
    } break;

        DISPATCH_STATUS(Reading);
        DISPATCH_STATUS(Writing);
        DISPATCH_STATUS(Wiping);

#undef DISPATCH_STATUS
        default:
            break;
    }
}
