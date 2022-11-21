#include <ArduinoSTL.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATAPIN 2

Adafruit_NeoPixel the_strip = Adafruit_NeoPixel(300, DATAPIN, NEO_GRB + NEO_KHZ800);

uint32_t rainbow[10] = { the_strip.Color(255, 0, 0), the_strip.Color(255, 127, 0), 
            the_strip.Color(255, 255, 0), the_strip.Color(127, 255, 0), 
            the_strip.Color(0, 255, 0), the_strip.Color(0, 255, 127), 
            the_strip.Color(0, 127, 255), the_strip.Color(0, 0, 255), 
            the_strip.Color(127, 0, 255), the_strip.Color(255, 0, 127) };

void setup() {
  // put your setup code here, to run once:
  the_strip.begin();
  // call to "show" turns all pixels off initially
  the_strip.show();
  Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:
    for (int i=0; i<sizeof(rainbow); i++) {
        blockColor(rainbow[i], false);
        the_strip.show();
        delay(50);
    }
}

void blockColor(uint32_t color, bool reverse) {
  if (reverse) {
    for (uint16_t i=the_strip.numPixels() - 1; i>= 0; i--) {
      the_strip.setPixelColor(i, color);
    }
  } else {
    for (uint16_t i=0; i<the_strip.numPixels(); i++) {
      the_strip.setPixelColor(i, color);
    }
  }
}
