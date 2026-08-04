#ifndef LDR_H
#define LDR_H
#include <Arduino.h>
#include <dv_every_interval.h>
#include <dv_average_accumulator8.h>
#include "setting.h"

class Ldr {
public:
  explicit Ldr(uint8_t pin, uint16_t adcResolution, SettingProgramLDRs *ldrsSetting);
  uint8_t getAveragePercentValue();
  uint8_t update();
  void init();

private:
  static void onIntervalTick(void *ctx);
  DV_AverageAccumulator8 _average;
  DV_EveryInterval _interval;
  SettingProgramLDRs *_ldrsSetting;
  uint16_t _adcResolution;
  uint8_t _pin;
  uint8_t interval();
};

#endif