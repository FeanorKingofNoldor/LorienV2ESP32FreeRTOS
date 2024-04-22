#include "PressureSensor.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

const int sensorPin = 39; // Specify the ADC pin here

// Global variable and mutex declaration
float globalPressurePSI = 0.0; // Global storage for pressure data in PSI
SemaphoreHandle_t pressureDataMutex; // Mutex to protect access to the pressure data

void PressureSensor::begin() {
    pressureDataMutex = xSemaphoreCreateMutex(); // Create the mutex
    xTaskCreate(
        PressureSensorTask,          // Task function
        "Pressure Sensor Reading",   // Name of the task
        2048,                        // Stack size in words
        NULL,                        // Task input parameter
        1,                           // Priority of the task
        NULL);                       // Task handle
}

void PressureSensor::PressureSensorTask(void *parameter) {
    Serial.begin(115200);
    analogReadResolution(12);  // Set ADC resolution to 12 bits

    for (;;) {  // Infinite task loop for continuous pressure monitoring
        int sensorValue = 0;
        const int numReadings = 10;
        for (int i = 0; i < numReadings; i++) {
            sensorValue += analogRead(sensorPin);  // Sum readings
            vTaskDelay(pdMS_TO_TICKS(10));  // Delay between readings to reduce noise and load
        }
        sensorValue /= numReadings;  // Average the readings

        // Adjust the conversion factor based on multimeter measurement
        float measuredVref = 3.3 * (2.07 / 1.84); // Adjusted based on your measurement comparison
        float voltage = sensorValue * (measuredVref / 4095.0);  // Use the measured Vref for conversion

        // Calculate pressure in psi based on new voltage range
        float pressure_psi = (voltage - 0.25) * (100 / (2.25 - 0.25));  // Adjust the baseline if necessary
        // Convert psi to bar
        float pressure_bar = pressure_psi / 14.5;

        // Protect global pressure update with mutex
        if (xSemaphoreTake(pressureDataMutex, portMAX_DELAY)) {
            globalPressurePSI = pressure_psi;
            xSemaphoreGive(pressureDataMutex);
        }

        // Output the calculated values to the Serial Monitor
        Serial.print("Voltage: "); Serial.println(voltage);
        Serial.print("Pressure (psi): "); Serial.println(pressure_psi);
        Serial.print("Pressure (bar): "); Serial.println(pressure_bar);

        vTaskDelay(pdMS_TO_TICKS(10000));  // Delay 10 seconds between readings
    }
}
