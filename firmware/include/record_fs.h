#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#define RECORD_FS_DATA_BLOCK_SIZE  8
#define RECORD_FS_SUPER_BLOCK_SIZE (RECORD_FS_DATA_BLOCK_SIZE * 2)

/**
 * @brief   Record.
 */
struct Record {
    int16_t targetTemperature; ///< Target temperature(0.01℃ ).
    uint8_t pwmPercentage;     ///< PWM percentage(percentage).
};

_Static_assert(sizeof(struct Record) <= RECORD_FS_DATA_BLOCK_SIZE,
               "Size of record too big.");

// Super block.
#define RECORD_FS_SUPER_BLOCK_MAGIC 0x5A

#define RECORD_FS_PAGE_STATUS_EMPTY 0xFF
#define RECORD_FS_PAGE_STATUS_USING 0xFE
#define RECORD_FS_PAGE_STATUS_SKIP  0xFC

/**
 * @brief   Super block.
 */
struct RecordFsSuperBlock {
    uint8_t magic;     ///< Magic(0x5A).
    uint8_t status;    ///< Pase status.
    uint8_t bitmap[8]; ///< Bitmap(The first two block has been used by super
                       ///< block).
};

_Static_assert(sizeof(struct RecordFsSuperBlock) <= RECORD_FS_SUPER_BLOCK_SIZE,
               "Size of super block too big.");

// Data block.
struct RecordFsDataBlock {
    struct Record record;   ///< Record.
    uint8_t       checksum; ///< Checksum.
};

_Static_assert(sizeof(struct RecordFsDataBlock) <= RECORD_FS_DATA_BLOCK_SIZE,
               "Size of data block too big.");

/**
 * @brief       Initialize record filesystem.
 */
extern void initRecordFs(void);

/**
 * @brief       Check if filesystem operation finished.
 */
extern bool isRecordFsOperationFinished();

/**
 * @brief       Start reading record.
 *
 * @param[out]  record      Record read.
 */
extern void startReadingRecord(struct Record *record);

/**
 * @brief       Start writing record.
 *
 * @param[in]   record      Record to write.
 */
extern void startWritingRecord(const struct Record *record);

/**
 * @brief       Record filesystem task.
 */
extern void recordFsTask(void);
