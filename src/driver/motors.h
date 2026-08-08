#ifndef MOTORS_H
#define MOTORS_H
#include "motor.h"

class Motors {
public:
	explicit Motors(
    Motor motor1,
    Motor motor2,
    uint8_t speed,
    unsigned long timeout = 0
  );
  void init();
	void deploy();
	void retract();
  void stop();

private:
	Motor _motor1;
	Motor _motor2;
  unsigned long _timeout = 0;
  uint8_t _speed;
};

#endif