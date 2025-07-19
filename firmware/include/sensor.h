#pragma once

#include <stdbool.h>

#include <platform.h>

/**
 * @brief       Initialize sensor.
 */
extern void initSensor(void);

/**
 * @brief       Check if the temperature ready.
 */
extern bool isSensorTemperatureReady(void);

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
