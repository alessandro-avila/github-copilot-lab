---
name: 'C standards'
description: 'Rules for changing the legacy C modules and their tests'
applyTo: '**/*.c,**/*.h'
---

# C standards

Copilot loads these rules for all `.c` and `.h` files in the repository.

## Production code

Production code is every `.c` and `.h` file.

- Keep current behaviour unless the user asks for a change.
- Add no new globals or `static` state.
- Write portable C99: no compiler-specific keywords, pragmas or headers. Build without warnings with MSVC `/W4` and with gcc or clang `-Wall -Wextra`.

## Tests

- Use the harness in the folder's `tests/test.h`. Sorter tests use the provided fake hardware in `legacy-c/tests/fake_hw.h`; monitor tests use the provided fake monitoring unit in `point-monitor/tests/fake_mu.h`. No test framework, no downloads.
- Never change production code to make a test pass. Flag odd behaviour in the spec instead of fixing it.
- Write one test per spec scenario, with the scenario number in the comment above it.

## Related

- [Legacy C sorter](../../legacy-c/README.md)
- [Point machine monitor](../../point-monitor/README.md)
- [How to write a spec you can test](../../legacy-c/specs/README.md)
