# CLAUDE.md - FourTop Analysis

## Critical Rules

1. **Config-driven** - Always `--config CONFIG --era ERA`, never hardcode paths
2. **Environment** - `source setEnv_newNew.sh` (combine: `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **Invoke skill before path checks** - Use `/workflow-stage{1-4}*` before checking stage outputs
5. **Commit often** - After each significant change

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
