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
→ Stage 4.1 (merge JES) → Stage 4.2-4.4 (re-run with systematics)
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

## Workflow Status Check

To determine the current workflow state and next step, check these indicators:

### Quick Status Check Commands

```bash
# Check config for workflow mode
grep "systematics:" config/analysis_config_1tau0l_TTBBtest.yaml

# Check Stage 2 output (nominal exists?)
ls -d /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94*_TTBBtest/ 2>/dev/null | head -3

# Check Stage 2 systematic outputs
ls -d /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94*_TES*/ 2>/dev/null | wc -l

# Check Stage 3 histograms exist
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_*/mc/variableHists_*/allHist*.root 2>/dev/null | wc -l

# Check running jobs
hep_q -u $USER | grep -c running
```

### State Inference Table

| State | Indicators | Next Step |
|-------|------------|-----------|
| **Not started** | No Stage 2 output | Start with Mode 1: OS → MV → Fake |
| **Nominal complete** | Stage 2 nominal exists, no sys dirs | Mode 2: Add systematics (OS sys) |
| **OS sys running** | Jobs in queue with "OS" | Wait, then MV sys |
| **MV sys complete** | 14+ Stage 2 sys dirs exist | Stage 3.1 (WH sys) |
| **WH sys running** | Jobs in queue with "WH" | Wait for completion |
| **WH sys complete** | variableHists in all sys dirs | Stage 4.1 (merge JES) |
| **Stage 4.1 done** | histAllDNN.root updated | Stage 4.2-4.4 (templates) |
| **Ready for combine** | Datacards exist | Stage 4.5 (cmsenv) |

### Determine Next Step

When resuming work, run:
```bash
source setEnv_newNew.sh
# Check jobs
hep_q -u $USER

# Check what exists for 2018
ls -d /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_*/ | wc -l
# Expected: 1 (nominal only) or 15 (nominal + 14 sys)
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
python3 makeJob_forWriteHist.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

# Monitor jobs
hep_q -u $USER
```

**Note on Systematics**:
- If `options.systematics: true` in config: Nominal WH jobs include all weight systematics internally.
  Still need Stage 3.1 for **energy scale** systematics (TES, JER, MET, EleScale).
- If `options.systematics: false` in config: Only nominal histograms are produced.

### Stage 3.1: WH Systematic Variations (Energy Scale)

Submit WH jobs for energy scale systematic variations (TES, JER, MET, EleScale).
Requires Stage 2.1 (MV systematics) to be complete.

```bash
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Submit ALL systematics for 2018 (14 variations × 59 MC files = 826 jobs)
python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

# Submit specific systematic group
python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --group TES
python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --group JER

# Dry run
python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --dry-run

# Available groups: TES, JER, MET, EleScale, all
```

**Systematic variations**:
- TES: TESdm0Up/Down, TESdm1Up/Down, TESdm10Up/Down, TESdm11Up/Down (8)
- JER: JERUp/Down (2)
- MET: METUp/Down (2)
- EleScale: EleScaleUp/Down (2)

### Stage 4.1: JES Template Consolidation

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
