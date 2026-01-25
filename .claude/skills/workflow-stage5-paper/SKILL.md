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
    --execute --quiet
```

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

# Step 1: Consolidate energy scale systematics
python3 plotting/addJESTemplatesToHistFile.py \
    --config config/analysis_config_1tau0l_XGB080test.yaml \
    --era 2018 \
    --mode variables \
    --variables tausT_1pt \
    --execute --quiet

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
python3 plotting/addJESTemplatesToHistFile.py \
    --config CONFIG.yaml --era 2018 --mode variables \
    --variables "tausT_1pt,jets_HT,MET_pt" --execute

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
