---
name: rail-spec
description: Reverse engineers a module of the point machine monitor in point-monitor/. Explains step by step what it does, with a Mermaid flowchart, then writes a reviewable Given/When/Then spec of what the code does today. Use when asked to explain, describe, document, reverse engineer or write a spec for monitor.c or grade.c.
argument-hint: the module to reverse engineer, e.g. point-monitor/grade.c (default point-monitor/monitor.c)
---

# Rail spec

Reverse engineer a module of the point machine monitor: first explain what it does **today**, then write it down as a spec that a person can review and a test can check.

Use the file the user named or attached. If there is none, use `point-monitor/monitor.c`.

## Steps

### Part 1: reverse engineer, in the chat

1. Read the module's `.c` and `.h` files and the functions it calls.
2. Explain step by step, in plain words, what one call of its main function does: for the monitor, `monitor_step()`. Give the file and line for every step.
3. Draw a Mermaid flowchart of one call, with every decision, every return value and every alert.
4. Read "What maintenance expects" in [point-monitor/README.md](../../../point-monitor/README.md) and list where the code does something else. Describe it; do not fix it.

### Part 2: write the spec

1. Read [How to write a spec you can test](../../../point-monitor/specs/README.md) and the model spec [grade.spec.md](../../../point-monitor/specs/grade.spec.md).
2. For the monitor, read [fake_mu.h](../../../point-monitor/tests/fake_mu.h) too: it shows what a test can set and check.
3. Where the code does something other than what maintenance expects, describe what the code does and tag the scenario `@flagged`.
4. Write `point-monitor/specs/<module>.spec.md` in the same shape and by the same rules. Set the status to "draft".
5. Give every `@flagged` scenario a row in the Flagged table, and leave the Decision column empty for the reviewers.

## Rules

- Describe current behaviour, even when it looks like a bug. Do not propose fixes.
- Do not edit any `.c` or `.h` file.
- Do not guess. If you cannot tell from the code what happens, say so in the explanation and put it under Not covered in the spec.
- The explanation and the flowchart stay in the chat. The spec keeps its usual shape.
- Work from the code and the files above only. Do not open `challenges/`: it holds the reference solutions.

## Finish by

Showing a table of the scenarios (number, title, flagged or not), then asking the user to check the explanation against the output of `monitor_app` and to review the spec before anyone writes tests.
