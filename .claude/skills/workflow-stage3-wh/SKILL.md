---
name: workflow-stage3-wh
description: Stage 3 Write Histograms (WH) - Histogram production from MV output. Use when submitting WH jobs, checking histogram output, running systematic histogram jobs, or verifying histogram counts. Keywords: WH, write histograms, histogram, stage 3, makeJob_WH, variableHists, systematic complete, nominal.
---

# Stage 3: Histogram Production (WH)

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

## Monitoring

```bash
# Check jobs
hep_q -u $USER

# Check nominal
ls /publicfs/.../variableHists_*/*.root | wc -l

# Debug failed jobs
cat /publicfs/.../variableHists_*/log/PROCESS.err
bash /publicfs/.../variableHists_*/jobSH/WH_PROCESS.sh  # rerun manually
```

## Next Step

After Stage 3 complete -> **Stage 4.1** (addJESTemplatesToHistFile.py)
