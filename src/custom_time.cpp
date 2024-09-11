#include <Arduino.h>
#include "RTClib.h"
#include "settings.h"

RTC_DS3231 rtc;


void init_time() {
    #ifdef RTC
    if (! rtc.begin()) {
        Serial.println("Couldn't find RTC");
        return;
    }
    if (rtc.lostPower()) {
        Serial.println("RTC lost power, please set the time!");
    }
    #endif
}

uint32_t get_ts() {
    #ifdef RTC
    return rtc.now().unixtime();
    #else
    return 0;
    #endif
}

bool is_rtc_set() {
    #ifdef RTC
    return rtc.lostPower();
    #else
    return false;
    #endif
}

void set_time(uint32_t ts) {
    #ifdef RTC
    rtc.adjust(DateTime(ts));
    #endif
}