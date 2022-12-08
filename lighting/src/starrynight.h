#include <ArduinoSTL.h>

#define TWINKLE_COUNT 5

struct RGB {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

struct Twinklers {
    uint8_t idx;
    int duration;   // ms
    int elapsed;    // ms
    RGB rgb;
    bool reverse;   // necessary?
};

struct Night {
    uint8_t range;
    uint8_t speed;
};

class StarryNight {
    public:
        // Constructor
        StarryNight(uint8_t stripLength);
        // Want a very (very) simple interface to the class.
        // Should only be able to instantiate, request an update,
        // and return a color value given a pixel position.
        void update();
        uint8_t getR(uint8_t position);
        uint8_t getG(uint8_t position);
        uint8_t getB(uint8_t position);
    private:
        uint8_t pixelCount;
        RGB* colorData;
        // Set color baseline for nighttime colors
        RGB nighttime[3] = {
            {0, 0, 15},
            {5, 0, 40}, 
            {0, 5, 30}
        };
        Twinklers twinklers[TWINKLE_COUNT];
        Night* nightLights;
        void initializeTwinkles(int arrIdx = -1);
        void initializeNight();
        void pickTwinkleColors(int i);
        uint8_t getTwinklerIdx(uint8_t position);
        bool isStar(uint8_t position);
        void cycleTwinkleColors(uint8_t position);
        void cycleNightSkyColors(uint8_t idx);
};
