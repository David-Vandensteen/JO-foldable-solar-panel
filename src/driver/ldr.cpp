#include <Arduino.h>
#include <ArduinoLog.h>
#include <dv_every_interval.h>
#include <dv_average_accumulator8.h>
#include "ldr.h"
#include "setting.h"

// Public
Ldr::Ldr(uint8_t pin, uint16_t adcResolution, SettingProgramLDRs *settingProgramLDRs)
  : _pin(pin),
    _adcResolution(adcResolution),
    _settingProgramLDRs(settingProgramLDRs) {}

void Ldr::init() {
  Log.traceln("Ldr::init - pin: %d, sampling interval: %lu", _pin, _settingProgramLDRs->sampling.interval);
  pinMode(_pin, INPUT);
  _everyInterval
    .setInterval(_settingProgramLDRs->sampling.interval)
    .setCallback(Ldr::onIntervalTick, this);
}

uint8_t Ldr::getAveragePercentValue() {
  return _averageAccumulator8.getValue();
}

uint8_t Ldr::update() {
  _everyInterval.update();

  return _averageAccumulator8.getValue();
}

// Private
void Ldr::onIntervalTick(void *ctx) {
  if (ctx == nullptr) {
    return;
  }

  Ldr *self = static_cast<Ldr *>(ctx);
  self->interval();
}

uint8_t Ldr::interval() {
  uint16_t rawInput = analogRead(_pin);
  uint8_t inputPercent = (uint8_t)(((uint32_t)rawInput * 100U) / _adcResolution);
  _averageAccumulator8.add(inputPercent);
  #if LOG_LDR_INTERVAL
  Log.noticeln("ldr-%d:%d, ldr-%d-average:%d", _pin, inputPercent, _pin, _averageAccumulator8.getValue());
  #endif
  return _averageAccumulator8.getValue();
}
