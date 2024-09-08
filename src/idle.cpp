#include "game_state.h"
#include "settings.h"
#include "display.h"
#ifdef RFID
#include "rfid.h"  
#endif

void draw();


static bool updated_display = false;
static bool settings = false;
static String last_card_id = "";

void idle_loop() {
    if (!updated_display) {
        draw();
        updated_display = true;
    }
    #ifdef RFID
    String card_uid = read_uid();
    if (card_uid == "" || card_uid == last_card_id) {
        return;
    }
    halt_card();
    last_card_id = card_uid;
    Serial.print("Read card:");
    Serial.println(card_uid);
    #endif
}

void idle_single_click() {
    game_state.player_count += 1;
    if (settings) {
        game_state.player_count = 1;
        settings = false;
    } else if (game_state.player_count > MAX_PLAYER) {
        settings = true;
    }
    updated_display = false;
}

void idle_double_click() {
    
}

void draw() {
    if (settings) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Settings");
        display.display();
    } else {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Player:");
        display.setCursor(0,25);
        display.println(game_state.player_count);  
        display.display();
    }
}

void idle_enter_click() {
    if (settings) {
        current_state = SETTINGS_MENU;
    } else if (game_state.player_count == 1) {
        current_state = PREPARE_SINGLE;
    } else {
        current_state = PREPARE_GROUP;
    }
    updated_display = false;
}