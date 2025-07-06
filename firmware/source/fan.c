#include <stdbool.h>

#include <fan.h>

#define MODE_MASK ((uint8_t)(1 << GPIO_BIT_FAN))

// Percentage.
static __data uint8_t l_percentage;

/**
 * @brief       Initialize fan.
 */
void initFan(void)
{
    // Set GPIO value.
    GPIO_PORT_FAN = 1;

    // Set GPIO mode.
    GPIO_MODE1_FAN &= ~MODE_MASK;
    GPIO_MODE0_FAN &= ~MODE_MASK;
}

/**
 * @brief       Fan pwm task.
 */
void fanTask(void) {}

/**
 * @brief       Task to test fan.
 */
void testFanTask(void)
{
    fanTask();
}

/**
 * @brief       Set PWM percentage of the fan.
 */
void setFanPercentage(uint8_t percentage)
{
    l_percentage = percentage;
}
