#include "motor.h"
#include "motors.h"

// Public
Motors::Motors(
  Motor motor1,
  Motor motor2,
  uint8_t speed,
  unsigned long timeout
)
  : _motor1(motor1),
    _motor2(motor2),
    _speed(speed),
    _timeout(timeout) {}

void Motors::init() {
  _motor1.init();
  _motor2.init();
  stop();
}

void Motors::deploy() {
  stop();
  if (_timeout > 0) {
    _motor1.deployWithTimeOut(_speed, _timeout);
    _motor2.deployWithTimeOut(_speed, _timeout);
  } else {
    _motor1.deploy(_speed);
    _motor2.deploy(_speed);
  }
}

void Motors::retract() {
  stop();
  if (_timeout > 0) {
    _motor1.retractWithTimeOut(_speed, _timeout);
    _motor2.retractWithTimeOut(_speed, _timeout);
  } else {
    _motor1.retract(_speed);
    _motor2.retract(_speed);
  }
}

void Motors::stop() {
  _motor1.stop();
  _motor2.stop();
}
