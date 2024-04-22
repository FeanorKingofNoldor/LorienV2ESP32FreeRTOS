#include "RelayControlPressure.h"

RelayControlPressure::RelayControlPressure(int sensorPin, int relayPin, float activationThreshold, float deactivationThreshold)
: _sensorPin(sensorPin), _relayPin(relayPin), _activationThreshold(activationThreshold), _deactivationThreshold(deactivationThreshold) {
}

void RelayControlPressure::begin() {
    pinMode(_relayPin, OUTPUT);
    digitalWrite(_relayPin, LOW);  // Ensure relay is off initially
    analogReadResolution(12);  // Set ADC resolution (assuming ESP32)
}

void RelayControlPressure::update() {
    readPressureAndControlRelay();
}

void RelayControlPressure::readPressureAndControlRelay() {
    int sensorValue = analogRead(_sensorPin);
    float voltage = sensorValue * (3.3 / 4095.0);
    float pressure_psi = (voltage - 0.25) * (100 / (2.00));  // Conversion based on your specific calibration

    // Check against thresholds to control relay
    if (pressure_psi > _activationThreshold) {
        digitalWrite(_relayPin, HIGH);
    } else if (pressure_psi < _deactivationThreshold) {
        digitalWrite(_relayPin, LOW);
    }

    // Optional: Add serial output for debugging
    Serial.print("Pressure (PSI): "); Serial.println(pressure_psi);
    Serial.print("Relay State: "); Serial.println(digitalRead(_relayPin) ? "ON" : "OFF");
}

// In the main file, you would typically instantiate and use this class like this:
// RelayControlPressure pressureControl(34, 5, 75, 70);  // example pin numbers and thresholds
// pressureControl.begin();
// pressureControl.update(); in a loop or task
