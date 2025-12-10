# Stage 2: Make Variables (MV)

Calculates BDT input variables from Stage 1 output.

## Commands

```bash
source setEnv_newNew.sh
cd makeVariables_goodCode/jobs/

# Submit nominal jobs for 2018
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018

# Submit for all eras in config
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml

# MC only (typical for systematic variations)
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018 --mc-only

# Dry run (show paths without submitting)
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018 --dry-run

# Submit with systematic variation (requires Stage 1 systematic output)
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018 --sys JERUp
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018 --sys TESdm0Down
```

## Batch Systematic Submission (14 variations: TES, JER, MET, EleScale)

```bash
# Submit all systematics for an era
python3 makeJob_MV_JESVariation.py --config ../../config/CONFIG.yaml --era 2018

# Submit specific systematic group
python3 makeJob_MV_JESVariation.py --config ../../config/CONFIG.yaml --era 2018 --group TES
python3 makeJob_MV_JESVariation.py --config ../../config/CONFIG.yaml --era 2018 --group JER

# Available groups: TES, JER, MET, EleScale, all
```

## Path Patterns

- Input: `{stage1_output}/UL{ERA}/{stage1_version}[_systematic]/mc/`
- Output: `{stage2_output}/{era}/{stage2_version}_{stage1_version}[_systematic]/mc/`

## Monitoring

```bash
# Check running jobs
hep_q -u $USER | grep MV_

# Check output files
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1*_v94*/mc/*.root | wc -l
```

## Stage 2.4: Fake Background Generation

**CRITICAL**: Must regenerate for EACH new analysis version. NEVER copy from reference!

```bash
source setEnv_newNew.sh
cd plotting/

# Fake tau (required for ALL channels)
python3 createFaketauTree.py --config ../config/CONFIG.yaml --era 2018

# Fake lepton (required for 1tau1l/1tau2l only)
python3 createFakeLeptonTree.py --config ../config/CONFIG.yaml --era 2018
```

## Next Step

After Stage 2 complete: **Stage 3 (WH)** - Histogram production
