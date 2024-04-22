#include "SensorTasks.h"
#include "SensorData.h"  // Include shared data structure and semaphore definitions
#include "PressureSensor.h"

SemaphoreHandle_t sensorDataMutex;  // You can initialize here or in the setup function
SensorData sharedSensorData;        // Global instance


extern float globalPressurePSI;  // Use the global variable from PressureSensor.cpp
extern SemaphoreHandle_t pressureDataMutex;  // Use the same mutex for protecting global pressure data

// Implementation of the private static task function
void SensorTasks::readSensorsTask(void *parameter) {
    const TickType_t xFrequency = pdMS_TO_TICKS(60000);
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    for (;;) {
        if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY)) {
            if (xSemaphoreTake(pressureDataMutex, portMAX_DELAY)) {
                sharedSensorData.pressure = globalPressurePSI;
                xSemaphoreGive(pressureDataMutex);
            }

            // Additional sensor readings can be implemented here
            // sharedSensorData.temperature = readTemperatureSensor();
            // sharedSensorData.humidity = readHumiditySensor();

            sharedSensorData.readyToSend = true;
            xSemaphoreGive(sensorDataMutex);
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// Static method to create and start the task
void SensorTasks::begin() {
    xTaskCreate(readSensorsTask, "Sensor Readings", 2048, NULL, 1, NULL);
}
