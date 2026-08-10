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
  CommandStateType getCommandStateType();
  bool isCommandStateStop();
  bool isCommandStateReset();
  bool isCommandStateIdle();
  CommandState setCommandState(CommandStateType commandStateType);
  CommandState setCommandStateStop();
  CommandState setCommandStateReset();
  CommandState setCommandStateIdle();
private:
  CommandStateType _commandStateType = CommandStateType::IDLE;
};


#endif