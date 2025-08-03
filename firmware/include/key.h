#pragma once

#include <stdint.h>

#include <platform.h>

/**
 * @brief       Initialize key.
 */
extern void initKey(void);

/**
 * @brief       Get key `UP` status.
 *
 * @return      If the key is pressed, a time count is returned,  if not,
 *              -1 is returned,
 */
extern int16_t getKeyUpStatus(void);

/**
 * @brief       Get key `DOWN` status.
 *
 * @return      If the key is pressed, a time count is returned,  if not,
 *              -1 is returned,
 */
extern int16_t getKeyDownStatus(void);

/**
 * @brief       Get key `SET` status.
 *
 * @return      If the key is pressed, a time count is returned,  if not,
 *              -1 is returned,
 */
extern int16_t getKeySetStatus(void);

/**
 * @brief       Key task.
 */
extern void keyTask(void);
