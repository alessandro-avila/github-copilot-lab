# Reference solution

This folder holds one possible answer to Challenge 3; compare it with your own after you try, not before.

| File | Step | What it is |
| ---- | ---- | ---------- |
| [how-it-works.md](how-it-works.md) | 1 | One monitor step as a flowchart, and today's behaviour against what maintenance expects |
| [review.md](review.md) | 2 | The review findings, sorted into defect, question and style, with decisions |
| [monitor.spec.md](monitor.spec.md) | 1, 2 | What `monitor_step()` does today: eleven scenarios, five of them flagged |
| [test_monitor.c](test_monitor.c) | 3 | One test per monitor scenario, with the provided fake monitoring unit |

The tests build against the unchanged code in `point-monitor/`.

## Run it

```
cmake -S point-monitor -B build-pm -DWITH_SOLUTION=ON
cmake --build build-pm
ctest --test-dir build-pm -C Debug -R solution --output-on-failure
```

## The stretch, step by step

| Step | Change | Result |
| ---- | ------ | ------ |
| 1. Spec | Scenarios 9 and 10: the step returns "no alert", and the monitor sends no alert | Reviewed by the pair |
| 2. Tests | Tests 9 and 10 check for return value 1 and no alert | Both fail on today's code |
| 3. Code | In `monitor.c`, `if (h >= 23 && h < 3)` becomes `if (h >= 23 \|\| h < 3)` | All eleven tests pass |

## Talking points for show and tell

| Question | What to look for |
| -------- | ---------------- |
| Did your spec find the count shared by all points? | Scenario 7. The program output shows it: P105 gets an alarm after one slow throw |
| Did anyone spot the missing alarm? | Scenario 8: the same defect hides an alarm, which matters more than a false one |
| Did a Then line name the counter? | Rule 3: rewrite it as a return value or an alert, which a test can check |
| Did Copilot fix something while it wrote the spec or the tests? | That skips a step. Behaviour changes come last, spec first |

## Related

- [Challenge 3](../README.md)
- [How to write a spec you can test](../../../point-monitor/specs/README.md)
