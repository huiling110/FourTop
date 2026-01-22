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

**IMPORTANT**: 1tau1l and 1tau0l **share the same Stage 1 (OS) and Stage 2 (MV) data** when using the same version strings (`v94HadroPreJetVetoHemOnly_TTBBtest`). This means:
- OS/MV data processed for one channel can be reused by the other
- Only Stage 3 (WH) and beyond differ between channels
- Always check both channels' workflow state for Stage 1/2 completion

### Stage 1 (OS) Status - 1tau1l & 1tau0l (SHARED)

**✅ COMPLETE for ALL 4 years**:
- **2017**: ✓ Nominal + 15 systematic variations (TES, JER, JES, MET, EleScale)
- **2018**: ✓ Nominal + systematic variations
- **2016preVFP**: ✓ Nominal + systematics
- **2016postVFP**: ✓ Nominal + 15 systematics (~1196 files each) - Completed Session 5

### 1tau1l Progress

**2018** (Testing Phase): ✅ COMPLETE
- Stage 3+3.1 (WH): Complete with all 74 systematics
- Stage 4.1-4.4: Complete (templates, datacard, plots)
- Stage 4.5 (Combine): Complete (significance=0 expected for single year/channel)

**2017** (Session 5 - Current):
- Stage 2.1 (MV systematics): ✅ Complete (14 variations × 59 files)
- Stage 3+3.1 (WH nominal + systematics): ✅ Submitted (~897 jobs, running)
- Stage 4 pipeline: Pending (waiting for WH to complete)

### 1tau0l Progress

- Stage 1 (OS): ✅ Complete for all 4 years (shared with 1tau1l)
- Stage 2 (MV): Need to submit
- Other stages: Not started yet

### 1tau2l

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

## Long-Running Stages Strategy

### Stage 4.5+ (Combine) - Over 1 Hour Execution

**Problem**: Stages 4.5 (combine fits) and 4.6 can take >1 hour, blocking workflow progression

**Strategy**: Use background execution with monitoring

#### Option 1: Screen/Tmux Sessions (Recommended for interactive work)
```bash
# Start screen session
screen -S combine_1tau1l_2018

# Run long-running stage
cd hua/combine/
cmsenv
python3 runCombineAll.py --config ../../config/analysis_config_1tau1l_TTBBtest.yaml --era 2018

# Detach: Ctrl+A, D
# Reattach: screen -r combine_1tau1l_2018
# List sessions: screen -ls
```

#### Option 2: Batch Job Submission (Recommended for production)
```bash
# For stages that support batch submission
cd hua/combine/jobs/
# Submit combine jobs to cluster
python3 makeJob_combine.py --config ../../config/analysis_config_1tau1l_TTBBtest.yaml --era 2018

# Monitor
hep_q -u $USER | grep combine
```

#### Option 3: Background Process with Logging
```bash
# Run in background with output capture
nohup bash -c "cd hua/combine/ && cmsenv && python3 runCombineAll.py --config ../../config/CONFIG.yaml --era 2018" > combine_2018.log 2>&1 &

# Save process ID
echo $! > combine_2018.pid

# Monitor progress
tail -f combine_2018.log

# Check if still running
ps -p $(cat combine_2018.pid)
```

#### Workflow Integration Pattern
```bash
# Stage 4.1-4.4 (quick, run interactively)
source setEnv_newNew.sh
python3 plotting/addJESTemplatesToHistFile.py --config CONFIG --era 2018 --execute --quiet
python3 plotting/addTemplateNew.py --config CONFIG --era 2018 --quiet
python3 plotting/writeDatacard.py --config CONFIG --era 2018
python3 plotting/pl.py --config CONFIG --era 2018

# Stage 4.5+ (long, run in background or submit batch)
cd hua/combine/
screen -S combine_era_channel
cmsenv
# Run combine commands...
# Detach and continue with other work
```

**Best Practice**:
- Stage 1-4: Interactive or batch depending on scale
- Stage 4.5-4.6: Always background or batch
- Use descriptive screen/job names: `combine_{channel}_{era}`
- Log all long-running processes
- Document PIDs/session names for easy recovery

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

## CRITICAL REMINDER: Update Hooks + Skills When Workflow Changes

**⚠️ IMPORTANT**: When making changes to workflow scripts or interfaces:

1. **Update `.claude/hooks/pre-tool-use.sh`** if environment requirements change
2. **Update `.claude/skills/workflow/stage*.md`** to reflect new commands/interfaces
3. **Update CLAUDE.md** if workflow principles change
4. **Test the new interface** before deprecating old scripts
5. **Add deprecation warnings** to old scripts with migration path

This ensures the hook system and skill documentation stay synchronized with code changes.

**Recent Example (2025-12-11)**: Consolidated `makeJob_forWriteHist.py` + `makeJob_WH_forJES.py` → unified `makeJob_WH.py`
- ✓ Added deprecation warnings to old scripts
- ✓ Updated `.claude/skills/workflow/stage3-wh.md`
- ✓ Hooks already covered new script pattern
- ✓ Documented in this context.md

---

**Last Updated**: 2025-12-11

**Note**: Permission fix moved to separate task: `dev-docs/active/permission-fix/`
