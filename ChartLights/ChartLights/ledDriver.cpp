#include <Arduino.h>
#include "ledDriver.h"

ledDriver::ledDriver() {
	for (int i = 0; i < NUM_BANKS; i++) {
		_data[i] = 0;
	}
	_pwmPct = PWM_PCT;
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	pinMode(oePin, OUTPUT);
	digitalWrite(latchPin, LOW);
	digitalWrite(oePin, HIGH);
}

void
ledDriver::setPwm(int pwmPct)
{
	// value will be used next writeData() call
	_pwmPct = pwmPct;
}

void 
ledDriver::writeData() {
	// disable LEDs and don't let driver switch to non-standard mode
	digitalWrite(oePin, HIGH);
	for (int bank = NUM_BANKS - 1; bank >= 0; bank--)
	{
		shiftOut(dataPin, clockPin, MSBFIRST, _data[bank]);
	}
	// toggle latch pin to latch data from shift register to output drivers
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin, LOW);
	// set ~OE according to PWM percentage
	analogWrite(oePin, PWM_PCT_ACT_LOW(_pwmPct));
}

void ledDriver::set(int i, bool val) {
	int bank = i / LEDS_PER_BANK;
	int bit = i % LEDS_PER_BANK;
	if (val) {
		_data[bank] |= 1 << bit;
	}
	else {
		_data[bank] &= ~(1 << bit);
	}
}
