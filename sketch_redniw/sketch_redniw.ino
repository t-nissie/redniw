/* -*-C++-*- sketch_redniw.ino */
#include "LEDbits.h"
#include <Bounce2.h> //Add Bounce2 through the library manager (Ctrl+Shift+I)
Bounce       n_wind_bouncer = Bounce();
const int    N_WIND_SW_PIN  = 1;
LEDbits      n_wind_LED     = LEDbits();
const int    N_WIND_LENGTH  = 6;
const int    N_WIND_PINS[N_WIND_LENGTH]  = {3,5,6,9,10,11};

Bounce       thickness_bouncer = Bounce();
const int    THICKNESS_SW_PIN  = 12;
LEDbits      thickness_LED     = LEDbits();
const int    THICKNESS_LENGTH  = 2;
const int    THICKNESS_PINS[THICKNESS_LENGTH]  = {13,8};

Bounce       spool_bouncer = Bounce();
const int    SPOOL_SW_PIN  = 0;
LEDbits      spool_LED     = LEDbits();
const int    SPOOL_LENGTH  = 3;
const int    SPOOL_PINS[SPOOL_LENGTH]  = {17,18,19};

void setup()
{
  pinMode(N_WIND_SW_PIN, INPUT_PULLUP);
  n_wind_bouncer.attach(N_WIND_SW_PIN);
  n_wind_bouncer.interval(5);
  n_wind_LED.init(N_WIND_LENGTH, N_WIND_PINS);

  pinMode(THICKNESS_SW_PIN, INPUT_PULLUP);
  thickness_bouncer.attach(THICKNESS_SW_PIN);
  thickness_bouncer.interval(5);
  thickness_LED.init(THICKNESS_LENGTH, THICKNESS_PINS, 0);

  pinMode(SPOOL_SW_PIN, INPUT_PULLUP);
  spool_bouncer.attach(SPOOL_SW_PIN);
  spool_bouncer.interval(5);
  spool_LED.init(SPOOL_LENGTH, SPOOL_PINS, 0);
}

void loop()
{
  if (n_wind_bouncer.update() && n_wind_bouncer.read()==HIGH) {
    n_wind_LED.up();
  }
  if (thickness_bouncer.update() && thickness_bouncer.read()==HIGH) {
    thickness_LED.up();
  }
  if (spool_bouncer.update() && spool_bouncer.read()==HIGH) {
    spool_LED.up();
  }
}
