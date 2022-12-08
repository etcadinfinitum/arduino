#include <Adafruit_NeoPixel.h>
#include "starrynight.h"

class PixelDispatcher {
    public:
        PixelDispatcher();
        void initialize(int reelsize, int datapin);
        void runMode(uint8_t mode, unsigned long wait, uint8_t brightness);
    private:
        Adafruit_NeoPixel strip;

        // Delay stuff.
        unsigned long start;
        bool continueWaiting(unsigned long wait);

        // Rainbow Mode stuff.
        unsigned long rainbow_hue;
        void rainbow();

        // Marquee Mode stuff.
        int marquee_start;
        void marquee();

        // Night Sky stuff.
        StarryNight* starryNightObj;
        void starryNight();
};
