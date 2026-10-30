# How to write a spec you can test

A spec describes what a module of the point machine monitor does today, in numbered Given/When/Then scenarios: clear enough for anyone to review, and exact enough to become one test per scenario.

These are the same six rules as for the parcel sorter in [legacy-c/specs](../../legacy-c/specs/README.md), with examples from the monitor. [grade.spec.md](grade.spec.md) is the model.

## Shape

| Part | What goes in it |
| ---- | --------------- |
| Intro | Two lines: what the spec covers, and its status. A spec stays a draft until a person has reviewed it |
| Scenarios | One `gherkin` block with numbered scenarios. Givens that every scenario shares go in a `Background` |
| Flagged | One row per `@flagged` scenario: the scenario, what the code does today, the question it raises, the decision |
| Not covered | What the spec leaves out, and why |
| Related | Links to the code, the tests and the other specs |

## Rules

| # | Rule | Good | Bad |
| - | ---- | ---- | --- |
| 1 | One behaviour per scenario, so a failing test tells you what broke | `Scenario: 2. A throw of 4500 ms is slow` | `Scenario: 2. Slow and too-slow throws` |
| 2 | Concrete values: the real input and the exact result | `Given points P101 move in 4500 ms` | `Given a slow throw` |
| 3 | Only observable results: a return value or an alert the unit sends. Never internal state, such as a counter | `Then it sends a warning for points P101` | `Then the slow count goes up by one` |
| 4 | Plain words, present tense, no code details | `When the monitor takes the next throw` | `When monitor_step() calls grade()` |
| 5 | Describe what the code does today. Tag odd behaviour `@flagged` and put the question in the Flagged table; never fix it in the spec | `@flagged` and today's result | What someone thinks the code should do |
| 6 | One test per scenario, with the scenario number in the test's comment | `/* Scenario 3 */` | One test for several scenarios |

The tests check return values and the alerts the fake monitoring unit records. The harness cannot capture printed lines, so list those under Not covered.

## Related

- [Grade spec](grade.spec.md), the model
- [Point machine monitor](../README.md)
- [Challenge 3](../../challenges/03-point-monitor/README.md)
