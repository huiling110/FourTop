# CLAUDE.md - FourTop Analysis AI Context

**Last updated**: 2025-12-24

---

## Critical Rules (ALWAYS FOLLOW)

1. **Use YAML configs** - Never hardcode paths. Always `--config CONFIG --era ERA`
2. **Environment first** - `source setEnv_newNew.sh` (except combine: use `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **Use workflow_utils** - All Python scripts use `from workflow_utils import ...`
5. **Commit often** - Commit after each significant code change, not batched
6. **Dev-docs lifecycle** - After plan approval, immediately create dev-docs structure (`plan.md`, `context.md`, `tasks.md`). **Update dev-docs frequently during execution** - After major milestones, before commits, or when tasks complete. Essential for later review of plan progress
7. **Workflow state first** - Before ANY workflow operation (checking jobs, verifying outputs, etc.), read `.workflow/state.json` to get concrete paths. This file contains computed paths for all eras - never guess directory structures.
8. **Stage skills auto-discover** - Stage-specific skills are now auto-discovered based on keywords:
   - `workflow-stage1-os` - OS, NanoAOD, skimmed, held jobs, jetHT, resubmit
   - `workflow-stage2-mv` - MV, BDT, fake tau, fake lepton, FR_weight
   - `workflow-stage3-wh` - WH, histograms, variableHists, systematic
   - `workflow-stage4-combine` - combine, datacard, template, limits, postfit

For general workflow overview, see `.claude/skills/workflow/overview.md`

---

## Project Overview

**CMS Four-Top Quark Analysis** - tttt production and VLL searches

**Channels**: `1tau0l`, `1tau1l`, `1tau2l`

**Pipeline**:
| Stage | Abbrev | Directory | Purpose |
|-------|--------|-----------|---------|
| 1 | OS | `objectSelectionOptimized/` | NanoAOD → skimmed ntuples |
| 2 | MV | `makeVariables_goodCode/` | Add BDT scores |
| 2.4 | - | `makeVariables_goodCode/` | Fake background estimation |
| 3 | WH | `writeHistGood/` | Histogram production |
| 4 | PL | `plotting/` | Plots, templates, datacards |
| 4.5 | - | `hua/combine/` | Statistical fits |

**Configs**: `config/analysis_config_{channel}_TTBBtest.yaml`

---

## Dev-Docs System

**Location**: `dev-docs/active/[task-name]/`

For multi-session tasks:
1. Check `dev-docs/active/` for existing tasks before starting
2. Read `plan.md`, `context.md`, `tasks.md` to resume
3. Update files regularly, commit often
4. Use `/update-dev-docs` command to sync progress

**Context preservation**: When context low (~10%), update dev-docs and commit before ending.

---

## Build & Submit

```bash
# Build C++ code
cd writeHistGood/ && source ../setEnv_newNew.sh && make

Test locally: mkdir -p /publicfs/.../variableHists_VERSION && ./apps/run_treeAnalyzer.out INPUT_DIR/ PROCESS CHANNEL VERSION IFSYS ISTEST ERA

# Submit jobs (use config!)
python3 makeJob_forWriteHist.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

# Monitor
hep_q -u $USER
```

---

## Key Files

| File | Purpose |
|------|---------|
| `.workflow/state.json` | **Workflow state with concrete paths** - READ THIS FIRST |
| `plotting/workflow_utils.py` | Config loading, path building |
| `config/analysis_config_*.yaml` | Analysis configurations |
| `.claude/skills/workflow-stage*` | Auto-discovered stage skills |
| `setEnv_newNew.sh` | Environment setup |

---

## User Preferences

- Physicist, experienced developer
- Direct feedback, explain *why* not just *how*
- Commit regularly, test before committing
- Physics safety: watch for sign errors, branch bugs

---

*Stage skills auto-discovered: workflow-stage1-os, workflow-stage2-mv, workflow-stage3-wh, workflow-stage4-combine*
