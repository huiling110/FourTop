# Plot Beautification - Tasks

## Status Table

| Phase | Task | Status | Notes |
|-------|------|--------|-------|
| **1** | Create `fourtop/plotting/labels.py` | complete | Label mappings for PROCESS_LABELS_PAPER, REGION_LABELS |
| **1** | Update `fourtop/plotting/__init__.py` | complete | Export labels functions |
| **2** | Add `preliminary` option to `addCMSTextToPad()` | complete | Can now hide "Preliminary" |
| **2** | Add `addRegionLabel()` function | complete | Draws region text on plot |
| **2** | Add `addFitTypeLabel()` function | complete | Draws Pre-fit/Post-fit text |
| **3** | Update `addLegend()` for paper mode | complete | Uses paper labels when ifPaper=True |
| **3** | Update `makeStackPlotNew()` for annotations | complete | Adds region/fit type labels |
| **3** | Reduce ratio y-axis divisions | complete | 505 divisions in paper mode |
| **4** | Add `--paper` flag to pl_postFit.py | complete | Publication mode enabled |
| **4** | Add publication subfolder output | complete | Outputs to `postfitPlots/publication/` |
| **5** | Test baseline plots | complete | Generated without --paper |
| **5** | Test paper mode plots | complete | Generated with --paper |
| **5** | Generate final publication plots | complete | All 3 channels + prefit |

## Session Notes

### Session 1 (2026-01-23)
- Analyzed current plot: `SR1tau2l_BDT_logy_BDT_SR1tau2l_fit_s_Run2.png`
- Identified issues: process labels, CMS header, missing annotations
- Created plan with user input on preferences
- User requirements:
  - Keep ttX as "ttX"
  - fakeTau -> "fake tau_h"
  - Add region labels (SR 1tau_h0l, etc.)
  - Add Pre-fit/Post-fit text
  - Output to publication/ subfolder
  - Add --paper flag

### Session 2 (2026-01-23)
- Implemented all phases:
  - Created `fourtop/plotting/labels.py` with centralized label mappings
  - Updated `fourtop/plotting/style.py` with preliminary option, addRegionLabel(), addFitTypeLabel()
  - Updated `plotting/pl.py` with ifPaper parameter throughout
  - Updated `plotting/pl_postFit.py` with --paper and --no-sb flags
- Fixed bug: `get_union_process_list()` not grouping ttZ/ttW/ttH into ttX
- Successfully tested both baseline and paper mode
- Generated publication plots to `publication/` subfolder

## Verification Commands
```bash
# Baseline test
python3 plotting/pl_postFit.py --fit-file hua/combine/combinationV22/run2_3channels_v4/fitDiagnosticsTest.root

# Paper mode test
python3 plotting/pl_postFit.py --fit-file hua/combine/combinationV22/run2_3channels_v4/fitDiagnosticsTest.root --paper
```

## Output Location
- Publication plots: `hua/combine/combinationV22/run2_3channels_v4/combineResults/postfitResult/postfitPlots/publication/`

## Task Complete
All tasks completed. Ready to commit and move to dev-docs/finished/.
