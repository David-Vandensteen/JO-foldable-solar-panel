#include "motor.h"
#include "motors.h"

// Public
Motors::Motors(Motor m1, Motor m2, uint8_t speed, unsigned long timeout)
  : motor1(m1),
    motor2(m2),
    speed(speed),
    _timeout(timeout) {}

void Motors::init() {
  motor1.init();
  motor2.init();
  stop();
}

void Motors::deploy() {
  stop();
  if (_timeout > 0) {
    motor1.deployWithTimeOut(speed, _timeout);
    motor2.deployWithTimeOut(speed, _timeout);
  } else {
    motor1.deploy(speed);
    motor2.deploy(speed);
  }
}

void Motors::retract() {
  stop();
  if (_timeout > 0) {
    motor1.retractWithTimeOut(speed, _timeout);
    motor2.retractWithTimeOut(speed, _timeout);
  } else {
    motor1.retract(speed);
    motor2.retract(speed);
  }
}

void Motors::stop() {
  motor1.stop();
  motor2.stop();
}
