# Tasks: FourTop Workflow Code Quality Improvements

**Created**: 2025-12-02
**Last Updated**: 2025-12-02
**Status**: Phase 1 - Complete

---

## Phase 1: Code Quality Fixes

### Task 1.1: Fix duplicate get_smoothed_up_and_down() function
- [x] Read smooth_systematics_fourTops.py to confirm duplicate locations
- [x] Delete duplicate function at lines 367-388
- [x] Verify first definition at lines 303-325 is complete

**Status**: Complete
**Notes**: Deleted duplicate function, kept original at lines 303-325

### Task 1.2: Add --quiet flag to writeDatacard.py
- [x] Add argparse import if not present
- [x] Create argument parser with --quiet/-q flag
- [x] Wrap sysDic printing with `if not args.quiet:` check

**Status**: Complete
**Notes**: Added argparse, wrapped verbose prints (processes, sysDic, per-systematic prints)

### Task 1.3: Add --quiet flag to addTemplateNew.py
- [x] Add argparse import if not present
- [x] Create argument parser with --quiet/-q flag
- [x] Wrap debug print statements with `if not args.quiet:` check

**Status**: Complete
**Notes**: Added argparse, wrapped verbose prints, passed quiet flag to addDataHist function

### Task 1.4: Add --quiet flag to smooth_systematics_fourTops.py
- [x] Add argparse to existing script
- [x] Wrap verbose print statements with global QUIET flag

**Status**: Complete
**Notes**: Used global QUIET flag approach since many helper functions need access

---

## Phase 2: Archive Commented Paths (Future)

### Task 2.1: Create OLD_CONFIGS.md
- [ ] Create plotting/OLD_CONFIGS.md with header and structure
- [ ] Add sections for each script

**Status**: Not Started

### Task 2.2: Archive paths from writeDatacard.py
- [ ] Extract ~250 commented inputTemplate paths
- [ ] Add to OLD_CONFIGS.md with context
- [ ] Remove from writeDatacard.py

**Status**: Not Started

### Task 2.3: Archive paths from addJESTemplatesToHistFile.py
- [ ] Extract ~300 commented nominalDir paths
- [ ] Add to OLD_CONFIGS.md
- [ ] Remove from script

**Status**: Not Started

### Task 2.4: Archive paths from addTemplateNew.py
- [ ] Extract ~80 commented inputDir paths
- [ ] Add to OLD_CONFIGS.md
- [ ] Remove from script

**Status**: Not Started

### Task 2.5: Archive paths from writeCombinationDatacard.py
- [ ] Extract ~150 path dictionary entries
- [ ] Add to OLD_CONFIGS.md or separate file
- [ ] Clean up script

**Status**: Not Started

---

## Success Criteria Checklist

- [x] No duplicate function definitions in smooth_systematics_fourTops.py
- [x] writeDatacard.py supports --quiet flag
- [x] addTemplateNew.py supports --quiet flag
- [x] smooth_systematics_fourTops.py supports --quiet flag
- [x] All scripts still work without --quiet (backward compatible)

---

## Notes

- 2025-12-02: Plan approved, starting Phase 1 implementation
- 2025-12-02: Phase 1 COMPLETE - All 4 code quality tasks finished
- User preference: Prioritize code quality fixes before archiving paths
