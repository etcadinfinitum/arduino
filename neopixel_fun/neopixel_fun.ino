#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATAPIN 2

Adafruit_NeoPixel the_strip = Adafruit_NeoPixel(60, DATAPIN, NEO_GRB + NEO_KHZ800);
uint32_t rainbow[10] = { the_strip.Color(255, 0, 0), the_strip.Color(255, 127, 0), the_strip.Color(255, 255, 0), the_strip.Color(127, 255, 0), the_strip.Color(0, 255, 0), the_strip.Color(0, 255, 127), the_strip.Color(0, 127, 255), the_strip.Color(0, 0, 255), the_strip.Color(127, 0, 255), the_strip.Color(255, 0, 127) };

void setup() {
  // put your setup code here, to run once:
  the_strip.begin();
  // call to "show" turns all pixels off initially
  the_strip.show();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("rainbow size: " + sizeof(rainbow));
  /*
  for (int i=0; i<sizeof(rainbow); i++) {
    blockColor(rainbow[i], false);
    blockColor(the_strip.Color(0, 0, 0), true);
  }
  */
  
  
  showRainbow();
  delay(1000);
  cycleRainbow();
  for (int i=0; i < the_strip.numPixels(); i++) {
    the_strip.setPixelColor(i, the_strip.Color(0, 0, 0));
  }
  
  the_strip.show();

  flashing(the_strip.Color(127, 127, 0));
}

void showRainbow() {
  for (int i = 0; i < the_strip.numPixels(); i++) {
    int col = i % (sizeof(rainbow) / 4);
    the_strip.setPixelColor(i, rainbow[col]);
    the_strip.show();
    delay(30);
  }
}

void cycleRainbow() {
  for (int i=0; i<100; i++) {
    for (int pix=0; pix<the_strip.numPixels(); pix++) {
      int col = (i + pix) % (sizeof(rainbow) / 4);
      the_strip.setPixelColor(pix, rainbow[col]);
    }
    the_strip.show();
    delay(50);
  }
}

void blockColor(uint32_t color, bool reverse) {
  if (reverse) {
    for (uint16_t i=the_strip.numPixels() - 1; i>= 0; i--) {
      the_strip.setPixelColor(i, color);
      the_strip.show();
      delay(30);
    }
  } else {
    for (uint16_t i=0; i<the_strip.numPixels(); i++) {
      the_strip.setPixelColor(i, color);
      the_strip.show();
      delay(30);
    }
  }
}

void flashing(uint32_t color) {
  Serial.print("beginning flashing method\n");
  for (uint32_t i=0; i<100; i++) {
    for (uint16_t pix=0; pix<the_strip.numPixels(); pix++) {
      uint16_t pos = (pix + i) % 5;
      if (pos == 0 || pos == 1 || pos == 2) {
        the_strip.setPixelColor(pix, color);
      } else {
        the_strip.setPixelColor(pix, the_strip.Color(0, 0, 0));
      }
      the_strip.show();
      //delay(15);
    }
  }
}




