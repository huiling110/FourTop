# VLL Integration Context

**Last Updated**: 2025-12-03

## Key Files

### Primary Files to Modify
- `hua/combine/runCombineAll.py` - Main Combine workflow script
- `hua/combine/run_runCombineAll.sh` - Shell script for running tests

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
