#include "starrynight.h"
#include <Arduino.h>

StarryNight::StarryNight(uint8_t stripLength) : pixelCount(stripLength), colorData(new RGB[stripLength]), nightLights(new Night[stripLength]) {
    // seed random number
    randomSeed(analogRead(0));
    initializeTwinkles();
    initializeNight();
}

void StarryNight::initializeTwinkles(int arrIdx = -1) {
    if (arrIdx < 0) {
        // If we didn't get a specific marker to cycle, then we want
        // to initialize the entire array of twinklers.
        for (uint8_t i = 0; i < TWINKLE_COUNT; i++) {
            pickTwinkleColors(i);
        }
    } else if (arrIdx < TWINKLE_COUNT) {
        // Call directly for a single twinkler setting.
        pickTwinkleColors(arrIdx);
    }
}

void StarryNight::initializeNight() {
    // initialize information about each light's speed, initial color, and fade pattern
    for (uint8_t i = 0; i < pixelCount; i++) {
        uint8_t range = (random(1000) % 10) + 1;
        uint8_t fastiboi = (random(1000) % 6) + 1;
        nightLights[i].range = range;
        nightLights[i].speed = fastiboi;
    }
}        

void StarryNight::pickTwinkleColors(int i) {
    bool added = false;
    uint8_t newIdx = 0;
    while (!added) {
        added = true;
        newIdx = random(1000) % pixelCount;
        for (int j = 0; j < i; j++) {
            if (newIdx == twinklers[i].idx) {
                added = false;
            }
        }
    }
    // if previous while block passes, then a unique index has been selected. now choose a color range
    // trying to be clever and pick a color at random (instead of defining a color array)
    // may switch to defining an array depending on color output
    twinklers[i] = {
        newIdx,             // location of star
        random(25, 100),    // how many frames each cycle lasts
        0,                  // how many frames along the current cycle is
        {random(225, 256), random(225, 256), random(225, 256)}, // RGB
        false               // reverse?
    };
}

bool StarryNight::isStar(uint8_t position) {
    for (uint8_t i = 0; i < TWINKLE_COUNT; i++) {
        if (twinklers[i].idx == position) return true;
    }
    return false;
}

uint8_t StarryNight::getTwinklerIdx(uint8_t position) {
    // Convert a position index in the LED strip to an index into the
    // star array. Do not validate that the position exists; should use isStar() for that.
    for (uint8_t i = 0; i < TWINKLE_COUNT; i++) {
        if (twinklers[i].idx == position) return i;
    }
    // Should be unreachable with correct client usage.
    return 0;
}

void StarryNight::update() {
    for (uint8_t i = 0; i < pixelCount; i++) {
        if (isStar(i)) {
            cycleTwinkleColors(i);
        } else {
            cycleNightSkyColors(i);
        }
    }
}

void StarryNight::cycleTwinkleColors(uint8_t position) {
    Twinklers star = twinklers[getTwinklerIdx(position)];
    // change color brightness
    // case 1: star is getting brighter (first half of duration cycle with reverse == 0)
    if (!star.reverse && star.elapsed < star.duration / 2) {
        // set RBG values to be proportionate to the brightness rate of the cycle
        uint8_t R = (star.rgb.r / (star.elapsed / 2)) * star.elapsed;
        uint8_t G = (star.rgb.g / (star.elapsed / 2)) * star.elapsed;
        uint8_t B = (star.rgb.b / (star.elapsed / 2)) * star.elapsed;
        colorData[position] = {R, G, B};
    } else if (star.reverse && star.elapsed > star.duration / 2) {
        // set RGB values to be proportionate to the brightness rate of the cycle
        uint8_t R = star.rgb.r - ((star.elapsed - (star.duration / 2)) * (star.rgb.r * 2 / star.duration));
        uint8_t G = star.rgb.g - ((star.elapsed - (star.duration / 2)) * (star.rgb.g * 2 / star.duration));
        uint8_t B = star.rgb.b - ((star.elapsed - (star.duration / 2)) * (star.rgb.b * 2 / star.duration));
        colorData[position] = {R, G, B};
    } else {
        colorData[position] = star.rgb;
    }
    // increment elapsedTime value
    star.elapsed = star.elapsed + 1;
    // if the brightness counter has maxed out, set the reverse value to 1 instead of 0 so light will dim
    if (!star.reverse && star.elapsed == star.duration) {
        star.reverse = true;
        star.elapsed = 0;
    }
    // if the current star is at the end of its cycle, then select a new light to twinkle
    if (star.reverse && star.elapsed == star.duration) {
        pickTwinkleColors(getTwinklerIdx(position));
    }
}

void StarryNight::cycleNightSkyColors(uint8_t idx) {
    uint8_t range = nightLights[idx].range;
    uint8_t phase = nightLights[idx].speed % (range * 4);
    uint8_t cycle = (phase - (phase % range)) / range;
    uint8_t interval = phase % range;
    uint8_t R = nighttime[idx % 3].r;
    uint8_t G = nighttime[idx % 3].g;
    uint8_t B = nighttime[idx % 3].b;
    switch (cycle) {
        case 0: 
            R = (R == 0 ? 0 : R + interval);
            G = (G == 0 ? 0 : G + interval); 
            B = (B == 0 ? 0 : B + interval);
            break;
        case 1: 
            R = (R == 0 ? 0 : R + (range - interval));
            G = (G == 0 ? 0 : G + (range - interval));
            B = (B == 0 ? 0 : B + (range - interval));
            break;
        case 2:
            R = (R == 0 ? 0 : (R - interval < 0 ? 0 : R - interval));
            G = (G == 0 ? 0 : (G - interval < 0 ? 0 : G - interval));
            B = (B == 0 ? 0 : (B - interval < 0 ? 0 : B - interval));
            break;
        case 3:
            R = (R == 0 ? 0 : (R - (range - interval) < 0 ? 0 : R - (range - interval)));
            G = (G == 0 ? 0 : (G - (range - interval) < 0 ? 0 : G - (range - interval)));
            B = (B == 0 ? 0 : (B - (range - interval) < 0 ? 0 : B - (range - interval)));
            break;
    }
    colorData[idx] = {R, G, B};
}

uint8_t StarryNight::getR(uint8_t position) {
    return colorData[position].r;
}

uint8_t StarryNight::getG(uint8_t position) {
    return colorData[position].g;
}

uint8_t StarryNight::getB(uint8_t position) {
    return colorData[position].b;
}
