// Cascaded TLC5916 drivers

#include <RTClib.h>
#include "perfStat.h"
#include "morse.h"
#include "timer.h"	
#include "scheduler.h"
#include "ledDriver.h"
#include "snapshotTime.h"
#include "ledTimer.h"
#include "debug.h"

scheduler *myScheduler;
ledDriver *myDriver;
snapshotTime *snapp;

#if 0
#include "rtc.h"
rtc* realTime;
#endif

void setup ()
{
  Serial.begin(115200);

 #if 0
  realTime = new rtc();
  realTime->setup();
#endif

#if 0
  if (MorseMap[0].letter != 'A') {
	  SPLN("BadMorseMap");
  }
#endif

  myScheduler = new scheduler();
  myDriver = new ledDriver();
  snapp = new snapshotTime();
  snapp->set(millis());

  ledTimer::loadPatterns(myScheduler, myDriver, snapp);
  myDriver->setPwm(PWM_PCT);
  myDriver->writeData();
}

void loop()
{
	snapp->set(millis());
	do {
		myScheduler->dispatch(snapp->get());
		myDriver->writeData();
		snapp->set(millis());
	} while (myScheduler->expired(snapp->get()));  // while there is any expired timer
	delay(myScheduler->remaining(snapp->get()));
}


