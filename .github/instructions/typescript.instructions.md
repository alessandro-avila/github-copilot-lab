---
name: 'TypeScript standards'
description: 'Strict typing and defensive coding rules for TypeScript files'
applyTo: '**/*.ts'
---

# TypeScript standards

These rules load **only** when Copilot is working on a `.ts` file. Open a `.md`
file and they do not apply — that contrast is the demo.

## Typing

- Every exported function needs explicit parameter and return types.
- `any` is banned. Use `unknown` and narrow it, or define a proper type.
- Define shared shapes as exported `interface` or `type` declarations, not inline.
- Prefer union literals over loose strings: `'open' | 'cancelled'`, not `string`.

## Safety

- Functions that can fail return `T | null` — never throw for expected cases.
- Check for `null` before property access.
- Never mutate a parameter. Return a new object instead.

## Documentation

- Every exported symbol gets a TSDoc block with a one-line summary and `@param`
  / `@returns` tags.

## Example of the expected shape

```ts
/**
 * Looks up an order by its identifier.
 * @param orders - The collection to search.
 * @param id - The identifier to match.
 * @returns The matching order, or `null` when nothing matches.
 */
export function getOrder(orders: readonly Order[], id: string): Order | null {
  return orders.find((order) => order.id === id) ?? null;
}
```
