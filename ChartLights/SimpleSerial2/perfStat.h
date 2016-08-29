#ifndef _PERFSTAT_H_INCLUDED
#define _PERFSTAT_H_INCLUDED

#include "Arduino.h"

template <int COUNT>
class perfStat {
private:
    typedef unsigned long sample_t;
    sample_t  _stats[COUNT];
    sample_t  _start;
    int       _index;

public:
    perfStat() : _index(0)
    {
      for (int i=0; i < COUNT; i++)
      {
        _stats[i] = 0;
      }
    }

    ~perfStat()
    {
      compute();
    }

    void compute()
    {
      Serial.println("Stats Printed");
    }

    void start()
    {
      _start = micros();
    }

    bool stop()
    {
      sample_t now = micros();
      _stats[_index++] = now - _start;
      return (_index < COUNT);
    }
};
#endif
