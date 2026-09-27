# GitHub Copilot customization lab

Five customization primitives.

| # | Primitive | Lives in | Invoked |
| - | --------- | -------- | ------- |
| 1 | Repo instructions | `.github/copilot-instructions.md` | always |
| 2 | Path instructions | `.github/instructions/*.instructions.md` | by `applyTo` glob |
| 3 | Prompt files | `.github/prompts/*.prompt.md` | `/name` |
| 4 | Skills | `.github/skills/*/SKILL.md` | by the model |
| 5 | MCP servers | `.vscode/mcp.json`, `.mcp.json` | tool calls |
| 6 | Plugins | installed, not committed | bundles 4 + 5 |

## Pre-flight

- Open this folder as the workspace root
- Chat view → **Agent** mode
- **MCP: List Servers** → `microsoft-learn` running (no auth needed)
- `docs/adr/` empty except `.gitkeep`

---

## 1. Repo instructions — always on

Show `.github/copilot-instructions.md`, then:

```
What does the cancel function in app/api.ts do, and is there anything wrong with it?
```

**Look for:** the `— Copilot Lab 🧪` footer. Nobody asked for it. Also British
spelling and full words over abbreviations.

## 2. Path instructions

The two files deliberately contradict each other. That contrast is the demo.

With **`app/api.ts`** open:

```
Add a function that finds all orders with a given status.
```

**Look for:** explicit types, no `any`, `T | null` instead of throwing, TSDoc.

Now open **`app/README.md`**:

```
Add a short section describing what this module is for.
```

**Look for:** sentence-case heading, "you" not "we", no marketing adjectives, a
`## Related` section. Same session, different rules.

## 3. Prompt files

```
/new-endpoint refunds
```

**Look for:** the argument hint in the input, and the TypeScript rules from beat 2
still applying underneath. Layers compose.

Self-documenting recap:

```
/explain-customizations
```

## 4. Skills

`.github/skills/adr-writer/` is a *folder*: `SKILL.md` + `template.md` +
`scripts/new-adr.ps1`. The `description` line is what triggers it.

No slash command, no mention of ADRs:

```
We've decided to use Postgres instead of MongoDB for the orders service, mainly because we need real transactions. Capture that decision.
```

**Look for:** it loads the skill unprompted, asks for alternatives and
consequences, writes `docs/adr/0001-*.md` from the bundled template.

Skills can ship executables — instructions can't:

```powershell
pwsh .github/skills/adr-writer/scripts/new-adr.ps1 -Title "Adopt OpenTelemetry"
```

**Fallback:** `/skills` to enable explicitly, or "use the adr-writer skill".
**Reset:** `Remove-Item docs\adr\*.md`

## 5. MCP servers — reach outside the repo

```
Using the Microsoft Learn MCP server, find the current guidance on Azure Container Apps scaling rules and summarise the options in a table.
```

**Look for:** tool-call disclosures. Expand one. Then **Configure Tools**.

**Two files, not interchangeable:**

| | `.vscode/mcp.json` | `.mcp.json` |
| - | ------------------ | ----------- |
| Read by | VS Code | CLI, Agent Host, Copilot app |
| Key | `"servers"` | `"mcpServers"` |
| Format | JSONC | strict JSON |
| `${input:}` | yes | no |

**The punchline:** VS Code forwards `.vscode/mcp.json` to the Agent Host *except*
`${input:}` servers — it can't show the prompt. So they work in VS Code and vanish
in the CLI. That is why both files exist.

**Expect:** *"where did all those other servers come from?"* Five sources merge with
no de-duplication — extensions, user profile, plugins, `~/.copilot/mcp-config.json`,
workspace. See the [cheatsheet](docs/CHEATSHEET.md).

**Fallback:** `List the open issues in the microsoft/vscode repository.`

## 6. Plugins — packaging

`plugins/copilot-lab-plugin/` is there to **read**, not load. Repo plugin folders
are never auto-discovered; real installs land in `~/.copilot/installed-plugins/`.

Portable: `skills/`, `mcp.json`. Copilot-only: `com.github.copilot/agents/`.

**Live install:** Extensions view → `@agentPlugins` → install from
`awesome-copilot` → show its skills in `/skills`.

```bash
copilot plugin install PLUGIN-NAME@awesome-copilot
```

Then ask for what the bundled skill does:

```
Draft release notes for the changes in this repository since the last tag.
```

## Bonus — custom agents

`.github/agents/docs-reviewer.agent.md`. Pick **Docs reviewer** from the agent
dropdown, then:

```
Review docs/CHEATSHEET.md against our house style.
```

**Look for:** it reviews and refuses to rewrite. Constrained tools enforce the role.

Frontmatter worth showing: `tools` limits capability. Adding `agent` enables
**subagent delegation** — but subagents bring their own tools, so a read-only
reviewer could delegate to something that edits. Whitelist with `agents:` or leave
`agent` out.

---

## Closing

**"Which do I use?"** Work down the table at the top. Stop at the first row that
fits. Most teams need row 1 only.

| | VS Code | CLI | Copilot app |
| - | ------- | --- | ----------- |
| `copilot-instructions.md` | yes | yes | yes |
| `*.instructions.md` | yes | yes | yes |
| Prompt files | local agents only | — | — |
| Skills | yes | yes | yes |
| MCP | both files | `.mcp.json` | `.mcp.json` |
| Plugins | yes | yes | yes |

Skills and MCP are the portable core. Invest there first.

## Related

- [Cheatsheet](docs/CHEATSHEET.md) — locations, precedence, MCP sources, chat modes
- [Demo app](app/README.md)
- [Plugin anatomy](plugins/copilot-lab-plugin/README.md)
- [Challenges](challenges/README.md) — hands-on: specs and tests for legacy C, better tickets
