#pragma once

#include "timer.h"

using namespace std;

#include <iterator>
#include <queue>

class scheduler {
	priority_queue<timer> timerList;

public:
	void schedule(timer t);

	bool empty();

	bool expired(ticks_t now, timer t);

	void dispatch(ticks_t now);

	//void dumpDestructive();
};
