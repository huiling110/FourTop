---
name: workflow-stage3-wh
description: Stage 3 Write Histograms (WH) - Histogram production from MV output. Use when submitting WH jobs, checking histogram output, running systematic histogram jobs, verifying histogram counts, or checking WH systematic variations. Keywords: WH, write histograms, histogram, stage 3, makeJob_WH, variableHists, systematic complete, nominal, check WH systematic, compare systematic, Up/Down variation.
---

# Stage 3: Histogram Production (WH)

## Prerequisites Check

**Before running Stage 3**, validate prerequisites:
```bash
python3 scripts/validate_stage.py --stage 3 --config config/CONFIG.yaml --era ERA
```

Requirements:
- Stage 2 (MV) complete for the era
- Fake tau trees if `fake_tau: true` in config

## Quick Reference

```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Stage 3: Complete (nominal + all systematics) - RECOMMENDED
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic complete

# Stage 3 (nominal only) - includes MC + Data by default
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic nominal

# Stage 3 (systematics only) - if nominal already done
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic all

# Specific systematic groups
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic JES
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic TES

# Available: nominal, TES, JER, MET, EleScale, JES, all, complete
```

**Note**: Use `--systematic complete` to submit nominal+systematics together for parallel execution.

**IMPORTANT**: Submitting `--systematic complete` or `--systematic all` takes ~20 minutes due to the large number of JES variations. Always use **screen** for these submissions:
```bash
screen -S wh_2017
source setEnv_newNew.sh
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era 2017 --systematic complete
# Ctrl+A, D to detach
```

## Expected Output Counts

| Type | Variations | Files per var | Total |
|------|------------|---------------|-------|
| Nominal | 1 | 71 | 71 |
| TES | 8 | 59 | 472 |
| JER | 2 | 59 | 118 |
| MET | 2 | 59 | 118 |
| EleScale | 2 | 59 | 118 |
| JES | 60 | 59 | 3,540 |

## Output Directory Structure

```
variableHists_{version}/     # BDT histograms (default mode)
├── *.root      # Histogram files
├── log/        # Job logs (.log, .err)
└── jobSH/      # Job scripts

inputVarHists_{version}/     # Input variable histograms (--mode variables)
├── *.root      # Variable histograms with full systematics
├── log/
└── jobSH/
```

**Paths:**
- Nominal: `v1baselineHadro_{stage1}_TTBBtest/mc/variableHists_{hist}/`
- TES/JER/MET/EleScale: `v1baselineHadro_{stage1}_TTBBtest_{sys}/mc/variableHists_{hist}/`
- JES: `v1baselineHadro_JES{up/Down}_{source}_{stage1}_TTBBtest_JESPt22/mc/variableHists_{hist}/`

**Note**: JES case is `JESup` (lowercase u) and `JESDown` (uppercase D)

## Input Variable Histograms (variableAnalyzer)

For generating input variable histograms (tausT_1pt, jets_HT, etc.) with full systematics matching treeAnalyzer:

### Build
```bash
cd writeHistGood
make variables  # Builds run_variableAnalyzer.out
```

### Submit Jobs (Recommended: makeJob_WH.py)
```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Nominal only (MC + Data)
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era 2018 --systematic nominal --mode variables

# Complete (nominal + all systematics)
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era 2018 --systematic complete --mode variables

# Specific systematic group
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era 2018 --systematic TES --mode variables
```

### Legacy: makeJob_forWriteHist.py
```bash
python3 makeJob_forWriteHist.py \
    --config ../../config/analysis_config_1tau0l_XGB080test.yaml \
    --era 2018 \
    --mode variables \
    --sys 1
```

### Output
- Location: `{MV_dir}/mc/inputVarHists_{version}/` (NOT variableHists_ to avoid BDT conflict)
- Contains: All input variables with full systematics matching treeAnalyzer
- Variables defined in: `writeHistGood/src/functions.C:initializeHistVec()`

### Key Differences from BDT Mode
| Aspect | BDT (treeAnalyzer) | Variables (variableAnalyzer) |
|--------|--------------------|-----------------------------|
| Output dir | `variableHists_{version}/` | `inputVarHists_{version}/` |
| Executable | `run_treeAnalyzer.out` | `run_variableAnalyzer.out` |
| Histograms | BDT discriminant | ~100+ input variables |
| MC fake tau | `_MCFT`/`_NotMCFT` separation | No separation |

### Verification
```bash
python3 -c "
import ROOT
f = ROOT.TFile('inputVarHists_v0/tttt.root')
hists = [k.GetName() for k in f.GetListOfKeys()]
print(f'Total histograms: {len(hists)}')
# Check for systematics
assert any('CMS_fake_t_2018' in h for h in hists), 'Missing CMS_fake_t_2018'
assert any('tausT_1pt' in h for h in hists), 'Missing tausT_1pt variable'
print('Systematics and variables present')
"
```

## Timing Expectations

Each WH job should complete in **<10 minutes** under normal conditions. If jobs take hours or hit time limits:
- Check for infinite loops or code bugs
- Check log files for errors
- Default cluster time limit is 10 hours; jobs shouldn't need anywhere near this

## Monitoring

```bash
hep_q -u $USER | grep WH_
```

## Verify Completion

```bash
# Base path (get from config)
BASE=/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}

# Nominal: expect ~71 files
ls $BASE/v1baselineHadro_{stage1}/mc/variableHists_{hist}/*.root | wc -l

# Check specific systematics
ls $BASE/v1baselineHadro_{stage1}_TESdm0Up/mc/variableHists_{hist}/*.root | wc -l
ls $BASE/v1baselineHadro_{stage1}_JERUp/mc/variableHists_{hist}/*.root | wc -l

# Count all histogram directories (expect 75 total)
ls -d $BASE/*/mc/variableHists_{hist}/ 2>/dev/null | wc -l

# Debug failed jobs
cat $BASE/.../variableHists_{hist}/log/PROCESS.err
```

## Job Monitor

Use the job monitor script for detailed tracking:
```bash
# Watch mode (refreshes every 60s)
python3 scripts/check_wh_jobs.py --config config/CONFIG.yaml --all --watch

# Quick status check
python3 scripts/check_wh_jobs.py --config config/CONFIG.yaml --era ERA --quiet
```

## Checking WH Systematic Variations

After addJES merges systematics into nominal files, check systematic consistency:

```bash
source setEnv_newNew.sh && python3 << 'EOF'
import ROOT

# Path to nominal file (contains JES systematics after addJES)
base = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadro_{stage1}/mc/variableHists_{hist}"
f = ROOT.TFile(f"{base}/tttt.root", "READ")

# Histogram naming: {process}_{channel}{region}_{systematic}_{variable}
# Example: tttt_1tau0lSR_CMS_scale_j_RelativeSample_2018Up_BDT
h_nom = f.Get("tttt_1tau0lSR_BDT")
h_up = f.Get("tttt_1tau0lSR_CMS_scale_j_RelativeSample_2018Up_BDT")
h_down = f.Get("tttt_1tau0lSR_CMS_scale_j_RelativeSample_2018Down_BDT")

for i in range(1, h_nom.GetNbinsX() + 1):
    nom = h_nom.GetBinContent(i)
    up_pct = ((h_up.GetBinContent(i) - nom) / nom * 100) if nom > 0 else 0
    down_pct = ((h_down.GetBinContent(i) - nom) / nom * 100) if nom > 0 else 0
    # Check if Up/Down go same direction (unusual)
    direction = "OK" if up_pct * down_pct < 0 else "SAME!"
    print(f"Bin {i}: Up={up_pct:+.2f}%, Down={down_pct:+.2f}% {direction}")
EOF
```

**Note**: After addJES, the original JES directories are cleaned up. Systematics are only available in the merged nominal files.

## Next Step

After Stage 3 complete -> **Stage 4.1** (addJESTemplatesToHistFile.py)
