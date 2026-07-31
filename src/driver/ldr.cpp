#include <Arduino.h>
#include <ArduinoLog.h>
#include <dv_every_interval.h>
#include <dv_average_accumulator8.h>
#include "ldr.h"
#include "setting.h"

// Public
Ldr::Ldr(uint8_t pin, uint16_t adcResolution, SettingProgramLDRs *ldrSetting)
  : _pin(pin),
    _adcResolution(adcResolution),
    _ldrSetting(ldrSetting) {}

void Ldr::init() {
  Log.traceln("Ldr::init");
  pinMode(_pin, INPUT);
  _interval
    .setInterval(_ldrSetting->sampling.interval)
    .setCallback(Ldr::onIntervalTick, this);
}

uint8_t Ldr::update() {
  _interval.update();
  return _average.getValue();
}

void Ldr::reset() {
  _average.reset();
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
  _average.add(inputPercent);
  return _average.getValue();
}
