#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);


void init_display() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    display.display();
    delay(500);
}
