#ifndef RFID_H
#define RFID_H

#include <Arduino.h>

void init_reader();
String read_uid();
void halt_card();

#endif