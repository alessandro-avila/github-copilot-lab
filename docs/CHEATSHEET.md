# Cheatsheet

Where every Copilot customization lives, how it is invoked, and where it works.
One page, meant to be printed or pasted into a wiki.

## Chat modes (agent roles)

The dropdown in the chat input. VS Code calls these **agent roles**: they supply the
instructions, tools and behaviour for a task. This is separate from customization —
you pick a role first, then the customizations in this repo apply within it.

| Role | You give it | You get back | Touches your files |
| ---- | ----------- | ------------ | ------------------ |
| **Ask** | a question | an answer | no |
| **Agent** | a goal | edits, commands, a finished task | yes |
| **Plan** | a goal | a reviewable plan, before any work | no |
| **Custom agent** | whatever you defined | whatever you defined | you decide |

**Agent** is the one to teach. It chooses which files to open, runs terminal
commands, reads the output, and corrects itself — you review the outcome rather
than each step.

**Plan** is often mistaken for Agent. If a description mentions producing a plan
draft for review and iteration, that is Plan, not Agent. Keep the two distinct or
attendees will conflate them.

**Edit** still appears in the dropdown but is being retired — VS Code's own docs now
list the roles as "Agent, Plan, Ask, and custom agents". Do not build training
material around it.

Custom agents are defined in `.github/agents/*.agent.md`; this repo ships
`docs-reviewer` as an example.

## File locations

| Primitive | Workspace | User level |
| --------- | --------- | ---------- |
| Repository instructions | `.github/copilot-instructions.md` | — |
| Agent instructions | `AGENTS.md` (root or subfolders) | — |
| Path-specific instructions | `.github/instructions/*.instructions.md` | `~/.copilot/instructions/` |
| Prompt files | `.github/prompts/*.prompt.md` | VS Code profile |
| Skills | `.github/skills/<name>/SKILL.md` | `~/.copilot/skills/` |
| Custom agents | `.github/agents/*.agent.md` | `~/.copilot/agents/` |
| MCP (VS Code) | `.vscode/mcp.json` | **MCP: Open User Configuration** |
| MCP (portable) | `.mcp.json` | `~/.copilot/mcp-config.json` |
| Plugins | installed, not committed | `~/.copilot/installed-plugins/` |

Instructions and skills folders are searched recursively, so you can group by team,
language or module in subfolders.

Alternative folders are also recognised for cross-tool compatibility: `.claude/skills/`
and `.agents/skills/` for skills, `.claude/rules/` for instructions, and `CLAUDE.md`
for always-on instructions.

## How each one is invoked

| Primitive | Trigger | You control it by |
| --------- | ------- | ----------------- |
| Repository instructions | Every request | Existing |
| Path-specific instructions | File matches `applyTo` glob, or description matches the task | The glob |
| Prompt files | You type `/name` | Typing it |
| Skills | Model decides from the `description` | Wording the description well |
| MCP servers | Model calls a tool | Enabling the server and its tools |
| Plugins | Whatever they contain | Installing / disabling |

## Frontmatter reference

**`*.instructions.md`**

| Field | Purpose |
| ----- | ------- |
| `name` | Display name in the UI |
| `description` | Shown on hover; also used for semantic matching |
| `applyTo` | Glob. `'**'` for everything. Omit and it never auto-applies |

**`*.prompt.md`**

| Field | Purpose |
| ----- | ------- |
| `name` | What you type after `/` |
| `description` | Shown in the prompt picker |
| `argument-hint` | Placeholder text in the chat input |
| `agent` | `ask`, `agent`, `plan`, or a custom agent name |
| `tools` | Restrict which tools the prompt may use |

Use `${input:variable}` in the body for values passed on the command line.

**`SKILL.md`**

| Field | Purpose |
| ----- | ------- |
| `name` | Skill identifier |
| `description` | **The most important line.** This is what the model matches against to decide relevance |

Write the description as *when to use this*, not *what this is*. Include the phrases
a user would actually say.

## Precedence and composition

Instructions **compose**, they do not override. If `copilot-instructions.md` and a
matching `*.instructions.md` both apply, you get both. VS Code guarantees no
particular ordering between multiple instruction files, so avoid writing rules that
contradict each other and expecting one to win.

A prompt file's body is added on top of whatever instructions already applied. That
is why `/new-endpoint` in this repo still produces typed, documented code — the
TypeScript instructions are underneath it.

## Cross-surface support

| | VS Code | Copilot CLI | Copilot app | github.com |
| - | ------- | ----------- | ----------- | ---------- |
| `copilot-instructions.md` | yes | yes | yes | yes |
| `*.instructions.md` | yes | yes | yes | yes |
| `AGENTS.md` | yes | yes | yes | yes |
| Prompt files | local agents only | — | — | — |
| Skills | yes | yes | yes | yes |
| MCP | yes | yes | yes | — |
| Plugins | yes | yes | yes | — |

**The one to remember:** prompt files do not run on the Agent Host. Skills do, and
they follow an open standard, so a skill you write today works in VS Code, the CLI
and the Copilot app without modification.

## Useful commands

**VS Code — Command Palette**

| Command | Does |
| ------- | ---- |
| `Chat: Open Customizations` | The Agent Customizations editor — everything in one place |
| `Chat: New Instructions File` | Scaffold an instructions file |
| `Chat: New Prompt File` | Scaffold a prompt file |
| `MCP: Add Server` | Guided MCP setup |
| `MCP: List Servers` | Status, restart, logs |
| `Chat: Install Plugin From Source` | Install a plugin from a Git URL |

In the chat input, `/instructions` and `/skills` jump straight to the relevant
configuration menus.

**Copilot CLI**

```bash
copilot plugin marketplace list
copilot plugin marketplace add OWNER/REPO
copilot plugin install PLUGIN-NAME@MARKETPLACE-NAME
copilot plugin list
copilot plugin uninstall PLUGIN-NAME
```

## Where MCP servers actually come from

The most common question once someone opens **Configure Tools** and finds a hundred
tools they never configured. Servers arrive from five independent places, and they
all merge into one list.

| Source | Location | Visible as a file? |
| ------ | -------- | ------------------ |
| VS Code extensions | registered in code by the extension | **No** — this is the surprising one |
| VS Code user profile | `%APPDATA%\Code\User\mcp.json` (Windows) | yes |
| Copilot plugins | `~/.copilot/installed-plugins/<marketplace>/<plugin>/.mcp.json` | yes |
| Copilot user config | `~/.copilot/mcp-config.json` | yes |
| Workspace | `.vscode/mcp.json` and `.mcp.json` | yes |

Extensions are usually the largest and least obvious source. Terraform, Bicep, AKS,
Azure, Cosmos DB, Pylance and GitLens all register MCP servers just by being
installed — nothing appears in any config file you own.

### Why you see duplicates

There is no global de-duplication. Two plugins that each bundle a server with the
same name produce two entries, and the same server declared in both a user config
and an extension appears twice. Names in the UI come from the server definition,
not from the source, so identical names from different sources look like a bug but
are not.

To trace one: **MCP: List Servers** shows each server and lets you open its
configuration or logs, which reveals the origin.

### Reducing tool count

Model tool-selection accuracy degrades as the list grows, so trimming is worthwhile:

- Disable overlapping plugins in **Agent Plugins - Installed** in the Extensions view
- Toggle individual tools off with **Configure Tools** in the chat input
- Disable MCP-contributing extensions you are not using in this workspace

## The two workspace MCP files

This repo ships both on purpose. They are not interchangeable.

| | `.vscode/mcp.json` | `.mcp.json` (repo root) |
| - | ------------------ | ----------------------- |
| Read by | VS Code | Copilot CLI, Agent Host, Copilot app |
| Top-level key | `"servers"` | `"mcpServers"` |
| Format | JSONC — comments allowed | strict JSON |
| `${input:...}` | supported, prompts and stores securely | not supported |
| `"inputs"` array | yes | no |

**The subtle part:** VS Code forwards your `.vscode/mcp.json` configuration to the
Agent Host — *except* servers that use `${input:...}`, because the Agent Host cannot
run the interactive prompt. A server with an `${input:}` secret therefore works in
VS Code chat and silently disappears on the Agent Host and CLI.

That is the whole reason to keep a `.mcp.json` alongside it: anything that must work
across surfaces belongs there, using environment variables rather than `${input:}`
for secrets.

## Not covered in this lab

**Hooks** — shell commands that fire at agent lifecycle points (`SessionStart`,
`PreToolUse`, `PostToolUse`, `Stop` and others). Configured in `hooks.json`. Genuinely
useful for auto-formatting or blocking risky tool calls, but they execute arbitrary
commands on your machine and are client-specific rather than portable, so they are
mentioned here rather than demonstrated.

**Organization-level instructions** — share instructions across every repository in a
GitHub organization, configured centrally rather than in a repo.

## Security notes worth repeating

- Local MCP servers and plugin hooks run code on your machine. Review the publisher.
- Never hardcode credentials in `mcp.json`. Use `${input:...}` or an env file.
- Plugin MCP servers are implicitly trusted once you install the plugin — they do not
  prompt separately at startup.

## Official documentation

- [Custom instructions (VS Code)](https://code.visualstudio.com/docs/agent-customization/custom-instructions)
- [Prompt files (VS Code)](https://code.visualstudio.com/docs/agent-customization/prompt-files)
- [Agent skills (VS Code)](https://code.visualstudio.com/docs/agent-customization/agent-skills)
- [MCP servers (VS Code)](https://code.visualstudio.com/docs/agent-customization/mcp-servers)
- [Agent plugins (VS Code)](https://code.visualstudio.com/docs/agent-customization/agent-plugins)
- [Repository instructions (GitHub Docs)](https://docs.github.com/en/copilot/how-tos/configure-custom-instructions/add-repository-instructions)
- [Copilot CLI plugins (GitHub Docs)](https://docs.github.com/en/copilot/how-tos/copilot-cli/customize-copilot/plugins-finding-installing)
- [Agent Skills standard](https://agentskills.io)
- [Agent Plugins standard](https://agent-plugins.org/)

## Related

- [Demo script](../README.md)
- [Plugin anatomy](../plugins/copilot-lab-plugin/README.md)
