#include "LightControl.h"
#include <freertos/FreeRTOS.h>
#include <freertos/timers.h>
#include "time.h"

/**
 * @brief Construct a new Light Control:: Light Control object initializing the control pin.
 */
LightControl::LightControl() : _lightPin(13) {}

/**
 * @brief Sets the pin mode to OUTPUT for the light control pin.
 */
void LightControl::begin() {
    pinMode(_lightPin, OUTPUT);
}

/**
 * @brief Starts the light control task.
 */
void LightControl::startTask() {
    xTaskCreate(
        lightControlTask,         // Task function
        "Light Control Task",     // Task name
        2048,                     // Stack size
        this,                     // Task parameter (pointer to this object)
        1,                        // Task priority
        NULL                      // Task handle
    );
}

/**
 * @brief Static task function that toggles light based on the time.
 * 
 * @param parameter Pointer to LightControl object passed during task creation.
 */
void LightControl::lightControlTask(void *parameter) {
    LightControl *lightControl = static_cast<LightControl*>(parameter);

    for (;;) {
        struct tm timeinfo;
        if (!getLocalTime(&timeinfo)) {
            Serial.println("LightControl - Failed to obtain time");
            vTaskDelay(pdMS_TO_TICKS(60000)); // Retry after 1 minute
            continue;
        }

        lightControl->updateLightStatus(timeinfo);
        vTaskDelay(pdMS_TO_TICKS(30000)); // Check every 30 seconds
    }
}

/**
 * @brief Updates the light's power state based on the current time.
 * 
 * @param timeinfo A struct containing the current time.
 */
void LightControl::updateLightStatus(const struct tm &timeinfo) {
    int currentHour = timeinfo.tm_hour;
    char timeStr[64];
    strftime(timeStr, sizeof(timeStr), "%A, %B %d %Y %H:%M:%S", &timeinfo);

    if (currentHour >= 6 && currentHour < 23) {
        if (digitalRead(_lightPin) == LOW) {
            digitalWrite(_lightPin, HIGH);
            Serial.print("Light turned ON at ");
            Serial.println(timeStr);
        }
    } else {
        if (digitalRead(_lightPin) == HIGH) {
            digitalWrite(_lightPin, LOW);
            Serial.print("Light turned OFF at ");
            Serial.println(timeStr);
        }
    }
}
