#ifndef LDRS_H
#define LDRS_H
#include "ldr.h"
#include "setting.h"

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
  explicit Ldrs(Ldr up, Ldr down, SettingProgramLDRs *ldrSetting);
  LdrsComparison getComparison();
  LdrsComparison update();
  void init();

private:
  SettingProgramLDRs *_ldrSetting;
};

#endif