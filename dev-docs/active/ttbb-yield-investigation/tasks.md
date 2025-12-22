# ttbb Yield Investigation - Tasks

**Status**: RESOLVED

## Completed

- [x] Compare XGB080 vs TTBBtest configs
- [x] Verify FR file path in inputMap_MV.h
- [x] Compare OS outputs between versions (IDENTICAL)
- [x] Verify FR file readable in Python (y=0.107, 0.129, etc.)
- [x] Add debug logging to weightVarMaker.C
- [x] Add debug logging to getFRandError in commenFunction.C
- [x] Rebuild myLibrary with debug output
- [x] Rebuild MV binary with debug output
- [x] Run MV test to capture detailed debug output
- [x] Verify FR_weight values in output file (0.07-0.11 range)
- [x] Update stage2-mv.md with local testing instructions

## Resolution

The FR_weight=0 bug was fixed by a full rebuild of myLibrary and MV binary. The issue was likely stale compiled objects.

## Optional Follow-up

- [ ] Remove debug logging from production code
- [ ] Regenerate fake_tau trees for XGB080 with fixed MV code
