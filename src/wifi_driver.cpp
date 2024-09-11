#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#include <WiFiManager.h>
#include "custom_time.h"
#include "settings.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiManager wifi_manager;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

bool setup_wifi() {
    if (!wifi_manager.autoConnect("Chugometer")) {
        return false;
    }
    
    #ifdef RTC
    if (!is_rtc_set()) {
        timeClient.begin();
        timeClient.update();
    
        uint32_t epochTime = timeClient.getEpochTime();
        Serial.println("Setting RTC time from NTP");
        set_time(epochTime);
    }
    #endif
    return true;
}