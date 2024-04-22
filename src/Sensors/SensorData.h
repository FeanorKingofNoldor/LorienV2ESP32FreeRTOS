#ifndef SENSOR_DATA_H
#define SENSOR_DATA_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

struct SensorData {
    float pressure;
    float temperature;
    float humidity;
    bool readyToSend;  // Flag to indicate data is ready for sending
};

// Mutex for data synchronization
extern SemaphoreHandle_t sensorDataMutex;
extern SensorData sharedSensorData;

void readSensorsTask(void *parameter);
void transmitDataTask(void *parameter);

#endif
