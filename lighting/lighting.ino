#include <ArduinoSTL.h>
#include <FTDebouncer.h>
#include "src/modes.h"

#define DATAPIN 2
#define BOUNCEPIN 12
#define REELSIZE 300
#define MODES 2

PixelDispatcher dispatcher;
FTDebouncer debouncer;

uint32_t MODE = 0;
uint32_t WAIT = 50;
uint32_t BRIGHTNESS = 160;

void setup() {
    // put your setup code here, to run once:
    dispatcher.initialize(REELSIZE, DATAPIN);

    debouncer.addPin(BOUNCEPIN, LOW);
    debouncer.begin();

    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:

    debouncer.update();

    // Retrieve sensor inputs as necessary.
    WAIT = getWait();
    BRIGHTNESS = getBrightness();

    // Tell the pixels what to do.
    dispatcher.runMode(MODE, WAIT, BRIGHTNESS);
}

void onPinActivated(int pin) {
    // Read button presses from digital pins to get mode selection.
    // This function is also responsible for managing value modulos
    // to ensure a valid mode is set.
    if (pin == BOUNCEPIN) {
        MODE = (MODE + 1) % MODES;
        Serial.print("In onPinActivated(). Pin number: ");
        Serial.println(pin);
        Serial.print("Toggled to mode: ");
        Serial.println(MODE);
    }
}

void onPinDeactivated(int pin) {
    if (pin == BOUNCEPIN) {
        Serial.print("In onPinDeactivated(). Pin number: ");
        Serial.println(pin);
        Serial.print("Toggled to mode: ");
        Serial.println(MODE);
    }
    // Do nothing.
}

uint32_t getWait() {
    // Read potentiometer value from digital pins and convert to a
    // usable time value to specify the display interval in milliseconds.
    // Until this is implemented, return 50.
    return 10;
}

uint32_t getBrightness() {
    // Read potentiometer value from digital pins and convert to a
    // usable brightness level to feed to the neopixel strip. The
    // brightness level must be specified between 0 and 255 inclusive.
    // Until this is implemented, return 160.
    return 160;
}
