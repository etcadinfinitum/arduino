#include "modes.h"
#include <ArduinoSTL.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

PixelDispatcher::PixelDispatcher() {
    rainbow_hue = 0;
    strip = Adafruit_NeoPixel(0, 0, NEO_GRB + NEO_KHZ800);
}

void PixelDispatcher::initialize(int reelsize, int datapin) {
    strip.setPin(datapin);
    strip.updateLength(reelsize);
    strip.begin();
    // call to "show" turns all pixels off initially
    strip.show();
}

void PixelDispatcher::runMode(int mode, int wait, int brightness) {
    // Did mode change? If so, we might need to reset some values.
    // Re-dispatch to correct method as needed.
    switch (mode) {
        case 0 :
            // Turn off pixels
            strip.show();
        case 1 :
            // Rainbow
            rainbow(wait, brightness);
        default :
            strip.show();
    }
}

/**
 * This function will produce a routine that displays and cycles a
 * rainbow hue gradient once. When repeated, the effect should be
 * continuous.
 */
void PixelDispatcher::rainbow(int speed, int brightness) {
    // Used to determine how many complete rainbow cycles to display
    // along strand of known size.
    int reps = 3;
    // The Adafruit Neopixel library has a wicked awesome rainbow()
    // function and I'm just now learning about this?
    strip.rainbow(rainbow_hue, reps, 255, brightness);
    strip.show();
    delay(speed);
    rainbow_hue = 65536 * reps / strip.numPixels();
}
