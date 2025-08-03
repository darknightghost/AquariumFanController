#pragma once

#include <stdarg.h>
#include <stdbool.h>

#include <platform.h>
#include <serial.h>

#include <log.h>

/**
 * @brief       Initialize log.
 */
extern void initLog(void);

/**
 * @brief       Print log.
 *
 * @param[in]   file    Source file.
 * @param[in]   line    Line number.
 * @param[in]   fmt     Format.
 * @param[in]   ...     Variable arguments.
 */
extern void printLog(const char *file, uint16_t line, const char *fmt, ...);

#define PRINT_LOG(fmt, ...) printLog(__FILE__, __LINE__, (fmt), ##__VA_ARGS__)
