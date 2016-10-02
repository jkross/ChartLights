#ifndef WIN32
#include <Arduino.h>
#endif // !WIN32
#include "debug.h"
#include "morseTimer.h"
#include "morseLightList.h"
#include "morse.h"
#include "lfsr.h"


morseTimer::morseTimer(morseLightDesc *mldp)
	: timer(0)
{
	_state_char = 0;
	_state = 0;
	_mldp = mldp;
}

int
morseTimer::index(char c)
{
	if (c == ' ') { return 0; }
	if (c >= '0' && c <= '9') { return 1 + c - '0'; }
	if (c >= 'A' && c <= 'Z') { return 11 + c - 'A'; }
	return 0;
}

const morseChar *
morseTimer::getCharDesc(int state_char) {
	int idx = index(_mldp->letters[state_char]);
	const morseChar *mcp = &MorseMap[idx];
#ifdef WIN32
	printf("state %2d char: %c, index: %2d\n", state_char, _mldp->letters[state_char], idx);
#endif // WIN32

	return mcp;
}


bool
morseTimer::init(ticks_t start, ledDriver* driver)
{
	_driver = driver;
	ticks = start;
	_mchar = getCharDesc(_state_char);
	return true; // invoke(now, 0);
}

int 
morseTimer::decodeStateDur() {
	int _pair = _state / 2;
	int _half = _state % 2;
	morseCharOnOff onOff = _mchar->delays[_pair];
	return _half == 0 ? onOff.on : onOff.off;
}

void
morseTimer::advanceState(void)
{
	_state++;			// next delay pattern
	if (decodeStateDur() == MORSE_END) {
		_state = 0;
		_state_char++;	// next character
		if (_mldp->letters[_state_char] == '\0') {
			_state_char = 0;	// start with first letter again
		}
		_mchar = getCharDesc(_state_char);
		//SPAB("char: ", _mldp->letters[_state_char]); SPLN();
	}
}

uint16_t
morseTimer::stepDuration(int state, int fuzz) {
	uint16_t duration = MORSE_UNIT * decodeStateDur(); 
	return duration;
}

bool
morseTimer::invoke(ticks_t now, int fuzz)
{
	do {
		int bitval = (_state & 0x1) ^ 0x1;		// alternate between on/off
		_driver->set(_mldp->pin, bitval);		// start off setting the bit
		ticks_t xdur = stepDuration(_state, fuzz);
		ticks = ticks + xdur;
		//SPAB("pin", _mldp->pin);  SPAB("bitval: ", bitval); SPAB(" dur: ", xdur); SPLN();
#ifdef WIN32
		printf("Pin: %2d %s %7d\n", _mldp->pin, bitval ? "on" : "off", xdur);
#endif // WIN32


		advanceState(); 
	} while (expired(now));						// catch up if we need to
	return true;								// schedule again
}

#define START_BUCKETS	16
// Spread starts over ~2s
#define START_FUZZ (2048 / START_BUCKETS)

void
morseTimer::loadPatterns(scheduler* schedp, ledDriver *driverp, ticks_t now)
{
	lfsr *lfsrp = new lfsr();
	for (int i = 0; i < NUM_MORSE_LIGHT_LIST; i++) {
		morseTimer *light = new morseTimer(&morseLightList[i]);
		ticks_t startOffset = (lfsrp->next() % START_BUCKETS) * START_FUZZ;
		if (light->init(now + startOffset, driverp)) {
			schedp->queueTimer(light);
		}
	}
}
