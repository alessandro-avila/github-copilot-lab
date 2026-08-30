# Copilot Lab plugin

A reference plugin for the GitHub Copilot Up skilling lab.

## Important

A plugin folder sitting inside a repository is **not** discovered or loaded. VS
Code and Copilot CLI install plugins from a marketplace or a Git URL into
`~/.copilot/installed-plugins/`. This copy is here so you can see the anatomy
without installing anything.

To actually install a plugin from source:

- **VS Code** — run `Chat: Install Plugin From Source` and give it a Git URL
- **CLI** — `copilot plugin install PLUGIN-NAME@MARKETPLACE-NAME`

## Anatomy

| Path | Portable | What it contributes |
| ---- | -------- | ------------------- |
| `plugin.json` | yes | Manifest. The `$schema` value is what marks this as Agent Plugins 1.0 |
| `skills/release-notes/SKILL.md` | yes | A skill, identical in format to a repo-level one |
| `mcp.json` | yes | MCP servers that start when the plugin is enabled |
| `com.github.copilot/agents/` | no | Copilot-specific custom agent |

Skills and MCP servers are part of the open standard, so any compatible agent
picks them up. Agents, hooks and slash commands are client-specific, so they live
under a reverse-domain namespace that other clients ignore. That is how one
package stays portable while still shipping Copilot-only capabilities.

## The point

Everything in this plugin could have been loose files in `.github/`. Packaging
them means a colleague runs one install command instead of copying four folders
and hoping they landed in the right place.

## Related

- [Cheatsheet](../../docs/CHEATSHEET.md)
- [Demo script](../../README.md)
