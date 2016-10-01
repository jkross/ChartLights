#pragma once
// using namespace std;
#include "snapshotTime.h"


const ticks_t HalfWrap = ~((ticks_t)0) >> 1;

class timer {
protected:
	snapshotTime *snapp;

public:
	ticks_t ticks;

	timer(ticks_t i, snapshotTime * snapshotp);

	// if returns true, re-schedule
	virtual bool invoke(ticks_t now, int fuzz);
	ticks_t remaining(ticks_t now);
	bool expired(ticks_t now);

	bool operator <(const timer* other) const;
};
