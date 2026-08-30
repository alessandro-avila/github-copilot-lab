---
name: 'new-endpoint'
description: 'Scaffold a new order API endpoint with types, validation and docs'
argument-hint: 'the resource name, e.g. refunds'
agent: 'agent'
---

# Scaffold a new endpoint

Add a new endpoint to the demo app for the resource: **${input:resource}**.

If no resource name came through, ask the user for one before doing anything else.

Read [api.ts](../../app/api.ts) and [utils.ts](../../app/utils.ts) first so the new
code matches the surrounding style and reuses existing helpers.

## What to produce

1. An exported `interface` describing the resource shape.
2. A create function and a lookup function for the resource.
3. Input validation that returns `null` for invalid input rather than throwing.
4. TSDoc on every exported symbol.

## Constraints

- Add the code to `app/api.ts`. Do not create new files.
- No new dependencies and no build tooling.
- Follow the TypeScript instructions that apply to this file — explicit types, no
  `any`, `T | null` for anything that can fail.

## Finish by

Printing a short summary table of what you added: symbol name, kind, and one-line
purpose.
