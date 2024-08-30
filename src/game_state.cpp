#include "game_state.h"

GameState game_state = {1, {0}, 0, {false}, {0}};
STATE current_state = SETUP;

void reset_game_state() {
    game_state = {1, {0}, 0, {false}, {0}};
}
