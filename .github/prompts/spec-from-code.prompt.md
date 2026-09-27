---
name: 'spec-from-code'
description: 'Describe what a legacy C module does today as a clean Given/When/Then spec'
argument-hint: 'the module to describe, e.g. legacy-c/sorter.c'
agent: 'agent'
---

# Spec from code

Write down what a module does **today** as a spec that a person can review and a test can check.

Use the file the user named or attached. If there is none, ask which module in `legacy-c/` to describe, and stop.

## Steps

1. Read [How to write a spec you can test](../../legacy-c/specs/README.md) and the two model specs, [checksum.spec.md](../../legacy-c/specs/checksum.spec.md) and [route.spec.md](../../legacy-c/specs/route.spec.md).
2. Read the module's `.c` and `.h` files and the functions it calls in `legacy-c/`. For the sorter, read [fake_hw.h](../../legacy-c/tests/fake_hw.h) too: it shows what a test can set and check.
3. Write `legacy-c/specs/<module>.spec.md` in the same shape and by the same rules. Set the status to "draft".
4. Tag odd behaviour `@flagged`, give it a row in the Flagged table, and leave the Decision column empty for the reviewer.

## Rules

- Describe current behaviour, even when it looks like a bug. Do not propose fixes.
- Do not edit any `.c` or `.h` file.
- Do not guess. If you cannot tell from the code what happens, put it under Not covered.
- Work from the code only. Do not open `challenges/`: it holds the reference solutions.

## Finish by

Showing a table of the scenarios (number, title, flagged or not), then asking the user to review the spec before anyone writes tests.

## Related

- [How to write a spec you can test](../../legacy-c/specs/README.md)
- [Tests from spec](tests-from-spec.prompt.md), the next step
