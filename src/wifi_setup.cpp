#include <Arduino.h>
#include "display.h"
#include "wifi_driver.h"
#include "game_state.h"

void wifi_setup_loop() {
    Serial.println("wifi setup");
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("To setup wifi, connect to chugometer.");
    display.display();

    bool connected = setup_wifi();

    if (connected) {
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.println("Connected");
        display.display();
    } else {
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.println("Error");
        display.display();
    }

    delay(1000);

    current_state = SETTINGS_MENU;
}