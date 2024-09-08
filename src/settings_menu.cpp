#include "settings.h"
#include "display.h"
#include "store_single_time.h"
#include "game_state.h"

static int current_menu = 0;

void settings_menu_loop() {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Settings");
    switch (current_menu) {
        case 0:
            display.println("clear data");
            break;
        case 1:
            display.println("read files");
            break;
        case 2:
            display.println("sync");
            break;
        case 3:
            display.println("back");
            break;
        default:
            break;
    }
    display.display();
}

void settings_menue_cycle() {
    current_menu++;
    if (current_menu > 3) {
        current_menu = 0;
    }
}

void read_json_files() {
    for (int i = 0; i < 5; i++) {
        read_json_file(i);
    }
}

void settings_menu_enter() {
    switch (current_menu) {
        case 0:
            remove_json_files();
            init_json_files();
            break;
        case 1:
            read_json_files();
            break;
        case 2:

            break;
        case 3:
            current_state = IDLE;
            break;
    }
}