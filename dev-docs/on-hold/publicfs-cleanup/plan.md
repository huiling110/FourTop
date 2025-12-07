# Plan: Safe Cleanup of /publicfs to Free File Quota

**Created**: 2025-11-27 11:20
**Last Updated**: 2025-11-27 17:20
**Status**: 🚀 Cleanup Executing - 50% complete (143K/273K files freed)
**Priority**: HIGH - Blocking new histogram production

---

## Goal

Free up file quota on /publicfs filesystem to allow new histogram production for v9BDT1tau0l_CMSNamingComplete. Current usage is 97% of file limit (970K/1M files).

**Target**: Reduce to <70% (700K files)

---

## Current Situation

**Initial Quota Status** (2025-11-27 13:55):
```
Filesystem  kbytes   quota   limit   grace   files   quota   limit   grace
 /publicfs 8519100240       0 10737418240       -  970553       0 1000000       -
```

**Current Quota Status** (2025-11-27 17:20):
```
Filesystem  kbytes   quota   limit   grace   files   quota   limit   grace
 /publicfs 8517996468       0 10737418240       -  827482       0 1000000       -
```

**Progress**:
- **Initial**: 970,553 files (97.0% used) ⚠️ **CRITICAL**
- **Current**: 827,482 files (82.7% used) 📉 **IMPROVING**
- **Freed**: 143,071 files (50% complete)
- **Target**: <700,000 files (70% quota)
- **Remaining**: 127,482 files to free
- **Disk space**: 8.5TB / 10TB (79% used) - OK
- **Problem**: File number quota, not disk space
- **Root cause**: log/ and jobSH/ directories in 1,636 histogram versions

---

## Cleanup Strategy

### ✅ Implemented Solution: Unified Survey + Cleanup Script

**Script Created**: `plotting/manage_systematic_histograms.py`

**Approach**: Data-driven cleanup using unified tool that can:
1. **Survey mode**: Scan all nominal histogram directories, identify systematic variations, count files → generate CSV report
2. **Cleanup mode**: Filter by version/era/consolidation, cleanup systematic dirs (dry-run default, --execute required)

**Key Features**:
- Reuses existing cleanup functions from `addJESTemplatesToHistFile.py`
- Safe by default (survey is read-only, cleanup defaults to dry-run)
- Flexible filtering (version, era, consolidation status, min files)
- Comprehensive logging and quota tracking
- Confirmation prompt before deletion

**Usage Examples**:
```bash
# Survey all versions (read-only)
cd plotting/
source ../setEnv_newNew.sh
python3 manage_systematic_histograms.py --output cleanup_report.csv

# Cleanup specific version (dry-run)
python3 manage_systematic_histograms.py --cleanup \
    --version v8BDT1tau0l_refactorAndBtagNameFix --dry-run

# Execute cleanup
python3 manage_systematic_histograms.py --cleanup \
    --version v8BDT1tau0l_refactorAndBtagNameFix --execute

# Cleanup all consolidated versions
python3 manage_systematic_histograms.py --cleanup \
    --consolidated-only --dry-run
```

### What Gets Cleaned

**Target**: Systematic variation histogram directories after consolidation
- JES variation ROOT files (already in nominal)
- TES variation ROOT files (already in nominal)
- JER, MET, EES variation ROOT files (already in nominal)
- jobSH/ directories (job submission scripts - always safe)
- log/ directories (compressed to .zip, not deleted)

**Preserved**:
- Nominal histogram ROOT files
- Consolidated systematic templates (in nominal files)
- All v8BDT+ and v9BDT versions
- Recent reference versions (v3BDT*V18)

### Expected Impact

**Per version with systematics** (estimated):
- JES variations: ~50 dirs × 50 files = 2,500 files
- TES variations: 8 dirs × 50 files = 400 files
- JER, MET, EES: 6 dirs × 50 files = 300 files
- **Total per version**: ~3,000-5,000 files

**Target**: Clean 5-10 consolidated versions → free 15K-50K files → reduce to <700K (70% quota)

---

## Safety Measures

**Built-in script safety**:
- ✅ Survey mode is read-only by default
- ✅ Cleanup mode defaults to dry-run
- ✅ Requires explicit `--execute` flag for deletion
- ✅ Confirmation prompt before deletion (if >10K files)
- ✅ Comprehensive logging with timestamps
- ✅ Quota tracking (before/after)
- ✅ Only deletes systematic variations, never nominal files
- ✅ Zips log directories instead of deleting

**Additional safety practices**:
- Get user approval before each execution
- Start with dry-run, review output carefully
- Incremental: one version at a time
- Check quota after each cleanup
- Verify nominal files intact after cleanup

---

## Implementation Phases

### ✅ Phase 1: Write Survey + Cleanup Script (COMPLETE)

**Script Created**: `plotting/manage_systematic_histograms.py`

**Features implemented**:
- Survey mode: Scans all nominal dirs, finds systematic variations, counts files
- Cleanup mode: Filters and cleans with dry-run/execute modes
- Safety: Defaults to read-only survey, requires explicit --execute for deletion
- Logging: Comprehensive logs with timestamps
- Quota tracking: Shows before/after file counts

### Phase 2: Run Survey (30 min - NEXT STEP)

**Action**:
```bash
cd plotting/
source ../setEnv_newNew.sh
python3 manage_systematic_histograms.py --output cleanup_report.csv
```

**Expected output**:
- CSV report with all versions sorted by file count
- Summary of total files in systematic directories
- Top 10 versions by file count

**Decision point**: Review report with user, identify cleanup candidates

### Phase 3: Execute Cleanup (2-3 hours)

**For each approved version**:

1. Dry-run first:
   ```bash
   python3 manage_systematic_histograms.py --cleanup \
       --version [VERSION] --dry-run
   ```

2. Review output, then execute:
   ```bash
   python3 manage_systematic_histograms.py --cleanup \
       --version [VERSION] --execute
   ```

3. Check quota:
   ```bash
   lfs quota -u huahuil /publicfs
   ```

4. Stop when quota < 70%

### Phase 4: Verification & Documentation (30 min)

- Final quota check
- Verify can submit v9BDT jobs
- Update this document with results

### Phase 7: Final Cleanup (After 1-2 weeks)
- If no issues, delete staging directory
- Update this document with final counts

---

## Risks and Mitigations

**Risk 1**: Accidentally delete needed version
- *Mitigation*: Move to staging first, not direct deletion
- *Recovery*: Restore from staging within 1-2 weeks

**Risk 2**: Delete version needed for comparison/validation
- *Mitigation*: Keep all v8+ and v3BDT*V18 versions
- *Recovery*: Check with user before final deletion

**Risk 3**: Cleanup takes too long, blocking urgent work
- *Mitigation*: Start with highest-impact categories first
- *Recovery*: Can delete staging directory immediately if needed

---

## Success Criteria

✅ File quota below 70% (< 700K files)
✅ All active analysis versions preserved (v8+, v9)
✅ Can submit full production run for v9BDT1tau0l_CMSNamingComplete
✅ Documentation of what was deleted

---

## Notes

- This is file quota issue, not disk space
- Each histogram version can have 50-200 files per process
- With systematics, this multiplies quickly
- Many old test/development versions no longer needed
- Conservative approach: keep all v8+ versions

---

**Next Step**: Get user approval for deletion categories and priorities

---

## 🔍 MAJOR DISCOVERY: Actual Source of File Quota Problem (2025-11-27 13:00)

### Discovery Process

After implementing the systematic histogram cleanup script, ran comprehensive surveys to identify actual file usage:

1. **Systematic histogram survey** (`manage_systematic_histograms.py`):
   - Found only **46,292 files** in systematic variation directories
   - This is only **4.8%** of the 970K file quota problem!

2. **Comprehensive file survey** (`survey_all_files.py`):
   - Scanned ALL files in 4,369 histogram directories
   - Found **553,203 files total** in histogram directories:
     - ROOT files: 239,162 (43%) - **KEEP**
     - log/ files: 192,690 (35%) - **CLEANUP TARGET**
     - jobSH/ files: 82,186 (15%) - **CLEANUP TARGET**
     - Other: 39,165 (7%)

3. **Missing files**: **417,350 files** (970K - 553K) are OUTSIDE histogram directories
   - Location unknown - need further investigation

### Revised Cleanup Strategy: Target log/ and jobSH/

**New priority**: Clean log/ and jobSH/ directories - **274,876 files** (28% of quota!)

**Created**: `plotting/cleanup_logs_jobsh.py`

**Approach**:
- **log/ directories**: ZIP entire directory to single log.zip file (preserves for debugging)
  - 191,055 files → ~1,636 zip files = **~189K files freed**
- **jobSH/ directories**: DELETE entirely (can be regenerated)
  - 82,186 files deleted = **82K files freed**
- **Total expected**: **~271K files freed** (reduce from 970K to ~699K files = 70% quota ✅)

### Implementation Timeline

**Phase 1**: Create Tools (COMPLETE)
- ✅ `manage_systematic_histograms.py` - Survey/cleanup systematic histograms
- ✅ `survey_all_files.py` - Comprehensive file survey
- ✅ `cleanup_logs_jobsh.py` - ZIP logs, DELETE jobSH

**Phase 2**: Surveys (COMPLETE)
- ✅ Systematic histogram survey: 46K files found
- ✅ Comprehensive file survey: 553K files in histogram dirs
- ✅ log/jobSH survey: 275K files identified for cleanup

**Phase 3**: Dry-Run (COMPLETE)
- ✅ Dry-run executed successfully
- ✅ Confirmed: 273,241 files would be freed
- ✅ User approved execution

**Phase 4**: Execute Cleanup (IN PROGRESS - 50% complete as of 2025-11-27 17:20)
- 🚀 Running: `python3 cleanup_logs_jobsh.py --cleanup --execute --yes`
- **Started**: 2025-11-27 13:55
- **Runtime**: 3h 25m so far
- **Progress**: 143,071 files freed (50% complete)
- **Current quota**: 827,482 files (82.7%, down from 97%)
- **Remaining**: 127,482 files to free
- **Status**: Active (PID 3060854, 9.9% CPU)
- **Rate**: ~44 files/second
- **Expected completion**: ~4-5 more hours (overnight)
- Processing 1,636 histogram directories: Zipping log/, deleting jobSH/
- **Monitor**: Background script will notify when complete

### Key Technical Decisions

**Decision 1**: ZIP vs DELETE for log/ directories
- **Chosen**: ZIP entire log/ directory to single log.zip
- **Why**: Preserves logs for debugging while freeing files
- **Impact**: Each directory: 100-200 log files → 1 zip file

**Decision 2**: Added --yes flag for automation
- **Problem**: Confirmation prompt blocked background execution
- **Solution**: Added `--yes` flag to skip confirmation
- **Impact**: Enables automated batch cleanup

**Decision 3**: Focus on log/jobSH instead of systematic histograms
- **Why**: Data-driven - surveys showed log/jobSH are 6x larger problem
- **Impact**: Will achieve 70% target in single cleanup run

### Success Metrics

**Target**: Reduce file quota from 970K (97%) to <700K (<70%)

**Expected after current cleanup**:
- Files freed: ~273K
- Final count: ~697K files
- Final quota: ~70% ✅ **TARGET ACHIEVED**

### Next Steps After Cleanup Completes

1. Verify final quota with `lfs quota -u huahuil /publicfs`
2. Test v9BDT job submission
3. Document cleanup in ANALYSIS_WORKFLOW.md
4. If needed, investigate the 417K missing files outside histogram directories

### Tools Created (Reusable)

All three scripts are production-ready and can be reused for future maintenance:

1. **`plotting/manage_systematic_histograms.py`**
   - Survey systematic histogram variations
   - Cleanup after consolidation
   - Usage: `python3 manage_systematic_histograms.py --help`

2. **`plotting/survey_all_files.py`**
   - Comprehensive file survey by type
   - Identifies cleanup targets
   - Usage: `python3 survey_all_files.py --output report.csv`

3. **`plotting/cleanup_logs_jobsh.py`**
   - ZIP log/ directories (preserves)
   - DELETE jobSH/ directories (regenerable)
   - Usage: `python3 cleanup_logs_jobsh.py --cleanup --execute --yes`

### Slash Commands Created

1. **`/create-dev-docs`** - Create comprehensive dev-docs for new tasks
2. **`/show-plans`** - Show all active dev-docs plans with status
3. **`/update-dev-docs`** - Update dev-docs with progress (requires git commit first)
4. **`/resume-task [task-name]`** - Resume active task from dev-docs with full context


