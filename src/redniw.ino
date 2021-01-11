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

// Add Bounce2 through the library manager (Ctrl+Shift+I)
#include <Bounce2.h>
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
