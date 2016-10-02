#pragma once
typedef unsigned long ticks_t;

const ticks_t HalfWrap = ~((ticks_t)0) >> 1;

//#define SNAP_OFFSET	(~((ticks_t)0) - 1000)
//#define SNAP_OFFSET (HalfWrap - 1000)
#define SNAP_OFFSET 0

class snapshotTime {
private:
	ticks_t _now;

public:
	snapshotTime() {
		set(0);
	}

	void set(ticks_t now) {
		_now = now + SNAP_OFFSET;
	}

	ticks_t get() {
		return _now;
	}
};