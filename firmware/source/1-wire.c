#include <platform.h>

#include <1-wire.h>

#define GPIO_PORT_BUS     P3_2
#define GPIO_PORT_BUS_BIT 2

#define GPIO_MODE1_BUS P3M1
#define GPIO_MODE0_BUS P3M0
#define MODE_MASK      (((uint8_t)1) << GPIO_PORT_BUS_BIT)

/// Time.
#define VALUE_MICROSECONDS(microseconds) \
    ((uint16_t)(65536 - (((uint32_t)IRC_FEQ) / 1000000) * (microseconds)))

#define TIMER_VALUE_RESET_PULL_DOWN VALUE_MICROSECONDS(500)

#define TIMER_VALUE_WRITE_RECORVER VALUE_MICROSECONDS(2)
#define TIMER_VALUE_WRITE_PULLDOWN VALUE_MICROSECONDS(5)
#define TIMER_VALUE_WRITE_BIT      VALUE_MICROSECONDS(55)

#define TIMER_VALUE_READ_RECORVER       VALUE_MICROSECONDS(2)
#define TIMER_VALUE_READ_PULLDOWN       VALUE_MICROSECONDS(5)
#define TIMER_VALUE_READ_SAMPLING_DELAY VALUE_MICROSECONDS(30)
#define TIMER_VALUE_READ_AFTER_SAMPLE   VALUE_MICROSECONDS(30)

/**
 * @brief   Status.
 *
 *        Call                            Timer1
 * Ready ------> ResettingMasterPullDown -------> ResettingMasterRelease
 *   ^                                                     |
 *   |                                                     | INT0
 *   |                                                     |
 *   |                INT0                                 v
 *   └------------------------------------------- ResettingSlavePullDown
 *
 *
 *         Call                  Timer1
 *  Ready -----> WritingRecover -------> WritingPullDown
 *   ^                ^                         |
 *   |                |                         | Timer1
 *   | Timer1         | Timer1                  |
 *   |                |                         V
 *   └----------------┴----------------- WritingWriteBit
 *
 *         Call                  Timer1
 *  Ready -----> ReadingRecover -------> ReadingMasterPullDown
 *   ^                ^                         |
 *   |                |                         | Timer1
 *   | Timer1         | Timer1                  |
 *   |                |                         V
 *   └--- ReadingMasterAfterSample <------ ReadingMasterSample
 *                                  Timer1
 *
 */
enum Status {
    Ready, ///< All operations ready.

    // Reset.
    ResettingMasterPullDown, ///< Resetting bus, master pull-down stage.
    ResettingMasterRelease,  ///< Resetting bus, master release stage
    ResettingSlavePullDown,  ///< Resetting bus, slave pull-down stage

    // Write
    WritingRecover,  ///< Writing data, recover stage.
    WritingPullDown, ///< Writing data, pull-down stage.
    WritingWriteBit, ///< Writing data, write bit stage.

    // Read.
    ReadingRecover,           ///< Reading data, recover stage.
    ReadingMasterPullDown,    ///< Reading data, master pull-down stage.
    ReadingMasterSample,      ///< Reading data, master sample stage.
    ReadingMasterAfterSample, ///< Reading data, master after sample stage.
};

// Status.
static __data enum Status l_status = Ready;

// Data to read/write.
static __data uint8_t l_data = 0;
// Bit offset.
static __data uint8_t l_bitOffset = 0;

/**
 * @brief       Initialize 1-wire bus module.
 */
void initOneWire(void)
{
    // Set GPIO value.
    GPIO_PORT_BUS = 1;

    // Set GPIO mode.
    P_SW2 |= 0x80;
    GPIO_MODE1_BUS &= ~MODE_MASK;
    GPIO_MODE0_BUS &= ~MODE_MASK;
    P_SW2 &= ~(uint8_t)0x80;

    // Initialize timer 1.
    // 1T mode.
    AUXR |= 0x40;

    // 16bit, not reload.
    TMOD &= 0x0F;
    TMOD |= 0x10;

    // Not running.
    TF1 = 0;
    TR1 = 0;

    // Set timeer 1 to the higest priority.
    IP |= 0x08;
    IPH |= 0x08;

    // Enable timer1 interrupt.
    ET1 = 1;

    // Initialize INT0.
    // Set INT0 to the higest priority.
    IP |= 0x02;
    IPH |= 0x02;

    // Interrupt when level changed.
    IT0 = 0;

    // Disable INT0.
    EX0 = 0;
}

/**
 * @brief       Check if 1-wire bus operation finished.
 */
bool isOneWireOperationFinished(void)
{
    __xdata bool ret;
    __sbit       oldEA = EA;
    EA                 = 0;
    ret                = l_status == Ready;
    EA                 = oldEA;

    return ret;
}

/**
 * @brief       Pull down the bus and wait for timer.
 *
 * @param[in]   value   Timer value.
 */
static inline void pullDownWaitForTimer(uint16_t value)
{
    TL1           = (value) & 0xFF;
    TH1           = ((value) & 0xFF00) >> 8;
    GPIO_PORT_BUS = 0;
    TR1           = 1;
}

/**
 * @brief       Release the bus and wait for timer.
 *
 * @param[in]   value   Timer value.
 */
static inline void releaseWaitForTimeer(uint16_t value)
{
    TL1           = (value) & 0xFF;
    TH1           = ((value) & 0xFF00) >> 8;
    GPIO_PORT_BUS = 1;
    TR1           = 1;
}

/**
 * @brief       Release the bus and wait for change.
 */
static inline void releaseWaitForChange()
{
    GPIO_PORT_BUS = 1;
    IE0           = 0;
    EX0           = 1;
}

/**
 * @brief       Start reset.
 */
void startResetOneWire(void)
{
    if (l_status != Ready) {
        return;
    }

    // Change status.
    l_status = ResettingMasterPullDown;

    // Pull down and wait.
    pullDownWaitForTimer(TIMER_VALUE_RESET_PULL_DOWN);
}

/**
 * @brief       Start writing one byte.
 */
void startWriteOneWire(uint8_t data)
{
    if (l_status != Ready) {
        return;
    }

    // Copy data to buffer.
    l_data      = data;
    l_bitOffset = 0;

    // Change status.
    l_status = WritingRecover;

    // Wait.
    releaseWaitForTimeer(TIMER_VALUE_WRITE_RECORVER);
}

/**
 * @brief       Start reading one byte.
 */
void startReadOneWire(void)
{
    if (l_status != Ready) {
        return;
    }

    // Clear buffer.
    l_data      = 0x00;
    l_bitOffset = 0x00;

    // Change status.
    l_status = ReadingRecover;

    // Wait.
    releaseWaitForTimeer(TIMER_VALUE_READ_RECORVER);
}

/**
 * @brief       Get data read.
 */
uint8_t getDataOneWireRead(void)
{
    return l_data;
}

/**
 * @brief   Status `ResettingMasterPullDown` handler.
 */
static inline void onResettingMasterPullDown(void)
{
    l_status = ResettingMasterRelease;
    releaseWaitForChange();
}

/**
 * @brief   Status `ResettingMasterRelease` handler.
 */
static inline void onResettingMasterRelease(void)
{
    if (GPIO_PORT_BUS == 0) {
        l_status = ResettingSlavePullDown;
        releaseWaitForChange();
    }
}

/**
 * @brief   Status `ResettingSlavePullDown` handler.
 */
static inline void onResettingSlavePullDown(void)
{
    if (GPIO_PORT_BUS == 1) {
        l_status = Ready;
    }
}

/**
 * @brief   Status `WritingRecover` handler.
 */
static inline void onWritingRecover(void)
{
    l_status = WritingPullDown;
    pullDownWaitForTimer(TIMER_VALUE_WRITE_PULLDOWN);
}

/**
 * @brief   Status `WritingPullDown` handler.
 */
static inline void onWritingPullDown(void)
{
    l_status = WritingWriteBit;
    if (l_data & 0x01) {
        // Write 1.
        releaseWaitForTimeer(TIMER_VALUE_WRITE_BIT);
    } else {
        // Write 0.
        pullDownWaitForTimer(TIMER_VALUE_WRITE_BIT);
    }
}

/**
 * @brief   Status `WritingWriteBit` handler.
 */
static inline void onWritingWriteBit(void)
{
    ++l_bitOffset;
    if (l_bitOffset < 8) {
        l_status = WritingRecover;
        l_data >>= 1;
        releaseWaitForTimeer(TIMER_VALUE_WRITE_RECORVER);
    } else {
        l_status = Ready;
    }
}

/**
 * @brief   Status `ReadingRecover` handler.
 */
static inline void onReadingRecover(void)
{
    l_status = ReadingMasterPullDown;
    pullDownWaitForTimer(TIMER_VALUE_READ_PULLDOWN);
}

/**
 * @brief   Status `ReadingMasterPullDown` handler.
 */
static inline void onReadingMasterPullDown(void)
{
    l_status = ReadingMasterSample;
    releaseWaitForTimeer(TIMER_VALUE_READ_SAMPLING_DELAY);
}

/**
 * @brief   Status `ReadingMasterSample` handler.
 */
static inline void onReadingMasterSample(void)
{
    if (GPIO_PORT_BUS) {
        // Read 1.
        l_data |= (0x01 << l_bitOffset);
    }
    ++l_bitOffset;
    l_status = ReadingMasterAfterSample;
    releaseWaitForTimeer(TIMER_VALUE_READ_AFTER_SAMPLE);
}

/**
 * @brief   Status `ReadingMasterAfterSample` handler.
 */
static inline void onReadingMasterAfterSample(void)
{
    if (l_bitOffset < 8) {
        l_status = ReadingRecover;
        releaseWaitForTimeer(TIMER_VALUE_READ_RECORVER);
    } else {
        l_status = Ready;
    }
}

/**
 * @brief   Dispatch status.
 */
static inline void dispatchStatus(void)
{
    switch (l_status) {
#define DISPATCH_STATUS(__status) \
    case __status: {              \
        on##__status();           \
    } break;

        DISPATCH_STATUS(ResettingMasterPullDown);
        DISPATCH_STATUS(ResettingMasterRelease);
        DISPATCH_STATUS(ResettingSlavePullDown);
        DISPATCH_STATUS(WritingRecover);
        DISPATCH_STATUS(WritingPullDown);
        DISPATCH_STATUS(WritingWriteBit);
        DISPATCH_STATUS(ReadingRecover);
        DISPATCH_STATUS(ReadingMasterPullDown);
        DISPATCH_STATUS(ReadingMasterSample);
        DISPATCH_STATUS(ReadingMasterAfterSample);

#undef DISPATCH_STATUS
        default:
            return;
    }
}

/**
 * @brief       Timer2 ISR.
 */
void oneWireTimer1ISR(void) __interrupt(INT_TIMER1)
{
    EA = 0;
    dispatchStatus();
    EA = 1;
}

/**
 * @brief       INT0 ISR.
 */
void oneWireINT0ISR(void) __interrupt(INT_INT0)
{
    EA  = 0;
    EX0 = 0;
    dispatchStatus();
    EA = 1;
}
