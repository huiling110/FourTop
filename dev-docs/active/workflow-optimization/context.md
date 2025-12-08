# Context: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-08 (Session 3)
**Status**: IN PROGRESS

---

## Problem Statement

The FourTop analysis workflow has grown organically with inconsistent config patterns:
- ~320 commented-out hardcoded paths across scripts (NOW REMOVED)
- 4+ different config loading patterns (NOW STANDARDIZED)
- No single source of truth for path building (NOW: workflow_utils.py)
- Unclear which config parameters are essential (NOW: minimal config schema)

---

## Key Files

### Config System
- `config/analysis_config_template.yaml` - **NEW** Minimal config template (created Phase 1)
- `config/analysis_config_1tau0l_full.yaml` - 1tau0l channel config
- `config/historical_paths_backup.txt` - **NEW** Backup of 385 commented paths
- `plotting/workflow_utils.py` - **UPDATED** Path building utilities with `_normalize_config()`, `get_regions()`, `get_versions()`
- `run_workflow.py` - Master workflow runner

### Cleaned Scripts (Phase 2 Complete)

| Script | Status | Paths Removed |
|--------|--------|---------------|
| `plotting/createFaketauTree.py` | ✅ Done | ~35 |
| `plotting/addJESTemplatesToHistFile.py` | ✅ Done | ~100 |
| `plotting/addTemplateNew.py` | ✅ Done | ~75 |
| `plotting/writeDatacard.py` | ✅ Done | ~110 |

All scripts now require: `--config CONFIG --era ERA` (no fallback to hardcoded paths)

### Scripts to Refactor (Pending)

**Phase 3: Stage 2.4**
- `plotting/createFakeLeptonTree.py` - Add argparse

**Phase 4: Stage 3**
- `writeHistGood/jobs/makeJob_forWriteHist.py` - Add workflow_utils

**Phase 5: Stage 1-2**
- `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` - Standardize
- `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` - Add argparse

### Claude Integration ✅ COMPLETE
- `.claude/skills/workflow.md` - Analysis pipeline skill with stage commands, workflow_utils pattern
- `.claude/hooks/pre-tool-use.sh` - Environment check, setEnv path validation
- `.claude/hooks/user-prompt-submit.sh` - Auto-activation based on workflow keywords
- `plotting/pl.py` - **REFACTORED** to use workflow_utils, ~200 lines removed

---

## Config Schema (New Minimal Format)

```yaml
metadata:
  name: "analysis_name"
  description: "Description"
  created: "YYYY-MM-DD"

versions:
  stage1: "v94HadroPreJetVetoHemOnly"      # Object selection
  stage2: "v1baselineHadro"                 # Variable calculation
  hist: "v0BDT1tau0l"                       # Histogram
  datacard: "v1"                            # Datacard
  combination: "combinationV21"             # Combine

channel: "1tau0l"   # 1tau0l, 1tau1l, 1tau2l

eras:
  - "2018"
  - "2017"
  - "2016preVFP"
  - "2016postVFP"

options:
  fake_tau: true
  mc_fake_tau: false
  blind: false
  systematics: true
  smoothing: false

paths:
  nanoaod_base: "/publicfs/cms/data/TopQuark/nanoAOD"
  output_base: "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD"
```

---

## Path Structure Reference

```
Stage 1 Input:  /publicfs/cms/data/TopQuark/nanoAOD/{YEAR}/mc/
Stage 1 Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL{ERA}/{STAGE1_VERSION}/mc/
Stage 2 Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{ERA}/{STAGE2}_{STAGE1}/mc/
Stage 3 Output: .../mc/variableHists_{HIST_VERSION}/
Stage 4 Combine: .../combine/
Stage 4.4/4.5: hua/combine/{COMB_VERSION}/run2_{CHANNEL}_{DC_VERSION}/
```

---

## Environment Requirements

| Stages | Environment | Command |
|--------|-------------|---------|
| 1, 2, 2.4, 3, 4.1-4.3, 4.6 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.4, 4.5 | CMSSW/Combine | `cmsenv` |

---

## Commands

```bash
# Source environment first
source setEnv_newNew.sh

# Run Stage 4 scripts with config
python3 plotting/createFaketauTree.py --config config/analysis_config_1tau0l_full.yaml --era 2018
python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau0l_full.yaml --era 2018
python3 plotting/addTemplateNew.py --config config/analysis_config_1tau0l_full.yaml --era 2018
python3 plotting/writeDatacard.py --config config/analysis_config_1tau0l_full.yaml --era 2018

# Test script help
python3 plotting/createFaketauTree.py --help
python3 plotting/addJESTemplatesToHistFile.py --help

# Check workflow_utils functions
python3 -c "from plotting.workflow_utils import *; help(load_config)"
```

---

## Key Commits

1. `4ab2fd5a` - Phase 1: Minimal config schema, workflow_utils updates
2. `d976f909` - createFaketauTree.py cleanup
3. `92637fe6` - addJESTemplatesToHistFile.py cleanup
4. `ae92a076` - addTemplateNew.py cleanup
5. `a0a9e5d7` - writeDatacard.py cleanup
6. `dd63c875` - Create workflow skill and hooks
7. `444ff113` - Update pl.py to read options from YAML config
8. `cc1be1c7` - refactor: Clean up pl.py to use workflow_utils consistently
9. `26037fa0` - docs: Update workflow skill with workflow_utils pattern
