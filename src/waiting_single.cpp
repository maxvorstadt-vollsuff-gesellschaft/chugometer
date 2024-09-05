#include "display.h"
#include "game_state.h"

#ifdef RFID
#include "rfid.h"  
#endif

static bool updated_display = false;

void waiting_single_loop() {
    if (!updated_display && game_state.card_ids[0] == "") {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("Start!");
        display.println("not logged in");
        display.display();

        updated_display = true;
    } else if (!updated_display) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Start!");
        display.println("logged in");
        display.display();
        updated_display = true;
    }

    #ifdef RFID
    String card_uid = read_uid();
    if (card_uid == "") {
        return;
    }
    game_state.card_ids[0] = card_uid;
    updated_display = false;
    halt_card();
    #endif
}

void waiting_single_pad_lifted(int pad) {
    if (pad == 0) {
        game_state.start_time = millis();
        updated_display = false;
        current_state = SINGLE_DRINKING;
    }
}