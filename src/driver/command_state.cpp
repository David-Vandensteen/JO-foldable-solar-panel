#include <Arduino.h>
#include "command_state.h"

// Public
CommandState::CommandState() : _commandStateType(CommandStateType::IDLE) {}

CommandState::CommandState(CommandStateType commandStateType)
  : _commandStateType(commandStateType) {}

bool CommandState::isStateStop() {
  return _commandStateType == CommandStateType::STOP;
}

bool CommandState::isStateReset() {
  return _commandStateType == CommandStateType::RESET;
}

bool CommandState::isStateIdle() {
  return _commandStateType == CommandStateType::IDLE;
}

bool CommandState::isStateInitializing() {
  return _commandStateType == CommandStateType::INITIALIZING;
}

CommandState CommandState::setState(CommandStateType commandStateType) {
  _commandStateType = commandStateType;
  return *this;
}

CommandState CommandState::setStateStop() {
  return setState(CommandStateType::STOP);
}

CommandState CommandState::setStateReset() {
  return setState(CommandStateType::RESET);
}

CommandState CommandState::setStateIdle() {
  return setState(CommandStateType::IDLE);
}

CommandState CommandState::setStateInitializing() {
  return setState(CommandStateType::INITIALIZING);
}
