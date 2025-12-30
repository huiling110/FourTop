# Workflow Status Checker

How to check the status of your analysis pipeline.

## Workflow State File

The workflow state is tracked in `.workflow_state.json` at the project root.

### View Current State

```bash
# Pretty-print entire state
cat .workflow_state.json | python3 -m json.tool

# Check specific channel state
python3 -c "
import json
state = json.load(open('.workflow_state.json'))
channel = '1tau0l'  # or '1tau1l', '1tau2l'
print(f'Current stage: {state[\"channels\"][channel][\"current\"]}')"
```

### Using workflow_utils

```python
from plotting.workflow_utils import get_workflow_state

# Get workflow state for a channel
state = get_workflow_state('1tau0l', 'config/analysis_config_1tau0l_TTBBtest.yaml')

# Check current stage
current = state.get_current()
print(f"Stage: {current['stage']}, Era: {current['era']}, Status: {current['status']}")

# Check specific stage status for an era
status = state.get_stage_status('3', '2018')
print(f"Stage 3 for 2018: {status}")  # pending/running/completed
```

## Job Queue Monitoring

### Check Running Jobs

```bash
# All your jobs
hep_q -u $USER

# Filter by stage
hep_q -u $USER | grep OS_     # Stage 1 (Object Selection)
hep_q -u $USER | grep MV_     # Stage 2 (Make Variables)
hep_q -u $USER | grep WH_     # Stage 3 (Write Histograms)

# Count jobs by status
hep_q -u $USER | awk '{print $6}' | sort | uniq -c
```

### Monitor Specific Job

```bash
# Get job ID from hep_q output
hep_q -u $USER | grep OS_

# Check job details
hep_rm <job_id>  # Remove job
condor_q <job_id>  # Check condor status
```

## Output File Verification

### Stage 1: Object Selection

```bash
ERA="2018"
VERSION="v94HadroPreJetVetoHemOnly_TTBBtest"

# Nominal outputs
ls /publicfs/cms/data/TopQuark/nanoAOD/UL${ERA}/${VERSION}/mc/*.root | wc -l

# Systematic outputs (15 variations)
ls -d /publicfs/cms/data/TopQuark/nanoAOD/UL${ERA}/${VERSION}_*/ 2>/dev/null | wc -l

# Check specific systematic
ls /publicfs/cms/data/TopQuark/nanoAOD/UL${ERA}/${VERSION}_JESPt22/mc/*.root | wc -l
```

### Stage 2: Make Variables

```bash
ERA="2018"
STAGE2_VERSION="v1baselineHadro"
STAGE1_VERSION="v94HadroPreJetVetoHemOnly_TTBBtest"

# Nominal outputs
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/${ERA}/${STAGE2_VERSION}_${STAGE1_VERSION}/mc/*.root | wc -l

# Systematic outputs
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/${ERA}/${STAGE2_VERSION}_${STAGE1_VERSION}_TES*/mc/*.root | wc -l
```

### Stage 3: Histograms

```bash
ERA="2018"
STAGE2_VERSION="v1baselineHadro"
STAGE1_VERSION="v94HadroPreJetVetoHemOnly_TTBBtest"
HIST_VERSION="v0BDT1tau0l_TTBBtest"

# Nominal histograms
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/${ERA}/${STAGE2_VERSION}_${STAGE1_VERSION}/mc/variableHists_${HIST_VERSION}/*.root | wc -l

# Systematic histograms
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/${ERA}/${STAGE2_VERSION}_${STAGE1_VERSION}_TES*/mc/variableHists_${HIST_VERSION}/*.root | wc -l
```

### Stage 4: Templates and Datacards

```bash
CHANNEL="1tau0l"
DATACARD_VERSION="v1_TTBBtest"

# Check template files
ls hua/combine/combinationV21/run2_${CHANNEL}_${DATACARD_VERSION}/*template*.root 2>/dev/null

# Check datacards
ls hua/combine/combinationV21/run2_${CHANNEL}_${DATACARD_VERSION}/datacard*.txt 2>/dev/null

# Check smoothed templates (if smoothing enabled)
ls hua/combine/combinationV21/run2_${CHANNEL}_${DATACARD_VERSION}/*smoothed*.root 2>/dev/null
```

## Common Issues

### Jobs Not Running

```bash
# Check job holds
condor_q -hold

# Check cluster load
condor_status

# Release held jobs (if safe)
condor_release $USER
```

### Missing Output Files

```bash
# Check log files for errors
tail -n 50 objectSelectionOptimized/jobs/log/*.log

# Look for common error patterns
grep -i "error\|fail\|exception" objectSelectionOptimized/jobs/log/*.log
```

### Disk Quota Issues

```bash
# Check file count quota (1M limit)
lfs quota -u $USER /publicfs

# Find largest directories
du -sh /publicfs/cms/user/huahuil/* | sort -h | tail -20

# Count files in analysis output
find /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD -type f | wc -l
```

## Expected File Counts

### Per Era (Typical 1tau0l channel)

| Stage | Data Files | MC Files | Total Jobs |
|-------|------------|----------|------------|
| 1 (OS nominal) | ~10 | ~120 | ~130 |
| 1.1 (OS sys) | 0 | ~1800 (120×15) | ~1800 |
| 2 (MV nominal) | ~10 | ~120 | ~130 |
| 2.1 (MV sys) | 0 | ~1680 (120×14) | ~1680 |
| 3 (WH nominal) | ~10 | ~59 | ~69 |
| 3.1 (WH sys) | 0 | ~826 (59×14) | ~826 |

### Systematic Counts

- Stage 1 systematics: 15 (JES, JER, MET, EleScale, TES by dm)
- Stage 2/3 systematics: 14 (JER, MET, EleScale, TES by dm - no JES)

## Next Steps Based on Status

| Current Stage | Next Action |
|---------------|-------------|
| 1 completed | Run Stage 2 (MV) |
| 1.1 completed | Run Stage 2.1 (MV sys) |
| 2 completed | Run Stage 2.4 (fake backgrounds) |
| 2.4 completed | Run Stage 3 (WH) |
| 3 completed | Run Stage 3.1 (WH sys) or Stage 4.1 (addJES) |
| 3.1 completed | Run Stage 4.1 (addJES) |
| 4.1 completed | Run Stage 4.2 (templates) |
| 4.2 completed | Run Stage 4.2.5 (smoothing) or 4.3 (datacards) |
| 4.2.5 completed | Run Stage 4.3 (datacards) |
| 4.3 completed | Run Stage 4.4 (plots) |
| 4.4 completed | Run Stage 4.5 (combine) |
