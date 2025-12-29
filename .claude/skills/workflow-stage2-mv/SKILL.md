---
name: workflow-stage2-mv
description: Stage 2 Make Variables (MV) and Stage 2.4 Fake Backgrounds. Use when submitting MV jobs, calculating BDT input variables, creating fake tau/lepton trees, or checking MV output. Keywords: MV, make variables, BDT, fake tau, fake lepton, FR_weight, fake rate, stage 2, createFaketauTree, createFakeLeptonTree, makeJob_makeVaribles.
---

# Stage 2: Make Variables (MV)

Calculates BDT input variables from Stage 1 output.

## Commands

```bash
source setEnv_newNew.sh
cd makeVariables_goodCode/jobs/

# Nominal
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018

# All systematics (74 total: TES×8, JER×2, MET×2, EleScale×2, JES×60)
# Takes ~10 mins to submit - run in screen/nohup!
nohup python3 makeJob_MV_JESVariation.py --config ../../config/CONFIG.yaml --era 2018 &

# Specific group: TES, JER, MET, EleScale, all
python3 makeJob_MV_JESVariation.py --config ../../config/CONFIG.yaml --era 2018 --group TES
```

## Path Patterns

| Type | Pattern |
|------|---------|
| Nominal | `forMVA/{era}/{stage2}_{stage1}/mc/` |
| TES/JER/MET/EleScale | `forMVA/{era}/{stage2}_{stage1}_{sys}/mc/` |
| JES | `forMVA/{era}/{stage2}_JES{up/Down}_{source}_{stage1}_JESPt22/mc/` |

**Note**: JES case is `JESup` (lowercase u) and `JESDown` (uppercase D)

## Monitor

```bash
hep_q -u $USER | grep MV_
```

**Job duration**: ~1 hour per job

## Stage 2.4: Fake Backgrounds

**Only needed for nominal MV**, not systematics. Run with Stage 2 nominal.

```bash
cd makeVariables_goodCode/

# Fake tau (ALL channels)
python3 createFaketauTree.py --config ../config/CONFIG.yaml --era 2018

# Fake lepton (1tau1l/1tau2l only)
python3 createFakeLeptonTree.py --config ../config/CONFIG.yaml --era 2018
```

**Output**: `{stage2_path}/mc/fakeTau_*.root`, `fakeLepton.root`

**CRITICAL**: Regenerate for each version. NEVER copy!

## Verify Completion

```bash
cd makeVariables_goodCode/

# Full verification (nominal + 74 systematics)
python3 verify_mv_completion.py --config ../config/CONFIG.yaml --era 2018

# Nominal only
python3 verify_mv_completion.py --config ../config/CONFIG.yaml --era 2017 --nominal-only
```

**Output**: Shows complete/incomplete/missing directories for all variations.

## Verify Fakes

```bash
# Check FR_weight non-zero (~0.1)
python3 -c "import ROOT; f=ROOT.TFile.Open('path/fakeTau_data_ptMorphed.root'); t=f.Get('newtree'); print('Mean:', t.GetEntries())"
```

## Local Testing

```bash
cd makeVariables_goodCode/

# Args: inputDir process outputDir numEntries if1tau2l JESType JESVar
./apps/run_makeVariables.out /publicfs/.../UL2018/{stage1}/mc/ tttt /tmp/test_mv/mc/ 100 0 0 0

# numEntries: 0=all, >0=test | if1tau2l: 0=1tau0l/1tau1l, 1=1tau2l
# JESType: 0=nominal, 1-6=sys | JESVar: 0=nominal, 1=up, 2=down
```

## Next: Stage 3 (WH)
