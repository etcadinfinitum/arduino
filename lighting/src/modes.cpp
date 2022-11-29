#include "modes.h"
#include <ArduinoSTL.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

PixelDispatcher::PixelDispatcher() {
    rainbow_hue = 0;
    start = millis();
    strip = Adafruit_NeoPixel(0, 0, NEO_GRB + NEO_KHZ800);
}

void PixelDispatcher::initialize(int reelsize, int datapin) {
    strip.setPin(datapin);
    strip.updateLength(reelsize);
    strip.begin();
    // call to "show" turns all pixels off initially
    strip.show();
}

/**
 * Use a state machine manager instead of calls to delay().
 *
 * This method updates an internal long for how long of an interval has
 * passed, and checks against how long the current wait time should be.
 */
bool PixelDispatcher::continueWaiting(int wait) {
    unsigned long now = millis();
    if (now - start < wait) {
        return true;
    }
    start = now;
    return false;
}

void PixelDispatcher::runMode(int mode, int wait, int brightness) {
    // Should we even try to cycle?
    if (continueWaiting(wait)) {
        return;
    }
    // Did mode change? If so, we might need to reset some values.
    // Re-dispatch to correct method as needed.
    switch (mode) {
        case 0 :
            // Turn off pixels
            strip.clear();
            strip.show();
            break;
        case 1 :
            // Rainbow
            rainbow(brightness);
            break;
        default :
            // Should be unreachable, but just in case, turn off all
            // pixels.
            strip.clear();
            strip.show();
            break;
    }
}

/**
 * This function will produce a routine that displays and cycles a
 * rainbow hue gradient once. When repeated, the effect should be
 * continuous.
 */
void PixelDispatcher::rainbow(int brightness) {
    Serial.print("Selected hue to display is: ");
    Serial.println(rainbow_hue);
    // Used to determine how many complete rainbow cycles to display
    // along strand of known size.
    int reps = 3;
    // The Adafruit Neopixel library has a wicked awesome rainbow()
    // function and I'm just now learning about this?
    strip.rainbow(rainbow_hue, reps, 255, brightness);
    strip.show();
    rainbow_hue = rainbow_hue + 256;
}
