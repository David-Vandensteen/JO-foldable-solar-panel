#ifndef COMMAND_H
#define COMMAND_H
#include <Arduino.h>
#include <dv_dual_hold_state.h>
#include "setting.h"

enum class CommandState {
  RUNNING,
  STOPPED,
  RESET
};

class Command {
public:
  explicit Command(SettingBoardPinTrackerCommand *command);
  void init();
  CommandState update();

private:
  static void onStopHold(void *ctx);
  static void onResetHold(void *ctx);

  DV_DualHoldState _hold;
  CommandState _state = CommandState::RUNNING;
  SettingBoardPinTrackerCommand *_command;
};

#endif