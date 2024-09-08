#include "settings.h"
#include "game_state.h"
#include "display.h"
#include "store_single_time.h"

static long last_rotate = 0;
static int position = 0;
static int saved = false;

void group_done_loop() {
    if (!saved) {
        for (int i = 0; i < game_state.player_count; i++) {
            if (game_state.card_ids[i] != "") {
                add_value_to_json(game_state.card_ids[i], game_state.player_times[i]);
            }
        }
        saved = true;
    }
    if (millis() - last_rotate > 2000) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.print("Player ");
        display.println(position+1);
        display.setCursor(0,25);
        if (game_state.disqualified[position]) {
            display.println("disqulified");
        } else {
            display.println(game_state.player_times[position]);
        }
        display.display();

        position += 1;
        if (position == game_state.player_count) {
            position = 0;
        }

        last_rotate = millis();
    }
}

void group_done_click() {
    current_state = IDLE;
    saved = false;
    reset_game_state();
}

void group_done_double_click() {
    current_state = IDLE;
    saved = false;
    reset_game_state();
}