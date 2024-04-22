#include "WifiManager.h"
#include <WiFi.h>
#include "time.h"

// Define your Wi-Fi credentials
static const char* _ssid = "A1-75CB0A01";
static const char* _password = "ky0Lm3CscBvodz";

WifiManager::WifiManager() {}

void WifiManager::begin() {
    // Connect to Wi-Fi
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("WiFi connected.");

    // Initialize the system time
    configTime(7200, 0, "pool.ntp.org");
}
