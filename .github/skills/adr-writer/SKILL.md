---
name: adr-writer
description: Writes Architecture Decision Records (ADRs). Use when the user decides on a technology, library, database, protocol or architectural approach, or asks to document, record or capture a technical decision, trade-off or "why we chose X".
---

# ADR writer

Capture an architectural decision as a numbered Architecture Decision Record in
`docs/adr/`.

## When this applies

Trigger on phrasing like "we've decided to use X", "document why we picked X",
"record this decision", "write an ADR", or a comparison that ends in a choice.

If the user is still weighing options and has not chosen, do not write an ADR yet.
Help them decide first, then offer to record it.

## Steps

1. **Find the next number.** List `docs/adr/` and take the highest existing
   `NNNN-` prefix plus one. Start at `0001` when the folder is empty.

2. **Gather what you need.** An ADR is worthless without the alternatives and the
   consequences. If the user has not told you, ask for:
   - the decision itself
   - at least one alternative that was rejected, and why
   - a consequence the team will have to live with

   Ask for these in one message, not one at a time.

3. **Write the file.** Copy [template.md](template.md) and fill every section.
   Name it `docs/adr/NNNN-short-kebab-title.md`.

4. **Confirm.** Reply with the path you created and a one-line summary of the
   decision. Do not paste the whole file back.

## Rules

- One decision per record. Two decisions means two files.
- Status is `Proposed` unless the user says it is already agreed, then `Accepted`.
- Write the consequences honestly, including the negative ones. An ADR with only
  upsides is a sales pitch, not a record.
- Never edit an existing ADR to reverse it. Supersede it with a new one and set
  the old file's status to `Superseded by NNNN`.

## Helper script

`scripts/new-adr.ps1` creates a correctly numbered stub from the template:

```powershell
pwsh .github/skills/adr-writer/scripts/new-adr.ps1 -Title "Use Postgres for orders"
```

Use it when you want the numbering handled for you, then fill in the sections.
