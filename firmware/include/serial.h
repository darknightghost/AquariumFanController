#pragma once

#include <stdbool.h>

#include <platform.h>

/**
 * @brief       Initialize serial.
 */
extern void initSerial(void);

/**
 * @brief       Start serial.
 */
extern void startSerial(void);

/**
 * @brief       Check if the serial is busy.
 */
extern bool isSerialBusy(void);

/**
 * @brief       Start writing serial.
 *
 * @param[in]   data    Data to write.
 * @param[in]   size    Size to write.
 */
extern void startWritingSerial(const void *data, uint16_t size);

/**
 * @brief       UART 1 ISR.
 */
extern void uart1ISR(void) __interrupt(INT_UART1);

/**
 * @brief       Task to test serial.
 */
extern void testSerialTask(void);
