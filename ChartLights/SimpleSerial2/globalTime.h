#pragma once

class globalTime {
private:
	ticks_t _now;

public:
	globalTime() {
		set(0);
	}

	void set(ticks_t now) {
		_now = now;
	}

	ticks_t get() {
		return _now;
	}
};

extern globalTime gTime;