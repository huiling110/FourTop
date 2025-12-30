---
name: workflow
description: FourTop analysis pipeline automation. Provides stage-specific commands for OS (Object Selection), MV (Make Variables), WH (Write Histograms), and Combine (statistical fits). Use when running pipeline stages, submitting jobs, or checking workflow status. Keywords: submit jobs, run stage, check status, makeJob, histogram, datacard, combine.
---

# FourTop Workflow Overview

## Stage Skills (invoke these for stage-specific commands)

| Stage | Skill | Purpose |
|-------|-------|---------|
| 1 | `/workflow-stage1-os` | Object Selection (NanoAOD → ntuples) |
| 2 | `/workflow-stage2-mv` | Make Variables + Fake backgrounds |
| 3 | `/workflow-stage3-wh` | Write Histograms |
| 4 | `/workflow-stage4-combine` | Templates, Datacards, Combine, Plots |

## Progress Tracking

Use dev-docs status table: `dev-docs/active/{task}/tasks.md`

Status table format:
```
| Era | S1 OS | S1.1 sys | S2 MV | S2.1 sys | S2.4 Fake | S3 WH | S4 |
```

## Config

All paths from: `config/analysis_config_{channel}_{version}.yaml`

## Quick Commands

```bash
# Check running jobs
hep_q -u $USER

# Environment (all stages except combine)
source setEnv_newNew.sh

# Combine environment
cd hua/combine && cmsenv
```
