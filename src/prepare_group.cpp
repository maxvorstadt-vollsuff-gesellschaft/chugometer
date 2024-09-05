#include "display.h"
#include "settings.h"
#include "game_state.h"
#include "buttons.h"

#ifdef RFID
int logging_in = 0;  
#endif


void prepare_group_loop() {
    bool all_ready = true;
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Missing:");
    //display.setCursor(0, 25);

    bool first = true;
    for (int i = 0; i < game_state.player_count; i++) {
        if (!pads[i]->isLongPressed()) {
            if (!first) {
                display.print(", ");
            }
            display.print(i+1);
            first = false;
            all_ready = false;
        }
    }
    display.println("");

    if (all_ready) {
        current_state = GROUP_COUNTDOWN;
    }

    #ifdef RFID
    // TODO: check if correct
    if (logging_in < game_state.player_count) {
        display.print("log in:");
        display.print(logging_in+1);
        String card_uid = read_uid();
        if (card_uid == "") {
            return;
        }
        game_state.card_ids[logging_in] = card_uid;
        logging_in++;
        halt_card();
    }
    #endif

    display.display();
}
