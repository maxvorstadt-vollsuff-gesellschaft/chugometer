#include "display.h"
#include "settings.h"
#include "game_state.h"
#include "buttons.h"

void prepare_group_loop() {
    bool all_ready = true;
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.println("Missing:");
    display.setCursor(0, 25);

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
    display.display();

    if (all_ready) {
        current_state = GROUP_COUNTDOWN;
    }
}
