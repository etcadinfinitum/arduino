#include <ArduinoSTL.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATAPIN 2

Adafruit_NeoPixel the_strip = Adafruit_NeoPixel(60, DATAPIN, NEO_GRB + NEO_KHZ800);
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
  /*
  Serial.println("rainbow size: " + sizeof(rainbow));
  */
  /*
  for (int i=0; i<sizeof(rainbow); i++) {
    blockColor(rainbow[i], false);
    blockColor(the_strip.Color(0, 0, 0), true);
  }
  */
  starryNight();
  showRainbow();
  delay(1000);
  cycleRainbow();
  for (int i=0; i < the_strip.numPixels(); i++) {
    the_strip.setPixelColor(i, the_strip.Color(0, 0, 0));
  }
  
  the_strip.show();

  flashing(the_strip.Color(127, 127, 0));
  /*
  */
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
  // Serial.print("beginning flashing method\n");
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

void starryNight() {
    // seed random number
    randomSeed(analogRead(0));
    // Set color baseline 
    uint32_t nighttime[3][3] = { 
            {0, 0, 15}, {5, 0, 40}, 
            {0, 5, 30} };
  
    // As a continuous process, we want colors to fade brighter and darker
    // at different intervals.
    // ᕙ( ͡° ͜ʖ ͡°)ᕗ
    // We also want the fading to be interrupted when a light is chosen to 
    // twinkle as a star.
  
    // initialize information about each light's speed, initial color, and fade pattern
    uint8_t color_data[the_strip.numPixels()][2];
    // vector<pair<int, int>> color_data;
    for (int i = 0; i < the_strip.numPixels(); i++) {
        uint8_t range = (random(1000) % 20) + 1;
        uint8_t fastiboi = (random(1000) % 15) + 1;
        color_data[i][0] = range;
        color_data[i][1] = fastiboi;
    }
    
    // initialize array of white and yellow stars
    // inner array: int idx, int duration, int elapsedTime, int r, int b, int g, int reverse
    uint8_t color_data[5][7];
    for (int i = 0; i < 5; i++) {
        bool added = true;
        for (int j = 0; j < i; j++) {
            if (
        }
    }
    
    // cycle color changes
    for (int i = 0; i < 10000; i++) {
        // determine color of each item (based on modulo?)
        for (int pix = 0; pix < the_strip.numPixels(); pix++) {
            // if pix is in the "twinkle" list, then process that first
            // TODO
            bool isStar = false;
            for (int i = 0; i < 5; i++) {
                if (color_data[i][0] == pix) {
                    isStar = true;
                    break;
                }
            }
            // if the current pixel is 
            if (isStar) {
                
            }
            // if millisecond delay cycle is up, then we want to change colors
            else if (i % color_data[pix][1] == 0) {
                uint8_t range = color_data[pix][0];
                uint8_t phase = (i / (color_data[pix][1])) % (range * 4);
                uint8_t cycle = (phase - (phase % range)) / range;
                uint8_t interval = phase % range;
                uint8_t R = nighttime[pix % 3][0];
                uint8_t G = nighttime[pix % 3][1];
                uint8_t B = nighttime[pix % 3][2];
                switch (cycle) {
                    case 0: 
                        R = (R == 0 ? 0 : R + interval);
                        G = (G == 0 ? 0 : G + interval); 
                        B = (B == 0 ? 0 : B + interval);
                        break;
                    case 1: 
                        R = (R == 0 ? 0 : R + (range - interval));
                        G = (G == 0 ? 0 : G + (range - interval));
                        B = (B == 0 ? 0 : B + (range - interval));
                        break;
                    case 2:
                        R = (R == 0 ? 0 : (R - interval < 0 ? 0 : R - interval));
                        G = (G == 0 ? 0 : (G - interval < 0 ? 0 : G - interval));
                        B = (B == 0 ? 0 : (B - interval < 0 ? 0 : B - interval));
                        break;
                    case 3:
                        R = (R == 0 ? 0 : (R - (range - interval) < 0 ? 0 : R - (range - interval)));
                        G = (G == 0 ? 0 : (G - (range - interval) < 0 ? 0 : G - (range - interval)));
                        B = (B == 0 ? 0 : (B - (range - interval) < 0 ? 0 : B - (range - interval)));
                        break;
                }
                the_strip.setPixelColor(pix, R, G, B);
            }
        }
        the_strip.show();
        delay(1);
    }
}




