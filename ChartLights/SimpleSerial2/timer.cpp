#include <Arduino.h>
#include "timer.h"
#include "globalTime.h"
#include <new>

void 
timer::invoke(ticks_t now) {
	// cout << "callback: " << ticks << endl;
	Serial.print("callback: ");
	Serial.print(ticks, HEX);
	Serial.println();
	//Serial.println(ticks, HEX);
}

ticks_t 
timer::remaining(ticks_t now) {
	return (ticks - now);
}

bool
timer::operator <(const timer& other) const
{
	return (other.ticks - gTime.get()) < (ticks - gTime.get());
}

timer::timer(int i)
{
	ticks = i;
}

timer::timer() {
	ticks = 0;
}
