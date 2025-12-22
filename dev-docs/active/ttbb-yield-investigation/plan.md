# ttbb Yield Investigation - FR_weight=0 Bug

**Status**: RESOLVED
**Last Updated**: 2025-12-22

## Problem Statement

FR_weight (Fake Rate weight) was 0 in XGB080 MV output while TTBBtest reference had ~0.109. This caused fake_tau yields to be 0.

## Resolution

**Root Cause**: Stale compiled objects in myLibrary/MV code.

**Fix**: Full rebuild of myLibrary and MV binary:
```bash
cd myLibrary && source ../setEnv_newNew.sh && make
cd ../makeVariables_goodCode && make clean && make
```

**Verification**: FR_weight now shows correct values (0.08-0.11) in output:
```
*    Row   * FR_weight *
*        0 * 0.1000924 *
*        1 * 0.0819416 *
*        2 * 0.1078551 *
```

## Investigation Summary

### Phase 1: Establish Baseline (COMPLETED)
- [x] Compared XGB080 vs TTBBtest configs - nearly identical
- [x] Verified FR file path is hardcoded in inputMap_MV.h
- [x] Confirmed OS outputs are IDENTICAL between versions
- [x] Verified Python can read FR file correctly (y=0.107, 0.129, etc.)

### Phase 2: Debug C++ Code (COMPLETED)
- [x] Added debug logging to weightVarMaker.C
- [x] Added debug logging to getFRandError in commenFunction.C
- [x] Rebuilt myLibrary and MV binary
- [x] Ran test to see detailed graph debug output
- [x] Debug output confirmed FR values now correct

### Phase 3: Verify (COMPLETED)
- [x] FR_weight values verified in output file
- [x] Values range from 0.07-0.11 as expected

## Debug Output (After Fix)
```
[FR DEBUG] Entry 1: eta=0.998, prong=1, pt=55.8, m_graphs.size=4
[getFRandError] Matched graph: etaRange=[0.8,1.5], prong=1, nPoints=8
[getFRandError] index=5, x=60, y(fr)=0.0909855
[FR DEBUG] ifFR=1, nominal=0.0909855, errDown=0.00418, errUp=0.00418
```

## Files Modified
- `makeVariables_goodCode/src/weightVarMaker.C` - added debug logging
- `myLibrary/commenFunction.C` - added debug logging to getFRandError
- `.claude/skills/workflow/stage2-mv.md` - added local testing instructions

## Next Steps
- [ ] Remove debug logging from production code (optional)
- [ ] Regenerate fake_tau trees for XGB080 production
