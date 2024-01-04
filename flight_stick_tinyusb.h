/************************************************************************
MIT License

Copyright (c) 2023-2024 touchgadgetdev@gmail.com

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
*************************************************************************/
#pragma once
#include "Adafruit_TinyUSB.h"

// Dpad directions
typedef uint8_t FSDirection_t;
#define FSJOYSTICK_DPAD_UP  0
#define FSJOYSTICK_DPAD_UP_RIGHT 1
#define FSJOYSTICK_DPAD_RIGHT 2
#define FSJOYSTICK_DPAD_DOWN_RIGHT 3
#define FSJOYSTICK_DPAD_DOWN 4
#define FSJOYSTICK_DPAD_DOWN_LEFT 5
#define FSJOYSTICK_DPAD_LEFT 6
#define FSJOYSTICK_DPAD_UP_LEFT 7
#define FSJOYSTICK_DPAD_CENTERED 0xF

enum FSBUTTONS {
  FSBUTTON_0 = 0,
  FSBUTTON_front = 0,
  FSBUTTON_1 = 1,
  FSBUTTON_side = 1,
  FSBUTTON_2,         // top large left
  FSBUTTON_3,         // top large right
  FSBUTTON_4,         // top small left
  FSBUTTON_5,         // top small right
  FSBUTTON_6,         // base buttons
  FSBUTTON_7,
  FSBUTTON_8,
  FSBUTTON_9,
  FSBUTTON_10,
  FSBUTTON_11,
};

// Flight sim joystick HID report layout
// Large joystick X, Y, Z (twist) axes
// 8 way hat switch
// 12 buttons (6 on the stick, 6 on the base)
// throttle slider
typedef struct __attribute__ ((packed)) {
  uint32_t x : 10;      // 0..512..1023
  uint32_t y : 10;      // 0..512..1023
  uint32_t hat : 4;
  uint32_t twist : 8;   // 0..127..255
  uint8_t buttons_a;
  uint8_t slider;       // 0..255
  uint8_t buttons_b;
} FSJoystick_Report_t;

// HID report descriptor using TinyUSB's template
// Single Report (no ID) descriptor
uint8_t const desc_hid_report[] = {
  0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
  0x09, 0x04,        // Usage (Joystick)
  0xA1, 0x01,        // Collection (Application)
  0xA1, 0x02,        //   Collection (Logical)
  0x95, 0x02,        //     Report Count (2)
  0x75, 0x0A,        //     Report Size (10)
  0x15, 0x00,        //     Logical Minimum (0)
  0x26, 0xFF, 0x03,  //     Logical Maximum (1023)
  0x35, 0x00,        //     Physical Minimum (0)
  0x46, 0xFF, 0x03,  //     Physical Maximum (1023)
  0x09, 0x30,        //     Usage (X)
  0x09, 0x31,        //     Usage (Y)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x75, 0x04,        //     Report Size (4)
  0x95, 0x01,        //     Report Count (1)
  0x25, 0x07,        //     Logical Maximum (7)
  0x46, 0x3B, 0x01,  //     Physical Maximum (315)
  0x66, 0x14, 0x00,  //     Unit (System: English Rotation, Length: Centimeter)
  0x09, 0x39,        //     Usage (Hat switch)
  0x81, 0x42,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,Null State)
  0x65, 0x00,        //     Unit (None)
  0x75, 0x08,        //     Report Size (8)
  0x26, 0xFF, 0x00,  //     Logical Maximum (255)
  0x46, 0xFF, 0x00,  //     Physical Maximum (255)
  0x09, 0x35,        //     Usage (Rz)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xA4,              //     Push
  0x95, 0x08,        //       Report Count (8)
  0x75, 0x01,        //       Report Size (1)
  0x25, 0x01,        //       Logical Maximum (1)
  0x45, 0x01,        //       Physical Maximum (1)
  0x05, 0x09,        //       Usage Page (Button)
  0x19, 0x01,        //       Usage Minimum (0x01)
  0x29, 0x08,        //       Usage Maximum (0x08)
  0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xB4,              //     Pop
  0x09, 0x36,        //     Usage (Slider)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x95, 0x04,        //     Report Count (4)
  0x75, 0x01,        //     Report Size (1)
  0x25, 0x01,        //     Logical Maximum (1)
  0x45, 0x01,        //     Physical Maximum (1)
  0x05, 0x09,        //     Usage Page (Button)
  0x19, 0x09,        //     Usage Minimum (0x09)
  0x29, 0x0C,        //     Usage Maximum (0x0C)
  0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0x95, 0x04,        //     Report Count (4)
  0x81, 0x01,        //     Input (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
  0xC0,              //   End Collection
  0xA1, 0x02,        //   Collection (Logical)
  0x95, 0x04,        //     Report Count (4)
  0x75, 0x08,        //     Report Size (8)
  0x26, 0xFF, 0x00,  //     Logical Maximum (255)
  0x46, 0xFF, 0x00,  //     Physical Maximum (255)
  0x06, 0x00, 0xFF,  //     Usage Page (Vendor Defined 0xFF00)
  0x09, 0x01,        //     Usage (0x01)
  0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  0xC0,              //   End Collection
  0xC0,              // End Collection
};

class FSJoystick {
  public:
    inline FSJoystick(Adafruit_USBD_HID *usb_hid);

    inline void begin(void);
    inline void end(void);
    inline void loop(void);
    inline void write(void);
    inline void write(void *report);
    inline void press(uint8_t b);
    inline void release(uint8_t b);
    inline void releaseAll(void) { _report.buttons_a = _report.buttons_b = 0;  }
    inline void buttons(uint16_t b) {
      _report.buttons_a = b & 0xFF;
      _report.buttons_b = (b & 0x0F00) >> 4;
    }
    inline void xAxis(int a) { _report.x = a; }
    inline void yAxis(int a) { _report.y = a; }
    inline void twist(uint8_t a) { _report.twist = a; }
    inline void slider(uint8_t a) { _report.slider= a; }
    inline void dPad(FSDirection_t d) { _report.hat = d; }
    inline void dPad(bool up, bool down, bool left, bool right);
    inline bool ready(void) { return this->usb_hid->ready(); }

    // Sending is public for advanced users.
    inline bool SendReport(void* data, size_t length) {
      return this->usb_hid->sendReport(0, data, (uint8_t)length);
    }

  protected:
    FSJoystick_Report_t _report;
    uint32_t startMillis;
    Adafruit_USBD_HID *usb_hid;
};

FSJoystick::FSJoystick(Adafruit_USBD_HID *usb_hid)
{
  this->startMillis = 0;
  this->usb_hid = usb_hid;
}

void FSJoystick::begin(void)
{
  this->usb_hid->setPollInterval(2);
  this->usb_hid->setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  this->usb_hid->begin();

  // release all buttons, center all sticks, etc.
  end();
  startMillis = millis();
}

void FSJoystick::loop(void)
{
  if (startMillis != millis()) {
    write();
    startMillis = millis();
  }
}

void FSJoystick::end(void)
{
  memset(&_report, 0x00, sizeof(_report));
  _report.x = _report.y = 512;
  _report.twist = _report.slider = 0x80;
  _report.hat = FSJOYSTICK_DPAD_CENTERED;
}

void FSJoystick::write(void)
{
  SendReport(&_report, sizeof(_report));
}

void FSJoystick::write(void *report)
{
  memcpy(&_report, report, sizeof(_report));
  SendReport(&_report, sizeof(_report));
}

void FSJoystick::press(uint8_t b)
{
  enum FSBUTTONS btn = constrain((enum FSBUTTONS)b, FSBUTTON_front,
      FSBUTTON_11);
  if (btn < FSBUTTON_8) {
    _report.buttons_a |= 1 << btn;
  } else {
    _report.buttons_b |= 1 << (btn - FSBUTTON_8);
  }
}


void FSJoystick::release(uint8_t b)
{
  enum FSBUTTONS btn = constrain((enum FSBUTTONS)b, FSBUTTON_front,
      FSBUTTON_11);
  if (btn < FSBUTTON_8) {
    _report.buttons_a &= ~(1 << btn);
  } else {
    _report.buttons_b &= ~(1 << (btn - FSBUTTON_8));
  }
}

// The direction pad is limited to 8 directions plus centered. This means
// some combinations of 4 dpad buttons are not valid and cannot be sent.
// Button down = true(1)
// Valid: Any 1 button down, any 2 adjacent buttons down, no buttons down
// Invalid: all other combinations
void FSJoystick::dPad(bool up, bool down, bool left, bool right)
{
  static const FSDirection_t BITS2DIR[16] = {
    FSJOYSTICK_DPAD_CENTERED,    // 0000
    FSJOYSTICK_DPAD_RIGHT,       // 0001
    FSJOYSTICK_DPAD_LEFT,        // 0010
    FSJOYSTICK_DPAD_CENTERED,    // 0011
    FSJOYSTICK_DPAD_DOWN,        // 0100
    FSJOYSTICK_DPAD_DOWN_RIGHT,  // 0101
    FSJOYSTICK_DPAD_DOWN_LEFT,   // 0110
    FSJOYSTICK_DPAD_CENTERED,    // 0111
    FSJOYSTICK_DPAD_UP,          // 1000
    FSJOYSTICK_DPAD_UP_RIGHT,    // 1001
    FSJOYSTICK_DPAD_UP_LEFT,     // 1010
    FSJOYSTICK_DPAD_CENTERED,    // 1011
    FSJOYSTICK_DPAD_CENTERED,    // 1100
    FSJOYSTICK_DPAD_CENTERED,    // 1101
    FSJOYSTICK_DPAD_CENTERED,    // 1110
    FSJOYSTICK_DPAD_CENTERED     // 1111
  };
  uint8_t dpad_bits = (up << 3) | (down << 2) | (left << 1) | (right << 0);
  _report.hat = BITS2DIR[dpad_bits];
}
