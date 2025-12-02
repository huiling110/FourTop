# Tasks: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02
**Status**: Phase 2A - Complete, Phase 2B - Ready to Start

---

## Phase 1: Code Quality Fixes - COMPLETE ✅

- ✅ Task 1.1: Fix duplicate function in smooth_systematics_fourTops.py
- ✅ Task 1.2: Add --quiet to writeDatacard.py
- ✅ Task 1.3: Add --quiet to addTemplateNew.py
- ✅ Task 1.4: Add --quiet to smooth_systematics_fourTops.py

**Commits**: 36726cea, 8759883a

---

## Phase 2A: Configuration System - COMPLETE ✅

- ✅ Task 2A.1: Create config/ directory structure
- ✅ Task 2A.2: Create config/analysis_config.yaml with v9BDT1tau0l settings
- ✅ Task 2A.3: Create version snapshot (config/versions/config_v9BDT1tau0l_CMSNamingComplete.yaml)
- ✅ Task 2A.4: Create plotting/workflow_utils.py

**Commits**: 238f2e68, (pending commit for workflow_utils.py)

**Functions created**:
- `load_config()` - Load YAML config with validation
- `build_hist_path()` - Build histogram directory path
- `build_combine_path()` - Build combine directory path
- `build_template_path()` - Build template ROOT file path
- `build_datacard_path()` - Build datacard output directory
- `get_template_suffix()` - Build suffix based on config options

---

## Phase 2B: Script Modifications - IN PROGRESS

- ✅ Add --config to writeDatacard.py
- ✅ Add --config to addTemplateNew.py
- [ ] Add --config to addJESTemplatesToHistFile.py
- [ ] Add --config to smooth_systematics_fourTops.py
- [ ] Add --config to writeCombinationDatacard.py

---

## Phase 2C: Master Workflow Script - NOT STARTED

- [ ] Create run_workflow.py skeleton with argparse
- [ ] Implement Stage 4 runners (4.1-4.4)
- [ ] Implement Stage 3 runners (3.3-3.4)
- [ ] Add config versioning commands

---

## Phase 2D: Testing - NOT STARTED

- [ ] Test individual scripts with --config
- [ ] Test full workflow for 1tau0l channel

---

## Success Criteria

- [x] Config directory structure created
- [x] analysis_config.yaml created with current settings
- [x] Version snapshot saved
- [x] workflow_utils.py created
- [ ] All plotting scripts accept --config flag
- [ ] run_workflow.py executes all stages
- [ ] Full workflow test passes

---

## Notes

- 2025-12-02: Phase 1 complete
- 2025-12-02: Phase 2A started - config system created
- User preferences: YAML config, versioned files, single master script
- CLAUDE.md updated with "no compact after dev-docs update" rule
