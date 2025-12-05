# TTBB Integration - Key Context

**Last Updated**: 2025-12-05 15:30

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
| `hua/src_py/ttttGlobleQuantity.py` | Cross-sections, process groupings | ✅ Done |
| `inputFiles/genSumMap2016.h` | Generator sum weights 2016 | ✅ Done |
| `inputFiles/genSumMap2017.h` | Generator sum weights 2017 | ✅ Done |
| `inputFiles/genSumMap2018.h` | Generator sum weights 2018 | ✅ Done |
| `inputFiles/genSumMap2016APV.h` | Generator sum weights 2016APV | ✅ Done |
| `config/analysis_config_1tau0l_full.yaml` | Full pipeline YAML config | ✅ New |

### Overlap Removal
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/src/copyBranch.C` | Event filtering logic | ✅ Done |
| `objectSelectionOptimized/include/copyBranch.h` | Function declaration | ✅ Done |

### Build System Fixes
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/Makefile` | Library paths | ✅ Fixed |
| `objectSelectionOptimized/src/PUWeightCal.C` | Pileup file path | ✅ Fixed |
| `setEnv_newNew.sh` | RoccoR library path | ✅ Fixed |

### Analysis Pipeline
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` | Stage 1 jobs | ✅ Done |
| `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` | Stage 2 jobs | Pending |
| `writeHistGood/jobs/makeJob_forWriteHist.py` | Stage 3 jobs | Auto-discovers |
| `plotting/writeDatacard.py` | TTBB systematics | Pending |

### Documentation
| File | Purpose | Status |
|------|---------|--------|
| `ANALYSIS_WORKFLOW.md` | Stage 1 & 2 documentation, Config section | ✅ Done |

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

## Stage 1 Output Location (2018)

```
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/mc/
├── TTBB_4f_TTToHadronic/      (66M, output complete)
├── TTBB_4f_TTToSemiLeptonic/  (56M, 15 files)
├── TTBB_4f_TTTo2L2Nu/         (12M, output complete)
├── ttbar_0l/                  (with overlap removal applied)
├── ttbar_1l/                  (570M, 391 files)
└── ttbar_2l/                  (with overlap removal applied)
```

## Notes

- TTBB cross-section should be verified from MC production cards or XSDB
- Generator sum weights must be calculated before processing
- Symlinks needed to integrate TTBB with existing job submission
- Stage 1 jobs completed successfully for 2018 (all 3826 jobs finished)
