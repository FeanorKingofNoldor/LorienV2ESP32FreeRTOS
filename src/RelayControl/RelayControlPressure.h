#ifndef RelayControlPressure_h
#define RelayControlPressure_h

#include <Arduino.h>

class RelayControlPressure {
public:
    RelayControlPressure(int sensorPin, int relayPin, float activationThreshold, float deactivationThreshold);
    void begin();
    void update();  // This method will be called periodically to check and update relay status

private:
    int _sensorPin;
    int _relayPin;
    float _activationThreshold;
    float _deactivationThreshold;
    void readPressureAndControlRelay();
};

#endif
