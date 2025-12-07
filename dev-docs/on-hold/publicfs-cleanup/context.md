# Context: Safe Cleanup of /publicfs File Quota

**Created**: 2025-11-27 11:20
**Last Updated**: 2025-11-27 11:30

---

## Problem

- **File quota**: 970K/1M files (97% - CRITICAL)
- **Blocking**: Cannot submit new histogram production jobs
- **Root cause**: Thousands of systematic histogram directories with many small files

---

## Existing Cleanup Infrastructure

**Good news**: Cleanup functionality already exists in `plotting/addJESTemplatesToHistFile.py`!

### Key Functions

1. **`find_systematic_directories(nominal_dir)`** (lines 19-103)
   - Finds all systematic variation directories (JES, JER, TES, MET, EES)
   - Constructs paths exactly as consolidation functions do
   - Returns list of directories to cleanup

2. **`cleanup_systematic_histogram_directory(sys_hist_dir, dry_run=True)`** (lines 134-194)
   - Deletes ROOT files (already consolidated into nominal)
   - Deletes jobSH/ directory
   - Zips log/ directory to save space
   - Returns count of files deleted

3. **`cleanup_systematic_directories(nominal_dir, dry_run=True)`** (lines 197-253)
   - Main cleanup orchestrator
   - Finds all systematic dirs
   - Cleans each one
   - Reports summary statistics

### Command-Line Interface

```bash
# Dry-run (safe, shows what would be deleted)
python3 addJESTemplatesToHistFile.py --delete-sys-dirs

# Actually execute cleanup
python3 addJESTemplatesToHistFile.py --delete-sys-dirs --execute
```

**Note**: Script requires era, channel, version arguments (see main())

---

## Cleanup Strategy

### Phase 1: Cleanup Consolidated Versions

For versions where systematic templates have been consolidated into nominal ROOT files:

**Candidates** (verify with user):
- `v8BDT1tau0l_refactorAndBtagNameFix` (V19 - consolidated)
- `v8BDT1tau1lV_refactorAndBtagNameFix` (may be consolidated)

**Safety checks before cleanup**:
1. Verify nominal file contains systematic histograms
2. Run dry-run first
3. Check file count reduction estimate
4. Get user approval

### Phase 2: Delete Old Obsolete Versions

Delete entire version directories (not just systematic subdirs) for old test/development versions:

**High priority** (many files):
- All `v0BasicSystematic*`
- All `v0systematic*`
- All `v*test*` variants
- All `v0FR_measure*`
- All `v0HLT*` measurement versions

**Medium priority**:
- Old BDT versions (v0BDT, v1BDT, v2BDT except kept references)
- Old dataMC versions
- Old binning test variants

**Keep** (active/reference):
- v8BDT* versions (current validated)
- v9BDT* versions (current work)
- v3BDT*V18 versions (may be reference for 1tau1l/1tau2l)

---

## Key Files

- **Cleanup script**: `plotting/addJESTemplatesToHistFile.py`
  - Lines 19-253: Cleanup functions
  - Lines 424-436: Cleanup invocation
  - Lines 270-292: Argparse setup

- **Helper functions**: `plotting/usefulFunc.py`
  - `getEraFromDir()`: Extract era from directory path

- **Configuration**: `plotting/ttttGlobleQuantity.py`
  - `JESVariationList`: List of JES systematic sources

---

## Safety Principles

1. **Always dry-run first**: `--delete-sys-dirs` without `--execute`
2. **Verify consolidation**: Check nominal ROOT file has systematic histograms
3. **User approval**: Get explicit OK before executing
4. **Incremental**: Clean one version at a time
5. **Document**: Record what was cleaned and file count reduction

---

## Expected Impact

**Per version with systematics** (estimated):
- JES variations: ~50 dirs × 50 files = 2,500 files
- TES variations: 8 dirs × 50 files = 400 files
- JER, MET, EES: 6 dirs × 50 files = 300 files
- **Total per version**: ~3,000-5,000 files

**Target**: Clean 5-10 consolidated versions → free 15K-50K files → reduce to 920K-955K (92-95%)

**For complete version deletion**: 50-200 files per version × 100+ old versions → could free 10K-100K+ files

---

## Next Steps

1. Identify which versions have been consolidated (check for template files)
2. Run dry-run cleanup for one version
3. Get user approval
4. Execute cleanup for that version
5. Verify file count reduction
6. Repeat for other versions
