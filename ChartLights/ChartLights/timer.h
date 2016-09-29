#pragma once
// using namespace std;
#include "snapshotTime.h"


const ticks_t HalfWrap = ~((ticks_t)0) >> 1;

class timer {
protected:
	snapshotTime *gTime;

public:
	ticks_t ticks;

	timer(int i, snapshotTime* snapshot);
	timer();

	// if returns true, re-schedule
	virtual bool invoke(ticks_t now, int fuzz);
	ticks_t remaining(ticks_t now);

	bool operator <(const timer* other) const;

	static bool expired(ticks_t now, ticks_t due);
};
