#pragma once

#include <stdbool.h>

#include <platform.h>

/**
 * @brief       Initialize 1-wire bus module.
 */
extern void initOneWire(void);

/**
 * @brief       Check if 1-wire bus operation finished.
 *
 * @return      \c true if finished.
 */
extern bool isOneWireOperationFinished(void);

/**
 * @brief       Start reset.
 */
extern void startResetOneWire(void);

/**
 * @brief       Start writing one byte.
 *
 * @param[in]   data    Data to write.
 */
extern void startWriteOneWire(uint8_t data);

/**
 * @brief       Start reading one byte.
 */
extern void startReadOneWire(void);

/**
 * @brief       Get data read.
 *
 * @return      Data read.
 */
extern uint8_t getDataOneWireRead(void);

/**
 * @brief       Timer2 ISR.
 */
extern void oneWireTimer1ISR(void) __interrupt(INT_TIMER1);

/**
 * @brief       INT0 ISR.
 */
extern void oneWireINT0ISR(void) __interrupt(INT_INT0);
