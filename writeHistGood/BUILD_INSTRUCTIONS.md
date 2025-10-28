# Build Instructions

## ⚠️ CRITICAL: Environment Setup

**ALWAYS source the environment file before ANY operation:**

```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop
source setEnv_newNew.sh
cd writeHistGood
```

This sets up:
- ROOT 6.36.01 with GCC 14.3.1
- TMVA libraries
- libcommenFunction.so library path
- Python environment with correctionlib
- RoccoR corrections

**Without sourcing this file, you will get library errors!**

## Building the Executable

```bash
# Clean build (recommended after changes)
source ../setEnv_newNew.sh
make clean
make -j4

# Quick rebuild
source ../setEnv_newNew.sh
make -j4
```

Executable location: `apps/run_treeAnalyzer.out` (≈7.4 MB)

## Running the Executable

### Test Mode (10,000 events)
```bash
source ../setEnv_newNew.sh
./apps/run_treeAnalyzer.out
# Uses default parameters from apps/run_treeAnalyzer.C:16-35
```

### Production Mode (full dataset)
```bash
source ../setEnv_newNew.sh
./apps/run_treeAnalyzer.out <inputDir> <process> <channel> <version> <ifSys> <isTest>
```

**Parameters:**
- `inputDir`: Path to input ROOT files (e.g., `/publicfs/cms/user/.../mc/`)
- `process`: Sample name (e.g., `tttt`, `ttbar_1l`, `fakeLepton`)
- `channel`: Analysis channel (`1tau1l`, `1tau0l`, `1tau2l`)
- `version`: Output version tag (e.g., `v0_test`, `v14`)
- `ifSys`: Include systematics (`0` = false, `1` = true)
- `isTest`: Test mode (`0` = full, `1` = 10k events)

**Example:**
```bash
./apps/run_treeAnalyzer.out \
  /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/ \
  tttt \
  1tau1l \
  v14 \
  1 \
  0
```

## Common Issues

### "cannot open shared object file: libcommenFunction.so"
**Solution:** You forgot to source `setEnv_newNew.sh`!

### "unable to open input weight file"
**Cause:** Hardcoded paths in code point to wrong CMSSW version
**Location:** Check [src/treeAnalyzer.C](src/treeAnalyzer.C) and [include/inputFileMap.h](include/inputFileMap.h)
**Fix:** Ensure paths use `CMSSW_14_1_0_pre4` not `CMSSW_10_6_20`

### "unknown branch" errors from ROOT
**Status:** These are warnings, not errors. Some branches don't exist in all samples.
**Action:** Can be safely ignored if analysis runs to completion.

## Output

Default output location: `<inputDir>/variableHists_<version>/<process>.root`

Contains BDT score histograms for:
- Signal regions (SR)
- Control regions (CR)
- Validation regions (VR)
- Systematic variations (if `ifSys=1`)

## Code Structure

- `apps/run_treeAnalyzer.C` - Main entry point with default parameters
- `src/treeAnalyzer.C` - Core analysis loop, BDT evaluation, histogram filling
- `include/treeAnalyzer.h` - Class definition with smart pointers
- `include/SystematicManager.h` - Centralized systematic variations (47 systematics)
- `include/AnalysisLogger.h` - Logging framework with color output
- `include/inputFileMap.h` - BDT weight file paths per era
- `Makefile` - Build configuration (uses CMSSW_14_1_0_pre4)

## Recent Improvements (2025-10)

See [REFACTORING_SUMMARY.md](REFACTORING_SUMMARY.md) for details:
- ✅ Smart pointers (no memory leaks)
- ✅ Structured logging with timestamps
- ✅ Systematic variations reduced by 75% (135 → 33 lines)
- ✅ Exception handling for better error messages
- ✅ Fixed CMSSW version paths

## For Claude Code / AI Assistants

**REMEMBER:** Always run:
```bash
source setEnv_newNew.sh
```
before make, run, or any ROOT operations in this directory!
