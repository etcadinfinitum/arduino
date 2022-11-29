#include <Adafruit_NeoPixel.h>

class PixelDispatcher {
    public:
        PixelDispatcher();
        void initialize(int reelsize, int datapin);
        void runMode(int mode, unsigned long wait, int brightness);
    private:
        Adafruit_NeoPixel strip;

        // Delay stuff.
        unsigned long start;
        bool continueWaiting(unsigned long wait);

        // Rainbow Mode stuff.
        unsigned long rainbow_hue;
        void rainbow(int brightness);

        // Marquee Mode stuff.
        int marquee_start;
        void marquee();
};
