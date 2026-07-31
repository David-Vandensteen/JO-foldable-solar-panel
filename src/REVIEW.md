# Code Review of src

## Scope

This pass reviews runtime behavior, board configuration parity, and command/control flow in `src/driver`.

## Findings

### 1. Medium: command state is latched with no return to RUNNING

- Location: `src/driver/command.cpp`, `src/driver/tracker.cpp`
- Issue: callbacks set `_state` to `STOP`/`RESET`, but there is no path setting `_state` back to `RUNNING`.
- Impact: once STOP is triggered, tracker remains stopped permanently unless a full reset/reinit occurs.
- Verification: `Command::update()` only updates hold timing and returns `_state`; no state transition back to RUNNING exists.

## Verified Improvements

- Interval decision loop is now connected: `Tracker::update()` advances `_interval` and decisions run in `Tracker::interval()`.
- One-cycle stale decision risk was removed by sampling (`_ldrs.update()`) inside the interval callback.
- Deadband now actively stops motion when tracker is moving.
- Manual mode pin is explicitly initialized in `Tracker::init()`.
- Manual mode now forces stop and exits interval tick early, preventing residual motion after mode switch.
- `Ldr` callback wiring is now AVR-safe via context callbacks in `DV_EveryInterval`.
- Stale symbols were removed (`Ldr::raw`, `LdrsComparison::NOT_UPDATED`).
- Nano and ESP32 settings now initialize `program.trackers.interval`, matching validation requirements.

## Test Gaps

- No automated test for STOP -> RUNNING recovery semantics (or explicit latching contract).
- No board-matrix startup validation test for Uno/Nano/ESP32 to catch config drift.

## Conclusion

Core tracker timing, deadband handling, and board-config parity improved significantly. The main remaining runtime ambiguity is command-state latching (`STOP`/`RESET` with no explicit return to `RUNNING`). Clarifying or implementing that transition should be the next stabilization step.