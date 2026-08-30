---
name: 'Documentation style'
description: 'Tone and structure rules for Markdown documentation'
applyTo: '**/*.md'
---

# Documentation style

These rules load **only** for Markdown files. They are deliberately written to
contrast with the TypeScript rules, so the same request produces visibly
different output depending on which file is in context.

## Structure

- Open with a one-sentence summary. No preamble, no "In this document we will…".
- Use sentence case for headings: `Getting started`, not `Getting Started`.
- Prefer a table over more than three consecutive bullet points.
- Maximum three heading levels. If you need a fourth, split the page.

## Tone

- Address the reader as "you". Never "we" or "the user".
- Active voice only. `Copilot loads the file`, not `the file is loaded`.
- No marketing adjectives: cut `powerful`, `seamless`, `robust`, `simply`, `just`.

## Mandatory element

Every Markdown file you create or substantially rewrite must end with a
`## Related` section linking to at least one other file in this repository.

## Example of the expected shape

```md
# Order totals

You calculate an order total by summing each line's price times its quantity.

## Related

- [Demo app](../../app/README.md)
```
