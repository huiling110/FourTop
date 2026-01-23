---
paths:
  - "hua/**/*.py"
  - "plotting/**/*.py"
  - "makeVariables_goodCode/**/*.py"
  - "writeHistGood/**/*.py"
  - "objectSelectionOptimized/**/*.py"
  - "scripts/**/*.py"
  - "fourtop/**/*.py"
  - "run_workflow.py"
---

# Python Import Rules - MUST FOLLOW

## NEVER do this
```python
import sys
sys.path.insert(0, '...')  # NEVER
import usefulFunc as uf     # NEVER - use fourtop.utils
import ttttGlobleQuantity as gq  # NEVER - use fourtop.constants
from workflow_utils import ...   # NEVER - use fourtop.workflow
```

## ALWAYS do this
```python
from fourtop.workflow import load_config, build_hist_path, get_channel, get_eras
from fourtop.utils import checkMakeDir, isData, getHistFromFile, getSumHist
from fourtop.utils.process import getSumListFull, getAllSubPro, getEraFromDir
from fourtop.constants import lumiMap, MCSYS, JESVariationList
from fourtop.constants.samples import histoGramPerSample
from fourtop.plotting.style import setTDRStyle, addCMSTextToPad
from fourtop.stage4.datacards import getSysDic, getProSysDicForPlotting
```

## Module purposes
| Need | Import from |
|------|-------------|
| Config, paths | `fourtop.workflow` |
| File I/O, dirs | `fourtop.utils.io` |
| Process filtering | `fourtop.utils.process` |
| Histograms | `fourtop.utils.histogram` |
| Physics constants | `fourtop.constants.physics` |
| Sample mappings | `fourtop.constants.samples` |
| Systematics | `fourtop.constants.systematics` |
| JES sources | `fourtop.constants.jes` |
| Era mapping | `fourtop.constants.era` |
| ROOT styling | `fourtop.plotting.style` |
| Datacards | `fourtop.stage4.datacards` |

## When writing new Python scripts
1. Check if function already exists in fourtop package before implementing
2. Add new reusable functions to appropriate fourtop module
3. Use type hints for new functions
4. For full API: `/python-package-guide`
