// Cascaded TLC5916 drivers

#include <RTClib.h>
#include "perfStat.h"
//#include "morse.h"
#include "timer.h"	
#include "scheduler.h"
#include "ledDriver.h"
#include "snapshotTime.h"
#include "ledTimer.h"
#include "debug.h"

scheduler *myScheduler;
ledDriver *myDriver;
snapshotTime *snap;

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

  myScheduler = new scheduler();
  myDriver = new ledDriver();
  snap = new snapshotTime();
  snap->set(millis());

  ledTimer::loadPatterns(myScheduler, myDriver, snap);
  myDriver->setPwm(PWM_PCT);
  myDriver->writeData();
}

void loop()
{
  snap->set(millis());
  ticks_t nextDelay = myScheduler->dispatch(snap->get());
  myDriver->writeData();
  delay(nextDelay);
}


