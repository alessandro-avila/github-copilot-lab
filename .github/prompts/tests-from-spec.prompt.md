---
name: 'tests-from-spec'
description: 'Write one test per scenario of a reviewed legacy C spec, then build and run them'
argument-hint: 'the spec to test, e.g. legacy-c/specs/route.spec.md'
agent: 'agent'
---

# Tests from spec

Turn every scenario in a reviewed spec into one test, so that the tests pin down what the code does today.

Use the spec the user named or attached. If there is none, ask which spec in `legacy-c/specs/` to use, and stop. If its status still says draft, ask the user to review it first.

## Steps

1. Read the spec, the module it describes, [test.h](../../legacy-c/tests/test.h) and the worked example [test_checksum.c](../../legacy-c/tests/test_checksum.c).
2. Write `legacy-c/tests/test_<module>.c`: one `static void` test per scenario, named after the scenario, with the scenario number in the comment above it. `CMakeLists.txt` picks up `test_route.c` and `test_sorter.c` by name, so do not edit it.
3. For the sorter, use the provided fake hardware in [fake_hw.h](../../legacy-c/tests/fake_hw.h). Start every test with `fake_hw_reset()` and `sorter_init()`: that is the spec's Background.
4. Build and run the tests with the commands below.
5. If a test fails, the test or the spec is wrong, not the code. Fix the test to match what the code does, and tell the user which scenario needs correcting.

## Rules

- Do not change production code, the `.c` and `.h` files directly in `legacy-c/`, or the provided files in `legacy-c/tests/`.
- Use only the harness in `test.h`: `CHECK`, `CHECK_EQ`, `CHECK_STR_EQ`, `RUN` and `TEST_SUMMARY`.
- Check only what the scenario's Then lines say.
- Tests must pass in any order. Undo every change a test makes to global state.
- Mark flagged scenarios with the comment `flagged: see spec`, and test them as they behave today.
- Work from the spec and the code only. Do not open `challenges/`: it holds the reference solutions.

## Build and run

From the repository root, run all three commands every time. The first one picks up new test files.

```
cmake -S legacy-c -B build
cmake --build build
ctest --test-dir build -C Debug --output-on-failure
```

If `cmake` is not found, run the commands in a Developer Command Prompt or Developer PowerShell for Visual Studio.

## Finish by

Reporting a table of scenario, test function and result (pass or fail). Then list any scenario you could not test, and why.

## Related

- [How to write a spec you can test](../../legacy-c/specs/README.md)
- [Spec from code](spec-from-code.prompt.md), the step before
