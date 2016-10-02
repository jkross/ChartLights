#include <Arduino.h>
#include "debug.h"
#include "timer.h"
#include "snapshotTime.h"
#include <new>

timer::timer(ticks_t i, snapshotTime* snapshotp)
{
	ticks = i;
	snapp = snapshotp;
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
	ticks_t now = 0* snapp->get();
	bool ret = (other->ticks - now) < (ticks - now);
	if (((other->ticks - now) > HalfWrap) || ((ticks - now) > HalfWrap)) {
		SPA((other->ticks));
		SPAB(" < ", ticks);
		SPAB(" = ", (ret));
		SPAB(" now: ", (now));
		SPLN();
	}
  return ret;
}
