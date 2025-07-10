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

    T4T3M |= 0x02; // Timer 3 : 1T.
    TM3PS = 0x00;

    T3L = l_clockInitValue & 0xFF;
    T3H = (l_clockInitValue & 0xFF00) >> 8;

    // Enable timer3 interrupt.
    IE2 |= 0x20;
}

/**
 * @brief       Start fan.
 */
void startFan(void)
{
    // Start.
    T4T3M |= 0x08;
}

/**
 * @brief       Task to test fan.
 */
void testFanTask(void)
{
    static __xdata uint32_t oldCount     = 0;
    static __xdata uint8_t  status       = 0;
    uint32_t                currentCount = getSystemClock() / (500L * 1000);
    if (currentCount != oldCount) {
        switch (status) {
            case 0: {
                setFanPercentage(0);
            } break;
            case 1: {
                setFanPercentage(25);
            } break;
            case 2: {
                setFanPercentage(0);
            } break;
            case 3: {
                setFanPercentage(50);
            } break;
            case 4: {
                setFanPercentage(0);
            } break;
            case 5: {
                setFanPercentage(75);
            } break;
            case 6: {
                setFanPercentage(0);
            } break;
            case 7: {
                setFanPercentage(100);
            } break;
        }
        ++status;
        if (status > 7) {
            status = 0;
        }
    }
}

/**
 * @brief       Set PWM percentage of the fan.
 */
void setFanPercentage(uint8_t percentage)
{
    l_percentage = percentage;
}

/**
 * @brief       Timer0 ISR.
  : */
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
