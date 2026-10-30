# Review findings (reference)

This is one possible result of Step 2: what a review of [monitor.c](../../../point-monitor/monitor.c) should find, sorted into defect, question or style, with the decision the pair made.

| # | Where | Finding | Kind | Scenario that exposes it | Decision |
| - | ----- | ------- | ---- | ------------------------ | -------- |
| 1 | `monitor.c:13`, `38` | One counter `n` for all points: slow throws on different points add up, and a normal throw on any points resets it | Defect | Spec 7 and 8 | Fix through a ticket: count per points |
| 2 | `monitor.c:30` | `h >= 23 && h < 3` is never true: the night possession crosses midnight, so the monitor alerts all night | Defect | Spec 9 and 10 | Fix: `h >= 23 \|\| h < 3` (the stretch) |
| 3 | `monitor.c:44` | An alarm resets the count, so continuing slow throws give warning, warning, alarm, warning | Question | Spec 11 | Ask maintenance |
| 4 | `monitor.c:22`, `25` | Points names of 8 characters or more come back as "no throw", and the main loop stops | Question | Not covered in the spec | Ask the supplier of the unit for the longest name |
| 5 | `grade.c:16` | 0 ms and negative times grade "ok" | Question | Grade spec 6 and 7 | Ask maintenance and the supplier |
| 6 | `monitor.c:38` | The count goes up inside the `if`, and only for slow throws: easy to misread | Style | — | Rewrite when you fix finding 1 |
| 7 | Everywhere | Magic numbers `3`, `23`, `4000`, `6000`; short names `n`, `t`, `g`, `h`, `pt` | Style | — | Name them when you touch the code |
| 8 | `monitor.c:43` | `printf` mixed in with the logic | Style | — | Keep |

## Talking points

| Question | What to look for |
| -------- | ---------------- |
| Which defect is worse? | Finding 1 also hides alarms (spec 8): points that need a technician get only a warning |
| Did the reviewer quote the maintenance rule it compared against? | A finding with evidence is easy to check; "might be a problem" is not |
| Would a compiler have caught finding 2? | No: MSVC `/W4` and gcc `-Wall -Wextra` build this code without a warning |
| Did a finding need a test to settle it? | Turn each defect into a scenario first, then into a test |

## Related

- [How the monitor works](how-it-works.md)
- [Monitor spec](monitor.spec.md)
- [Code reviewer agent](../../../.github/agents/code-reviewer.agent.md)
