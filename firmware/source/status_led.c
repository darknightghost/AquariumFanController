#include <clock.h>

#include <status_led.h>

#define GPIO_PORT_STATUS_LED  P1_5
#define GPIO_BIT_STATUS_LED   5
#define GPIO_MODE1_STATUS_LED P1M1
#define GPIO_MODE0_STATUS_LED P1M0

#define MODE_MASK ((uint8_t)(1 << GPIO_BIT_STATUS_LED))

/**
 * @brief       Initialize status LED.
 */
void initStatusLED(void)
{
    // Set GPIO value.
    GPIO_PORT_STATUS_LED = 1;

    // Set GPIO mode.
    GPIO_MODE1_STATUS_LED &= ~MODE_MASK;
    GPIO_MODE0_STATUS_LED &= ~MODE_MASK;
}

/**
 * @brief       Task to test status LED.
 */
void testStatusLEDTask(void)
{
    static __xdata uint32_t oldCount     = 0;
    static __xdata bool     status       = false;
    __xdata uint32_t        currentCount = getSystemClock() / (500L * 1000);
    if (currentCount != oldCount) {
        setStatusLED(status);
        status   = ! status;
        oldCount = currentCount;
    }
}

/**
 * @brief       Set the status of status LED.
 */
void setStatusLED(bool on)
{
    GPIO_PORT_STATUS_LED = on ? 0 : 1;
}
