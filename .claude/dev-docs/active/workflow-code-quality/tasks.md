# Tasks: FourTop Workflow Automation

**Created**: 2025-12-02
**Last Updated**: 2025-12-02 14:55
**Status**: Phase 3D Blocked - Missing stages 4.3.2/4.3.5

---

## Phase 1: Code Quality Fixes - COMPLETE ✅

- [x] Fix duplicate function in smooth_systematics_fourTops.py
- [x] Add --quiet to writeDatacard.py, addTemplateNew.py, smooth_systematics_fourTops.py

**Commits**: 36726cea, 8759883a

---

## Phase 2: Configuration System & Script Modifications - COMPLETE ✅

- [x] Create config/ directory with analysis_config.yaml
- [x] Create workflow_utils.py with path building functions
- [x] Add --config to all plotting scripts
- [x] Create run_workflow.py master script

---

## Phase 3: Full End-to-End Workflow - IN PROGRESS

### Phase 3A-C: Infrastructure - COMPLETE ✅
- [x] Stage 3 runners (3.3, 3.3.1, 3.4)
- [x] Parallel job submission
- [x] 1tau1l configuration
- [x] Logging system

### Phase 3D: Full Pipeline Test - BLOCKED ⚠️
- [x] Stage 3 (histogram jobs) - COMPLETE
- [x] Stage 4.1 (consolidate systematics) - COMPLETE
- [x] Stage 4.2 (create templates) - COMPLETE
- [x] Stage 4.2.5 (smooth systematics) - COMPLETE
- [x] Stage 4.3 (write datacards) - COMPLETE
- [ ] **BLOCKED**: Stage 4.3.2 - (need user clarification)
- [ ] **BLOCKED**: Stage 4.3.5 - (need user clarification)
- [ ] Stage 4.4 (combine datacards) - WAITING
- [ ] Stage 4.5 (combine analysis) - WAITING
- [ ] Stage 4.6 (fit plots) - WAITING

### Phase 3E: Complete Workflow Stages - COMPLETE ✅
- [x] Stage 4.5 (runCombineAll.py) integration
- [x] Stage 4.6 (pl_postFit.py) integration
- [x] Command-line flags: --no-combine, --no-plots, --combine-steps, --blind

---

## Session 2: Code Quality Improvements

### Completed ✅
- [x] Create refactor skill and /review-code command
- [x] Refactor run_workflow.py (main: 157→20 lines, nesting: 7→3)
- [x] Add output path logging to all stage runners
- [x] Fix addJESTemplatesToHistFile.py quiet mode (QUIET global flag)
- [x] Fix Stage 4.2.5 to run as global stage (not per-era)
- [x] Add 'impacts' to default Stage 4.5 steps
- [x] Fix config structure (combination vs combine)

### Pending
- [ ] **Add stages 4.3.2 and 4.3.5** (need user clarification on what these do)
- [ ] Refactor pl_postFit.py (7 errors, 11 warnings)
- [ ] Complete Stage 4.4/4.5/4.6 testing

---

## Recent Commits

| Commit | Description |
|--------|-------------|
| ac3aa7e4 | fix: Update config to use correct datacard and combination paths |
| 61cb0287 | feat: Add output path logging and fix Stage 4.2.5 + quiet mode |
| 0151d378 | refactor: Improve run_workflow.py code quality and add review tools |
| 146978c5 | perf: Add parallel submission for systematic jobs (Stage 3.3.1) |

---

## Quality Check Summary

| File | Errors | Warnings | Status |
|------|--------|----------|--------|
| run_workflow.py | 0 | 5 | ✅ PASS |
| workflow_utils.py | 0 | 0 | ✅ PASS |
| pl_postFit.py | 7 | 11 | ❌ NEEDS REFACTOR |

---

## Blocker: User Clarification Needed

**Question**: What do stages 4.3.2 and 4.3.5 do?
- Stage 4.3.2: Copy datacards to combine directory?
- Stage 4.3.5: Combine region datacards?

Per-era datacards exist at:
```
/publicfs/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt
```

But they need to be copied/combined into:
```
hua/combine/combinationV21/run2_1tau0l_v4_unblind/
```
