# Analysis Workflow Instruction

This guide outlines the steps required to implement the analysis workflow, specifically focusing on the 1tau0l channel. It covers the process from running the tree analyzer to plotting distributions and generating templates for Combine.

## Workflow

The analysis follows these steps:

- **Initial Analysis**: `run_treeAnalyzer.out`
- **Template Generation**: `addTemplatesForCombine.py`
- **1tau0l Channel Specific**:
  - Generate fake tau background and plot distributions using `writeHist_fakeRate.C` and `plotVariables1tau0l.py`.
  - Process with `treeAnalyzer.C`, then proceed with `addTemplatesForCombine.py` and finalize with `runCombineAll.py`.

### 1tau0l fake tau
- `createFaketauTree.py`


## To-Do List

- [ ] Create a compact object class to encapsulate all objects.
- [ ] Develop a Python script for generating datacards.

## Installation Instructions

Follow these steps to set up your environment and repositories:

```bash
# Clone the necessary repositories
git clone ssh://git@gitlab.cern.ch:7999/cms-nanoAOD/jsonpog-integration.git
git clone git@github.com:huiling110/FourTop.git

# Run the environment setup script (this sets up g++, ROOT, Python, and corrections)
bash setupEnv.sh

# Change directory to FourTop
cd FourTop
```

## Execution Guide

To run the analysis, execute the following:

```bash
# Change to the objectSelection directory
cd objectSelection

# Create an output directory
mkdir output

# Compile the code
make

# Execute the analysis
./run_objectTSelectorForNanoAOD.out
# Alternatively, run using ROOT
root -b -q run_objectTSelectorForNanoAOD.C
```

## Development Tips

- Modify `Linkdef.h` and `Makefile` to use classes and functions from other `.C` source files. Avoid including `.C` source code directly; only include `.h` headers.
- Keep the `objectTSelector` class file clean by placing only member functions within it. Other functions should go to `utilityFunctions.C` for modularity and clarity.
- Recompilation is necessary only if you modify source code. Changes to `run_objectTSelectorForNanoAOD.C` do not require recompilation.

## Submitting Jobs on the IHEP Cluster

For job submission on the IHEP cluster:

```bash
# Navigate to the objectSelection directory within FourTop
cd FourTop/objectSelection

# Open and adjust the makeJob_objectTSelectorForNanoAOD.py script with your settings
python3 makeJob_objectTSelector_forSeperate.py

# Submit all jobs
. subAllJobs.sh
```

## Setting Up Combine

To set up the Combine tool:

```bash
# Navigate to the CMSSW_BASE/src directory
cd $CMSSW_BASE/src

# Clone the CombinedLimit repository
git clone git@github.com:cms-analysis/HiggsAnalysis-CombinedLimit.git HiggsAnalysis/CombinedLimit

# Navigate into the CombinedLimit directory
cd HiggsAnalysis/CombinedLimit

# Fetch and checkout the desired version
git fetch origin
git checkout v8.1.0

# Return to the CMSSW_BASE/src directory
cd $CMSSW_BASE/src

# Run the sparse checkout script and build
curl -s https://raw.githubusercontent.com/cms-analysis/CombineHarvester/master/CombineTools/scripts/sparse-checkout-https.sh | bash
scramv1  clean; scramv1 bb
```

This markdown guide provides a structured approach to conducting the analysis workflow, from setting up the environment to processing data and utilizing the Combine tool. 


## Kind reminders 
# Important to check the job results with ```checkJobResult.pu```, as jobs may fail
