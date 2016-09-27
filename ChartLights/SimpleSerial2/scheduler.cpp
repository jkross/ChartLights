#include <Arduino.h>
#include "scheduler.h"
#include <pnew.cpp>

void 
scheduler::schedule(timer t)
{
	timerList.push(t);
}

bool 
scheduler::empty()
{
	return timerList.empty();
}

bool 
scheduler::expired(ticks_t now, timer t)
{
	ticks_t remaining = t.remaining(now);
	bool ret = (remaining - 1) > HalfWrap;
	return ret;
}

void 
scheduler::dispatch(ticks_t now)
{
	do {
		timer top = timerList.top();
		if (!expired(now, top))
			break;
		timerList.pop();
		top.invoke(now);
	} while (!timerList.empty());
}

//void 
//scheduler::dumpDestructive()
//{
//  while (!timerList.empty()) {
//    unsigned long long i = timerList.top().ticks;
//    timerList.pop();
//    cout << i << endl;
//  }
//}

#include "globalTime.h"
globalTime gTime;

void 
scheduler::testTimers() {

	gTime.set(((ticks_t)2));
	schedule(3);
	schedule(10);
	schedule(3);
	schedule(1);
	schedule(-1);

	ticks_t now = gTime.get();
	while (!empty())
	{
		// cout << "now: " << now << endl;
		Serial.print("now: ");
		Serial.print(now, HEX);
		Serial.println();
		dispatch(now);
		gTime.set(now++);
	}
}
