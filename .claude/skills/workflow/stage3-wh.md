# Stage 3: Histogram Production (WH)

Produces histogram files from Stage 2 output.

## Commands

```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Submit jobs for all processes
python3 makeJob_forWriteHist.py --config ../../config/CONFIG.yaml --era 2018

# Monitor jobs
hep_q -u $USER
```

## Note on Systematics

- If `options.systematics: true` in config: Nominal WH jobs include all weight systematics internally.
  Still need Stage 3.1 for **energy scale** systematics (TES, JER, MET, EleScale).
- If `options.systematics: false` in config: Only nominal histograms are produced.

## Stage 3.1: WH Systematic Variations (Energy Scale)

Submit WH jobs for energy scale systematic variations (TES, JER, MET, EleScale).
Requires Stage 2.1 (MV systematics) to be complete.

```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Submit ALL systematics for 2018 (14 variations × 59 MC files = 826 jobs)
python3 makeJob_WH_forJES.py --config ../../config/CONFIG.yaml --era 2018

# Submit specific systematic group
python3 makeJob_WH_forJES.py --config ../../config/CONFIG.yaml --era 2018 --group TES
python3 makeJob_WH_forJES.py --config ../../config/CONFIG.yaml --era 2018 --group JER

# Dry run
python3 makeJob_WH_forJES.py --config ../../config/CONFIG.yaml --era 2018 --dry-run

# Available groups: TES, JER, MET, EleScale, all
```

## Systematic Variations

- TES: TESdm0Up/Down, TESdm1Up/Down, TESdm10Up/Down, TESdm11Up/Down (8)
- JER: JERUp/Down (2)
- MET: METUp/Down (2)
- EleScale: EleScaleUp/Down (2)

Total: 14 variations

## Path Patterns

**Energy scale systematics (TES, JER, MET, EleScale):**
- Input: `/publicfs/.../forMVA/{era}/{stage2_version}_{stage1_version}_TTBBtest_{systematic}/mc/`
- Output: `{input}/variableHists_{hist_version}/`
- Example: `v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest_TESdm0Up/mc/variableHists_v0BDT1tau1l_TTBBtest/`

**JES systematics:**
- Input: `/publicfs/.../forMVA/{era}/{stage2_version}_JES{up/Down}_{source}_{stage1_version}_TTBBtest_JESPt22/mc/`
- Output: `{input}/variableHists_{hist_version}/`
- Example Up: `v1baselineHadro_JESup_Total_AK4PFchs_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/mc/variableHists_v0BDT1tau1l_TTBBtest/`
- Example Down: `v1baselineHadro_JESDown_Total_AK4PFchs_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/mc/variableHists_v0BDT1tau1l_TTBBtest/`
- **Note**: Case is `JESup` (lowercase u) and `JESDown` (uppercase D)

## Monitoring

```bash
# Check running jobs
hep_q -u $USER | grep WH_

# Check nominal output (channel-specific hist version)
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l_TTBBtest/*.root | wc -l

# Check TES systematic output (8 variations, should be 8 dirs × 59 files = 472)
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest_TES*/mc/variableHists_v0BDT1tau1l_TTBBtest/*.root 2>/dev/null | wc -l

# Check JES systematic output (60 variations, should be 60 × 59 = 3,540)
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_JES*_v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22/mc/variableHists_v0BDT1tau1l_TTBBtest/*.root 2>/dev/null | wc -l
```

## Next Step

After Stage 3 complete: **Stage 4.1-4.4** - Templates, Datacards, Plots
