#ifndef STATE_H
#define STATE_H
#include <Arduino.h>

enum class StateType {
  INITIALIZING,
  RUNNING,
  STOPPED,
  ERROR
};

class State {
public:
  explicit State();
  explicit State(StateType stateType);
  StateType getStateType();
  bool isStateInitializing();
  bool isStateRunning();
  bool isStateStopped();
  bool isStateError();
  State setState(StateType stateType);
  State setStateInitializing();
  State setStateRunning();
  State setStateStopped();
  State setStateError();

private:
  StateType _stateType = StateType::INITIALIZING;
};
#endif