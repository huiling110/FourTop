# CLAUDE.md - FourTop Analysis

## Project Overview

**CMS four-top (tttt) measurement and VLL search in hadronic tau channels**

| Channel | Description | Trigger |
|---------|-------------|---------|
| 1tau0l | 1 hadronic tau, 0 leptons | HT-based (shared) |
| 1tau1l | 1 hadronic tau, 1 lepton | HT-based (shared) |
| 1tau2l | 1 hadronic tau, 2 leptons | Different trigger |

**Note**: 1tau0l and 1tau1l share OS and MV steps (same triggers).

## Critical Rules

1. **Config-driven** - Always `--config CONFIG --era ERA`, never hardcode paths
2. **Environment** - `source setEnv_newNew.sh` (combine: `cmsenv`)
3. **Regenerate fakes** - Never copy fake tau/lepton files between versions
4. **ALWAYS invoke stage skill first** - Before ANY stage work, ASK: "Which stage am I in?" then invoke `/workflow-stage{1-4}*`. This applies to:
   - Running stage commands (submit jobs, run combine, etc.)
   - Checking stage outputs or paths
   - Debugging stage issues
   - Continuing interrupted stage work
5. **Commit often** - After each significant change
6. **Dev-docs for new tasks** - After exiting plan mode, create `dev-docs/active/{task}/` with:
   - `context.md` - Goal, key paths, environment, critical notes
   - `plan.md` - Implementation approach, dependencies, risks
   - `tasks.md` - Status table, session notes, next steps

## Workflow

**Stage skills** (invoke for commands, paths, verification):
- `/workflow-stage1-os` - Object Selection
- `/workflow-stage2-mv` - Make Variables + Fakes
- `/workflow-stage3-wh` - Write Histograms
- `/workflow-stage4-combine` - Templates, Datacards, Combine

**Progress tracking**: `dev-docs/active/{task}/tasks.md` with status table

**Config**: `config/analysis_config_{channel}_*.yaml`

## Dev-Docs

For multi-session tasks in `dev-docs/active/{task}/`:
- Read `tasks.md` to resume
- Update frequently, commit often
- When context low, update dev-docs before ending

## User Preferences

- Physicist, experienced developer
- Direct feedback, explain *why* not just *how*
- Physics safety: watch for sign errors, branch bugs

## Python Package Structure

The `fourtop/` package provides centralized utilities for the analysis.

### Setup
```bash
source setEnv_newNew.sh  # Sets PYTHONPATH
```

### Constants (`fourtop.constants`)

| Module | Purpose | Key Exports |
|--------|---------|-------------|
| `physics` | Cross sections, luminosity | `lumiMap`, `crossSectionMap` |
| `samples` | Process mappings | `histoGramPerSample`, `proChannelDic`, `proChannelDic_forCombine` |
| `systematics` | Systematic definitions | `MCSYS`, `get_systematics_for_channel()` |
| `jes` | JES configuration | `JESVariationList`, `SKIP_SUBPROCESSES`, `validate_jes_list()` |
| `era` | Era mappings | `map_vfp_era()`, `VFP_ERAS`, `ERA_TO_UL` |

**Usage:**
```python
from fourtop.constants import lumiMap, crossSectionMap, MCSYS
from fourtop.constants.jes import JESVariationList, validate_jes_list
from fourtop.constants.era import map_vfp_era, ERAS
```

### Utilities (`fourtop.utils`)

| Module | Purpose | Key Functions |
|--------|---------|---------------|
| `io` | File operations | `checkMakeDir()`, `runCommand()` |
| `histogram` | Histogram ops | `getHistFromFile()`, `handle_negative_bins()`, `addBGHist()` |
| `process` | Process helpers | `isData()`, `isBG()`, `getSumList()`, `getSubProScale()` |
| `logging` | Logging setup | `setup_logger()` |

**Usage:**
```python
from fourtop.utils import checkMakeDir, isData, getHistFromFile
from fourtop.utils.logging import setup_logger
```

### Workflow (`fourtop.workflow`)

| Module | Purpose | Key Functions |
|--------|---------|---------------|
| `config` | Config loading | `load_config()`, `get_channel()`, `get_eras()`, `get_options()` |
| `paths` | Path builders | `build_hist_path()`, `build_template_path()`, `build_datacard_path()` |
| `state` | State tracking | `WorkflowState` class |

**Usage:**
```python
from fourtop.workflow import load_config, build_hist_path, get_channel
config = load_config('config/analysis_config_1tau0l.yaml')
hist_path = build_hist_path(config, '2018')
```

### Plotting (`fourtop.plotting`)

| Module | Purpose | Key Functions |
|--------|---------|---------------|
| `stack` | Stack plots | `getHists()`, `getErrorPlot()`, `COLOUR_PER_SAMPLE` |

**Usage:**
```python
from fourtop.plotting import getHists, COLOUR_PER_SAMPLE
```

## Import Conventions

```python
# Preferred imports
from fourtop.constants import lumiMap, crossSectionMap, MCSYS
from fourtop.utils import checkMakeDir, isData
from fourtop.workflow import load_config, build_hist_path
from fourtop.plotting import getHists

# Example workflow
config = load_config('config/analysis_config_1tau0l_XGB080test.yaml')
era = '2018'
hist_path = build_hist_path(config, era)
```

## Python Coding Guidelines

1. **Use fourtop package** - Never add sys.path hacks
2. **Config-driven paths** - Use `workflow.paths.build_*()` functions
3. **Reuse constants** - Check `fourtop.constants/` before defining new ones
4. **Reuse process functions** - Use `fourtop.utils.process` for filtering
5. **Type hints encouraged** - For new functions
6. **Logging over print** - Use `fourtop.utils.logging` for debug output
