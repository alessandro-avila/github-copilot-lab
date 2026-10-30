# Monitor spec (reference solution)

This spec covers `monitor_step()` in [monitor.c](../../../point-monitor/monitor.c): each step takes the next throw from the monitoring unit and returns "no throw", "no alert", "warning" or "alarm".

**Status:** reviewed. [test_monitor.c](test_monitor.c) has one test per scenario and uses the provided fake monitoring unit.

## Scenarios

```gherkin
Background:
  Given a freshly started monitor
  And the time is 10:00

Scenario: 1. Without a throw the monitor does nothing
  Given the unit reports no throw
  When the monitor runs one step
  Then the step returns "no throw"
  And the monitor sends no alert

Scenario: 2. A normal throw sends no alert
  Given points P101 move in 3200 ms
  When the monitor runs one step
  Then the step returns "no alert"
  And the monitor sends no alert

Scenario: 3. A slow throw sends a warning
  Given points P101 move in 4500 ms
  When the monitor runs one step
  Then it sends a warning for points P101

Scenario: 4. A throw that is too slow sends an alarm
  Given points P101 move in 7000 ms
  When the monitor runs one step
  Then it sends an alarm for points P101

Scenario: 5. The third slow throw in a row sends an alarm
  Given points P101 move in 4500 ms, then 4600 ms, then 4700 ms
  When the monitor runs three steps
  Then the third step sends an alarm for points P101

Scenario: 6. A normal throw starts the count again
  Given points P101 move in 4500 ms, 4600 ms, 3200 ms, then 4700 ms
  When the monitor runs four steps
  Then the fourth step sends a warning for points P101

@flagged
Scenario: 7. Slow throws on different points add up
  Given points P101 move in 4500 ms, then P102 in 4600 ms, then P103 in 4700 ms
  When the monitor runs three steps
  Then the third step sends an alarm for points P103

@flagged
Scenario: 8. A normal throw on other points starts the count again
  Given points P101 move in 4500 ms and 4600 ms, then P102 in 3200 ms, then P101 in 4700 ms
  When the monitor runs four steps
  Then the fourth step sends a warning for points P101

@flagged
Scenario: 9. At 23:30, during the night possession, a slow throw sends a warning
  Given the time is 23:30
  And points P101 move in 4500 ms
  When the monitor runs one step
  Then it sends a warning for points P101

@flagged
Scenario: 10. At 02:00, during the night possession, a throw that is too slow sends an alarm
  Given the time is 02:00
  And points P101 move in 7000 ms
  When the monitor runs one step
  Then it sends an alarm for points P101

@flagged
Scenario: 11. After an alarm, the next slow throw sends a warning
  Given points P101 move in 4500 ms, 4600 ms, 4700 ms, then 4800 ms
  When the monitor runs four steps
  Then the fourth step sends a warning for points P101
```

## Flagged

| Scenario | Today | Question | Decision |
| -------- | ----- | -------- | -------- |
| 7 | One count for all points: P103 gets an alarm after a single slow throw. The program output shows the same for P105 | Maintenance expects three slow throws in a row on the same points. Is this a bug? | Fix through a ticket: count per points |
| 8 | A normal throw on any points restarts the count: P101's third slow throw in a row sends only a warning | Same as 7, and worse: an alarm goes missing | Fix with 7 |
| 9 | At 23:30 the monitor sends alerts | Maintenance expects no alerts from 23:00 to 03:00. Why does the check never match? | Fix: the window crosses midnight (the stretch) |
| 10 | At 02:00 the monitor sends alerts | Same as 9 | Fix with 9 |
| 11 | An alarm starts the count again, so continuing slow throws give warning, warning, alarm, warning | Should every slow throw after an alarm raise another alarm until a normal throw? | Keep. Maintenance to answer |

## Not covered

- Printed lines: the tests do not check console output.
- Points names of 8 characters or more: the unit reports "no throw", and the main loop stops. No scenario pins this down yet; ask the supplier of the unit for the longest name.
- A throw that is too slow also starts the count again. No scenario pins this down yet.
- The clock reports whole hours, so 03:00 to 03:59 counts as hour 3.

## Related

- [Reference solution](README.md)
- [How to write a spec you can test](../../../point-monitor/specs/README.md)
- [Challenge 3](../README.md)
