#include "motor.h"
#include "motors.h"

// Public
Motors::Motors(Motor m1, Motor m2, uint8_t speed)
  : motor1(m1), motor2(m2), speed(speed) {}

void Motors::init() {
  motor1.init();
  motor2.init();
  stop();
}

void Motors::deploy() {
  stop();
  motor1.deploy(speed);
  motor2.deploy(speed);
}

void Motors::retract() {
  stop();
  motor1.retract(speed);
  motor2.retract(speed);
}

void Motors::stop() {
  motor1.stop();
  motor2.stop();
}
