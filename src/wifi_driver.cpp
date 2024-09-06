#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>
#endif

#include <ESPAsyncWebServer.h>
#include <ESPAsyncWiFiManager.h>

AsyncWebServer server(80);
DNSServer dns;
AsyncWiFiManager wifi_manager(&server,&dns);

bool setup_wifi() {
    return wifi_manager.autoConnect("Chugometer");
}

bool wifi_connected() {
    return false;
}