#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

/**
 * @brief       Initialize display.
 */
extern void initDisplay(void);

/**
 * @brief       Start display.
 */
extern void startDisplay(void);

/**
 * @brief       Task to test display.
 */
extern void testDisplayTask(void);

/**
 * @brief       Set display temperature.
 *
 * @param[in]   temperature     Temperature.
 */
extern void setDisplayTemperature(float temperature);

/**
 * @brief       Set display error.
 */
extern void setDisplayError(void);

/**
 * @brief       Timer4 ISR.
 */
extern void displayTimer4ISR(void) __interrupt(INT_TIMER4);
