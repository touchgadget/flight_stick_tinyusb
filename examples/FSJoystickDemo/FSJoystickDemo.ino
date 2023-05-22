/*
MIT License

Copyright (c) 2023 touchgadgetdev@gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "flight_stick_tinyusb.h"
Adafruit_USBD_HID G_usb_hid;
FSJoystick FSJoy(&G_usb_hid);

void setup() {
  FSJoy.begin();

  // wait until device mounted
  while( !USBDevice.mounted() ) delay(1);
}

void loop() {
  static uint8_t count = FSBUTTON_0;
  if (count > FSBUTTON_11) {
    FSJoy.releaseAll();
    count = FSBUTTON_0;
  }
  FSJoy.press(count);
  count++;

  // Move x/y Axis to a random position (10-bit)
  FSJoy.xAxis(random(1024));
  FSJoy.yAxis(random(1024));
  FSJoy.twist(random(256));
  FSJoy.slider(random(256));

  // Go through all dPad positions
  static uint8_t dpad = FSJOYSTICK_DPAD_UP;
  FSJoy.dPad(dpad++);
  if (dpad > FSJOYSTICK_DPAD_UP_LEFT)
    dpad = FSJOYSTICK_DPAD_UP;

  // Functions above only set the values.
  // This writes the report to the host.
  if ( FSJoy.ready() ) FSJoy.loop();
  delay(100);
}
