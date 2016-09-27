#pragma once

struct patterns {
  int pin;
  // on, followed by off
  int sequence[2];
};

struct patterns patterns[] = {
  { /*pin*/  0, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-56-23.244N 076-31-38.730W  South River Light 12 */ },
  { /*pin*/  1, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-56-49.913N 076-27-47.212W  Lake Ogleton Entrance Light 5 */ },
  { /*pin*/  2, /*sequence*/ { 250, 2250 } /* Fl G 2.5s    38-56-06.378N 076-31-24.210W  South River Light 11 */ },
  { /*pin*/  3, /*sequence*/ { 250, 2250 } /* Fl R 2.5s    38-56-07.908N 076-22-55.842W  Chesapeake Channel Lighted Buoy 88 */ },
  { /*pin*/  4, /*sequence*/ {  10,   10 } /* Q G          38-55-58.127N 076-23-32.776W  Chesapeake Channel Lighted Buoy WR87 */ },
  { /*pin*/  5, /*sequence*/ { 250, 4750 } /* Fl W 5s      38-53-56.300N 076-26-09.200W  Thomas Point Shoal Light */ },
  { /*pin*/  6, /*sequence*/ { 250, 2250 } /* Fl R 2.5s    38-51-56.391N 076-29-27.019W  West River Entrance Light 2 */ },
  { /*pin*/  7, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-51-58.414N 076-23-32.836W  Chesapeake Channel Lighted Buoy 86 */ },
  { /*pin*/  8, /*sequence*/ { 250, 4750 } /* Bl B M        38-46-22.58N   76-33-47.61W  VaLeighGirl */ },
  { /*pin*/  9, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-46-14.975N 076-33-38.896W  Rockhold Creek Channel Light 12 */ },
  { /*pin*/ 10, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-46-01.659N 076-33-16.223W  Rockhold Creek Jetty Light 2 */ },
  { /*pin*/ 11, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-45-55.848N 076-33-08.994W  Rockhold Creek Channel Light 1R */ },
  { /*pin*/ 12, /*sequence*/ { 250, 5750 } /* Fl W 6s      38-50-01.500N 076-23-30.000W  Bloody Point Bar Light */ },
  { /*pin*/ 13, /*sequence*/ { 250, 2250 } /* Fl R 2.5s    38-47-35.620N 076-24-41.331W  Chesapeake Channel Lighted Buoy 84A */ },
  { /*pin*/ 14, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-49-07.418N 076-22-07.829W  Eastern Bay Entrance Lighted Buoy 1E */ },
  { /*pin*/ 15, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-45-07.524N 076-26-39.330W  Chesapeake Channel Lighted Buoy 83 */ },
  { /*pin*/ 16, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-45-27.424N 076-25-06.828W  Chesapeake Channel Lighted Buoy 84 */ },
  { /*pin*/ 17, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-50-47.111N 076-15-43.284W  Tilghman Creek Light 1TC */ },
  { /*pin*/ 18, /*sequence*/ { 250, 3750 } /* Fl W 4s      38-46-05.539N 076-20-38.121W  Ferry Cove Light */ },
  { /*pin*/ 19, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-45-51.573N 076-10-33.531W  Miles River Light 7 */ },
  { /*pin*/ 20, /*sequence*/ { 250, 5750 } /* Fl W 6s      39-00-57.238N 076-23-04.488W  Sandy Point Shoal Light */ },
  { /*pin*/ 21, /*sequence*/ { 250, 3750 } /* Fl R 4s      39-00-14.938N 076-29-42.010W  Severn River Light 2 */ },
  { /*pin*/ 22, /*sequence*/ { 250, 2250 } /* Fl G 2.5s    39-00-26.901N 076-22-43.848W  Chesapeake Channel Lighted Buoy 95 */ },
  { /*pin*/ 23, /*sequence*/ { 250, 3750 } /* Fl G 4s      39-00-03.080N 076-22-52.720W  Chesapeake Channel Lighted Buoy 93 */ },
  { /*pin*/ 24, /*sequence*/ { 250, 3750 } /* Fl R 4s      39-00-00.062N 076-22-40.238W  Chesapeake Channel Lighted Buoy 94 */ },
  { /*pin*/ 25, /*sequence*/ { 250, 4750 } /* Fl B M        38-58-33.98N   76-29-57.50W  Drifmier */ },
  { /*pin*/ 26, /*sequence*/ {  10,   10 } /* Q G          38-58-42.189N 076-28-00.826W  Annapolis Harbor Channel Lighted Buoy 9 */ },
  { /*pin*/ 27, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-58-59.103N 076-23-16.547W  Chesapeake Channel Lighted Buoy 91 */ },
  { /*pin*/ 28, /*sequence*/ { 250, 2250 } /* Fl R 2.5s    38-58-29.000N 076-27-46.500W  Annapolis Harbor Channel Lighted Buoy 6 */ },
  { /*pin*/ 29, /*sequence*/ { 250, 5750 } /* Fl W 6s      38-58-24.611N 076-28-09.127W  Horn Point Light HP */ },
  { /*pin*/ 30, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-58-55.803N 076-23-04.547W  Chesapeake Channel Lighted Bell Buoy  92 */ },
  { /*pin*/ 31, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-58-17.815N 076-27-43.465W  Annapolis Harbor Channel Lighted Buoy 5 */ },
  { /*pin*/ 32, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-58-04.979N 076-28-27.976W  Eastport Harbor Entrance Light 5 */ },
  { /*pin*/ 33, /*sequence*/ { 250, 2250 } /* Fl R 2.5s    38-58-04.085N 076-28-14.776W  Eastport Harbor Entrance Light 2E */ },
  { /*pin*/ 34, /*sequence*/ { 250, 3750 } /* Fl R 4s      38-58-06.185N 076-27-27.737W  #N/A */ },
  { /*pin*/ 35, /*sequence*/ { 250, 2250 } /* Fl G 2.5s    38-57-57.251N 076-28-08.998W  Eastport Harbor Entrance Light 1E */ },
  { /*pin*/ 36, /*sequence*/ { 250, 2250 } /* Fl Y 2.5s    38-58-00.507N 076-27-09.003W  Naval Anchorage Light  A */ },
  { /*pin*/ 37, /*sequence*/ { 250, 2250 } /* Fl R 2.5s    38-58-18.504N 076-23-18.946W  Chesapeake Channel Lighted Buoy 90 */ },
  { /*pin*/ 38, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-56-42.036N 076-32-27.235W  South River Light 15 */ },
  { /*pin*/ 39, /*sequence*/ { 250, 3750 } /* Fl G 4s      38-57-07.889N 076-27-27.802W  Lake Ogleton Entrance Light 1L */ },
};
#define NUM_PATTERNS = sizeof(patterns)/sizeof(patterns[0])
