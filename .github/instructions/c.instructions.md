---
name: 'C standards'
description: 'Rules for changing the legacy C modules and their tests'
applyTo: 'legacy-c/**/*.c,legacy-c/**/*.h'
---

# C standards

These rules load only when Copilot works on a C file in `legacy-c/`.

## Production code

Production code is every `.c` and `.h` file directly in `legacy-c/`.

- Keep current behaviour unless the user asks for a change.
- Add no new globals or `static` state.
- Write portable C99: no compiler-specific keywords, pragmas or headers. Build without warnings with MSVC `/W4` and with gcc or clang `-Wall -Wextra`.

## Tests

- Use the harness in `legacy-c/tests/test.h`. Sorter tests use the provided fake hardware in `legacy-c/tests/fake_hw.h`. No test framework, no downloads.
- Never change production code to make a test pass. Flag odd behaviour in the spec instead of fixing it.
- Write one test per spec scenario, with the scenario number in the comment above it.

## Related

- [Legacy C sorter](../../legacy-c/README.md)
- [How to write a spec you can test](../../legacy-c/specs/README.md)
