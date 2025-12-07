# Plan: FourTop Workflow Automation

**Created**: 2025-12-02
**Status**: Phase 3E COMPLETE, Phase 3D Testing - Stage 4.4/4.5 Blocked
**Priority**: HIGH
**Last Updated**: 2025-12-02 14:55

---

## Executive Summary

Create a complete workflow automation system for the FourTop analysis, covering Stage 3 (histogram production) through Stage 4 (combine results). Uses versioned YAML configuration files and a single master script for running the entire workflow.

---

## Phase 1 Status: COMPLETE ✅

- Fixed duplicate function in smooth_systematics_fourTops.py
- Added --quiet flag to writeDatacard.py, addTemplateNew.py, smooth_systematics_fourTops.py
- All scripts tested and committed (36726cea, 8759883a)

---

## Phase 2: Workflow Automation System - COMPLETE ✅

### Architecture

```
FourTop/
├── config/
│   ├── analysis_config.yaml          # Current active configuration
│   ├── versions/                     # Historical configs
├── run_workflow.py                   # Master workflow script
└── plotting/
    ├── workflow_utils.py             # Shared config loading utilities
```

---

## Phase 3: Full End-to-End Workflow - IN PROGRESS

### Phase 3A: Extend run_workflow.py with Stage 3 - COMPLETE ✅
### Phase 3B: Create 1tau1l Configuration - COMPLETE ✅
### Phase 3C: Add Logging System - COMPLETE ✅
### Phase 3E: Add Complete Workflow Stages (4.5, 4.6) - COMPLETE ✅

### Phase 3D: Full Pipeline Test - IN PROGRESS (BLOCKED)

**Status**: Stage 4.4/4.5 blocked - need to add missing stages

**Completed**:
- Stage 3 (histogram jobs): ✅ All jobs completed
- Stage 4.1 (consolidate systematics): ✅
- Stage 4.2 (create templates): ✅
- Stage 4.2.5 (smooth systematics): ✅
- Stage 4.3 (write datacards): ✅

**Blocked**:
- Stage 4.4 (combine datacards): Need to add Stage 4.3.2 and 4.3.5
- Stage 4.5 (combine analysis): Waiting on 4.4

**Missing Stages Identified**:
- Stage 4.3.2: Copy per-era datacards to combine directory
- Stage 4.3.5: Combine region datacards (if applicable)

---

## Code Quality Improvements (Session 2)

### Completed:
1. **run_workflow.py refactoring** (commit 0151d378)
   - Extracted `create_parser()`, `handle_special_commands()`, `load_workflow_config()`
   - Reduced main() from 157 lines to ~20 lines
   - Reduced run_stage() nesting from 7 to 3 levels using dispatch tables
   - All quality errors fixed (0 errors, 5 warnings)

2. **Output path logging** (commit 61cb0287)
   - Added `get_output_paths()` function
   - Each stage logs output file path after completion
   - Added 'impacts' to default Stage 4.5 steps

3. **Quiet mode fixes for addJESTemplatesToHistFile.py** (commit 61cb0287)
   - Added global QUIET flag
   - Wrapped verbose print statements
   - Significantly reduces token usage when running with Claude

4. **Stage 4.2.5 fix** (commit 61cb0287)
   - Changed from per-era to global stage
   - Matches actual script behavior

5. **Config fixes** (commit ac3aa7e4)
   - Updated datacard_version to match existing files
   - Fixed combination config structure

### Pending:
- Refactor pl_postFit.py (7 errors, 11 warnings)

---

## Recent Commits

```
ac3aa7e4 fix: Update config to use correct datacard and combination paths
61cb0287 feat: Add output path logging and fix Stage 4.2.5 + quiet mode
0151d378 refactor: Improve run_workflow.py code quality and add review tools
146978c5 perf: Add parallel submission for systematic jobs (Stage 3.3.1)
```

---

## Next Steps

1. **Add missing stages 4.3.2 and 4.3.5** to run_workflow.py
2. **Complete Stage 4.4/4.5** testing
3. **Refactor pl_postFit.py** to pass quality checks
4. **Document final workflow** in ANALYSIS_WORKFLOW.md
