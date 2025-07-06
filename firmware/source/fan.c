#include <stdbool.h>

#include <clock.h>
#include <hd_math.h>

#include <fan.h>

#define MODE_MASK ((uint8_t)(1 << GPIO_BIT_FAN))

// Percentage.
static __data uint8_t l_percentage;
static __data uint8_t l_count;

#define PWM_FREQ  2000
#define TICK_TIME ((uint16_t)(1000000L / 2000 / 100))

#define l_clockInitValue (65536 - (IRC_FEQ / 1000000) * TICK_TIME)

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

    l_count      = 0;
    l_percentage = 0;

    // T4T3M |= 0x02;		//定时器时钟1T模式
    // T3L = 0x75;		//设置定时初始值
    // T3H = 0xF9;		//设置定时初始值
    // T4T3M |= 0x08;		//定时器3开始计时
}

/**
 * @brief       Start fan.
 */
void startFan(void) {}

/**
 * @brief       Task to test fan.
 */
void testFanTask(void) {}

/**
 * @brief       Set PWM percentage of the fan.
 */
void setFanPercentage(uint8_t percentage)
{
    l_percentage = percentage;
}

/**
 * @brief       Timer0 ISR.
 */
void fanTimer3ISR(void) __interrupt(INT_TIMER3)
{
    EA = 0;
    ++l_count;
    if (l_count > 100) {
        l_count = 0;
    }
    if (l_count < l_percentage) {
        GPIO_PORT_FAN = 0;
    } else {
        GPIO_PORT_FAN = 1;
    }
    EA = 1;
}
