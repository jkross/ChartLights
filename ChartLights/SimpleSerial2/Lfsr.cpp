#include "lfsr.h"
#define LFSR_START_STATE	0xDEAD
#define	LFSR_POLY			0xB400


lfsr::lfsr() {
	_start_state = LFSR_START_STATE;
}

lfsr_val_t
lfsr::next() {
	lfsr_val_t lsb = _lfsr & 1;   /* Get LSB (i.e., the output bit). */
	_lfsr >>= 1;                  /* Shift register */
	if (lsb) {					  /* If the output bit is 1, apply toggle mask. */
		_lfsr ^= LFSR_POLY;
	}
	return _lfsr;
}