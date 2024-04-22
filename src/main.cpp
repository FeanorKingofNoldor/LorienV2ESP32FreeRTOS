#include <Arduino.h>
#include "WifiManager.h"
#include "RelayControlNozzle.h"
#include "LightControl.h"
#include "PressureSensor.h"
#include "SensorTasks.h"
#include "DataTransmission.h"

void setup() {
    Serial.begin(115200);

    // Initialize Wi-Fi connection and time synchronization
    WifiManager wifiManager;
    wifiManager.begin();
    
    // Initialize the relay control
    RelayControl relay;
    relay.begin();

    // Initialize the light control
    LightControl light;
    light.begin();

    // Start the light control task
    light.startTask();

    // Start the pressure sensor task
    PressureSensor::begin();

    // Start general sensor reading tasks
    SensorTasks::begin();

    // Initialize and start the data transmission task
    DataTransmission::begin();
}

void loop() {
    // Keep the loop empty as tasks are managed by FreeRTOS
    vTaskDelay(1000);  // This delay is just to prevent the loop from spinning.
}
