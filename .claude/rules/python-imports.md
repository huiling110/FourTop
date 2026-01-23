---
paths:
  - "hua/**/*.py"
  - "plotting/**/*.py"
  - "makeVariables_goodCode/**/*.py"
  - "writeHistGood/**/*.py"
  - "objectSelectionOptimized/**/*.py"
  - "scripts/**/*.py"
  - "fourtop/**/*.py"
---

# Python Import Conventions

Use `fourtop` package for all imports. Never use `sys.path` hacks.

## Quick Imports

```python
from fourtop.workflow import load_config, build_hist_path, get_channel, get_eras
from fourtop.utils import checkMakeDir, isData, getHistFromFile
from fourtop.constants import lumiMap, MCSYS, JESVariationList
```

## For full API reference

Invoke `/python-package-guide` skill.
