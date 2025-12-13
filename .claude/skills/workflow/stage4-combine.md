# Stage 4: Templates, Datacards, Combine, and Plots

Final stages of the analysis pipeline.

## Stage Overview

| Stage | Name | Description |
|-------|------|-------------|
| 4.1 | addJES | Consolidate JES/JER/TES systematics into nominal files |
| 4.2 | addTemplate | Create template histograms for combine |
| 4.3 | smooth | Smooth systematic variations (mandatory for 1tau1l/1tau0l, requires ALL eras) |
| 4.4 | writeDatacard | Generate datacards for combine |
| 4.4.1 | Run2 combination | Combine 4 eras → 1-channel Run2 datacard (SYNC POINT) |
| 4.5 | combine fits | Run statistical analysis (significance, limits, signal strength) |
| 4.6 | postfit | Generate post-fit plots |
| 4.7 | plots | Generate pre-fit validation plots |

## Environment Setup

**IMPORTANT**: Stages 4.4.1, 4.5 require CMSSW environment

| Stage | Environment | Command |
|-------|-------------|---------|
| 4.1-4.4, 4.6, 4.7 | ROOT/Python | `source setEnv_newNew.sh` |
| 4.4.1, 4.5 | CMSSW/Combine | `source /cvmfs/cms.cern.ch/cmsset_default.sh && cmsenv` (in hua/combine/) |

## Stage 4.1: JES Template Consolidation

Only needed when running separate JES systematic variation jobs.

```bash
source setEnv_newNew.sh
python3 plotting/addJESTemplatesToHistFile.py \
  --config config/CONFIG.yaml \
  --era 2018 \
  --execute \
  --quiet
```

**IMPORTANT FLAGS**:
- `--execute`: Actually cleanup systematic directories after consolidation (default: dry-run)
- `--quiet`: Suppress verbose ROOT output (saves tokens, faster execution)
- `--keep-sys-dirs`: Keep systematic directories (skip cleanup) - only use for debugging

**What it does**:
1. Merges JES/JER/TES/MET/EES systematic variations into nominal histogram files
2. Cleans up systematic directories (ROOT files, jobSH dirs, zips logs) to free disk space

**Verification after completion**:
```bash
# Check systematic directories were cleaned
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/*TTBBtest_TES*/mc/variableHists_*/
# Should show: log.zip files exist, but *.root files are gone

# Verify consolidation worked (check nominal file size grew)
ls -lh /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/variableHists_v0BDT1tau1l_TTBBtest/*.root
# Files should be larger (~100-500 MB) after adding systematics
```

## Stage 4.2: Template Creation

```bash
source setEnv_newNew.sh
cd plotting/
python3 addTemplateNew.py --config ../config/CONFIG.yaml --era 2018
```

**What it does**: Creates template histograms for combine from WH output.

## Stage 4.3: Smooth Systematics

**CRITICAL**:
- Run AFTER addTemplateNew.py (4.2) and BEFORE writeDatacard.py (4.4)
- **Requires ALL eras to have templates** - this is a synchronization point
- **Mandatory for 1tau1l and 1tau0l channels**

Smooths systematic variations to reduce statistical fluctuations that can cause fit instabilities.

```bash
source setEnv_newNew.sh
cd plotting/
python3 smooth_systematics_fourTops.py --config ../config/CONFIG.yaml --quiet
```

**Config requirement**: Set `options.smoothing: true` in your config to enable.

**Channel-specific settings** are defined in the script itself (`CHANNEL_SMOOTHING_CONFIG`):
- **1tau1l**: `tt, ttbb, ttH, ttZ, ttW, singleTop` with `ps_fsr, ps_isr, QCDscale_*, CMS_scale_j_*, CMS_res_j`
- **1tau0l**: `tt, ttbb, ttH, ttZ, ttW, WJets` with `ps_fsr, ps_isr, QCDscale_*, CMS_btag_fullShape_hf, pdf_alphas`
- **1tau2l**: `tt, ttbb, ttH, ttZ, ttW, singleTop` with `ps_fsr, ps_isr, QCDscale_*, CMS_scale_j_*, CMS_res_j`

**What it does**:
- Applies LOWESS smoothing to systematic shape variations
- Creates `*_smoothed.root` template files
- Outputs comparison plots to `results/` subdirectory
- Processes all eras specified in config

**When to skip**: For quick tests set `options.smoothing: false` in config. Script will exit early.

## Stage 4.4: Datacard Generation

```bash
source setEnv_newNew.sh
cd plotting/
python3 writeDatacard.py --config ../config/CONFIG.yaml --era 2018
```

**Note**: writeDatacard.py uses the smoothed templates when `options.smoothing: true` in config.

## Stage 4.4.1: Run2 Combination (SYNC POINT)

**Requires all 4 eras to have datacards (Stage 4.4 done)**

Combines per-era datacards into a single Run2 datacard for the channel.

```bash
cd hua/combine/
source /cvmfs/cms.cern.ch/cmsset_default.sh && cmsenv

python3 writeCombinationDatacard.py \
  --config ../../config/analysis_config_1tau1l_TTBBtest.yaml \
  --channel 1tau1l
```

**Output**: `hua/combine/combinationV{XX}/run2_{channel}_v4/datacard.txt`

**Version**: Uses `versions.combination` from config (e.g., `combinationV21`)

## Stage 4.5: Combine Fits (Statistical Analysis)

**IMPORTANT**: Combine is SLOW (1-2 hours) - Always use screen session!

### Recommended: Run with Bash Script in Screen

```bash
# Create screen session
screen -S combine_1tau1l_2018

# Inside screen: Run the wrapper script
cd hua/combine/
bash run_combine_fits.sh ../../config/analysis_config_1tau1l_TTBBtest.yaml 2018 1tau1l

# Detach: Ctrl+A then D
# Reattach: screen -r combine_1tau1l_2018
# Monitor: tail -f combine_1tau1l_2018_YYYYMMDD_HHMMSS.log
```

**Script does**:
- Sets up CMSSW environment (cmsenv) automatically
- Builds datacard path from config
- Runs all combine steps: workspace, significance, postfit, signal_strength, impacts
- Creates timestamped log file
- Takes ~1-2 hours to complete

**Arguments**:
1. `CONFIG_FILE`: Path to YAML config (e.g., `../../config/analysis_config_1tau1l_TTBBtest.yaml`)
2. `ERA`: Era to process (`2018`, `2017`, `2016preVFP`, `2016postVFP`)
3. `CHANNEL`: Channel name (`1tau1l`, `1tau0l`, `1tau2l`)

### Alternative: Direct Python Call (Advanced)

Only if you need custom options. **IMPORTANT**: Must setup CMSSW environment first!

```bash
cd hua/combine/

# Setup CMSSW (required for combine directory!)
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv  # NOT setEnv_newNew.sh!

# Then run combine
python3 runCombineAll.py --cardDir CARDDIR --channel CHANNEL --no-blind --steps workspace significance postfit
```

**Note**: The bash script `run_combine_fits.sh` handles CMSSW setup automatically.

## Stage 4.6: Postfit Plots

Generate post-fit distributions using combine results.

```bash
source setEnv_newNew.sh
python3 plotting/pl_postFit.py --fit-file hua/combine/combinationV21/run2_1tau0l_v4/combineResults/postfitPlots/fitDiagnosticsTest.root
```

**Options**:
- `--plot-type`: `prefit`, `postfit`, or `both` (default: postfit)
- `--no-logy`: Use linear scale instead of log
- `--blind`: Blind signal region data

**Output**: Plots saved to `{fit-file-dir}/postfitPlots/`

**Requires**: Combine fits (Stage 4.5) must be complete (fitDiagnosticsTest.root exists).

## Stage 4.7: Pre-fit Validation Plots (pl.py)

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
