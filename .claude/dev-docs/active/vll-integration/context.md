# VLL Integration Context

**Last Updated**: 2025-12-03 13:55

## Key Files

### Primary Files to Modify
- `hua/combine/runCombineAll.py` - Main Combine workflow script
- `hua/combine/run_runCombineAll.sh` - Shell script for running tests

### Educational Resources
- `hua/combine/asymptotic_limits_tutorial.py` - Step-by-step CLs limit calculation tutorial

### Reference Files
- `/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/runCombineAll.py` - Reference implementation with VLL support

### Test Data
- `hua/combine/combinationV10/run2_1tau0l_VLLm700/` - VLL test datacards (copied from reference)
- `hua/combine/combinationV20/run2_1tau0l_v4_unblind/` - tttt regression test datacards

## Key Functions (runCombineAll.py)

| Function | Lines | Purpose |
|----------|-------|---------|
| `goodnessOfFit()` | 273-331 | Goodness-of-fit test |
| `runImpact()` | 435-468 | Impact plots |
| `runCombineSig()` | 540-603 | Limits and significance |
| `main()` | 140-270 | Main workflow |

## Physics Background

VLL analysis searches for Vector-Like Leptons (BSM particles). Unlike tttt (SM process), VLL requires:
- `r=0` (no signal) as baseline hypothesis
- `--setParameters r=0 --freezeParameters r` freezes signal strength at 0
- This is because we're setting exclusion limits on a BSM signal

## Useful Commands

```bash
# Monitor VLL test progress
tail -f hua/combine/combinationV10/run2_1tau0l_VLLm700/run2_1tau0l_VLLm700_fullTest.log

# Check running combine jobs
ps aux | grep -E "(combine|runCombineAll)" | grep -v grep

# Run VLL analysis
python3 runCombineAll.py --cardDir combinationV10/run2_1tau0l_VLLm700/ --no-blind --ifVLL --channel 1tau0l --steps workspace significance limits impacts postfit

# Run tttt regression test
python3 runCombineAll.py --cardDir combinationV20/run2_1tau0l_v4_unblind/ --no-blind --steps workspace significance limits impacts postfit signal_strength

# Validation: Run limits WITHOUT VLL options (for comparison)
cd hua/combine/combinationV10/run2_1tau0l_VLLm700
combine -M AsymptoticLimits workspace/datacard_1tau0l.root --name _noVLLopts

# MC toys validation (exact limit calculation)
combine -M HybridNew workspace/datacard_1tau0l.root --LHCmode LHC-limits -T 200 --name _MCToys --rMin 0 --rMax 5 --fork 4

# Verbose AsymptoticLimits (show intermediate calculations)
combine -M AsymptoticLimits workspace/datacard_1tau0l.root -v 3 --name _verbose 2>&1 | tee limit_verbose.log
```

## Key Findings

### AsymptoticLimits Validation (2025-12-03)
- VLL options (`--setParameters r=0 --freezeParameters r`) do NOT affect limit values
- AsymptoticLimits scans r from rMin to rMax regardless of initial parameters
- VLL options ARE important for:
  - **Significance**: Sets null hypothesis at r=0
  - **Impacts**: Computes systematic effects at r=0 baseline
  - **GoF tests**: Evaluates fit quality at background-only hypothesis
