# Arduino Experiments by a ~~N00b~~ _Computer Science Student_

### Setup

Assuming the Arduino IDE is downloaded and running on your machine, test a simple sketch.

Most common error message on first execution:
`Error opening serial port <portname>: Permission denied`
Solution:
* First, type into terminal: `ls -l /dev/ttyACM*`
* The output will show what serial ports are available on the machine. We want to enable serial port permissions for the resulting ports.
* In terminal, type: `sudo usermod -a -G dialout <username>` where <username> is your username in the system.
* Lastly, we want the serial port enabled for execution in Linux. Type: `sudo chmod a+rw /dev/ttyACM0`
* In the final instruction, your port name `ttyACM<digit>` is the port name with final digit as displayed in the first `ls` step. 
If stuck, read this: http://arduino-er.blogspot.com/2014/08/arduino-ide-error-avrdude-seropen-cant.html or this: https://www.arduino.cc/en/Guide/Linux#toc2


### Documentation

My objective is to provide detailed hardware lists and circuit diagrams for 
each project; some may be simple enough to forgo the documentation for, but 
it's a good habit that could use some practicing. :)

Each subfolder will include documentation for that specific experiment.

Feel free to open an issue/comment on a commit if you have any questions.

### Hardware

Unless otherwise mentioned, all hardware used was included in the [Elegoo Super Starter Kit](https://www.amazon.com/gp/product/B01D8KOZF4/ref=oh_aui_detailpage_o00_s00?ie=UTF8&psc=1). 
