# Checksum spec

This spec covers `chk()` in [checksum.c](../checksum.c), the check-digit test for a parcel code: a code passes when `chk()` returns 1 and fails when it returns 0.

**Status:** reviewed. [test_checksum.c](../tests/test_checksum.c) has one test per scenario.

## Scenarios

```gherkin
Scenario: 1. A code with the right check digit passes
  Given the parcel code "30123458"
  When you check it
  Then it passes

Scenario: 2. A code with a wrong check digit fails
  Given the parcel code "30123459"
  When you check it
  Then it fails

Scenario: 3. A code with a letter fails
  Given the parcel code "3012A458"
  When you check it
  Then it fails

Scenario: 4. A code shorter than two digits fails
  Given the parcel code "7"
  When you check it
  Then it fails

Scenario: 5. A code longer than 18 digits fails
  Given the 19-digit parcel code "3012345678901234567", whose check digit is right
  When you check it
  Then it fails

@flagged
Scenario: 6. A two-digit code passes
  Given the parcel code "17"
  When you check it
  Then it passes

@flagged
Scenario: 7. A code of all zeros passes
  Given the parcel code "00000000"
  When you check it
  Then it passes
```

## Flagged

| Scenario | Today | Question | Decision |
| -------- | ----- | -------- | -------- |
| 6 | Any code of 2 to 18 digits passes | Labels have 8 digits: should other lengths fail? | Keep. Operations to answer |
| 7 | `00000000` passes | Can a faulty scanner return all zeros? | Keep. Operations to answer |

## Not covered

- A missing code (a null pointer): `chk()` crashes, so no test can pin it down.

## Related

- [Checksum tests](../tests/test_checksum.c)
- [How to write a spec you can test](README.md)
- [Route spec](route.spec.md), the next one to test
