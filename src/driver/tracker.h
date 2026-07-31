#ifndef TRACKER_H
#define TRACKER_H
#include <Arduino.h>
#include "command.h"
#include "ldrs.h"
#include "motors.h"
#include "setting.h"

class Tracker {
public:
  explicit Tracker(
    SettingBoardPinTracker *trackerPin,
    SettingBoardPinMode *modePin,
    SettingProgramTrackers *trackingSetting,
    SettingProgramLDRs *ldrSetting,
    SettingBoardADC *adcSetting,
    SettingBoardPWM *pwmSetting,
    SettingProgramMotor *motorSetting
  );
  void init();
  void update();

private:
  enum class State {
    IDLE,
    DEPLOYING,
    RETRACTING,
  };
  SettingBoardPinMode *_modePin;
  Ldrs _ldrs;
  Motors _motors;
  State _state = State::IDLE;
  SettingProgramMotor *_motorSetting;
  unsigned long _trackingInterval;
  bool isManualMode();
  void deploy();
  void retract();
  void stop();
};

#endif