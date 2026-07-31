#ifndef LDR_H
#define LDR_H
#include <Arduino.h>
#include <dv_every_interval.h>
#include <dv_average_accumulator8.h>
#include "setting.h"

class Ldr {
public:
  int raw;
  explicit Ldr(uint8_t pin, uint16_t adcResolution, SettingProgramLDRs *ldrSetting);
  void init();
  uint8_t update();
  void reset();

private:
  static void onIntervalTick(void *ctx);
  DV_AverageAccumulator8 _average;
  DV_EveryInterval _samplingInterval;
  SettingProgramLDRs *_ldrSetting;
  uint16_t _adcResolution;
  uint8_t _pin;
  uint8_t interval();
};

#endif