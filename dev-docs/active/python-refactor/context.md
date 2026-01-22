# Python System Refactoring - Context

## Goal

Refactor the FourTop Python system (~125 files) to:
1. Create proper `fourtop/` package structure
2. Eliminate code duplication (VFP mapping, MCSys, process filtering)
3. Add type hints and centralized logging
4. Create physics validation test suite
5. Update CLAUDE.md for better Claude awareness

## Key Constraints

- **Physics results must remain IDENTICAL** - bit-exact template comparisons
- **Backward compatible** - original files become thin wrappers
- **Config-driven** - continue using YAML configs
- **ROOT compatible** - test with CMSSW_14_1_0_pre4 ROOT version

## Environment

- **Branch**: `refactor-python-system` (new)
- **Python**: Python 3 (CMSSW_14_1_0_pre4)
- **Setup**: `source setEnv_newNew.sh`
- **Test config**: `config/analysis_config_1tau0l_XGB080test.yaml`

## Critical Files

| File | Lines | Priority | Notes |
|------|-------|----------|-------|
| plotting/pl.py | 663 | HIGH | Core validation plotting |
| plotting/writeDatacard.py | 508 | HIGH | MCSys dictionary (105+ entries) |
| plotting/addTemplateNew.py | 189 | HIGH | Template consolidation |
| plotting/addJESTemplatesToHistFile.py | 694 | HIGH | JES/TES/MET systematics |
| plotting/workflow_utils.py | 721 | MEDIUM | Already well-structured |
| hua/src_py/ttttGlobleQuantity.py | 722 | MEDIUM | Physics constants |
| hua/src_py/usefulFunc.py | 758 | MEDIUM | Utility functions |
| hua/combine/runCombineAll.py | 800 | MEDIUM | Combine orchestration |

## Key Duplications to Fix

1. **VFP Era Mapping** - In 5+ files: workflow_utils.py, writeDatacard.py, addTemplateNew.py, addJESTemplatesToHistFile.py, pl.py
2. **MCSys Dictionary** - 105+ entries hardcoded in writeDatacard.py
3. **Process Filtering** - `getSumList()` duplicated in pl.py, addTemplateNew.py
4. **Histogram Operations** - Overlap between usefulFunc.py and pl.py

## Package Structure

```
fourtop/
  constants/    # physics.py, samples.py, systematics.py, jes.py, era.py
  utils/        # io.py, histogram.py, process.py, logging.py
  workflow/     # config.py, paths.py, state.py
  plotting/     # style.py, stack.py, validation.py
  stage4/       # templates.py, datacards.py, systematics.py, combine.py
  jobs/         # base.py, stage1.py, stage2.py, stage3.py
```

## Validation Strategy

- Generate golden references before refactoring
- Compare templates bin-by-bin after each phase
- Verify expected limits within 0.1%
- Check all 105+ systematics preserved
