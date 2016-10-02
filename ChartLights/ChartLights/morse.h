#pragma once

enum Morse {
	MORSE_UNIT = 250,
	MORSE_END = 0xF
};

#define MORSE_DIT   { 1, 1 }
#define MORSE_DIT_E { 1, 3 }
#define MORSE_DAH   { 3, 1 }
#define MORSE_DAH_E { 3, 3 }
#define MORSE_GAP { 0, 4 }
#define MORSE_ENDS { MORSE_END, MORSE_END }

struct morseCharOnOff {
	uint8_t	on : 4;
	uint8_t	off : 4;
};

static const struct morseChar {
	/*unsigned char letter;*/
	struct morseCharOnOff delays[6];
} MorseMap[] = {
	{/* ' ',*/{ MORSE_GAP, MORSE_ENDS } }, //Gap between word
	{/* '0',*/{ MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* '1',*/{ MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* '2',*/{ MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* '3',*/{ MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* '4',*/{ MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* '5',*/{ MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* '6',*/{ MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* '7',*/{ MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* '8',*/{ MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* '9',*/{ MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'A',*/{ MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'B',*/{ MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'C',*/{ MORSE_DAH, MORSE_DIT, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'D',*/{ MORSE_DAH, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'E',*/{ MORSE_DIT_E, MORSE_ENDS } },
	{/* 'F',*/{ MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'G',*/{ MORSE_DAH, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'H',*/{ MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'I',*/{ MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'J',*/{ MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'K',*/{ MORSE_DAH, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'L',*/{ MORSE_DIT, MORSE_DAH, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'M',*/{ MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'N',*/{ MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'O',*/{ MORSE_DAH, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'P',*/{ MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'Q',*/{ MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'R',*/{ MORSE_DIT, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'S',*/{ MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	{/* 'T',*/{ MORSE_DAH_E, MORSE_ENDS } },
	{/* 'U',*/{ MORSE_DIT, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'V',*/{ MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'W',*/{ MORSE_DIT, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'X',*/{ MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'Y',*/{ MORSE_DAH, MORSE_DIT, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	{/* 'Z',*/{ MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	// {/* '.',*/ { MORSE_DIT, MORSE_DAH, MORSE_DIT, MORSE_DAH, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	// {/* ',',*/ { MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DAH_E, MORSE_ENDS } },
	// {/* '?',*/ { MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	// {/* '-',*/ { MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DIT, MORSE_DAH_E, MORSE_ENDS } },
	// {/* '\'',*/ { MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	// {/* ':',*/ { MORSE_DAH, MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DIT_E, MORSE_ENDS } },
	// {/* '"',*/ { MORSE_DIT, MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	// {/* '/',*/ { MORSE_DAH, MORSE_DIT, MORSE_DIT, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },
	// {/* '@',*/ { MORSE_DIT, MORSE_DAH, MORSE_DAH, MORSE_DIT, MORSE_DAH, MORSE_DIT_E, MORSE_ENDS } },};
};