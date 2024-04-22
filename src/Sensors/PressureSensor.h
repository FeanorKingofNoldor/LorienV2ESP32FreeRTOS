#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

extern SemaphoreHandle_t pressureDataMutex;
extern float globalPressurePSI; // Global storage for pressure data

class PressureSensor {
public:
    static void begin();
    static void PressureSensorTask(void *parameter);
};

#endif
