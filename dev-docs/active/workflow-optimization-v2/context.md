# Context: Workflow Optimization V2

**Created**: 2025-12-11
**Last Updated**: 2025-12-11
**Status**: ACTIVE

---

## Primary Goal: Optimize Workflow Standard

**THIS IS THE CORE OBJECTIVE** - Not just completing V21, but OPTIMIZING the workflow standard as we execute.

### What This Means

Every step of the V21 production run is an opportunity to:
1. **Validate** workflow_utils patterns work robustly across all channels/eras
2. **Identify** gaps or friction points in the workflow standard
3. **Refine** scripts, configs, and documentation for production readiness
4. **Document** best practices and lessons learned
5. **Ensure** reproducibility for future analyses

### Workflow Standard Compliance (CRITICAL FOR PHASE 1)

**Phase 1 Testing (2018)** specifically validates that ALL scripts comply with:
- ✅ `--config` required (no hardcoded paths)
- ✅ `--era` required (or `--all-eras` option)
- ✅ Uses `workflow_utils` for ALL path building
- ✅ Reads options from config (systematics, fake_tau, etc.)
- ✅ Has `--quiet` option for batch runs
- ✅ Updates `.workflow_state.json` on execution
- ✅ Clear error messages when config invalid
- ✅ Self-documenting help text (`--help`)

**Success Metric**: Can run complete 2018 workflow (1tau1l, 1tau2l) with ONLY config file and era flag, zero hardcoded paths, zero manual interventions.

### Secondary Goal: V21 Combination

Complete Run2 four-top analysis: 3 channels × 4 years → V21 combination.

This production run **proves** the workflow standard works at scale.

---

## Current State (from .workflow_state.json)

**1tau1l**:
- Stage 3.1 (WH systematics) for 2018: TES/MET/EleScale submitted (708 jobs)
- Nearly complete for 2018 testing phase

**1tau0l**:
- Stage 1.1 (OS systematics): Running for multiple eras
- Background work in progress

**1tau2l**:
- No config exists yet
- OS/MV data exists → start from Stage 3 (WH)
- No TTBB integration needed

---

## Parent Task: workflow-optimization

This task continues from workflow-optimization which completed Phases 1-8:

**Phase 1-2**: Config schema cleanup + Script cleanup (✓ Complete)
**Phase 3-5**: Stage integration (OS, MV, WH) (✓ Complete)
**Phase 6**: Claude integration (skills, hooks) (✓ Complete)
**Phase 7**: Long-running job patterns (✓ Complete)
**Phase 8**: Modular skills + WorkflowState tracking (✓ Complete)

**Achievements**:
- ~320 commented paths removed from scripts
- All scripts use workflow_utils with minimal config
- WorkflowState class tracks pipeline progress
- Modular skill system for stage-specific guidance
- Hooks inject workflow context automatically

---

## Key Configuration Files

### Analysis Configs
- `config/analysis_config_1tau1l_TTBBtest.yaml` - 1tau1l channel (exists, systematics: true)
- `config/analysis_config_1tau0l_TTBBtest.yaml` - 1tau0l channel (exists, systematics: true)
- `config/analysis_config_1tau2l_TTBBtest.yaml` - **TO CREATE** from 1tau1l template

### Settings Files
- `.claude/settings.json` - Main permissions (to simplify)
- `.claude/settings.local.json` - Local overrides (to clear)

---

## Workflow Scripts (All Use workflow_utils)

### Stage 1: Object Selection (OS)
- `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py`
- `objectSelectionOptimized/jobs/submit_all_systematics.sh` (batch script)

### Stage 2: Make Variables (MV)
- `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py`
- `makeVariables_goodCode/jobs/makeJob_MV_JESVariation.py` (batch script)

### Stage 3: Write Histograms (WH)
- `writeHistGood/jobs/makeJob_forWriteHist.py` (nominal)
- `writeHistGood/jobs/makeJob_WH_forJES.py` (systematics, batch script)

### Stage 4: Templates and Analysis
- `plotting/addJESTemplatesToHistFile.py` - Stage 4.1 (consolidate JES)
- `plotting/addTemplateNew.py` - Stage 4.2 (all other systematics)
- `plotting/smooth_systematics_fourTops.py` - Stage 4.2.5 (smoothing, needs TTBB support)
- `plotting/writeDatacard.py` - Stage 4.3 (datacards)
- `plotting/pl.py` - Stage 4.4 (plots)

### Stage 4.5+: Combination
- `hua/combine/runCombineAll.py` - Combine tool
  - **TO VERIFY**: Supports `--combine-years` and `--combine-channels`

---

## Path Structure

```
Stage 1 Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL{ERA}/{v94HadroPreJetVetoHemOnly}/mc/
Stage 2 Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{ERA}/{v1baselineHadro}_{v94HadroPreJetVetoHemOnly}/mc/
Stage 3 Output: .../mc/variableHists_{v0BDT1tau{0l|1l|2l}_TTBBtest}/
Stage 4 Combine: .../combine/
Stage 4.3 Datacards: .../combine/datacardSys_{v0_ttbb_nosmoothing}/
```

---

## Environment Requirements

| Stages | Environment | Command |
|--------|-------------|---------|
| 1, 2, 3, 4.1-4.4 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.5+ (Combine) | CMSSW | `cmsenv` in hua/combine/ |

---

## Workflow Standard Checklist

All scripts comply with:
- ✓ `--config` required argument
- ✓ `--era` argument (or `--all-eras`)
- ✓ Uses `workflow_utils` for all path building
- ✓ Reads options from config
- ✓ `--quiet` option for batch runs
- ✓ Updates `.workflow_state.json`

---

## Channel-Specific Details

### 1tau1l
- **Regions**: 1tau1lSR, l1tau1lCR12
- **TTBB**: Yes (requires integration)
- **Systematics**: Full (JES×60, TES×8, JER×2, MET×2, EleScale×2)

### 1tau0l
- **Regions**: 1tau0lSR, 1tau0lCRMR, 1tau0lVR
- **TTBB**: Yes (requires integration)
- **Systematics**: Full (same as 1tau1l)

### 1tau2l
- **Regions**: 1tau2lSR, 1tau2lCR3
- **TTBB**: **NO** (skip integration steps)
- **Systematics**: TBD (may be nominal only or subset)
- **Starting Point**: Stage 3 (WH) - OS/MV data exists

---

## Commands Reference

### Check Job Status
```bash
hep_q -u $USER
hep_q -u $USER | grep 1tau1l
```

### Check Workflow State
```python
from plotting.workflow_utils import get_workflow_state
state = get_workflow_state('1tau1l', 'config/analysis_config_1tau1l_TTBBtest.yaml')
state.get_current()
```

### Run Stage 3 (WH) Nominal
```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/
python3 makeJob_forWriteHist.py --config ../../config/analysis_config_1tau1l_TTBBtest.yaml --era 2018
```

### Run Stage 3.1 (WH) Systematics
```bash
python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau1l_TTBBtest.yaml --era 2018 --group all
```

### Run Stage 4 Pipeline
```bash
# Stage 4.1: Consolidate JES
python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018 --execute --quiet

# Stage 4.2: Add other systematics
python3 plotting/addTemplateNew.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018 --quiet

# Stage 4.3: Write datacards
python3 plotting/writeDatacard.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018

# Stage 4.4: Generate plots
python3 plotting/pl.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018
```

---

## Related Documentation

- `.claude/skills/workflow/` - Modular skill system for stage-specific help
- `dev-docs/active/workflow-optimization/` - Parent task documentation
- `dev-docs/active/workflow-optimization/session-learnings-2025-12-10.md` - Phase 8 real-world testing

---

**Last Updated**: 2025-12-11
