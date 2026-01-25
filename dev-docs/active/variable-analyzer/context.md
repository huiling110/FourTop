# Variable Analyzer - Input Variable Histogram Generation

## Goal

Create `variableAnalyzer.C` to generate input variable histograms (tausT_1pt, jets_HT, etc.) with full systematics matching `treeAnalyzer.C`. Output compatible with Stage 4 combine workflow.

## Key Files

### Create
- `writeHistGood/include/variableAnalyzer.h`
- `writeHistGood/src/variableAnalyzer.C`
- `writeHistGood/apps/run_variableAnalyzer.C`

### Modify
- `writeHistGood/src/functions.C` - Copy from Ruobing
- `writeHistGood/include/SystematicManager.h` - Add variable methods
- `writeHistGood/Makefile` - Add `make variables`
- `writeHistGood/jobs/makeJob_forWriteHist.py` - Add `--mode variables`

### Reference
- Ruobing's binning: `/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/writeHistGood/src/functions.C`

## Critical Notes

1. **No MC fake tau separation** (unlike treeAnalyzer)
2. **Use Ruobing's binning** for variables
3. **Same systematics** as treeAnalyzer via SystematicManager
