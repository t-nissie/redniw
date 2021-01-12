/* LEDbits.h */
#ifndef LEDbits_h
#define LEDbits_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class LEDbits
{
 public:
  LEDbits() : _bits(0), _length(0), _max(0), _analog_or_digital(0) {
  }

  LEDbits& set_analog_or_digital(const int ad) {
    _analog_or_digital = ad;
    return *this;
  }

  LEDbits& set_length(const int len) {
    _length = len;
    _max = (1<<(len+1)) - 1;   // _max will be 63, when len=6.
    return *this;
  }

  LEDbits& set_pins(const int p[]) {
    for (int i=0; i<_length; ++i) _pins[i] = p[i];
    return *this;
  }

  LEDbits& init() {
    _bits = _max;
    show();
    return *this;
  }

  LEDbits& set_bits(unsigned int val) {
    _bits = _max & val;
    show();
    return *this;
  }

  unsigned int get_bits() {
    return _bits;
  }

  LEDbits& up() {
    if (_bits>=_max) _bits=0; else _bits++;
    show();
    return *this;
  }

  LEDbits& down() {
    if (_bits==0) _bits=_max; else _bits--;
    show();
    return *this;
  }

 private:
  int _bits;
  int _length;
  unsigned int _max;
  int _analog_or_digital; //0: digital, 1-255: lower value for analogWrite()
  int _pins[32];

  void show() {
    unsigned int tester=1;
    for (int i=0; i<_length; ++i) {
      if (_bits & tester) {
        if (_analog_or_digital) analogWrite(_pins[i],255);                else digitalWrite(_pins[i],HIGH);
      } else {
        if (_analog_or_digital) analogWrite(_pins[i],_analog_or_digital); else digitalWrite(_pins[i],LOW);
      }
      tester = tester << 1;
    }
  }
};

#endif
