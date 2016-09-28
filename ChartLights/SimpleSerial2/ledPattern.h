#pragma once
#include "scheduler.h"
#include "ledDriver.h"
#include "patterns.h"
#include "timer.h"



class ledPattern : public timer {
private:
	int				_state;
	struct pattern* _ppattern;
	ledDriver*		_driver;
public:
	ledPattern(pattern * ppattern, snapshotTime * snapshot);
	virtual bool init(ticks_t now, ledDriver* driver);
	virtual bool invoke(ticks_t now);
	static void loadPatterns(scheduler * sched, ledDriver * driver, snapshotTime* snapshot);
};
