#include <ArduinoSTL.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define DATAPIN 2
#define REELSIZE 300

Adafruit_NeoPixel the_strip = Adafruit_NeoPixel(300, DATAPIN, NEO_GRB + NEO_KHZ800);

uint32_t MODE       = 0;
uint32_t WAIT       = 50;
uint32_t BRIGHTNESS = 160;

void setup() {
    // put your setup code here, to run once:
    the_strip.begin();
    // call to "show" turns all pixels off initially
    the_strip.show();
    Serial.begin(9600);
}

void loop() {
    // put your main code here, to run repeatedly:

    // Retrieve sensor inputs as necessary.
    MODE = getMode();
    WAIT = getWait();
    BRIGHTNESS = getBrightness();

    // 
    rainbow(0, 255);
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

/**
 * This function will produce a routine that displays and cycles a
 * rainbow hue gradient once. When repeated, the effect should be
 * continuous.
 */
void rainbow(int speed, int brightness) {
    // Used to determine how many complete rainbow cycles to display
    // along strand of known size.
    int reps = 3;
    // The Adafruit Neopixel library has a wicked awesome rainbow()
    // function and I'm just now learning about this?
    the_strip.rainbow(0, reps, 255, brightness);
    the_strip.show();
    if (speed > 0) {
        int hue_interval = 65536 * reps / REELSIZE;
        for (int h = hue_interval; h < 65536, h += hue_interval) {
            delay(speed);
            the_strip.rainbow(h, reps, 255, brightness);
            the_strip.show();
        }
    }
    delay(speed);
}
