#ifndef TRACKER_H
#define TRACKER_H
#include <Arduino.h>
#include <dv_every_interval.h>
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
    SettingProgramLDRs *ldrsSetting,
    SettingBoardADC *adcSetting,
    SettingBoardPWM *pwmSetting,
    SettingProgramMotors *motorSetting
  );
  void init();
  TrackerState update();

private:
  static void onIntervalTick(void *ctx);
  SettingBoardPinMode *_modePin;
  Ldrs _ldrs;
  Motors _motors;
  TrackerState _state = TrackerState::IDLE;
  SettingProgramMotors *_motorSetting;
  Command _command;
  SettingProgramTrackers *_trackersSetting;
  DV_EveryInterval _interval;
  bool isManualMode();
  void deploy();
  void retract();
  void stop();
  void interval();
};

#endif