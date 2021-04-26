/* -*-C++-*- sketch_redniw.ino */
#include <Bounce2.h> //Add Bounce2 through the library manager (Ctrl+Shift+I)
const int PP_SW_PIN  =  9;
Bounce    pp_bouncer = Bounce();   // play and pause

const int NOT_ENABLE =  8;
const int GUIDE_END  = 10;

const int    GUIDE_STEP =  3;
const int    GUIDE_DIR  =  6;
const int    GUIDE_MODE = 32;
const double GUIDE_1RND  = 40.0; // mm/round

const int    SPOOL_STEP =  2;
const int    SPOOL_DIR  =  5;
const int    SPOOL_MODE = 32;

const double theta_step = 1.8;
const int  n_123  =      (123.0/GUIDE_1RND) * GUIDE_MODE * 360.0 / theta_step;
const long n2_119  = 2 * (119.0/GUIDE_1RND) * GUIDE_MODE * 360.0 / theta_step;

void setup()
{
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
  for (int i = 0; i < n_123; i++) {
    digitalWrite(GUIDE_STEP,0);
    delayMicroseconds(125);
    digitalWrite(GUIDE_STEP,1);
    delayMicroseconds(125);
  }

  digitalWrite(NOT_ENABLE,1); // disable stepper drivers
  do {
  } while (!(pp_bouncer.update() && pp_bouncer.read()==HIGH));

  digitalWrite(NOT_ENABLE,0); // eable stepper drivers
  digitalWrite(SPOOL_DIR,0);
  int dir = 0;
  int sig = 0;
  long acm = 0;
  digitalWrite(GUIDE_DIR,0);
  while(1) {
    if (++acm>n2_119) {
      acm = 1;
      digitalWrite(GUIDE_DIR,dir^=1);   // Set Dir
    }
    digitalWrite(SPOOL_STEP, 0);
    delayMicroseconds(6);
    digitalWrite(SPOOL_STEP, 1);
    delayMicroseconds(6);
    digitalWrite(GUIDE_STEP, sig^=1);
  }

  digitalWrite(NOT_ENABLE,1); // disenable stepper drivers
}

void loop()
{
}
