#include "OneButton.h"
#include "settings.h"
#include "game_state.h"
#include "idle.h"
#include "waiting_single.h"
#include "single_drinking.h"
#include "group_countdown.h"
#include "group_drinking.h"
#include "single_done.h"
#include "group_done.h"


OneButton menu_button;

OneButton pad_a;
OneButton pad_b;
OneButton pad_c;

OneButton* pads[MAX_PLAYER] = {&pad_a, &pad_b, &pad_c};

void menu_single_click();
void menu_double_click();

void pad_a_press();
void pad_b_press();
void pad_c_press();

void pad_a_lift();
void pad_b_lift();
void pad_c_lift();

void init_buttons() {
  menu_button.setup(MENU_BUTTON_PIN, INPUT_PULLUP, true);
  menu_button.attachClick(menu_single_click);
  menu_button.attachDoubleClick(menu_double_click);

  // pads
  pad_a.setup(PAD_A_PIN, INPUT_PULLUP, true);
  pad_a.attachPress(pad_a_press);
  pad_a.attachLongPressStop(pad_a_lift);
  pad_a.setLongPressIntervalMs(LONG_PRESS_DELAY);

  pad_b.setup(PAD_B_PIN, INPUT_PULLUP, true);
  pad_b.attachPress(pad_b_press);
  pad_b.attachLongPressStop(pad_b_lift);
  pad_b.setLongPressIntervalMs(LONG_PRESS_DELAY);

  pad_c.setup(PAD_C_PIN, INPUT_PULLUP, true);
  pad_c.attachPress(pad_c_press);
  pad_c.attachLongPressStop(pad_c_lift);
  pad_b.setLongPressIntervalMs(LONG_PRESS_DELAY);
}

void poll_buttons() {
  menu_button.tick();
  pad_a.tick();
  pad_b.tick();
  pad_c.tick();
}

void menu_single_click() {
  Serial.println("m single click");
  switch (current_state) {
    case IDLE:
      idle_single_click();
      break;
    case SINGLE_DONE:
      single_done_click();
      break;
    case GROUP_DONE:
      group_done_click();
      break;
    default:
        break;
  }
}

void menu_double_click() {
  Serial.println("m double click");
  switch (current_state) {
    case IDLE:
      idle_double_click();
      break;
    case SINGLE_DONE:
      single_done_double_click();
      break;
    case GROUP_DONE:
      group_done_double_click();
      break;
    default:
        break;
  }
}

void pad_pressed(int pad) {
  Serial.print("pad ");
  Serial.print(pad);
  Serial.println(" pressed");
  switch (current_state) {
    case SINGLE_DRINKING:
      single_drinking_pressed(pad);
      break;
    case GROUP_DRINKING:
      group_drinking_pressed(pad);
      break;
    default:
        break;
  }
}

void pad_lifted(int pad) {
  Serial.print("pad ");
  Serial.print(pad);
  Serial.println(" long press lifted");
  switch (current_state) {
    case SINGLE_WAITING:
      waiting_single_pad_lifted(pad);
      break;
    case GROUP_COUNTDOWN:
      group_countdown_pad_lifted(pad);
      break;
    default:
        break;
  }
}

void pad_a_press() {
  pad_pressed(0);
}

void pad_b_press() {
  pad_pressed(1);
}

void pad_c_press() {
  pad_pressed(2);
}

void pad_a_lift() {
  pad_lifted(0);
}

void pad_b_lift() {
  pad_lifted(1);
}

void pad_c_lift() {
  pad_lifted(2);
}
