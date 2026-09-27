# Challenge 2: better implementation tickets

You turn a vague business request into a ticket a developer can start on: Copilot drafts it, and you answer its questions and decide what goes in.

| Item | Details |
| ---- | ------- |
| Time | 45–60 minutes, in pairs: one of you plays the product owner, the other the developer |
| Input | Three [business requests](business-requests/): an e-mail, meeting notes and a one-liner |
| Copilot | Agent mode, the prompt file [`/refine-ticket`](../../.github/prompts/refine-ticket.prompt.md), repository search, optionally a Jira MCP server |

## What you need

| Need | Details |
| ---- | ------- |
| Editor | VS Code or Visual Studio 2026, with the repository root open. Visual Studio needs custom instructions switched on, see [Before you start](../README.md#before-you-start) |
| Template | [ticket-template.md](ticket-template.md): the Definition of Ready on one screen |
| Jira | Optional. Without it, you copy the finished ticket into Jira by hand |

The prompts below use VS Code syntax. Visual Studio 2026 uses the same `/` commands; in older versions, type `#prompt:` and pick the prompt instead.

## Steps

### 1. Spot the problems (5 minutes)

Read [poor-ticket.md](examples/poor-ticket.md), written straight from the operations e-mail. Before you read the "What is wrong with it" table, list what a developer would have to ask before starting.

### 2. Refine the e-mail (20 minutes)

1. Run:

   ```
   /refine-ticket challenges/02-better-tickets/business-requests/01-operations-email.md
   ```

2. Copilot asks up to three questions. The product owner answers. If you do not know an answer, say so: Copilot must then list it as an open question, not make one up.
3. Check the draft against the "Ready when" table in [ticket-template.md](ticket-template.md).
4. Compare it with [improved-ticket.md](examples/improved-ticket.md). What did Copilot miss? What did it invent? Did it find `legacy-c/sorter.c` and the counter that carries over?

### 3. Refine the one-liner (10 minutes)

```
/refine-ticket challenges/02-better-tickets/business-requests/03-one-liner.md
```

"Make the sorter faster" has no numbers at all. Good output asks what "faster" means and lists assumptions. Bad output invents a target such as "20% faster".

### 4. Refine the meeting notes (15 minutes)

```
/refine-ticket challenges/02-better-tickets/business-requests/02-meeting-notes.md
```

The notes mix several topics. Copilot should list them and ask which one to refine: pick "the time thing". Check "Affected code areas": does it point at the hour calculation in `legacy-c/sorter.c`?

## Done when

| Check | How you know |
| ----- | ------------ |
| E-mail ticket | You filled in every section of the template or marked it "none", and the acceptance criteria are Given/When/Then with concrete values |
| No inventions | Every number in your tickets came from the request, from your answers or from the code. Everything else sits under open questions or assumptions |
| One-liner | Copilot asked before it wrote, and the ticket has no made-up targets |
| From ticket to code | The e-mail ticket names `legacy-c/sorter.c` and says which sorter spec scenarios change |

There is no single right ticket. [improved-ticket.md](examples/improved-ticket.md) shows one good answer for the e-mail. To take it all the way to tested code, do the stretch step of [Challenge 1](../01-legacy-c-testable/README.md#stretch-change-behaviour-spec-first).

## Connect Copilot to Jira (optional)

An MCP server lets Copilot read and create Jira issues for you. Which one you use depends on where your Jira runs.

| Your Jira | MCP server | Notes |
| --------- | ---------- | ----- |
| Jira Cloud | Atlassian's official Rovo MCP server | Works with Atlassian Cloud only |
| Jira Server or Data Center | The community server [mcp-atlassian](https://github.com/sooperset/mcp-atlassian) | Open source (MIT), not an Atlassian product. Supports Jira Server/Data Center 8.14 and later with a personal access token, set through `JIRA_URL` and `JIRA_PERSONAL_TOKEN`. Runs on your machine with `uvx mcp-atlassian` and offers tools such as `jira_search`, `jira_get_issue` and `jira_create_issue` |

Before you connect anything:

- Get your organisation's security approval. The server acts in Jira with your permissions and runs code on your machine.
- Never commit a token. [jira-mcp.example.jsonc](jira-mcp.example.jsonc) asks for it when the server starts, and VS Code stores it securely.

To try mcp-atlassian in VS Code, copy the entry from [jira-mcp.example.jsonc](jira-mcp.example.jsonc) into your user MCP configuration (**MCP: Open User Configuration**), set `JIRA_URL`, and start the server from **MCP: List Servers**. You need `uv` installed for `uvx`. Then run `/refine-ticket` again: when the ticket is ready, Copilot offers to create it and waits for your yes.

No Jira connection? Copy the finished ticket into Jira by hand. Everything else in this challenge works the same.

## Related

- [Ticket template](ticket-template.md)
- [Challenges](../README.md)
- [Challenge 1: specs you can test](../01-legacy-c-testable/README.md)
