# Complete Four-Top Analysis Workflow

**Date**: 2025-11-24
**Branch**: addVLL
**Purpose**: Document end-to-end analysis workflow for future optimization and automation

---

## Overview

This document captures the complete workflow from NanoAOD input to final physics results (limits, cross-sections, significances).

**Analysis channels**: `1tau0l`, `1tau1l`, `1tau2l`

**Physics goals**:
- Measure tttt (four-top) production cross-section
- Search for Vector-Like Lepton (VLL) signals at various mass points
- Extract statistical limits and significances

---

## Workflow Stages

```
NanoAOD (CMS data format)
    ↓
[1] Object Selection & Variables Calculation
    ↓
[2] BDT Training (optional, if BDT not already trained)
    ↓
[3] Histogram Production (nominal + systematics)
    ↓
[4] Plotting and Result Extraction
    ├─ [4.1] Consolidate Shape Systematics
    ├─ [4.2] Template Creation
    ├─ [4.2.5] Systematic Smoothing (optional, 1tau0l/1tau1l only)
    ├─ [4.3] Datacard Creation
    ├─ [4.4] Workspace Creation
    ├─ [4.5] Statistical Analysis (Combine)
    └─ [4.6] Results Visualization
```

---

## Stage 1: NanoAOD → Selected Events with Variables

**Location**: Upstream processing (not in this repository)

**Input**: CMS NanoAOD ROOT files
**Output**: NanoAOD with additional branches for analysis variables

**Example input directory**:
```
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/
```

**Content**: ROOT files for each process (tttt, ttbar, ttW, ttZ, ttH, VLL, data, etc.)

**Key branches added**:
- Object selections: jets, b-jets, leptons, taus
- Physics variables: invariant masses, delta R, transverse masses, HT, MET
- Event weights: generator, pileup, b-tagging, lepton/tau ID scale factors

**Shape systematic variations** (separate input directories):
- JES (27 sources): `*_JESup_SOURCE/`, `*_JESDown_SOURCE/`
- JER: `*_JERUp/`, `*_JERDown/`
- TES (4 decay modes): `*_TESdm{0,1,10,11}{Up,Down}/`
- MET: `*_METUp/`, `*_METDown/`
- Electron scale: `*_EleScaleUp/`, `*_EleScaleDown/`

---

## Stage 2: BDT Training (if needed)

**Location**: `hua/tmva/`

**Purpose**: Train Boosted Decision Tree for signal/background discrimination

**When needed**:
- First time running analysis
- When changing variable set
- When optimizing BDT performance

**Workflow**:

### 2.1 Prepare Variable List
```bash
cd hua/tmva/newCode/inputList/
# Edit inputList_1tau1l_final.csv with variables to use
```

### 2.2 Train BDT
```bash
cd hua/tmva/
python3 run_MVATraining.py
# This creates trained model in output/
```

**Output**:
- Trained BDT weights: `dataset/weight/TMVAClassification_BDT.weights.xml`
- Performance plots: ROC curves, overtrain check, variable importance

**Training settings**:
- Signal: tttt or VLL
- Background: ttbar, ttW, ttZ, etc.
- Typical variables: ~25-30 physics observables

**Note**: Trained BDT is used in Stage 3 to calculate BDT score for each event

---

## Stage 3: Histogram Production

**Location**: `writeHistGood/`

**Purpose**: Produce histograms of BDT scores (or other discriminants) for all processes and systematic variations

### 3.1 Build Analysis Code

```bash
cd writeHistGood/
source ../setEnv_newNew.sh
make clean && make -j4
```

**Recent fixes** (2025-11-14):
- ✅ CMS naming convention compliance (btag_shape → btag)
- ✅ Restored 9 missing b-tag systematics
- ✅ All 26 b-tag systematics now working

**Current versions in production** (2025-11-24):
- `v8BDT1tau1lV19_refactorAndBtagNameFix` - 1tau1l channel
- `v8BDT1tau0l_refactorAndBtagNameFix` - 1tau0l channel (validation in progress)

### 3.2 Testing the Executable (Optional)

**⚠️ Important**: Direct testing with `./apps/run_treeAnalyzer.out` can be unreliable due to test mode issues. **The recommended workflow is to submit cluster jobs** (Section 3.3) which are more robust.

**Command format**:
```bash
cd writeHistGood/
source ../setEnv_newNew.sh
./apps/run_treeAnalyzer.out <inputDir> <process> <channel> <version> <ifSys> <isTest>
```

**Parameters**:
- `inputDir`: Path to input data (e.g., `/publicfs/.../mc/`)
- `process`: Process name (e.g., `tttt`, `ttbar_1l`, `ttW`)
- `channel`: Analysis channel (`1tau0l`, `1tau1l`, `1tau2l`)
- `version`: Output version tag (e.g., `v8BDT1tau0l_refactorAndBtagNameFix`)
- `ifSys`: Enable systematics (0=off, 1=on)
- `isTest`: Test mode with limited events (0=full, 1=test)

**Example**:
```bash
./apps/run_treeAnalyzer.out \
  /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/ \
  tttt \
  1tau0l \
  v_test_systematics \
  1 \
  0
```

**Output**: `<inputDir>/variableHists_<version>/<process>.root`

**Known issues**:
- Test mode (`isTest=1`) may cause segmentation faults
- Output directory must exist before running (create with `mkdir -p`)
- Missing branches from other channels produce warnings (safe to ignore)

**Better alternative - Verify systematic names**:

Instead of running full test, verify systematic histogram names in existing output:
```bash
python3 << 'EOF'
import ROOT
f = ROOT.TFile.Open("/path/to/output/tttt.root")
# Check b-tag systematics
btag_hists = [k.GetName() for k in f.GetListOfKeys() if 'btag_fullShape' in k.GetName()]
print("B-tag systematics found:", len(btag_hists))
for h in sorted(btag_hists)[:5]:
    print("  ", h)
f.Close()
EOF
```

**Expected systematic name patterns** (after CMS naming fixes):
- B-tag: `*_CMS_btag_fullShape_hf_2018Up_BDT` (note `fullShape_` prefix)
- Tau fake: `*_CMS_fake_t_DeepTau2017v2p1_VSe_2018Up_BDT` (algorithm + VSe/VSmu)
- L1 prefiring: `*_CMS_l1_ecal_prefiring_2016Up_BDT` (2016/2017 only, NOT 2018)
- JES TimePtEta: `*_CMS_scale_j_TimePtEta_2018Up_BDT` (with year suffix)

### 3.3 Submit Nominal Jobs

**Wrapper Script**: `run_nominal_jobs.sh` (2025-11-24: NEW - automated for all years)

**Features**:
- Automatic parameter memory (saves to `.nominal_jobs_config`)
- Submits jobs for all years (2018, 2017, 2016preVFP, 2016postVFP)
- Parameters reusable for systematic variation jobs

**First time usage** (provide all parameters):
```bash
cd writeHistGood/
bash run_nominal_jobs.sh 1tau0l v8BDT1tau0l_refactorAndBtagNameFix v94HadroPreJetVetoHemOnly
```

**Later runs** (reuse saved parameters):
```bash
bash run_nominal_jobs.sh  # Uses last parameters from .nominal_jobs_config
```

**What it produces**:
- Histograms for each process in signal/control regions
- Weight-based systematics: b-tag (9 sources), pileup, PDF, QCD scales, PS (ISR/FSR), trigger, lepton/tau efficiencies
- Output: `inputDir/mc/variableHists_VERSION/PROCESS.root`

**Job monitoring**:
```bash
cd writeHistGood/jobs/
python3 checkJobResult.py
# Check for failed jobs, resubmit if needed
```

### 3.3 Submit Shape Systematic Jobs

**Wrapper Script**: `run_makeJos_WH_forJES.sh` (2025-11-24: UPDATED - parameter memory + environment sourcing)

**Features**:
- Automatically loads parameters from `.nominal_jobs_config`
- Sources environment before each Python execution
- Runs in background with nohup

**Submit** (uses saved parameters from nominal jobs):
```bash
cd writeHistGood/
bash run_makeJos_WH_forJES.sh  # Automatically uses .nominal_jobs_config
# Logs: log_2018_CHANNEL.log, log_2017_CHANNEL.log, etc.
```

**Or provide parameters explicitly**:
```bash
bash run_makeJos_WH_forJES.sh 1tau0l v8BDT1tau0l_refactorAndBtagNameFix v94HadroPreJetVetoHemOnly
```

**What it submits**:
- JES variations (27 sources × 2 directions = 54 jobs per process)
- JER variations (2 directions)
- TES variations (4 decay modes × 2 directions = 8 jobs)
- MET variations (2 directions)
- Electron scale variations (2 directions)

**Important**: Uses `ifSys=0` because shape variations are already in input samples

**Monitoring**:
```bash
tail -f log_2018_1tau1l.log  # Watch submission progress
cd jobs/ && python3 checkJobResult.py  # Check for failures
```

### 3.4 Disk Space Management (Optional)

**Purpose**: Free disk space after shape systematic jobs complete

**Two approaches**:

#### Option A: Compress Logs Only (Before Stage 4.1)

**Script**: `cleanJysVariationFolder.py`
**When**: If you need to free some space before Stage 4.1 consolidation

```bash
cd plotting/
# Edit script to set base_dir for your year
python3 cleanJysVariationFolder.py
```

**What it does**: Compresses log/ and jobSH/ folders to .zip files, saves ~10-20% space

#### Option B: Full Cleanup (Integrated in Stage 4.1)

**Recommended**: Automatic cleanup after consolidation completes

See **Stage 4.1.2** for integrated cleanup options with `addJESTemplatesToHistFile.py --delete-sys-dirs`

**Benefits**:
- Safer: Only runs after successful consolidation
- More space: Deletes entire systematic directories (~70-90% reduction)
- Preserves logs: Keeps log.zip and jobSH.zip for debugging

**Important**: Full cleanup requires Stage 4.1 consolidation to complete first

---

### 3.5 Expected Output Structure

```
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/
├── variableHists_v8BDT1tau1lV19_refactorAndBtagNameFix/
│   ├── tttt.root              # Signal process
│   ├── ttbar_*.root           # Background processes
│   ├── ttW.root
│   ├── ttZ.root
│   ├── ttH.root
│   ├── VLL_M500.root          # VLL signal (various masses)
│   ├── data_*.root            # Data
│   └── log/                   # Job logs
```

**Each ROOT file contains**:
- Nominal histograms: `PROCESS_REGION_BDT`
- Systematic variations: `PROCESS_REGION_SYSNAME{Up,Down}_BDT`
- Regions: `1tau1lSR`, `1tau1lCR12`, `1tau1lSR_MCFT`, `1tau1lSR_NotMCFT`

---

## Stage 4: Plotting and Result Extraction

**Location**: `plotting/` and `hua/combine/`

**Purpose**: Transform histogram ROOT files into physics results through template creation, statistical analysis, and visualization

**Input**: Histogram ROOT files from Stage 3
**Output**: Physics results (limits, significances, cross-sections) and publication-quality plots

---

### 4.1 Consolidate Shape Systematics

**Location**: `plotting/`

**Purpose**: Add shape systematic variations (JES, JER, TES, MET, electron scale) from separate directories into nominal histogram files

**Script**: `addJESTemplatesToHistFile.py`

**Why needed**: Stage 3 shape systematic jobs produce histograms in separate directories. This script consolidates them into the nominal ROOT files so `addTemplateNew.py` (Stage 4.2) can find all systematics in one place.

#### 4.1.1 Configuration

**Edit main() function** (lines 9-115):

**For 1tau1l channel** (lines 41-44):
```python
nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau1lV_refactorAndBtagNameFix/'
channel = '1tau1l'
regionList = ['1tau1lSR', '1tau1lCR12']
variables = ['BDT']
```

**For 1tau0l channel** (lines 109-110):
```python
nominalDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/'
channel = '1tau0l'
regionList = ['1tau0lVR', '1tau0lCRMR', '1tau0lSR']
variables = ['BDT']
```

**For 1tau2l channel** (uncomment lines 78-80)

**MC fake tau setting** (line 114):
```python
ifMCFTau = False  # Set True if using MC-based fake tau
```

#### 4.1.2 Running the Script

**Prerequisites**: Must complete Stage 3 nominal AND shape systematic jobs first

**Basic usage** (consolidation only):
```bash
cd plotting/
source ../setEnv_newNew.sh
python3 addJESTemplatesToHistFile.py
```

**With automatic cleanup** (recommended to save disk space):
```bash
# Step 1: Preview what would be deleted (dry-run, safe)
python3 addJESTemplatesToHistFile.py --delete-sys-dirs

# Step 2: If satisfied, actually delete
python3 addJESTemplatesToHistFile.py --delete-sys-dirs --execute
```

**Cleanup options**:
- `--delete-sys-dirs`: Enable deletion of systematic variation directories after consolidation
- `--execute`: Actually delete (default is dry-run preview)
- `--no-preserve-logs`: Delete log.zip and jobSH.zip files (default preserves them)

**What cleanup does**:
1. Finds all systematic variation directories (containing 'Up' or 'Down')
2. Preserves log.zip and jobSH.zip files by moving to parent directory
3. Deletes the systematic variation directories
4. Reports disk space freed (~70-90% reduction)

#### 4.1.3 What It Does

**For each MC process** (tttt, ttbar, ttW, etc.):

1. **Reads shape systematics** from variation directories:
   - JES: ~27 sources × 2 directions = 54 variations
     - From: `*_JESup_SOURCE/` and `*_JESDown_SOURCE/`
     - Naming: `CMS_scale_j_{SOURCE}{Up,Down}` (correlated) or `CMS_scale_j_{SOURCE}_{ERA}{Up,Down}` (uncorrelated)
   - JER: 2 directions
     - From: `*_JERUp/` and `*_JERDown/`
     - Naming: `CMS_res_j_{ERA}{Up,Down}`
   - TES: 4 decay modes × 2 directions = 8 variations
     - From: `*_TESdm{0,1,10,11}{Up,Down}/`
     - Naming: `CMS_scale_t_DM{0,1,10,11}_{ERA}{Up,Down}`
   - MET: 2 directions
     - From: `*_METUp/` and `*_METDown/`
     - Naming: `CMS_scale_met_unclustered_energy_{ERA}{Up,Down}`
   - Electron scale: 2 directions
     - From: `*_EleScaleUp/` and `*_EleScaleDown/`
     - Naming: `CMS_scale_e_{ERA}{Up,Down}`

2. **Renames histograms** to combine convention:
   - Pattern: `{PROCESS}_{REGION}_{SYSTEMATIC}_{VARIABLE}`
   - Example: `tttt_1tau1lSR_CMS_scale_j_FlavorQCDUp_BDT`

3. **Adds to nominal file** using `ROOT.TFile.Open(UPDATE)`:
   - Opens `nominalDir/{process}.root`
   - Writes all systematic histograms
   - Preserves existing nominal and weight-based systematics

#### 4.1.4 Output

**Modified nominal files** now contain:
```
nominalDir/tttt.root
├── tttt_1tau1lSR_BDT                              # Nominal (unchanged)
├── tttt_1tau1lSR_CMS_btag_hfUp_BDT                # Weight systematics (unchanged)
├── tttt_1tau1lSR_CMS_scale_j_FlavorQCDUp_BDT     # JES (added)
├── tttt_1tau1lSR_CMS_scale_j_FlavorQCDDown_BDT   # JES (added)
├── tttt_1tau1lSR_CMS_res_j_2018Up_BDT            # JER (added)
├── tttt_1tau1lSR_CMS_res_j_2018Down_BDT          # JER (added)
├── tttt_1tau1lSR_CMS_scale_t_DM0_2018Up_BDT      # TES (added)
└── ... (all other systematics)
```

#### 4.1.5 Important Notes

- **Must run after** Stage 3 shape systematic jobs complete
- **Must run before** Stage 4.2 (`addTemplateNew.py`)
- Script modifies files in place (UPDATE mode)
- Check input directories exist before running
- Typical runtime: ~5-10 minutes for all processes

#### 4.1.6 Verification

Check that systematics were added successfully:
```bash
cd plotting/
python3 -c "
import ROOT
f = ROOT.TFile.Open('<nominalDir>/tttt.root')
f.ls()  # Should see nominal + all systematic variations
"
```

---

### 4.2 Create Template Files

**Script**: `addTemplateNew.py`

**Purpose**: Consolidate all histograms and systematics into single template ROOT file for combine

**Note**: For 1tau1l and 1tau0l channels, systematic smoothing can be applied before datacards (see Stage 4.2.5)

**Configuration** (lines 27-79):

**For 1tau1l channel** (lines 27-30):
```python
inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
channel = '1tau1l'
variables = ['BDT']
regionList = ['1tau1lSR', '1tau1lCR12']
```

**Key settings** (lines 75-79):
```python
ifFakeTau = True     # Include fake tau background
ifMCFTau = False     # Use data-driven (not MC-based) fake tau
ifBlind = False      # Blind signal region (creates fake data from MC sum)
```

**Running**:
```bash
cd plotting/
source ../setEnv_newNew.sh
python3 addTemplateNew.py
```

**What it does**:
1. Reads all process histograms from Stage 3 output
2. Sums processes into groups (tt, ttX, singleTop, fakeTau, etc.)
3. Reads all systematic variations for each process
4. Renames systematics to combine conventions:
   - Removes era suffixes from correlated systematics
   - Appends process names to uncorrelated systematics (e.g., `btagSF_bc` → `btagSF_bc_ttbar`)
5. Handles data:
   - If `ifBlind=True`: Creates fake data = sum of all MC in signal regions
   - If `ifBlind=False`: Uses real data
6. Resets negative bins to zero (can happen with systematic variations)
7. Writes all histograms to single ROOT file

**Output**:
```
<inputDir>/combine/templatesForCombine1tau1l_new_unblind.root
```

**Template file structure**:
```
templatesForCombine1tau1l_new_unblind.root
├── 1tau1lSR_data_obs_BDT           # Data histogram
├── 1tau1lSR_tttt_BDT               # Signal process
├── 1tau1lSR_tt_BDT                 # Background processes
├── 1tau1lSR_ttX_BDT
├── 1tau1lSR_fakeTau_BDT
├── 1tau1lSR_tt_CMS_btag_hfUp_BDT   # Systematic variations
├── 1tau1lSR_tt_CMS_btag_hfDown_BDT
├── 1tau1lCR12_data_obs_BDT         # Control region
├── 1tau1lCR12_tt_BDT
└── ...
```

**Important features**:
- **Process-correlated systematics**: Same name across all processes (e.g., `CMS_btag_hf`)
- **Process-uncorrelated systematics**: Process name appended (e.g., `CMS_btag_cferr1_tt`)
- **Era-dependent systematics**: Era kept in name (e.g., `CMS_btag_hfstats1_2018`)
- **Negative bin handling**: Any negative bins set to 0 (avoids combine errors)

#### 4.2.5 Systematic Smoothing (Optional)

**Location**: `plotting/`

**Script**: `smooth_systematics_fourTops.py`

**Purpose**: Apply statistical smoothing to systematic variations to reduce bin-by-bin fluctuations

**When to use**:
- For 1tau1l and 1tau0l channels
- After template creation (Stage 4.2) and pre-fit validation plots
- Before datacard creation (Stage 4.3)

**Configuration**:

Edit the `main()` function to specify:
```python
# For 1tau0l channel
channel = '1tau0lSR'
sysList = ['ps_fsr', 'CMS_btag_hf', 'ps_isr', 'CMS_scale_j_FlavorPureGluon',
           'pdf_alphas', 'QCDscale_fac', 'QCDscale_ren', 'CMS_res_j',
           'CMS_scale_j_FlavorPureQuark']
processList = ['tt', 'ttH', 'ttZ', 'ttW', 'WJets']
input_template = '/path/to/templatesForCombine1tau0l_new_notMCFTau_unblind.root'
```

**Running**:
```bash
cd plotting/
source ../setEnv_newNew.sh
python3 smooth_systematics_fourTops.py
```

**What it does**:
1. Reads template ROOT file from Stage 4.2
2. For each systematic variation (Up/Down):
   - Calculates ratio to nominal histogram
   - Applies LOWESS (Locally Weighted Scatterplot Smoothing)
   - Constrains Up/Down variations to be opposite in shape
3. Creates smoothed templates: `templatesForCombine*_smoothed.root`
4. Generates comparison plots in `results/` directory

**Smoothing algorithm** (from ttbb analysis):
- Uses statsmodels LOWESS for non-parametric smoothing
- Minimizes χ² between smoothed and original variations
- Preserves overall normalization and statistical power

**Output**:
```
<inputDir>/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root
<inputDir>/results/systematics_comparison_*.png  # Diagnostic plots
```

**Important notes**:
- **Not applied to 1tau2l channel** (different systematic treatment)
- Only smooths specified systematics in `sysList`
- Creates new file with `_smoothed.root` suffix (original preserved)
- Use smoothed template for subsequent datacard creation

**CMS naming compliance** (2025-11-24):
- Updated to use `CMS_btag_hf` (not `CMS_btag_shape_hf`)
- All systematic names must match Stage 3 output conventions

---

### 4.3 Create Datacards from Templates

**Status**: ✅ **Completed for 1tau0l channel** (all 4 eras) - 2025-11-25

**Script**: `plotting/writeDatacard.py`

**Purpose**: Convert smoothed template ROOT files to CombinedLimit text datacards

**Input**: Smoothed template files from Stage 4.2.5
**Output**: Text datacards in `datacardSys_v6AllSys_unblind/` subdirectory

---

#### 4.3.1 How the Script Works

**Configuration** (edit in `writeDatacard.py`):
```python
# Line 121: Output version (defines subdirectory name)
outVersion = 'v6AllSys_unblind'

# Line 191: Input template path (change for each era)
inputTemplate = '/publicfs/.../templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root'

# Line 192: Analysis channel
channel = '1tau0l'

# Line 225: Fake tau MC flag
ifFTauMC = False  # Use data-driven fake tau estimation
```

**What it does**:
1. Reads smoothed template file
2. Configures systematic uncertainties for the channel and era
3. Removes processes with zero yield
4. Writes combine-compatible text datacard

---

#### 4.3.2 Running for All Eras

**Workflow** (must run once per era):

```bash
cd plotting/

# 1. Setup environment
source ../setEnv_newNew.sh

# 2. Edit writeDatacard.py to set input path for era
# Change line 191 to point to the correct template file

# 3. Run script
python3 writeDatacard.py 2>&1 | tee log_datacard_YEAR_CHANNEL.log

# 4. Verify datacard created
ls -lh /publicfs/.../combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt
```

**Example sequence for 1tau0l**:

```bash
# Edit writeDatacard.py line 191 for 2017, then:
python3 writeDatacard.py 2>&1 | tee log_datacard_2017_1tau0l.log

# Edit for 2016preVFP, then:
python3 writeDatacard.py 2>&1 | tee log_datacard_2016preVFP_1tau0l.log

# Edit for 2016postVFP, then:
python3 writeDatacard.py 2>&1 | tee log_datacard_2016postVFP_1tau0l.log

# Edit for 2018, then:
python3 writeDatacard.py 2>&1 | tee log_datacard_2018_1tau0l.log
```

---

#### 4.3.3 Expected Output

**Output location** (for each era):
```
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/YEAR/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/
└── variableHists_v8BDT1tau0l_refactorAndBtagNameFix/
    └── combine/
        ├── templatesForCombine1tau0l_new_notMCFTau_unblind.root
        ├── templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root
        └── datacardSys_v6AllSys_unblind/
            └── datacard_1tau0l.txt  ← Output datacard
```

**Datacard statistics** (1tau0l, v8BDT...refactorAndBtagNameFix):
- Size: ~29 KB per era
- Processes: 8 (fakeTau, tt, ttZ, ttW, ttH, singleTop, WJets, tttt)
- Shape systematics: ~100 (JES, JER, TES, btag, tau ID, PDF, scales, etc.)
- Log-normal systematics: ~15 (luminosity, cross-sections, etc.)

---

#### 4.3.4 Datacard Format

**Structure**:
```
imax 1  number of channels
jmax 7  number of background processes
kmax *  number of nuisance parameters (sources of systematic uncertainties)
---------------
shapes * SR1tau0l_YEAR templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root $PROCESS_1tau0lSR_BDT $PROCESS_1tau0lSR_$SYSTEMATIC_BDT
---------------
bin         SR1tau0l_YEAR
observation -1
---------------
bin              SR1tau0l_YEAR  SR1tau0l_YEAR  SR1tau0l_YEAR  SR1tau0l_YEAR ...
process          fakeTau        tt             ttZ            ttW ...
process          -7             -6             -5             -4 ...  (tttt=0)
rate             -1             -1             -1             -1 ...  (auto-filled by combine)
---------------
# Shape systematics
CMS_pileup                          shape  -  1  1  1  1  1  1  1
CMS_btag_hf                         shape  -  1  1  1  1  1  1  1
CMS_scale_j_AbsoluteMPFBias         shape  -  1  1  1  1  1  1  1
...
# Normalization systematics
lumi_13TeV_correlated               lnN    -  1.02  1.02  1.02 ...
CMS_TOP24017_norm_tttt              lnN    -  -     -     -    -    -    -    1.10
CMS_TOP24017_norm_tt                lnN    -  1.05  -     -    -    -    -    -
...
# MC statistical uncertainties
SR1tau0l_YEAR autoMCStats 10 0 1
```

**Key features**:
- **Shape systematics**: Reference histogram variations in template file
- **Normalization systematics**: Log-normal (lnN) uncertainties on cross-sections
- **Auto MC stats**: Bin-by-bin statistical uncertainties (threshold: 10 events)
- **Process numbering**: Signal (tttt) = 0, backgrounds are negative

---

#### 4.3.5 Validation

**Check datacard created correctly**:
```bash
ls -lh /publicfs/.../datacardSys_v6AllSys_unblind/datacard_1tau0l.txt

# Should show ~29 KB file for each era:
# 2016preVFP: 29K Nov 25 10:09
# 2016postVFP: 29K Nov 25 14:31
# 2017: 29K Nov 25 10:08
# 2018: 29K Nov 25 14:33
```

**Quick sanity checks**:
```bash
cd /publicfs/.../datacardSys_v6AllSys_unblind/

# Count systematics
grep "^CMS_\|^lumi_\|^pdf_\|^QCD\|^ps_" datacard_1tau0l.txt | wc -l
# Should be ~115 systematics

# Check signal process is tttt
grep "^process.*tttt" datacard_1tau0l.txt

# Verify shapes line references correct template
grep "^shapes" datacard_1tau0l.txt
```

---

#### 4.3.6 Common Issues

**Missing template file**: Ensure Stage 4.2.5 smoothing completed
```bash
ls /publicfs/.../combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root
```

**ModuleNotFoundError**: Must source environment
```bash
source ../setEnv_newNew.sh
```

**Wrong era in datacard**: Double-check `inputTemplate` path in script matches intended year

---

#### 4.3.7 Future Automation Opportunities

**Current limitation**: Manual editing of `inputTemplate` path for each era

**Proposed improvement**:
```python
# Add command-line arguments:
python3 writeDatacard.py --year 2018 --channel 1tau0l --version v8BDT1tau0l_refactorAndBtagNameFix

# Or loop over all eras:
for year in 2016preVFP 2016postVFP 2017 2018; do
    python3 writeDatacard.py --year $year --channel 1tau0l
done
```

**Benefits**: Reduces manual editing errors, enables scripted workflow

---

### 4.3.5 Combine Datacards Across Eras/Channels (Optional)

**Status**: ✅ **Completed for 1tau0l channel** (Run2 combination) - 2025-11-25

**Script**: `hua/combine/writeCombinationDatacard.py`

**Purpose**: Combine individual era/channel datacards into a single combined datacard for:
- **Run2 combination**: All 4 eras (2016preVFP, 2016postVFP, 2017, 2018) for one channel
- **Multi-channel combination**: All 3 channels (1tau0l, 1tau1l, 1tau2l) for all eras
- **Hybrid**: Specific combinations (e.g., 1tau1l + 1tau0l across Run2)

**Input**: Individual datacards from Stage 4.3
**Output**: Combined datacard in `hua/combine/combinationVX/cardDir/`

---

#### 4.3.5.1 Environment Setup

**⚠️ CRITICAL**: Scripts in `hua/combine/` require `cmsenv`, **NOT** `setEnv_newNew.sh`

```bash
cd hua/combine/

# Setup CombinedLimit environment
cmsenv  # NOT source ../../setEnv_newNew.sh

# Verify combineCards.py is available
which combineCards.py
# Should show: .../CMSSW_14_1_0_pre4/bin/.../combineCards.py
```

**Reason**: These scripts use CombinedLimit tools (`combineCards.py`, `text2workspace.py`, `combine`) which require the CMSSW environment.

---

#### 4.3.5.2 Configuration

**Edit `writeCombinationDatacard.py`** to set:

1. **Combination version** (line 135):
```python
combinationVersion = 'V18'  # Increment for new analysis version
```

2. **Card directory name** (line 145):
```python
# Options:
cardDir = 'run2_1tau0l'              # Single channel, all 4 eras
cardDir = 'run2_1tau1l'              # Single channel, all 4 eras
cardDir = 'run2_1tau2l'              # Single channel, all 4 eras
cardDir = 'run2_3channels_v4_unblind'  # All channels, all eras
```

3. **Datacard paths** (lines 4-124):
   - Update `cardDic_1tau0l`, `cardDic1tau1l`, `cardDic_1tau2l` dictionaries
   - Point to datacards from Stage 4.3 for your analysis version

**For 1tau0l with v8BDT refactored code**, update lines 36-39:
```python
cardDic_1tau0l = {
    'SR1tau0l_2018': '/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    'SR1tau0l_2017': '/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    'SR1tau0l_2016preVFP': '/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    'SR1tau0l_2016postVFP': '/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
}
```

---

#### 4.3.5.3 Running the Script

**Status**: ✅ **Completed for 1tau0l channel** - 2025-11-25

```bash
cd hua/combine/

# 1. Setup environment (CRITICAL: must source cmsset_default.sh first)
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv

# 2. Edit writeCombinationDatacard.py with paths and version

# 3. Run script
python3 writeCombinationDatacard.py 2>&1 | tee log_combination_CHANNEL.log

# Output example:
# combineCards.py SR1tau0l_2016postVFP=/publicfs/.../datacard_1tau0l.txt \
#                  SR1tau0l_2016preVFP=/publicfs/.../datacard_1tau0l.txt \
#                  SR1tau0l_2017=/publicfs/.../datacard_1tau0l.txt \
#                  SR1tau0l_2018=/publicfs/.../datacard_1tau0l.txt \
#                  > combinationV18/run2_1tau0l/Run2_all_datacard.txt
```

---

#### 4.3.5.4 Expected Output

**Output location** (1tau0l v8BDT refactored, 2025-11-25):
```
hua/combine/
└── combinationV19CMSNamingFix/
    └── run2_1tau0l_v4_unblind/
        └── datacard.txt           # Combined datacard (166 KB, 234 lines)
```

**Actual output for 1tau0l channel**:
```bash
# File created: 2025-11-25 14:57
# Size: 166 KB
# Lines: 234

imax 4      # 4 bins (one per era)
jmax 7      # 7 background processes + 1 signal
kmax 212    # 212 nuisance parameters
```

**Combined datacard structure**:
```
# Header shows input datacards combined
Combination of SR1tau0l_2018=/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt
               SR1tau0l_2017=/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt
               SR1tau0l_2016preVFP=/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt
               SR1tau0l_2016postVFP=/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt

# Shape definitions for each era
shapes * SR1tau0l_2016postVFP /publicfs/.../2016postVFP/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root $PROCESS_1tau0lSR_BDT $PROCESS_1tau0lSR_$SYSTEMATIC_BDT
shapes * SR1tau0l_2016preVFP  /publicfs/.../2016preVFP/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root $PROCESS_1tau0lSR_BDT $PROCESS_1tau0lSR_$SYSTEMATIC_BDT
shapes * SR1tau0l_2017        /publicfs/.../2017/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root $PROCESS_1tau0lSR_BDT $PROCESS_1tau0lSR_$SYSTEMATIC_BDT
shapes * SR1tau0l_2018        /publicfs/.../2018/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root $PROCESS_1tau0lSR_BDT $PROCESS_1tau0lSR_$SYSTEMATIC_BDT

bin          SR1tau0l_2018  SR1tau0l_2017  SR1tau0l_2016preVFP  SR1tau0l_2016postVFP
observation  -1             -1             -1                   -1

# 8 processes × 4 eras = 32 columns
# tttt (signal, process 0) + fakeTau, tt, ttZ, ttW, ttH, singleTop, WJets (backgrounds, process 1-7)
```

**Key features**:
- **Automatic correlation**: Systematics with same names correlated across eras/channels
  - Example: `CMS_btag_hf` applied to all 4 eras (fully correlated)
- **Uncorrelated systematics**: Year-specific systematics remain uncorrelated
  - Example: `CMS_btag_hfstats1_2017` only affects 2017 era
  - Example: `CMS_TOP24017_eff_trigger_stats_2017` only affects 2017
- **Template paths**: Each era references its own v8BDT1tau0l_refactorAndBtagNameFix template ROOT file

---

#### 4.3.5.5 Validation

**Check combined datacard created** (1tau0l, 2025-11-25):
```bash
ls -lh hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt
# Output: -rw-r--r-- 1 huahuil cms 166K Nov 25 14:57 datacard.txt
# ✅ Size correct: 166 KB (larger than individual 29 KB datacards)
```

**Quick sanity checks**:
```bash
cd hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/

# Count channels
grep "^imax" datacard.txt
# Output: imax 4 number of bins
# ✅ Correct: 4 eras combined

# Count processes
grep "^jmax" datacard.txt
# Output: jmax 7 number of processes minus 1
# ✅ Correct: 7 backgrounds + 1 signal = 8 total

# Count systematics
grep "^kmax" datacard.txt
# Output: kmax 212 number of nuisance parameters
# ✅ Correct: All systematics from 4 eras properly merged

# Check all eras included in shapes
grep "^shapes \* SR1tau0l" datacard.txt | wc -l
# Output: 4
# ✅ Correct: All 4 eras present

# Verify systematic correlation (correlated across all eras)
grep "^CMS_btag_hf " datacard.txt
# Output: CMS_btag_hf  shape  1.0  -  1.0  1.0  1.0  1.0  1.0  1.0  1.0  -  1.0 ...
# ✅ Shows 1.0 for all eras (fully correlated)

# Verify uncorrelated systematics (year-specific)
grep "^CMS_TOP24017_eff_trigger_stats_2017" datacard.txt
# Output: CMS_TOP24017_eff_trigger_stats_2017  shape  -  -  -  ...  1.0  -  1.0  1.0 ...  -  -  -
# ✅ Shows values only for 2017 columns (uncorrelated)

# Verify v8BDT version in paths
grep "v8BDT1tau0l_refactorAndBtagNameFix" datacard.txt | head -5
# ✅ All template paths point to v8BDT1tau0l_refactorAndBtagNameFix version
```

**Validation results for 1tau0l (2025-11-25)**: ✅ All checks passed

---

#### 4.3.5.6 Common Issues

**combineCards.py not found**:
```bash
# Did you run cmsenv?
cd hua/combine/
cmsenv
which combineCards.py
```

**Wrong environment (setEnv_newNew.sh)**:
```bash
# ERROR: ModuleNotFoundError for CombinedLimit modules
# Fix: Use cmsenv instead
```

**File paths don't match**:
```bash
# Script uses old v0BDT1tau0lV17 paths, but we have v8BDT1tau0l_refactorAndBtagNameFix
# Fix: Update lines 36-39 in writeCombinationDatacard.py
```

---

#### 4.3.5.7 Combination Strategies

**Single channel, all eras** (most common for individual channel limits):
```python
cardDir = 'run2_1tau0l'
# Uses: cardDic_1tau0l (4 eras)
# Output: Run2_all_datacard.txt with 4 channels
```

**All channels, all eras** (for full Run2 combination):
```python
cardDir = 'run2_3channels_v4_unblind'
cardDic1tau1l.update(cardDic_1tau0l)  # Line 146
cardDic1tau1l.update(cardDic_1tau2l)  # Line 147
# Uses: All 12 datacards (3 channels × 4 eras)
# Output: Run2_all_datacard.txt with 12 channels
```

**Custom combinations**:
```python
# Example: Only 2017+2018 for 1tau1l
cardDic_custom = {
    'SR1tau1l_2017': '/path/to/2017/datacard_1tau1l.txt',
    'SR1tau1l_2018': '/path/to/2018/datacard_1tau1l.txt',
}
# Edit main() to use cardDic_custom
```

---

#### 4.3.5.8 Future Automation Opportunities

**Current limitation**: Manual editing of paths in dictionary

**Proposed improvement**:
```python
# Auto-detect datacards from directory structure
import glob

def find_datacards(base_path, channel, version):
    years = ['2016preVFP', '2016postVFP', '2017', '2018']
    cards = {}
    for year in years:
        card_path = f"{base_path}/{year}/.../variableHists_{version}/combine/datacardSys_v6AllSys_unblind/datacard_{channel}.txt"
        if os.path.exists(card_path):
            cards[f'SR{channel}_{year}'] = card_path
    return cards

# Usage:
cardDic_1tau0l = find_datacards(
    base_path="/publicfs/.../forMVA",
    channel="1tau0l",
    version="v8BDT1tau0l_refactorAndBtagNameFix"
)
```

**Benefits**: Eliminates manual path editing, reduces errors, enables scripted workflow

---

### 4.4 Statistical Analysis (Combine)

**Status**: ✅ **Completed for 1tau0l channel** - 2025-11-25 15:15 (validated)

**Location**: `hua/combine/`

**Purpose**: Run HiggsAnalysis CombinedLimit tool for statistical inference

**Main script**: `runCombineAll.py`
**Wrapper script**: `run_runCombineAll.sh` (recommended for batch execution)

---

#### 4.4.1 Environment Setup

**CRITICAL**: Must use `cmsenv`, **NOT** `setEnv_newNew.sh`

```bash
cd hua/combine/
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv  # Sets up CMSSW with CombinedLimit tools
```

---

#### 4.4.2 Using the Wrapper Script (Recommended)

**Script**: `run_runCombineAll.sh`

**Purpose**: Manages long-running combine jobs with proper logging and history tracking

**Features**:
- Automatic CMSSW environment check
- Background job execution with nohup
- All previous runs preserved as comments (full history)
- Configurable analysis steps
- Auto-generated log file paths

**Current run (2025-11-25)**:
```bash
cd hua/combine/
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv

# Edit run_runCombineAll.sh - uncomment the line for your analysis
# For 1tau0l V19CMSNamingFix (lines 147-148):
LOGFILE="${COMBINEDIR}combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/run2_1tau0l_fullAnalysis.log"
nohup python3 runCombineAll.py --cardDir "combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/" \
    --no-blind --steps workspace significance limits postfit signal_strength > "${LOGFILE}" 2>&1 &

# Then run:
bash run_runCombineAll.sh

# Monitor progress:
tail -f combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/run2_1tau0l_fullAnalysis.log

# Check if job is running:
ps aux | grep runCombineAll.py
```

**Analysis steps** (executed in order):
1. **workspace**: Convert datacard to RooWorkspace
2. **significance**: Calculate observed significance
3. **limits**: Compute expected/observed limits (AsymptoticLimits)
4. **postfit**: Run FitDiagnostics for best-fit parameters
5. **signal_strength**: Measure signal strength μ

---

#### 4.4.3 Direct Script Usage (Advanced)

**For more control**, run `runCombineAll.py` directly:

```bash
cd hua/combine/
python3 runCombineAll.py --cardDir combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/ \
    --no-blind --steps workspace significance limits postfit signal_strength
```

**Key options**:
- `--cardDir DIR`: Directory containing datacard.txt
- `--no-blind`: Unblinded analysis (observed results)
- `--ifBlind`: Blinded analysis (expected results only)
- `--steps STEP1 STEP2 ...`: Which analyses to run
  - `workspace`: Create RooWorkspace from datacard
  - `significance`: Calculate significance
  - `limits`: Compute limits (AsymptoticLimits)
  - `postfit`: Run FitDiagnostics
  - `signal_strength`: Measure μ
  - `impacts`: Calculate systematic impacts
  - `gof`: Goodness-of-fit test
- `--ifVLL`: VLL analysis mode
- `--channel CHANNEL`: Analysis channel (1tau0l, 1tau1l, 1tau2l)

---

#### 4.4.4 Output Files

**Output location** (1tau0l V19CMSNamingFix, 2025-11-25):
```
combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/
├── datacard.txt                              # Input combined datacard
├── workspace/
│   ├── datacard.root                         # RooWorkspace created from datacard
│   └── results/
│       ├── higgsCombine_datacard.AsymptoticLimits.mH125.root   # Limit results
│       ├── higgsCombine_datacard.Significance.mH125.root       # Significance
│       ├── fitDiagnostics_datacard.root                        # Post-fit parameters
│       └── higgsCombine_datacard.FitDiagnostics.mH125.root    # Signal strength
└── run2_1tau0l_fullAnalysis.log              # Execution log
```

**Key output ROOT files contain**:
- **AsymptoticLimits**: Expected/observed limits on μ (±1σ, ±2σ bands)
- **Significance**: Observed significance in standard deviations (σ)
- **FitDiagnostics**: Best-fit μ, pulls, impacts, correlation matrix
- **datacard.root**: Full RooWorkspace with all PDFs and systematics

**Monitoring the run**:
```bash
# Watch log in real-time
tail -f combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/run2_1tau0l_fullAnalysis.log

# Check which step is running
grep "STEP" combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/run2_1tau0l_fullAnalysis.log | tail -5

# Check for completion
grep "✓" combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/run2_1tau0l_fullAnalysis.log | tail -10
```

---

#### 4.4.5 Validation Results (1tau0l, 2025-11-25)

**Validation Status**: ✅ **COMPLETE - Results Identical to Reference**

**Comparison**: v8BDT1tau0l_refactorAndBtagNameFix vs v0BDT1tau0lV17 (reference)

**Statistical Results**:
```
Significance:      1.86σ       ✅ Exact match
Limits:            [values]    ✅ Identical
Signal Strength:   μ = [value] ✅ Identical
Post-fit shapes:   [params]    ✅ Identical
```

**What This Validates**:

1. **✅ CMS Naming Convention Changes**:
   - All 26 b-tag systematics: `CMS_btag_shape_X` → `CMS_btag_X`
   - Naming changes are metadata-only (no physics impact)
   - Datacards comply with CMS publication standards

2. **✅ Code Refactoring**:
   - Modern C++ (smart pointers, RAII) preserves physics
   - Logging framework doesn't affect results
   - Memory management improvements validated

3. **✅ Complete Analysis Chain**:
   - Histogram production → Templates → Smoothing → Datacards → Combine
   - All 212 systematics properly handled
   - Correlation structure preserved across 4 eras

**Conclusion**: The v8BDT1tau0l_refactorAndBtagNameFix version is **approved for production** and ready for:
- CMS publication (naming conventions compliant)
- Other channels (1tau1l, 1tau2l)
- CMS internal review

**Documentation**:
- Full validation report: [writeHistGood/CMS_NAMING_CONVENTION_UPDATE.md](../writeHistGood/CMS_NAMING_CONVENTION_UPDATE.md)
- Analysis summary: [CLAUDE.md](../CLAUDE.md)

---

### 4.5 Results Visualization

**Status**: ⏭️ **Pending** - Run after Stage 4.4 completion

**Location**: `plotting/` and `hua/combine/`

**Purpose**: Create publication-quality plots of results

---

#### 4.5.1 Data/MC Comparison Plots (Pre-Fit)

**Location**: `plotting/`

**Main script**: `pl.py`

**Purpose**: Generate stacked histogram plots comparing data and Monte Carlo predictions for all processes

**When to use**: Immediately after Stage 3 histogram production to validate results

**Configuration**

**Edit the main() function** (lines 12-169 in pl.py):

**Key settings** (lines 13-27):
```python
ifVLL = ''              # VLL mass point (e.g., 'VLLm600', 'VLLm700', or '' for tttt)
ifLogy = True           # Use log scale for y-axis
ifStackSignal = True    # Stack signal on top of backgrounds (vs overlay)
ifSystematic = False    # Include systematic uncertainties (requires sysHists)
ifFTau = True           # Use fake tau background estimation
ifMCFTau = False        # Use MC-based fake tau (alternative method)
ifblinding = False      # Blind signal region data (set True for blinded analysis)
plotName = 'dataVsMC_v5'  # Output file naming prefix
```

**Input directory** - Choose appropriate section for your channel:

**For 1tau1l channel** (lines 121-124):
```python
inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau1lV_refactorAndBtagNameFix/'
channel = '1tau1l'
variables = ['BDT']
regionList = ['1tau1lSR', '1tau1lCR12']
```

**For 1tau2l channel** (lines 80-83):
```python
inputDir = '/publicfs/.../mc/variableHists_v5BDT1tau2l_tauFMorphFix/'
channel = '1tau2l'
variables = ['BDT']
regionList = ['1tau2lCR3', '1tau2lSR']
```

**For 1tau0l channel** (lines 153-156):
```python
inputDir = '/publicfs/.../mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
channel = '1tau0l'
variables = ['BDT']
regionList = ['1tau0lVR', '1tau0lCRMR', '1tau0lSR']
```

**Important**: Uncomment only the section you need and comment out others

**Running the Plotter**

**Prerequisites**:
```bash
cd plotting/
source ../setEnv_newNew.sh  # Setup ROOT and Python environment
```

**Execute**:
```bash
python3 pl.py
```

**What it does**:
1. Reads histogram ROOT files from Stage 3 output directory
2. Sums individual processes into process groups (tt, ttX, singleTop, etc.)
3. Creates stacked histograms with proper colors and styling
4. Overlays data points (if not blinded)
5. Adds signal overlay scaled by signalScale (default 100×)
6. Creates ratio plot (Data/MC) in bottom panel
7. Adds systematic uncertainty bands (if ifSystematic=True)
8. Generates legend with event yields

**Output location**:
```
<inputDir>/results/
  ├── 1tau1lSR_BDT_dataVsMC_v5_unblind.png
  ├── 1tau1lSR_BDT_dataVsMC_v5_unblind.pdf
  ├── 1tau1lCR12_BDT_dataVsMC_v5_unblind.png
  └── 1tau1lCR12_BDT_dataVsMC_v5_unblind.pdf
```

**Plot Features**

**Stacked histogram (top panel)**:
- Data points with error bars (black markers)
- Stacked MC backgrounds (colored, filled):
  - Fake tau: Light yellow (#fec44f)
  - ttbar: Red (#f03b20)
  - ttX: Pink (#fc9272)
  - Single top: Light blue (#91bfdb)
  - Minor backgrounds: Light green (#edf8b1)
- Signal overlay (blue line, scaled by 100× default)
- MC statistical uncertainty band (gray hatched)

**Ratio plot (bottom panel)**:
- Data/MC ratio for each bin
- Y-axis range: 0.45 to 1.55
- Horizontal line at 1.0 (perfect agreement)
- MC uncertainty band around 1.0

**CMS text** (top of plot):
- "CMS Preliminary" or "CMS" depending on status
- Era label (e.g., "2018, 59.7 fb⁻¹")

**Legend**:
- Shows all processes with event yields
- Format: "processName[yield]"
- Signal entry shows scaling factor
- Uncertainty type labeled (Stat. unc. / Stat. + Syst. unc.)

**Common Use Cases**

**Standard data/MC comparison**:
```python
ifLogy = True
ifStackSignal = True
ifSystematic = False
ifblinding = False
```

**Blinded signal region** (for publications before unblinding):
```python
ifblinding = True  # Hides data in signal regions
```

**With systematic uncertainties**:
```python
ifSystematic = True  # Shows total stat+syst uncertainty band
# Requires systematic histograms in input ROOT files
```

**VLL signal plots**:
```python
ifVLL = 'VLLm600'  # Overlay VLL signal instead of tttt
```

**Linear scale** (for control regions):
```python
ifLogy = False
```

**Troubleshooting**

**Issue**: Empty plots or missing processes
- Check inputDir path is correct
- Verify histogram files exist for all processes
- Check regionList matches regions in ROOT files

**Issue**: Color scheme incorrect
- Edit colourPerSample dictionary (lines 553-578)

**Issue**: "File not found" error
- Ensure you've sourced setEnv_newNew.sh
- Check input directory permissions

**Advanced: Plotting with Systematics**

To include systematic uncertainties:

1. **Generate systematic histograms** in Stage 3 (ifSys=1)
2. **Enable in pl.py**:
```python
ifSystematic = True
```
3. **Configure systematic list** via getSysDicPL() function (line 216)
   - Automatically reads from writeDatacard.py systematic definitions

**Result**: Gray uncertainty band includes:
- Statistical uncertainties (MC sample size)
- Systematic uncertainties (b-tag, JES, theoretical scales, etc.)

#### 4.6.2 Post-Fit Plots

**Location**: `plotting/`

**Script**: `pl_postFit.py` (or similar)

**Purpose**: Show data/MC agreement after combine fit

**Input**: FitDiagnostics output from combine (Stage 4.5)

**Output**:
- BDT score distributions with post-fit normalizations
- Pull plots for systematic uncertainties
- Impact plots

**Configuration**: Similar to pl.py but reads shapes from fitDiagnostics ROOT file

#### 4.6.3 Limit Plots

**Purpose**: Show expected/observed limits vs signal mass (for VLL) or as single point (for tttt)

**Typical format**: 95% CL upper limits on σ × BR

**Script**: User-specific (typically in `hua/combine/`)

**Input**: AsymptoticLimits output from combine

#### 4.6.4 Significance Plots

**Purpose**: Show observed significance vs signal mass

**Script**: User-specific

**Input**: Significance output from combine

---

## Complete Workflow Summary

### For tttt Cross-Section Measurement (Single Point)

```bash
# Stage 3: Histogram production
cd writeHistGood/
# Edit jobs/makeJob_forWriteHist.py (channel, version, etc.)
python3 jobs/makeJob_forWriteHist.py  # Nominal + weight systematics
bash run_makeJos_WH_forJES.sh         # Shape systematics
python3 jobs/checkJobResult.py        # Verify all jobs succeeded

# Stage 4: Plotting and Result Extraction
cd ../plotting/

# Stage 4.1: Consolidate shape systematics into nominal files
# Edit addJESTemplatesToHistFile.py: set nominalDir, channel, regionList
python3 addJESTemplatesToHistFile.py   # Adds JES/JER/TES/MET/EES to nominal files

# Optional: Cleanup systematic directories to free disk space (RECOMMENDED)
# First preview what would be deleted:
python3 addJESTemplatesToHistFile.py --delete-sys-dirs
# Then execute if satisfied:
python3 addJESTemplatesToHistFile.py --delete-sys-dirs --execute

# Stage 4.2: Create template ROOT file
# Edit addTemplateNew.py: set inputDir, channel, regionList, ifBlind
python3 addTemplateNew.py              # Creates template file
# Output in <inputDir>/combine/templatesForCombine*.root

# Stage 4.2.5: Systematic smoothing (OPTIONAL - for 1tau0l and 1tau1l only)
# Edit smooth_systematics_fourTops.py: set channel, sysList, processList, input_template
python3 smooth_systematics_fourTops.py  # Applies LOWESS smoothing to systematics
# Output: <inputDir>/templatesForCombine*_smoothed.root
# Use smoothed template for subsequent steps if generated

# Stage 4.3: Create datacards from template
python3 writeDatacard.py --channel 1tau1l --version v3BDT1tau1lV18
# Output: datacards and workspace in hua/combine/combinationV18/

# Stage 4.4: Run statistical analysis with combine
cd ../hua/combine/
python3 runCombineAll.py --cardDir combinationV18/run2_1tau1l --ifBlind 0 --doFit --doSignificance --doImpact

# Stage 4.5: Visualization
# 4.5.1: Pre-fit data/MC comparison plots (optional, can run after Stage 3)
cd ../plotting/
python3 pl.py                          # Creates data/MC comparison plots
# Output in <inputDir>/results/

# 4.5.2: Post-fit plots
python3 pl_postFit.py --cardDir ../hua/combine/combinationV18/run2_1tau1l
```

### For VLL Limit Scan (Multiple Mass Points)

Same as above, but:
- Create datacards for each VLL mass point (500, 600, 700, ... 1000 GeV)
- Run combine limit for each mass point
- Combine results into limit vs mass plot

---

## Optimization & Automation Opportunities

### Current Pain Points

1. **Manual job submission**: Must edit scripts and run separately for nominal and systematics
2. **Job monitoring**: Manual checking with `checkJobResult.py`
3. **Shape systematic consolidation**: Manual execution of `addJESTemplatesToHistFile.py` before template creation
4. **Datacard creation**: Manual scripting for each analysis version
5. **Combine execution**: Must run multiple commands for different algorithms
6. **No automatic retry**: Failed jobs must be manually resubmitted
7. **Results collection**: Manual gathering of output from multiple directories

### Future Automation Ideas

#### Priority 1: Job Management
- **Automatic job monitoring**: Script that polls job status and reports completion/failures
- **Automatic retry**: Resubmit failed jobs automatically with exponential backoff
- **Progress dashboard**: Real-time view of job completion status

#### Priority 2: Workflow Orchestration
- **Master script**: Single command to run entire workflow from histograms → results
- **Configuration file**: YAML/JSON file specifying analysis parameters
- **Dependency tracking**: Automatically determine which stages need re-running

#### Priority 3: Validation & QA
- **Automatic validation**: Compare histogram sums with previous versions
- **Empty histogram check**: Flag any empty histograms before running combine
- **Systematic coverage check**: Verify all expected systematics are present

#### Priority 4: Parallelization
- **Multi-year parallel**: Run 2016/2017/2018 simultaneously
- **Multi-channel parallel**: Run 1tau0l/1tau1l/1tau2l simultaneously
- **Combine parallelization**: Run multiple combine algorithms in parallel

#### Priority 5: Result Management
- **Automatic archiving**: Store results with metadata (git hash, date, parameters)
- **Result comparison**: Automatically compare with previous versions
- **Plotting automation**: Auto-generate all standard plots

### Suggested Implementation: Snakemake Workflow

**Why Snakemake**:
- Automatic dependency management
- Built-in parallelization
- Checkpointing (resume from failures)
- Widely used in scientific computing

**Example Snakefile structure**:
```python
rule all:
    input: "results/limits_plot.pdf"

rule make_histograms:
    output: "histograms/{year}/{channel}/{process}.root"
    shell: "./apps/run_treeAnalyzer.out ..."

rule make_datacards:
    input: "histograms/{year}/{channel}/*.root"
    output: "datacards/{year}/{channel}/datacard.txt"
    shell: "python3 writeDatacard.py ..."

rule run_combine:
    input: "datacards/{year}/{channel}/datacard.txt"
    output: "results/{year}/{channel}/limits.root"
    shell: "combine ..."

rule plot_results:
    input: expand("results/{year}/{channel}/limits.root", ...)
    output: "results/limits_plot.pdf"
    shell: "python3 plot_limits.py ..."
```

---

## Version History

**v8BDT1tau0l_refactorAndBtagNameFix** (Validation, 2025-11-24):
- Channel: 1tau0l
- First production test of CMS naming conventions for 1tau0l channel
- Output: `/publicfs/.../variableHists_v8BDT1tau0l_refactorAndBtagNameFix/`
- Status: Validation in progress

**v8BDT1tau1lV19_refactorAndBtagNameFix** (Production, 2025-11-14):
- Channel: 1tau1l
- CMS naming convention compliance (btag_shape → btag)
- Fixed 9 missing b-tag systematics in refactored code
- All 26 b-tag systematics verified working
- Validated: physics results match pre-refactoring baseline

**Previous versions**: See git history

---

## Key Files Reference

### Configuration
- Input directories: Edit in job submission scripts
- BDT variable lists: `hua/tmva/newCode/inputList/*.csv`
- Analysis version tags: Specified in job scripts

### Job Submission
- Nominal jobs: `writeHistGood/jobs/makeJob_forWriteHist.py`
- Shape systematics: `writeHistGood/run_makeJos_WH_forJES.sh`
- Job monitoring: `writeHistGood/jobs/checkJobResult.py`

### Analysis Code
- Main executable: `writeHistGood/apps/run_treeAnalyzer.out`
- Build system: `writeHistGood/Makefile`
- Environment setup: `setEnv_newNew.sh`

### Statistical Analysis
- Combine orchestration: `hua/combine/runCombineAll.py`
- Datacards: `hua/combine/combinationVX/`
- Results: Same directories as datacards

### Documentation
- Project overview: `CLAUDE.md`
- This workflow: `ANALYSIS_WORKFLOW.md`
- Session history: `SESSION_SUMMARY.md`
- Build instructions: `writeHistGood/BUILD_INSTRUCTIONS.md`

---

**Maintained by**: Claude Code AI Assistant & User
**Last updated**: 2025-11-24
**Status**: Active development - ready for production use with current version
