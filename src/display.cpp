#include <Wire.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);


void init_display() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
    display.display();
    delay(500);
    display.clearDisplay();
    display.display();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("CHUGOMETER");
    display.display();
}

void display_time(long time) {
  display.display();
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("CHUGOMETER");
  display.setCursor(0,25);
  display.println(time);  
  display.display();
}

void display2_time(long timeA, long timeB) {
  display.display();
  display.clearDisplay();
  display.display();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("CHUGOMETER");
  display.setCursor(0,25);
  display.println(timeA);
  display.setCursor(0,50);
  display.println(timeB);  
  display.display();
}