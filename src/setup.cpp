#include "display.h"
#include "settings.h"
#include "game_state.h"
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

static bool display_updated = false;
static unsigned long start_time = 0;

void setup_loop() {
    if (!display_updated) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Chugometer");
        display.setCursor(0, 25);
        display.setTextSize(1);
        display.println("connecting to wifi. Press button to abort.");
        display.display();

        display_updated = true;
        start_time = millis();
    }
    if (millis()-start_time > WIFI_TIMEOUT) {
        current_state = IDLE;
        display_updated = false;
    }
}

void setup_single_click() {
    current_state = IDLE;
    display_updated = false;
}