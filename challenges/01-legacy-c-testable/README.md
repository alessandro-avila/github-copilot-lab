# Challenge 1: specs you can test

You describe what legacy C code does today in clean, readable Given/When/Then specs, then turn every scenario into one test.

| Item | Details |
| ---- | ------- |
| Time | 45–60 minutes, in pairs |
| Code | [legacy-c/](../../legacy-c/README.md): `checksum` (easy), `route` (medium), `sorter` (hard) |
| Spec rules | [How to write a spec you can test](../../legacy-c/specs/README.md): read it first |
| Copilot | Agent mode, the prompt files `/spec-from-code` and `/tests-from-spec`, the spec and C instructions, and the **Spec reviewer** agent |

## Before you start

| Where | Build and run the tests |
| ----- | ----------------------- |
| VS Code | With the C/C++ and CMake Tools extensions: pick a compiler kit, then run **CMake: Build** and **CMake: Run Tests** |
| Visual Studio 2026 | With the **Desktop development with C++** workload: **File > Open > Folder** on the repository root, accept CMake and set `"sourceDirectory": "legacy-c"` in the file it opens. Run the tests from **Test Explorer** |
| Command line | See [Build and run](../../legacy-c/README.md#build-and-run) |

Open the repository root, so Copilot finds `.github/`. Visual Studio needs custom instructions switched on: see [Before you start](../README.md#before-you-start). You run a prompt file by typing `/` and its name; in Visual Studio versions before 2026, type `#prompt:` and pick it.

## The method

| Step | Copilot | You |
| ---- | ------- | --- |
| 1. Spec | Writes what the code does today and flags anything odd | Check every scenario against the code and the rules, decide on every flag, set the status to reviewed |
| 2. Tests | Writes one test per scenario, builds and runs them | Check each test against its scenario. They pass on the unchanged code |
| 3. Change | Only when you ask: the spec first, then the test, then the code | Decide what changes |

## Level 1: read the worked example (10 minutes)

1. Build and run the tests: `checksum` passes.
2. Read [checksum.spec.md](../../legacy-c/specs/checksum.spec.md) next to [test_checksum.c](../../legacy-c/tests/test_checksum.c). Find the test for each scenario by its number.
3. Pick **Spec reviewer** in the agent picker and ask `Review legacy-c/specs/checksum.spec.md.` Do you agree with its findings?

## Level 2: test a reviewed spec (15 minutes)

1. Read [route.spec.md](../../legacy-c/specs/route.spec.md). A person has reviewed it.
2. Run `/tests-from-spec legacy-c/specs/route.spec.md`.
3. Check: one test per scenario, all pass, and the only new file is `legacy-c/tests/test_route.c`. Swap two `RUN` lines and run again: the tests must pass in any order.

<details>
<summary>Hint: a test passes alone but fails after another one</summary>

`route_add()` changes the global table for the rest of the run. Save `nroutes` at the start of the test and restore it at the end; declare it in the test file with `extern int nroutes;`.

</details>

## Level 3: spec and test the sorter (30 minutes)

1. Run `/spec-from-code legacy-c/sorter.c`.
2. Review `legacy-c/specs/sorter.spec.md` together, against the code and the rules, and optionally with **Spec reviewer**. Run the program and compare its output with the spec.
3. Write a decision for every flag, then set the status to reviewed.
4. Run `/tests-from-spec legacy-c/specs/sorter.spec.md`. The tests use the provided fake hardware in [fake_hw.h](../../legacy-c/tests/fake_hw.h), so no other file changes.

<details>
<summary>Hint: what the spec should notice</summary>

In the program output, count the "no read" lines for the damaged parcel. Then read the "giving up" line after them.

</details>

## Stretch: change behaviour, spec first

Take the [improved ticket](../02-better-tickets/examples/improved-ticket.md) from Challenge 2: unreadable parcels go into the reject chute after three failed reads. Change the spec, then the tests (they fail), then the code (they pass).

```
Update legacy-c/specs/sorter.spec.md to match the acceptance criteria in challenges/02-better-tickets/examples/improved-ticket.md. Show me the changed scenarios and wait for my review before you change any test or code.
```

## Done when

| Check | How you know |
| ----- | ------------ |
| Route tests | One per scenario, all pass in any order |
| Sorter spec | Follows the six rules, both of you reviewed it, and every flag has a decision |
| Sorter tests | One per scenario, all pass with the provided fake |
| Production code | Unchanged: no `.c` or `.h` file directly in `legacy-c/` changed |

## Reference solution

[solution/](solution/README.md) holds one possible answer: the sorter spec, and the route and sorter tests. Look after you try, not before.

## Related

- [How to write a spec you can test](../../legacy-c/specs/README.md)
- [Legacy C sorter](../../legacy-c/README.md)
- [Challenge 2: better tickets](../02-better-tickets/README.md)
