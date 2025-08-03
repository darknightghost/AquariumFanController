#include <record_fs.h>

#include <eeprom.h>

/**
 * @brief   Task status.
 */
enum TaskStatus {
    Ready,          ///< Operation ready.
                    // Mount.
    MountScanPage,  ///< Scan for data page.
    MountScanBlock, ///< Scan for data block.

    // Format.
    FormatWipe,             ///< Wipe page.
    FormatWrite,            ///< Write initial super block.
    FormatUpdateReadCache,  ///< Update read cache.
    FormatUpdateWriteCache, ///< Update write cache.

    // Read.
    ReadLoadSuperblock, ///< Read superblock.
    ReadSearchBlock,    ///< Read block.

    // Write.
    WriteSuperBlock,      ///< Write superblock.
    WriteCheckSuperBlock, ///< Check superblock written.
    WriteDataBlock,       ///< Write data block.
    WriteCheckDataBlock,  ///< Check data block written.
};

/**
 * @brief   Mount data.
 */
struct MountData {
    uint16_t                  currentPage;    ///< IAP address of current page.
    struct RecordFsSuperBlock superblockRead; ///< Superblock read.
};

/**
 * @brief   Format data.
 */
struct FormatData {
    uint16_t                  currentPage; ///< IAP address of current page.
    struct RecordFsSuperBlock superblockToWrite; ///< Superblock to write.
};

/**
 * @brief   Read data.
 */
struct ReadData {
    struct Record            *buffer;         ///< Output buffer.
    struct RecordFsSuperBlock superblockRead; ///< Superblock read.
    struct RecordFsDataBlock  dataBlockRead;  ///< Data block read.
    uint16_t                  blockIndex;     ///< Block index.
};

/**
 * @brief   Write data.
 */
struct WriteData {
    const struct Record      *data;              ///< Data to write.
    struct RecordFsSuperBlock superblockToWrite; ///< Superblock to write.
    struct RecordFsSuperBlock superblockRead;    ///< Superblock read.
    struct RecordFsDataBlock  dataBlockToWrite;  ///< Data block to write.
    struct RecordFsDataBlock  dataBlockRead;     ///< Data block read to check.
};

/**
 * @brief   Filesystem task data.
 */
union TaskData {
    struct MountData  mountData;  ///< Data of mount task.
    struct FormatData formatData; ///< Data of format task.
    struct ReadData   readData;   ///< Data of read task.
    struct WriteData  writeData;  ///< Data of write task.
};

/**
 * @brief   Filesystem task.
 */
struct FsTask {
    enum TaskStatus status; ///< Task status.
    union TaskData  data;   ///< Task data.
};

/**
 * @brief   Previous operation result.
 */
enum OperationResult {
    Success, ///< Operation successed.
    NoData,  ///< No data.
    Error    ///< Error occured.
};

// Task.
static __xdata uint16_t l_currentPage; ///< IAP address of current page.

static __xdata struct FsTask        l_taskStack[2]; ///< Task stack.
static __xdata int8_t               l_taskStackPos; ///< Position of task stack.
static __xdata enum OperationResult l_operationResult; ///< Operation result.

/**
 * @brief       Initialize record filesystem.
 */
void initRecordFs(void)
{
    // Set mount task.
    l_taskStack[0].status                     = MountScanPage;
    l_taskStack[0].data.mountData.currentPage = RECORD_FS_IAP_BEGIN;
    l_taskStackPos                            = 0;
    l_operationResult                         = Success;
}

/**
 * @brief       Get record filesystem status.
 */
enum RecordFsStatus recordFsStatus(void)
{
    if (l_taskStackPos == -1) {
        if (l_operationResult == NoData) {
            return RecordFsStatusNoData;
        } else if (l_operationResult == Error) {
            return RecordFsStatusError;
        } else {
            return RecordFsStatusReady;
        }
    } else {
        return RecordFsStatusBusy;
    }
}

/**
 * @brief       Start reading record.
 */
void startReadingRecord(struct Record *record)
{
    if (l_taskStackPos != -1) {
        return;
    }
}

/**
 * @brief       Start writing record.
 */
void startWritingRecord(const struct Record *record)
{
    if (l_taskStackPos != -1) {
        return;
    }
}

/**
 * @brief       Record filesystem task.
 */
void recordFsTask(void) {}
