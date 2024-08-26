#include "display.h"
#include "buttons.h"
#include "game_state.h"

static bool display_updated = false;

void prepare_single_loop() {
    if (!display_updated) {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.println("Ready your beer!");
        display.display();

        display_updated = true;
    }
    
    if (pad_a.isLongPressed()) {
        Serial.println("now chug");
        display_updated = false;
        current_state = SINGLE_WAITING;
    }
}
