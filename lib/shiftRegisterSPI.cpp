#include "shiftRegisterSPI.h"
#include <Arduino.h>

void ShiftRegisterSPI::initShiftRegister(void){
  // initializes shift register with a single 1
  // Pin Configuration
  pinMode(clearPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  digitalWrite(dataPin,LOW);
  digitalWrite(clockPin,LOW);
  digitalWrite(latchPin,LOW);
  // clear shift register
  digitalWrite(clearPin,LOW);
  digitalWrite(clearPin,HIGH);
  // write a one to the shift register
  digitalWrite(dataPin,HIGH);
  digitalWrite(clockPin,HIGH);
  digitalWrite(clockPin,LOW);
  digitalWrite(dataPin ,LOW);
  // needed for circular shift register [?]
  pinMode(dataPin,INPUT);
  // latchPin to HIGH
  digitalWrite(latchPin, HIGH);
}

void ShiftRegisterSPI::initShiftRegister(const unsigned char value){
  // initializes shift register with value (8 bits)
  // Pin Configuration
  pinMode(clearPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  digitalWrite(dataPin,LOW);
  digitalWrite(clockPin,LOW);
  digitalWrite(latchPin,LOW);
  // clear shift register
  digitalWrite(clearPin,LOW);
  digitalWrite(clearPin,HIGH);
  // shift out value
  shiftOut(dataPin, clockPin, MSBFIRST, value);
  // needed for circular shift register [?]
  pinMode(dataPin,INPUT);
  // latchPin to HIGH
  digitalWrite(latchPin, HIGH);
}

void ShiftRegisterSPI::shiftShiftRegister(void){
  digitalWrite(latchPin,LOW);
  digitalWrite(clockPin,LOW);
  digitalWrite(clockPin,HIGH);
  digitalWrite(latchPin,HIGH);
}

void ShiftRegisterSPI::shiftOutSPI(const unsigned char value1, const unsigned char value2){
  digitalWrite(latchPin, LOW);
  SPI.transfer(value1);
  SPI.transfer(value2);
  // shiftOut(dataPin, clockPin, MSBFIRST, value);
  digitalWrite(latchPin, HIGH);
}

void ShiftRegisterSPI::setBitOrder(const unsigned char bitOrder){
  SPI.setBitOrder(bitOrder); 
}
