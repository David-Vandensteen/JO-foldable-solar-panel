#include <Arduino.h>
#include "command_state.h"

CommandState::CommandState() : _commandStateType(CommandStateType::IDLE) {}

CommandState::CommandState(CommandStateType commandStateType)
  : _commandStateType(commandStateType) {}

bool CommandState::isCommandStateStop() {
  return _commandStateType == CommandStateType::STOP;
}

bool CommandState::isCommandStateReset() {
  return _commandStateType == CommandStateType::RESET;
}

bool CommandState::isCommandStateIdle() {
  return _commandStateType == CommandStateType::IDLE;
}

CommandState CommandState::setCommandState(CommandStateType commandStateType) {
  _commandStateType = commandStateType;
  return *this;
}

CommandState CommandState::setCommandStateStop() {
  return setCommandState(CommandStateType::STOP);
}

CommandState CommandState::setCommandStateReset() {
  return setCommandState(CommandStateType::RESET);
}

CommandState CommandState::setCommandStateIdle() {
  return setCommandState(CommandStateType::IDLE);
}
