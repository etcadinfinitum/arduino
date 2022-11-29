# Superfluously Home-Baked LED Accent Lighting

I didn't want to pay a trivial extra number of dollars to buy LED RGB
lightstrips that already have a bunch of settings with a bluetooth
remote.

Bells and whistles are for people with no dedication and no
self-loathing.

So, like the obstinate curmudgeon that I am, I am building a thing
that will likely be frustrating, won't work as well, and if I
"productionize" it, will cost more money than the $40 light strips I
could buy off of Amazon.

## Materials

I have an Elegoo super starter kit, some very mangled pin wires, and
some off-brand WS2812D lights in a 300-pixel 16.4-foot roll. I also
have an Arduino knockoff device that must be at least 5 years old at
time of writing. YOLO until you ohno, I guess.

Exact materials used:

- Aforementioned Arduino thingy
- Aforementioned lights
- ???

## The Plan

Currently, the plan is to write and load some routines for the LED
strip onto the Arduino, and to make the routine selection configurable
on a cycle using a button. I'd also like to add at least one
potentiometer to configure dimming, because I'm an aesthetically picky
bitch and I love dimmer switches.

Tentatively, it might be interesting to add a second potentiometer
to be able to specify speed. I'd also like to have some kind of visual
status indicators; maybe 7-segment displays, maybe a full LCD display.

I have some useful code in this same repository that I will cannibalize
for individual routines; most likely, the breadboarding is going to be
the trickiest part since I haven't done anything like this since I
started a big grown-up jobby job and my memory is garbage.

Breadboarding is fine for prototyping, but not exactly stable for
day-to-day usage, and I've never printed a PCB or soldered components
for any electronics project before, so I may look into that down the
line.

## Technical Notes

I have the memory of a goldfish, so as follows are my notes for how
to actually do all this stuff.

### Host Machine Software Prerequisites

This should be one-and-done stuff.

I'm not worried about having the Arduino IDE because I'm an
insufferable sOfTwArE eNgiNeEr aNd i UsE ViM

...but I still need at least a few libraries in the Arduino STL, as
well as the CLI tool. Installation instructions are
[in the docs](https://arduino.github.io/arduino-cli/0.29/installation/)
for the Arduino CLI tool; I'm on Linux so `curl`ing the installation
script is the way to go. For completion and consistency:

```shell
$ sudo apt-get install arduino
$ sudo usermod -a -G tty $USER
$ sudo usermod -a -G dialout $USER
$ curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sudo BINDIR=/usr/local/bin sh
```

Installed libs:

```shell
$ arduino-cli core update-index
$ arduino-cli core install arduino:avr
$ arduino-cli lib install ArduinoSTL
$ arduino-cli lib install "Adafruit NeoPixel"
$ arduino-cli lib install FTDebouncer
$ arduino-cli core list
```

### Interacting With the Board

With the pre-requisites done, the board should be discoverable and
attachable, if it isn't already automatically detected and attached.
It's an Elegoo knockoff board but mimics an Arduino Uno.

```shell
$ sudo dmsg | grep -C 8 Arduino
[Will show discoverable port number]
$ arduino-cli board attach -p /dev/ttyACM0
$ arduino-cli board list
Port         Protocol Type              Board Name  FQBN            Core       
/dev/ttyACM0 serial   Serial Port (USB) Arduino Uno arduino:avr:uno arduino:avr
```

### Compiling and Uploading

1. Make sure the Arduino device is plugged into the computer.
2. Wire the ground and 5V lines on the LED strip to power & ground
   sources and ensure the strip's data pin is wired into the pin
   specified in the sketch.

```shell
# I have found that trying to specify the sketch file produces errors.
$ arduino-cli compile --fqbn arduino:avr:uno
$ arduino-cli arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno lighting
```
