#include "DataTransmission.h"
#include "SensorData.h"

extern SemaphoreHandle_t sensorDataMutex;
extern SensorData sharedSensorData;  // Ensure this is properly defined and includes the necessary data

void DataTransmission::transmitDataTask(void *parameter) {
    for (;;) {
        if (xSemaphoreTake(sensorDataMutex, portMAX_DELAY)) {
            if (sharedSensorData.readyToSend) {
                // sendSensorDataToAPI(sharedSensorData);  // Implement this function to handle API communication
                sharedSensorData.readyToSend = false;
            }
            xSemaphoreGive(sensorDataMutex);
        }
        vTaskDelay(pdMS_TO_TICKS(5000));  // Run this task every 5 seconds
    }
}

void DataTransmission::begin() {
    xTaskCreate(transmitDataTask, "Data Transmission", 2048, NULL, 1, NULL);
}
