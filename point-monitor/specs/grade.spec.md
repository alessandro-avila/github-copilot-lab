# Grade spec

This spec covers [grade.c](../grade.c): `grade()` takes how long one throw of the points took, in milliseconds, and grades it "ok", "slow" or "too slow".

**Status:** reviewed. [test_grade.c](../tests/test_grade.c) has one test per scenario.

## Scenarios

```gherkin
Scenario: 1. A normal throw is ok
  When you grade a throw of 3200 ms
  Then it is "ok"

Scenario: 2. A throw of 4500 ms is slow
  When you grade a throw of 4500 ms
  Then it is "slow"

Scenario: 3. A throw of 7000 ms is too slow
  When you grade a throw of 7000 ms
  Then it is "too slow"

Scenario: 4. A throw of exactly 4000 ms is still ok
  When you grade a throw of 4000 ms
  Then it is "ok"

Scenario: 5. A throw of exactly 6000 ms is slow, not too slow
  When you grade a throw of 6000 ms
  Then it is "slow"

@flagged
Scenario: 6. A throw of 0 ms is ok
  When you grade a throw of 0 ms
  Then it is "ok"

@flagged
Scenario: 7. A negative time is ok
  When you grade a throw of -50 ms
  Then it is "ok"
```

## Flagged

| Scenario | Today | Question | Decision |
| -------- | ----- | -------- | -------- |
| 6 | A throw of 0 ms is "ok" | 0 ms means the unit did not time the throw. Should the monitor raise an alert? | Keep. Maintenance to answer |
| 7 | A negative time is "ok" | Can the unit report a negative time, and what would it mean? | Keep. Ask the supplier of the unit |

## Not covered

- The limits are fixed in the code, 4000 ms and 6000 ms: nothing in the program changes them.
- How a grade turns into an alert: that is `monitor.c`, and its spec is yours to write.

## Related

- [How to write a spec you can test](README.md)
- [Point machine monitor](../README.md)
- [Challenge 3](../../challenges/03-point-monitor/README.md)
