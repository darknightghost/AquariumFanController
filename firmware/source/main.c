#include <1-wire.h>
#include <clock.h>
#include <display.h>
#include <fan.h>
#include <platform.h>
#include <sensor.h>
#include <status_led.h>

#include <test.h>

/**
 * @brief       Main loop.
 */
void mainLoop(void)
{
    setStatusLED(true);
    while (1) {
        // Run tasks.
        sensorTask();

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
