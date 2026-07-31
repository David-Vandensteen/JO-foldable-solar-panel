#include <Arduino.h>
#include <ArduinoLog.h>
#include "ldr.h"
#include "ldrs.h"
#include "setting.h"

Ldrs::Ldrs(Ldr up, Ldr down, SettingProgramLDRs *ldrSetting)
  : up(up),
    down(down),
    _ldrSetting(ldrSetting)
{}

void Ldrs::init() {
  Log.traceln("Ldrs::init");
  up.init();
  down.init();
}

LdrsComparison Ldrs::getComparison() {
  uint8_t upValue = up.getAveragePercentValue();
  uint8_t downValue = down.getAveragePercentValue();

  const int16_t delta = (int16_t)upValue - (int16_t)downValue;
  if (abs(delta) <= _ldrSetting->threshold) {
    return LdrsComparison::DEADBAND;
  }
  if (delta > 0) {
    return LdrsComparison::UP_GREATER_THAN_DOWN;
  }

  return LdrsComparison::DOWN_GREATER_THAN_UP;
}

LdrsComparison Ldrs::update() {
  // if (
  //   millis() - up.getLastUpdateTime() < up.getSamplingInterval()
  //   || millis() - down.getLastUpdateTime() < down.getSamplingInterval()
  // ) {
  //   return LdrsComparison::NOT_UPDATED;
  // }



  uint8_t upValue = up.update();
  uint8_t downValue = down.update();

  const int16_t delta = (int16_t)upValue - (int16_t)downValue;
  if (abs(delta) <= _ldrSetting->threshold) {
    return LdrsComparison::DEADBAND;
  }
  if (delta > 0) {
    return LdrsComparison::UP_GREATER_THAN_DOWN;
  }

  return LdrsComparison::DOWN_GREATER_THAN_UP;
}
