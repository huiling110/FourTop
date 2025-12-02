# Context: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02

---

## Problem Overview

The FourTop analysis workflow (Stage 3-4) requires manual path editing in multiple scripts for each analysis version. This creates errors and makes reproducibility difficult. Solution: centralized YAML config with versioning and a master workflow script.

---

## Key Files

### Configuration (New)
- `config/analysis_config.yaml` - Active configuration
- `config/versions/config_v9BDT1tau0l_CMSNamingComplete.yaml` - Version snapshot

### Scripts to Modify (Phase 2B)
- `plotting/writeDatacard.py` - Add --config, --era args
- `plotting/addTemplateNew.py` - Add --config, --era args
- `plotting/addJESTemplatesToHistFile.py` - Add --config, --era args
- `plotting/smooth_systematics_fourTops.py` - Add --config, --era args
- `hua/combine/writeCombinationDatacard.py` - Add --config support

### New Files Created
- `plotting/workflow_utils.py` - Config loading utilities (DONE)
  - `load_config()`, `build_hist_path()`, `build_combine_path()`
  - `build_template_path()`, `build_datacard_path()`, `get_template_suffix()`
- `run_workflow.py` - Master workflow script (TODO)

### Reference (Good Patterns)
- `hua/combine/runCombineAll.py` - Template for CLI design, logging, error handling

---

## Key Concepts

**Config Path Building**: All scripts use paths following pattern:
```
{base}/{era}/{out_version}_{in_version}/mc/variableHists_{hist_version}/
```

**Backward Compatibility**: Scripts must work without --config (use hardcoded fallback)

**Stage Groups**:
- Stage 3: 3.3 (nominal jobs), 3.4 (systematic jobs), 3.5 (status check)
- Stage 4: 4.1-4.4 (templates → datacards → combine)

---

## Commits

| Commit | Description |
|--------|-------------|
| 36726cea | Phase 1: --quiet flags, duplicate function fix |
| 8759883a | Phase 1: Testing guideline in CLAUDE.md |
| 238f2e68 | Phase 2A: Config system, directory structure |

---

## Commands

```bash
# Resume this task
/resume-task workflow-code-quality

# Test config loading (after workflow_utils.py created)
source setEnv_newNew.sh
python3 -c "from plotting.workflow_utils import load_config; print(load_config())"

# Run workflow (after run_workflow.py created)
python3 run_workflow.py --config config/analysis_config.yaml --stages 4
```
