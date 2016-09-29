#pragma once
#include "scheduler.h"
#include "ledDriver.h"
#include "patterns.h"
#include "timer.h"



class ledPattern : public timer {
private:
	uint8_t			_state;
	uint8_t			_pin;
	uint8_t		    _seqIndex;
	ledDriver*		_driver;

	uint16_t sequenceLength(int state, int fuzz);

public:
	ledPattern(uint8_t pin, int seqIndex, snapshotTime * snapshot);
	virtual bool init(ticks_t now, ledDriver* driver);
	virtual bool invoke(ticks_t now, int fuzz);
	static void loadPatterns(scheduler * sched, ledDriver * driver, snapshotTime* snapshot);
};
