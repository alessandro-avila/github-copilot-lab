---
name: 'Spec style'
description: 'How to write testable Given/When/Then specs for the legacy C modules'
applyTo: 'legacy-c/specs/**/*.md'
---

# Spec style

These rules load when Copilot works on a spec in `legacy-c/specs/`. The version with examples is [How to write a spec you can test](../../legacy-c/specs/README.md).

## Shape

Follow `legacy-c/specs/checksum.spec.md`: a two-line intro (what the spec covers, its status), numbered scenarios in one `gherkin` block, a Flagged table (scenario, today, question, decision), Not covered, Related. Put Givens that every scenario shares in a `Background`.

## Rules

| # | Rule |
| - | ---- |
| 1 | One behaviour per scenario |
| 2 | Concrete values: the real input and the exact result, never "a valid code" |
| 3 | Only observable results: a return value, a hardware call or a printed line. Never internal state, such as a counter |
| 4 | Plain domain words and present tense. No variable names, loops or other implementation details |
| 5 | Describe what the code does today. Tag odd behaviour `@flagged` and add a Flagged row; never fix it in the spec |
| 6 | Every scenario gets one test, with the scenario number in the test's comment |

## Related

- [How to write a spec you can test](../../legacy-c/specs/README.md)
