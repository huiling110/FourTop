# TTBB Integration - Key Context

**Last Updated**: 2025-12-07 16:55

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
| `config/analysis_config_1tau0l_full.yaml` | 1tau0l channel config | ✅ Updated |
| `config/analysis_config_1tau1l_TTBBtest.yaml` | 1tau1l channel config | ✅ Created |

### Overlap Removal (v2 - Ghost-matching, CMS standard)
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/src/copyBranch.C` | Ghost-matching overlap removal | ✅ Updated |
| `objectSelectionOptimized/include/copyBranch.h` | countAdditionalBHadrons() declaration | ✅ Updated |
| `objectSelectionOptimized/include/eventReader_nano.h` | GenJet_hadronFlavour added | ✅ Updated |

### Build System Fixes
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/Makefile` | Library paths | ✅ Fixed |
| `objectSelectionOptimized/src/PUWeightCal.C` | Pileup file path | ✅ Fixed |
| `setEnv_newNew.sh` | RoccoR library path | ✅ Fixed |

### Analysis Pipeline
| File | Purpose | Status |
|------|---------|--------|
| `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` | Stage 1 jobs (loads version from YAML) | ✅ Updated |
| `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` | Stage 2 jobs | Pending |
| `writeHistGood/jobs/makeJob_forWriteHist.py` | Stage 3 jobs | Auto-discovers |
| `plotting/writeDatacard.py` | TTBB systematics | Pending |
| `plotting/pl.py` | Validation plots with YAML config | ✅ Updated |

### Documentation
| File | Purpose | Status |
|------|---------|--------|
| `ANALYSIS_WORKFLOW.md` | Stage 1 & 2 documentation, Config section | ✅ Done |
| `.claude/dev-docs/active/ttbb-integration/todo.md` | Future refactoring tasks | ✅ Created |

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

**TTBB cross-sections** (scaled from ttH AN: 43.74 × 17.75/21.34 = 36.3 pb):
```python
"TTBB_4f_TTToHadronic": 16.52     # 36.3 × 0.455 (hadronic BR)
"TTBB_4f_TTToSemiLeptonic": 15.97 # 36.3 × 0.440 (semileptonic BR)
"TTBB_4f_TTTo2L2Nu": 3.85         # 36.3 × 0.106 (dilepton BR)
```

## Stage 1 Output Location (2018)

```
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/mc/
├── TTBB_4f_TTToHadronic/      (10 files, 58M)
├── TTBB_4f_TTToSemiLeptonic/  (15 files, 51M)
├── TTBB_4f_TTTo2L2Nu/         (6 files, 11M)
├── ttbar_0l/                  (339 files, 509M, with overlap removal)
├── ttbar_1l/                  (391 files, 392M, with overlap removal)
└── ttbar_2l/                  (155 files, 49M, with overlap removal)
```

## Ghost-Matching Validation Results

From analysis of 10,000 events each:
- **ttbar**: ~25% of events have ≥1 additional b-jet (will be removed)
- **TTBB**: ~63% of events have ≥1 additional b-jet (will be kept)

## Stage 4 Validation Results (2018)

### 1tau0l Channel
| Region | ttbb Events | tt Events | ttbb/tt Ratio | Notes |
|--------|-------------|-----------|---------------|-------|
| 1tau0lSR | 412.0 | 360.7 | 1.14 | Higher ratio = more b-jets in SR |
| 1tau0lCRMR | 573.2 | 4386.2 | 0.13 | Lower b-jet fraction in CR |

### 1tau1l Channel
| Region | ttbb Events | tt Events | ttbb/tt Ratio | Notes |
|--------|-------------|-----------|---------------|-------|
| 1tau1lSR | 35.5 | 15.0 | 2.36 | Even higher ratio in lepton channel |
| 1tau1lCR12 | 44.3 | 161.9 | 0.27 | Lower b-jet fraction in CR |

Plot colors:
- ttbb: #e6550d (darker orange)
- tt: #f03b20 (red-orange)

## Notes

- ✅ TTBB cross-sections: 43.74 × (17.75/21.34) = 36.3 pb total
- ✅ Generator sum weights calculated for all years
- ✅ Symlinks created for TTBB samples
- ✅ Stage 1 complete for 2018 with ghost-matching overlap removal
- ✅ Stage 2 complete for 2018 (variable production)
- ✅ Fake tau files regenerated (2025-12-06 19:13/19:21)
- ✅ Stage 3 complete for 2018 1tau0l (histograms with systematics)
- ✅ Stage 3 complete for 2018 1tau1l (histograms with systematics)
- ✅ Stage 4 complete for 2018 1tau0l (validation plots generated 2025-12-07 09:08)
- ✅ Stage 4 complete for 2018 1tau1l (validation plots generated 2025-12-07 09:32)
- ✅ **2017 fake files regenerated** (2025-12-07 16:28-16:37)
- ✅ **2016postVFP fake files regenerated** (2025-12-07 16:39-16:43)
- ✅ **2016preVFP fake files regenerated** (2025-12-07 16:42-16:48)
- Jobs must run on AlmaLinux9 (not CentOS7) for CMSSW_14 compatibility
- **2018 both channels validated** (1tau0l and 1tau1l) - ready for other years
- **CRITICAL**: Fake tau/lepton files MUST be regenerated for each version (added to CLAUDE.md)

## Resume Commands

```bash
# Check job status
hep_q -u huahuil | grep WH_

# Run WH (Stage 3) for a channel
source setEnv_newNew.sh
python3 run_workflow.py --stage 3.3 --config config/analysis_config_1tau0l_full.yaml
python3 run_workflow.py --stage 3.3 --config config/analysis_config_1tau1l_TTBBtest.yaml

# Run pl.py for validation
cd plotting
python3 pl.py --config ../config/analysis_config_1tau0l_full.yaml --era 2018 --channel 1tau0l --regions 1tau0lSR 1tau0lCRMR 1tau0lVR --unblind --no-sys
python3 pl.py --config ../config/analysis_config_1tau1l_TTBBtest.yaml --era 2018 --channel 1tau1l --regions 1tau1lSR 1tau1lCR12 --unblind --no-sys
```

## Analysis Pipeline Abbreviations

| Abbrev | Full Name | Directory |
|--------|-----------|-----------|
| **OS** | Object Selection | `objectSelectionOptimized/` |
| **MV** | Make Variables | `makeVariables_goodCode/` |
| **WH** | Write Histograms | `writeHistGood/` |
| **PL** | Plotting | `plotting/` |
