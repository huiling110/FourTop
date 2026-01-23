# CLAUDE.md - FourTop Analysis

<!-- Keep this file under 50 lines. Move details to skills or .claude/rules/ -->

## Project Overview

CMS four-top (tttt) measurement in hadronic tau channels: 1tau0l, 1tau1l, 1tau2l.

## Critical Rules

1. **Config-driven** - Always `--config CONFIG --era ERA`, never hardcode paths
2. **Environment** - `source setEnv_newNew.sh` (combine: `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **Invoke stage skill first** - Before stage work, invoke `/workflow-stage{1-4}*`
5. **Commit often** - After each significant change
6. **Dev-docs for tasks** - Create `dev-docs/active/{task}/` with context.md, plan.md, tasks.md

## Skills

| Skill | Purpose |
|-------|---------|
| `/workflow-stage1-os` | Object Selection commands |
| `/workflow-stage2-mv` | Make Variables + Fakes |
| `/workflow-stage3-wh` | Write Histograms |
| `/workflow-stage4-combine` | Templates, Datacards, Combine |
| `/python-package-guide` | fourtop package API reference |
| `/refactor` | Python code refactoring |

## Quick Reference

- **Config**: `config/analysis_config_{channel}_*.yaml`
- **Progress**: `dev-docs/active/{task}/tasks.md`
- **Python imports**: Use `fourtop` package, never `sys.path` hacks

## User Preferences

- Physicist, experienced developer - direct feedback, explain *why*
- Physics safety: watch for sign errors, branch bugs
