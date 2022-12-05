#include <ArduinoSTL.h>
#include "src/modes.h"

#define DATAPIN 5
#define BOUNCEPIN 2
#define REELSIZE 300
#define MODES 3

PixelDispatcher dispatcher;

unsigned long WAIT = 10;

uint8_t MODE = 0;
uint8_t BRIGHTNESS = 160;

unsigned long LAST_PRESS;

const uint32_t DEBOUNCE_INTERVAL = 100; // ms

void setup() {
    // put your setup code here, to run once:
    dispatcher.initialize(REELSIZE, DATAPIN);

    Serial.begin(9600);

    // Set up button pin and debouncer routines
    LAST_PRESS = millis();
    pinMode(BOUNCEPIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BOUNCEPIN), interrupt, RISING);
}

void loop() {
    // put your main code here, to run repeatedly:

    // Retrieve sensor inputs as necessary.
    WAIT = getWait();
    BRIGHTNESS = getBrightness();

    // Tell the pixels what to do.
    dispatcher.runMode(MODE, WAIT, BRIGHTNESS);
}

void interrupt() {
    unsigned long now = millis();
    if (now - LAST_PRESS < DEBOUNCE_INTERVAL) {
        // Do nothing. Do not reset timing or toggle modes.
        return;
    }
    MODE = (MODE + 1) % MODES;
    LAST_PRESS = now;
}

unsigned long getWait() {
    // Read potentiometer value from digital pins and convert to a
    // usable time value to specify the display interval in milliseconds.
    // Until this is implemented, return 50.
    return 100;
}

uint8_t getBrightness() {
    // Read potentiometer value from digital pins and convert to a
    // usable brightness level to feed to the neopixel strip. The
    // brightness level must be specified between 0 and 255 inclusive.
    // Until this is implemented, return 160.
    return 50;
}
