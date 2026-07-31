#include <Arduino.h>
#include <ArduinoLog.h>
#include <dv_average_accumulator8.h>
#include "ldr.h"
#include "setting.h"

Ldr::Ldr(uint8_t pin, uint16_t adcResolution, SettingProgramLDRs *ldrSetting)
  : _pin(pin),
    _adcResolution(adcResolution),
    _samplingInterval(ldrSetting->sampling.interval),
    _lastUpdateTime(0) {}

unsigned long Ldr::getLastUpdateTime() {
  return _lastUpdateTime;
}

unsigned long Ldr::getSamplingInterval() {
  return _samplingInterval;
}

void Ldr::init() {
  Log.traceln("Ldr::init");
  pinMode(_pin, INPUT);
}

uint8_t Ldr::update() {
  _lastUpdateTime = millis();
  uint16_t rawInput = analogRead(_pin);
  uint8_t inputPercent = (uint8_t)(((uint32_t)rawInput * 100U) / _adcResolution);


  if (LOG) {
    Serial.print("input-id"); Serial.print(_pin); Serial.print(":");  Serial.print(inputPercent);
    Serial.println("");

    Serial.print("filtered-id"); Serial.print(_pin); Serial.print(":"); Serial.print(_average.getValue());
    Serial.println("");
  }

  return _average.add(inputPercent);
}
