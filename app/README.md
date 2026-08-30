# Demo app

A deliberately tiny order-handling module. It exists only to give Copilot
something concrete to read and change during the session.

There is no `package.json`, no install step and nothing to run. That is on
purpose — nothing here can break on conference wifi.

## Files

- `api.ts` — add, look up, total and cancel orders
- `utils.ts` — formatting and object helpers

## Known rough edges (left in on purpose)

These are the "before" state. The demo uses custom instructions to fix them live:

- no parameter or return types anywhere
- `var` and `==` in `getOrder`
- `cancel()` will throw if the order does not exist
- `orders` is untyped module-level mutable state
- no doc comments on any exported function
