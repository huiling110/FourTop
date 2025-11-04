# Quick Validation Test Reference

## Purpose
This document provides a reference for quick validation testing during development.
Use the quick test (`isTest=1`) to rapidly verify that code changes don't break functionality.

---

## Quick Test Setup

### Test Script: `test_refactored_quick.sh`
- **Test Mode**: `IS_TEST=1` (processes ~10,000 events instead of full 1.6M)
- **Runtime**: ~4-5 seconds (vs 7+ minutes for full run)
- **Purpose**: Fast sanity check during development

### Usage
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/writeHistGood
bash test_refactored_quick.sh
```

---

## Reference Results (Baseline: commit fa93627c)

### Test Configuration
- **Input**: `/publicfs/.../v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/tttt.root`
- **Channel**: 1tau1l
- **Systematics**: Enabled (IF_SYS=1)
- **Test Mode**: Enabled (IS_TEST=1)

### Performance Metrics
- **Real Time**: 4 seconds
- **CPU Time**: 3.88 seconds
- **Events Processed**: 478 entries (passing selection)
- **Total Events Scanned**: ~10,000 (from 1.66M total in file)

### Sample Histogram Outputs
Last 14 systematic variations (for quick verification):

| Systematic | Entries | Sum | 
|------------|---------|-----|
| CMS_pileupDown | 478 | 0.021519 |
| CMS_pileupUp | 478 | 0.0227218 |
| QCDscale_facDown | 478 | 0.0220518 |
| QCDscale_facUp | 478 | 0.0221742 |
| QCDscale_renDown | 478 | 0.0219742 |
| QCDscale_renUp | 478 | 0.022255 |
| pdf_00Down | 478 | 0.0220622 |
| pdf_00Up | 478 | 0.0221912 |
| pdf_alphasDown | 478 | 0.0219513 |
| pdf_alphasUp | 478 | 0.0221505 |
| ps_fsrDown | 478 | 0.0181293 |
| ps_fsrUp | 478 | 0.0217485 |
| ps_isrDown | 478 | 0.0224624 |
| ps_isrUp | 478 | 0.0218356 |

---

## When to Use Quick Test vs Full Validation

### Use Quick Test (`isTest=1`) When:
- ✅ Making small incremental changes (e.g., code style, comments)
- ✅ Testing build system changes
- ✅ Verifying no crashes after refactoring
- ✅ Checking that systematics are still processed
- ✅ During active development iteration

### Use Full Validation (`isTest=0`) When:
- ✅ Completing major refactoring milestone
- ✅ Changing logic that affects physics calculations
- ✅ Before committing to main/master branch
- ✅ Final validation before production use
- ✅ Investigating numerical precision issues

---

## How to Verify Quick Test Results

After running the quick test, check:

1. **Exit Code**: Should be 0
   ```bash
   echo $?
   ```

2. **Runtime**: Should be ~4-5 seconds
   - Significantly longer? Check for performance regression
   - Much shorter? Test may have crashed early

3. **Event Count**: Should show ~478 entries
   ```bash
   grep "Entries=" test_quick_refactored.log | tail -5
   ```

4. **Output File Created**: ROOT file should exist
   ```bash
   ls -lh /publicfs/.../variableHists_*_quickTest/tttt.root
   ```

5. **No Crashes**: Check for segfaults or exceptions
   ```bash
   grep -i "segmentation\|exception\|error" test_quick_refactored.log
   ```

---

## Expected Behavior After Code Changes

### Memory Management Changes (smart pointers, etc.)
- ✅ Runtime should be similar (±10%)
- ✅ No memory leaks or crashes
- ✅ Event counts should match
- ✅ Histogram sums should be identical

### Logging Framework Changes
- ✅ Colored output may appear in logs
- ✅ Timestamps added to log lines
- ✅ Slight runtime overhead acceptable (~5-10%)
- ✅ Physics results unchanged

### Systematic Manager Changes
- ✅ All systematic variations present in output
- ✅ Histogram sums must match reference
- ✅ Entry counts unchanged

### Configuration Changes (constants, bin definitions)
- ⚠️ **Requires full validation** - quick test not sufficient
- Compare histogram distributions, not just sums

---

## Troubleshooting

### Test Runs Too Long (>10 seconds)
- Check if `IS_TEST=1` is properly set
- Verify `isTest` parameter is being read correctly
- Look for infinite loops or performance issues

### Different Entry Counts
- Check if selection criteria changed
- Verify BDT weights file path is correct
- Check for changes in baseline selection logic

### Histogram Sums Don't Match
- Expected if physics logic changed
- Run full validation to confirm
- Compare with reference log carefully

### Crashes or Segfaults
- Check smart pointer usage
- Verify ROOT object ownership
- Run with valgrind for detailed memory analysis:
  ```bash
  valgrind --leak-check=full ./apps/run_treeAnalyzer.out [args]
  ```

---

## Updating This Reference

When making major validated changes, update this reference:
1. Run quick test with new code
2. Update performance metrics if significantly changed
3. Update sample histogram values
4. Update commit hash in header
5. Commit updated reference file

---

**Baseline Commit**: fa93627c  
**Date**: 2025-11-04  
**Status**: Validated against full run (commit 5869d89a)  
**Last Updated**: 2025-11-04

