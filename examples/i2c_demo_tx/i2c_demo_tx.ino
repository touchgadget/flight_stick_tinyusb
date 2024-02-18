/*
MIT License

Copyright (c) 2024 touchgadgetdev@gmail.com

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
#include <Wire.h>

void setup() {
  Wire.setClock(400000);
  Wire.begin();
}

void loop() {
  static FSJoystick_Report_t FSJoy;
  static bool buttons_on = false;

  memset(&FSJoy, 0, sizeof(FSJoy));
  if (buttons_on) {
    FSJoy.buttons_a = FSJoy.buttons_b = 0x00;
    buttons_on = false;
  } else {
    FSJoy.buttons_a = FSJoy.buttons_b = 0xFF;
    buttons_on = true;
  }
  FSJoy.x = random(1024);
  FSJoy.y = random(1024);
  FSJoy.twist = random(256);
  FSJoy.slider = random(256);

  // Go through all dPad positions
  static uint8_t dpad = FSJOYSTICK_DPAD_UP;
  FSJoy.hat = dpad++;
  if (dpad > FSJOYSTICK_DPAD_UP_LEFT)
    dpad = FSJOYSTICK_DPAD_UP;

  // Functions above only set the values.
  // This writes the report to the i2c joystick device.
  Wire.beginTransmission(0x30);
  Wire.write((uint8_t *)&FSJoy, sizeof(FSJoy));
  Wire.endTransmission();

  delay(100);
}
