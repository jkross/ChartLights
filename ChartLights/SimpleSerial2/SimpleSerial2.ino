// Cascaded TLC5916 drivers
#define RUN_TESTS

#include <RTClib.h>
#include "perfStat.h"
#include "morse.h"
#include "patterns.h"
#include "timer.h"	
#include "scheduler.h"
#include "ledDriver.h"

#ifdef RUN_TESTS
#define TEST(X) X

// Timing delay for test loop
#define DELAY 1000

#define NUM_SAMPLES 2
ledDriver datArray[NUM_SAMPLES];
#else	// !RUN_TESTS
#define TEST(X)
#endif	// !RUN_TESTS

scheduler *myScheduler;

#include "rtc.h"

rtc* realTime;

void setup ()
{
  Serial.begin(57600);
  // cnt = new perfStat<100>();

  myScheduler = new scheduler();
  TEST(myScheduler->testTimers());
  realTime = new rtc();
  realTime->setup();
  TEST(realTime->test());

  for (int sample = 0; sample < NUM_SAMPLES; sample++) {
	  for (int bit = sample; bit < 40; bit += 2) {
		  datArray[sample].set(bit, 1);
	  }
  }
}



void loop()
{

  for (int j = 2; j <= 2; j += 40) {  //350mA @ 20%, 50% too high for wall plug
    //loop through all samples
    for (int sample = 0; sample < NUM_SAMPLES; sample++) {
      datArray[sample].setPwm(j);
      datArray[sample].writeData();
      delay(DELAY);
    }
  }
}


