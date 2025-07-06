#include <clock.h>

#include <status_led.h>

/**
 * @brief       Initialize status LED.
 */
void initSatusLED(void)
{
    // Set GPIO value.
    GPIO_PORT_STATUS_LED = 1;

    // Set GPIO mode.
    GPIO_MODE1_STATUS_LED |= 1 << GPIO_BIT_STATUS_LED;
    GPIO_MODE0_STATUS_LED |= 1 << GPIO_BIT_STATUS_LED;
}

/**
 * @brief       Task to test status LED.
 */
void testStatusLEDTask(void)
{
    static __xdata uint32_t oldTime     = 0;
    static __xdata bool     status      = false;
    uint32_t                currentTime = getSystemClock();
    if (currentTime - oldTime > 500 * 1000) {
        status = ! status;
        setStatusLED(status);
        oldTime = currentTime;
    }
}

/**
 * @brief       Set the status of status LED.
 */
void setStatusLED(bool on)
{
    GPIO_PORT_STATUS_LED = on ? 0 : 1;
}
