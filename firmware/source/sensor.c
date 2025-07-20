#include <1-wire.h>
#include <clock.h>

#include <status_led.h>

#include <sensor.h>

#define CONVERT_TIME ((uint32_t)750000L)

/**
 * @brief   Status.
 */
enum Status {
    Initialized,         ///< Only initialized.
    ResettingWrite,      ///< Resetting for write.
    SendConvertTemp0xCC, ///< Sending 0xcc(convert temperature).
    SendConvertTemp0x44, ///< Sending 0x44(convert temperature).
    ConvertBegin,        ///< Begin to wait for convert temperature.
    ConvertDelay,        ///< Waiting for convert temperature.
    ResettingRead,       ///< Resetting for read.
    SendReadTemp0xCC,    ///< Sending 0xcc(read temperature).
    SendReadTemp0xBE,    ///< Sending 0xcc(read temperature).
    ReadTempTL,          ///< Read low 8 bits of temperature.
    ReadTempTH,          ///< Read low 8 bits of temperature.
    Ready,               ///< Temperature ready.
    Error,               ///< Sensor read error.
};

/**
 * @brief   Read buffer.
 */
union ReadBuffer {
    uint16_t value;
    uint8_t  bytes[2];
};

/// Status.
static __xdata enum Status l_status;

/// Temperature.
static __xdata float l_temperature;

/// Read buffer.
static __xdata union ReadBuffer l_buffer;

/// Timestamp convert begin.
static __xdata uint32_t l_beginConvertTime = 0;

/**
 * @brief       Initialize sensor.
 */
void initSensor(void)
{
    l_status           = Initialized;
    l_beginConvertTime = 0;
    l_temperature      = 0.0;
}

/**
 * @brief       Get sensor temperature status.
 */
enum SensorStatus getSensorTemperatureStatus(void)
{
    if (l_status == Initialized) {
        return SensorInitialized;
    } else if (l_status == Ready) {
        return SensorReady;
    } else if (l_status == Error) {
        return SensorError;
    } else {
        return SensorBusy;
    }
}

/**
 * @brief       Start reading sensor.
 */
void startReadingSensor(void)
{
    if ((l_status != Ready) && (l_status != Initialized)
        && (l_status != Error)) {
        return;
    }
    l_buffer.value = 0x0000;
    l_status       = ResettingWrite;
    startResetOneWire();
}

/**
 * @brief       Get temperature.
 */
float getSensorTemperature(void)
{
    return l_temperature;
}

/**
 * @brief   Status `ResettingWrite` handler.
 */
static inline void onResettingWrite(void)
{
    l_status = SendConvertTemp0xCC;
    startWriteOneWire(0xCC);
}

/**
 * @brief   Status `SendConvertTemp0xCC` handler.
 */
static inline void onSendConvertTemp0xCC(void)
{
    l_status = SendConvertTemp0x44;
    startWriteOneWire(0x44);
}

/**
 * @brief   Status `SendConvertTemp0x44` handler.
 */
static inline void onSendConvertTemp0x44(void)
{
    l_status = ConvertBegin;
}

/**
 * @brief   Status `ConvertBegin` handler.
 */
static inline void onConvertBegin(void)
{
    l_beginConvertTime = getSystemClock();
    l_status           = ConvertDelay;
}

/**
 * @brief   Status `ConvertDelay` handler.
 */
static inline void onConvertDelay(void)
{
    if (getSystemClock() - l_beginConvertTime < CONVERT_TIME) {
        return;
    }

    l_status = ResettingRead;
    startResetOneWire();
}

/**
 * @brief   Status `ResettingRead` handler.
 */
static inline void onResettingRead(void)
{
    l_status = SendReadTemp0xCC;
    startWriteOneWire(0xCC);
}

/**
 * @brief   Status `SendReadTemp0xCC` handler.
 */
static inline void onSendReadTemp0xCC(void)
{
    l_status = SendReadTemp0xBE;
    startWriteOneWire(0xBE);
}

/**
 * @brief   Status `SendReadTemp0xBE` handler.
 */
static inline void onSendReadTemp0xBE(void)
{
    l_status = ReadTempTL;
    startReadOneWire();
}

/**
 * @brief   Status `SendReadTempTL` handler.
 */
static inline void onReadTempTL(void)
{
    // Get data read.
    l_buffer.bytes[0] = getDataOneWireRead();

    // Nest status.
    l_status = ReadTempTH;
    startReadOneWire();
}

/**
 * @brief   Status `SendReadTempTH` handler.
 */
static inline void onReadTempTH(void)
{
    // Get data read.
    l_buffer.bytes[1] = getDataOneWireRead();

    // Convert temperature.
    if (l_buffer.value & 0x8000) {
        // Below zero.
        l_temperature = -((float)(~l_buffer.value)) * 0.0625;
    } else {
        // Above zero.
        l_temperature = ((float)(l_buffer.value)) * 0.0625;
    }

    // Nest status.
    l_status = Ready;
}

/**
 * @brief       Sensor task.
 */
static inline void dispatchSensorTask(void)
{
    switch (l_status) {
#define DISPATCH_STATUS(__status) \
    case __status: {              \
        on##__status();           \
    } break;

        DISPATCH_STATUS(ResettingWrite);
        DISPATCH_STATUS(SendConvertTemp0xCC);
        DISPATCH_STATUS(SendConvertTemp0x44);
        DISPATCH_STATUS(ConvertBegin);
        DISPATCH_STATUS(ConvertDelay);
        DISPATCH_STATUS(ResettingRead);
        DISPATCH_STATUS(SendReadTemp0xCC);
        DISPATCH_STATUS(SendReadTemp0xBE);
        DISPATCH_STATUS(ReadTempTL);
        DISPATCH_STATUS(ReadTempTH);

#undef DISPATCH_STATUS
        default:
            return;
    }
}

/**
 * @brief       Sensor task.
 */
void sensorTask(void)
{
    __xdata enum BusOpStatus busStatus = getOneWireOperationStatus();
    if (busStatus == BusReady) {
        dispatchSensorTask();
    } else if (busStatus == BusError) {
        l_status = Error;
    }
}

/**
 * @brief       Test sensor task.
 */
void testSensorTask(void)
{
    sensorTask();

    static __xdata uint32_t oldCount = 0;
    __xdata uint32_t currentCount    = getSystemClock() / (2L * 1000L * 1000);
    if (currentCount != oldCount) {
        startReadingSensor();
    }
}
