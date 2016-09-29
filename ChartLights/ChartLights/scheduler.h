#pragma once

#include "timer.h"

using namespace std;

#include <iterator>
#include <queue>
#include "Lfsr.h"

class Compare {
  public:
    bool operator()(timer *left, timer* right) {
      bool ret = left->operator <(right);
      return ret;
    }
};

class scheduler {
    priority_queue<timer *, vector<timer *>, Compare> timerList;
	deque<timer *> expiredDeque;
	lfsr* _lfsr;

  public:
	scheduler();

    void queueTimer(timer* t);

    bool empty();

	int size();

    bool expired(ticks_t now, timer* t);

    ticks_t dispatch(ticks_t now);

    ticks_t remaining(ticks_t now);
};
