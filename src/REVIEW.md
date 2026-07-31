# Code Review of src

## Scope

This review focuses on runtime behavior and board configuration consistency in `src/driver`.

## Findings

### 1. Medium: reset command path is acknowledged but not implemented

- Location: `src/driver/tracker.cpp`
- Issue: `Tracker::update()` now handles `CommandState::STOP` and `CommandState::RESET`, but the reset branch only stops motors and leaves a `TODO` instead of returning the tracker to a known initial position.
- Impact: a long hold can enter RESET state without performing any reset behavior, so the runtime contract remains incomplete.
- Verification: the `CommandState::RESET` branch logs, calls `stop()`, and ends with `// TODO: reset the tracker to initial position`.

### 2. Medium: deadband does not issue stop command

- Location: `src/driver/tracker.cpp`
- Issue: in `Tracker::interval()`, the `LdrsComparison::DEADBAND` branch only logs and does not call `stop()`.
- Impact: when interval execution is restored, motors may continue moving after returning to neutral range.

## Verified Improvements Since Previous Pass

- Nano/ESP32 settings were aligned with `SettingProgramLDRs` and no longer reference removed `filter.smoothing` fields.
- Threshold is now used in `Ldrs::update()` through `delta` and `_threshold` deadband logic.
- Program naming is being normalized (`ldrs`, `motors`) and applied in core Uno path.
- `DV_DualHoldState` integration in `Command` now uses context-aware callbacks (`void*`) and no longer relies on a global active instance singleton.
- `Tracker` now owns a concrete `Command`, initializes it, and consumes `CommandState::STOP` / `CommandState::RESET` during `update()`.
- `Ldr` now uses `DV_EveryInterval` context callbacks (`setCallback(void (*)(void*), context)`), removing the previous lambda-to-function-pointer mismatch on AVR.
- `Tracker` now includes `DV_EveryInterval` plumbing plus a dedicated `interval()` decision path based on `Ldrs::getComparison()`.
- `Tracker::update()` now calls `_interval.update()`, so interval callbacks are executed at runtime.
- `Tracker` decisions now run on fresh values inside `Tracker::interval()` via `_ldrs.update()`, removing the previous one-cycle stale-decision risk.
- `Tracker::init()` now explicitly configures the manual mode pin with `pinMode(_modePin->manual, INPUT)` before reads.
- Stale symbols were cleaned up: unused `Ldr::raw` and `LdrsComparison::NOT_UPDATED` were removed.
- Driver diagnostics currently show no active errors for the current workspace state.

## Test Gaps

- No automated test covers stop/reset button behavior in runtime loop.
- No test verifies deadband transition stops motors.
- No test verifies per-LDR sampling cadence across both sensors under load.
- No board-matrix compile check is present for Uno/Nano/ESP32 after recent settings-model changes.

## Conclusion

The codebase progressed on naming consistency, threshold usage, command integration, and callback compatibility on AVR, and board settings are structurally aligned. The main remaining risks are runtime behavior gaps: reset behavior is unfinished and deadband still does not actively stop motion.