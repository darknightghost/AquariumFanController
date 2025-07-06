#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#define GPIO_PORT_FAN  P1_3
#define GPIO_BIT_FAN   3
#define GPIO_MODE1_FAN P1M1
#define GPIO_MODE0_FAN P1M0

/**
 * @brief       Initialize fan.
 */
extern void initFan(void);

/**
 * @brief       Fan pwm task.
 */
extern void fanTask(void);

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
