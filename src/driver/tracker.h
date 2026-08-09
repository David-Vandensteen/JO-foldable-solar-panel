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
    SettingBoardPinTracker *settingBoardPinTracker,
    SettingBoardPinMode *settingBoardPinMode,
    SettingProgramTrackers *settingProgramTrackers,
    SettingProgramLDR *settingProgramLDR,
    SettingProgramLDRs *settingProgramLDRs,
    SettingBoardADC *settingBoardADC,
    SettingBoardPWM *settingBoardPWM,
    SettingProgramMotors *settingProgramMotors
  );
  void init();
  TrackerState update();

private:
  static void onIntervalTick(void *ctx);
  SettingBoardPinMode *_settingBoardPinMode;
  Ldrs _ldrs;
  Motors _motors;
  SettingProgramMotors *_settingProgramMotors;
  SettingProgramTrackers *_settingProgramTrackers;
  TrackerState _state = TrackerState::IDLE;
  Command _command;
  DV_EveryInterval _everyInterval;
  bool isManualMode();
  void deploy();
  void retract();
  void stop();
  void interval();
};

#endif