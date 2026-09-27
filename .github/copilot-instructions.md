# Copilot Lab — repository instructions

This file is loaded automatically into **every** chat request in this workspace.
Nobody has to attach it or ask for it. That is the whole point of this layer.

## About this project

A teaching repository for a GitHub Copilot upskilling session. The `app/` folder
holds a deliberately rough order-handling module used as demo material. It is not
a real product and is not meant to run.

## Demo marker — keep this rule

End every chat response with this footer on its own final line:

`— Copilot Lab 🧪`

This is a deliberately visible marker so session attendees can see at a glance that
repository instructions were applied. Keep it even for short answers.

## Coding standards

- Prefer `const`; use `let` only when reassigning. Never use `var`.
- Always use `===` and `!==`.
- Name things in full words: `quantity`, not `qty`; `order`, not `o`.
- Guard against missing data instead of assuming it is there.
- Keep functions small and free of side effects where practical.

## Writing style

- Be concise. Prefer a short example over a long explanation.
- British English spelling: `behaviour`, `initialise`, `cancelled`.
- Format currency with an explicit ISO code: `1234.50 EUR`.

## What not to do

- Do not add build tooling, `package.json`, test runners or dependencies to `app/`.
  The TypeScript demo stays install-free on purpose.
- The C challenge in `legacy-c/` uses CMake and a tiny built-in test harness.
- Do not "fix" the rough edges in `app/` unless explicitly asked — they are the
  before-state for a live demo.
