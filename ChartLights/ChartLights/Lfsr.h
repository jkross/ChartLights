#pragma once
#include <stdint.h>

#define LFSR_BITS			16

typedef uint16_t lfsr_val_t;

class lfsr {
private:
	lfsr_val_t	_start_state;
	lfsr_val_t	_lfsr;
public:
	lfsr();
	lfsr_val_t next(void);
};