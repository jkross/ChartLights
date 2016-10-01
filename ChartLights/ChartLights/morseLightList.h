#pragma once

struct morseLightDesc morseLightList[] = {
	{ /*pin*/  8, /*letters*/  "DKD "  /* Bl B M        38-46-22.58N   76-33-47.61W  VaLeighGirl */ },
	{ /*pin*/ 25, /*letters*/  "1961 " /* Fl B M        38-58-33.98N   76-29-57.50W  Drifmier */ },
};
#define NUM_MORSE_LIGHT_LIST sizeof(morseLightList)/sizeof(morseLightList[0])
