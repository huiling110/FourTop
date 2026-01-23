# CLAUDE.md - FourTop Analysis

## Project Overview

**CMS four-top (tttt) measurement and VLL search in hadronic tau channels**

| Channel | Description | Trigger |
|---------|-------------|---------|
| 1tau0l | 1 hadronic tau, 0 leptons | HT-based (shared) |
| 1tau1l | 1 hadronic tau, 1 lepton | HT-based (shared) |
| 1tau2l | 1 hadronic tau, 2 leptons | Different trigger |

**Note**: 1tau0l and 1tau1l share OS and MV steps (same triggers).

## Critical Rules

1. **Config-driven** - Always `--config CONFIG --era ERA`, never hardcode paths
2. **Environment** - `source setEnv_newNew.sh` (combine: `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **ALWAYS invoke stage skill first** - Before ANY stage work, ASK: "Which stage am I in?" then invoke `/workflow-stage{1-4}*`. This applies to:
   - Running stage commands (submit jobs, run combine, etc.)
   - Checking stage outputs or paths
   - Debugging stage issues
   - Continuing interrupted stage work
5. **Commit often** - After each significant change
6. **Dev-docs for new tasks** - After exiting plan mode, create `dev-docs/active/{task}/` with:
   - `context.md` - Goal, key paths, environment, critical notes
   - `plan.md` - Implementation approach, dependencies, risks
   - `tasks.md` - Status table, session notes, next steps

## Workflow

**Stage skills** (invoke for commands, paths, verification):
- `/workflow-stage1-os` - Object Selection
- `/workflow-stage2-mv` - Make Variables + Fakes
- `/workflow-stage3-wh` - Write Histograms
- `/workflow-stage4-combine` - Templates, Datacards, Combine

**Progress tracking**: `dev-docs/active/{task}/tasks.md` with status table

**Config**: `config/analysis_config_{channel}_*.yaml`

## Dev-Docs

For multi-session tasks in `dev-docs/active/{task}/`:
- Read `tasks.md` to resume
- Update frequently, commit often
- When context low, update dev-docs before ending

## User Preferences

- Physicist, experienced developer
- Direct feedback, explain *why* not just *how*
- Physics safety: watch for sign errors, branch bugs

## Python Package

Use `fourtop` package for all Python imports. For full API reference: `/python-package-guide`
