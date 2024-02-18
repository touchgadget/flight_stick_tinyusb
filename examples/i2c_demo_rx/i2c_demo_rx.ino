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

#define DEBUG_ON  (0)

// For Adafruit TrinKey QT2040 (RP2040)
// Receive HID report on i2c interface then write it to the USB interface
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#include "flight_stick_tinyusb.h"
Adafruit_USBD_HID G_usb_hid;
FSJoystick FSJoy(&G_usb_hid);

// How many internal neopixels do we have? some boards have more than one!
#define NUMPIXELS        1
Adafruit_NeoPixel pixels(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

volatile bool G_recv_state = false; // true when G_buff has new data
volatile bool G_recv_overrun = false; // true when G_buff is processed too slow
volatile uint8_t G_buff[32];
volatile uint8_t G_buff_len = 0;    // number of bytes in G_buff

void setup() {
#if defined(NEOPIXEL_POWER)
  // If this board has a power control pin, we must set it to output and high
  // in order to enable the NeoPixels. We put this in an #if defined so it can
  // be reused for other boards without compilation errors
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
#endif

  // Initialize the NeoPixel LED
  pixels.begin();
  pixels.setBrightness(25);
  pixels.fill(0xFF0000);
  pixels.show();

  // i2x address 0x30 @ 400,000 bits/sec clock
  Wire.setClock(400000);
  Wire.begin(0x30);
  Wire.onReceive(recv);
  Wire.onRequest(req);

#if DEBUG_ON
  FSJoy.begin();
  Serial.begin(115200);
  while (!Serial && millis() < 4000) delay(10);
  Serial.println("i2c_demo_rx");
#else
  Serial.end();
  FSJoy.begin();
  delay(3000);
#endif
  while(!FSJoy.ready()) delay(10);
  FSJoy.loop();
  // Set NeoPixel LED green
  pixels.fill(0x00FF00);
  pixels.show();
}

void loop() {
  if (G_recv_state) {
    if (G_recv_overrun) {
#if DEBUG_ON
      Serial.println("i2c_rx buffer overrun");
#endif
      G_recv_overrun = false;
    }
#if DEBUG_ON
    // This is useful for debugging but is slow. Turn on only when
    // needed.
    for (int i = 0; i < G_buff_len; i++) {
      Serial.printf("%02x ", G_buff[i]);
    }
    Serial.println();
#endif
    if (FSJoy.ready() && (G_buff_len == sizeof(FSJoystick_Report_t))) {
      FSJoy.write((void *)G_buff);
      FSJoy.loop();
    }
    G_recv_state = false;
  }
}

// These are called in an **INTERRUPT CONTEXT** which means NO serial port
// access (i.e. Serial.print is illegal) and no memory allocations, etc.

// Called when the I2C slave gets written to
void recv(int len) {
  if (G_recv_state) {
    G_recv_overrun = true;
    return;
  }

  // copy to global buffer with check for overflow
  int copy_len = (len > sizeof(G_buff) ? sizeof(G_buff) : len);
  for (int i = 0; i < copy_len; i++) {
    G_buff[i] = Wire.read();
  }
  G_buff_len = copy_len;
  G_recv_state = true;
}

// Called when the I2C slave is read from
void req() {
  static uint16_t ctr = 0;
  char buff[7];
  snprintf(buff, sizeof(buff), "%06X", ctr++);
  Wire.write(buff, 6);
}
