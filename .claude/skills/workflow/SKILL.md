---
name: workflow
description: FourTop analysis pipeline automation. Provides stage-specific commands for OS (Object Selection), MV (Make Variables), WH (Write Histograms), and Combine (statistical fits). Use when running pipeline stages, submitting jobs, or checking workflow status. Keywords: submit jobs, run stage, check status, makeJob, histogram, datacard, combine.
---

# Workflow Skill - FourTop Analysis Pipeline

Automates the four-stage physics analysis pipeline with config-driven job submission.

## Pipeline Overview

| Stage | Abbrev | Purpose |
|-------|--------|---------|
| 1 | OS | Object Selection (NanoAOD → skimmed ntuples) |
| 2 | MV | Make Variables (add BDT scores) |
| 3 | WH | Write Histograms (histogram production) |
| 4 | Combine | Statistical fits (datacards, limits) |

## When to Use

- Submitting batch jobs for any stage
- Checking job status and output completion
- Running combine fits and limit calculations
- Managing multi-era production workflows

## Quick Commands

### Check Status
```bash
hep_q -u $USER  # Running jobs
```

### Stage 3 (WH) - Most Common
```bash
cd writeHistGood/jobs
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA
```

### Stage 4 (Combine)
```bash
cd plotting
python3 pl.py --config ../config/CONFIG.yaml --era ERA  # Make plots/datacards
cd ../hua/combine
python3 run_combine.py --config ../config/CONFIG.yaml --era ERA
```

## Key Files

- **Config**: `config/analysis_config_*.yaml` (YAML configuration)
- **State**: `.workflow/state.json` (computed paths for all eras)
- **Skills**: See `overview.md` for detailed stage documentation

## Usage Pattern

1. Always use `--config CONFIG --era ERA` pattern
2. Read `.workflow/state.json` for concrete paths
3. Source `setEnv_newNew.sh` before running (except combine: use `cmsenv`)
