# Stage 1: Object Selection (OS)

NanoAOD → skimmed ntuples. **Default: CentOS7** (XGBoost 0.80).

## Paths

```
Input:  /publicfs/cms/data/TopQuark/nanoAOD/{nanoaod_era}/
Output: /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL{era}/{stage1_version}/
        └── mc/{process}/*.root, data/{dataset}/*.root
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
```

## Verify Before Stage 2

```bash
# Check key processes have output
ls /publicfs/.../UL2018/v95XGB080testOS7/mc/tttt/*.root | wc -l
ls /publicfs/.../UL2018/v95XGB080testOS7/data/jetHT_2018a/*.root | wc -l
```

## Binary Mismatch Error

If `GLIBCXX_3.4.32 not found`: recompile for CentOS7:
```bash
source setEnv_centos7.sh && cd objectSelectionOptimized/ && make clean && make
```

## Next: Stage 2 (MV)
