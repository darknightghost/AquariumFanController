#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

/**
 * @brief       Initialize fan.
 */
extern void initFan(void);

/**
 * @brief       Start fan.
 */
extern void startFan(void);

/**
 * @brief       Task to test fan.
 */
extern void testFanTask(void);

/**
 * @brief       Set PWM percentage of the fan.
 *
 * @param[in]   percentage  Percentage.
 */
extern void setFanPercentage(uint8_t percentage);

/**
 * @brief       Timer3 ISR.
 */
extern void fanTimer3ISR(void) __interrupt(INT_TIMER3);
