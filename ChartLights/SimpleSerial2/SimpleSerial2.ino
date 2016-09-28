// Cascaded TLC5916 drivers

#include <RTClib.h>
#include "perfStat.h"
#include "morse.h"
#include "timer.h"	
#include "scheduler.h"
#include "ledDriver.h"
#include "debug.h"

#ifdef RUN_TESTS
// Timing delay for test loop
#define DELAY 1000

#define NUM_SAMPLES 2
ledDriver* datArray[NUM_SAMPLES];
#endif	// !RUN_TESTS

scheduler *myScheduler;

#include "rtc.h"

rtc* realTime;

void setup ()
{
  Serial.begin(57600);

#ifdef  RUN_TESTS
  for (int sample = 0; sample < NUM_SAMPLES; sample++) {
    datArray[sample] = new ledDriver();
    for (int bit = sample; bit < 40; bit += 2) {
      datArray[sample]->set(bit, 1);
    }
  }
#endif  // RUN_TESTS
  // cnt = new perfStat<100>();

  myScheduler = new scheduler();
  TEST((myScheduler->testTimers()));
  realTime = new rtc();
  realTime->setup();
  TEST((realTime->test()));
}



void loop()
{
#ifdef RUN_TESTS
  for (int j = 5; j <= 5; j += 40) {  //350mA @ 20%, 50% too high for wall plug
    //loop through all samples
    for (int sample = 0; sample < NUM_SAMPLES; sample++) {
      datArray[sample]->setPwm(j);
      datArray[sample]->writeData();
      delay(DELAY);
    }
  }
#endif // RUN_TESTS
}


