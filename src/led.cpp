#include "settings.h"
#include "game_state.h"
#include "buttons.h"
#include <FastLED.h>

#define MAX_BRIGHTNESS 128
#define FRAMES_PER_SECOND 120
#define SWITCH_INTERVAL 750

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];

CRGB* leds[MAX_PLAYER] = {leds1, leds2, leds3};

uint8_t gHue1 = 0;
uint8_t gHue2 = 85;
uint8_t gHue3 = 170;

static long remaining_time = 0;

void set_countdown_leds(long remaining) {
    remaining_time = remaining;
}

void juggle(CRGB* leds, uint8_t num_leds, uint8_t hue) 
{
    fadeToBlackBy(leds, num_leds, 20);
    uint8_t dothue = hue;
    for(int i = 0; i < 8; i++) {
        uint16_t ledIndex = beatsin16(i + 7, 0, num_leds - 1);
        leds[ledIndex] = CHSV(dothue, 200, 255);
        dothue += 32;
    }
}

void updateCountdownLEDs(CRGB* leds, unsigned long remainingTime) {
  int ledsToLight = map(remainingTime, 0, COUNTDOWN_DURATION, 0, NUM_LEDS);
  
  ledsToLight = constrain(ledsToLight, 0, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < ledsToLight) {
      uint8_t pulseValue = sin8(map(remainingTime % 1000, 0, 999, 0, 255));
      leds[i] = CHSV(0, 255, pulseValue);
    } else {
      leds[i] = CRGB::Black;
    }
  }

  if (remainingTime == 0) {
    fill_solid(leds, NUM_LEDS, CRGB::Green);
  }
}

void alternatingGreenLEDs(CRGB* leds, unsigned long currentTime) {
  bool evenLEDs = (currentTime / SWITCH_INTERVAL) % 2 == 0;

  for (int i = 0; i < NUM_LEDS; i++) {
    if ((i % 2 == 0) == evenLEDs) {
      leds[i] = CRGB::Green;
    } else {
      leds[i] = CRGB::Black;
    }
  }
}


void setup_leds() {
    FastLED.addLeds<WS2812B, DATA_PIN_1, GRB>(leds[0], NUM_LEDS);
    FastLED.addLeds<WS2812B, DATA_PIN_2, GRB>(leds[1], NUM_LEDS);
    FastLED.addLeds<WS2812B, DATA_PIN_3, GRB>(leds[2], NUM_LEDS);
    FastLED.setBrightness(MAX_BRIGHTNESS);
}


void clear_leds() {
    for (int i = 0; i < MAX_PLAYER; i++) {
        fill_solid(leds[i], NUM_LEDS, CRGB::Black);
    }
}

void led_loop() {
    clear_leds();
    EVERY_N_MILLISECONDS(20) {
        gHue1++;
        gHue2++;
        gHue3++;
    }

    switch (current_state) {
        case SETUP:
        case IDLE:
            for (int i = 0; i < MAX_PLAYER; i++) {
                juggle(leds[i], NUM_LEDS, gHue1);
            }
            break;
        case PREPARE_SINGLE:
            fill_solid(leds[0], NUM_LEDS, CRGB::Red);
            break;
        case SINGLE_WAITING:
            fill_solid(leds[0], NUM_LEDS, CRGB::Green);
            break;
        case SINGLE_DRINKING:
            alternatingGreenLEDs(leds[0], millis());
            break;
        case SINGLE_DONE:
            fill_solid(leds[0], NUM_LEDS, CRGB::Green);
            break;
        case GROUP_COUNTDOWN:
            for (int i = 0; i<MAX_PLAYER; i++) {
                if (game_state.disqualified[i]) {
                    fill_solid(leds[i], NUM_LEDS, CRGB::Red);
                } else {
                    updateCountdownLEDs(leds[i], remaining_time);
                }
            }
            break;
        case PREPARE_GROUP:
            for (int i = 0; i < game_state.player_count; i++) {
                if(pads[i]->isLongPressed()) {
                    fill_solid(leds[i], NUM_LEDS, CRGB::Green);
                } else {
                    fill_solid(leds[i], NUM_LEDS, CRGB::Red);
                }
            }
            break;
        case GROUP_DRINKING:
            for (int i = 0; i < MAX_PLAYER; i++) {
                if (game_state.disqualified[i]) {
                    fill_solid(leds[i], NUM_LEDS, CRGB::Red);
                } else {
                    if (game_state.player_times[i] != 0) {
                        fill_solid(leds[i], NUM_LEDS, CRGB::Green);
                    } else {
                        alternatingGreenLEDs(leds[i], millis());
                    }
                }
            }
            break;
        case GROUP_DONE:
            for (int i = 0; i<MAX_PLAYER; i++) {
                if (game_state.disqualified[i]) {
                    fill_solid(leds[i], NUM_LEDS, CRGB::Red);
                } else {
                    fill_solid(leds[i], NUM_LEDS, CRGB::Green);
                }
            }
            break;
        default:
            break;
    }

    FastLED.show();  
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}