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
    uint8_t twinkle[5][7];
    for (int i = 0; i < 5; i++) {
        bool added = false;
        uint8_t newIdx = 0;
        while (!added) {
            added = true;
            newIdx = random(1000) % the_strip.numPixels();
            for (int j = 0; j < i; j++) {
                if (newIdx == twinkle[i][0]) {
                    added = false;
                }
            }
        }
        // if previous while block passes, then a unique index has been selected. now choose a color range
        // trying to be clever and pick a color at random (instead of defining a color array)
        // may switch to defining an array depending on color output
        twinkle[i][3] = random(225, 256);
        twinkle[i][4] = random(225, 256);
        twinkle[i][5] = random(225, 256);
        twinkle[i][1] = random(25, 100);
        twinkle[i][0] = newIdx;
        twinkle[i][2] = 0;
        twinkle[i][6] = 0;
    }
    
    // cycle color changes
    for (int i = 0; i < 10000; i++) {
        // determine color of each item (based on modulo?)
        for (int pix = 0; pix < the_strip.numPixels(); pix++) {
            // if pix is in the "twinkle" list, then process that first
            bool isStar = false;
            uint8_t starIdx = 0;
            for (int i = 0; i < 5; i++) {
                if (twinkle[i][0] == pix) {
                    isStar = true;
                    starIdx = i;
                    break;
                }
            }
            // if the current pixel is a star, handle color cycling separately
            if (isStar) {
                // `twinkle`'s inner array: int idx, int duration, int elapsedTime, int r, int b, int g, int reverse
                // change color brightness
                // case 1: star is getting brighter (first half of duration cycle with reverse == 0)
                if (twinkle[starIdx][6] == 0 && twinkle[starIdx][2] < twinkle[starIdx][1] / 2) {
                    // set RBG values to be proportionate to the brightness rate of the cycle
                    uint8_t R = (twinkle[starIdx][3] / (twinkle[starIdx][2] / 2)) * twinkle[starIdx][2];
                    uint8_t B = (twinkle[starIdx][4] / (twinkle[starIdx][2] / 2)) * twinkle[starIdx][2];
                    uint8_t G = (twinkle[starIdx][5] / (twinkle[starIdx][2] / 2)) * twinkle[starIdx][2];
                    the_strip.setPixelColor(pix, R, B, G);
                } else if (twinkle[starIdx][6] == 1 && twinkle[starIdx][2] > twinkle[starIdx][1] / 2) {
                    // set RBG values to be proportionate to the brightness rate of the cycle
                    uint8_t R = twinkle[starIdx][3] - ((twinkle[starIdx][2] - (twinkle[starIdx][1] / 2)) * (twinkle[starIdx][3] * 2 / twinkle[starIdx][1]));
                    uint8_t B = twinkle[starIdx][4] - ((twinkle[starIdx][2] - (twinkle[starIdx][1] / 2)) * (twinkle[starIdx][4] * 2 / twinkle[starIdx][1]));
                    uint8_t G = twinkle[starIdx][4] - ((twinkle[starIdx][2] - (twinkle[starIdx][1] / 2)) * (twinkle[starIdx][5] * 2 / twinkle[starIdx][1]));
                    the_strip.setPixelColor(pix, R, B, G);
                } else {
                    the_strip.setPixelColor(pix, twinkle[starIdx][3], twinkle[starIdx][4], twinkle[starIdx][5]);
                }
                // increment elapsedTime value
                twinkle[starIdx][2] = twinkle[starIdx][2] + 1;
                // if the brightness counter has maxed out, set the reverse value to 1 instead of 0 so light will dim
                if (twinkle[starIdx][6] == 0 && twinkle[starIdx][2] == twinkle[starIdx][1]) {
                    twinkle[starIdx][6] = 1;
                    twinkle[starIdx][2] = 0;
                }
                // if the current star is at the end of its cycle, then select a new light to twinkle
                if (twinkle[starIdx][6] == 1 && twinkle[starIdx][2] == twinkle[starIdx][1]) {
                    bool added = false;
                    uint8_t newIdx = 0;
                    while (!added) {
                        added = true;
                        newIdx = random(1000) % the_strip.numPixels();
                        for (int j = 0; j < 5; j++) {
                            if (newIdx == twinkle[j][0]) {
                                added = false;
                            }
                        }
                        twinkle[starIdx][3] = random(225, 256);
                        twinkle[starIdx][4] = random(225, 256);
                        twinkle[starIdx][5] = random(225, 256);
                        twinkle[starIdx][1] = random(25, 100);
                        twinkle[starIdx][0] = newIdx;
                        twinkle[starIdx][2] = 0;
                        twinkle[starIdx][6] = 0;
                    }
                }
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
