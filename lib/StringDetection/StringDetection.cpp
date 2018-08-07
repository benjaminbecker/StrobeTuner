#include <Arduino.h>

int currentString = -1;
int lastString = -1;
const float stringFrequencies[6] = {82.41,110.0,146.83,196,246.94,329.63};

int estimateString(float frequency){
  // estimate string number based on frequency
  // 0: lower E, 1: A, 2: D, 3: G, 4: B, 5: higher E
  float frequencyRatio;
  float minFrequencyRatio = 100;
  int idMin = -1;
  for (int id=0; id<6; id++){
    frequencyRatio = abs(1 - (frequency/stringFrequencies[id]));
    if (frequencyRatio < minFrequencyRatio){
      minFrequencyRatio = frequencyRatio;
      idMin = id;
    }
  }
  currentString = idMin;
  return currentString;
}

bool stringHasChanged(void){
  // returns true if detected string has changed compared to the value in memory
  bool returnValue = !(currentString==lastString);
  lastString = currentString;
  return returnValue;
}
