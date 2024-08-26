#include <Arduino.h>
#include "settings.h"
#include "display.h"
#include "game_state.h"

static long last_draw = 0;
static long countdown_start = 0;

void group_countdown_loop() {
    long ts = millis();
    if (countdown_start == 0) {
        countdown_start = ts;
    }
    
    long remaining = COUNTDOWN_DURATION - (ts - countdown_start);
    if (ts - last_draw > TIMER_UPDATE_INTERVAL) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Chug in:");
        display.setCursor(0,25);
        display.println(remaining);
        display.display();

        last_draw = ts;
    }

    if (remaining <= 0) {
        countdown_start = 0;
        game_state.start_time = ts;
        current_state = GROUP_DRINKING;
    }
}

void group_countdown_pad_lifted(int pad) {
    if (pad < game_state.player_count) {
        Serial.print("player ");
        Serial.print(pad+1);
        Serial.println(" disqualified!");
        game_state.disqualified[pad] = true;
    }

    bool all_disqualified = true;
    for (int i = 0; i < game_state.player_count; i++) {
        if (!game_state.disqualified[i]) {
            all_disqualified = false;
        }
    }
    if (all_disqualified) {
        countdown_start = 0;
        current_state = GROUP_DONE;
    }
}
