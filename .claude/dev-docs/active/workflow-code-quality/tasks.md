# Tasks: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02
**Status**: Phase 2A - Starting

---

## Phase 1: Code Quality Fixes - COMPLETE ✅

### Task 1.1: Fix duplicate function - COMPLETE
### Task 1.2: Add --quiet to writeDatacard.py - COMPLETE
### Task 1.3: Add --quiet to addTemplateNew.py - COMPLETE
### Task 1.4: Add --quiet to smooth_systematics_fourTops.py - COMPLETE

**Commits**: 36726cea, 8759883a

---

## Phase 2A: Configuration System

### Task 2A.1: Create config/ directory structure
- [ ] Create `config/` directory
- [ ] Create `config/versions/` subdirectory

**Status**: In Progress

### Task 2A.2: Create analysis_config.yaml
- [ ] Create YAML with current v9BDT1tau0l settings

**Status**: Not Started

### Task 2A.3: Create workflow_utils.py
- [ ] Implement load_config(), build_hist_path(), build_template_path()

**Status**: Not Started

---

## Phase 2B: Script Modifications

### Task 2B.1-2B.5: Add --config to plotting scripts
- [ ] writeDatacard.py
- [ ] addTemplateNew.py
- [ ] addJESTemplatesToHistFile.py
- [ ] smooth_systematics_fourTops.py
- [ ] writeCombinationDatacard.py

**Status**: Not Started

---

## Phase 2C: Master Workflow Script

### Task 2C.1: Create run_workflow.py
- [ ] Stage 4 runners (4.1-4.4)
- [ ] Stage 3 runners (3.3-3.4)
- [ ] Config versioning commands

**Status**: Not Started

---

## Phase 2D: Testing

- [ ] Test full workflow for 1tau0l channel

---

## Notes

- 2025-12-02: Phase 1 complete, starting Phase 2
