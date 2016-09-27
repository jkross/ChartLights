#pragma once
// using namespace std;



typedef unsigned long ticks_t;
const ticks_t HalfWrap = ~((ticks_t)0) >> 1;

class timer {
private:
	ticks_t ticks;

public:
	timer(int i);
	timer();

	void invoke(ticks_t now);
	ticks_t remaining(ticks_t now);
	
	bool operator <(const timer& other) const;

};
