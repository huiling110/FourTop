# Variable Analyzer Implementation Plan

## Approach: Option C (New variableAnalyzer.C)

Create a completely separate `variableAnalyzer.C` based on `treeAnalyzer.C` pattern to generate input variable histograms with full systematics.

## Key Design Decisions

1. **No MC fake tau separation** - Unlike treeAnalyzer which has `_MCFT`/`_NotMCFT` histograms
2. **Output directory**: `inputVarHists_{version}/` (NOT `variableHists_` to avoid BDT conflict)
3. **Binning source**: Ruobing's `functions.C` from `/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/`
4. **Same systematics** as treeAnalyzer via SystematicManager

## Files to Create

| File | Purpose |
|------|---------|
| `writeHistGood/include/variableAnalyzer.h` | Header for variable analyzer class |
| `writeHistGood/src/variableAnalyzer.C` | Implementation with SystematicManager |
| `writeHistGood/apps/run_variableAnalyzer.C` | Entry point for variable mode |

## Files to Modify

| File | Change |
|------|--------|
| `writeHistGood/src/functions.C` | Copy from Ruobing for updated binning |
| `writeHistGood/include/SystematicManager.h` | Add methods for variable histogram filling |
| `writeHistGood/src/SystematicManager.C` | Implement new methods |
| `writeHistGood/Makefile` | Add `make variables` target |
| `writeHistGood/jobs/makeJob_forWriteHist.py` | Add `--mode variables` option |
| `.claude/skills/workflow-stage3-wh/SKILL.md` | Document variable workflow |

## SystematicManager Extensions

New methods needed:
- `fillSystematicsForVariables()` - Detector systematics for variable histograms
- `fillTheorySystematicsForVariables()` - Theory systematics
- `fillDataDrivenFakeTauSystematicForVariables()` - Data-driven fake tau

## Dependencies

- Existing `histForRegionsBase` class with `fillHistVec()` method
- Existing `WH::initializeHistVec()` from functions.C
- Existing `SystematicManager` infrastructure

## Risks

1. **BDT conflict** - Mitigated by using `inputVarHists_` instead of `variableHists_`
2. **Shared code changes** - Test BDT workflow after SystematicManager updates
3. **Binning mismatch** - Use Ruobing's exact binning

## Verification

1. Build with `make variables`
2. Quick test: single process, single era
3. Check systematic names match treeAnalyzer pattern
4. Compare systematic counts with BDT output
