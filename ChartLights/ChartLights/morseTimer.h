#pragma once
#include "scheduler.h"
#include "ledDriver.h"
#include "timer.h"
#include "morsePatterns.h"
#include "morse.h"



class morseTimer : public timer {
private:
	morseLightDesc*	_mldp;
	ledDriver*		_driver;
	uint8_t			_state_char;		// the character we are on
	uint8_t			_state;				// position in the character
	const morseChar* _mchar;

	uint16_t stepDuration(int state, int fuzz);
	int index(char c);
	const morseChar * getCharDesc(int state_char);
	int decodeStateDur();
	void advanceState(void);

public:
	morseTimer(morseLightDesc * mldp);
	virtual bool init(ticks_t now, ledDriver* driver);
	virtual bool invoke(ticks_t now, int fuzz);
	static void loadPatterns(scheduler * schedp, ledDriver * driverp, ticks_t now);
};
