# Strobe Tuner based on Teensy 3.6

In this project I built a **guitar tuner** similar to a strobe tuner. A strobe tuner uses a strobe triggered by the positive or negative half-wave of an musicla instrument signal. The strobe is used to illuminate a disc with rotates at the desired tuning frequency. The disc has a regular pattern on it which seems to be standing still if the instrument is in tune. If the instrument is out of tune, the pattern seems to rotate clockwise or counter-clockwise depending on the frequency difference between instrument and reference. Strobe tuners allow for a much higher accuracy than tuners based on autocorrelation etc.

## Hardware
Instead of a rotating disc **two SN74HC595 shift registers** are used as a ring buffer shifting a single one through its sixteen bits. The one is shifted through the buffer with the desired tuning frequency. The outputs of the shift registers are connected to 16 LED soldered in one row (the may also be soldered in a circular pattern).
To control the shift registers and as a frequency reference a **Teensy 3.6** development board is used. The Teensy board is also used for detection of the plugged string. For this purpose an [implementation of the YIN algorithm](https://github.com/duff2013/AudioTuner) for Teensy Audio Library is used.
For the input of the guitar signal a home-made board is used. It contains a **non-inverting amplifier** with gain 2 and offset of 0.6 V. The amplifier uses a **LM358 op-amp**.

## Software
The software for the Teensy 3.6 development board was written using **PlatformIO**.

## Wiring Diagram

```  
10:SRCLR, 11:SRCLK, 12:RCLK, 13:OE, 14:SER, L1, .., LE: LEDS  
G: Ground (Teensy)  

 G  L7 L6 L5 L4 L3 L2 L1  
 |  |  |  |  |  |  |  |  
 08 07 06 05 04 03 02 01  
|-----------------------| |-----------------------|  
|    sn74hc595 #1       | |    sn74hc595 #2       |  
|-----------------------| |-----------------------|  
 09 10 11 12 13 14 15 16   09 10 11 12 13 14 15 16  
    |  |  |  |  |  |  |    |  |  |  |  |  |  |  
    |  |  |  |  |  L1 3V   | [same as #1] |  L9  
    |  |  |  |  |          |              |  
    |  |  |  |  |          |              ----Pin 09 of sn74hc595 \#1  
    29 31 32 DA 30         ----Pin 14 of sn74hc595 #1  
|-----------------------|  
|    Teensy 3.6         |  DA = DAC0  
|-----------------------|  
       A2  
 3V G  16  
 |  |  |  
 |  |  |  
 |  |  |  
 |  |  |  
 +  G  ->  
|--------------------------|  
| Guitar input circuit     | -> = Signal  
|--------------------------|  
```
