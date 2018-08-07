#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=78,342
AudioEffectWaveshaper    waveshape1;     //xy=249,359
AudioAnalyzeNoteFrequency notefreq1;      //xy=372,244
AudioFilterStateVariable filter1;        //xy=403,345
AudioMixer4              mixer1;         //xy=549,312
AudioOutputAnalog        dac1;           //xy=690,304
AudioConnection          patchCord1(adc1, notefreq1);
AudioConnection          patchCord2(adc1, waveshape1);
AudioConnection          patchCord3(waveshape1, 0, filter1, 0);
AudioConnection          patchCord4(filter1, 1, mixer1, 0);
AudioConnection          patchCord5(mixer1, dac1);
//AudioControlSGTL5000     sgtl5000_1;     //xy=166,218
// GUItool: end automatically generated code

#include <Arduino.h>
#include <shiftRegister.h>
#include <StringDetection.h>

const float stringFrequencies[6] = {82.41,110.0,146.83,196,246.94,329.63};

// timer for shift register
IntervalTimer shiftTimer;
// shift register controller
// Teensy 3.6
// ShiftRegister shiftRegister1(29, 30, 31, 32);
// Teensy 3.2
ShiftRegister shiftRegister1(9, 10, 11, 12);

float frequencyEstimate;

void timerCallback(){
  shiftRegister1.shiftShiftRegister();
}

void setString(int idString){
  float fSet = stringFrequencies[idString];
  float Q = 0.7;
  shiftTimer.end();
  filter1.frequency(fSet);
  filter1.resonance(Q);
  shiftTimer.priority(0);
  shiftTimer.begin(timerCallback, (long)1/fSet/16*1000000);
}

int main(void) {
  // initialize shift register
  // Teensy 3.6
  ShiftRegister shiftRegister1(29, 30, 31, 32);
  // Teensy 3.2
  //ShiftRegister shiftRegister1(9, 10, 11, 12);
  // start serial connection
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // setup for Audio sketch
  AudioMemory(30); // from duff2013/AudioTuner
  mixer1.gain(0, 2.0);
  notefreq1.begin(0.3);
  float squareWave[65] = {
    -1., -1., -1., -1., -1., -1., -1., -1.,
    -1., -1., -1., -1., -1., -1., -1., -1.,
    -1., -1., -1., -1., -1., -1., -1., -1.,
    -1., -1., -1., -1., -1., -1., -1., -1.,
    0.,
    1., 1., 1., 1., 1., 1., 1., 1.,
    1., 1., 1., 1., 1., 1., 1., 1.,
    1., 1., 1., 1., 1., 1., 1., 1.,
    1., 1., 1., 1., 1., 1., 1., 1.
  };
  waveshape1.shape(squareWave, 65);
  dac1.analogReference(EXTERNAL);
  // setup shift registers
  shiftRegister1.initShiftRegister();
  // setup initial string
  int idString = 4;
  setString(idString);
  // loop
  while (true){
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    if (notefreq1.available()){
      frequencyEstimate = notefreq1.read();
      idString = estimateString(frequencyEstimate);
      if (stringHasChanged()){
        // change value for shiftTimer
        setString(idString);
        Serial.println(idString);
      }
    }
    else {
      //Serial.println("Nothing detected...");
    }
  }
}
