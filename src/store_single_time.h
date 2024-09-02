#include <Arduino.h>
#include <ArduinoJson.h>  // ArduinoJson library
#include <LittleFS.h> 


void init_json_file(int pointer);

void init_json_files();

void read_json_file(int pointer);

void remove_json_file(int pointer);

void remove_json_files();

boolean add_value_to_json(long id, int time);