# Legacy C sorter

A deliberately rough controller for a small parcel sorter, there to give you legacy code to describe in specs and pin down with tests in [Challenge 1](../challenges/01-legacy-c-testable/README.md).

A scanner reads each parcel's barcode, and a diverter pushes the parcel off the conveyor into a chute. The code builds and runs on a laptop, but it is not a real product.

## Files

| File | What it does | How hard to test |
| ---- | ------------ | ---------------- |
| `checksum.c` | Checks the check digit of a parcel code | Easy: a pure function |
| `route.c` | Picks the chute for a destination from a global table | Medium: global state |
| `sorter.c` | One controller step: scan, retry, route, divert | Hard: hardware, and a counter kept between steps |
| `hw.c` | Stand-in for the hardware. Replays four parcels, prints what the hardware would do and reads the computer's clock | — |
| `main.c` | The main loop | — |
| `specs/` | The spec rules, and the `checksum` and `route` specs | — |
| `tests/` | The provided test support, and the `checksum` tests | — |

A parcel code has 8 digits: destination (2), serial number (5) and check digit (1). `30123458` goes to destination 30, which is chute 3.

## Test support (provided)

The test support is provided: you do not need to change it. [test.h](tests/test.h) is a tiny test harness with `CHECK_EQ` and a pass/fail summary. [fake_hw.c](tests/fake_hw.c) stands in for the hardware in the sorter tests: a test sets the parcel, what each read returns and the time, runs `sorter_step()`, then checks the diverts and releases the fake recorded. [CMakeLists.txt](CMakeLists.txt) builds `tests/test_route.c` and `tests/test_sorter.c` as soon as they exist, and links the sorter tests with the fake instead of `hw.c`.

## Known rough edges (left in on purpose)

These are the "before" state for the challenge. Record them in a spec; do not fix them unless the challenge asks you to.

| Rough edge | Where |
| ---------- | ----- |
| Short, unclear names: `chk`, `s`, `w`, `rt`, `tries` | Everywhere |
| Magic numbers: `5`, `8`, `9`, `18`, `20`, `3600` | Everywhere |
| A global, writable routing table | `route.c` |
| `printf` mixed in with the logic | `route.c`, `sorter.c` |
| A retry counter kept in `static` state | `sorter.c` |
| Three return-code styles: `1`/`0`, `0`/`-1` and `0`/`1`/`2`/`-1` | `chk()`, `hw_read_barcode()`, `sorter_step()` |
| No `NULL` checks | Everywhere |

## Build and run

From the repository root, with CMake and a C compiler:

```
cmake -S legacy-c -B build
cmake --build build
ctest --test-dir build -C Debug
build\Debug\sorter_app.exe
```

After you add a test file, run the first three commands again: the first one picks the file up. With the Visual Studio generator the program lands in `build\Debug\`; with Ninja or on Linux it is `build/sorter_app`.

Without CMake, run this one line in a Developer Command Prompt for Visual Studio:

```
mkdir build 2>nul & cl /nologo /W4 /Ilegacy-c /Fo:build\ /Fe:build\ legacy-c\tests\test_checksum.c legacy-c\checksum.c && build\test_checksum.exe
```

## Related

- [Challenge 1](../challenges/01-legacy-c-testable/README.md)
- [How to write a spec you can test](specs/README.md)
- [Demo app](../app/README.md), the TypeScript counterpart
