# Code Review of src

## Scope

This review focuses on runtime behavior and board configuration consistency in `src/driver`.

## Findings

### 1. Medium: reset command path is acknowledged but not implemented

- Location: `src/driver/tracker.cpp`
- Issue: `Tracker::update()` now handles `CommandState::STOP` and `CommandState::RESET`, but the reset branch only stops motors and leaves a `TODO` instead of returning the tracker to a known initial position.
- Impact: a long hold can enter RESET state without performing any reset behavior, so the runtime contract remains incomplete.
- Verification: the `CommandState::RESET` branch logs, calls `stop()`, and ends with `// TODO: reset the tracker to initial position`.

### 2. Medium: tracker timing setting is passed but not used

- Location: `src/driver/tracker.cpp`, `src/driver/tracker.h`
- Issue: `SettingProgramTrackers *trackingSetting` is still accepted by the `Tracker` constructor but no field stores it and no timing gate uses it.
- Impact: configured tracker interval has no effect; control decisions run each loop.

### 3. Medium: deadband does not issue stop command

- Location: `src/driver/tracker.cpp`
- Issue: `ldrsComparison::Deadband` only logs and does not call `stop()`.
- Impact: motors may continue moving after returning to neutral range.

### 4. Low: manual mode pin is read without explicit initialization in Tracker

- Location: `src/driver/tracker.cpp`
- Issue: `isManualMode()` reads `_modePin->manual`, but no `pinMode` setup is visible in `Tracker::init()`.
- Impact: behavior depends on external wiring assumptions; susceptible to floating input if hardware pull resistors are absent.

### 5. Low: stale or unused code remains

- Location: `src/driver/ldr.h`, `src/driver/ldrs.h`, `src/driver/tracker.h`
- Issue:
  - `Ldr::raw` is declared but unused.
  - `LdrsComparison::NOT_UPDATED` is declared but never returned by current implementation.
  - `Tracker::sampling()` is declared but has no implementation and no usage.
- Impact: readability and intent clarity degrade.

## Verified Improvements Since Previous Pass

- Nano/ESP32 settings were aligned with `SettingProgramLDRs` and no longer reference removed `filter.smoothing` fields.
- Threshold is now used in `Ldrs::update()` through `delta` and `_threshold` deadband logic.
- Program naming is being normalized (`ldrs`, `motors`) and applied in core Uno path.
- `DV_DualHoldState` integration in `Command` now uses context-aware callbacks (`void*`) and no longer relies on a global active instance singleton.
- `Tracker` now owns a concrete `Command`, initializes it, and consumes `CommandState::STOP` / `CommandState::RESET` during `update()`.
- `Ldr` now uses `DV_EveryInterval` context callbacks (`setCallback(void (*)(void*), context)`), removing the previous lambda-to-function-pointer mismatch on AVR.
- Driver diagnostics currently show no active errors for the current workspace state.

## Test Gaps

- No automated test covers stop/reset button behavior in runtime loop.
- No test verifies tracker interval gating behavior.
- No test verifies deadband transition stops motors.
- No test verifies per-LDR sampling cadence across both sensors under load.
- No board-matrix compile check is present for Uno/Nano/ESP32 after recent settings-model changes.

## Conclusion

The codebase progressed on naming consistency, threshold usage, command integration, and callback compatibility on AVR, and board settings are structurally aligned. The main remaining risks are behavioral gaps in the active loop: reset behavior is still unfinished, tracker timing settings are not enforced, and deadband still does not actively stop motion.