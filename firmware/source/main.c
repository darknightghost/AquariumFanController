#include <math.h>

#include <1-wire.h>
#include <clock.h>
#include <display.h>
#include <eeprom.h>
#include <fan.h>
#include <key.h>
#include <log.h>
#include <platform.h>
#include <record_fs.h>
#include <sensor.h>
#include <serial.h>
#include <status_led.h>

#include <test.h>

/**
 * @brief       Main loop.
 */
void mainLoop(void)
{
    __xdata uint32_t timeCost = getSystemClock();

    PRINT_LOG("All modules initialized, %lu microseconds costed.", timeCost);
    PRINT_LOG("Main loop started.");
    setStatusLED(true);
    setDisplayTemperature(NAN);
    while (1) {
        // Run tasks.
        sensorTask();
        keyTask();
        eepromTask();

        // Get sensor status.
        __xdata enum SensorStatus sensorStatus = getSensorTemperatureStatus();
        if (sensorStatus != SensorBusy) {
            if (sensorStatus == SensorReady) {
                setDisplayTemperature(getSensorTemperature());
            } else if (sensorStatus == SensorError) {
                setDisplayError();
            }
            startReadingSensor();
        }
        startReadingSensor();
    }
}

/**
 * @brief       Entery.
 *
 * @return      Not used.
 */
int main(void)
{
    initPlatform();

    if (needTest()) {
        testLoop();
    } else {
        mainLoop();
    }

    return 0;
}
