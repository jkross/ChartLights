#ifndef WIN32
#include <Arduino.h>
#include <pnew.cpp>
#endif // !WIN32
#include "scheduler.h"

scheduler::scheduler()
{
	_lfsr = new lfsr();
}

void
scheduler::queueTimer(timer* t)
{
	timerList.push(t);
}

bool 
scheduler::empty()
{
	return timerList.empty();
}

int
scheduler::size()
{
	return timerList.size();
}

// Has any scheduled timer expired?
bool
scheduler::expired(ticks_t now)
{
	// Check the next timer...
	return timerList.top()->expired(now);
}

void
scheduler::dispatch(ticks_t now)
{
	timer *top;
	while (!timerList.empty() && expired(now)) {
		top = timerList.top();
		timerList.pop();
		expiredDeque.push_front(top);
	}
	while (!expiredDeque.empty()) {
		top = expiredDeque.back();
		expiredDeque.pop_back();
		bool another = top->invoke(now, (_lfsr->next() & 0x1));
		if (another) {
			queueTimer(top);
			//ticks_t next = timerList.top()->ticks; // DBG
			//lSize = size(); // DBG
		}
	}
}

ticks_t
scheduler::remaining(ticks_t now)
{
	ticks_t remain = 0;
	if (!timerList.empty()) {
		timer *top = timerList.top();
		remain = top->remaining(now);
	}
	return remain;
}