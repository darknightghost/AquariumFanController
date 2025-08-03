#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <platform.h>

#define RECORD_FS_DATA_BLOCK_SIZE  8
#define RECORD_FS_SUPER_BLOCK_SIZE (RECORD_FS_DATA_BLOCK_SIZE * 2)
#define RECORD_FS_IAP_BEGIN        0x4000
#define RECORD_FS_IAP_END          (64 * 1024)

/**
 * @brief   Record.
 */
struct Record {
    int16_t targetTemperature; ///< Target temperature(0.01℃ ).
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

/**
 * @brief    Data block.
 */
struct RecordFsDataBlock {
    struct Record record;   ///< Record.
    uint8_t       checksum; ///< Checksum.
};

_Static_assert(sizeof(struct RecordFsDataBlock) <= RECORD_FS_DATA_BLOCK_SIZE,
               "Size of data block too big.");

/**
 * @brief   Filesystem status.
 */
enum RecordFsStatus {
    RecordFsStatusBusy,   ///< Busy.
    RecordFsStatusReady,  ///< Ready for next operation.
    RecordFsStatusNoData, ///< No data saved.
    RecordFsStatusError   ///< Error.
};

/**
 * @brief       Initialize record filesystem.
 */
extern void initRecordFs(void);

/**
 * @brief       Get record filesystem status.
 *
 * @return      Status.
 */
extern enum RecordFsStatus recordFsStatus(void);

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
