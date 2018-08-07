#ifndef SHIFTREGISTER_H
#define SHIFTREGISTER_H

class ShiftRegister {
public:
  int clearPin, // SRCLR
  dataPin, // SER
  clockPin, // SRCLK
  latchPin; // RCLK

  ShiftRegister(int clearpin, int datapin, int clockpin, int latchpin);
  void initShiftRegister(void);
  void shiftShiftRegister(void);
};

#endif
