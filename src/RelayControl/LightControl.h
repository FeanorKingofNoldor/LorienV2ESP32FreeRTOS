#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <Arduino.h>

class LightControl {
public:
    LightControl();
    void begin();
    void startTask();
    void updateLightStatus(const struct tm &timeinfo); // Make sure this is declared

private:
    int _lightPin;
    static void lightControlTask(void *parameter);  // Now a private static member function
};

#endif
