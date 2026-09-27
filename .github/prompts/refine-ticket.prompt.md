---
name: 'refine-ticket'
description: 'Turn a business request into an implementation ticket that follows the ticket template'
argument-hint: 'a request file, e.g. challenges/02-better-tickets/business-requests/01-operations-email.md, or pasted text'
agent: 'agent'
---

# Refine a business request into a ticket

Turn a business request into a ticket a developer can start on: you draft, the user decides.

The request is a file the user named or attached, or text they pasted. If there is none, ask for it, and stop.

## Steps

1. Read the request and [ticket-template.md](../../challenges/02-better-tickets/ticket-template.md).
2. If the request mixes several topics, list them and ask which one to refine. One ticket, one outcome.
3. If the ticket needs missing information, ask **at most three** clarifying questions in one message, and wait for the answers. Ask about what changes the implementation most: numbers, limits, exceptions, who is affected.
4. Search the repository for the code the request touches. Name the files and functions under "Affected code areas". If a spec covers that code, for example in `legacy-c/specs/` or `challenges/01-legacy-c-testable/solution/`, say which scenarios the ticket changes.
5. Write the ticket in the template. Acceptance criteria are Given/When/Then scenarios with concrete values, including at least one unhappy path.

## Rules

- Never invent numbers, dates, names or requirements. If neither the user nor the code tells you, put it under "Open questions and assumptions".
- Label every assumption as an assumption.
- The title states an outcome, such as "Unreadable parcels go to the reject chute", not an activity such as "Fix scanner".
- Write in plain language, so both a developer and a product owner can read the ticket.
- Do not open `challenges/02-better-tickets/examples/`: the user compares your draft with those examples afterwards.

## Jira (optional)

If a Jira MCP server is available, for example with a `jira_create_issue` tool, offer to create the issue. First show the project, issue type, summary and description you would send. Create it only after the user says yes. Never create, update or transition an issue without that confirmation.

If no Jira server is available, tell the user to copy the ticket into Jira by hand.

## Finish by

Listing the open questions that still block the start, or saying "Ready: no blocking questions".

## Related

- [Ticket template](../../challenges/02-better-tickets/ticket-template.md)
- [Challenge 2](../../challenges/02-better-tickets/README.md)
