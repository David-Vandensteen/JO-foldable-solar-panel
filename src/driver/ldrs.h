#ifndef LDRS_H
#define LDRS_H
#include "ldr.h"

enum class LdrsComparison {
  UP_GREATER_THAN_DOWN,
  DOWN_GREATER_THAN_UP,
  DEADBAND,
  NOT_UPDATED
};

class Ldrs {
public:
  Ldr up;
  Ldr down;
  explicit Ldrs(Ldr up, Ldr down, uint8_t threshold);
  void init();
  LdrsComparison update();

private:
  uint8_t _threshold;
};

#endif