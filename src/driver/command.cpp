#include <Arduino.h>
#include <ArduinoLog.h>
#include <dv_dual_hold_state.h>
#include "command.h"
#include "setting.h"

void Command::onStopHold(void *ctx) {
  if (ctx == nullptr) {
    return;
  }
  Command *self = static_cast<Command *>(ctx);
  Log.noticeln("Command::stop pressed");
  self->_state = CommandState::STOP;
}

void Command::onResetHold(void *ctx) {
  if (ctx == nullptr) {
    return;
  }
  Command *self = static_cast<Command *>(ctx);
  Log.noticeln("Command::stop reset");
  self->_state = CommandState::RESET;
}

Command::Command(SettingBoardPinTrackerCommand *command)
  : _command(command) {}

void Command::init() {
  Log.traceln("Command::init");
  Log.noticeln("Initializing command");
  pinMode(_command->stop, INPUT_PULLUP);
  _hold.init(
    500,
    Command::onStopHold,
    1000,
    Command::onResetHold,
    this,
    this
  );
}

CommandState Command::getState() {
  return _state;
}

CommandState Command::update() {
  _hold.update(digitalRead(_command->stop) == LOW);
  return _state;
}
