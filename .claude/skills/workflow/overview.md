# Workflow Skill - FourTop Analysis Pipeline

Guide for running analysis stages with proper configuration and environment.

## When to Use

- When user asks to run any analysis stage (OS, MV, WH, PL, combine)
- When processing data for specific eras
- When generating fake backgrounds (Stage 2.4)
- When creating histograms, templates, or datacards

---

## Three Workflow Modes

### Mode 1: Nominal Test Run

Quick validation run with only nominal samples (no systematics).

**When to use**: Testing new config, validating paths, debugging.

**Config setting**: `options.systematics: false`

**Steps**:
```
Stage 1 (OS) nominal → Stage 2 (MV) nominal → Stage 2.4 (Fake)
→ Stage 3 (WH) nominal → Stage 4.2-4.4 (Templates, Datacards, Plots)
```

**Commands**:
```bash
source setEnv_newNew.sh

# Stage 1: OS nominal
cd objectSelectionOptimized/jobs/
python3 makeJob_OS_fromRuobing2.py --config ../../config/CONFIG.yaml --era 2018

# Stage 2: MV nominal
cd makeVariables_goodCode/jobs/
python3 makeJob_makeVaribles_forBDT.py --config ../../config/CONFIG.yaml --era 2018

# Stage 2.4: Fake backgrounds
cd plotting/
python3 createFaketauTree.py --config ../config/CONFIG.yaml --era 2018

# Stage 3: WH nominal
cd writeHistGood/jobs/
python3 makeJob_forWriteHist.py --config ../../config/CONFIG.yaml --era 2018

# Stage 4: Templates and plots
cd plotting/
python3 addTemplateNew.py --config ../config/CONFIG.yaml --era 2018
python3 writeDatacard.py --config ../config/CONFIG.yaml --era 2018
python3 pl.py --config ../config/CONFIG.yaml --era 2018
```

### Mode 2: Add Systematics After Nominal Test

After nominal validation, add energy scale systematic variations.

**When to use**: Nominal test passed, ready to add systematic variations.

**Config setting**: Keep `options.systematics: false` (nominal WH already done)

**Steps** (continue from Mode 1):
```
Stage 1.1 (OS sys) → Stage 2.1 (MV sys) → Stage 3.1 (WH sys)
→ Stage 4.1 (merge JES) → Stage 4.2 (templates) → Stage 4.2.5 (smoothing)
→ Stage 4.3 (datacards) → Stage 4.4 (plots)
```

**Commands**:
```bash
source setEnv_newNew.sh

# Stage 1.1: OS all systematics (15 variations)
cd objectSelectionOptimized/jobs/
./submit_all_systematics.sh ../../config/CONFIG.yaml 2018

# Stage 2.1: MV all systematics (14 variations: TES, JER, MET, EleScale)
cd makeVariables_goodCode/jobs/
python3 makeJob_MV_JESVariation.py --config ../../config/CONFIG.yaml --era 2018

# Stage 3.1: WH all systematics (14 variations)
cd writeHistGood/jobs/
python3 makeJob_WH_forJES.py --config ../../config/CONFIG.yaml --era 2018

# Stage 4.1: Merge JES templates into nominal
cd plotting/
python3 addJESTemplatesToHistFile.py --config ../config/CONFIG.yaml --era 2018

# Stage 4.2-4.4: Re-run with systematics in config
# Set options.systematics: true in config first!
python3 addTemplateNew.py --config ../config/CONFIG.yaml --era 2018

# Stage 4.2.5: Smooth systematics (IMPORTANT - before writeDatacard!)
python3 smooth_systematics_fourTops.py --config ../config/CONFIG.yaml

# Stage 4.3-4.4: Datacards and plots
python3 writeDatacard.py --config ../config/CONFIG.yaml --era 2018
python3 pl.py --config ../config/CONFIG.yaml --era 2018
```

### Mode 3: Full Workflow (Nominal + Systematics Together)

Complete pipeline from scratch with all systematics.

**When to use**: Production run, final results.

**Config setting**: `options.systematics: true`

**Steps**:
```
Stage 1 (nominal) + Stage 1.1 (systematics) → Stage 2 + 2.1 → Stage 2.4
→ Stage 3 (with internal sys) + 3.1 (energy scale sys)
→ Stage 4.1 (merge JES) → Stage 4.2-4.4 → Stage 4.5 (Combine)
```

**Commands**:
```bash
source setEnv_newNew.sh

# Run nominal and systematics together (parallel if resources allow)
# Follow Mode 1 for nominal, Mode 2 for systematics
# Then Stage 4.5 for combine:

cd hua/combine/
cmsenv  # Switch environment for combine
python3 writeCombinationDatacard.py --config CONFIG.yaml --era run2
python3 runCombineAll.py ...  # See combine docs
```

---

## Environment Requirements

**CRITICAL**: Always source the correct environment BEFORE running scripts.

| Stages | Environment | Command |
|--------|-------------|---------|
| 1, 2, 2.4, 3, 4.1-4.3, 4.6 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.4, 4.5 (combine) | CMSSW | `cmsenv` (in hua/combine/) |

## Config-Based Workflow

All scripts require `--config` and `--era` flags. Never use hardcoded paths.

### Available Configs

```
config/analysis_config_1tau0l_full.yaml      # 1tau0l channel
config/analysis_config_1tau1l_TTBBtest.yaml  # 1tau1l channel
config/analysis_config_1tau2l.yaml           # 1tau2l channel
config/analysis_config_template.yaml         # Template for new configs
```

### Config Schema (minimal)

```yaml
versions:
  stage1: "v94HadroPreJetVetoHemOnly_TTBBtest"
  stage2: "v1baselineHadro"
  hist: "v0BDT1tau0l_TTBBtest"
  datacard: "v1_TTBBtest"
  combination: "combinationV21"

channel: "1tau0l"

eras:
  - "2018"
  - "2017"
  - "2016preVFP"
  - "2016postVFP"

options:
  fake_tau: true
  mc_fake_tau: false
  blind: false
  systematics: true  # Set false for testing without JES
  smoothing: false

paths:
  nanoaod_base: "/publicfs/cms/data/TopQuark/nanoAOD"
  output_base: "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
```

## Python Script Pattern (workflow_utils)

All Stage 4 scripts MUST use `workflow_utils` for consistent config handling:

```python
from workflow_utils import (
    load_config, build_hist_path, get_channel, get_regions, get_options
)

# Load config (validates and normalizes format)
config = load_config(args.config)

# Build paths
inputDir = build_hist_path(config, args.era)

# Get settings from config
options = get_options(config)
channel = get_channel(config)
regionList = get_regions(config)

# Access options
ifSystematic = options['systematics']
ifFTau = options['fake_tau']
ifMCFTau = options['mc_fake_tau']
ifblinding = options['blind']
```

**Key workflow_utils functions:**
- `load_config(path)` - Load and validate YAML config
- `build_stage1_input(config, era)` - Build NanoAOD input path
- `build_stage1_output(config, era, sys)` - Build Stage 1 output path (optional systematic suffix)
- `build_stage2_path(config, era)` - Build Stage 2 output path (nominal)
- `build_stage2_output(config, era, sys, data_type)` - Build Stage 2 output with systematic support
- `build_hist_path(config, era)` - Build histogram directory path
- `get_options(config)` - Get normalized options dict
- `get_channel(config)` - Get channel name
- `get_channel_if1tau2l(config)` - Get if1tau2l flag (0 or 1) for Stage 1/2
- `get_regions(config)` - Get default regions for channel
- `get_versions(config)` - Get version strings
- `ERA_TO_UL` - Dict mapping era names to UL directory names
- `ERA_TO_NANOAOD` - Dict mapping era names to NanoAOD directory names

---

**For stage-specific commands, see:**
- stage1-os.md - Object Selection (Stage 1, 1.1)
- stage2-mv.md - Make Variables (Stage 2, 2.1, 2.4)
- stage3-wh.md - Histograms (Stage 3, 3.1)
- stage4-combine.md - Templates, Datacards, Combine (Stage 4.1-4.5)
- status-checker.md - How to check pipeline status
