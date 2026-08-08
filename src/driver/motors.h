#ifndef MOTORS_H
#define MOTORS_H
#include "motor.h"

class Motors {
public:
	explicit Motors(
    Motor m1,
    Motor m2,
    uint8_t speed,
    unsigned long timeout = 0
  );
  void init();
	void deploy();
	void retract();
  void stop();
	Motor motor1;
	Motor motor2;

private:
  unsigned long _timeout = 0;
  uint8_t speed;
};

#endif