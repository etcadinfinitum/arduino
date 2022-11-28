#include <ArduinoSTL.h>
#include "src/modes.h"

#define DATAPIN 2
#define REELSIZE 300

PixelDispatcher dispatcher;

uint32_t MODE = 0;
uint32_t WAIT = 50;
uint32_t BRIGHTNESS = 160;

void setup() {
    // put your setup code here, to run once:
    dispatcher.initialize(REELSIZE, DATAPIN);
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:

    // Retrieve sensor inputs as necessary.
    MODE = getMode();
    WAIT = getWait();
    BRIGHTNESS = getBrightness();

    // Tell the pixels what to do.
    dispatcher.runMode(MODE, WAIT, BRIGHTNESS);
}

uint32_t getMode() {
    // Read button presses from digital pins to get mode selection.
    // This function is also responsible for managing value modulos
    // to ensure a valid mode is set.
    // Until this is implemented, return 0.
    return 0;
}

uint32_t getWait() {
    // Read potentiometer value from digital pins and convert to a
    // usable time value to specify the display interval in milliseconds.
    // Until this is implemented, return 50.
    return 50;
}

uint32_t getBrightness() {
    // Read potentiometer value from digital pins and convert to a
    // usable brightness level to feed to the neopixel strip. The
    // brightness level must be specified between 0 and 255 inclusive.
    // Until this is implemented, return 160.
    return 160;
}
