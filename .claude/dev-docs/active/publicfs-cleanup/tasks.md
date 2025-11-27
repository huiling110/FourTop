# Tasks: Safe Cleanup of /publicfs File Quota

**Created**: 2025-11-27 11:30
**Last Updated**: 2025-11-27 14:00
**Status**: 🚀 Phase 4 In Progress - Executing cleanup

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

## Phase 2: Run Survey and Analyze (30 min - NEXT)

### Task 2.1: Run survey script
- [ ] cd plotting/
- [ ] source ../setEnv_newNew.sh
- [ ] python3 manage_systematic_histograms.py --output cleanup_report.csv
- [ ] Wait for scan to complete (may take 5-10 minutes)

### Task 2.2: Review survey report
- [ ] Open cleanup_report.csv
- [ ] Identify versions with highest file counts
- [ ] Check which versions are marked as consolidated
- [ ] Make note of top 10-20 cleanup candidates

### Task 2.3: Get user approval for cleanup targets
- [ ] Present top candidates to user
- [ ] Confirm which versions are safe to clean
- [ ] Prioritize by file count (highest impact first)
- [ ] Document approved versions

---

## Phase 3: Execute Cleanup (2-3 hours)

### Task 3.1: Dry-run cleanup for first approved version
- [ ] cd plotting/
- [ ] source ../setEnv_newNew.sh
- [ ] Run: `python3 manage_systematic_histograms.py --cleanup --version [VERSION] --dry-run`
- [ ] Review output: number of files to be deleted, space to be freed

### Task 3.2: Execute cleanup for first version
- [ ] Verify dry-run results look correct
- [ ] Run: `python3 manage_systematic_histograms.py --cleanup --version [VERSION] --execute`
- [ ] Confirm deletion when prompted
- [ ] Monitor progress
- [ ] Check quota: `lfs quota -u huahuil /publicfs`

### Task 3.3: Verify cleanup success
- [ ] Check log file for any errors
- [ ] Verify quota reduction matches expectations
- [ ] Verify nominal histogram files still intact
- [ ] Record files deleted in this document

### Task 3.4: Repeat for other approved versions
- [ ] For each version: dry-run → review → execute → verify
- [ ] Track cumulative file reduction
- [ ] Stop when file quota < 70% (700K files)

---

## Phase 4: Verification & Documentation (30 min)

### Task 4.1: Final verification
- [ ] Check final quota: `lfs quota -u huahuil /publicfs`
- [ ] Verify target reached (< 700K files, < 70%)
- [ ] Test job submission for v9BDT (one small test job)

### Task 4.2: Document results
- [ ] Update plan.md with:
  - List of versions cleaned
  - Files deleted per version
  - Total files freed
  - Final quota status
- [ ] Update tasks.md to mark all tasks complete
- [ ] Archive dev-docs to completed/ if task finished

---

## Success Criteria

- ✅ File quota below 70% (< 700K files)
- ✅ Can submit v9BDT1tau0l_CMSNamingComplete production jobs
- ✅ All active analysis versions preserved
- ✅ Systematic templates intact in nominal files
- ✅ Documentation complete

---

## Notes

- Script is at `plotting/manage_systematic_histograms.py`
- Always run dry-run first, review carefully before --execute
- Check quota after each version cleanup
- Keep cleanup logs for reference
- If quota still >70% after Phase 3, may need to delete old obsolete versions entirely (Phase 4 in plan.md)

---

**Next action**: Run survey to identify cleanup candidates
