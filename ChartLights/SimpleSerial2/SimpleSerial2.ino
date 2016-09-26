// Cascaded TLC5916 drivers

#include "perfStat.h"

const int latchPin = 12;  // connected to LE  of TLC5916
const int clockPin = 8;   // connected to CLK of TLC5916
const int dataPin = 11;   // connected to SDI of TLC5916
const int oePin = 3;      // connected to ~OE of TLC5916

// Since ~OE is active low we calcuate our PWM percent as the inverse %
#define PWM_PCT_ACT_LOW(_PCT) ((int)255*(1-(_PCT/100.0)))
#define PWM_PCT 10

#define NUM_BANKS 5       // number of drivers
#define LEDS_PER_BANK 8
byte datArray[][NUM_BANKS] = {{0x0, 0x0, 0x0, 0x0, 0x0},
  {0xaa, 0xaa, 0xaa, 0xaa, 0xaa},
  {0x55, 0x55, 0x55, 0x55, 0x55},
};
#define NUM_SAMPLES (sizeof(datArray)/sizeof(datArray[0]))

// Timing delay for test loop
#define DELAY 1000


perfStat<100> *cnt;

void setup ()
{
  //set pins to output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(oePin, OUTPUT);
  Serial.begin(57600);
  digitalWrite(latchPin, LOW);
  analogWrite(oePin, PWM_PCT_ACT_LOW(PWM_PCT));
  cnt = new perfStat<100>();
}

void loop()
{
  for (int j = 10; j <= 100; j += 90) {
    analogWrite(oePin, PWM_PCT_ACT_LOW(j));
    //loop through all samples
    for (int sample = 0; sample < NUM_SAMPLES; sample++)
    {
      {
        // new variable through the loop hangs after 3 iterations - looks like memory isn't being freed
        //      auto cnt = new perfStat<100>();
        cnt->init();
        do {  // 232us avg w/ 2, 562us w/ 5
          cnt->start();
          //digitalWrite(oePin,HIGH); // disable LEDs and don't let driver switch to non-standard mode
          for (int bank = NUM_BANKS - 1; bank >= 0; bank--)
          {
            //dPrint(sample, bank);
            shiftOut(dataPin, clockPin, MSBFIRST, datArray[sample][bank]);
          }
          // toggle latch pin to latch data from shift register to output drivers
          digitalWrite(latchPin, HIGH);
          digitalWrite(latchPin, LOW);
          // set ~OE according to PWM percentage
          //analogWrite(oePin, PWM_PCT_ACT_LOW(PWM_PCT));
        } while (!(cnt->stop()));
        cnt->compute();
      }
      delay(DELAY);
    }
  }
}

void dPrint(int sample, int bank)
{
  Serial.print("sample: ");
  Serial.print(sample, DEC);
  Serial.print(" bank: ");
  Serial.print(bank, DEC);
  Serial.print(" ");
  Serial.print(datArray[sample][bank], DEC);
  Serial.println();
}
