# Stage 5: Paper Plots and Input Variable Prefit

## Overview

This stage covers publication-quality plots and input variable prefit plots for the four-top analysis.

## Environment

```bash
source setEnv_newNew.sh
```

---

## Input Variable Prefit Plots

Generate prefit plots for input variables (tausT_1pt, jets_HT, etc.) using the same workflow as BDT but with `--mode variables`.

### Workflow

The input variable prefit workflow follows Stage 3-4 but uses `inputVarHists_*` directories instead of `variableHists_*`.

#### 1. Generate WH Output (Stage 3)

```bash
cd writeHistGood/jobs/

# Build variableAnalyzer
cd .. && make variables && cd jobs/

# Submit nominal + energy scale systematics
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era 2018 --systematic complete --mode variables
```

**Output**: `{MV_dir}/mc/inputVarHists_{version}/`

#### 2. Consolidate Energy Scale Systematics (Stage 4.1)

```bash
python3 plotting/addJESTemplatesToHistFile.py \
    --config config/CONFIG.yaml \
    --era 2018 \
    --mode variables \
    --variables tausT_1pt \
    --execute --quiet \
    --keep-sys-dirs  # CRITICAL: Keep systematic dirs for other variables!
```

**CRITICAL**: Always use `--keep-sys-dirs` for input variables mode! By default, addJES deletes the systematic variation directories after merging. If you need to process multiple variables (tausT_1pt, tausF_1jetPt, jets_HT, etc.), you MUST keep the source directories.

**Note**: JES variations require separate Stage 2/3 jobs with JES systematic flag. For prefit plots, JER/TES/MET/EES are sufficient.

#### 3. Create Template File (Stage 4.2)

```bash
python3 plotting/addTemplateNew.py \
    --config config/CONFIG.yaml \
    --era 2018 \
    --mode variables \
    --variables tausT_1pt
```

**Output**: `{inputVarHists_dir}/combine/templatesForCombine{channel}_{version}_{variable}_*.root`

#### 4. Write Datacard (Stage 4.4)

```bash
python3 plotting/writeDatacard.py \
    --config config/CONFIG.yaml \
    --era 2018 \
    --mode variables \
    --variable tausT_1pt \
    --no-smoothed
```

**Output**: `{inputVarHists_dir}/combine/datacardSys_{version}_{variable}/datacard.txt`

### Full Example (2018, tausT_1pt)

```bash
source setEnv_newNew.sh

# Assuming WH output exists from variableAnalyzer

# Step 1: Consolidate energy scale systematics (KEEP sys dirs for other variables!)
python3 plotting/addJESTemplatesToHistFile.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --era 2018 \
    --mode variables \
    --variables tausT_1pt \
    --execute --quiet --keep-sys-dirs

# Step 2: Create template
python3 plotting/addTemplateNew.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --era 2018 \
    --mode variables \
    --variables tausT_1pt

# Step 3: Write datacard
python3 plotting/writeDatacard.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --era 2018 \
    --mode variables \
    --variable tausT_1pt \
    --no-smoothed
```

### Multiple Variables

Process multiple variables by specifying a comma-separated list:

```bash
# addJES and addTemplate support comma-separated variables
# CRITICAL: Use --keep-sys-dirs to preserve dirs for other eras/variables!
python3 plotting/addJESTemplatesToHistFile.py \
    --config CONFIG.yaml --era 2018 --mode variables \
    --variables "tausT_1pt,jets_HT,MET_pt" --execute --keep-sys-dirs

python3 plotting/addTemplateNew.py \
    --config CONFIG.yaml --era 2018 --mode variables \
    --variables "tausT_1pt,jets_HT,MET_pt"

# writeDatacard processes one variable at a time
for var in tausT_1pt jets_HT MET_pt; do
    python3 plotting/writeDatacard.py \
        --config CONFIG.yaml --era 2018 --mode variables \
        --variable $var --no-smoothed
done
```

### Available Variables

Variables are defined in `writeHistGood/src/functions.C:initializeHistVec()`:

| Category | Variables |
|----------|-----------|
| Tau | tausT_1pt, tausT_1eta, tausT_1phi, tausT_1mass, tausT_1decayMode |
| Jets | jets_num, jets_HT, jets_MHT |
| B-jets | bjetsM_num, bjetsM_1pt, bjetsM_2pt |
| MET | MET_pt, MET_phi |
| Kinematics | nJetsAbovePtCut, minDeltaRTauJet |

### Directory Structure Comparison

| Mode | Histogram Dir | Template Dir |
|------|---------------|--------------|
| bdt (default) | `variableHists_{version}/` | `variableHists_*/combine/` |
| variables | `inputVarHists_{version}/` | `inputVarHists_*/combine/` |

---

## Publication Plots

### Postfit Plots (after Combine)

```bash
# Standard postfit
python3 plotting/pl_postFit.py --fit-file hua/combine/.../fitDiagnosticsTest.root

# Publication mode (clean labels, no "Preliminary")
python3 plotting/pl_postFit.py --fit-file hua/combine/.../fitDiagnosticsTest.root --paper
```

### Impact Plots

Impact plots are generated during Stage 4.5 combine fits. Results are in:
```
hua/combine/{combination}/run2_{channel}_{version}/combineResults/impactResult/impacts.json
```

---

## Verification

### Check Template Content

```bash
source setEnv_newNew.sh && python3 << 'EOF'
import ROOT
template = "path/to/templatesForCombine1tau0l_v3_tausT_1pt_notMCFTau_unblind.root"
f = ROOT.TFile(template, "READ")
hists = [k.GetName() for k in f.GetListOfKeys()]
print(f"Total histograms: {len(hists)}")

# Count systematics
sys_hists = [h for h in hists if 'Up' in h or 'Down' in h]
nom_hists = [h for h in hists if 'Up' not in h and 'Down' not in h]
print(f"Nominal: {len(nom_hists)}, Systematic: {len(sys_hists)}")
EOF
```

### Validate Datacard

```bash
# Check datacard structure
head -20 path/to/datacard.txt

# Validate with combine (requires cmsenv)
cd hua/combine && cmsenv
ValidateDatacards.py datacard.txt
```

---

## Getting Prefit Shapes from Combine

### Quick Command

```bash
cd hua/combine && cmsenv
cd /path/to/datacardSys_v1_xgb080_test_{variable}/

# Create workspace
text2workspace.py datacard.txt -o workspace_{variable}.root

# Get prefit shapes (with --skipBOnlyFit for speed)
combine -M FitDiagnostics workspace_{variable}.root \
    --saveShapes \
    --saveWithUncertainties \
    --skipBOnlyFit \
    -n _{variable}_prefit
```

### Output Structure

`fitDiagnostics_{variable}_prefit.root`:
```
shapes_prefit/
├── {channel}_{era}/
│   ├── data (TGraphAsymmErrors)
│   ├── {process} (TH1F) - per-process histograms
│   ├── total (TH1F)
│   ├── total_signal (TH1F)
│   ├── total_background (TH1F)
│   └── total_covar (TH2F) - covariance matrix
shapes_fit_s/ (similar structure, S+B fit)
```

### Key Options

| Option | Purpose |
|--------|---------|
| `--saveShapes` | Save prefit and postfit shapes |
| `--saveWithUncertainties` | Include stat+sys uncertainties |
| `--skipBOnlyFit` | Skip background-only fit (faster) |
| `-t -1` | Use Asimov dataset (blinded) |

### Extract Prefit Histograms

```python
import ROOT

f = ROOT.TFile("fitDiagnostics_{variable}_prefit.root", "READ")
shapes = f.Get("shapes_prefit/SR1tau0l_2018")

# Get stacked background
total_bkg = shapes.Get("total_background")

# Get individual processes
ttbb = shapes.Get("ttbb")
tttt = shapes.Get("tttt")

# Data points
data = shapes.Get("data")  # TGraphAsymmErrors

# Covariance matrix for uncertainty band
covar = shapes.Get("total_covar")
```

**Note**: NumPy version warnings in CMSSW env can be ignored - combine runs successfully.

---

## Plotting Prefit Input Variables

After FitDiagnostics creates `shapes_prefit`, use `plot_prefit_inputvar.py` to create publication-quality plots.

### Basic Usage

```bash
source setEnv_newNew.sh
cd plotting/plotting_paper/

# Single channel
python plot_prefit_inputvar.py fitDiagnostics.root \
    --variable tausT_1pt \
    --channels SR1tau0l \
    --output-dir ./plots

# Run2 combination
python plot_prefit_inputvar.py fitDiagnostics_run2.root \
    --variable tausT_1pt \
    --channels SR1tau0l SR1tau1l SR1tau2l \
    --output-dir ./plots
```

### Key Features

- **Linear y-axis** (appropriate for input variables, unlike log-scale BDT plots)
- **No event counts in legend** (cleaner for publication)
- **Same CMS styling** as `plot_postfit_histograms.py` (fonts, colors, stacking order)
- **Auto-positioning legend** based on histogram shape
- **Data/MC ratio panel** with uncertainty band

### Output Files

```
prefit_inputvar_{channel}_{variable}.pdf
prefit_inputvar_{channel}_{variable}.png
```

### Example: Full Run2 Prefit Workflow

```bash
# 1. Combine datacards (use combineCards.py)
cd hua/combine/combinationV{XX}/run2_1tau0l_{variable}/
cmsenv
combineCards.py \
    SR1tau0l_2018="$BASE/2018/.../datacardSys_v1_{variable}/datacard.txt" \
    SR1tau0l_2017="$BASE/2017/.../datacardSys_v1_{variable}/datacard.txt" \
    SR1tau0l_2016preVFP="$BASE/2016preVFP/.../datacardSys_v1_{variable}/datacard.txt" \
    SR1tau0l_2016postVFP="$BASE/2016postVFP/.../datacardSys_v1_{variable}/datacard.txt" \
    > datacard.txt

# 2. Create workspace and run FitDiagnostics
text2workspace.py datacard.txt -o workspace.root
combine -M FitDiagnostics workspace.root \
    --saveShapes --saveWithUncertainties --skipBOnlyFit \
    -n _run2_{variable}_prefit

# 3. Create plots
source setEnv_newNew.sh
cd plotting/plotting_paper/
python plot_prefit_inputvar.py \
    ../../hua/combine/combinationV{XX}/run2_1tau0l_{variable}/fitDiagnostics_run2_{variable}_prefit.root \
    --variable {variable} \
    --channels SR1tau0l \
    --output-dir ./plots
```

### Available Variable Labels

| Variable | X-axis Label |
|----------|--------------|
| `tausT_1pt` | τh pT [GeV] |
| `jets_HT` | HT [GeV] |
| `MET_pt` | pTmiss [GeV] |
| `bjetsM_num` | Number of b-jets |
| `jets_num` | Number of jets |
| `tausT_1eta` | τh η |
| `tausT_1decayMode` | τh decay mode |
| `lepsT_1pt` | Lepton pT [GeV] |

For additional variables, add to `VARIABLE_LABELS` dict in the script.

---

## Automation Script: run_inputvar_prefit_pipeline.py

For processing multiple regions (SR, CRMR, VR) with a single command:

```bash
source setEnv_newNew.sh

# Full pipeline (Stage 4.1 to plots) - DRY-RUN first
python scripts/run_inputvar_prefit_pipeline.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --variable tausT_1pt \
    --regions SR CRMR VR \
    --dry-run

# Execute (Stage 4.1-4.4 only, combine needs cmsenv)
python scripts/run_inputvar_prefit_pipeline.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --variable tausT_1pt \
    --regions SR CRMR VR \
    --start-from addjes
```

### Multi-Region Datacards

The `--region` parameter in `writeDatacard.py` supports SR, CRMR, VR:

```bash
# Generate datacards for each region
for REGION in SR CRMR VR; do
    python3 plotting/writeDatacard.py \
        --config config/CONFIG.yaml --era 2018 \
        --mode variables --variable tausT_1pt \
        --region $REGION --no-smoothed
done
```

Output paths:
- SR: `datacardSys_v1_xgb080_test_tausT_1pt/`
- CRMR: `datacardSys_v1_xgb080_test_tausT_1pt_CRMR/`
- VR: `datacardSys_v1_xgb080_test_tausT_1pt_VR/`

### Run2 Combination for Multiple Regions

```bash
cd hua/combine && cmsenv

for REGION in SR CRMR VR; do
    mkdir -p combinationV23/run2_1tau0l_tausT_1pt_$REGION
    cd combinationV23/run2_1tau0l_tausT_1pt_$REGION

    # Determine version suffix
    if [ "$REGION" = "SR" ]; then
        VERSION="v1_xgb080_test_tausT_1pt"
    else
        VERSION="v1_xgb080_test_tausT_1pt_$REGION"
    fi

    # Combine datacards
    combineCards.py \
        ${REGION}1tau0l_2018="$BASE/2018/.../datacardSys_$VERSION/datacard.txt" \
        ${REGION}1tau0l_2017="$BASE/2017/.../datacardSys_$VERSION/datacard.txt" \
        ${REGION}1tau0l_2016preVFP="$BASE/2016preVFP/.../datacardSys_$VERSION/datacard.txt" \
        ${REGION}1tau0l_2016postVFP="$BASE/2016postVFP/.../datacardSys_$VERSION/datacard.txt" \
        > datacard.txt

    # Create workspace and run FitDiagnostics
    text2workspace.py datacard.txt -o workspace.root
    combine -M FitDiagnostics workspace.root \
        --saveShapes --saveWithUncertainties --skipBOnlyFit \
        -n _run2_tausT_1pt_${REGION}_prefit

    cd ../..
done
```

### Plot All Regions

```bash
source setEnv_newNew.sh
cd plotting/plotting_paper/

for REGION in SR CRMR VR; do
    python plot_prefit_inputvar.py \
        ../../hua/combine/combinationV23/run2_1tau0l_tausT_1pt_$REGION/fitDiagnostics_run2_tausT_1pt_${REGION}_prefit.root \
        --variable tausT_1pt \
        --channels ${REGION}1tau0l \
        --output-dir ./inputvar_plots
done
```

---

## Fake Tau Jet Variables (tausF_*)

For variables like `tausF_1jetPt` (fake tau candidate jet pT):

1. **WH jobs include all variables** - nominal + systematics run together
2. **addJES merges energy scale systematics** per variable
3. **Run addJES before addTemplate** for each variable you want to plot

```bash
# Merge energy scale systematics for tausF_1jetPt
# CRITICAL: Always use --keep-sys-dirs for input variables!
python3 plotting/addJESTemplatesToHistFile.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --era 2018 --mode variables \
    --variables tausF_1jetPt \
    --execute --quiet --keep-sys-dirs
```

**WARNING**: If you ran addJES without `--keep-sys-dirs`, the systematic directories are deleted and you must resubmit WH Stage 3 jobs:
```bash
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/CONFIG.yaml --era ERA --systematic complete --mode variables
```
