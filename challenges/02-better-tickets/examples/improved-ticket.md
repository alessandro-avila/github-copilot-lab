# Unreadable parcels go into the reject chute after three failed reads

This is the improved version of the [poor ticket](poor-ticket.md): Copilot drafted it from the operations e-mail with `/refine-ticket`, and a product owner answered its three questions.

**Why:** Since the new label printer arrived, the scanner fails on more labels. The sorter tries five times, then lets the parcel run to the end of the belt, where parcels pile up until someone carries them back to the manual desk ([request](../business-requests/01-operations-email.md)). Operations also see it "sometimes give up sooner".

**User story:** As an operator in hall 2, I want unreadable parcels to go into the reject chute, so that nobody has to carry them back from the end of the belt.

## Acceptance criteria

```gherkin
Scenario: An unreadable parcel goes into the reject chute after three failed reads
  Given a parcel whose label cannot be read
  When the third read fails
  Then the diverter puts the parcel into the reject chute, chute 10

Scenario: A parcel read on the second try is sorted as usual
  Given a parcel whose first read fails and whose second read is "30123458"
  When the sorter reads it the second time
  Then the parcel goes into its own chute, chute 3

Scenario: A wrong check digit counts as a failed read
  Given a parcel whose label reads "30123459" every time
  When the third read is checked
  Then the parcel goes into the reject chute

Scenario: Every parcel gets its own three reads
  Given the previous parcel needed two failed reads before it was sorted
  And the next parcel's label cannot be read
  When the sorter reads the next parcel
  Then it goes into the reject chute after its own third failed read, not sooner
```

## Out of scope

- The 18:00 cut-off and time zones: a separate ticket, from the [meeting notes](../business-requests/02-meeting-notes.md)
- Label printers and scanner hardware
- Counting rejects in the shift report (question 4)

## Open questions and assumptions

| # | Question or assumption | Who answers | Blocks start? |
| - | ---------------------- | ----------- | ------------- |
| 1 | Which chute is the reject chute? | Product owner, checked with operations. Answered: chute 10 | No |
| 2 | Does "3 tries" mean three reads in total? | Product owner. Answered: yes, three in total | No |
| 3 | Does a wrong check digit count as a failed read? | Product owner. Answered: yes, as today | No |
| 4 | Should rejects appear in the shift report? | Operations | No: follow-up ticket |
| 5 | Assumption: chute 10 has room for a whole shift of rejects | Operations | No |

## Affected code areas

- `legacy-c/sorter.c`, `sorter_step()`: the limit of five reads (`tries < 5`), the `hw_release()` call that becomes `hw_divert(10)`, and the counter that a good read does not reset
- `legacy-c/hw.h`: no change, `hw_divert()` already takes any chute
- Sorter spec: scenario 4 ("After five failed reads the sorter gives up") and scenario 7 ("The next parcel inherits the failed reads") change, see the [reference spec](../../01-legacy-c-testable/solution/sorter.spec.md). Scenarios 3, 5 and 6 stay as they are

## Test notes

- Spec first: change scenarios 4 and 7 in the sorter spec and have the change reviewed.
- Then the tests: they fail against today's code. Then the code: they pass. The spec's Background sets the time to 10:00 UTC, before the 18:00 cut-off.
- By hand: run `sorter_app`. The damaged parcel goes into chute 10 after three "no read" lines.

## Related

- [Poor ticket](poor-ticket.md), the before
- [Ticket template](../ticket-template.md)
- [Challenge 1](../../01-legacy-c-testable/README.md), where the tests live
