# Challenge 3: reverse engineer, review and test a point machine monitor

You work out what a legacy C monitor for railway points does today, review it against what maintenance expects, then pin its behaviour down with one test per scenario.

| Item | Details |
| ---- | ------- |
| Time | 55 minutes, in pairs |
| Code | [point-monitor/](../../point-monitor/README.md): `grade` (easy, a worked example) and `monitor` (the exercise) |
| Rules | [What maintenance expects](../../point-monitor/README.md#what-maintenance-expects) and [how to write a spec you can test](../../point-monitor/specs/README.md) |
| Copilot | Agent mode, the skills `/rail-spec` and `/rail-tests`, the **Code reviewer** custom agent, the C and spec instructions |

## The story

Points, or switches, let a train change track. A point machine moves them; one movement is a throw. A monitoring unit times every throw, and a slow throw is an early sign of a fault. The monitor in `point-monitor/` turns those times into warnings and alarms for the maintenance desk. Nobody who wrote it is still on the team, and nobody has written down what it really does.

This animation replays one run of `monitor_app` with the eight throws in [mu.c](../../point-monitor/mu.c):

![Animation of one monitor run. For each throw the points move, the throw time fills a gauge with limits at 4 and 6 seconds, and the monitor sends any alert to the maintenance desk. P101 moves in 3.2 seconds: ok, no alert. P101, 4.5 seconds: slow, a warning. P102, 4.7 seconds: slow, a warning. P101, 3.3 seconds: ok. P103, 4.4 seconds: slow, a warning. P104, 4.6 seconds: slow, a warning. P105, 4.8 seconds: slow, an alarm. P102, 7.2 seconds: too slow, an alarm.](monitor-run.svg)

The run takes place in the daytime. To see it as console output, [build and run](../../point-monitor/README.md#build-and-run) `monitor_app`.

## Before you start (5 minutes)

Open the repository root, not a subfolder, so Copilot finds `.github/`.

| Where | Build and run the tests |
| ----- | ----------------------- |
| VS Code | With the C/C++ and CMake Tools extensions: pick `point-monitor` as the active project in the CMake view, pick a compiler kit, then run **CMake: Build** and **CMake: Run Tests** |
| Visual Studio 2026 | With the **Desktop development with C++** workload: **File > Open > Folder** on the repository root. In `.vs/CMakeWorkspaceSettings.json`, set `"enableCMake": true` and `"sourceDirectory": ["legacy-c", "point-monitor"]`, then **Build > Build All** and run the tests from **Test Explorer** |
| Command line | See [Build and run](../../point-monitor/README.md#build-and-run) |

Then run `monitor_app` and read its output: a line for every throw, and the alerts the monitor sent.

You start a skill by typing `/` and its name in VS Code or Copilot CLI, for example `/rail-spec`. In Visual Studio 2026, version 18.5 or later, ask for it in agent mode: `Use the rail-spec skill on point-monitor/monitor.c`.

## The method

| Step | Copilot | You |
| ---- | ------- | --- |
| 1. Reverse engineer | Explains the code, then writes what it does today as a spec and flags anything odd | Check the explanation against the code and the program output |
| 2. Review | The **Code reviewer** agent lists findings, with a scenario that would expose each one | Sort every finding: defect, question or style. Decide every flag in the spec |
| 3. Test | Writes one test per scenario, builds and runs them | Check each test against its scenario. They pass on the unchanged code |
| Stretch | Only when you ask: the spec first, then the test, then the code | Decide what changes |

## Level 1: read the worked example (5 minutes)

1. Read [grade.spec.md](../../point-monitor/specs/grade.spec.md) next to [test_grade.c](../../point-monitor/tests/test_grade.c). Find the test for each scenario by its number.
2. Scenarios 6 and 7 are flagged. Why does a spec record behaviour that looks wrong instead of fixing it?

## Step 1: reverse engineer the monitor (15 minutes)

1. In Agent mode, run `/rail-spec point-monitor/monitor.c`, or just `/rail-spec`: the monitor is the default. Copilot first explains step by step what `monitor_step()` does and draws a Mermaid flowchart of one step, in the chat. Then it writes `point-monitor/specs/monitor.spec.md` as a draft.
2. Compare the explanation with the output of `monitor_app`. Which alert surprises you?

## Step 2: review the code (10 minutes)

1. Pick **Code reviewer** in the agent picker and ask `Review point-monitor/monitor.c.` In VS Code you can also select the code and choose **Generate Code > Review**; in Copilot CLI, run `/review`. All three work on a local repository, wherever it is hosted.
2. Sort every finding into defect, question or style. Did the reviewer find something the spec missed, or the other way round?
3. Write a decision for every flag in the spec, then set its status to reviewed.

<details>
<summary>Hint: where to look</summary>

What does the counter in `monitor.c` count: the slow throws of which points? And which hours of the day make the night possession check true?

</details>

## Step 3: test the monitor (15 minutes)

1. Run `/rail-tests point-monitor/specs/monitor.spec.md`.
2. Check: one test per scenario, all pass, and the only new file is `point-monitor/tests/test_monitor.c`. Swap two `RUN` lines and run again: the tests must pass in any order.

## Stretch: fix one defect, test first

Take the night possession flag. Change the scenarios to what maintenance expects, then the tests (they fail), then the code (they pass).

```
Change the night possession scenarios in point-monitor/specs/monitor.spec.md to what maintenance expects: no alerts from 23:00 to 03:00. Show me the changed scenarios and wait for my review before you change any test or code.
```

## Done when

| Check | How you know |
| ----- | ------------ |
| Spec | Follows the six rules, both of you reviewed it, and every flag has a decision |
| Review | Every finding is sorted into defect, question or style |
| Tests | One per scenario, all pass with the provided fake, in any order |
| Production code | Unchanged: no `.c` or `.h` file directly in `point-monitor/` changed, unless you did the stretch |

## Show and tell

Two minutes per pair: one thing Copilot found that you missed, one thing it got wrong, one decision you made.

## Reference solution

[solution/](solution/README.md) holds one possible answer: how the monitor works, the review findings, the monitor spec and its tests. Look after you try, not before.

## Related

- [Point machine monitor](../../point-monitor/README.md)
- [How to write a spec you can test](../../point-monitor/specs/README.md)
- [Challenge 1](../01-legacy-c-testable/README.md), the same method on a parcel sorter
