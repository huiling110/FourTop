# Context: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02
**Status**: COMPLETE ✅

---

## Problem Overview

The FourTop analysis workflow (Stage 3-4) requires manual path editing in multiple scripts for each analysis version. This creates errors and makes reproducibility difficult. Solution: centralized YAML config with versioning and a master workflow script.

---

## Key Files

### Configuration (Created)
- `config/analysis_config.yaml` - Active configuration
- `config/versions/config_v9BDT1tau0l_CMSNamingComplete.yaml` - Version snapshot

### Scripts Modified (All have --config support)
- `plotting/writeDatacard.py` - --config, --era, --smoothed, --quiet
- `plotting/addTemplateNew.py` - --config, --era, --quiet
- `plotting/addJESTemplatesToHistFile.py` - --config, --era, --quiet
- `plotting/smooth_systematics_fourTops.py` - --config, --era, --quiet
- `hua/combine/writeCombinationDatacard.py` - --config, --channel, --version, --quiet

### New Files Created
- `plotting/workflow_utils.py` - Config loading utilities
  - `load_config()` - Load YAML with validation
  - `build_hist_path()` - Build histogram directory path
  - `build_combine_path()` - Build combine directory path
  - `build_template_path()` - Build template ROOT file path
  - `build_datacard_path()` - Build datacard output directory
  - `get_template_suffix()` - Build suffix from options
  - `get_eras()`, `get_channel()`, `get_options()`
- `run_workflow.py` - Master workflow script
  - Stages 4.1, 4.2, 4.2.5, 4.3, 4.4 runners
  - --stage, --era, --list-stages, --save-version, --quiet

### Reference (Good Patterns)
- `hua/combine/runCombineAll.py` - Template for CLI design, logging, error handling

---

## Key Concepts

**Config Path Building**: All scripts use paths following pattern:
```
{base}/{era}/{out_version}_{in_version}/mc/variableHists_{hist_version}/
```

**Backward Compatibility**: Scripts work without --config (use hardcoded fallback)

**Stage Groups**:
- Stage 4.1: Consolidate shape systematics (addJESTemplatesToHistFile.py)
- Stage 4.2: Create template files (addTemplateNew.py)
- Stage 4.2.5: Smooth systematics (smooth_systematics_fourTops.py)
- Stage 4.3: Write datacards (writeDatacard.py)
- Stage 4.4: Combine era datacards (writeCombinationDatacard.py) - requires cmsenv

---

## Commits

| Commit | Description |
|--------|-------------|
| 36726cea | Phase 1: --quiet flags, duplicate function fix |
| 8759883a | Phase 1: Testing guideline in CLAUDE.md |
| 238f2e68 | Phase 2A: Config system, directory structure |
| a7835693 | Phase 2A: workflow_utils.py |
| d6e22275 | Phase 2B: --config for writeDatacard.py |
| 19fc919c | Phase 2B: --config for addTemplateNew.py |
| 4023e100 | Phase 2B: --config for addJES, smooth scripts |
| fa47bdf1 | Phase 2B: --config for writeCombinationDatacard.py |
| 014c1608 | Phase 2C: run_workflow.py master script |
| 6a6d0f3c | --quiet for addJESTemplatesToHistFile.py |
| 3a334827 | Task complete documentation |

---

## Commands

```bash
# Run full Stage 4 workflow
python3 run_workflow.py --stage 4

# Run single stage for one era
python3 run_workflow.py --stage 4.3 --era 2018 --smoothed

# List available stages
python3 run_workflow.py --list-stages

# Save config version
python3 run_workflow.py --save-version my_version_name

# Test config loading
source setEnv_newNew.sh
python3 -c "from plotting.workflow_utils import load_config; print(load_config())"
```

---

## Known Issues

1. **Stage 4.1 JES Path Pattern**: The JES directory path construction in `addJESTemplatesToHistFile.py` doesn't match the v9 version naming convention. Needs separate fix if JES consolidation is required.

2. **Stage 4.4 Environment**: `writeCombinationDatacard.py` requires `cmsenv` (CMSSW environment), not `setEnv_newNew.sh`.
