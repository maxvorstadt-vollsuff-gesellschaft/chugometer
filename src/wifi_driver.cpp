#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

WiFiManager wifi_manager;

bool setup_wifi() {
    // AutoConnect will try to connect to the last known WiFi network or start the configuration portal
    if (!wifi_manager.autoConnect("Chugometer")) {
        // If connection fails, return false
        return false;
    }
    // If connected, return true
    return true;
}