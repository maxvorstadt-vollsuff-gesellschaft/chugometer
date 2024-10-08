#include <Arduino.h>
#include "OneButton.h"
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "display.h"
#include "game_state.h"
#include "settings.h"
#include "idle.h"

#define WIRE Wire

const int BUTTON_SINGLE_PIN = D6;
const int BUTTON_BEER_PIN = D5;
const int BUTTON_MULTI_PIN = 1;
const int Button_B = D7;


OneButton buttonA;
OneButton buttonB;
OneButton start_button;

enum STATE {
  IDLE,
  PreparingSingle,
  PreparingGroup,
  DrinkingSingle,
  DrinkingGroup,
  DrinkingStopSingle,
  DrinkingStopGroup
};

STATE current_state = IDLE;

bool single_state = false;  //true = preparingSingle
bool multi_state = false;   //true = preparingSingle
bool drinking = false;      //true = DrinkingSingle

long last_display_update = 0;


// Group session state vars
long countdown_start_time = 0;
long person_A_end_time = 0;
long person_B_end_time = 0;

long start_time;

void display_timer() {
  long current_time = millis();
  if (current_time - last_display_update > 100 && current_state == DrinkingSingle){
    display_time(current_time-start_time);
    last_display_update = current_time;
  }
}


void entering_group_contest() {
  Serial.println("start group click!");
  current_state = PreparingGroup;
  countdown_start_time = millis();
}

void entering_single_contest() {
  Serial.println("start single contest");
  current_state = PreparingSingle;
}

void start_single_timer() { 
  Serial.println("long press A stop");
  if (current_state == PreparingSingle) {
    current_state = DrinkingSingle;
    start_time = millis(); // das bleibt hier
  }
 //current_state = PreparingGroup;
}

void stop_single_timer() {
  long chug_time = millis() - start_time;
  display_time(chug_time);
  current_state = IDLE;
}

void drinking_group_loop() {
  long current_time = millis();
  if (current_time - last_display_update > 100){
    if (person_A_end_time != 0) {
      display2_time(person_A_end_time-start_time , current_time-start_time);
    } else if (person_B_end_time != 0) {
      display2_time(current_time-start_time, person_B_end_time-start_time);
    } else {
      display2_time(current_time-start_time, current_time-start_time);
    }
    last_display_update = current_time;
  }
}


void stop_group_timer() {
  long chug_timeA = person_A_end_time - start_time;
  long chug_timeB = person_B_end_time - start_time;
  display2_time(chug_timeA, chug_timeB);

  current_state = IDLE;
  person_A_end_time = 0;
  person_B_end_time = 0;
}

void pressButtonA() {
  Serial.println("press button A");
  switch (current_state) {
  case DrinkingSingle:
    current_state = DrinkingStopSingle;
    break;
  case DrinkingGroup:
    person_A_end_time = millis();
    if (person_B_end_time != 0) {
      current_state = DrinkingStopGroup;
    }
    break;
  default:
    break;
  }
  //current_state = DrinkingStopSingle;
}

void pressButtonB() {
  Serial.println("press button B");
  switch (current_state) {
  case DrinkingSingle:
    current_state = DrinkingStopSingle;
    break;
  case DrinkingGroup:
    person_B_end_time = millis();
    if (person_A_end_time != 0) {
      current_state = DrinkingStopGroup;
    }
    break;
  default:
    break;
  }
}

void countdown() {
  long current_ct = (countdown_start_time + 5000) - millis();
  if (current_ct <= 0) {
    start_time = millis();
    current_state = DrinkingGroup;
    Serial.println("DrinkingMultiStage");
  } else {
    display_time(current_ct);
  }
}


void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");

  // setup OneButton
  buttonA.setup(BUTTON_BEER_PIN, INPUT_PULLUP, true);
  buttonB.setup(Button_B, INPUT_PULLUP, true);
  start_button.setup(BUTTON_SINGLE_PIN, INPUT_PULLUP, true);

  buttonA.attachPress(pressButtonA);
  buttonA.attachLongPressStop(start_single_timer);
  buttonB.attachPress(pressButtonB);
  
  start_button.attachClick(entering_single_contest);
  start_button.attachDoubleClick(entering_group_contest);

  init_display();
}

void loop() {
  start_button.tick();
  buttonA.tick();
  buttonB.tick();

  switch (current_state) {
  case IDLE:
    break;
  case PreparingSingle:
    display_time(0);
  case DrinkingSingle:
    display_timer();
    break;
  case DrinkingStopSingle:
    stop_single_timer();
    break;
  case PreparingGroup:
    countdown();
    break;
  case DrinkingGroup:
    drinking_group_loop();
    break;
  case DrinkingStopGroup:
    stop_group_timer();
    break;
  default:
    break;
  }
}
