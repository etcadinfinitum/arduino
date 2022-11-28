#include <Adafruit_NeoPixel.h>

class PixelDispatcher {
    public:
        PixelDispatcher();
        void initialize(int reelsize, int datapin);
        void runMode(int mode, int wait, int brightness);
    private:
        Adafruit_NeoPixel strip;
        int rainbow_hue;
        void rainbow(int speed, int brightness);
};
