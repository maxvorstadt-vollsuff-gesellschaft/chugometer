#include <Arduino.h>
#include "game_state.h"
#include "settings.h"
#include "display.h"

static long last_update = 0;

void single_drinking_loop() {
    if (millis() - last_update > TIMER_UPDATE_INTERVAL) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Time:");
        display.setCursor(0,25);
        display.println(millis() - game_state.start_time);  
        display.display();

        last_update = millis();
    }
}

void single_drinking_pressed(int pad) {
    game_state.player_times[0] = millis() - game_state.start_time;
    current_state = SINGLE_DONE;
}
