# Important Updates Log

This file tracks important C++ code changes that affect physics analysis.

---

## 2026-01-28: B-hadron pT Cut Change for Overlap Removal

**File**: `objectSelectionOptimized/src/copyBranch.C`

**Change**: Changed B-hadron pT cut in `countAdditionalBHadrons()` from 5 GeV to 20 GeV

**Before**:
```cpp
if (e->GenPart_pt->At(p) < 5.0) continue;  // B-hadron pT > 5 GeV
```

**After**:
```cpp
if (e->GenPart_pt->At(p) < 20.0) continue;  // B-hadron pT > 20 GeV for overlap removal
```

**Reason**:
- The overlap removal between ttbar and TTBB samples was removing ALL ttbar events with any additional B-hadrons (pT > 5 GeV)
- This meant 100% of ttbar events had `deltaR_bb_min = -1` (no pairs to calculate deltaR)
- With pT > 20 GeV threshold, events with softer additional B-hadrons remain in ttbar
- This allows meaningful deltaR calculation for the tt collinear modeling uncertainty

**Physics Impact**:
- Affects ttbar/TTBB overlap removal for ALL analyses using this code
- ttbar events with additional B-hadrons (5 < pT < 20 GeV) now stay in ttbar, not moved to TTBB
- The deltaR_bb_min calculation still uses pT > 5 GeV to find softer b-jets

**Samples Affected**: ttbar (TTToSemiLeptonic, TTTo2L2Nu, TTToHadronic), TTBB

**Action Required**: Re-run Stage 1 (OS) for both tt and ttbb samples
