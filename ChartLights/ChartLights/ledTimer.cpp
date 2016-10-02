#include <Arduino.h>
#include "debug.h"
#include "ledTimer.h"
#include "lightList.h"


ledTimer::ledTimer(uint8_t pin, int seqIndex)
	: timer(0)
{
	_state = 0;
	_pin = pin;
	_seqIndex = seqIndex;
}

bool
ledTimer::init(ticks_t start, ledDriver* driver)
{
	_driver = driver;
	ticks = start;
	return true; // invoke(now, 0);
}

#define MULTIPLIER 1
#define FUZZ	   10
#define START_BUCKETS	16
// Spread starts over ~2s
#define START_FUZZ (2048 / START_BUCKETS)

uint16_t
ledTimer::stepDuration(int state, int fuzz) {
	uint16_t duration = uniqueLightSeq[_seqIndex].sequence[state];
	duration += fuzz ? FUZZ : 0;
	return duration;
}

bool
ledTimer::invoke(ticks_t now, int fuzz)
{
	do {
		int bitval = (_state & 0x1) ^ 0x1;		// alternate between on/off
		_driver->set(_pin, bitval);				// start off setting the bit
		ticks = ticks + stepDuration(_state, fuzz);
		_state = (_state + 1) % PATTERN_SEQ_LEN;
		//SPAB("now ", now); SPAB(" pin: ", _ppattern->pin); SPAB(" val: ", bitval); SPAB(" ticks ", ticks); SPLN();
	} while (expired(now));						// catch up if we need to
	//  SPLN("lpInvoke end");
	return true;								// schedule again
}

void 
ledTimer::loadPatterns(scheduler* schedp, ledDriver *driverp, ticks_t now)
{
	lfsr *lfsrp = new lfsr();
	for (int i = 0; i < NUM_LIGHT_LIST; i++) {
		if (lightList[i].seqId != LIGHT_DESC_NO_BLINK) {
			ledTimer *light = new ledTimer(i, lightList[i].seqId);
			ticks_t startOffset = (lfsrp->next() % START_BUCKETS) * START_FUZZ;
			if (light->init(now + startOffset, driverp)) {
				schedp->queueTimer(light);
			}
		}
	}
}
