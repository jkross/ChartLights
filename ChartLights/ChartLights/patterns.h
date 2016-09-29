#pragma once

typedef uint16_t seq_t;
//typedef uint8_t pin_t;

#define PATTERN_SEQ_LEN 2
struct pattern {
  // pin_t pin;
  // on, followed by off
  seq_t sequence[PATTERN_SEQ_LEN];
};

