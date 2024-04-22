#ifndef RELAY_CONTROL_NOZZLE_H
#define RELAY_CONTROL_NOZZLE_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>

class RelayControl {
public:
    RelayControl();  // Constructor no longer needs pin parameter
    void begin();

private:
    int _relayPin;  // GPIO pin associated with the relay
    TimerHandle_t _timer;  // Handle for the FreeRTOS timer
    static void relayTimerCallback(TimerHandle_t xTimer);  // Timer callback function to toggle the relay state
};

#endif
