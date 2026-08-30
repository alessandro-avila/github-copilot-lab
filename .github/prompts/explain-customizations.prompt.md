---
name: 'explain-customizations'
description: 'Audit this repository and explain every Copilot customization it contains'
agent: 'agent'
tools: ['search', 'edit/editFiles']
---

# Explain the customizations in this repository

You are helping someone who has just cloned this lab and wants to understand what
is configured and why.

## Steps

1. Find every customization file in the workspace. Look for:
   - `.github/copilot-instructions.md`
   - `.github/instructions/*.instructions.md`
   - `.github/prompts/*.prompt.md`
   - `.github/skills/*/SKILL.md`
   - `.github/agents/*.agent.md`
   - `.vscode/mcp.json` and `.mcp.json`
   - `plugins/*/plugin.json`

2. For each file, report:
   - its path
   - which primitive it demonstrates
   - how it gets invoked — always on, glob-matched, slash command, model-invoked,
     or tool call
   - one sentence on what it actually does here

3. Present the result as a single table, ordered from most automatic to most
   explicit.

4. Close with the one thing you think is least obvious to a newcomer.

## Constraint

Report only what you actually find on disk. If a file listed above is missing, say
so rather than describing what it would contain.
