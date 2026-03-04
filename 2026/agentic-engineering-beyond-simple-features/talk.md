# Agentic Engineering: Beyond Simple Features

## Agenda

- Demo of some of my recent side-projects
- AGENTS.md / CLAUDE.md
- PLANS.md
- The docs/ directory
- Closing the loop
- Claude vs. Codex
- Discussion

## What this talk is not about

- Setting up and using SKILLS. They obviously work and are really good. If you don't use them, start today. No point to spend more time on this.
- Setting up and using MCPs. If you want my take, I personally don't use them.
- Ergonomics
- Instead, we'll focus on achieving better results for complex work.

## Demo

- Vigil
- [Mirage](https://github.com/devinitive-team/mirage)
- [Mirage Launch Video](<https://www.youtube.com/watch?v=BrIUXE-wt88>)

## AGENTS.md / CLAUDE.md

- Context is a scarce resource
- Models' ability to reason declines as context grows bigger
  - <https://arxiv.org/pdf/2508.19363>
  - <https://arxiv.org/pdf/2509.21361v1>
  - <https://whatllm.org/blog/best-long-context-models-january-2026>
- One big AGENTS.md / CLAUDE.md doesn't work well in my experience
- "[...] instead of treating AGENTS.md as the encyclopedia, we treat it as the table of contents."
  - Key insight
- Personal vs. Project
  - Personal: Under `${HOME}./codex/AGENTS.md` or `${HOME}/.claude/CLAUDE.md`
  - Project: `AGENTS.md` or `CLAUDE.md` at the project root.
- What I keep in my AGENTS.md?
  - Personal is really minimal; just a few lines of code.
  - Project one is a bit longer, describes ExecPlans (more on that later), workflow and ToC.
- Don't be afraid to change it
  - It's supposed to be a living thing.
  - With every new leap in models' performance, you likely have to adapt your files.
  - Remember when we used to type "IMPORTANT: YOU MUST DO <blah> <blah> <blah>"?

## PLANS.md

- Enables the coding agent to run autonomously for longer periods of time
  - In my experience, you can fairly easily prompt it to run for 30+ minutes.
  - If you're careful with your prompt, you can get it to run for multiple hours.
  - My longest autonomous session was a bit more than 2 hours.
- Works extremely well with Codex / GPT 5.3 Codex; Not so well with Claude Code / Opus 4.6
  - In my experience, Claude rushes to finish the problem, where as Codex will take much more thorough approach.
  - As a result, it's hard to get Claude run autonomously for more than 30 minutes.
- It's similar, but not the same as "Plan Mode"
  - Actually, I recommend disabling plan mode when you use "ExecPlans".
  - In my opinion/experience, it works much better than "Plan Mode" for the most complex tasks.
  - For low / medium complexity features, stick to built-in Plan Mode.
- What's inside of PLANS.md?

## The docs/ directory

- Making repository the system of record is a game changer
- Must have for any codebase that grows beyond a few thousand lines of code
- I keep the repository knowledge base simply under `docs/`
  - When we talked about using AGENTS.md as ToC, the `docs/` directory is what you want to index.
- Layout

  ```
  AGENTS.md
  docs/
  ├── design-docs/              design decisions & rationale
  ├── exec-plans/
  │   ├── active/               in-flight implementation plans
  │   ├── completed/            finished plans (date-prefixed)
  │   └── tech-debt-tracker.md
  ├── generated/                screenshots & visual artifacts
  ├── product-specs/            feature specifications
  ├── references/               external docs & vendored SDKs
  ├── ARCHITECTURE.md
  ├── DESIGN.md
  ├── FRONTEND.md
  ├── LESSONS.md
  ├── PLANS.md
  ├── PRODUCT_SENSE.md
  ├── QUALITY.md
  ├── RELIABILITY.md
  └── SECURITY.md
  ```

- Gardening instructions in AGENTS.md / QUALITY.md are not enough in my experience
  - You will still want to run reconciliation yourself from time to time
  - I created a "Doc Gardening" skill I execute every now and then

## Closing the loop

- The agent MUST be able to test whatever it produced
- Unit and integration tests are not enough, unless you develop some deep systems code
- You have to make your agent actually USE the product it's building
- For browsers, I found the `agent-browser` skill to work really nicely
  - <https://skills.sh/vercel-labs/agent-browser/agent-browser>
- For CLIs and TUIs, I found `agent-tui` and `tui-explorer` skills to work really well
  - <https://github.com/pproenca/agent-tui/tree/master>
- Try these out, you'll be surprised how far they can get you

## Claude vs. Codex

- Both are excellent in my experience, especially since the release of Opus 4.5 and Codex 5.2 late last year
- I find that Claude has "better taste"
  - Claude will run circles around Codex on any UI / Design work (example: Remotion video from the hackathon)
  - Codex is much better at long-running tasks and coding in general.
  - That said, sometimes where Codex fails, Claude does just fine.
  - So... what's my advise? Just use both. For really hard work, make the cross-check each other.

## Closing note

- When I was referring to Claude / Codex models, I always:
  - Had the latest and greatest model in mind, aka. Claude Opus 4.6 and GPT Codex 5.3
  - Both running on the highest reasoning / thinking levels.
  - Anything below that... well, IMO it's a waste of time.

## Discussion

- What's your experience? Curious to find out.

## References

- <https://developers.openai.com/cookbook/articles/codex_exec_plans>
- <https://openai.com/index/harness-engineering/>
- <https://simonwillison.net/guides/agentic-engineering-patterns/>
- <https://matklad.github.io/2021/02/06/ARCHITECTURE.md.html>
