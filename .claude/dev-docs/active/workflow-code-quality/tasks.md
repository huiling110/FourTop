# Tasks: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02 13:55
**Status**: Phases 1-3C Complete, Phase 3E Complete, Phase 3D (1tau1l Full Workflow Test) In Progress

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

## Phase 2B: Script Modifications - COMPLETE ✅

- ✅ Add --config to writeDatacard.py
- ✅ Add --config to addTemplateNew.py
- ✅ Add --config to addJESTemplatesToHistFile.py
- ✅ Add --config to smooth_systematics_fourTops.py
- ✅ Add --config to writeCombinationDatacard.py (in hua/combine/)

---

## Phase 2C: Master Workflow Script - COMPLETE ✅

- ✅ Create run_workflow.py skeleton with argparse
- ✅ Implement Stage 4 runners (4.1, 4.2, 4.2.5, 4.3, 4.4)
- ⏸️ Stage 3 runners deferred (not needed for current workflow)
- ✅ Add config versioning commands (--save-version, --list-stages)

---

## Phase 2D: Testing - COMPLETE ✅

- ✅ Test individual scripts with --config
  - addJESTemplatesToHistFile.py: Works (JES paths need config update for v9 version)
  - addTemplateNew.py: Works
  - writeDatacard.py: Works (datacard generated successfully)
  - writeCombinationDatacard.py: Works (requires cmsenv for combineCards.py)
- ✅ Test full workflow for 1tau0l channel
  - Stages 4.2-4.4 functional with --config
  - Stage 4.1 needs JES path pattern fix (separate issue)

---

## Phase 3: Full End-to-End Workflow (1tau1l Channel) - IN PROGRESS

### Phase 3A: Extend run_workflow.py with Stage 3 - COMPLETE ✅
- ✅ Task 3A.1: Add Stage 3.3 definition (nominal job submission)
- ✅ Task 3A.2: Add Stage 3.3.1 definition (shape systematic jobs)
- ✅ Task 3A.3: Add Stage 3.4 definition (job monitoring)
- ✅ Task 3A.4: Implement `run_stage_3_3()` - nominal jobs
- ✅ Task 3A.5: Implement `run_stage_3_3_1()` - systematic jobs
- ✅ Task 3A.6: Implement `run_stage_3_4()` - job monitor using hep_q
- ✅ Task 3A.7: Add comprehensive logging

### Phase 3B: Create 1tau1l Configuration - COMPLETE ✅
- ✅ Task 3B.1: Create config/analysis_config_1tau1l.yaml
- ✅ Task 3B.2: Configure regions, smoothing, combination version

### Phase 3C: Add Logging System - COMPLETE ✅
- ✅ Task 3C.1: Create setup_logging() function (file + console logging)
- ✅ Task 3C.2: Add --log-file argument
- ✅ Task 3C.3: Log all stages with timestamps and duration

### Phase 3E: Add Complete Workflow Stages (4.5, 4.6) - COMPLETE ✅
- [x] Task 3E.1: Add Stage 4.5 (runCombineAll.py) to run_workflow.py
- [x] Task 3E.2: Add Stage 4.6 (fit plots) to run_workflow.py
- [x] Task 3E.3: Add run_stage_4_5() and run_stage_4_6() functions
- [x] Task 3E.4: Add argparse to pl_postFit.py (--config, --plot-type, --fit-file)
- [x] Task 3E.5: Add pre-fit plotting capability to pl_postFit.py
- [x] Task 3E.6: Add --no-combine, --no-plots, --combine-steps, --blind flags
- [x] Task 3E.7: Add permissions to .claude/settings.json for dev-docs auto-approve

### Phase 3D: Full Pipeline Test (1tau1l) - IN PROGRESS
- [x] Task 3D.0: Add parallel systematic submission (run_stage_3_3_1_parallel)
- [x] Task 3D.0.1: Add --stage all for full pipeline (run_full_pipeline)
- 🔄 Task 3D.1: Run Stage 3 (job submission) - currently running in background
- [ ] Task 3D.2: Wait for job completion
- [ ] Task 3D.3: Run Stage 4 (templates → datacards → combine)
- [ ] Task 3D.4: Verify results match previous 1tau1l

**Performance Discovery**:
- makeJob_WH_forJES.py takes ~34 min/era (68 variations × 30s each)
- Sequential submission: ~2h for Stage 3.3.1
- Parallel submission: ~35 min for Stage 3.3.1 (4x speedup)

---

## Success Criteria

- [x] Config directory structure created
- [x] analysis_config.yaml created with current settings
- [x] Version snapshot saved
- [x] workflow_utils.py created
- [x] All plotting scripts accept --config flag
- [x] run_workflow.py executes all stages
- [x] Full workflow test passes (Stages 4.2-4.4 verified)
- [ ] Full validation with result plots verified (Phase 3)

---

## Notes

- 2025-12-02: Phase 1 complete
- 2025-12-02: Phase 2A started - config system created
- User preferences: YAML config, versioned files, single master script
- CLAUDE.md updated with "no compact after dev-docs update" rule
