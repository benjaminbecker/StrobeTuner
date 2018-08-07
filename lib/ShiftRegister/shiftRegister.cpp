#include "shiftRegister.h"
#include <Arduino.h>

ShiftRegister::ShiftRegister(int clearpin, int datapin, int clockpin, int latchpin){
  clearPin = clearpin;
  dataPin = datapin;
  clockPin = clockpin;
  latchPin = latchpin;
}

void ShiftRegister::initShiftRegister(void){
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
}

void ShiftRegister::shiftShiftRegister(void){
  digitalWrite(latchPin,HIGH);
  digitalWrite(clockPin,LOW);
  digitalWrite(clockPin,HIGH);
  digitalWrite(latchPin,LOW);
}
