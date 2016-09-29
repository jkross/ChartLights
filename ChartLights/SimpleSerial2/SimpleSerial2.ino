// Cascaded TLC5916 drivers

#include <RTClib.h>
#include "perfStat.h"
//#include "morse.h"
#include "timer.h"	
#include "scheduler.h"
#include "ledDriver.h"
#include "snapshotTime.h"
#include "ledPattern.h"
#include "debug.h"

#ifdef RUN_TESTS2
// Timing delay for test loop
#define DELAY 1000

#define NUM_SAMPLES 2
ledDriver* datArray[NUM_SAMPLES];
#endif	// RUN_TESTS

scheduler *myScheduler;
ledDriver *myDriver;
snapshotTime *snap;

#include "rtc.h"
rtc* realTime;

void setup ()
{
  Serial.begin(115200);

#ifdef  RUN_TESTS2  
  for (int sample = 0; sample < NUM_SAMPLES; sample++) {
    datArray[sample] = new ledDriver();
    for (int bit = sample; bit < 40; bit += 2) {
      datArray[sample]->set(bit, 1);
    }
  }

  // cnt = new perfStat<100>();

  //scheduler *testScheduler = new scheduler();
  //testScheduler->testTimers();
#endif  // RUN_TESTS

  realTime = new rtc();
  realTime->setup();
  TEST((realTime->test()));

  myScheduler = new scheduler();
  myDriver = new ledDriver();
  snap = new snapshotTime();
  snap->set(millis());

  ledPattern::loadPatterns(myScheduler, myDriver, snap);
  myDriver->setPwm(PWM_PCT);
  myDriver->writeData();
}

int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void loop()
{
  snap->set(millis());
  ticks_t nextDelay = myScheduler->dispatch(snap->get());
  myDriver->writeData();
  delay(nextDelay);
}


