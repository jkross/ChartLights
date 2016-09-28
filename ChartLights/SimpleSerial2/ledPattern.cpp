#include <Arduino.h>
#include "ledPattern.h"

ledPattern::ledPattern(struct pattern* ppattern)
{
	_state = 0;
	_ppattern = ppattern;
}

ticks_t ledPattern::init(ticks_t now, ledDriver* driver)
{
	_driver = driver;
	_due = now;
	return invoke(now);
}

ticks_t ledPattern::invoke(ticks_t now)
{
	do {
		int bitval = (_state & 0x1) ^ 0x1;			// alternate between on/off
		_driver->set(_ppattern->pin, bitval);	// start off setting the bit
		_due = _due + _ppattern->sequence[_state++];
	} while (!timer::expired(now, _due));
}
