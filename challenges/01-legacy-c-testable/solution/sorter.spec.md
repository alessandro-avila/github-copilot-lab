# Sorter spec (reference solution)

This spec covers `sorter_step()` in [sorter.c](../../../legacy-c/sorter.c): each step reads the parcel at the scanner once and returns "no parcel", "read again", "sorted" or "gave up".

**Status:** reviewed. [test_sorter.c](test_sorter.c) has one test per scenario and uses the provided fake hardware.

## Scenarios

```gherkin
Background:
  Given a freshly started sorter
  And the time is 10:00 UTC

Scenario: 1. Without a parcel the sorter does nothing
  Given no parcel at the scanner
  When the sorter runs one step
  Then the step returns "no parcel"
  And the sorter reads, diverts and releases nothing

Scenario: 2. A readable parcel goes into its chute
  Given a parcel whose label reads "30123458"
  When the sorter runs one step
  Then it diverts the parcel into chute 3

Scenario: 3. After a failed read the sorter reads again
  Given a parcel with an unreadable label
  When the sorter runs one step
  Then the step returns "read again"
  And the sorter neither diverts nor releases the parcel

@flagged
Scenario: 4. After five failed reads the sorter gives up
  Given a parcel with an unreadable label
  When the sorter runs five steps
  Then the fifth step releases the parcel to the end of the belt

@flagged
Scenario: 5. A wrong check digit counts as a failed read
  Given a parcel whose label reads "30123459"
  When the sorter runs one step
  Then the step returns "read again"
  And the sorter does not divert the parcel

Scenario: 6. A parcel read on the third try goes into its chute
  Given a parcel whose label reads "30123458" only on the third read
  When the sorter runs three steps
  Then the third step diverts the parcel into chute 3

@flagged
Scenario: 7. The next parcel inherits the failed reads
  Given the sorter diverted parcel "30123458" on its third read
  And right behind it comes a parcel with an unreadable label
  When the sorter runs three more steps
  Then the third of them releases that parcel to the end of the belt

Scenario: 8. A parcel without a route goes into chute 9
  Given a parcel whose label reads "55123457"
  When the sorter runs one step
  Then it diverts the parcel into chute 9

Scenario: 9. At 17:59 UTC a parcel still goes into its own chute
  Given the time is 17:59 UTC
  And a parcel whose label reads "30123458"
  When the sorter runs one step
  Then it diverts the parcel into chute 3

@flagged
Scenario: 10. From 18:00 UTC every parcel goes into chute 8
  Given the time is 18:00 UTC
  And a parcel whose label reads "30123458"
  When the sorter runs one step
  Then it diverts the parcel into chute 8
```

## Flagged

| Scenario | Today | Question | Decision |
| -------- | ----- | -------- | -------- |
| 4 | After five failed reads the parcel runs to the end of the belt | Should it go into a reject chute instead, and after how many reads? | Keep. Raised with operations: see the [ticket](../../02-better-tickets/examples/improved-ticket.md) |
| 5 | A wrong check digit counts as a failed read, although the scanner reads the same code every time | Is it worth reading a wrong code five times? | Keep |
| 7 | A good read does not reset the failed reads, so the next parcel gets fewer. The console still says "giving up after 5 reads" | Is this a bug? | Keep for now. Probably a bug: fix it through a ticket, spec first |
| 10 | The 18:00 cut-off uses the hour in UTC, not local time | Which time zone does the site run on? | Keep. Ask operations |

## Not covered

- Printed lines: the tests do not check console output.
- After the sorter gives up, the next parcel gets five reads again. No scenario pins this down yet.
- At midnight UTC the late rule stops. No scenario pins this down yet.

## Related

- [Reference solution](README.md)
- [How to write a spec you can test](../../../legacy-c/specs/README.md)
- [Challenge 1](../README.md)
