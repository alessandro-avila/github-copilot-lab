---
name: rail-spec
description: Reverse engineers a module of the point machine monitor in point-monitor/ into a reviewable Given/When/Then spec of what the code does today. Use when asked to describe, document, reverse engineer or write a spec for monitor.c or grade.c.
argument-hint: the module to describe, e.g. point-monitor/monitor.c
---

# Rail spec

Write down what a module of the point machine monitor does **today**, as a spec that a person can review and a test can check.

Use the file the user named or attached. If there is none, ask which module in `point-monitor/` to describe, and stop.

## Steps

1. Read [How to write a spec you can test](../../../point-monitor/specs/README.md) and the model spec [grade.spec.md](../../../point-monitor/specs/grade.spec.md).
2. Read the module's `.c` and `.h` files and the functions it calls. For the monitor, read [fake_mu.h](../../../point-monitor/tests/fake_mu.h) too: it shows what a test can set and check.
3. Read "What maintenance expects" in [point-monitor/README.md](../../../point-monitor/README.md). Where the code does something else, describe what the code does and tag the scenario `@flagged`.
4. Write `point-monitor/specs/<module>.spec.md` in the same shape and by the same rules. Set the status to "draft".
5. Give every `@flagged` scenario a row in the Flagged table, and leave the Decision column empty for the reviewers.

## Rules

- Describe current behaviour, even when it looks like a bug. Do not propose fixes.
- Do not edit any `.c` or `.h` file.
- Do not guess. If you cannot tell from the code what happens, put it under Not covered.
- Work from the code and the files above only. Do not open `challenges/`: it holds the reference solutions.

## Finish by

Showing a table of the scenarios (number, title, flagged or not), then asking the user to review the spec before anyone writes tests.
