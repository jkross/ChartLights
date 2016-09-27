// Cascaded TLC5916 drivers


#include "perfStat.h"
#include "morse.h"


const int latchPin = 12;  // connected to LE  of TLC5916
const int clockPin = 8;   // connected to CLK of TLC5916
const int dataPin = 11;   // connected to SDI of TLC5916
const int oePin = 3;      // connected to ~OE of TLC5916

// Since ~OE is active low we calcuate our PWM percent as the inverse %
#define PWM_PCT_ACT_LOW(_PCT) ((int)255*(1-(_PCT/100.0)))
#define PWM_PCT 10

#define NUM_BANKS 5       // number of drivers
#define LEDS_PER_BANK 8
byte datArray[][NUM_BANKS] = {{0x0, 0x0, 0x0, 0x0, 0x0},
  {0xaa, 0xaa, 0xaa, 0xaa, 0xaa},
  {0x55, 0x55, 0x55, 0x55, 0x55},
};
#define NUM_SAMPLES (sizeof(datArray)/sizeof(datArray[0]))

// Timing delay for test loop
#define DELAY 1000


perfStat<100> *cnt;

//#include <iostream>
using namespace std;
#include <pnew.cpp>
#include <iterator>
#include <queue>



typedef unsigned long ticks_t;
const ticks_t HalfWrap = ~((ticks_t)0) >> 1;

class globalTime {
private:
  ticks_t _now;

public:
  globalTime() {
    set(0);
  }

  void set(ticks_t now) {
    _now = now;
  }

  ticks_t get() {
    return _now;
  }
};

static globalTime gTime;

class timer {
public:

  ticks_t ticks;

  void invoke(ticks_t now)
  {
    // cout << "callback: " << ticks << endl;
    Serial.print("callback: ");
    Serial.print(ticks, HEX);
    Serial.println();
    //Serial.println(ticks, HEX);
  }

  ticks_t remaining(ticks_t now)
  {
    return (ticks - now);
  }

  bool operator <(const timer& other) const
  {
    return (other.ticks - gTime.get()) < (ticks - gTime.get());
  }

  timer(int i)
  {
    ticks = i;
  }

  timer() {
    ticks = 0;
  }
};

class timers {
  priority_queue<timer> timerList;

public:
  void schedule(timer t)
  {
    timerList.push(t);
  }

  bool empty()
  {
    return timerList.empty();
  }

  bool expired(ticks_t now, timer t) 
  {
    ticks_t remaining = t.remaining(now);
    bool ret = (remaining -1) > HalfWrap;
    return ret;
  }

  void dispatch(ticks_t now)
  {
    do {
      timer top = timerList.top();
      if (!expired(now, top))
        break;
      timerList.pop();
      top.invoke(now);
    } while (!timerList.empty());
  }

  //void dumpDestructive()
  //{
  //  while (!timerList.empty()) {
  //    unsigned long long i = timerList.top().ticks;
  //    timerList.pop();
  //    cout << i << endl;
  //  }
  //}
};

void doTimers() {
    
  timers timers;
  gTime.set(((ticks_t)2));
  timers.schedule(3);
  timers.schedule(10); 
  timers.schedule(3); 
  timers.schedule(1); 
  timers.schedule(-1);

  ticks_t now = gTime.get();
  while (!timers.empty())
  {
    // cout << "now: " << now << endl;
    Serial.print("now: ");
    Serial.print(now, HEX);
    Serial.println();
    timers.dispatch(now);
    gTime.set(now++);
  }
}

void setup ()
{
  //set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  Serial.begin(57600);
  digitalWrite(latchPin, LOW);
  analogWrite(oePin, PWM_PCT_ACT_LOW(PWM_PCT));
  cnt = new perfStat<100>();

  doTimers();

}

void loop()
{
  for (int j = 10; j <= 100; j += 90) {
    analogWrite(oePin, PWM_PCT_ACT_LOW(j));
    //loop through all samples
    for (int sample = 0; sample < NUM_SAMPLES; sample++)
    {
      {
        cnt->init();
        do {  // 232us avg w/ 2, 562us w/ 5
          cnt->start();
          //digitalWrite(oePin,HIGH); // disable LEDs and don't let driver switch to non-standard mode
          for (int bank = NUM_BANKS - 1; bank >= 0; bank--)
          {
            //dPrint(sample, bank);
            shiftOut(dataPin, clockPin, MSBFIRST, datArray[sample][bank]);
          }
          // toggle latch pin to latch data from shift register to output drivers
          digitalWrite(latchPin, HIGH);
          digitalWrite(latchPin, LOW);
          // set ~OE according to PWM percentage
          //analogWrite(oePin, PWM_PCT_ACT_LOW(PWM_PCT));
        } while (!(cnt->stop()));
        cnt->compute();
      }
      delay(DELAY);
    }
  }
}


