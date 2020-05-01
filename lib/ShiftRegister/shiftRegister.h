#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

class ShiftRegister {
public:
  const int clearPin, // SRCLR
  dataPin, // SER
  clockPin, // SRCLK
  latchPin; // RCLK

  ShiftRegister(int clearPin, int dataPin, int clockPin, int latchPin):
    clearPin(clearPin), dataPin(dataPin), clockPin(clockPin), latchPin(latchPin){}
  void initShiftRegister(void);
  void initShiftRegister(const unsigned char value);
  void shiftShiftRegister(void);
};

#endif
