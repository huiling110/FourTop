# Stage 4: Templates, Datacards, Plots, and Combine

Final stages of the analysis pipeline.

## Environment Setup

**IMPORTANT**: Stage 4.1-4.3 use ROOT/Python, Stage 4.4-4.5 use CMSSW/Combine

| Stage | Environment | Command |
|-------|-------------|---------|
| 4.1-4.3 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.4-4.5 | CMSSW/Combine | `cmsenv` (in hua/combine/) |

## Stage 4.1: JES Template Consolidation

Only needed when running separate JES systematic variation jobs.

```bash
source setEnv_newNew.sh
cd plotting/
python3 addJESTemplatesToHistFile.py --config ../config/CONFIG.yaml --era 2018
```

**What it does**: Merges JES systematic variations from separate histogram files into the nominal histogram file.

## Stage 4.2: Template Creation

```bash
source setEnv_newNew.sh
cd plotting/
python3 addTemplateNew.py --config ../config/CONFIG.yaml --era 2018
```

**What it does**: Creates template histograms for combine from WH output.

## Stage 4.2.5: Smooth Systematics (IMPORTANT!)

**CRITICAL**: Run AFTER addTemplateNew.py and BEFORE writeDatacard.py.

Smooths systematic variations to reduce statistical fluctuations that can cause fit instabilities.

```bash
source setEnv_newNew.sh
cd plotting/
python3 smooth_systematics_fourTops.py --config ../config/CONFIG.yaml
```

**Config requirements**: Add a `smoothing` section to your config:

```yaml
smoothing:
  systematics:
    - ps_fsr
    - ps_isr
    - QCDscale_fac
    - QCDscale_ren
    - CMS_scale_j_FlavorPureGluon
    - CMS_scale_j_FlavorPureQuark
    - CMS_res_j
    - CMS_btag_fullShape_hf
    - pdf_alphas
  processes:
    - tt
    - ttH
    - ttZ
    - ttW
    - WJets
```

**What it does**:
- Applies LOWESS smoothing to systematic shape variations
- Creates `*_smoothed.root` template files
- Outputs comparison plots to `results/` subdirectory
- Processes all eras specified in config

**When to skip**: For quick tests with `options.smoothing: false`, you can skip this step.

## Stage 4.3: Datacard Generation

```bash
source setEnv_newNew.sh
cd plotting/
python3 writeDatacard.py --config ../config/CONFIG.yaml --era 2018
```

**Note**: writeDatacard.py uses the smoothed templates when `options.smoothing: true` in config.

## Stage 4.4: Validation Plots (pl.py)

```bash
source setEnv_newNew.sh
cd plotting/
python3 pl.py --config ../config/CONFIG.yaml --era 2018
```

Options read from config:
- `options.systematics`: Whether to plot with systematic error bands
- `options.fake_tau`: Whether to use data-driven fake tau
- `options.mc_fake_tau`: Whether to use MC fake tau
- `options.blind`: Whether to blind the signal region

## Stage 4.5: Combine (Statistical Analysis)

**IMPORTANT**: Switch to CMSSW environment!

```bash
cd hua/combine/
cmsenv  # NOT setEnv_newNew.sh!
python3 runCombineAll.py  # Check script for options
```

## Common Options

### Check script help

```bash
python3 script.py --help
```

### Run for all eras (if supported)

```bash
# Some scripts process all eras from config if --era not specified
python3 createFaketauTree.py --config ../config/CONFIG.yaml
```

### Quiet mode (reduce output)

```bash
python3 addTemplateNew.py --config ../config/CONFIG.yaml --era 2018 --quiet
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
config = load_config('config/CONFIG.yaml')
print(build_hist_path(config, '2018'))
"
```

## Important Notes

1. **Never skip environment setup** - scripts will fail or produce wrong results
2. **Config is required** - all Stage 4 scripts now require --config flag
3. **Regenerate fakes** - fake tau/lepton must be generated per version
4. **Check output paths** - verify paths match expected versions
5. **Monitor jobs** - use `hep_q -u $USER` to track cluster jobs

## Next Step

After Stage 4 complete: **Combine analysis** or start next era/channel
