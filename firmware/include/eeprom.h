#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

/**
 * @brief   EEPROM operation status.
 */
enum EEPROMOpStatus {
    EEPROMReady, ///< EEPROM ready.
    EEPROMError, ///< EEPROM error.
    EEPROMBusy   ///< EEPROM busy.
};

/**
 * @brief       Initialize EEPROM.
 */
extern void initEEPROM(void);

/**
 * @brief       Get EEPROM operation status.
 *
 * @return      Status.
 */
extern enum EEPROMOpStatus getEEPROMOperationStatus(void);

/**
 * @brief       Start reading bytes.
 *
 * @param[in]   addr        IAP address to read.
 * @param[out]  buffer      Output buffer.
 * @param[in]   size        Size to read.
 */
extern void startReadingEEPROM(uint16_t addr, void *buffer, uint16_t size);

/**
 * @brief       Start write bytes.
 *
 * @param[in]   data        Data to write.
 * @param[in]   size        Data size.
 * @param[out]  addr        IAP address to write.
 */
extern void startWritingEEPROM(const void *data, uint16_t size, uint16_t addr);

/**
 * @brief       Wipe.
 *
 * @param[out]  addr        IAP address of the page to wipe.
 */
extern void wipeEEPROM(uint16_t addr);

/**
 * @brief       EEPROM task.
 */
extern void eepromTask(void);
