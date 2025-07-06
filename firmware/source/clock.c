#include <platform.h>

#include <clock.h>

#include <status_led.h>

/// System time.
static __data uint32_t l_systemTime;

/// Clock initial value.
#define l_clockInitValue (65536 - (IRC_FEQ / 1000000) * SYS_TICK)

/**
 * @brief       Initialize clock.
 */
void initClock(void)
{
    l_systemTime = 0;

    // Stop timer 0.
    TR0 = 0;

    // Set timer 0 to 1T mode.
    AUXR |= 0x80;

    // Set timer0 to 16bit reload mode, use as timer, ignore INT0.
    TMOD &= 0xF0;

    // Set timer 0 initial value.
    TL0 = l_clockInitValue & 0xFF;
    TH0 = l_clockInitValue >> 8;

    ET0 = 1;
}

/**
 * @brief       Start clock.
 */
void startClock(void)
{
    // Start timer 0.
    TF0 = 0;
    TR0 = 1;
}

/**
 * @brief       Get system clock.
 */
uint32_t getSystemClock(void)
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
void clockTimer0ISR(void) __interrupt(INT_TIMER0)
{
    EA = 0;
    l_systemTime += SYS_TICK;
    EA = 1;
}
