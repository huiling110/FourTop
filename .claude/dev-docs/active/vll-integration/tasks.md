# VLL Integration Tasks

**Last Updated**: 2025-12-03 18:30

## Tasks

- [x] Copy VLL test data (run2_1tau0l_VLLm700) to local directory
- [x] Update goodnessOfFit() with VLL options
- [x] Update runImpact() - add ifVLL param and VLL options
- [x] Add runImpactSnapshot() function
- [x] Update runCombineSig() for unblinded VLL
- [x] Update main() to pass ifVLL to runImpact and call runImpactSnapshot
- [x] Add VLL and tttt test commands to run_runCombineAll.sh
- [x] Run VLL limit WITHOUT r=0 freeze for validation comparison
- [x] Compare VLL limits with/without freeze (identical - expected for AsymptoticLimits)
- [x] Remove redundant VLL options from AsymptoticLimits (commit e606c987)
- [x] Create asymptotic_limits_tutorial.py educational script (commit 5c28b581)
- [x] VLL full test (workspace ✅, limits ✅, significance ✅, impacts ✅)
- [x] Fix mv error in runImpact() - files already in impacDir after cd
- [~] MC toys validation (HybridNew) - completed (results in higgsCombine_MCToys.HybridNew.mH120.root)
- [~] Verbose AsymptoticLimits with intermediate values - completed (limit_verbose.log)
- [ ] Run tttt regression test
- [ ] Verify tttt results unchanged from previous runs

## Progress Notes

### 2025-12-03 18:30
- **Fixed mv error in runImpact()**: The mv command tried to move files to impacDir, but we already cd'd to impacDir so files were already there
- **Fix**: Added `2>/dev/null || true` and `check_returncode=False` to make mv command robust
- VLL full test completed successfully (impacts.pdf generated at combineResults/impactResult/)
- MC toys and verbose limit tests completed earlier

### 2025-12-03 13:55
- **MC toys validation started**: HybridNew method running (200 toys)
- **Verbose limit calculation started**: Shows intermediate values (r scan, NP fits)
- **Permissions fix committed** (d67f56b7): Changed glob patterns for dev-docs
- VLL impacts and MC toys tests still running

### 2025-12-03 13:25
- **Code fix committed** (e606c987): Removed redundant VLL options from AsymptoticLimits
- **Tutorial created** (5c28b581): asymptotic_limits_tutorial.py for educational purposes
- VLL full test still running (impacts step in progress)

### 2025-12-03 13:10
- **Validation test completed**: Ran AsymptoticLimits without VLL options
- **Result**: Limits identical with/without `--setParameters r=0 --freezeParameters r`
- **Explanation**: AsymptoticLimits scans r values regardless of initial params
- VLL options more important for Significance/Impacts (r=0 baseline matters)
- VLL full test still running (impacts step in progress)

### 2025-12-03 12:46
- Resumed task from dev-docs
- VLL test progress: workspace ✅, limits ✅ (r < 1.88), significance ✅ (2.0σ)
- Impacts step running with 8 parallel workers (~431/469 fits done)

### 2025-12-03 12:25
- **Committed changes**: `a1ba3107` - feat: Add VLL analysis options to runCombineAll.py
- VLL test still running in background
- Monitor: `tail -f combinationV10/run2_1tau0l_VLLm700/run2_1tau0l_VLLm700_fullTest.log`

### 2025-12-03 12:14
- Created dev-docs
- Copied VLL test data from reference directory
- Implemented all code changes to runCombineAll.py:
  - goodnessOfFit(): Added VLL options
  - runImpact(): Added ifVLL param and VLL options
  - runImpactSnapshot(): Added new function
  - runCombineSig(): Added VLL options for unblinded
  - main(): Updated to pass ifVLL and call runImpactSnapshot for VLL
- Added test commands to run_runCombineAll.sh
- VLL test running in background (PID 3381956)
- Log: combinationV10/run2_1tau0l_VLLm700/run2_1tau0l_VLLm700_fullTest.log
- Verified VLL options correctly applied: `--setParameters r=0 --freezeParameters r`
