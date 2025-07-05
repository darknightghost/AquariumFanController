#include <platform.h>

#include <clock.h>

/// System time.
static __data uint32_t l_systemTime;

/**
 * @brief       Initialize clock.
 */
void clock_init(void)
{
    l_systemTime = 0;
}

/**
 * @brief       Get system clock.
 */
uint32_t get_system_clock(void)
{
    // Lock.
    EA = 0;

    // Get return value.
    uint32_t ret = l_systemTime;

    // Unlock.
    EA = 1;

    return ret;
}

/**
 * @brief       Timer0 ISR.
 */
void timer0_isr(void) __interrupt(INT_TIMER0)
{
    EA = 0;
    l_systemTime += 20;
    EA = 1;
}
