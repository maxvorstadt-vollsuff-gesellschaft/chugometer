#ifndef TIME_H
#define TIME_H
#include <Arduino.h>

void init_time();
uint32_t get_ts();
bool is_rtc_set();
void set_time(uint32_t ts);

#endif