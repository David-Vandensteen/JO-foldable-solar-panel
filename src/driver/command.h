#ifndef COMMAND_H
#define COMMAND_H
#include <Arduino.h>
#include <dv_dual_hold_state.h>
#include "setting.h"
#include "command_state.h"

class Command {
public:
  explicit Command(SettingBoardPinTrackerCommand *command);
  void init();
  CommandState getState();
  CommandState update();

private:
  static void onStopHold(void *ctx);
  static void onResetHold(void *ctx);

  DV_DualHoldState _hold;
  CommandState _state;
  SettingBoardPinTrackerCommand *_command;
};

#endif