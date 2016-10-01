#pragma once
#include "snapshotTime.h"



class timer {
protected:
	snapshotTime *snapp;

public:
	ticks_t ticks;

	timer(ticks_t i, snapshotTime * snapshotp);
	bool operator <(const timer* other) const;

	virtual bool invoke(ticks_t now, int fuzz);	// if returns true, re-schedule
	ticks_t remaining(ticks_t now);
	bool expired(ticks_t now);

};
