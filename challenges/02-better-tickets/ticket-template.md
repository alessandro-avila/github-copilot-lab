# Ticket template

You use this template to turn a business request into a ticket a developer can start on: the Definition of Ready on one screen.

## Ready when

| Section | Ready when |
| ------- | ---------- |
| Title | It names the outcome, not the activity |
| Why | A developer can explain the problem in one sentence |
| User story | It names a real role and a real benefit |
| Acceptance criteria | Every rule has a Given/When/Then scenario with concrete values, including one unhappy path |
| Out of scope | It says what this ticket does not change |
| Open questions | Nothing left in the table blocks the start |
| Affected code areas | It names files or functions, not "the backend" |
| Test notes | It says which specs and tests change |

## Copy this

````md
# <Outcome, e.g. "Unreadable parcels go into the reject chute">

**Why:** <The problem today and who feels it. Link to the request.>

**User story:** As a <role>, I want <capability>, so that <benefit>.

## Acceptance criteria

```gherkin
Scenario: <the rule in a few words>
  Given <the starting situation>
  When <the event>
  Then <the result you can observe>
```

## Out of scope

- <What this ticket does not change>

## Open questions and assumptions

| # | Question or assumption | Who answers | Blocks start? |
| - | ---------------------- | ----------- | ------------- |
| 1 | <...> | <role> | <yes or no> |

## Affected code areas

- `<path>`: <what changes there>

## Test notes

- <Specs and tests to update, and how to check by hand>
````

## Related

- [Challenge 2](README.md)
