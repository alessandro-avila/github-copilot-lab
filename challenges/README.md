# Challenges

Three hands-on challenges you work through in pairs, each in 45–60 minutes.

| # | Challenge | Goal | You learn | Copilot building blocks |
| - | --------- | ---- | --------- | ----------------------- |
| 1 | [Specs you can test](01-legacy-c-testable/README.md) | Describe what old C code does today in clean, readable specs, then turn every scenario into a test | Six rules for a spec you can test, reviewing a spec, flagging instead of fixing, one test per scenario | Agent mode, the skills `/spec-from-code` and `/tests-from-spec`, path instructions for specs and C, the **Spec reviewer** custom agent |
| 2 | [Better implementation tickets](02-better-tickets/README.md) | Turn a vague business request into a ticket a developer can start on | A one-screen Definition of Ready, acceptance criteria as Given/When/Then, asking instead of guessing | The skill `/refine-ticket`, repository search, optionally a Jira MCP server |
| 3 | [Reverse engineer, review and test](03-point-monitor/README.md) | Work out what a legacy C monitor for railway points does, review it against what maintenance expects, then test it | Reverse engineering, sorting review findings, characterisation tests, fixing a defect test first | Ask and Agent mode, the skills `/rail-spec` and `/rail-tests`, the **Code reviewer** custom agent, path instructions for specs and C |

The first two connect: a ticket from Challenge 2 changes the sorter you test in Challenge 1. That is the path from ticket to tested code. Challenge 3 applies the method of Challenge 1 to new code, and adds a code review.

## How to run a challenge

| Step | What you do |
| ---- | ----------- |
| Pair up | Two people, one keyboard. Mix roles where you can: a developer with a product owner or an architect. Swap the keyboard halfway |
| Time box | 45–60 minutes. Stop when the time is up, even if you are not done |
| Done | Tick off the "Done when" table in the challenge README |
| Show and tell | Two minutes per pair: one thing Copilot did well, one thing it got wrong, one decision you made |

## Before you start

| Check | Details |
| ----- | ------- |
| Folder | Open the repository root, not a subfolder, so Copilot finds `.github/` |
| Chat | Agent mode |
| Visual Studio | In **Tools > Options > All Settings > GitHub > Copilot > Copilot Chat**, select **Enable custom instructions to be loaded from .github/copilot-instructions.md files and added to requests** |
| Skills | Type `/` and the skill name, for example `/spec-from-code` or `/rail-spec`, in VS Code or Copilot CLI. In Visual Studio 2026, version 18.5 or later, ask for the skill by name in agent mode, for example `Use the rail-spec skill on point-monitor/monitor.c`; if it does not load, attach its `SKILL.md` with `#` |

## Related

- [Demo script](../README.md)
- [Cheatsheet](../docs/CHEATSHEET.md)
