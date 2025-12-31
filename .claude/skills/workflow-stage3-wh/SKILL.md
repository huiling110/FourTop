---
name: workflow-stage3-wh
description: Stage 3 Write Histograms (WH) - Histogram production from MV output. Use when submitting WH jobs, checking histogram output, running systematic histogram jobs, or verifying histogram counts. Keywords: WH, write histograms, histogram, stage 3, makeJob_WH, variableHists, systematic complete, nominal.
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

# Stage 3 (nominal, MC only - skip data)
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic nominal --no-data

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
variableHists_{version}/
├── *.root      # Histogram files
├── log/        # Job logs (.log, .err)
└── jobSH/      # Job scripts
```

**Paths:**
- Nominal: `v1baselineHadro_{stage1}_TTBBtest/mc/variableHists_{hist}/`
- TES/JER/MET/EleScale: `v1baselineHadro_{stage1}_TTBBtest_{sys}/mc/variableHists_{hist}/`
- JES: `v1baselineHadro_JES{up/Down}_{source}_{stage1}_TTBBtest_JESPt22/mc/variableHists_{hist}/`

**Note**: JES case is `JESup` (lowercase u) and `JESDown` (uppercase D)

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

## Next Step

After Stage 3 complete -> **Stage 4.1** (addJESTemplatesToHistFile.py)
