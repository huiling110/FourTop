# Stage 1: Object Selection (OS)

Converts NanoAOD to skimmed ntuples with object selection.

## Commands

```bash
source setEnv_newNew.sh
cd objectSelectionOptimized/jobs/

# Submit nominal jobs for 2018
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml --era 2018

# Submit for all eras in config
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml

# Dry run (show paths without submitting)
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml --dry-run

# Submit with systematic variation
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml --era 2018 --sys JERUp
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml --era 2018 --sys TESdm0Down

# Submit ALL systematic variations at once (15 total)
./submit_all_systematics.sh ../../config/CONFIG.yaml 2018

# Check systematic job status
./check_systematic_jobs.sh 2018
```

## Available Systematics (15 variations)

- JES (Jet Energy Scale)
- JERUp, JERDown (Jet Energy Resolution)
- METUp, METDown (Missing ET)
- EleScaleUp, EleScaleDown (Electron Energy Scale)
- TESdm0Up, TESdm0Down (Tau Energy Scale, decay mode 0)
- TESdm1Up, TESdm1Down (Tau Energy Scale, decay mode 1)
- TESdm10Up, TESdm10Down (Tau Energy Scale, decay mode 10)
- TESdm11Up, TESdm11Down (Tau Energy Scale, decay mode 11)

**Note**: Use TES by decay mode only (dm0, dm1, dm10, dm11), NOT total TESUp/TESDown

## Output

Stage 1 systematics create separate output directories:
- Nominal: `{output_base}/{era}/{stage1_version}/`
- Systematic: `{output_base}/{era}/{stage1_version}_{sys}/`

Example: `v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/`

## Monitoring

```bash
# Check running jobs
hep_q -u $USER | grep OS_

# Check output files
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v94*_TTBBtest*/mc/*.root | wc -l

# Check systematic outputs exist
ls -d /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v94*_TES*/ 2>/dev/null | wc -l
```

## Next Step

After Stage 1 complete: **Stage 2 (MV)** - Make Variables
