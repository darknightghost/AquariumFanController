#pragma once

#include <stdbool.h>

#include <platform.h>

/**
 * @brief   Bus operation status.
 */
enum SensorStatus {
    SensorInitialized, ///< Sensor initialize.
    SensorReady,       ///< Sensor ready.
    SensorError,       ///< Sensor error.
    SensorBusy         ///< Sensor busy.
};

/**
 * @brief       Initialize sensor.
 */
extern void initSensor(void);

/**
 * @brief       Get sensor temperature status.
 */
extern enum SensorStatus getSensorTemperatureStatus(void);

/**
 * @brief       Start reading sensor.
 */
extern void startReadingSensor(void);

/**
 * @brief       Get temperature.
 */
extern float getSensorTemperature(void);

/**
 * @brief       Sensor task.
 */
extern void sensorTask(void);

/**
 * @brief       Test sensor task.
 */
extern void testSensorTask(void);
