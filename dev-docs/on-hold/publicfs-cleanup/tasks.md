# Tasks: Safe Cleanup of /publicfs File Quota

**Created**: 2025-11-27 11:30
**Last Updated**: 2025-11-27 17:20
**Status**: 🚀 Phase 3 In Progress - Cleanup executing (50% complete)

---

## ✅ Phase 1: Create Unified Survey + Cleanup Script (COMPLETE)

### Task 1.1: Write manage_systematic_histograms.py script
- [x] Design script architecture (survey + cleanup modes)
- [x] Implement survey mode:
  - [x] Scan for nominal `variableHists_v*` directories
  - [x] Import `find_systematic_directories()` from existing script
  - [x] Count files in each systematic directory
  - [x] Check consolidation status (heuristic)
  - [x] Generate CSV report
- [x] Implement cleanup mode:
  - [x] Filter by version, era, consolidation, min_files
  - [x] Import `cleanup_systematic_histogram_directory()` from existing script
  - [x] Implement dry-run default
  - [x] Require explicit --execute flag
  - [x] Add confirmation prompt for large deletions
- [x] Add argparse CLI
- [x] Add logging functionality
- [x] Add quota tracking (before/after)
- [x] Make script executable

**Script location**: `plotting/manage_systematic_histograms.py`

---

## ✅ Phase 1.5: Create Additional Survey and Cleanup Tools (COMPLETE)

### Task 1.2: Create survey_all_files.py
- [x] Design comprehensive file type survey (ROOT, log, jobSH, other)
- [x] Implement file counting by subdirectory type
- [x] Generate CSV report with breakdown
- [x] Make script executable

**Script location**: `plotting/survey_all_files.py`

### Task 1.3: Create cleanup_logs_jobsh.py
- [x] Design log/jobSH cleanup script
- [x] Implement ZIP mode for log/ directories (preserves while freeing quota)
- [x] Implement DELETE mode for jobSH/ directories (regenerable)
- [x] Add survey and cleanup modes
- [x] Add --yes flag for automation
- [x] Make script executable

**Script location**: `plotting/cleanup_logs_jobsh.py`

---

## ✅ Phase 2: Run Comprehensive Surveys (COMPLETE)

### Task 2.1: Survey systematic histograms
- [x] Run manage_systematic_histograms.py --output cleanup_report.csv
- [x] Found 46,292 files in systematic directories (only 5% of problem)

### Task 2.2: Survey ALL files by type
- [x] Created survey_all_files.py script
- [x] Ran comprehensive file type survey
- [x] Identified actual problem: log/ (193K files) + jobSH/ (82K files) = 275K files

### Task 2.3: Survey log/jobSH directories
- [x] Created cleanup_logs_jobsh.py script
- [x] Ran survey mode to identify 1,636 histogram directories with log/jobSH
- [x] Confirmed 274,876 files ready for cleanup

### Task 2.4: Get user approval
- [x] Presented findings: log/jobSH are 6x larger problem than systematic histograms
- [x] User approved cleanup strategy: ZIP log/, DELETE jobSH/
- [x] User approved execution

---

## 🚀 Phase 3: Execute Cleanup (IN PROGRESS - 50% complete)

### Task 3.1: Dry-run cleanup
- [x] Ran: `python3 cleanup_logs_jobsh.py --cleanup --dry-run`
- [x] Verified: 273,241 files would be freed
- [x] User approved execution

### Task 3.2: Add --yes flag for automation
- [x] Modified script to add --yes flag (skip confirmation prompt)
- [x] Tested --yes flag works correctly
- [x] Committed changes to git

### Task 3.3: Execute cleanup
- [x] Started: `python3 cleanup_logs_jobsh.py --cleanup --execute --yes`
- [x] Running since 2025-11-27 13:55 (3h 25m so far)
- [ ] **IN PROGRESS**: Processing 1,636 directories
  - Current progress: 143,071 files freed (50%)
  - Current quota: 827,482 files (82.7%, down from 97%)
  - Remaining: 127,482 files to free
  - Expected completion: ~4-5 more hours

### Task 3.4: Monitor cleanup progress
- [x] Set up background monitor script
- [ ] **WAITING**: Monitor will notify when complete

---

## Phase 4: Verification & Documentation (PENDING)

### Task 4.1: Final verification
- [ ] Check final quota: `lfs quota -u huahuil /publicfs`
- [ ] Verify target reached (< 700K files, < 70%)
- [ ] Test job submission for v9BDT (one small test job)

### Task 4.2: Document results
- [ ] Update plan.md with final results
- [ ] Update tasks.md to mark all tasks complete
- [ ] Document cleanup scripts in ANALYSIS_WORKFLOW.md Stage 3.4
- [ ] Archive dev-docs to completed/ if task finished

---

## ✅ Phase 5: Create Dev-Docs Infrastructure (COMPLETE)

### Task 5.1: Create slash commands for dev-docs workflow
- [x] Created `/create-dev-docs` command
  - Gathers context efficiently
  - Analyzes project structure
  - Creates comprehensive plans with phases, tasks, risks
  - Generates plan.md, context.md, tasks.md automatically
- [x] Created `/show-plans` command
  - Lists all active dev-docs with status
- [x] Created `/update-dev-docs` command
  - Updates progress in dev-docs
  - **Requires git commit first** (ensures docs reflect committed state)
- [x] Created `/resume-task [task-name]` command
  - Resume active task from dev-docs with full context
  - Loads plan, context, tasks
  - Sets up TodoWrite automatically

### Task 5.2: Commit dev-docs infrastructure
- [x] Commit slash commands to git
- [x] Commit dev-docs for publicfs-cleanup task
- [x] Commit dev-docs for gitlab-ci-1tau0l-validation task

**Locations**:
- `.claude/commands/` - 4 slash commands
- `.claude/dev-docs/active/publicfs-cleanup/` - This task's docs
- `.claude/dev-docs/active/gitlab-ci-1tau0l-validation/` - Previous task docs

---

## Success Criteria

- 🚧 File quota below 70% (< 700K files) - **IN PROGRESS: 50% complete, currently at 82.7%**
- ✅ Three production-ready cleanup scripts created and committed
- ✅ Dev-docs infrastructure with 4 slash commands created
- ⏳ Can submit v9BDT1tau0l_CMSNamingComplete production jobs - **PENDING: After cleanup**
- ✅ All active analysis versions preserved (only log/jobSH cleaned, not ROOT files)
- ✅ Systematic templates intact in nominal files (not touched by cleanup)
- 🚧 Documentation complete - **PENDING: ANALYSIS_WORKFLOW.md update after cleanup**

---

## Notes

- Script is at `plotting/manage_systematic_histograms.py`
- Always run dry-run first, review carefully before --execute
- Check quota after each version cleanup
- Keep cleanup logs for reference
- If quota still >70% after Phase 3, may need to delete old obsolete versions entirely (Phase 4 in plan.md)

---

**Next action**: Run survey to identify cleanup candidates
