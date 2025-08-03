#include <display.h>
#include <fan.h>
#include <sensor.h>
#include <serial.h>
#include <status_led.h>

#include <test.h>

/**
 * @brief       Initialize test module.
 */
void initTest(void)
{
    GPIO_PORT_TEST = 1;
}

/**
 * @brief       Need test.
 */
bool needTest(void)
{
    return GPIO_PORT_TEST == 0;
}

/**
 * @brief       Test loop.
 */
void testLoop(void)
{
    while (1) {
        // Call test tasks.
        testStatusLEDTask();
        testFanTask();
        testDisplayTask();
        testSensorTask();
        testSerialTask();
    }
}
