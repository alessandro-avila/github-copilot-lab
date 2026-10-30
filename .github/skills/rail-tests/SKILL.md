---
name: rail-tests
description: Writes one C test per scenario of a reviewed point-monitor spec, then builds and runs them. Use when asked to create, generate or write tests for the point machine monitor from a spec.
argument-hint: the reviewed spec, e.g. point-monitor/specs/monitor.spec.md
---

# Rail tests

Turn every scenario of a reviewed spec into one test, so that the tests pin down what the code does today.

Use the spec the user named or attached. If there is none, ask which spec in `point-monitor/specs/` to use, and stop. If its status still says draft, ask the user to review it first.

## Steps

1. Read the spec, the module it describes, [test.h](../../../point-monitor/tests/test.h) and the worked example [test_grade.c](../../../point-monitor/tests/test_grade.c).
2. Write `point-monitor/tests/test_<module>.c`: one `static void` test per scenario, named after the scenario, with the scenario number in the comment above it. `CMakeLists.txt` picks up `test_monitor.c` by name, so do not edit it.
3. For the monitor, use the provided fake monitoring unit in [fake_mu.h](../../../point-monitor/tests/fake_mu.h). Start every test with `fake_mu_reset()` and `monitor_init()`: that is the spec's Background.
4. Build and run the tests with the commands below.
5. If a test fails, the test or the spec is wrong, not the code. Fix the test to match what the code does, and tell the user which scenario needs correcting.

One exception to step 5: when the Decision column in the Flagged table says "Fix", the scenario describes the behaviour the team wants. Write its test for that behaviour, expect it to fail, and say so. Change the code only when the user asks.

## Rules

- Do not change production code, the `.c` and `.h` files directly in `point-monitor/`, or the provided files in `point-monitor/tests/`.
- Use only the harness in `test.h`: `CHECK`, `CHECK_EQ`, `CHECK_STR_EQ`, `RUN` and `TEST_SUMMARY`.
- Check only what the scenario's Then lines say.
- Tests must pass in any order: every test starts from the Background.
- Mark flagged scenarios with the comment `flagged: see spec`, and test them as they behave today.
- Work from the spec and the code only. Do not open `challenges/`: it holds the reference solutions.

## Build and run

From the repository root, run all three commands every time. The first one picks up new test files.

```
cmake -S point-monitor -B build-pm
cmake --build build-pm
ctest --test-dir build-pm -C Debug --output-on-failure
```

If `cmake` is not found, run the commands in a Developer Command Prompt or Developer PowerShell for Visual Studio.

## Finish by

Reporting a table of scenario, test function and result (pass or fail). Then list any scenario you could not test, and why.
