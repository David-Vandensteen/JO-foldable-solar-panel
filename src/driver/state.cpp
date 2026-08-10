#include <Arduino.h>
#include "state.h"

State::State() : _stateType(StateType::INITIALIZING) {}
State::State(StateType stateType) : _stateType(stateType) {}

StateType State::getState() {
  return _stateType;
}

bool State::isStateInitializing() {
  return _stateType == StateType::INITIALIZING;
}

bool State::isStateRunning() {
  return _stateType == StateType::RUNNING;
}

bool State::isStateStopped() {
  return _stateType == StateType::STOPPED;
}

bool State::isStateError() {
  return _stateType == StateType::ERROR;
}

void State::setState(StateType stateType) {
  _stateType = stateType;
}

void State::setStateInitializing() {
  setState(StateType::INITIALIZING);
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
