# USB Flight Joystick Arduino Library Using Adafruit TinyUSB

Create USB flight joysticks using Arduino and Adafruit TinyUSB. This has only
been tested on RP2040 boards such as the Raspberry Pi Pico using the [Earle
Philhower RP2040 board
package](https://github.com/earlephilhower/arduino-pico).

This may work on other boards supported by the Adafruit TinyUSB library but
no testing has been done.

The 3D joystick has the following controls.

Control |Description
--------|---------------
X       |10 bits, 0..1023
Y       |10 bits, 0..1023
Z       |8 bits, 0..255
Throttle|8 bits, 0..255
Buttons |12 buttons
Hat     |8 way hat switch/direction pad

The HID report has been carefully chosen so it works with the Xbox Adaptive
Controller(XAC). All the other open source XAC joysticks I have seen use 8 bits
for X and Y. When used with XAC, only the X, Y, and 8 buttons are supported.
This is a limitation of the XAC.

Install this library by downloading a zip file from this repo. Use the IDE
"Add .zip library" option.

## Dependencies

Use the IDE Library Manager to install the following libraries.

* "Adafruit TinyUSB Library"
* "Adafruit NeoPixel"

Install this project as a library by download it as a ZIP file from https://github.com/touchgadget/flight_stick_tinyusb.
Then use the Arduino IDE option to install the ZIP as a library.

## Troubleshooting

If the following error message appears when compiling, change the USB Stack to
"Adafruit TinyUSB" as it says in the message.

```
   32 | #error TinyUSB is not selected, please select it in "Tools->Menu->USB Stack"
      |  ^~~~~
```
