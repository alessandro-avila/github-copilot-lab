# Poor ticket (before)

Someone wrote this ticket straight from the [operations e-mail](../business-requests/01-operations-email.md); read it and ask yourself whether a developer could start on it today.

---

> **SORT-101 Fix scanner**
>
> Parcels not read properly, they go to the end. Needs to be 3 tries. Urgent!!!
>
> *Priority: Highest · Component: Scanner*

## What is wrong with it

| Problem | What happens next |
| ------- | ----------------- |
| The title names a part, not an outcome | Nobody can tell when it is done |
| "Fix scanner": the scanner works; the retry rule is the problem | The ticket lands with the wrong team |
| "3 tries": three in total, or three more after the first? | Two developers build two different things |
| No reject chute named | The developer guesses a chute number |
| No acceptance criteria | Nobody knows what to test |
| "Sometimes it gives up sooner" from the e-mail is missing | A real bug stays hidden |
| "Urgent!!!" but no date | The real deadline, peak season, gets lost |

## Related

- [Improved ticket](improved-ticket.md), the after
- [Ticket template](../ticket-template.md)
