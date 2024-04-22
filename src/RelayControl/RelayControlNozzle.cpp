#include "RelayControlNozzle.h"
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include <time.h>

RelayControl::RelayControl() : _relayPin(17) {}  // Default pin number

void RelayControl::begin() {
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, HIGH);  // Start with the relay ON

    _timer = xTimerCreate("RelayTimer", pdMS_TO_TICKS(15000), pdFALSE, (void*)this, relayTimerCallback);
    if (_timer == NULL) {
        Serial.println("Failed to create the timer for RelayControl");
    } else {
        xTimerStart(_timer, 0);
    }
}

// Callback function for the relay timer
void RelayControl::relayTimerCallback(TimerHandle_t xTimer) {
    static bool relayIsOn = true; // Static variable to track relay state
    RelayControl *relayControl = (RelayControl *)pvTimerGetTimerID(xTimer);
    struct tm timeinfo; // Structure to hold the time

    if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
    }

    char buffer[64]; // Buffer to hold the formatted time
    strftime(buffer, sizeof(buffer), "%A, %B %d %Y %H:%M:%S", &timeinfo); // Format the time

    if (relayIsOn) {
        // Turn the relay OFF
        digitalWrite(relayControl->_relayPin, LOW);
        Serial.print("Relay is OFF - ");
        Serial.println(buffer); // Print relay status with the current time
        // Reconfigure timer for 120 seconds OFF duration
        xTimerChangePeriod(xTimer, pdMS_TO_TICKS(1000000), 0);
        relayIsOn = false; // Update state
    } else {
        // Turn the relay ON
        digitalWrite(relayControl->_relayPin, HIGH);
        Serial.print("Relay is ON - ");
        Serial.println(buffer); // Print relay status with the current time
        // Reconfigure timer for 15 seconds ON duration
        xTimerChangePeriod(xTimer, pdMS_TO_TICKS(15000), 0);
        relayIsOn = true; // Update state
    }
}