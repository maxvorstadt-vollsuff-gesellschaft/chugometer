#ifndef SETTINGS_H
#define SETTINGS_H

#define COUNTDOWN_DURATION 5000
#define MAX_PLAYER 3
#define LONG_PRESS_DELAY 200
#define TIMER_UPDATE_INTERVAL 50
#define WIFI_TIMEOUT 10000
#define NUM_LEDS 13
#define RTC

#ifdef ESP8266

#define MENU_BUTTON_PIN D6
#define PAD_A_PIN D5
#define PAD_B_PIN D7
#define PAD_C_PIN D4
#define PAD_D_PIN

#define DATA_PIN_1 D0
#define DATA_PIN_2 D8
#define DATA_PIN_3 D3

#elif defined(ESP32)

#define MENU_BUTTON_PIN GPIO_NUM_2
#define MENU_BUTTON_ENTER GPIO_NUM_15
#define PAD_A_PIN GPIO_NUM_12
#define PAD_B_PIN GPIO_NUM_13
#define PAD_C_PIN GPIO_NUM_33
#define PAD_D_PIN GPIO_NUM_14

#define DATA_PIN_1 GPIO_NUM_26
#define DATA_PIN_2 GPIO_NUM_25
#define DATA_PIN_3 GPIO_NUM_27
#define DATA_PIN_4 GPIO_NUM_32
#define RFID

#define SS_PIN 5
#define RST_PIN 22


#endif

#endif