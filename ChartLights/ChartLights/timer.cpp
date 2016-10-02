#ifndef WIN32
#include <Arduino.h>
#endif
#include "debug.h"
#include "timer.h"
#include "snapshotTime.h"
#include <new>

timer::timer(ticks_t i)
{
	ticks = i;
}

bool
timer::invoke(ticks_t now, int fuzz) {
	return false;		// default to one-shot
}

ticks_t
timer::remaining(ticks_t now) {
  return (ticks - now);
}

bool
timer::expired(ticks_t now)
{
	return (now - ticks) < HalfWrap; // remaining(now)-1) < HalfWrap;
}

bool
timer::operator <(const timer* other) const
{
	bool ret = (other->ticks - ticks) > HalfWrap;
		SPAV((other->ticks));
		SPABV(" < ", ticks);
		SPABV(" = ", (ret));
		SPABV(" now: ", (now));
		SPLNV();
  return ret;
}
