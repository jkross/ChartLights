#pragma once
#include <stdint.h>

class ledDriver {
private:
	static const int NUM_BANKS = 5;
	const int LEDS_PER_BANK = 8;
	const int latchPin = 12;  // connected to LE  of TLC5916
	const int clockPin = 8;   // connected to CLK of TLC5916
	const int dataPin = 11;   // connected to SDI of TLC5916
	const int oePin = 3;      // connected to ~OE of TLC5916

							  // Since ~OE is active low we calcuate our PWM percent as the inverse %
#define PWM_PCT_ACT_LOW(_PCT) ((int)255*(1-(_PCT/100.0)))
#define PWM_PCT 10

	uint8_t _data[NUM_BANKS];
	int		_pwmPct;
public:
	ledDriver();

	void setPwm(int pwmPct);

	void writeData();

	void set(int i, bool val);
};