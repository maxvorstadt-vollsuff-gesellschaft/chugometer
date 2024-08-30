#include "settings.h"

#ifndef GAME_STATE_H
#define GAME_STATE_H

struct GameState {
  int player_count;
  long player_times[MAX_PLAYER];
  long start_time;
  bool disqualified[MAX_PLAYER];
  long player_ids[MAX_PLAYER];
};

enum STATE {
  SETUP,
  IDLE,
  PREPARE_SINGLE,
  SINGLE_WAITING,
  SINGLE_DRINKING,
  SINGLE_DONE,
  PREPARE_GROUP,
  GROUP_COUNTDOWN,
  GROUP_DRINKING,
  GROUP_DONE
};

extern GameState game_state;
extern STATE current_state;

void reset_game_state();


#endif