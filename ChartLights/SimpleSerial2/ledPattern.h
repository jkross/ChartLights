#pragma once
#include "scheduler.h"
#include "ledDriver.h"
#include "patterns.h"
#include "timer.h"



class ledPattern : public timer {
private:
	int				_state;
	ticks_t			_due;
	struct pattern* _ppattern;
	ledDriver*		_driver;
public:
	ledPattern(struct pattern* ppattern);
	ticks_t init(ticks_t now, ledDriver* driver);
	ticks_t invoke(ticks_t now);

};
