#ifndef SENSOR_TASKS_H
#define SENSOR_TASKS_H

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class SensorTasks {
public:
    static void begin();  // Static method to start the sensor tasks

private:
    static void readSensorsTask(void *parameter);  // Private static member function
};

#endif
