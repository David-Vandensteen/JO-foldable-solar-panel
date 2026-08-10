#include <Arduino.h>
#include "state.h"

State::State(StateType stateType) : _stateType(stateType) {}

StateType State::getState() {
  return _stateType;
}

void State::setState(StateType stateType) {
  _stateType = stateType;
}

void State::setStateRunning() {
  setState(StateType::RUNNING);
}

void State::setStateStopped() {
  setState(StateType::STOPPED);
}

void State::setStateError() {
  setState(StateType::ERROR);
}
