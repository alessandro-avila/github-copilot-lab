# Route spec

This spec covers the routing table in [route.c](../route.c): `route()` gives the chute for a parcel code, and `route_add()` adds a destination or fails with "table full" or "bad destination".

**Status:** reviewed. The tests are yours to write, in `tests/test_route.c`.

## Scenarios

```gherkin
Background:
  Given the starting routing table
    | destination | chute |
    | 10          | 1     |
    | 11          | 1     |
    | 20          | 2     |
    | 30          | 3     |
    | 31          | 3     |
    | 40          | 4     |

Scenario: 1. A known destination gets its chute
  When you look up parcel "30123458"
  Then you get chute 3

@flagged
Scenario: 2. A destination without a route gets chute 9
  When you look up parcel "55123457"
  Then you get chute 9

Scenario: 3. An added destination gets its chute
  When you add destination "50" with chute 5
  Then adding succeeds
  And looking up parcel "50123452" gives chute 5

@flagged
Scenario: 4. Adding a destination that is already there keeps the old chute
  When you add destination "30" with chute 7
  Then adding succeeds
  And looking up parcel "30123458" still gives chute 3

Scenario: 5. The table holds at most 20 routes
  Given you added destinations "60" to "73" with chute 6, so the table holds 20 routes
  When you add destination "74" with chute 7
  Then adding fails with "table full"

Scenario: 6. A destination needs exactly two characters
  When you add destination "500" with chute 5
  Then adding fails with "bad destination"
```

## Flagged

| Scenario | Today | Question | Decision |
| -------- | ----- | -------- | -------- |
| 2 | Gives chute 9 and prints "route: no route for 55, using chute 9" | Is chute 9 the right place for parcels without a route? | Keep. Operations to answer |
| 4 | Adding succeeds, but the first route still wins, and the add uses up one of the 20 places | Should adding an existing destination change its chute, or fail? | Keep. Operations to answer |

## Not covered

- Printed lines: the tests do not check console output.
- Removing a destination: `route.c` cannot remove one, so a destination you add stays until the program ends.
- A missing code or destination (a null pointer) crashes, so no test can pin it down.

## Related

- [Checksum spec](checksum.spec.md), the model
- [How to write a spec you can test](README.md)
- [Challenge 1](../../challenges/01-legacy-c-testable/README.md)
