// Cascaded TLC5916 drivers

#include "perfStat.h"
#include "morse.h"
#include "patterns.h"
#include "timer.h"	

// Timing delay for test loop
#define DELAY 1000

// perfStat<100> *cnt;

//#include <iostream>

#include "globalTime.h"
#include "scheduler.h"

globalTime gTime;



void doTimers() {

  scheduler scheduler;
  gTime.set(((ticks_t)2));
  scheduler.schedule(3);
  scheduler.schedule(10);
  scheduler.schedule(3);
  scheduler.schedule(1);
  scheduler.schedule(-1);

  ticks_t now = gTime.get();
  while (!scheduler.empty())
  {
    // cout << "now: " << now << endl;
    Serial.print("now: ");
    Serial.print(now, HEX);
    Serial.println();
    scheduler.dispatch(now);
    gTime.set(now++);
  }
}

void setup ()
{
  //set pins to output
  Serial.begin(57600);
  // cnt = new perfStat<100>();

  doTimers();

}

class ledDriver {
  private:
    static const int NUM_BANKS = 5;
    const int LEDS_PER_BANK = 8;
    const int latchPin = 12;  // connected to LE  of TLC5916
    const int clockPin = 8;   // connected to CLK of TLC5916
    const int dataPin = 11;   // connected to SDI of TLC5916
    const int oePin = 3;      // connected to ~OE of TLC5916

    // Since ~OE is active low we calcuate our PWM percent as the inverse %
#define PWM_PCT_ACT_LOW(_PCT) ((int)255*(1-(_PCT/100.0)))
#define PWM_PCT 10

    byte _data[NUM_BANKS];
    int  _pwmPct;
  public:
    ledDriver() {
      for (int i = 0; i < NUM_BANKS; i++) {
        _data[i] = 0;
      }
      _pwmPct = PWM_PCT;
      pinMode(latchPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(dataPin, OUTPUT);
      pinMode(oePin, OUTPUT);
      digitalWrite(latchPin, LOW);
      analogWrite(oePin, PWM_PCT_ACT_LOW(PWM_PCT));
    }

    void setPwm(int pwmPct) {
      // value will be used next writeData() call
      _pwmPct = pwmPct;
    }

    void writeData() {
      // disable LEDs and don't let driver switch to non-standard mode
      digitalWrite(oePin, HIGH);
      for (int bank = NUM_BANKS - 1; bank >= 0; bank--)
      {
        shiftOut(dataPin, clockPin, MSBFIRST, _data[bank]);
      }
      // toggle latch pin to latch data from shift register to output drivers
      digitalWrite(latchPin, HIGH);
      digitalWrite(latchPin, LOW);
      // set ~OE according to PWM percentage
      analogWrite(oePin, PWM_PCT_ACT_LOW(_pwmPct));
    }

    void set(int i, bool val) {
      int bank = i / LEDS_PER_BANK;
      int bit  = i % LEDS_PER_BANK;
      if (val) {
        _data[bank] |= 1 << bit;
      } else {
        _data[bank] &= ~(1 << bit);
      }
    }
};

#define NUM_SAMPLES 2
ledDriver datArray[NUM_SAMPLES];

void loop()
{
  for (int sample = 0; sample < NUM_SAMPLES; sample++) {
    for (int bit = sample; bit < 40; bit += 2) {
      datArray[sample].set(bit, 1);
    }
  }
  for (int j = 20; j <= 20; j += 40) {  //350mA @ 20%, 50% too high for wall plug
    //loop through all samples
    for (int sample = 0; sample < NUM_SAMPLES; sample++) {
      datArray[sample].setPwm(j);
      datArray[sample].writeData();
      delay(DELAY);
    }
  }
}


