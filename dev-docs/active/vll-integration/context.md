# VLL Integration Context

**Last Updated**: 2025-12-04 17:20

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

### MC Toys Validation (2025-12-04)
- HybridNew with 500 toys did not complete after 4+ hours
- Too CPU-intensive for routine validation
- AsymptoticLimits (r < 1.88) is sufficient for production use

### tttt Regression Test (2025-12-04)
- Limits: r < 14.4951 ✅ matches previous
- Significance: 1.86σ ✅ matches previous
- Confirms VLL integration did not affect tttt analysis

### Bug Fix: cardToWorkspaces() (commit aba2eaa8)
- After `os.chdir(working_cardDir)`, relative path no longer worked
- Fixed by converting to absolute path before chdir

---

## Related Documentation

### TTBB Yield Investigation (COMPLETE)
- **Location**: `dev-docs/completed/ttbb-yield-investigation/`
- **Relevance**: Investigated yield differences when re-running OS stage with TTBB integration
- **Key Finding**: Floating-point precision differences between CentOS 7 and AlmaLinux 9 cause small yield variations (~0.05% at baseline, amplified through tight SR cuts)
- **Impact on VLL**: Same environmental differences will affect VLL sample processing
- **Conclusion**: Yield variations are expected environmental variation, NOT bugs. Acceptable for physics analysis.

**Summary of findings**:
| Channel | Effect | Explanation |
|---------|--------|-------------|
| 1tau0l | +0.38% data | Tau cuts dominate, more events pass threshold |
| 1tau1l | -5.0% data | Lepton cut dominates, fewer events pass |
