#include <Arduino.h>
#include "debug.h"
#include "timer.h"
#include "snapshotTime.h"
#include <new>

bool
timer::invoke(ticks_t now, int fuzz) {
	return false;
}

ticks_t
timer::remaining(ticks_t now) {
  return (ticks - now);
}

bool
timer::expired(ticks_t now)
{
	return remaining(now) < HalfWrap;
}

bool
timer::operator <(const timer* other) const
{
  ticks_t now = 0/*snapp->get()*/;
  bool ret = (other->ticks - now) < (ticks - now);
  SPAV((other->ticks, DEC));
  SPABV(" < ", ticks);
  SPABV(" = ", (ret, DEC));
  SPLNV();
  return ret;
}

timer::timer(ticks_t i, snapshotTime* snapshotp)
{
  ticks = i;
  snapp = snapshotp;
}
