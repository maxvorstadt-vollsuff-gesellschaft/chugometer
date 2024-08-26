#include "game_state.h"
#include "settings.h"
#include "display.h"


void draw();


static bool updated_display = false;

void idle_loop() {
    if (!updated_display) {
        draw();
        updated_display = true;
    }
}

void idle_single_click() {
    game_state.player_count += 1;
    if (game_state.player_count > MAX_PLAYER) {
        game_state.player_count = 1;
    }
    updated_display = false;
}

void idle_double_click() {
    if (game_state.player_count == 1) {
        current_state = PREPARE_SINGLE;
    } else {
        current_state = PREPARE_GROUP;
    }
    updated_display = false;
}

void draw() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("Player:");
    display.setCursor(0,25);
    display.println(game_state.player_count);  
    display.display();
}