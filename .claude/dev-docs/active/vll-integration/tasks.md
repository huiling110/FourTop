# VLL Integration Tasks

**Last Updated**: 2025-12-03 12:17

## Tasks

- [x] Copy VLL test data (run2_1tau0l_VLLm700) to local directory
- [x] Update goodnessOfFit() with VLL options
- [x] Update runImpact() - add ifVLL param and VLL options
- [x] Add runImpactSnapshot() function
- [x] Update runCombineSig() for unblinded VLL
- [x] Update main() to pass ifVLL to runImpact and call runImpactSnapshot
- [x] Add VLL and tttt test commands to run_runCombineAll.sh
- [~] Run tests and verify results (VLL test running in background)

## Progress Notes

### 2025-12-03
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
