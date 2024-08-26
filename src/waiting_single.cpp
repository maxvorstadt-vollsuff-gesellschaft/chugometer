#include "display.h"
#include "game_state.h"

static bool updated_display = false;

void waiting_single_loop() {
    if (!updated_display) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0,0);
        display.println("CHUG!");
        display.display();

        updated_display = true;
    }
}

void waiting_single_pad_lifted(int pad) {
    if (pad == 0) {
        game_state.start_time = millis();
        updated_display = false;
        current_state = SINGLE_DRINKING;
    }
}