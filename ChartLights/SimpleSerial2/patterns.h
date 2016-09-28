#pragma once

#define PATTERN_SEQ_LEN 2
struct pattern {
  int pin;
  // on, followed by off
  int sequence[PATTERN_SEQ_LEN];
};

