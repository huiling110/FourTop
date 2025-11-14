# Complete Four-Top Analysis Workflow

**Date**: 2025-11-14
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
[4] Datacard Creation for Combine
    ↓
[5] Statistical Analysis (HiggsAnalysis CombinedLimit)
    ↓
[6] Results Visualization & Interpretation
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

### 3.2 Submit Nominal Jobs

**Script**: `jobs/makeJob_forWriteHist.py`

**Edit parameters** (lines 30-80):
```python
inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/'
channel = '1tau1l'  # or '1tau0l', '1tau2l'
version = 'v8BDT1tau1lV19_refactorAndBtagNameFix'
exe = './apps/run_treeAnalyzer.out'
ifSys = 1  # Enable weight-based systematics
justMC = False  # Process both MC and data
```

**Submit**:
```bash
cd writeHistGood/jobs/
python3 makeJob_forWriteHist.py
# Jobs submitted automatically
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

**Script**: `run_makeJos_WH_forJES.sh` (wrapper for `jobs/makeJob_WH_forJES.py`)

**Edit parameters** (lines 3-12):
```bash
INPUT_DIR_BASE="/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/"
IN_VERSION="v94HadroPreJetVetoHemOnly"
OUT_VERSION="v1baselineHadroBtagWeightAdded"
CHANNEL="1tau1l"
VERSION="v8BDT1tau1lV_refactorAndBtagNameFix"
```

**Submit**:
```bash
cd writeHistGood/
bash run_makeJos_WH_forJES.sh
# Runs in background with nohup, logs to log_2018_1tau1l.log
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

### 3.4 Expected Output Structure

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

## Stage 4: Template and Datacard Creation

**Location**: `plotting/`

**Purpose**: Create template ROOT files and convert to HiggsAnalysis CombinedLimit datacards

**Input**: Histogram ROOT files from Stage 3
**Output**: Template ROOT files → Text datacards → Workspace ROOT files

### 4.1 Create Template Files

**Script**: `addTemplateNew.py`

**Purpose**: Consolidate all histograms and systematics into single template ROOT file for combine

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

### 4.2 Create Datacards from Templates

**Script**: `writeDatacard.py` (user-specific implementation)

**Purpose**: Convert template ROOT file to text datacards

**Input**: Template ROOT file from Step 4.1
**Output**: Text datacards for combine

**Typical usage**:
```bash
cd plotting/
python3 writeDatacard.py --channel 1tau1l --version v3BDT1tau1lV18
```

**Datacard format**:
```
imax 2  # number of channels (SR + CR)
jmax N  # number of backgrounds
kmax M  # number of systematics
---
shapes * 1tau1lSR templatesForCombine1tau1l_new_unblind.root 1tau1lSR_$PROCESS_BDT
shapes * 1tau1lCR12 templatesForCombine1tau1l_new_unblind.root 1tau1lCR12_$PROCESS_BDT
---
bin          1tau1lSR  1tau1lCR12
observation  123       456
---
bin              1tau1lSR  1tau1lSR  1tau1lSR  1tau1lCR12  1tau1lCR12 ...
process          tttt      tt        ttX       tttt        tt ...
process          0         1         2         0           1 ...
rate             1.23      45.6      7.8       2.34        67.8 ...
---
# Systematics
lumi_2018        lnN  1.025  1.025  1.025  1.025  1.025 ...
CMS_btag_hf      shape 1     1      1      1      1 ...
CMS_btag_cferr1_tt  shape -    1      -      -      1 ...
```

**Key features**:
- **Shape systematics**: Use histogram shapes from template file
- **Normalization systematics**: Log-normal (lnN) uncertainties
- **Process-specific systematics**: Marked with `-` for non-applicable processes

### 4.3 Create Workspace for Combine

**Script**: HiggsAnalysis CombinedLimit tool

**Purpose**: Convert text datacard to ROOT workspace for faster combine execution

**Running**:
```bash
cd hua/combine/datacards/
text2workspace.py datacard_1tau1l.txt -o workspace_1tau1l.root
```

**Output**: `workspace_1tau1l.root` - binary workspace file used by combine

**Location of datacards** (typical):
```
hua/combine/combinationV18/run2_1tau1l/
├── datacard_1tau1l.txt
├── workspace_1tau1l.root
└── templatesForCombine1tau1l_new_unblind.root
```

---

## Stage 5: Statistical Analysis (Combine)

**Location**: `hua/combine/`

**Purpose**: Run HiggsAnalysis CombinedLimit tool for statistical inference

### 5.1 Setup Combine Tool

Combine is installed in CMSSW environment:
```bash
source ../setEnv_newNew.sh  # Sets up CMSSW with combine
```

### 5.2 Run Statistical Inference

**Main script**: `runCombineAll.py`

**Features**:
- Auto-detects tttt vs VLL analysis from workspace
- Handles read-only directories (creates temp workspace if needed)
- Supports blinded/unblinded analysis
- Runs multiple combine algorithms

**Usage**:
```bash
cd hua/combine/
python3 runCombineAll.py --cardDir combinationV18/run2_1tau1l --ifBlind 1 --doLimit
```

**Key options**:
- `--cardDir`: Directory with workspace ROOT file
- `--ifBlind`: 1=blinded (expected limits), 0=unblinded (observed limits)
- `--doLimit`: Compute expected/observed limits
- `--doSignificance`: Compute significance
- `--doFit`: Run FitDiagnostics for signal strength measurement
- `--doImpact`: Compute impact of each systematic
- `--doGoF`: Goodness-of-fit test

### 5.3 Common Combine Algorithms

#### A. Expected/Observed Limits
```bash
python3 runCombineAll.py --cardDir DIR --ifBlind 1 --doLimit
```
**Output**: Expected ±1σ, ±2σ limits on signal strength

#### B. Signal Strength Measurement
```bash
python3 runCombineAll.py --cardDir DIR --ifBlind 0 --doFit
```
**Output**: Best-fit signal strength μ with uncertainties

#### C. Significance Calculation
```bash
python3 runCombineAll.py --cardDir DIR --ifBlind 0 --doSignificance
```
**Output**: Observed significance in σ

#### D. Systematic Impact
```bash
python3 runCombineAll.py --cardDir DIR --doImpact
```
**Output**: Impact plot showing effect of each systematic on μ

#### E. Goodness-of-Fit Test
```bash
python3 runCombineAll.py --cardDir DIR --doGoF --toysFreq 100
```
**Output**: GoF test statistic and p-value

### 5.4 Output Files

Combine creates output in datacard directory:
```
combinationV18/run2_1tau1l/
├── workspace_run2_1tau1l.root         # Input workspace
├── higgsCombineTest.AsymptoticLimits.mH125.root  # Limit results
├── fitDiagnosticsTest.root            # Fit results
├── impacts.json                       # Impact results
└── combine_logger.out                 # Execution log
```

---

## Stage 6: Results Visualization

**Location**: `plotting/` and `hua/combine/`

**Purpose**: Create publication-quality plots of results

### 6.1 Data/MC Comparison Plots

**Location**: `plotting/`

**Main script**: `pl.py`

**Purpose**: Generate stacked histogram plots comparing data and Monte Carlo predictions for all processes

**When to use**: Immediately after Stage 3 histogram production to validate results

#### 6.1.1 Configuration

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

#### 6.1.2 Running the Plotter

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

#### 6.1.3 Plot Features

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

#### 6.1.4 Common Use Cases

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

#### 6.1.5 Troubleshooting

**Issue**: Empty plots or missing processes
- Check inputDir path is correct
- Verify histogram files exist for all processes
- Check regionList matches regions in ROOT files

**Issue**: Color scheme incorrect
- Edit colourPerSample dictionary (lines 553-578)

**Issue**: "File not found" error
- Ensure you've sourced setEnv_newNew.sh
- Check input directory permissions

#### 6.1.6 Advanced: Plotting with Systematics

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

### 6.2 Post-Fit Plots

**Location**: `plotting/`

**Script**: `pl_postFit.py` (or similar)

**Purpose**: Show data/MC agreement after combine fit

**Input**: FitDiagnostics output from combine (Stage 5)

**Output**:
- BDT score distributions with post-fit normalizations
- Pull plots for systematic uncertainties
- Impact plots

**Configuration**: Similar to pl.py but reads shapes from fitDiagnostics ROOT file

### 6.3 Limit Plots

**Purpose**: Show expected/observed limits vs signal mass (for VLL) or as single point (for tttt)

**Typical format**: 95% CL upper limits on σ × BR

**Script**: User-specific (typically in `hua/combine/`)

**Input**: AsymptoticLimits output from combine

### 6.4 Significance Plots

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

# Stage 3.5: Validation plots (recommended before combining)
cd ../plotting/
# Edit pl.py: set inputDir, channel, regionList
python3 pl.py                          # Creates data/MC comparison plots
# Output in <inputDir>/results/

# Stage 4: Template and datacard creation
# Step 4.1: Create template ROOT file
# Edit addTemplateNew.py: set inputDir, channel, regionList, ifBlind
python3 addTemplateNew.py              # Creates template file
# Output in <inputDir>/combine/templatesForCombine*.root

# Step 4.2: Create datacards from template
python3 writeDatacard.py --channel 1tau1l --version v3BDT1tau1lV18
# Output: datacards and workspace in hua/combine/combinationV18/

# Stage 5: Run combine
cd ../hua/combine/
python3 runCombineAll.py --cardDir combinationV18/run2_1tau1l --ifBlind 0 --doFit --doSignificance --doImpact

# Stage 6: Post-fit plots
cd ../plotting/
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
3. **Datacard creation**: Manual scripting for each analysis version
4. **Combine execution**: Must run multiple commands for different algorithms
5. **No automatic retry**: Failed jobs must be manually resubmitted
6. **Results collection**: Manual gathering of output from multiple directories

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

**v8BDT1tau1lV19_refactorAndBtagNameFix** (Current, 2025-11-14):
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
**Last updated**: 2025-11-14
**Status**: Active development - ready for production use with current version
