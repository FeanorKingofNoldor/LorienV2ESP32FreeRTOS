#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

class WifiManager {
public:
    WifiManager();  // Constructor does not need parameters anymore
    void begin();
};

#endif