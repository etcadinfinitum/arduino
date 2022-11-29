#include <Adafruit_NeoPixel.h>

class PixelDispatcher {
    public:
        PixelDispatcher();
        void initialize(int reelsize, int datapin);
        void runMode(int mode, int wait, int brightness);
    private:
        Adafruit_NeoPixel strip;

        // Delay stuff.
        unsigned long start;
        bool continueWaiting(int wait);

        // Rainbow Mode stuff.
        unsigned long rainbow_hue;
        void rainbow(int brightness);
};
