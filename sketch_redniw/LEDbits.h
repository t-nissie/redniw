/* LEDbits.h */
#ifndef LEDbits_h
#define LEDbits_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <limits.h>   // for UINT_MAX

class LEDbits
{
 public:
  LEDbits() : _bits(0), _length(0), _max(0), _analog_or_digital(0) {
  }

  LEDbits& init(const int len, const int p[], const int ad=5, const unsigned int val=UINT_MAX) {
    _length = len;
    _max = (1<<(_length+1)) - 1;   // _max will be 63, when len=6.
    _analog_or_digital = ad;
    for (int i=0; i<_length; ++i) {
      _pins[i] = p[i];
      if (_analog_or_digital==0) pinMode(_pins[i], OUTPUT);
    }          // We do not need initialization for analog output mode pins.
    set_bits(val);
    return *this;
  }

  LEDbits& set_bits(const unsigned int val) {
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
