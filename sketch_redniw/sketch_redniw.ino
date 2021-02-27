/* -*-C++-*- sketch_redniw.ino */
#include "LEDbits.h"
#include <Bounce2.h> //Add Bounce2 through the library manager (Ctrl+Shift+I)

const int N_WIND_SW_PIN = 1;
LEDbits   n_wind_LED    = LEDbits();   // It will be used in both setup() and loop().
const int N_WIND_LENGTH = 6;
const int N_WIND_PINS[N_WIND_LENGTH] = {3,5,6,9,10,11};

const int SPOOL_SW_PIN = 0;
LEDbits   spool_LED = LEDbits();
const int SPOOL_LENGTH = 3;
const int SPOOL_PINS[SPOOL_LENGTH] = {17,18,19};

const int PP_SW_PIN  = 14;
Bounce    pp_bouncer = Bounce();   // play and pause

const int NOT_ENABLE = 13;
const int GUIDE_END  = 15;

const int    GUIDE_STEP =  2;
const int    GUIDE_DIR  =  4;
const int    GUIDE_MODE = 32;
const double GUIDE_1RND  = 40.0; // mm/round

const int    SPOOL_STEP = 16;
const int    SPOOL_DIR  =  7;
const int    SPOOL_MODE =  4;

const double theta_step = 1.8;
const int n_127 =          (127.0/GUIDE_1RND) * GUIDE_MODE * 360.0 / theta_step;
const int n_102 = 16320; //(102.0/GUIDE_1RND) * GUIDE_MODE * 360.0 / theta_step;

void setup()
{
  pinMode(  N_WIND_SW_PIN, INPUT_PULLUP);
  Bounce    n_wind_bouncer = Bounce();
  n_wind_bouncer.attach(N_WIND_SW_PIN);
  n_wind_bouncer.interval(5);
  n_wind_LED.init(N_WIND_LENGTH, N_WIND_PINS);

  pinMode(  SPOOL_SW_PIN, INPUT_PULLUP);
  Bounce    spool_bouncer = Bounce();
  spool_bouncer.attach(SPOOL_SW_PIN);
  spool_bouncer.interval(5);
  spool_LED.init(SPOOL_LENGTH, SPOOL_PINS, 0);

  pinMode(PP_SW_PIN, INPUT_PULLUP);
  pp_bouncer.attach(PP_SW_PIN);
  pp_bouncer.interval(5);

  pinMode(NOT_ENABLE,OUTPUT);
  pinMode(GUIDE_STEP,OUTPUT);
  pinMode(GUIDE_DIR, OUTPUT);
  pinMode(GUIDE_END,  INPUT_PULLUP); // endstop
  pinMode(SPOOL_STEP,OUTPUT);
  pinMode(SPOOL_DIR, OUTPUT);

  digitalWrite(NOT_ENABLE,0); // enable stepper drivers
  digitalWrite(GUIDE_DIR,0);   // to the endstop direction
  do {
        digitalWrite(GUIDE_STEP,0);
        delayMicroseconds(250);
        digitalWrite(GUIDE_STEP,1);
        delayMicroseconds(250);
  } while (digitalRead(GUIDE_END));

  delay(1000); // Wait 1 seconds
  digitalWrite(GUIDE_DIR,1); // Set Dir
  for (int i = 0; i < n_127; i++) {
    for (int k = 0; k < 2; k++) {
      digitalWrite(GUIDE_STEP,k);
      delayMicroseconds(125);
    }
  }

  digitalWrite(NOT_ENABLE,1); // disable stepper drivers
  n_wind_LED.set_bits(0);
  spool_LED.set_bits(0);

  do {
    if (   n_wind_bouncer.update() &&    n_wind_bouncer.read()==HIGH)    n_wind_LED.up();
    if (    spool_bouncer.update() &&     spool_bouncer.read()==HIGH)     spool_LED.up();
  } while (  !(pp_bouncer.update() &&        pp_bouncer.read()==HIGH)  );

  digitalWrite(NOT_ENABLE,0); // eable stepper drivers
  digitalWrite(SPOOL_DIR,0);
  do {
    for (int j=0; j<2; j++) {
      digitalWrite(GUIDE_DIR,j);   // Set Dir
      for (int i = 0; i < n_102; i++) {
        if ((i%4)==0) digitalWrite(SPOOL_STEP,0);
        if ((i%4)==2) digitalWrite(SPOOL_STEP,1);
        for (int k = 0; k < 2; k++) {
          digitalWrite(GUIDE_STEP,k);
          delayMicroseconds(20);
        }
      }
    }
  } while (n_wind_LED.down().get_bits());

  digitalWrite(NOT_ENABLE,1); // disenable stepper drivers
}

void loop()
{
  spool_LED.set_bits(0);
  spool_LED.set_bits(1);     delay(100);
  spool_LED.set_bits(2);     delay(100);
  spool_LED.set_bits(4);     delay(100); spool_LED.set_bits(0);
  n_wind_LED.set_bits( 1);   delay(100);
  n_wind_LED.set_bits( 2);   delay(100);
  n_wind_LED.set_bits( 4);   delay(100);
  n_wind_LED.set_bits( 8);   delay(100);
  n_wind_LED.set_bits(16);   delay(100);
  n_wind_LED.set_bits(32);   delay(100); n_wind_LED.set_bits(0);
}
