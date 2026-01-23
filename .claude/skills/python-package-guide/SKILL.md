---
name: python-package-guide
description: FourTop Python package structure, API reference, and import conventions. Use when working with fourtop/ modules, implementing utilities, or checking package API.
user-invocable: true
---

# FourTop Python Package Guide

## Quick Reference

| Package | Purpose | Example Import |
|---------|---------|----------------|
| `fourtop.constants` | Physics data, samples, systematics | `from fourtop.constants import lumiMap, MCSYS` |
| `fourtop.utils` | File I/O, histograms, process filtering | `from fourtop.utils import checkMakeDir, isData` |
| `fourtop.workflow` | Config loading, path building | `from fourtop.workflow import load_config` |
| `fourtop.plotting` | ROOT styling, stack plots | `from fourtop.plotting import setTDRStyle` |
| `fourtop.stage4` | Templates, datacards, combine | `from fourtop.stage4 import getSysDic` |
| `fourtop.jobs` | Job submission base classes | `from fourtop.jobs import JobSubmitter` |

## Package Structure

```
fourtop/
├── constants/
│   ├── era.py          # ERAS, VFP_ERAS, ERA_TO_UL, map_vfp_era()
│   ├── jes.py          # JESVariationList, SKIP_SUBPROCESSES
│   ├── physics.py      # lumiMap, crossSectionMap
│   ├── samples.py      # histoGramPerSample, proChannelDic
│   └── systematics.py  # MCSYS (82 entries), get_systematics_for_channel()
├── utils/
│   ├── io.py           # checkMakeDir, runCommand, getDirDic
│   ├── process.py      # isData, isBG, getAllSubPro, getSumListFull
│   ├── histogram.py    # getHistFromFile, getSumHist, handle_negative_bins
│   └── logging.py      # setup_logger, get_logger
├── workflow/
│   ├── config.py       # load_config, get_channel, get_eras
│   ├── paths.py        # build_hist_path, build_template_path, build_datacard_path
│   └── state.py        # WorkflowState class
├── plotting/
│   ├── stack.py        # getHists, getErrorPlot, COLOUR_PER_SAMPLE
│   └── style.py        # setTDRStyle, addCMSTextToPad, getMyLegend
├── stage4/
│   ├── templates.py    # resetNegativeBins, addDataHist, TemplateBuilder
│   ├── datacards.py    # getSysDic, addLumi, getProSysDicForPlotting
│   ├── systematics.py  # addJESToFile, addTESToFile, addMETToFile
│   └── combine.py      # cardToWorkspaces, runCommand
└── jobs/
    └── base.py         # JobSubmitter, BatchJobSubmitter
```

## Module Details

### fourtop.constants

```python
from fourtop.constants.physics import lumiMap, crossSectionMap
from fourtop.constants.samples import histoGramPerSample, proChannelDic
from fourtop.constants.systematics import MCSYS, get_systematics_for_channel
from fourtop.constants.jes import JESVariationList, SKIP_SUBPROCESSES, validate_jes_list
from fourtop.constants.era import ERAS, VFP_ERAS, ERA_TO_UL, map_vfp_era
```

### fourtop.utils

```python
from fourtop.utils.io import checkMakeDir, runCommand, getDirDic, getInputDicNew
from fourtop.utils.process import isData, isBG, getAllSubPro, getSumListFull, getEraFromDir
from fourtop.utils.histogram import getHistFromFile, getSumHist, handle_negative_bins
from fourtop.utils.logging import setup_logger, get_logger
```

### fourtop.workflow

```python
from fourtop.workflow import (
    load_config, get_channel, get_eras, get_options, get_regions,
    build_hist_path, build_template_path, build_datacard_path,
    build_stage1_output, build_stage2_output, build_combine_path,
    ERA_TO_UL, ERA_TO_NANOAOD
)
```

### fourtop.plotting

```python
from fourtop.plotting.style import setTDRStyle, setMyStyle, addCMSTextToPad, getMyLegend
from fourtop.plotting.stack import getHists, getErrorPlot, COLOUR_PER_SAMPLE
```

### fourtop.stage4

```python
from fourtop.stage4.templates import resetNegativeBins, addDataHist, TemplateBuilder
from fourtop.stage4.datacards import getSysDic, addLumi, getProSysDicForPlotting
from fourtop.stage4.systematics import addJESToFile, addTESToFile, addMETToFile
from fourtop.stage4.combine import cardToWorkspaces, runCommand
```

## Coding Guidelines

1. **Always use fourtop package** - Never add `sys.path` hacks
2. **Config-driven paths** - Use `build_*_path()` functions, never hardcode
3. **Reuse constants** - Check `fourtop.constants/` before defining new values
4. **Type hints required** - All new functions need type hints
5. **Logging not print** - Use `fourtop.utils.logging` for new code

## Migration Pattern

Replace legacy imports:
```python
# OLD (remove)
import sys
sys.path.insert(0, '...')
from workflow_utils import load_config
import ttttGlobleQuantity as gq
import usefulFunc as uf

# NEW (use)
from fourtop.workflow import load_config
from fourtop.constants import samples, physics
from fourtop.utils import checkMakeDir, isData
```

## Test Commands

```bash
source setEnv_newNew.sh
python3 -c "from fourtop.constants import lumiMap, MCSYS, JESVariationList"
python3 -c "from fourtop.utils import checkMakeDir, isData, getHistFromFile"
python3 -c "from fourtop.workflow import load_config, build_hist_path"
python3 -c "from fourtop.plotting import setTDRStyle, getHists"
python3 -c "from fourtop.stage4 import getSysDic, addJESToFile"
```
