# Python System Refactoring - Tasks

## Status Table

| Phase | Task | Status | Notes |
|-------|------|--------|-------|
| **1** | Create branch `refactor-python-system` | ✅ done | |
| **1** | Create `fourtop/` package skeleton | ✅ done | All __init__.py files |
| **1** | Update setEnv_newNew.sh | ✅ done | PYTHONPATH added |
| **1** | Move workflow_utils.py | ✅ done | fourtop/workflow/ modules |
| **2** | Extract constants/era.py | ✅ done | VFP mapping consolidation |
| **2** | Extract constants/systematics.py | ✅ done | MCSys dictionary (82 entries) |
| **2** | Split ttttGlobleQuantity.py | ✅ done | physics.py, samples.py, jes.py |
| **3** | Split usefulFunc.py | ✅ done | io.py, histogram.py, process.py |
| **3** | Create utils/logging.py | ✅ done | setup_logger, get_logger |
| **4** | Refactor pl.py | ✅ done | plotting/stack.py module |
| **4** | Refactor addTemplateNew.py | pending | |
| **5** | Refactor writeDatacard.py | pending | |
| **5** | Refactor addJESTemplatesToHistFile.py | pending | |
| **5** | Refactor runCombineAll.py | pending | |
| **6** | Create jobs/base.py | pending | |
| **6** | Add type hints | pending | |
| **6** | Update CLAUDE.md | ✅ done | Package documentation added |
| **6** | Create test suite | pending | |

## Session Notes

### Session 1 (2026-01-21)
- Explored Python system: 125 files, ~15,000+ lines
- Identified key duplications (VFP mapping, MCSys, process filtering)
- Created comprehensive refactoring plan
- Key files: pl.py (663 lines), writeDatacard.py (508 lines), workflow_utils.py (721 lines)

### Session 2 (2026-01-22)
- Created `fourtop/` package with all subpackages
- Extracted constants modules:
  - `era.py`: ERAS, VFP_ERAS, map_vfp_era(), ERA_TO_UL
  - `systematics.py`: MCSYS (82 entries), get_systematics_for_channel()
  - `physics.py`: lumiMap, crossSectionMap
  - `samples.py`: histoGramPerSample, proChannelDic, sample utilities
  - `jes.py`: JESVariationList, SKIP_SUBPROCESSES, validate_jes_list()
- Created utils modules:
  - `io.py`: checkMakeDir, runCommand, file I/O
  - `process.py`: isData, isBG, getAllSubPro, process filtering
  - `histogram.py`: getHistFromFile, handle_negative_bins, histogram ops
  - `logging.py`: setup_logger, centralized logging
- Created workflow modules (from workflow_utils.py):
  - `config.py`: load_config, get_channel, get_eras, get_options
  - `paths.py`: build_hist_path, build_template_path, build_datacard_path
  - `state.py`: WorkflowState class
- Created plotting/stack.py: getHists, getErrorPlot, COLOUR_PER_SAMPLE
- Updated CLAUDE.md with package documentation

**Commits:**
- `feat: Create fourtop Python package with core modules` (17 files, 1685 insertions)
- `feat: Add constants and utils modules to fourtop package` (8 files, 1880 insertions)
- `feat: Add plotting/stack.py module for stack plot building` (2 files, 357 insertions)
- `docs: Add Python package documentation to CLAUDE.md` (1 file, 91 insertions)

## Package Structure (Created)

```
fourtop/
├── __init__.py
├── constants/
│   ├── __init__.py
│   ├── era.py          # VFP mapping, era constants
│   ├── jes.py          # JES sources, skip lists
│   ├── physics.py      # Cross sections, luminosity
│   ├── samples.py      # Process mappings
│   └── systematics.py  # MCSys dictionary (82 entries)
├── utils/
│   ├── __init__.py
│   ├── histogram.py    # ROOT histogram operations
│   ├── io.py           # File I/O, directory ops
│   ├── logging.py      # Centralized logging
│   └── process.py      # Process filtering
├── workflow/
│   ├── __init__.py
│   ├── config.py       # Config loading
│   ├── paths.py        # Path builders
│   └── state.py        # Workflow state
├── plotting/
│   ├── __init__.py
│   └── stack.py        # Stack plot building
├── stage4/
│   └── __init__.py     # (stub - future)
└── jobs/
    └── __init__.py     # (stub - future)
```

## Next Steps

1. Refactor Stage 4 scripts (addTemplateNew.py, writeDatacard.py, etc.)
2. Create jobs/base.py for job submission
3. Add comprehensive type hints
4. Create test suite with golden references

## Commands Reference

```bash
# Test package imports
source setEnv_newNew.sh
python3 -c "from fourtop.constants import lumiMap, MCSYS, JESVariationList"
python3 -c "from fourtop.utils import checkMakeDir, isData, getHistFromFile"
python3 -c "from fourtop.workflow import load_config, build_hist_path"
python3 -c "from fourtop.plotting import getHists, COLOUR_PER_SAMPLE"
```
