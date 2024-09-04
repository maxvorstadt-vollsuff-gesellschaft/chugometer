#include <Arduino.h>
#include "display.h"
#include "game_state.h"
#include "settings.h"
#include "idle.h"
#include "prepare_single.h"
#include "waiting_single.h"
#include "single_drinking.h"
#include "single_done.h"
#include "prepare_group.h"
#include "group_countdown.h"
#include "group_drinking.h"
#include "group_done.h"
#include "wifi_setup.h"
#include "setup.h"
#include "buttons.h"
#include "led.h"
#include "custom_time.h"
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif

#include "store_single_time.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  Serial.println("Chip ID:");
  Serial.println(ESP.getChipId());
  WiFi.setHostname("chugometer");
  WiFi.begin();

  init_buttons();
  init_display();
  
  //hier nur test
  remove_json_files();
  init_json_files();
  setup_leds();
  init_time();
}

void loop() {
  
  poll_buttons();
  led_loop();

  switch (current_state) {
  case SETUP:
    setup_loop();
    break;
  case IDLE:
    idle_loop();
    break;
  case PREPARE_SINGLE:
    prepare_single_loop();
    break;
  case SINGLE_WAITING:
    waiting_single_loop();
    break;
  case SINGLE_DRINKING:
    single_drinking_loop();
    break;
  case SINGLE_DONE:
    single_done_loop();
    break;
  case PREPARE_GROUP:
    prepare_group_loop();
    break;
  case GROUP_COUNTDOWN:
    group_countdown_loop();
    break;
  case GROUP_DRINKING:
    group_drinking_loop();
    break;
  case GROUP_DONE:
    group_done_loop();
    break;
  case WIFI_SETUP:
    wifi_setup_loop();
    break;
  default:
    break;
  }
}
