# Python System Refactoring - Tasks

## Status Table

| Phase | Task | Status | Notes |
|-------|------|--------|-------|
| **1** | Create branch `refactor-python-system` | pending | |
| **1** | Create `fourtop/` package skeleton | pending | |
| **1** | Update setEnv_newNew.sh | pending | |
| **1** | Move workflow_utils.py | pending | |
| **2** | Extract constants/era.py | pending | VFP mapping consolidation |
| **2** | Extract constants/systematics.py | pending | MCSys dictionary |
| **2** | Split ttttGlobleQuantity.py | pending | physics, samples, jes |
| **3** | Split usefulFunc.py | pending | io, histogram, process |
| **3** | Create utils/logging.py | pending | |
| **4** | Refactor pl.py | pending | HIGH priority |
| **4** | Refactor addTemplateNew.py | pending | |
| **5** | Refactor writeDatacard.py | pending | |
| **5** | Refactor addJESTemplatesToHistFile.py | pending | |
| **5** | Refactor runCombineAll.py | pending | |
| **6** | Create jobs/base.py | pending | |
| **6** | Add type hints | pending | |
| **6** | Update CLAUDE.md | pending | |
| **6** | Create test suite | pending | |

## Session Notes

### Session 1 (2026-01-21)
- Explored Python system: 125 files, ~15,000+ lines
- Identified key duplications (VFP mapping, MCSys, process filtering)
- Created comprehensive refactoring plan
- Key files: pl.py (663 lines), writeDatacard.py (508 lines), workflow_utils.py (721 lines)

## Next Steps

1. Create new branch `refactor-python-system`
2. Generate golden references before any changes
3. Start Phase 1: Package foundation

## Golden Reference Generation

```bash
# Run before any refactoring
for channel in 1tau0l 1tau1l 1tau2l; do
    config="config/analysis_config_${channel}_XGB080test.yaml"
    python3 plotting/addTemplateNew.py --config $config --era 2018
    python3 plotting/writeDatacard.py --config $config --era 2018
done
```

## Commands Reference

```bash
# Test package imports
python3 -c "from fourtop.workflow import config, paths"

# Run validation tests
python3 -m pytest tests/ -v

# Compare ROOT files
python3 tests/compare_root_files.py golden.root new.root
```
