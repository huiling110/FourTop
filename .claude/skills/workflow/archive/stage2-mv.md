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

**Energy scale systematics (TES, JER, MET, EleScale):**
- Input: `/publicfs/.../UL{ERA}/{stage1_version}_TTBBtest_{systematic}/mc/`
- Output: `/publicfs/.../forMVA/{era}/{stage2_version}_{stage1_version}_TTBBtest_{systematic}/mc/`
- Example: `v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest_TESdm0Up/mc/`

**JES systematics:**
- Input: `/publicfs/.../UL{ERA}/{stage1_version}_TTBBtest_JESPt22/mc/JES{up/Down}_{source}/`
- Output: `/publicfs/.../forMVA/{era}/{stage2_version}_JES{up/Down}_{source}_{stage1_version}_TTBBtest_JESPt22/mc/`
- Example Up: `v1baselineHadro_JESup_Total_AK4PFchs_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/mc/`
- Example Down: `v1baselineHadro_JESDown_Total_AK4PFchs_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/mc/`
- **Note**: Case is `JESup` (lowercase u) and `JESDown` (uppercase D)

## Monitoring

```bash
# Check running jobs
hep_q -u $USER | grep MV_

# Check nominal output files
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly/mc/*.root | wc -l

# Check TES systematic files (8 variations)
ls -d /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest_TES*/mc/ | wc -l

# Check JES systematic files (60 variations)
ls -d /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_JES*_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/mc/ | wc -l
```

## Stage 2.4: Fake Background Generation

**CRITICAL**: Must regenerate for EACH new analysis version. NEVER copy from reference!

**Location**: `makeVariables_goodCode/` (moved from plotting/ for organizational clarity)

```bash
source setEnv_newNew.sh
cd makeVariables_goodCode/

# Fake tau (required for ALL channels)
python3 createFaketauTree.py --config ../config/CONFIG.yaml --era 2018

# Fake lepton (required for 1tau1l/1tau2l only)
python3 createFakeLeptonTree.py --config ../config/CONFIG.yaml --era 2018
```

### Fake Tau Details
- Creates `fakeTau_data_ptMorphed.root` and `fakeTau_MC_ptMorphed.root`
- Applies fake rate (FR) weights from measurement region
- pT morphing corrects for pT spectrum differences
- Output: `{stage2_path}/mc/fakeTau_*.root`

### Fake Lepton Details
- Creates `fakeLepton.root` from anti-isolated lepton region (AR)
- Only needed for channels with lepton requirement (1tau1l, 1tau2l)
- Output: `{stage2_path}/mc/fakeLepton.root`

### Verification
```bash
# Check FR_weight is non-zero (should be ~0.1)
python3 -c "import ROOT; f=ROOT.TFile.Open('path/to/fakeTau_data_ptMorphed.root'); t=f.Get('newtree'); t.Draw('FR_weight','','',100); print('Mean FR_weight:', ROOT.gDirectory.Get('htemp').GetMean())"
```

## Local Testing

Run MV binary directly for debugging/testing:

```bash
source setEnv_newNew.sh
cd makeVariables_goodCode/

# Arguments: inputDir process outputDir numEntries if1tau2l JESType JESVar
# numEntries=0 for all, >0 for test mode (e.g., 100 entries)

# Test with 100 entries (fast)
./apps/run_makeVariables.out \
    /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/{stage1_version}/mc/ \
    tttt \
    /tmp/test_mv/mc/ \
    100 0 0 0

# Full run (all entries)
./apps/run_makeVariables.out \
    /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/{stage1_version}/mc/ \
    tttt \
    /tmp/test_mv/mc/ \
    0 0 0 0

# Check output
root -l /tmp/test_mv/mc/tttt.root -e "newtree->Scan(\"FR_weight:tausF_jetPt:tausF_jetEta\",\"\",\"\",10)"
```

**Arguments**:
- `numEntries`: 0=all, >0=test mode with N entries
- `if1tau2l`: 0=1tau0l/1tau1l, 1=1tau2l channel
- `JESType`: 0=nominal, 1-6=systematic types
- `JESVar`: 0=nominal, 1=up, 2=down

## Next Step

After Stage 2 + 2.4 complete: **Stage 3 (WH)** - Histogram production
