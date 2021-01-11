/* LEDbits.h */
#ifndef LEDbits_h
#define LEDbits_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

unsigned int up_down_led(unsigned int bits,
                         const boolean up_or_down,
                         const int len,
                         const int analog_or_digital, /* 0: digital, 1-255: lower value for */
                         const int pins[])
{
  unsigned int Max = (1<<(len+1)) - 1;   // Max will be 63, when len=6.
  if (up_or_down) {
    if (bits>=Max) bits=0; else bits++;  // count up
  } else {
    if (bits==0) bits=Max; else bits--;  // or count down
  }
  unsigned int tester=1;
  for (int i=0; i<len; ++i) {
    if (bits & tester) {
      if (analog_or_digital) analogWrite(pins[i],255);               else digitalWrite(pins[i],HIGH);
    } else {
      if (analog_or_digital) analogWrite(pins[i],analog_or_digital); else digitalWrite(pins[i],LOW);
    }
    tester = tester << 1;
  }
  return bits;
}

#endif
