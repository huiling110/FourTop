# Context: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02 14:55
**Status**: Phase 3D Testing Blocked - Missing stages 4.3.2/4.3.5

---

## Problem Overview

The FourTop analysis workflow (Stage 3-4) requires manual path editing in multiple scripts for each analysis version. This creates errors and makes reproducibility difficult. Solution: centralized YAML config with versioning and a master workflow script.

---

## Key Files

### Configuration
- `config/analysis_config.yaml` - Active configuration
- `config/versions/config_v9BDT1tau0l_CMSNamingComplete.yaml` - Version snapshot

### Scripts Modified (All have --config support)
- `plotting/writeDatacard.py` - --config, --era, --smoothed, --quiet
- `plotting/addTemplateNew.py` - --config, --era, --quiet
- `plotting/addJESTemplatesToHistFile.py` - --config, --era, --quiet (+ QUIET global flag)
- `plotting/smooth_systematics_fourTops.py` - --config, --quiet (NO --era, processes all at once)
- `hua/combine/writeCombinationDatacard.py` - --config, --channel, --version, --quiet

### New Files Created
- `plotting/workflow_utils.py` - Config loading utilities
- `run_workflow.py` - Master workflow script
- `.claude/hooks/check_python_quality.py` - AST-based quality checker
- `.claude/hooks/post-tool-use.sh` - Post-edit quality hook
- `.claude/skills/refactor.md` - Refactoring skill
- `.claude/commands/review-code.md` - Code review command

---

## Key Concepts

**Config Path Building**: All scripts use paths following pattern:
```
{base}/{era}/{out_version}_{in_version}/mc/variableHists_{hist_version}/
```

**Stage Types**:
- Per-era stages: 3.3, 3.3.1, 4.1, 4.2, 4.3 (run once per era)
- Global stages: 3.4, 4.2.5, 4.4, 4.5, 4.6 (run once for all eras)

**Output Path Logging**: Each stage logs its output path via `get_output_paths()` function.

---

## Current Blocker

**Stage 4.4 cannot run** because:
1. Per-era datacards exist at: `datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`
2. But they need to be copied/linked to the combine directory
3. Missing stages 4.3.2 and 4.3.5 (user identified)

**User clarification needed**: What do stages 4.3.2 and 4.3.5 do?

---

## Commits (Session 2)

| Commit | Description |
|--------|-------------|
| ac3aa7e4 | fix: Update config to use correct datacard and combination paths |
| 61cb0287 | feat: Add output path logging and fix Stage 4.2.5 + quiet mode |
| 0151d378 | refactor: Improve run_workflow.py code quality and add review tools |

---

## Commands

```bash
# Run FULL pipeline (Stage 3 + Stage 4)
python3 run_workflow.py --stage all --config config/analysis_config.yaml -l workflow.log

# Run Stage 4 only (templates → datacards → combine)
python3 run_workflow.py --stage 4 --config config/analysis_config.yaml

# Run single stage
python3 run_workflow.py --stage 4.3 --era 2018

# Check code quality
python3 .claude/hooks/check_python_quality.py run_workflow.py

# For Stage 4.4/4.5 (requires cmsenv):
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src
source /cvmfs/cms.cern.ch/cmsset_default.sh && eval `scramv1 runtime -sh`
cd FourTop && python3 run_workflow.py --stage 4.5 --config config/analysis_config.yaml
```

---

## Known Issues

1. **Stage 4.2.5**: Script processes all eras at once (not per-era). Fixed in workflow.

2. **Stage 4.4/4.5**: Blocked - need missing stages 4.3.2 and 4.3.5 to copy datacards.

3. **pl_postFit.py quality**: 7 errors, 11 warnings. Needs refactoring.

---

## Performance Notes

- Stage 3.3 (nominal jobs): ~30s per era
- Stage 3.3.1 (systematic jobs): ~34 min per era (parallel: ~35 min total)
- Stage 4 (analysis): ~5-10 min total
