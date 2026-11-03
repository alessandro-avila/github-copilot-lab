# Point machine monitor

A deliberately rough monitor for railway point machines, there to give you legacy C code to reverse engineer, review and pin down with tests in [Challenge 3](../challenges/03-point-monitor/README.md).

Points, or switches, let a train change track. A point machine moves them from normal to reverse and back: one movement is a throw. A monitoring unit next to the points times every throw, because slow throws are an early sign of a fault, such as dry slide chairs or an obstruction. The monitor alerts the maintenance desk before the points fail. It controls nothing: the interlocking moves the points, the monitor only watches. The code builds and runs on a laptop, but it is not a real product.

## What maintenance expects

The maintenance team wrote down these rules. The code is meant to follow them; whether it does is for you to find out.

| Rule | What the monitor does |
| ---- | --------------------- |
| A throw over 4 seconds is slow | Sends a warning for those points |
| A throw over 6 seconds is too slow | Sends an alarm for those points |
| Three slow throws in a row on the same points | Sends an alarm: a technician goes out |
| Night possession, from 23:00 to 03:00 | Sends no alerts: technicians are testing the points |

## Files

| File | What it does | How hard to test |
| ---- | ------------ | ---------------- |
| `grade.c` | Grades one throw: ok, slow or too slow | Easy: a pure function |
| `monitor.c` | One monitor step: take the next throw, grade it, send an alert | Hard: the monitoring unit, the clock and a counter kept between steps |
| `mu.c` | Stand-in for the monitoring unit. Replays eight throws, prints what the unit would send and reads the computer's clock | — |
| `main.c` | The main loop | — |
| `specs/` | The spec rules, and the `grade` spec | — |
| `tests/` | The provided test support, and the `grade` tests | — |

## Test support (provided)

You do not need to change the test support. [test.h](tests/test.h) is the same tiny harness as in Challenge 1. [fake_mu.c](tests/fake_mu.c) stands in for the monitoring unit in the monitor tests: a test queues throws with `fake_throw("P101", 4500)`, sets the clock with `fake.hour`, runs `monitor_step()`, then checks the alerts the fake recorded. [CMakeLists.txt](CMakeLists.txt) builds `tests/test_monitor.c` as soon as it exists, and links it with the fake instead of `mu.c`.

## Known rough edges (left in on purpose)

These are the "before" state for the challenge. Record them in a spec or a review; do not fix them unless the challenge asks you to.

| Rough edge | Where |
| ---------- | ----- |
| Short, unclear names: `t`, `g`, `h`, `n`, `pt`, `mu` | Everywhere |
| Magic numbers: `3`, `23`, `4000`, `6000` | `grade.c`, `monitor.c` |
| `printf` mixed in with the logic | `monitor.c` |
| A counter kept in `static` state | `monitor.c` |
| Two return-code styles: `0`/`-1` and `0`/`1`/`2`/`3` | `mu_next_throw()`, `monitor_step()` |
| No `NULL` checks | Everywhere |

## Build and run

From the repository root, with CMake and a C compiler:

```
cmake -S point-monitor -B build-pm
cmake --build build-pm
ctest --test-dir build-pm -C Debug
build-pm\Debug\monitor_app.exe
```

After you add a test file, run the first three commands again: the first one picks the file up. With the Visual Studio generator the program lands in `build-pm\Debug\`; with Ninja or on Linux it is `build-pm/monitor_app`.

## Related

- [Challenge 3](../challenges/03-point-monitor/README.md)
- [How to write a spec you can test](specs/README.md)
- [Legacy C sorter](../legacy-c/README.md), the same method on a parcel sorter
