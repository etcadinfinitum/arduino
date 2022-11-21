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
