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
  explicit State(StateType stateType);
  StateType getState();
  void setState(StateType stateType);
  void setStateInitializing();
  void setStateRunning();
  void setStateStopped();
  void setStateError();

private:
  StateType _stateType = StateType::INITIALIZING;
};
#endif