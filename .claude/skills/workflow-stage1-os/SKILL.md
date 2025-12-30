---
name: workflow-stage1-os
description: Stage 1 Object Selection (OS) - NanoAOD to skimmed ntuples. Use when submitting OS jobs, checking OS job status, monitoring held jobs, resubmitting failed jobs, or verifying Stage 1 output. Keywords: OS, object selection, NanoAOD, skimmed, stage 1, makeJob_OS, hep_q, held jobs, jetHT, resubmit.
---

# Stage 1: Object Selection (OS)

NanoAOD to skimmed ntuples. **Default: CentOS7** (XGBoost 0.80).

## Paths

```
Input:  /publicfs/cms/data/TopQuark/nanoAOD/{nanoaod_era}/
Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/{output_era}/{stage1_version}/
        └── mc/{process}/*.root, data/{dataset}/*.root

Era mapping (config era → output directory):
  2018        → UL2018
  2017        → UL2017
  2016preVFP  → UL2016_preVFP   (note underscore)
  2016postVFP → UL2016_postVFP  (note underscore)
```

## Commands

```bash
source setEnv_newNew.sh
cd objectSelectionOptimized/jobs/

# Submit nominal
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml --era 2018

# Submit ALL systematics (use screen - takes ~10 min)
screen -S os_sys
./submit_all_systematics.sh ../../config/CONFIG.yaml 2018
```

## Systematics (15 total)

JES, JERUp/Down, METUp/Down, EleScaleUp/Down, TESdm{0,1,10,11}Up/Down

## Job Duration

- **Nominal jobs**: 1-2 hours to complete
- **Systematic jobs**: Similar duration per variation

## Monitor & Release

```bash
hep_q -u $USER | grep OS_     # Check jobs
hep_q -u $USER -hold          # Check held jobs with reason
hep_release -a                 # Release all held jobs

# Resubmit held jobs with higher memory (if memory issue)
cd objectSelectionOptimized/jobs/
./resubmit_held.sh            # Default 6GB
./resubmit_held.sh 8000       # 8GB memory
./resubmit_held.sh 12000      # 12GB memory
```

## Verify Completion

```bash
# Base path
BASE=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD

# Count processes (expect ~59-68 depending on era/channel)
ls $BASE/UL{era}/{stage1}/mc/ | wc -l

# Check key samples exist
ls $BASE/UL{era}/{stage1}/mc/tttt/*.root | wc -l      # signal
ls $BASE/UL{era}/{stage1}/mc/TTBB*/ | wc -l           # TTBB (3 samples)
ls $BASE/UL{era}/{stage1}/data/jetHT_*/ | wc -l       # data

# For systematics (15 variations)
ls -d $BASE/UL{era}/{stage1}_*/ | wc -l               # expect 16 (nominal + 15 sys)
```

## Troubleshooting

### Binary Mismatch Error
If `GLIBCXX_3.4.32 not found`: recompile for CentOS7:
```bash
source setEnv_centos7.sh && cd objectSelectionOptimized/ && make clean && make
```

### Excessive Memory Usage
If jobs need unexpectedly high memory (>12GB), check the job script for **wrong input paths**:
```bash
# Read a held job script
cat /publicfs/.../jobs_eachYear/.../OS_*.sh | grep "run_objectSelection"
```
**Common issue**: Script points to old nanoAOD path (e.g., `/nanoAOD/2016/data/`) instead of UL path (`/nanoAOD/UL2016_postVFP/`). Old files may be larger or corrupted.

### Ghost Jobs
Jobs may show "running" for hours after completion:
- Check if output files exist
- Remove with `hep_rm <jobid>` if outputs verified

## Next: Stage 2 (MV)
