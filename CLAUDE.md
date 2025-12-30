# CLAUDE.md - FourTop Analysis AI Context

**Last updated**: 2025-12-30

---

## Critical Rules (ALWAYS FOLLOW)

1. **Use YAML configs** - Never hardcode paths. Always `--config CONFIG --era ERA`
2. **Environment first** - `source setEnv_newNew.sh` (except combine: use `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **Use workflow_utils** - All Python scripts use `from workflow_utils import ...`
5. **Commit often** - Commit after each significant code change, not batched
6. **Dev-docs lifecycle** - After plan approval, create dev-docs structure. Update frequently during execution
7. **INVOKE SKILL BEFORE PATH CHECKS (MANDATORY - ENFORCED BY HOOK)**

   The pre-tool-use hook BLOCKS `ls`/`find` on stage paths until skill is invoked.

   **Before checking ANY stage output paths, follow this protocol:**

   Step 1 - EVALUATE: Which stage am I checking?
   - `/tauOfTTTT_NanoAOD/UL*` (not forMVA) → Stage 1 OS
   - `/forMVA/` or `*baselineHadro*` → Stage 2 MV
   - `variableHists_*` → Stage 3 WH
   - `datacard/` or `combine/` → Stage 4 Combine

   Step 2 - ACTIVATE: Use Skill() tool NOW
   ```
   Skill("workflow-stage1-os")  # for OS paths
   Skill("workflow-stage2-mv")  # for MV paths
   Skill("workflow-stage3-wh")  # for WH paths
   Skill("workflow-stage4-combine")  # for combine paths
   ```

   Step 3 - IMPLEMENT: Only after activation, run ls/verification commands

   **CRITICAL: Hook WARNS if skill not recently invoked. Follow the 3-step protocol.**

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
1. **If hook blocks you** - Invoke the skill it requests, then retry
2. **Use config to get version strings** - `stage1`, `stage2`, `hist` from YAML
3. **Follow the path pattern exactly** - Don't invent subdirectory structures
4. **Skill has verification commands** - Use them, don't invent your own

## Hook Enforcement

The `pre-tool-use.sh` hook WARNS when checking stage paths without recent skill invocation:
- Detects `ls`/`find` on `/forMVA/`, `variableHists_`, etc.
- Shows warning if skill wasn't invoked in last 30 minutes
- Marker file created by `user-prompt-submit.sh` when keywords detected

**For Skill() tool invocations**, manually create marker after invoking:
```bash
echo "$(date +%s)" > /tmp/.claude_skill_workflow-stage2-mv_$USER
```
