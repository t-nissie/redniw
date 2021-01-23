/* -*-C++-*- sketch_redniw.ino */
#include "LEDbits.h"
#include <Bounce2.h> //Add Bounce2 through the library manager (Ctrl+Shift+I)

const int N_WIND_SW_PIN = 1;
LEDbits   n_wind_LED    = LEDbits();   // It will be used in both setup() and loop().
const int N_WIND_LENGTH = 6;
const int N_WIND_PINS[N_WIND_LENGTH] = {3,5,6,9,10,11};

const int THICKNESS_SW_PIN = 12;
const int THICKNESS_LENGTH = 2;
const int THICKNESS_PINS[THICKNESS_LENGTH] = {13,8};

const int SPOOL_SW_PIN = 0;
const int SPOOL_LENGTH = 3;
const int SPOOL_PINS[SPOOL_LENGTH] = {17,18,19};

const int PP_SW_PIN  = 14;
Bounce    pp_bouncer = Bounce();   // play and pause

const int GUIDE_STEP =  2;
const int GUIDE_DIR  =  4;
const int GUIDE_END  = 15;
const double theta_step = 1.8;
const int n_mode  = 8;
const int n_2_0 = 2.0 * n_mode * 360.0 / theta_step;
const int n_2_5 = 2.5 * n_mode * 360.0 / theta_step;

void setup()
{
  pinMode(  N_WIND_SW_PIN, INPUT_PULLUP);
  Bounce    n_wind_bouncer = Bounce();
  n_wind_bouncer.attach(N_WIND_SW_PIN);
  n_wind_bouncer.interval(5);
  n_wind_LED.init(N_WIND_LENGTH, N_WIND_PINS);

  pinMode(  THICKNESS_SW_PIN, INPUT_PULLUP);
  Bounce    thickness_bouncer = Bounce();
  LEDbits   thickness_LED = LEDbits();
  thickness_bouncer.attach(THICKNESS_SW_PIN);
  thickness_bouncer.interval(5);
  thickness_LED.init(THICKNESS_LENGTH, THICKNESS_PINS, 0);

  pinMode(  SPOOL_SW_PIN, INPUT_PULLUP);
  Bounce    spool_bouncer = Bounce();
  LEDbits   spool_LED     = LEDbits();
  spool_bouncer.attach(SPOOL_SW_PIN);
  spool_bouncer.interval(5);
  spool_LED.init(SPOOL_LENGTH, SPOOL_PINS, 0);

  pinMode(PP_SW_PIN, INPUT_PULLUP);
  pp_bouncer.attach(PP_SW_PIN);
  pp_bouncer.interval(5);

  pinMode(GUIDE_STEP,OUTPUT);
  pinMode(GUIDE_DIR, OUTPUT);
  pinMode(GUIDE_END,  INPUT); // endstop

  digitalWrite(GUIDE_DIR,0);   // to the endstep direction
  do {
        digitalWrite(GUIDE_STEP,0);
        delayMicroseconds(1000);
        digitalWrite(GUIDE_STEP,1);
        delayMicroseconds(1000);
  } while (digitalRead(GUIDE_END));

  delay(1000); // Wait 1 seconds
  digitalWrite(GUIDE_DIR,1); // Set Dir
  for (int i = 0; i < n_2_5; i++) {
    for (int k = 0; k < 2; k++) {
      digitalWrite(GUIDE_STEP,k);
      delayMicroseconds(500);
    }
  }

  n_wind_LED.set_bits(0);
  thickness_LED.set_bits(0);
  spool_LED.set_bits(0);

  do {
    if (   n_wind_bouncer.update() &&    n_wind_bouncer.read()==HIGH)    n_wind_LED.up();
    if (thickness_bouncer.update() && thickness_bouncer.read()==HIGH) thickness_LED.up();
    if (    spool_bouncer.update() &&     spool_bouncer.read()==HIGH)     spool_LED.up();
  } while (  !(pp_bouncer.update() &&        pp_bouncer.read()==HIGH)  );
}

void loop()
{
  n_wind_LED.down();
  delay(500);
}
