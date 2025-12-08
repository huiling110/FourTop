# Workflow Skill - FourTop Analysis Pipeline

Guide for running analysis stages with proper configuration and environment.

## When to Use

- When user asks to run any analysis stage (OS, MV, WH, PL, combine)
- When processing data for specific eras
- When generating fake backgrounds (Stage 2.4)
- When creating histograms, templates, or datacards

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

## Stage Commands

### Stage 1: Object Selection (OS)

Converts NanoAOD to skimmed ntuples with object selection.

```bash
source setEnv_newNew.sh
cd objectSelectionOptimized/jobs/

# Submit nominal jobs for 2018
python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

# Submit for all eras in config
python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml

# Dry run (show paths without submitting)
python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --dry-run

# Submit with systematic variation
python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --sys JES
python3 makeJob_OS_fromRuobing2.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --sys JERUp

# Available systematics: JES, JERUp, JERDown, METUp, METDown, EleScaleUp, EleScaleDown,
#                        TESdm0Up, TESdm0Down, TESdm1Up, TESdm1Down,
#                        TESdm10Up, TESdm10Down, TESdm11Up, TESdm11Down
# Note: Use TES by decay mode only (dm0, dm1, dm10, dm11), not total TESUp/TESDown

# Submit ALL systematic variations at once (15 total)
./submit_all_systematics.sh ../../config/analysis_config_1tau0l_TTBBtest.yaml 2018

# Check systematic job status
./check_systematic_jobs.sh 2018
```

**Note**: Stage 1 systematics create separate output directories (e.g., `v94..._JESPt22/`).

**Batch Scripts**:
- `submit_all_systematics.sh` - Submits all 15 systematic variations (JES, JER, MET, EleScale, TES by dm)
- `check_systematic_jobs.sh` - Shows job status and output file counts for each systematic

### Stage 2: Make Variables (MV)

Calculates BDT input variables from Stage 1 output.

```bash
source setEnv_newNew.sh
cd makeVariables_goodCode/jobs/

# Submit nominal jobs for 2018
python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

# Submit for all eras in config
python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml

# MC only (typical for systematic variations)
python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --mc-only

# Dry run (show paths without submitting)
python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --dry-run

# Submit with systematic variation (requires Stage 1 systematic output)
python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --sys JERUp
python3 makeJob_makeVaribles_forBDT.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --sys TESdm0Down
```

**Batch Systematic Submission** (14 variations: TES, JER, MET, EleScale):

```bash
# Submit all systematics for an era
python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

# Submit specific systematic group
python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --group TES
python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --group JER

# Available groups: TES, JER, MET, EleScale, all
```

**Path patterns**:
- Input: `{stage1_output}/UL{ERA}/{stage1_version}[_systematic]/mc/`
- Output: `{stage2_output}/{era}/{stage2_version}_{stage1_version}[_systematic]/mc/`

### Stage 2.4: Fake Background Generation

**CRITICAL**: Must regenerate for EACH new analysis version. NEVER copy from reference!

```bash
source setEnv_newNew.sh
cd plotting/

# Fake tau (required for ALL channels)
python3 createFaketauTree.py --config ../config/analysis_config_1tau0l_full.yaml --era 2018

# Fake lepton (required for 1tau1l/1tau2l only)
python3 createFakeLeptonTree.py --config ../config/analysis_config_1tau1l_full.yaml --era 2018
```

### Stage 3: Histogram Production (WH)

```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Submit jobs for all processes
python3 makeJob_forWriteHist.py --config ../../config/analysis_config_1tau0l_full.yaml --era 2018

# Monitor jobs
hep_q -u $USER
```

**Note on Systematics**:
- If `options.systematics: true` in config: Nominal WH jobs include all systematics internally.
  **Skip Stage 4.1 and JES systematic WH jobs** - they are NOT needed.
- If `options.systematics: false` in config: Only nominal histograms are produced.
  For full systematics, you would need separate JES variation jobs + Stage 4.1.

### Stage 4.1: JES Template Consolidation (SKIP if systematics: true)

Only needed when running separate JES systematic variation jobs:

```bash
source setEnv_newNew.sh
cd plotting/
python3 addJESTemplatesToHistFile.py --config ../config/analysis_config_1tau0l_full.yaml --era 2018
```

### Stage 4.2: Template Creation

```bash
python3 addTemplateNew.py --config ../config/analysis_config_1tau0l_full.yaml --era 2018
```

### Stage 4.3: Datacard Generation

```bash
python3 writeDatacard.py --config ../config/analysis_config_1tau0l_full.yaml --era 2018
```

### Stage 4.4: Validation Plots (pl.py)

```bash
source setEnv_newNew.sh
cd plotting/
python3 pl.py --config ../config/analysis_config_1tau0l_full.yaml --era 2018
```

Options read from config:
- `options.systematics`: Whether to plot with systematic error bands
- `options.fake_tau`: Whether to use data-driven fake tau
- `options.mc_fake_tau`: Whether to use MC fake tau
- `options.blind`: Whether to blind the signal region

### Stage 4.5: Combine (Statistical Analysis)

```bash
cd hua/combine/
cmsenv  # NOT setEnv_newNew.sh!
python3 runCombineAll.py  # Check script for options
```

## Era Processing Order

Recommended order for full Run2:
1. `2018` - Most data, good for validation
2. `2017` - Second highest statistics
3. `2016postVFP` - Part of 2016
4. `2016preVFP` - Part of 2016

## Common Patterns

### Check script help

```bash
python3 script.py --help
```

### Run for all eras (if supported)

```bash
# Some scripts process all eras from config if --era not specified
python3 createFaketauTree.py --config ../config/analysis_config_1tau0l_full.yaml
```

### Quiet mode (reduce output)

```bash
python3 addTemplateNew.py --config ../config/... --era 2018 --quiet
```

## Debugging

### Check workflow_utils functions

```bash
python3 -c "from plotting.workflow_utils import *; help(load_config)"
```

### Verify config loading

```bash
python3 -c "
from plotting.workflow_utils import load_config, build_hist_path
config = load_config('config/analysis_config_1tau0l_full.yaml')
print(build_hist_path(config, '2018'))
"
```

## Important Notes

1. **Never skip environment setup** - scripts will fail or produce wrong results
2. **Config is required** - all Stage 4 scripts now require --config flag
3. **Regenerate fakes** - fake tau/lepton must be generated per version
4. **Check output paths** - verify paths match expected versions
5. **Monitor jobs** - use `hep_q -u $USER` to track cluster jobs
