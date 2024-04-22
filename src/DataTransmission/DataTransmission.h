#ifndef DATA_TRANSMISSION_H
#define DATA_TRANSMISSION_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class DataTransmission {
public:
    static void begin();  // Static method to start the data transmission task

private:
    static void transmitDataTask(void *parameter);  // Private static member to keep the task encapsulated within the class
};

#endif
