#pragma once

#include <stdint.h>

#include <platform.h>

/**
 * @brief       Initialize clock.
 */
extern void clock_init(void);

/**
 * @brief       Get system clock.
 *
 * @return      System steady clock time(microseconds).
 */
extern uint32_t get_system_clock(void);

/**
 * @brief       Timer0 ISR.
 */
extern void timer0_isr(void) __interrupt(INT_TIMER0);
