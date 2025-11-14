# CLAUDE.md - AI Assistant Context for FourTop Analysis

## Project Overview

This is a **CMS Four-Top Quark Physics Analysis** project within the CMSSW (CMS Software) framework. The analysis searches for rare four-top quark production events and Beyond Standard Model signals (VLL - Vector-Like Leptons) using data from the CMS detector at CERN's Large Hadron Collider.

**Key Analysis Channels**:
- `1tau0l`: One hadronic tau + 0 leptons
- `1tau1l`: One hadronic tau + 1 lepton
- `1tau2l`: One hadronic tau + 2 leptons

**Primary Analysis Goals**:
- Measure four-top quark (tttt) production cross-section
- Search for Vector-Like Lepton (VLL) signals
- Use multivariate analysis (BDT/TMVA) for signal discrimination
- Perform statistical inference using HiggsAnalysis CombinedLimit tool

---

## Project Structure

```
FourTop/
├── writeHistGood/          # Main histogram production (C++/ROOT)
│   ├── apps/               # Main executables
│   ├── include/            # C++ headers
│   ├── src/                # C++ source files
│   ├── Makefile           # Build system
│   └── jobs/              # Job submission scripts
│
├── hua/
│   ├── combine/           # Statistical analysis with CombinedLimit
│   │   ├── runCombineAll.py     # Main combine orchestration script
│   │   ├── combinationVX/       # Analysis result versions
│   │   └── datacards/           # Input datacards for combine
│   └── tmva/              # Machine learning training
│
├── plotting/              # Plotting scripts (Python/ROOT)
├── objectSelectionOptimized/  # Event selection code
├── makeVariables_goodCode/    # Variable calculation
├── inputFiles/            # Input ROOT files and configurations
├── myLibrary/             # Shared C++ utilities
│
├── README.md              # User-facing documentation
├── SESSION_SUMMARY.md     # Development session notes
├── setEnv_newNew.sh       # Environment setup script
└── CLAUDE.md              # This file (AI assistant context)
```

---

## Analysis Workflow

### 1. NanoAOD Processing → Histograms
**Location**: `writeHistGood/`

**Main executable**: `apps/run_treeAnalyzer.out`

**Purpose**:
- Reads CMS NanoAOD ROOT files
- Applies object selection (jets, leptons, taus, b-tagging)
- Calculates physics variables
- Applies systematic variations
- Produces histograms for combine datacards

**Key parameters**:
```bash
./run_treeAnalyzer.out <inputDir> <process> <channel> <version> <ifSys> <isTest>
# Example:
# ./run_treeAnalyzer.out input_dir/ tttt 1tau1l v3BDT 1 0
```

**Recent refactoring**: Code recently refactored with modern C++ (smart pointers, RAII, logging framework, systematic variations manager). Validation confirmed bit-for-bit identical output.

---

### 2. Machine Learning (BDT Training)
**Location**: `hua/tmva/`

**Purpose**:
- Train Boosted Decision Trees (BDT) for signal/background discrimination
- Optimize variable selection
- Generate BDT scores applied in histogram production

**Key files**:
- `run_MVATraining.py`: Training orchestration
- `inputList/`: Variable configuration files
- `output/`: Trained models and performance plots

---

### 3. Statistical Analysis
**Location**: `hua/combine/`

**Main script**: `runCombineAll.py`

**Purpose**:
- Convert histogram templates to HiggsAnalysis CombinedLimit workspace
- Run various combine algorithms:
  - Expected/observed limits (AsymptoticLimits)
  - Signal strength measurements (FitDiagnostics)
  - Goodness-of-fit tests
  - Impact plots for systematics
  - Significance calculations

**Key features**:
- Automatic workspace detection (handles both tttt and VLL analyses)
- Permission handling for read-only directories (creates temp workspace if needed)
- Support for blinded/unblinded analysis
- Parallel toy generation for GoF tests

**Example usage**:
```bash
python3 runCombineAll.py --cardDir combinationV18/run2_1tau1l --ifBlind 0 --doLimit
```

---

### 4. Visualization
**Location**: `plotting/`

**Key scripts**:
- `plotVariables*.py`: Distribution plots
- `pl_postFit.py`: Post-fit plots from combine
- `checkTauIDEff_nanoAOD.py`: Efficiency studies

---

## Important Technical Context

### 1. Build System

**Compiler**: gcc 14.3.1
**ROOT Version**: 6.36.01
**C++ Standard**: C++20
**Dependencies**: ROOT, TBB, custom myLibrary, JSON for Modern C++

**Building writeHistGood**:
```bash
cd writeHistGood/
source ../setEnv_newNew.sh  # Sets up environment
make clean
make  # Parallel build with multiple cores
```

**Common build issues**:
- Missing TBB library: Ensure `TBBLIBS = -ltbb` in Makefile
- Environment issues: Always source `setEnv_newNew.sh` from project root

---

### 2. Environment Setup

**Primary script**: `setEnv_newNew.sh`

**What it sets up**:
- CMS software environment (`cmsenv`)
- Custom C++ library paths (`myLibrary/`)
- ROOT, Python, TBB paths
- CMSSW corrections and JSON POG integration

**Important**: Script uses location-independent path resolution:
```bash
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
```
This allows sourcing from any directory.

**Usage**:
```bash
source setEnv_newNew.sh  # Must be sourced, not executed
```

---

### 3. Job Submission (IHEP Cluster)

**Cluster**: IHEP computing cluster
**Batch system**: HTCondor via `hep_sub` command

#### Nominal Jobs

**Script**: [writeHistGood/jobs/makeJob_forWriteHist.py](writeHistGood/jobs/makeJob_forWriteHist.py)

**Purpose**: Submit jobs for nominal analysis (central value + weight-based systematics)

**Key parameters** (edit in script):
```python
inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/'
channel = '1tau1l'  # or '1tau0l', '1tau2l'
version = 'v8BDT1tau1lV19_refactorAndBtagNameFix'  # Output version tag
exe = './apps/run_treeAnalyzer.out'
ifSys = 1  # Enable weight-based systematics (b-tag, PDF, scales, etc.)
justMC = False  # Process both MC and data
```

**Usage**:
```bash
cd writeHistGood/jobs/
# Edit makeJob_forWriteHist.py with desired parameters
python3 makeJob_forWriteHist.py
# This creates and submits all jobs automatically
```

**What it does**:
- Creates job submission scripts in `variableHists_VERSION/jobSH/`
- Generates `subAllProcess.sh` with all `hep_sub` commands
- Automatically submits jobs (calls `hep_sub` for each process)
- Processes all `.root` files in input directory (tttt, ttbar, VLL, data, etc.)
- Applies weight-based systematics (b-tag, pileup, PDF, scales, parton shower)

#### Systematic Variation Jobs (Shape Systematics)

**Script**: [writeHistGood/jobs/makeJob_WH_forJES.py](writeHistGood/jobs/makeJob_WH_forJES.py)

**Purpose**: Submit jobs for shape systematic variations (JES, JER, TES, MET, electron scale)

**Key parameters** (pass via command line):
```bash
python3 makeJob_WH_forJES.py \
  --inputDirBase /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/ \
  --inVersion v94HadroPreJetVetoHemOnly_JESPt22 \
  --outVersion v1baselineHadroBtagWeightAdded \
  --channel 1tau1l \
  --version v8BDT1tau1lV19_refactorAndBtagNameFix
```

**What it submits**:
1. **JES variations**: ~27 sources (Total, FlavorQCD, TimePtEta, RelativeBal, etc.)
   - Reads from varied input samples: `*_JESup_SOURCE_*/` and `*_JESDown_SOURCE_*/`
2. **JER variations**: Up/Down
   - Input: `*_JERUp/`, `*_JERDown/`
3. **MET variations**: Up/Down
   - Input: `*_METUp/`, `*_METDown/`
4. **Electron energy scale**: Up/Down
   - Input: `*_EleScaleUp/`, `*_EleScaleDown/`
5. **Tau energy scale**: 4 decay modes (0, 1, 10, 11), Up/Down each
   - Input: `*_TESdm{0,1,10,11}{Up,Down}/`

**Important**: These jobs use `ifSys=0` because the systematic variation is already in the input NanoAOD samples (shape-changing systematics require re-running object selection).

#### Job Monitoring

**Check job status**:
```bash
cd writeHistGood/jobs/
python3 checkJobResult.py
```

**Important reminders**:
- Always check job results - jobs may silently fail
- Log files: `outputDir/log/PROCESS.log` and `PROCESS.err`
- Failed jobs need to be resubmitted individually

---

### 4. Git Branches

**Current branch**: `addVLL`
**Main branch**: `master`

**Recent commits focus on**:
- VLL analysis permission handling
- Code refactoring (writeHistGood)
- Documentation improvements
- Build system fixes

---

## Key Files for AI Understanding

### Critical Configuration Files

1. **Build & Environment**:
   - [writeHistGood/Makefile](writeHistGood/Makefile): Build system
   - [setEnv_newNew.sh](setEnv_newNew.sh): Environment configuration

2. **Analysis Code**:
   - `writeHistGood/apps/run_treeAnalyzer.C`: Main analysis loop
   - `writeHistGood/include/*.h`: Analysis headers
   - `hua/combine/runCombineAll.py`: Statistical analysis orchestration

3. **Documentation**:
   - [README.md](README.md): User guide and workflow
   - [SESSION_SUMMARY.md](SESSION_SUMMARY.md): Recent development history
   - [writeHistGood/BASH_COMMANDS_EXPLAINED.md](writeHistGood/BASH_COMMANDS_EXPLAINED.md): Command reference
   - [writeHistGood/BUILD_INSTRUCTIONS.md](writeHistGood/BUILD_INSTRUCTIONS.md): Detailed build guide

---

## Common Tasks & How to Help

### When user asks about building/compiling:
1. Check if environment is sourced (`setEnv_newNew.sh`)
2. Check Makefile for TBB and other dependencies
3. Check for compilation errors related to missing headers
4. Verify ROOT version compatibility

### When user asks about running analysis:
1. Understand which channel (`1tau0l`, `1tau1l`, `1tau2l`)
2. Check input file paths in `inputFiles/` or specified directory
3. Verify output directory exists
4. Check systematic variations flag (`ifSys`)

### When user asks about combine/statistics:
1. Check if datacards exist in specified directory
2. Verify workspace files (`.root` files in card directory)
3. Understand if analysis is VLL or tttt (different workspace naming)
4. Check for permission issues (read-only directories)
5. Reference `runCombineAll.py` helper functions

### When user asks about performance/debugging:
1. Check log files in respective directories
2. For writeHistGood: Check `AnalysisLogger` output
3. For combine: Check `combine_logger.out`
4. Consider validation tests against reference outputs

### Code modification guidelines:
1. **writeHistGood**: Recently refactored, preserve modern C++ patterns
2. **Commits**: User requests regular commits for major changes
3. **Documentation**: Update `BASH_COMMANDS_EXPLAINED.md` when using new bash patterns
4. **Testing**: Validate physics results remain unchanged after code modifications

---

## Recent Development History

### Last Session (2025-11-04)

**Major accomplishments**:
1. Fixed VLL analysis permission issues with automatic temp directory creation
2. Refactored duplicate workspace detection code in `runCombineAll.py`
3. Completed validation testing of refactored `writeHistGood` code
   - All 80,144 events processed successfully
   - Bit-for-bit identical physics results
   - All systematic variations match reference

**Active refactoring roadmap** (writeHistGood):
- Completed: Memory management, logging framework, systematic variations manager
- In progress: Validation complete, ready for next steps
- Remaining: Named constants, configuration system, modern C++ features, documentation

---

## Physics Context (Brief)

### Standard Model Process
- **tttt (four-top production)**: Very rare SM process (σ ~12 fb)
- Signature: Multiple b-jets, leptons, large missing energy
- Main backgrounds: ttbar, ttW, ttZ, ttH, fake backgrounds

### BSM Search
- **VLL (Vector-Like Leptons)**: Heavy exotic leptons predicted by BSM theories
- Tested mass points: 500-1000 GeV typically
- Couples to top quarks, gives similar signatures to tttt

### Analysis Strategy
- Use BDT to separate signal from background
- Fit BDT score distributions in signal regions
- Extract limits on signal cross-section or measure tttt rate
- Systematic uncertainties: JES, b-tagging, theoretical scales, etc.

---

## Helpful Commands Reference

### Quick Build & Run (writeHistGood)
```bash
cd writeHistGood/
source ../setEnv_newNew.sh
make clean && make
./apps/run_treeAnalyzer.out <args>
```

### Quick Combine Analysis
```bash
cd hua/combine/
python3 runCombineAll.py --cardDir <dir> --ifBlind 1 --doLimit
```

### Check Job Status
```bash
cd writeHistGood/jobs/
python3 checkJobResult.py
```

### Git Workflow
```bash
git status
git add <files>
git commit -m "descriptive message"
# Note: User prefers commits for major changes
```

---

## Special Notes for AI Assistants

### User Preferences
1. **Commits**: User wants major changes committed regularly (acknowledged 2025-11-04)
2. **Documentation**: Update `BASH_COMMANDS_EXPLAINED.md` across all sessions
3. **Code Quality**: Preserve refactored patterns, maintain backward compatibility
4. **Testing**: Validate physics output when modifying analysis code

### Code Review Priorities
- **Safety**: Watch for physics bugs (wrong sign, wrong branch, off-by-one)
- **Consistency**: Maintain naming conventions for systematics
- **Performance**: Large datasets (~millions of events), be memory-conscious
- **Reproducibility**: Physics results must be deterministic and reproducible

### Communication Style
- User is a physicist and experienced developer
- Can handle technical details and direct feedback
- Appreciates explanations of *why*, not just *how*
- Values code maintainability and long-term project health

---

## Resources

### Internal Documentation
- See `README.md` for user-level workflow
- See `SESSION_SUMMARY.md` for recent session notes
- See `writeHistGood/BUILD_INSTRUCTIONS.md` for detailed build info
- See `writeHistGood/BASH_COMMANDS_EXPLAINED.md` for command reference
- See `MCP_SETUP_GUIDE.md` for MCP servers configuration and usage

### External References
- CMS NanoAOD: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookNanoAOD
- HiggsAnalysis CombinedLimit: https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/
- ROOT Documentation: https://root.cern.ch/doc/master/
- CMSSW: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCMSSWFramework

---

## Questions to Ask When Context is Unclear

1. **Which analysis component** are you working with?
   - Histogram production (writeHistGood)?
   - Machine learning (TMVA)?
   - Statistical analysis (combine)?
   - Plotting/visualization?

2. **Which channel** are you analyzing?
   - 1tau0l, 1tau1l, or 1tau2l?

3. **Which process** are you studying?
   - tttt (four-top) signal?
   - VLL (Vector-Like Lepton) signal?
   - Background processes?

4. **What version** of the analysis?
   - Look for version strings like "v3BDT", "V18", "combinationVX"

5. **Are systematics enabled**?
   - This significantly affects runtime and output

---

*This document serves as comprehensive context for AI assistants working on the FourTop analysis project. It should be updated as the project evolves.*

*Last updated: 2025-11-13*
*Maintained by: Claude Code AI Assistant*
