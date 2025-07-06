#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#define GPIO_PORT_STATUS_LED  P1_5
#define GPIO_BIT_STATUS_LED   5
#define GPIO_MODE1_STATUS_LED P1M1
#define GPIO_MODE0_STATUS_LED P1M0

/**
 * @brief       Initialize status LED.
 */
extern void initSatusLED(void);

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
