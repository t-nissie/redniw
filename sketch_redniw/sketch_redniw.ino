/* -*-C++-*- sketch_redniw.ino */
#include "LEDbits.h"
#include <Bounce2.h> //Add Bounce2 through the library manager (Ctrl+Shift+I)
Bounce       n_wind_bouncer = Bounce();
const int    N_WIND_SW_PIN  = 1;
unsigned int n_wind_bits    = 0;
const int    N_WIND_LEN     = 6;
const int    N_WIND_ANALOG  = 5;
const int    N_WIND_PINS[]  = {3,5,6,9,10,11};

void setup()
{
  pinMode(N_WIND_SW_PIN, INPUT_PULLUP);
  n_wind_bouncer.attach(N_WIND_SW_PIN);
  n_wind_bouncer.interval(5);
  n_wind_bits = up_down_led(n_wind_bits,
                            false,
                            N_WIND_LEN,
                            N_WIND_ANALOG,
                            N_WIND_PINS);   // turn on all LEDs
}

void loop()
{
  if (n_wind_bouncer.update() && n_wind_bouncer.read()==HIGH) {
    n_wind_bits = up_down_led(n_wind_bits,
                              true,
                              N_WIND_LEN,
                              N_WIND_ANALOG,
                              N_WIND_PINS);   // turn on all LEDs
  }
}
