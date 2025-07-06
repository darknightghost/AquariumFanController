#pragma once

#include <stdint.h>

#include <platform.h>

#define SYS_TICK 10

/**
 * @brief       Initialize clock.
 */
extern void initClock(void);

/**
 * @brief       Start clock.
 */
extern void startClock(void);

/**
 * @brief       Get system clock.
 *
 * @return      System steady clock time(microseconds).
 */
extern uint32_t getSystemClock(void);

/**
 * @brief       Timer0 ISR.
 */
extern void clockTimer0ISR(void) __interrupt(INT_TIMER0);
