#include <Arduino.h>
#include <ArduinoLog.h>
#include <dv_every_interval.h>
#include "command.h"
#include "setting.h"
#include "tracker.h"
#include "ldr.h"
#include "ldrs.h"
#include "motor.h"

// Public
Tracker::Tracker(
  SettingBoardPinTracker *trackerPin,
  SettingBoardPinMode *modePin,
  SettingProgramTrackers *trackersSetting,
  SettingProgramLDRs *ldrSetting,
  SettingBoardADC *adcSetting,
  SettingBoardPWM *pwmSetting,
  SettingProgramMotor *motorSetting
)
  : _motorSetting(motorSetting),
    _modePin(modePin),
    _ldrs(
      Ldr(
        trackerPin->ldr.up,
        adcSetting->resolution,
        ldrSetting
      ),
      Ldr(
        trackerPin->ldr.down,
        adcSetting->resolution,
        ldrSetting
      ),
      ldrSetting->threshold
    ),
    _motors(
      Motor(
        trackerPin->motors.in1,
        trackerPin->motors.in2,
        trackerPin->motors.ena,
        pwmSetting->resolution
      ),
      Motor(
        trackerPin->motors.in3,
        trackerPin->motors.in4,
        trackerPin->motors.enb,
        pwmSetting->resolution
      )
    ),
    _command(&trackerPin->command),
    _trackersSetting(trackersSetting) {}

void Tracker::init() {
  Log.traceln("Tracker::init");
  _state = TrackerState::IDLE;
  pinMode(_modePin->manual, INPUT);
  _ldrs.init();
  _motors.init();
  _command.init();
  _interval
    .setInterval(_trackersSetting->interval)
    .setCallback(Tracker::onIntervalTick, this);
}

TrackerState Tracker::update() {
  CommandState commandState = _command.update();
  if (commandState == CommandState::STOP) {
    Log.traceln("Tracker::update - Command STOP");
    stop();
    return TrackerState::STOP;
  } else if (commandState == CommandState::RESET) {
    Log.traceln("Tracker::update - Command RESET");
    stop();
    // TODO: reset behavior
  }
  _interval.update();

  return _state;
}

// Private
void Tracker::deploy() {
  Log.traceln("Tracker::deploy");
  _state = TrackerState::DEPLOY;
  _motors.deploy(_motorSetting->speed);
}

void Tracker::retract() {
  Log.traceln("Tracker::retract");
  _state = TrackerState::RETRACT;
  _motors.retract(_motorSetting->speed);
}

void Tracker::stop() {
  Log.traceln("Tracker::stop");
  _state = TrackerState::IDLE;
  _motors.stop();
}

bool Tracker::isManualMode() {
  return digitalRead(_modePin->manual) == HIGH;
}

void Tracker::onIntervalTick(void *ctx) {
  if (ctx == nullptr) {
    return;
  }

  Tracker *self = static_cast<Tracker *>(ctx);
  self->interval();
}

void Tracker::interval() {
  Log.traceln("Tracker::interval");
  LdrsComparison comparison = _ldrs.update();
  switch (comparison) {
  case LdrsComparison::UP_GREATER_THAN_DOWN:
    Log.traceln("Tracker::update - LDR UP_GREATER_THAN_DOWN");
    if (!isManualMode()) deploy();
    break;
  case LdrsComparison::DOWN_GREATER_THAN_UP:
    Log.traceln("Tracker::update - LDR DOWN_GREATER_THAN_UP");
    if (!isManualMode()) retract();
    break;
  case LdrsComparison::DEADBAND:
    Log.traceln("Tracker::update - LDR DEADBAND");
    break;
  default:
    break;
  }
}
