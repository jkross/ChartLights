#include <Arduino.h>
#include "debug.h"
#include "ledPattern.h"
#include "lightList.h"


ledPattern::ledPattern(uint8_t pin, int seqIndex, snapshotTime *snapshot)
{
	_state = 0;
	_pin = pin;
	_seqIndex = seqIndex;
	gTime = snapshot;
}

bool
ledPattern::init(ticks_t now, ledDriver* driver)
{
	_driver = driver;
	ticks = now;
	return invoke(now, 0);
}

#define MULTIPLIER 1
#define FUZZ	   10
uint16_t
ledPattern::sequenceLength(int state, int fuzz) {
	uint16_t duration = uniqueLightSeq[_seqIndex].sequence[state];
	duration += fuzz ? FUZZ : 0;
	return duration;
}

bool
ledPattern::invoke(ticks_t now, int fuzz)
{
	do {
		int bitval = (_state & 0x1) ^ 0x1;		// alternate between on/off
		_driver->set(_pin, bitval);	// start off setting the bit
		ticks = ticks + sequenceLength(_state, fuzz);
		_state = (_state + 1) % PATTERN_SEQ_LEN;
		//SPAB("now ", now); SPAB(" pin: ", _ppattern->pin); SPAB(" val: ", bitval); SPAB(" ticks ", ticks); SPLN();
	} while (timer::expired(now, ticks));
	//  SPLN("lpInvoke end");
	return true;
}

void ledPattern::loadPatterns(scheduler* sched, ledDriver* driver, snapshotTime* snapshot)
{
	ticks_t now = snapshot->get();
	for (int i = 0; i < 38/*NUM_LIGHT_LIST*/; i++) {
		ledPattern *light = new ledPattern(i, lightList[i], snapshot);
		if (0 == i) { SPAB("szLed ", (sizeof(ledPattern), DEC)); }
		if (light->init(now, driver)) {
			sched->queueTimer(light);
		}
	}
}
