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
metadata:
  channel: "1tau0l"
paths:
  base: "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
  out_version: "v1baselineHadro"
  in_version: "v94HadroPreJetVetoHemOnly"
  hist_version: "v0BDT1tau0l"
eras:
  - "2018"
  - "2017"
  - "2016preVFP"
  - "2016postVFP"
options:
  ifFakeTau: true
  ifMCFTau: false
  ifBlind: false
```

## Stage Commands

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

### Stage 4.1: JES Template Consolidation

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
python3 pl.py  # Uses hardcoded paths currently - check inside script
```

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
