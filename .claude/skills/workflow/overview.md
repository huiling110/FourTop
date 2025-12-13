# Workflow Skill - FourTop Analysis Pipeline

## Stage Order

```
Per-Era:
1 → 1.1 → 2 → 2.1 → 2.4 → 3 → 4.1 → 4.2 → 4.3 → 4.4 → 4.5 → 4.6 → 4.7
OS  OS    MV  MV    Fake  WH  JES   Tmpl  Smth  Card  Plot  Comb  Post
    sys       sys         +sys

Sync Point (all 4 eras for 1 channel):
4.4.1 (combineDatacard) - combines 4 eras → 1-channel Run2 datacard
```

## Environment

| Stages | Command |
|--------|---------|
| 1-4.4, 4.5, 4.7 | `source setEnv_newNew.sh` |
| 4.4.1, 4.6 (combine) | `cmsenv` (in hua/combine/) |

## Automated Workflow (V3)

```bash
# Initialize
python3 run_workflow_auto.py --init --channel 1tau1l \
    --config config/analysis_config_1tau1l_TTBBtest.yaml --eras 2018

# Check status
python3 run_workflow_auto.py --status

# Run automation
python3 run_workflow_auto.py --run --eras 2018 --start-stage 3

# Resume
python3 run_workflow_auto.py --resume --eras 2016preVFP --start-stage 4.1
```

**Features**: Job monitoring (hep_q), auto env setup, file logging (`.workflow/auto_*.log`)

**State**: `.workflow/state.json` (V3.1 - includes concrete paths)

## State File (V3.1)

The state file contains **concrete paths** for immediate use:

```bash
# View state
python3 plotting/workflow_state_v3.py --status

# Get paths for an era
python3 plotting/workflow_state_v3.py --paths 2017

# Refresh paths after config change
python3 plotting/workflow_state_v3.py --refresh-paths
```

**State includes per-era:**
- `hist_dir`: Full path to histogram directory
- `combine_dir`: Full path to combine subdirectory
- `templates`: Pattern for template files
- `log_dir`, `job_dir`: Job output directories

**IMPORTANT**: Always read `.workflow/state.json` before workflow operations to get correct paths.

## Manual Commands

All scripts: `--config CONFIG.yaml --era ERA`

```bash
source setEnv_newNew.sh

# Stage 3: WH (nominal + systematics)
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic complete

# Stage 4.1-4.5
cd plotting/
python3 addJESTemplatesToHistFile.py --config ../config/CONFIG.yaml --era ERA --execute
python3 addTemplateNew.py --config ../config/CONFIG.yaml --era ERA
python3 smooth_systematics_fourTops.py --config ../config/CONFIG.yaml
python3 writeDatacard.py --config ../config/CONFIG.yaml --era ERA
python3 pl.py --config ../config/CONFIG.yaml --era ERA

# Stage 4.4.1: Combine 4 eras (different env!)
cd hua/combine/ && cmsenv
python3 writeCombinationDatacard.py --config ../../config/CONFIG.yaml --channel CHANNEL

# Stage 4.6: Combine fits (different env!)
cd hua/combine/ && cmsenv
python3 runCombineAll.py ...
```

## Config

```yaml
versions:
  stage1: "v94HadroPreJetVetoHemOnly_TTBBtest"
  stage2: "v1baselineHadro"
  hist: "v0BDT1tau1l_TTBBtest"
channel: "1tau1l"
eras: ["2018", "2017", "2016postVFP", "2016preVFP"]
options:
  systematics: true
  fake_tau: true
paths:
  output_base: "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
```

## Stage-Specific Docs

- `stage1-os.md` - Object Selection
- `stage2-mv.md` - Make Variables
- `stage3-wh.md` - Histograms
- `stage4-combine.md` - Templates, Datacards, Combine
