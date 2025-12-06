# Future Refactoring Tasks

**Created**: 2025-12-06
**Related to**: TTBB Integration & General Code Quality

---

## Python Script Refactoring

### Priority 1: pl.py (Plotting Script)
- [ ] **Extract hardcoded paths to YAML config** (partially done)
- [ ] **Add command-line argument support** for all options (partially done)
- [ ] **Split into modules**: separate plotting logic from data loading
- [ ] **Add docstrings** to all functions
- [ ] **Reduce function length**: `makeStackPlotNew()` and `getHists()` are too long
- [ ] **Create config dataclass** for plot settings (ifLogy, ifStackSignal, etc.)

### Priority 2: Other Plotting Scripts
- [ ] `plotting/writeDatacard.py` - Add YAML config support
- [ ] `plotting/usefulFunc.py` - Document utility functions
- [ ] `plotting/smooth_systematics_fourTops.py` - Add argparse

### Priority 3: Job Scripts
- [ ] `objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py` - Clean up path handling
- [ ] `makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py` - Standardize with YAML
- [ ] `writeHistGood/jobs/makeJob_forWriteHist.py` - Already uses YAML, add more options

### Priority 4: Analysis Scripts
- [ ] `hua/src_py/ttttGlobleQuantity.py` - Convert to YAML-based configuration
- [ ] `hua/combine/*.py` - Standardize argument handling

---

## Claude Code Configuration

### Hooks (to remember structure)
- [ ] Create `.claude/hooks/pre-tool-use.sh` for environment validation
- [ ] Create `.claude/hooks/post-tool-use.sh` for code quality checks (exists, extend)
- [ ] Add hook to auto-update dev-docs on significant changes

### Skills (custom capabilities)
- [ ] Create `refactor` skill for Python code quality improvements
- [ ] Create `run-analysis` skill for running full pipeline stages
- [ ] Create `validate-physics` skill for checking histogram integrals/event counts

### Settings Enhancements
- [ ] Add more allowed bash commands to `.claude/settings.json`
- [ ] Configure auto-context loading for dev-docs
- [ ] Set up project-specific MCP servers if needed

---

## Code Style Standards (for refactoring reference)

### Python Scripts
- Max function length: 80 lines
- Max nesting depth: 5 levels
- Max cyclomatic complexity: 20
- Use argparse for CLI scripts
- Use YAML for configuration
- Add type hints where beneficial

### Naming Conventions
- Functions: `snake_case`
- Classes: `PascalCase`
- Constants: `UPPER_SNAKE_CASE`
- Files: `snake_case.py`

---

## Notes

- The refactoring skill already exists in `.claude/skills/refactor.md`
- Current hooks check Python code quality after edits
- YAML config pattern established in `config/analysis_config_1tau0l_full.yaml`
