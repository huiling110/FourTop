# Context: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-09 (Session 7)
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
- `config/analysis_config_1tau0l_TTBBtest.yaml` - 1tau0l channel config (renamed)
- `config/analysis_config_1tau1l_TTBBtest.yaml` - 1tau1l channel config
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

### Phase 5: Stage 1 ✅ COMPLETE

- `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` - **REFACTORED** to use workflow_utils
- `objectSelectionOptimized/jobs/submit_all_systematics.sh` - **NEW** Batch submission for 15 systematics
- `objectSelectionOptimized/jobs/check_systematic_jobs.sh` - **NEW** Job status monitoring

### Phase 5: Stage 2 ✅ COMPLETE

- `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` - **REFACTORED** to use workflow_utils
- `makeVariables_goodCode/jobs/makeJob_MV_JESVariation.py` - **REFACTORED** for batch systematic submission
- `plotting/workflow_utils.py` - **ADDED** `build_stage2_output()` function
- `run_workflow.py` - **ADDED** Stage 1, 1.1, 2, 2.1 support

### Phase 5: Stage 3.1 ✅ COMPLETE

- `writeHistGood/jobs/makeJob_WH_forJES.py` - **REFACTORED** to use workflow_utils
  - Added argparse: --config (required), --era, --group (TES/JER/MET/EleScale/all), --dry-run, --quiet
  - Uses workflow_utils: load_config, build_stage2_output, get_channel, get_versions
  - Removed all commented-out hardcoded paths

### JES Path Format (IMPORTANT)

JES directories use **full source names** including `_AK4PFchs` suffix:
```
v1baselineHadro_JES{Up/Down}_{SOURCE}_AK4PFchs_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22
```

Example sources: `AbsoluteMPFBias`, `AbsoluteScale`, `FlavorPureBottom`, `Total`, etc.

The `_AK4PFchs` suffix is part of the JES source name from `ttttGlobleQuantity.py`.

**Case note**: Directory names use `JESup`/`JESDown` (lowercase 'u'/'D'), not `JESUp`/`JESDown`.

### Three Workflow Modes (Documented)

1. **Mode 1: Nominal Test Run** - Quick validation with `systematics: false`
2. **Mode 2: Add Systematics After Nominal** - Continue from Mode 1, add energy scale sys
3. **Mode 3: Full Workflow** - Production run with nominal + systematics together

See `.claude/skills/workflow.md` for detailed commands.

### IMPORTANT: run_workflow.py Integration

**After refactoring any stage script, ALWAYS check if run_workflow.py needs to be updated.**

Each stage should be callable via:
```bash
python3 run_workflow.py --config CONFIG.yaml --stage X.X --era 2018
```

Currently integrated stages in run_workflow.py:
- Stage 1 (OS), Stage 1.1 (OS sys)
- Stage 2 (MV), Stage 2.1 (MV sys)
- Stage 3 (WH) - nominal only
- Stage 3.1 (WH sys) - **TODO: Add to run_workflow.py**
- Stage 4 scripts - via temp script creation

### Workflow Standard Checklist

**IMPORTANT**: Check each script for workflow standard compliance:
- [ ] `--config` required argument
- [ ] `--era` required argument
- [ ] Uses `workflow_utils` (load_config, build_*_path, get_channel, get_options, get_regions)
- [ ] Reads options from config (not hardcoded): `fake_tau`, `mc_fake_tau`, `blind`, `smoothing`, `systematics`
- [ ] Has `--quiet` option for batch runs
- [ ] Command-line args override config options when both provided

**Scripts Verified** ✅:
- `addTemplateNew.py` - ✅ fits standard
- `addJESTemplatesToHistFile.py` - ✅ fits standard (uses `build_hist_path_jes`)
- `writeDatacard.py` - ✅ fixed to read `smoothing` from config

**Scripts to Check**:
- `smooth_systematics_fourTops.py` - needs verification
- `createFaketauTree.py` - needs verification
- `pl.py` - needs verification

### Workflow State Tracking (Phase 8 ✅ COMPLETE)

**File**: `.workflow_state.json` at project root (unified for all channels)

**Purpose**: Persist pipeline state across sessions for context injection by hooks

**Implementation**: `plotting/workflow_utils.py` - `WorkflowState` class (~180 lines)

**Key Features**:
- Unified state file tracking all channels (user preference)
- Atomic writes with temp file for safety
- History logging (keeps last 100 entries)
- Methods: `update_stage()`, `get_current()`, `get_stage_status()`, `log_execution()`
- Convenience function: `get_workflow_state(channel, config_path)`

**Test Result** (2025-12-10):
```python
from plotting.workflow_utils import get_workflow_state

# Test with 1tau0l
state = get_workflow_state('1tau0l', 'config/analysis_config_1tau0l_TTBBtest.yaml')
state.update_stage('1.1', '2017', 'running', 'OS_systematics')
current = state.get_current()
# Returns: {'stage': '1.1', 'era': '2017', 'status': 'running', 'operation': 'OS_systematics', 'timestamp': ...}

# Test with 1tau1l
state = get_workflow_state('1tau1l', 'config/analysis_config_1tau1l_TTBBtest.yaml')
state.update_stage('3.1', '2018', 'running', 'WH_all_systematics')
current = state.get_current()
# Both channels persist in same .workflow_state.json ✅
```

**State File Structure**:
```json
{
  "channels": {
    "1tau0l": {
      "config": "config/analysis_config_1tau0l_TTBBtest.yaml",
      "current": {"stage": "1.1", "era": "2017", "status": "running", "operation": "OS_systematics", "timestamp": "..."},
      "stage_status": {"1.1": {"2017": "running"}}
    },
    "1tau1l": {
      "config": "config/analysis_config_1tau1l_TTBBtest.yaml",
      "current": {"stage": "3.1", "era": "2018", "status": "running", "operation": "WH_all_systematics", "timestamp": "..."},
      "stage_status": {"3.1": {"2018": "running"}}
    }
  },
  "history": [
    {"timestamp": "...", "channel": "1tau0l", "stage": "1.1", "era": "2017", "operation": "OS_systematics", "status": "submitted", ...},
    {"timestamp": "...", "channel": "1tau1l", "stage": "3.1", "era": "2018", "operation": "WH_all_systematics", "status": "submitting", ...}
  ]
}
```

**Hook Integration**: `.claude/hooks/user-prompt-submit.sh` reads state and injects `<workflow_context>` tags

**Status**: ✅ Tested with both channels, working correctly

### Scripts to Refactor (Pending)

**Phase 3: Stage 2.4**
- `plotting/createFakeLeptonTree.py` - Add argparse

**Phase 4: Stage 3**
- `writeHistGood/jobs/makeJob_forWriteHist.py` - Add workflow_utils

### Claude Integration ✅ COMPLETE
- `.claude/skills/workflow.md` - Analysis pipeline skill with stage commands, workflow_utils pattern
  - **Updated**: Added Stage 4.2.5 (smooth_systematics_fourTops.py)
- `.claude/hooks/pre-tool-use.sh` - Environment check, setEnv path validation
- `.claude/hooks/user-prompt-submit.sh` - Auto-activation based on workflow keywords
- `plotting/pl.py` - **REFACTORED** to use workflow_utils, ~200 lines removed

### Smoothing Step (Stage 4.2.5)
- `plotting/smooth_systematics_fourTops.py` - LOWESS smoothing for systematic variations
- **IMPORTANT**: Requires ALL eras (2016preVFP, 2016postVFP, 2017, 2018) templates
- For single-era testing (e.g., 2018 only): SKIP this step
- Run after all eras processed, before final datacards

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
10. `1487d2f9` - docs: Trim CLAUDE.md and add commit-often rule
11. `3eac2730` - docs: Update workflow-optimization dev-docs with Session 4 progress
12. `efad13c1` - docs: Move workflow-code-quality to completed
13. `14e2ae73` - feat: Complete Phase 5 Stage 1 workflow integration
14. `19300aed` - feat: Integrate Stage 1 (OS) and Stage 2 (MV) into run_workflow.py
15. `97d36dd9` - docs: Phase 7 and Phase 8 documentation
16. `42ccbafd` - docs: Phase 8 planning and real test case
17. `d865d525` - feat: Add WorkflowState class (Phase 8 Step 1)
18. `890503a8` - feat: Enhance user-prompt-submit hook (Phase 8 Step 2)
19. `de247280` - feat: Split workflow.md into modular skill system (Phase 8 Step 3)
20. `18a660d0` - test: Enable systematics in 1tau1l config (Phase 8 Step 4)

---

## Validation Results (Session 4)

**1tau0l Channel** - All eras tested successfully:
- 2018, 2017, 2016postVFP, 2016preVFP: WH jobs ✅, pl.py plots ✅

**1tau1l Channel** - All eras tested successfully:
- 2017, 2016postVFP, 2016preVFP: WH jobs (71 files each) ✅, pl.py plots ✅

**File Quota Status**: 966,519 / 1,000,000 files (96.7%) - cleanup needed
