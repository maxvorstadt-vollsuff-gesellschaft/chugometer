#include "display.h"
#include "settings.h"
#include "game_state.h"

static long last_update = 0;

void group_drinking_loop() {
    if (millis() - last_update > TIMER_UPDATE_INTERVAL) {
        display.clearDisplay();
        display.setTextColor(SSD1306_WHITE);
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Time:");
        display.setCursor(0, 25);
        display.println(millis()-game_state.start_time);
        display.display();

        last_update = millis();
    }
}

void group_drinking_pressed(int pad) {
    if (pad < game_state.player_count && !game_state.disqualified[pad]) {
        game_state.player_times[pad] = millis() - game_state.start_time;
        Serial.print("Player ");
        Serial.print(pad);
        Serial.print(" time: ");
        Serial.println(game_state.player_times[pad]);
    }

    bool all_done = true;
    for (int i = 0; i<game_state.player_count; i++) {
        if (game_state.player_times[i] == 0 && !game_state.disqualified[i]) {
            all_done = false;
        }
    }

    if (all_done) {
        current_state = GROUP_DONE;
    }
}