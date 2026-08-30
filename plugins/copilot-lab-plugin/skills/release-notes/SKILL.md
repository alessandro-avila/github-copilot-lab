---
name: release-notes
description: Drafts release notes from a set of changes. Use when the user asks for release notes, a changelog entry, a "what's new" summary, or wants to describe a release to end users.
metadata:
  author: Microsoft
  version: "1.1.1"
---

# Release notes writer

Turn a list of changes into release notes an end user can actually understand.

## Steps

1. Collect the changes. Ask the user for a commit range, a list of merged pull
   requests, or a plain description of what shipped.

2. Group them under these headings, dropping any heading with nothing in it:
   - **Added** — new capability
   - **Changed** — different behaviour for something that already existed
   - **Fixed** — a bug that users noticed
   - **Security** — anything with a vulnerability implication

3. Rewrite each entry from the user's point of view. `Refactored the order
   service` is not a release note. `Orders now load about twice as fast` is.

4. Put anything that requires action from the user in a **Breaking changes**
   section at the very top, with migration steps.

## Rules

- No commit hashes, branch names or internal ticket IDs in the output.
- One line per change. If it needs a paragraph, it needs its own section.
- Say the version and date at the top.
- Omit internal refactors entirely unless they changed something observable.

## Why this lives in a plugin

This skill is identical in format to `.github/skills/adr-writer/`. The only
difference is distribution: a plugin bundles it with an MCP server and a custom
agent so a team installs the whole set in one step instead of copying folders.
