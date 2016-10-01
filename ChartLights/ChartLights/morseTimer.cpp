#include <Arduino.h>
#include "debug.h"
#include "morseTimer.h"
#include "morseLightList.h"


morseTimer::morseTimer(morseLightDesc *mldp, snapshotTime *snapshotp)
	: timer(0, snapshotp)
{
	_state_char = 0;
	_state = 0;
	_mldp = mldp;
}

bool
morseTimer::init(ticks_t start, ledDriver* driver)
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
morseTimer::stepDuration(int state, int fuzz) {
	uint16_t duration = 0; // TODO
	duration += fuzz ? FUZZ : 0;
	return duration;
}

bool
morseTimer::invoke(ticks_t now, int fuzz)
{
	do {
		int bitval = (_state & 0x1) ^ 0x1;		// alternate between on/off
		_driver->set(_mldp->pin, bitval);				// start off setting the bit
		ticks = ticks + stepDuration(_state, fuzz);
		_state = 0; // TODO (_state + 1) % PATTERN_SEQ_LEN;
		//SPAB("now ", now); SPAB(" pin: ", _ppattern->pin); SPAB(" val: ", bitval); SPAB(" ticks ", ticks); SPLN();
	} while (expired(now));						// catch up if we need to
												//  SPLN("lpInvoke end");
	return true;								// schedule again
}

void
morseTimer::loadPatterns(scheduler* schedp, ledDriver *driverp, snapshotTime* snapshotp)
{
	lfsr *lfsrp = new lfsr();
	ticks_t now = snapshotp->get();
	for (int i = 0; i < NUM_MORSE_LIGHT_LIST; i++) {
		morseTimer *light = new morseTimer(&morseLightList[i], snapshotp);
		ticks_t startOffset = (lfsrp->next() % START_BUCKETS) * START_FUZZ;
		if (light->init(now + startOffset, driverp)) {
			schedp->queueTimer(light);
		}
	}
}
