#ifndef SHIFTREGISTERSPI_H
#define SHIFTREGISTERSPI_H

#include <SPI.h>

class ShiftRegisterSPI{
public:
  const int clearPin, // SRCLR
  dataPin = 11, // SER
  clockPin = 13, // SRCLK
  latchPin; // RCLK

  ShiftRegisterSPI(int clearPin, int latchPin):
    clearPin(clearPin), latchPin(latchPin){
      SPI.begin();
      // SPI.setMOSI(dataPin);
      // SPI.setSCK(clockPin);
      pinMode(clearPin,OUTPUT);
      // clear shift register
      digitalWrite(clearPin,LOW);
      digitalWrite(clearPin,HIGH);
      pinMode(latchPin,OUTPUT);
    }
  void initShiftRegister(void);
  void initShiftRegister(const unsigned char value);
  void shiftShiftRegister(void);
  void shiftOutSPI(const unsigned char value1, const unsigned char value2);
  void setBitOrder(const unsigned char bitOrder);
};

#endif
