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
| **4** | Refactor addTemplateNew.py | ✅ done | stage4/templates.py |
| **5** | Refactor writeDatacard.py | ✅ done | stage4/datacards.py |
| **5** | Refactor addJESTemplatesToHistFile.py | ✅ done | stage4/systematics.py |
| **5** | Refactor runCombineAll.py | ✅ done | stage4/combine.py |
| **6** | Create jobs/base.py | ✅ done | JobSubmitter, BatchJobSubmitter |
| **6** | Add type hints | ✅ done | All modules have type hints |
| **6** | Update CLAUDE.md | ✅ done | Package documentation added |
| **6** | Create test suite | pending | |
| **E** | Create fourtop/plotting/style.py | ✅ done | setTDRStyle, addCMSTextToPad, getMyLegend |
| **E** | Add getSumHist to fourtop.utils.histogram | ✅ done | Main aggregation function |
| **E** | Convert workflow_utils.py to thin wrapper | ✅ done | ~700→85 lines |
| **E** | Update pl.py to use fourtop imports | ✅ done | Removed uf, st, workflow_utils |
| **F** | Update job scripts (OS/MV/WH) | ✅ done | All use fourtop imports |
| **F** | Update run_workflow.py | ✅ done | Uses fourtop.workflow |
| **F** | Update writeCombinationDatacard.py | ✅ done | Uses fourtop.workflow |
| **F** | Update helper scripts | ✅ done | check_*.py, verify_*.py |

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

### Session 3 (2026-01-22 continued)
- Refactored Stage 4 scripts to use fourtop package:
  - `fourtop/stage4/templates.py`: resetNegativeBins, addDataHist, TemplateBuilder
  - `fourtop/stage4/datacards.py`: getSysDic, addLumi, write_shape_datacard, DatacardWriter
  - `fourtop/stage4/systematics.py`: addJESToFile, addJERToFile, addTESToFile, addMETToFile, addEESToFile
  - `fourtop/stage4/combine.py`: ensure_dir, runCommand, cardToWorkspaces
- Updated Stage 4 scripts to use fourtop imports:
  - addTemplateNew.py: 155 → uses fourtop.stage4.templates
  - writeDatacard.py: 508 → 109 lines (80% reduction)
  - addJESTemplatesToHistFile.py: 694 → ~480 lines (30% reduction)
- Added build_hist_path_jes to fourtop.workflow exports

**Commits:**
- `refactor: Extract template functions to fourtop/stage4/templates.py`
- `refactor: Extract datacard functions to fourtop/stage4/datacards.py`
- `refactor: Extract systematic consolidation to fourtop/stage4/systematics.py`
- `refactor: Extract Combine helpers to fourtop/stage4/combine.py`

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
│   ├── stack.py        # Stack plot building
│   └── style.py        # ROOT TDR style, CMS labels
├── stage4/
│   ├── __init__.py
│   ├── templates.py    # Template ROOT file generation
│   ├── datacards.py    # CMS Combine datacard writing
│   ├── systematics.py  # JES/TES/MET consolidation
│   └── combine.py      # Combine fit orchestration
└── jobs/
    ├── __init__.py
    └── base.py         # JobSubmitter, BatchJobSubmitter
```

### Session 4 (2026-01-22 continued)
- Created `fourtop/jobs/base.py`:
  - `JobSubmitter` - Abstract base class for HTCondor job submission
  - `BatchJobSubmitter` - Subclass for multi-file batch processing (Stage 1)
  - `get_processes_from_directory()` - List processes from directory
  - `check_input_directory()` - Validate process directory names
- Common patterns encapsulated:
  - Directory structure creation (job_scripts, logs)
  - Shell script generation with environment setup
  - HTCondor submission via hep_sub
  - Cluster logging to CSV

**Commits:**
- `feat: Add jobs/base.py with JobSubmitter base class`

### Session 5 (2026-01-22 continued)
- Phase E: Complete pl.py Refactoring
- Created `fourtop/plotting/style.py`:
  - `setTDRStyle()` - ROOT TDR style configuration
  - `setMyStyle()` - Custom plot styling
  - `addCMSTextToPad()` - Add CMS label to pad
  - `addCMSTextToCan()` - Add CMS label to canvas
  - `getMyLegend()` - Create styled legend
  - Uses fourtop imports (lumiMap, isRun3) instead of legacy gq/uf
- Added `getSumHist()` to `fourtop/utils/histogram.py`:
  - Main histogram aggregation function (~100 lines)
  - `_modifyDicForMCFTau()` helper for MC fake tau splitting
  - Reuses existing functions from fourtop.utils.process
- Converted `plotting/workflow_utils.py` to thin wrapper:
  - Reduced from ~700 lines to ~85 lines
  - Now just re-exports from fourtop.workflow
- Updated `plotting/pl.py` to use fourtop imports:
  - Removed `import usefulFunc as uf`
  - Removed `import setTDRStyle as st`
  - Now imports directly from fourtop.workflow, fourtop.plotting.style, fourtop.utils.histogram

**Files modified:**
- fourtop/plotting/style.py (NEW ~220 lines)
- fourtop/plotting/__init__.py
- fourtop/utils/histogram.py (added getSumHist, ~100 lines)
- fourtop/utils/__init__.py
- fourtop/workflow/__init__.py
- plotting/pl.py (updated imports)
- plotting/workflow_utils.py (thin wrapper)

### Session 5 continued - Phase F: Migrate remaining scripts
- Updated job submission scripts to use fourtop imports:
  - `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py`
  - `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py`
  - `writeHistGood/jobs/makeJob_WH.py`
  - `writeHistGood/jobs/makeJob_WH_forJES.py`
  - `writeHistGood/jobs/makeJob_forWriteHist.py`
  - `makeVariables_goodCode/jobs/makeJob_MV_JESVariation.py`
- Updated core workflow scripts:
  - `run_workflow.py`
  - `hua/combine/writeCombinationDatacard.py`
- Updated helper scripts:
  - `scripts/check_mv_systematics.py`
  - `scripts/check_os_systematics.py`
  - `scripts/submit_os_resubmit.py`
  - `makeVariables_goodCode/verify_mv_completion.py`

**Commits:**
- `refactor: Complete Phase E - pl.py uses fourtop imports`
- `refactor: Remove sys.path hacks from job scripts`
- `refactor: Update run_workflow.py and makeJob_forWriteHist.py`
- `refactor: Update helper scripts to use fourtop imports`

## Next Steps

1. ~~Create jobs/base.py for job submission~~ ✅
2. ~~Add type hints~~ ✅ (all modules created with type hints)
3. ~~Phase E: Complete pl.py refactoring~~ ✅
4. ~~Phase F: Update remaining scripts to use fourtop imports~~ ✅
5. Create test suite with golden references (optional)

## Migration Status

### COMPLETED ✅
| Script | Status |
|--------|--------|
| `run_workflow.py` | ✅ Uses fourtop.workflow |
| `hua/combine/writeCombinationDatacard.py` | ✅ Uses fourtop.workflow |
| `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` | ✅ Uses fourtop imports |
| `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` | ✅ Uses fourtop imports |
| `makeVariables_goodCode/jobs/makeJob_MV_JESVariation.py` | ✅ Uses fourtop imports |
| `writeHistGood/jobs/makeJob_WH.py` | ✅ Uses fourtop imports |
| `writeHistGood/jobs/makeJob_WH_forJES.py` | ✅ Uses fourtop imports |
| `writeHistGood/jobs/makeJob_forWriteHist.py` | ✅ Uses fourtop imports |
| `scripts/check_mv_systematics.py` | ✅ Uses fourtop imports |
| `scripts/check_os_systematics.py` | ✅ Uses fourtop imports |
| `scripts/submit_os_resubmit.py` | ✅ Uses fourtop imports |
| `makeVariables_goodCode/verify_mv_completion.py` | ✅ Uses fourtop imports |

### Remaining (archive/low priority)
| Script | Notes |
|--------|-------|
| `archive/workflow_automation_backup/run_workflow_auto.py` | Archive, no need to update |
| `archive/workflow_automation_backup/workflow_state_v3.py` | Archive, no need to update |

### Migration Pattern

Replace:
```python
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', '..', 'plotting'))
from workflow_utils import load_config, get_eras
import ttttGlobleQuantity as gq
import usefulFunc as uf
```

With:
```python
from fourtop.workflow import load_config, get_eras
from fourtop.constants import samples, physics
from fourtop.utils import checkMakeDir, isData
```

**Note**: Scripts can be migrated incrementally as they are modified for other reasons.

## Commands Reference

```bash
# Test package imports
source setEnv_newNew.sh
python3 -c "from fourtop.constants import lumiMap, MCSYS, JESVariationList"
python3 -c "from fourtop.utils import checkMakeDir, isData, getHistFromFile"
python3 -c "from fourtop.workflow import load_config, build_hist_path"
python3 -c "from fourtop.plotting import getHists, COLOUR_PER_SAMPLE, setTDRStyle, addCMSTextToPad"
python3 -c "from fourtop.stage4 import resetNegativeBins, getSysDic, addJESToFile, runCommand"
python3 -c "from fourtop.jobs import JobSubmitter, BatchJobSubmitter"
```
