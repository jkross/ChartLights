#include <Arduino.h>
#include "debug.h"
#include "timer.h"
#include "snapshotTime.h"
#include <new>

bool
timer::invoke(ticks_t now) {
	SPAB("callback: ", (ticks, HEX)); SPLN();
	return false;
}

ticks_t
timer::remaining(ticks_t now) {
  return (ticks - now);
}

bool
timer::operator <(const timer other) const
{
  bool ret = (other.ticks - gTime->get()) < (ticks - gTime->get());
  SPAV((other.ticks, DEC));
  SPABV(" < ", ticks);
  SPABV(" = ", (ret, DEC));
  SPLNV();
  return ret;
}

bool
timer::operator <(const timer* other) const
{
  bool ret = (other->ticks - gTime->get()) < (ticks - gTime->get());
  SPAV((other->ticks, DEC));
  SPABV(" < ", ticks);
  SPABV(" = ", (ret, DEC));
  SPLNV();
  return ret;
}

bool
timer::expired(ticks_t now, ticks_t due)
{
	bool ret = (now - due) < HalfWrap;
  return ret;
}

timer::timer(int i, snapshotTime* snapshot)
{
  ticks = i;
  gTime = snapshot;
}

timer::timer() {
  ticks = 0;
}
