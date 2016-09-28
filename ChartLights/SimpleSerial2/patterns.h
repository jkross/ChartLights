#pragma once

typedef unsigned short seq_t;
typedef unsigned short pin_t;

#define PATTERN_SEQ_LEN 2
struct pattern {
  pin_t pin;
  // on, followed by off
  seq_t sequence[PATTERN_SEQ_LEN];
};

