#ifndef LDRS_H
#define LDRS_H
#include "ldr.h"
#include "setting.h"

enum class LdrsComparison {
  UP_GREATER_THAN_DOWN,
  DOWN_GREATER_THAN_UP,
  DEADBAND
};

class Ldrs {
public:
  Ldr ldrUp;
  Ldr ldrDown;
  explicit Ldrs(Ldr ldrUp, Ldr ldrDown, SettingProgramLDRs *settingProgramLDRs);
  LdrsComparison getComparison();
  LdrsComparison update();
  void init();

private:
  SettingProgramLDRs *_settingProgramLDRs;
};

#endif