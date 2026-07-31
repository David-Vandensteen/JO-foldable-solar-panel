#ifndef TRACKER_H
#define TRACKER_H
#include <Arduino.h>
#include "command.h"
#include "ldrs.h"
#include "motors.h"
#include "setting.h"

enum class TrackerState {
  IDLE,
  DEPLOY,
  RETRACT,
  STOP
};

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
  TrackerState update();

private:
  SettingBoardPinMode *_modePin;
  Ldrs _ldrs;
  Motors _motors;
  TrackerState _state = TrackerState::IDLE;
  SettingProgramMotor *_motorSetting;
  Command _command;
  bool isManualMode();
  void deploy();
  void retract();
  void stop();
};

#endif