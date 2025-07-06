#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#define GPIO_PORT_TEST P1_7

/**
 * @brief       Initialize test module.
 */
extern void initTest(void);

/**
 * @brief       Need test.
 */
extern bool needTest(void);

/**
 * @brief       Test loop.
 */
extern void testLoop(void);
