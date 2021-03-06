#include <Arduino.h>
#include "MotorDriver.h"
#include "DataSource.h"
#include "Pinouts.h"

/*
 * ADCSampler implements SD logging for the ADC channels
 */

 /* Pinmap, for reference, implemented in ADSampler.cpp
 Analog input name       Teensy Pin
 A0                      14
 A1                      15
 A7                      21
 A9                      23
 A10                     24
 A11                     25
 A12                     26
 */

#define NUM_PINS 7

#define ADC_LOOP_INTERVAL 100 // ms
#define ADC_LOOP_OFFSET 30 // ms

class ADCSampler : public DataSource
{
public:
  ADCSampler(void);

  // Managing state
  int sample [NUM_PINS];
  void updateSample(void);
  void printSample(void);

  // Write out
  size_t writeDataBytes(unsigned char * buffer, size_t idx);

  bool loopTime(int loopStartTime);

private:
  int lastLoopTime = -1;
};
