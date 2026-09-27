# Reference solution

This folder holds one possible answer to Challenge 1; compare it with your own after you try, not before.

| File | Level | What it is |
| ---- | ----- | ---------- |
| [test_route.c](test_route.c) | 2 | One test per scenario in `legacy-c/specs/route.spec.md` |
| [sorter.spec.md](sorter.spec.md) | 3 | What `sorter_step()` does today: ten scenarios, four of them flagged |
| [test_sorter.c](test_sorter.c) | 3 | One test per sorter scenario, with the provided fake hardware |

The tests build against the unchanged code in `legacy-c/`.

## Run it

```
cmake -S legacy-c -B build -DWITH_SOLUTION=ON
cmake --build build
ctest --test-dir build -C Debug -R solution --output-on-failure
```

## Talking points for show and tell

| Question | What to look for |
| -------- | ---------------- |
| Did your spec find the counter that carries over to the next parcel? | Scenario 7. The program output shows it: three "no read" lines, then "giving up after 5 reads" |
| Did a Then line name internal state, such as the counter? | Rule 3: rewrite it as a return value or a hardware call, which a test can check |
| Did Copilot try to fix something while it wrote the spec or the tests? | That skips a step. Behaviour changes come last, spec first |

## Related

- [Challenge 1](../README.md)
- [How to write a spec you can test](../../../legacy-c/specs/README.md)
