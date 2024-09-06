#include "OneButton.h"
#include "settings.h"

#ifndef BUTTONS_H
#define BUTTONS_H

void init_buttons();
void poll_buttons();

extern OneButton pad_a;
extern OneButton pad_b;
extern OneButton pad_c;
extern OneButton enter_button;
extern OneButton* pads[MAX_PLAYER];

#endif