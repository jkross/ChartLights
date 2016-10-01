#pragma once
#include "scheduler.h"
#include "ledDriver.h"
#include "timer.h"
#include "morsePatterns.h"



class morseTimer : public timer {
private:
	uint8_t			_state_char;		// the character we are on
	uint8_t			_state;				// position in the character
	morseLightDesc*	_mldp;
	ledDriver*		_driver;

	uint16_t stepDuration(int state, int fuzz);

public:
	morseTimer(morseLightDesc * mldp, snapshotTime * snapshotp);
	virtual bool init(ticks_t now, ledDriver* driver);
	virtual bool invoke(ticks_t now, int fuzz);
	static void loadPatterns(scheduler * sched, ledDriver * driver, snapshotTime* snapshot);
};
