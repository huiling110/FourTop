# Support Scripts for Future Migration

This document catalogs Python scripts in the `plotting/` directory that are NOT part of the critical Stage 4 workflow but could benefit from migration to `fourtop` package imports in the future.

## Status Key
- **Ready**: Script uses legacy imports (gq, uf) that have fourtop equivalents
- **Partial**: Some imports already use fourtop, others still legacy
- **Complex**: Would require significant refactoring beyond simple import changes

---

## Support Scripts Catalog

### BDT/Optimization Scripts

| Script | Legacy Imports | fourtop Replacement | Status |
|--------|---------------|---------------------|--------|
| `optimizeBinning.py` | uf, gq | checkMakeDir, isRun3 | Ready |
| `optimizeBinning_fromTraining.py` | uf | checkMakeDir | Ready |

### Systematic Checks

| Script | Legacy Imports | fourtop Replacement | Status |
|--------|---------------|---------------------|--------|
| `smooth_systematics_fourTops.py` | uf | checkMakeDir, getEraFromDir | Ready |
| `check_systematic_fluctuations.py` | gq, uf | MCSYS, checkMakeDir | Partial |
| `plottingToCheckSystemUncertainty.py` | gq, uf | MCSYS, isData, checkMakeDir | Ready |

### Efficiency/Study Plots

| Script | Legacy Imports | fourtop Replacement | Status |
|--------|---------------|---------------------|--------|
| `plotHLTEfficiency.py` | gq, uf | histoGramPerSample, checkMakeDir | Ready |
| `plotBtagEff.py` | uf | checkMakeDir | Ready |
| `plotForFakeRate.py` | uf | checkMakeDir, isData | Ready |

### Limit/Signal Plots

| Script | Legacy Imports | fourtop Replacement | Status |
|--------|---------------|---------------------|--------|
| `plotLimitVsMass.py` | gq, uf | checkMakeDir | Ready |
| `plotSignalStrength.py` | uf | checkMakeDir | Ready |

### Job Management

| Script | Legacy Imports | fourtop Replacement | Status |
|--------|---------------|---------------------|--------|
| `checkJobResult.py` | gq, uf | histoGramPerSample, checkMakeDir | Ready |

### Sample Definition Files (plotting/input/)

These files define sample configurations and generally don't need migration:
- `tttt_Charis_*.py` - Sample definitions for tttt
- `VLL_Charis*.py` - Sample definitions for VLL signals

---

## Migration Instructions

When migrating a support script:

1. **Remove sys.path hacks** for `hua/src_py`:
   ```python
   # REMOVE these lines:
   sys.path.insert(0, '../../hua/src_py')
   ```

2. **Replace legacy imports**:
   ```python
   # OLD:
   import ttttGlobleQuantity as gq
   import usefulFunc as uf

   # NEW:
   from fourtop.utils.io import checkMakeDir
   from fourtop.utils.process import isData, isRun3, getEraFromDir
   from fourtop.constants.samples import histoGramPerSample
   from fourtop.constants.jes import JESVariationList
   ```

3. **Update function calls**:
   ```python
   # OLD:
   uf.checkMakeDir(path)
   gq.histoGramPerSample[sample]
   uf.isData(sample)

   # NEW:
   checkMakeDir(path)
   histoGramPerSample[sample]
   isData(sample)
   ```

---

## fourtop Package Reference

### fourtop.utils
| Function | Replaces |
|----------|----------|
| `checkMakeDir()` | `uf.checkMakeDir()` |
| `getInputDicNew()` | `uf.getInputDicNew()` |
| `submitJobs()` | `uf.submitJobs()` |
| `isData()` | `uf.isData()` |
| `isBG()` | `uf.isBG()` |
| `isRun3()` | `uf.isRun3()` |
| `getEraFromDir()` | `uf.getEraFromDir()` |
| `checkIfInputDic()` | `uf.checkIfInputDic()` |
| `getSumListFull()` | `pl.getSumList()` |

### fourtop.constants
| Module | Replaces |
|--------|----------|
| `fourtop.constants.samples.histoGramPerSample` | `gq.histoGramPerSample` |
| `fourtop.constants.jes.JESVariationList` | `gq.JESVariationList` |
| `fourtop.constants.jes.SKIP_SUBPROCESSES` | `gq.SKIP_SUBPROCESSES` |
| `fourtop.constants.systematics.MCSYS` | `wd.MCSys` |

### fourtop.stage4
| Function | Replaces |
|----------|----------|
| `getProSysDicForPlotting()` | `pl.getSysDicPL()` |
| `getSysDic()` | `wd.getSysDic()` |

---

## Notes

- Support scripts are lower priority than critical Stage 4 scripts
- Migration can be done incrementally when scripts are modified for other reasons
- Test thoroughly after migration to ensure physics results unchanged
