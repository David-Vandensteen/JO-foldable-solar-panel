#ifndef COMMAND_STATE_H
#define COMMAND_STATE_H
#include <Arduino.h>

enum class CommandStateType {
  IDLE,
  STOP,
  RESET
};

class CommandState {
public:
  explicit CommandState();
  explicit CommandState(CommandStateType commandStateType);
  bool isStateStop();
  bool isStateReset();
  bool isStateIdle();
  CommandState setState(CommandStateType commandStateType);
  CommandState setStateStop();
  CommandState setStateReset();
  CommandState setStateIdle();
private:
  CommandStateType _commandStateType = CommandStateType::IDLE;
};

#endif