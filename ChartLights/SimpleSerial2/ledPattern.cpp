#include <Arduino.h>
#include "ledPattern.h"
#include "lightList.h"

ledPattern::ledPattern(struct pattern* ppattern, snapshotTime *snapshot)
{
	_state = 0;
	_ppattern = ppattern;
	gTime = snapshot;
}

bool
ledPattern::init(ticks_t now, ledDriver* driver)
{
	_driver = driver;
	ticks = now;
	return invoke(now);
}

bool
ledPattern::invoke(ticks_t now)
{
	do {
		int bitval = (_state & 0x1) ^ 0x1;		// alternate between on/off
		_driver->set(_ppattern->pin, bitval);	// start off setting the bit
		ticks = ticks + _ppattern->sequence[_state];
    _state = (_state + 1) % PATTERN_SEQ_LEN;
#define SPAB(A,B) Serial.print(A); Serial.print(B)
#define SPL Serial.println
  SPAB("now ", now); SPAB(" pin: ", _ppattern->pin); SPAB(" val: ", bitval); SPAB(" ticks ", ticks); SPL();
	} while (timer::expired(now, ticks));
//  SPL("lpInvoke end");
	return true;
}

void ledPattern::loadPatterns(scheduler* sched, ledDriver* driver, snapshotTime* snapshot)
{
	ticks_t now = snapshot->get();
	for (int i = 0; i < 2; i++) {
		ledPattern *light = new ledPattern(&lightList[i], snapshot);
		if (light->init(now, driver)) {
			sched->schedule(light);
		}
	}
}
