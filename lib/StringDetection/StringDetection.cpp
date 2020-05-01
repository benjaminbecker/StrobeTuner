#include <Arduino.h>
#include <math.h>
#include "StringDetection.h"

int currentString = -1;
int lastString = -1;
float deviationCents = 0.;
unsigned char tunerMode = MODE_GUITAR;

int estimateTone(float frequency){
  // estimate string number based on frequency
  // 0: lower E, 1: A, 2: D, 3: G, 4: B, 5: higher E
  float frequencyRatio;
  float minFrequencyRatio = 1;
  float frequencyRatioOffset;
  float minFrequencyRatioOffset = 100;
  int idMin = -1;
  unsigned int nFreq;
  switch (tunerMode){
    case MODE_GUITAR:
      nFreq = sizeof(stringFrequencies)/sizeof(stringFrequencies[0]);
      break;
    case MODE_CHROMATIC:
      nFreq = sizeof(toneFrequencies)/sizeof(toneFrequencies[0]);
      break;
  }

  for (unsigned int id=0; id<nFreq; id++){
    switch (tunerMode){
      case MODE_GUITAR:
        frequencyRatio = frequency/stringFrequencies[id];
        break;
      case MODE_CHROMATIC:
        frequencyRatio = frequency/toneFrequencies[id];
        break;
    }
    frequencyRatioOffset = abs(1 - (frequencyRatio));
    if (frequencyRatioOffset < minFrequencyRatioOffset){
      minFrequencyRatioOffset = frequencyRatioOffset;
      minFrequencyRatio = frequencyRatio;
      idMin = id;
    }
  }
  currentString = idMin;
  // calculate deviation in cents
  deviationCents = 1200. * log(minFrequencyRatio)/log(2.);
  // return the number of the current string
  return currentString;
}

bool stringHasChanged(void){
  // returns true if detected string has changed compared to the value in memory
  bool returnValue = !(currentString==lastString);
  lastString = currentString;
  return returnValue;
}

float getDeviationCents(){
  return deviationCents;
}

void setTunerMode(unsigned char mode){
  tunerMode = mode;
}

unsigned char getTunerMode(void){
  return tunerMode;
}
