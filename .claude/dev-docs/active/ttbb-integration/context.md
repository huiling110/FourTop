# TTBB Integration - Key Context

**Last Updated**: 2025-12-05

## TTBB Sample Locations (Verified)

```
/publicfs/cms/data/TopQuark/Fourtop_VLL/
├── 2016/mc/TTBB_4f_*          # 2016postVFP
├── 2016APV/mc/TTBB_4f_*       # 2016preVFP
├── 2017/mc/TTBB_4f_*
└── 2018/mc/TTBB_4f_*

Each with 3 decay modes:
- TTBB_4f_TTToHadronic/      (~14G) → ttbb_0l
- TTBB_4f_TTToSemiLeptonic/  (~18G) → ttbb_1l
- TTBB_4f_TTTo2L2Nu/         (~8G)  → ttbb_2l
```

## Critical Files to Modify

### Configuration
| File | Purpose | Status |
|------|---------|--------|
| `hua/src_py/ttttGlobleQuantity.py` | Cross-sections, process groupings | Pending |
| `inputFiles/genSumMap2016.h` | Generator sum weights 2016 | Pending |
| `inputFiles/genSumMap2017.h` | Generator sum weights 2017 | Pending |
| `inputFiles/genSumMap2018.h` | Generator sum weights 2018 | Pending |

### Overlap Removal
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/src/copyBranch.C` | Event filtering logic | Pending |
| `objectSelectionOptimized/include/copyBranch.h` | Function declaration | Pending |

### Analysis Pipeline
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/jobs/makeJob_objectTSelectorForNanoAOD.py` | Stage 1 jobs | Pending |
| `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` | Stage 2 jobs | Pending |
| `writeHistGood/jobs/makeJob_forWriteHist.py` | Stage 3 jobs | Auto-discovers |
| `plotting/writeDatacard.py` | TTBB systematics | Pending |

### Documentation
| File | Purpose | Status |
|------|---------|--------|
| `ANALYSIS_WORKFLOW.md` | Stage 1 & 2 documentation | Pending |

## Existing Infrastructure for Overlap

### GenPart Access (eventReader_nano.h)
```cpp
// Available branches for overlap removal
TTreeReaderArray<Float_t> GenPart_pt;
TTreeReaderArray<Float_t> GenPart_eta;
TTreeReaderArray<Float_t> GenPart_phi;
TTreeReaderArray<Int_t>   GenPart_pdgId;
TTreeReaderArray<Short_t> GenPart_genPartIdxMother;
TTreeReaderArray<Int_t>   GenPart_statusFlags;
```

### Utility Functions (usefulFunc.C)
```cpp
// Existing functions that can be reused
OS::overlapRemove()    // Configurable cone matching
OS::genMatchForJER()   // Jet-GenJet matching template
OS::DeltaR()           // Delta-R calculation
```

### Existing Overlap Pattern (copyBranch.C)
```cpp
// Example: overlapRemovalSamples() for gamma processes
// Uses GenPart to filter events based on parton matching
// This pattern can be adapted for ttbb/ttbar overlap
```

## Cross-Section Reference

Current ttbar values (pb):
```python
"ttbar_0l": 377.96
"ttbar_1l": 365.34
"ttbar_2l": 88.29
```

TTBB estimates (to be verified from XSDB):
```python
"TTBB_4f_TTToHadronic": ~1.06      # ~46% of ~2.3 pb total
"TTBB_4f_TTToSemiLeptonic": ~1.03  # ~45%
"TTBB_4f_TTTo2L2Nu": ~0.21         # ~9%
```

## Notes

- TTBB cross-section should be verified from MC production cards or XSDB
- Generator sum weights must be calculated before processing
- Symlinks needed to integrate TTBB with existing job submission
