#include "display.h"
#include "game_state.h"
#include "store_single_time.h"
//HTTP TEST
#include "database_request.h"

static bool display_updated = false;

void single_done_loop() {
    if (!display_updated) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Time:");
        display.setCursor(0,25);
        display.println(game_state.player_times[0]);  
        display.display();

        display_updated = true;
        add_value_to_json(game_state.card_ids[0], game_state.player_times[0]);
        read_json_file(0);
    }
}
void single_done_double_click() {
    display_updated = false;
    current_state = IDLE;
    reset_game_state();
}

void single_done_click() {
    display_updated = false;
    current_state = IDLE;
    reset_game_state();
}