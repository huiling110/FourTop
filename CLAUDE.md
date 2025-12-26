# CLAUDE.md - FourTop Analysis AI Context

**Last updated**: 2025-12-26

---

## Critical Rules (ALWAYS FOLLOW)

1. **Use YAML configs** - Never hardcode paths. Always `--config CONFIG --era ERA`
2. **Environment first** - `source setEnv_newNew.sh` (except combine: use `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **Use workflow_utils** - All Python scripts use `from workflow_utils import ...`
5. **Commit often** - Commit after each significant code change, not batched
6. **Dev-docs lifecycle** - After plan approval, create dev-docs structure. Update frequently during execution
7. **READ SKILL BEFORE VERIFYING** - Before checking ANY stage output, READ the corresponding skill file first:
   - OS/Stage 1 → `.claude/skills/workflow-stage1-os/SKILL.md`
   - MV/Stage 2 → `.claude/skills/workflow-stage2-mv/SKILL.md`
   - WH/Stage 3 → `.claude/skills/workflow-stage3-wh/SKILL.md`
   - Combine/Stage 4 → `.claude/skills/workflow-stage4-combine/SKILL.md`
   **NEVER guess paths. Skills have the correct path patterns.**
8. **Proactive skill reading** - When user mentions OS/MV/WH/combine keywords, immediately read the skill BEFORE taking action

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

**Configs**: `config/analysis_config_{channel}_*.yaml`

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
| `config/analysis_config_*.yaml` | Analysis configurations - source of truth for versions |
| `plotting/workflow_utils.py` | Config loading, path building |
| `.claude/skills/workflow-stage*/SKILL.md` | Stage-specific commands and paths |
| `dev-docs/active/*/tasks.md` | Current task progress tracking |
| `setEnv_newNew.sh` | Environment setup (except combine) |

---

## User Preferences

- Physicist, experienced developer
- Direct feedback, explain *why* not just *how*
- Commit regularly, test before committing
- Physics safety: watch for sign errors, branch bugs

---

## AI Self-Correction Rules

When I make mistakes like checking wrong paths:
1. **Stop and read the skill file** - Don't continue guessing
2. **Use config to get version strings** - `stage1`, `stage2`, `hist` from YAML
3. **Follow the path pattern exactly** - Don't invent subdirectory structures
4. **When in doubt, list directories first** - `ls -d /publicfs/.../forMVA/2018/v1baselineHadro*`
