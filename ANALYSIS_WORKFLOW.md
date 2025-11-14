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

## Stage 4: Datacard Creation

**Location**: `plotting/` (typically, or using custom scripts)

**Purpose**: Convert ROOT histograms to HiggsAnalysis CombinedLimit datacards

**Input**: Histogram ROOT files from Stage 3
**Output**: Text datacards + workspace ROOT files for combine

**Typical script**: `writeDatacard.py` (user may have custom version)

**Datacard format**:
```
imax 1  # number of channels
jmax N  # number of backgrounds
kmax M  # number of systematics
---
bin          1tau1lSR
observation  123  # observed events in data
---
bin              1tau1lSR  1tau1lSR  1tau1lSR ...
process          tttt      ttbar     ttW ...
process          0         1         2 ...
rate             1.23      45.6      7.8 ...
---
# Systematics
lumi            lnN  1.025  1.025  1.025 ...
CMS_btag_hf     shape 1     1      1 ...
```

**Workspace creation**:
```bash
cd hua/combine/datacards/
text2workspace.py datacard_1tau1l.txt -o workspace_1tau1l.root
```

**Location of datacards** (example):
```
hua/combine/combinationV18/run2_1tau1l/
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

### 6.1 Post-Fit Plots

**Script**: `plotting/pl_postFit.py` (or similar)

**Purpose**: Show data/MC agreement after fit

**Output**:
- BDT score distributions with post-fit normalizations
- Pull plots for systematic uncertainties
- Impact plots

### 6.2 Limit Plots

**Purpose**: Show expected/observed limits vs signal mass (for VLL) or as single point (for tttt)

**Typical format**: 95% CL upper limits on σ × BR

### 6.3 Significance Plots

**Purpose**: Show observed significance vs signal mass

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

# Stage 4: Create datacards (user-specific script)
cd plotting/
python3 writeDatacard.py --channel 1tau1l --version v8BDT1tau1lV19

# Stage 5: Run combine
cd ../hua/combine/
python3 runCombineAll.py --cardDir combinationV18/run2_1tau1l --ifBlind 0 --doFit --doSignificance --doImpact

# Stage 6: Make plots
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
