#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

/**
 * @brief       Initialize status LED.
 */
extern void initStatusLED(void);

/**
 * @brief       Task to test status LED.
 */
extern void testStatusLEDTask(void);

/**
 * @brief       Set the status of status LED.
 *
 * @param[in]   on  LED status.
 */
extern void setStatusLED(bool on);
