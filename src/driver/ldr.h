#ifndef LDR_H
#define LDR_H
#include <Arduino.h>
#include <dv_average_accumulator8.h>
#include "setting.h"

class Ldr {
public:
  int raw;
  explicit Ldr(uint8_t pin, uint16_t adcResolution, SettingProgramLDRs *ldrSetting);
  void init();
  unsigned long getLastUpdateTime();
  unsigned long getSamplingInterval();
  uint8_t update();

private:
  DV_AverageAccumulator8 _average;
  unsigned long _lastUpdateTime;
  unsigned long _samplingInterval;
  uint16_t _adcResolution;
  uint8_t _pin;
};

#endif