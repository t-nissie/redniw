/* -*-C++-*- sketch_redniw.ino */
#include "LEDbits.h"
#include <Bounce2.h> //Add Bounce2 through the library manager (Ctrl+Shift+I)
Bounce       n_wind_bouncer = Bounce();
const int    N_WIND_SW_PIN  = 1;
LEDbits      n_wind_LED     = LEDbits();
const int    N_WIND_LENGTH  = 6;
const int    N_WIND_PINS[N_WIND_LENGTH]  = {3,5,6,9,10,11};
void setup()
{
  pinMode(N_WIND_SW_PIN, INPUT_PULLUP);
  n_wind_bouncer.attach(N_WIND_SW_PIN);
  n_wind_bouncer.interval(5);
  n_wind_LED.init(N_WIND_LENGTH, N_WIND_PINS);
}

void loop()
{
  if (n_wind_bouncer.update() && n_wind_bouncer.read()==HIGH) {
    n_wind_LED.up();
  }
}
