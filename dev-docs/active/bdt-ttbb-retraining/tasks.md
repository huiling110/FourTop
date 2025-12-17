# BDT Retraining Tasks

## Status: In Progress - Testing Improvement Options (A, B, D)
## Last Updated: 2025-12-17 Session 11

## Phase 1: Setup ✓
- [x] Create feature branch `addBDTttbb`
- [x] Create dev-docs structure

## Phase 2: Link WH Code to TMVA ✓
- [x] Modify TMVA Makefile (`hua/tmva/newCode/Makefile`)
- [x] Refactor `tmvaBDT_training.C` with WH-consistent selection/weights
- [x] Build TMVA code successfully
- [x] Add minimum events threshold (50)

## Phase 3: YAML Configs ✓
- [x] Create `config/analysis_config_1tau1l_v1BDTttbb.yaml`
- [x] Create `config/analysis_config_1tau0l_v1BDTttbb.yaml`

## Phase 4: Build & Train ✓
- [x] Train all BDTs with excellent ROC scores:
  - 2018 1tau1l: ROC-integ = 0.977-0.978
  - 2018 1tau0l: ROC-integ = 0.911
  - 2017 1tau1l: ROC-integ = 0.979
  - 2017 1tau0l: ROC-integ = 0.913

## Phase 5: Integration ✓
- [x] Update `inputFileMap.h` with new BDT paths (BDT1tau1l_TTBBtrain, BDT1tau0l_TTBBtrain)
- [x] Add m_histVersion member to treeAnalyzer class
- [x] Update `treeAnalyzer.C` to select BDT based on version containing "v1BDTttbb"
- [x] Commit: `a5bb8db8 feat: Add BDT training with TTBB samples`

## Phase 6: Testing - FAILED (Bug Found)
- [x] Submit WH nominal jobs for 2017/2018
- [x] All 38/38 MC jobs completed for each era/channel
- [x] Data jobs completed
- [x] Run pl.py for BDT score plots
- [x] **BUG FOUND**: TTBB scores HIGH instead of LOW!

### Bug Analysis (2025-12-17)
The new BDT was scoring TTBB as **signal-like** (high BDT) instead of background-like (low BDT):
- Old BDT: TTBB mean=0.028, spread across bins
- New BDT: TTBB mean=0.177, **69% in highest bin!**

**Root Cause**: Training selection mismatch
- Old BDT input: Pre-selected data (`v1cut1tau1lSR_*`) with SR cuts applied
- New BDT input: Baseline-only data (`v1baselineHadro_*`) without SR cuts

Variable Min/Max comparison:
| Variable | Old BDT | New BDT | Issue |
|----------|---------|---------|-------|
| jets_num | Min=7 | Min=6 | No 7th jet requirement |
| bjetsM_num | Min=3 | Min=2 | No 3 b-jet requirement |
| jets_7pt | Min=25 | Min=-99 | Missing value! |
| tausT_1pt | Min=20 | Min=-99 | Missing value! |

The BDT trained on events failing SR selection, so it couldn't discriminate SR-passing events properly.

**Fix Applied**: Modified `tmvaBDT_training.C` to apply common SR cut in `PrepareTrainingAndTestTree`:
```cpp
TCut commonSRCut = "(jets_num>=7 && bjetsM_num>=3)";  // channel-specific
dataloader->PrepareTrainingAndTestTree(commonSRCut, commonSRCut, trainingSetup);
```

## Phase 7: Retrain BDT - COMPLETED ✓
- [x] Rebuild training code with SR selection fix
- [x] Retrain 2017 1tau1l BDT (ROC-integ: 0.967)
- [x] Retrain 2018 1tau1l BDT (ROC-integ: 0.965)
- [x] Retrain 2017 1tau0l BDT (ROC-integ: 0.838)
- [x] Retrain 2018 1tau0l BDT (ROC-integ: 0.844)
- [x] Verified variable Min/Max: jets_num=7, bjetsM_num=3, jets_7pt=25 ✓

## Phase 8: Re-test - COMPLETED ✓
- [x] Updated inputFileMap.h with v2BDTttbb weight paths
- [x] Rebuilt WH code
- [x] Quick test on TTBB_4f_TTTo2L2Nu

### Test Results (2025-12-17)
| Version | TTBB Mean BDT | High BDT bin |
|---------|---------------|--------------|
| Reference (old BDT) | 0.0276 | 2.56 |
| Broken v1BDTttbb | 0.1774 | 24.32 |
| **Fixed v2BDTttbb** | **0.0276** | **2.56** |

**Fix verified!** TTBB now scores at low BDT values (background-like) as expected.

## Phase 9: Full Production - BUGS FOUND
- [x] Fix treeAnalyzer.C version check bug (was checking "v1BDTttbb" but config had "v2BDTttbb")
- [x] Simplify code to always use TTBB-trained BDT (removed version check)
- [x] Submit full WH jobs for 2017/2018 (314 jobs total)
- [x] Verified jobs using correct v2BDTttbb weights via log inspection
- [x] Jobs completed
- [x] **BUG FOUND**: Entries not matching WH exactly (2-3% fewer)

### Bug Fix (2025-12-17 Session 7)
**Problem**: Jobs were using OLD BDT weights instead of v2BDTttbb
- Log showed: `training input: .../v1cut1tau1lSR_v84HadroPresel/.../v1finalVar27/...`
- Should be: `.../v1baselineHadro_.../v2BDTttbb/...`

**Root Cause**: `treeAnalyzer.C` checked `m_histVersion.Contains("v1BDTttbb")` but config had `v2BDTttbb_1tau1l`

**Fix**: Removed version check, always use `BDT1tau1l_TTBBtrain` / `BDT1tau0l_TTBBtrain` maps
- Commit: `16369fd9 fix: Always use TTBB-trained BDT (v2) for all channels`

### Bug Fix (2025-12-17 Session 8)
**Problem**: Training entries not matching WH exactly
| Process | Training | WH | Match |
|---------|----------|-----|-------|
| tttt | 76669 | 78674 | NO |
| fakeTau_data_ptMorphed | 619 | 640 | NO |
| TTBB_4f_TTTo2L2Nu | 819 | 848 | NO |

**Root Cause**: Baseline cut mismatch
- Training used: `jets_HT>500 && jets_6pt>40` (hard-coded)
- WH uses conditional:
  - If `bjetsM_num < 4`: `jets_HT > 500 && jets_6pt > 40`
  - If `bjetsM_num >= 4`: `jets_HT > 480 && jets_6pt > 38`

**Fix Applied**: Updated `getSelectionCut()` in `tmvaBDT_training.C`:
```cpp
TCut baseCut = "(jets_num>=6 && bjetsM_num>=2) && ((bjetsM_num<4 && jets_HT>500 && jets_6pt>40) || (bjetsM_num>=4 && jets_HT>480 && jets_6pt>38))";
```

## Phase 10: v3BDTttbb Training - COMPLETED
- [x] Fix baseline cut to match WH conditional (bjetsM_num<4 vs >=4)
- [x] Verify entries match WH exactly (all processes: YES)
- [x] Train 2018 1tau1l BDT (v3BDTttbb) - ROC-integ = 0.778
- [x] Train 2017 1tau1l BDT (v3BDTttbb) - ROC-integ = 0.798
- [x] Update inputFileMap.h with v3BDTttbb paths
- [x] Rebuild WH code and submit 1tau1l jobs (157 jobs: 76 for 2018, 81 for 2017)

## Phase 11: Validation - ISSUE FOUND
- [x] Wait for WH jobs to complete
- [x] Run pl.py and compare BDT distributions
- [x] **ISSUE**: S/sqrt(B) decreased by 2.7% with old binning

### Validation Results (2025-12-17 Session 9)
Initial comparison with v3BDTttbb using old binning showed worse performance:
| Metric | v0BDT | v3BDT | Change |
|--------|-------|-------|--------|
| tttt in top 2 bins | 41.4% | 41.4% | Same |
| TTBB in top 2 bins | 18.5% | 19.5% | +1.0% |
| S/sqrt(B) | 0.561 | 0.546 | **-2.7%** |

**Root Cause**: Old binning [-0.25, 0.36] mismatched v3BDT score range [-0.10, 0.21]

## Phase 12: Binning Optimization - COMPLETED
- [x] Check v3BDT score range from training output
- [x] Found: v3BDT range [-0.10, 0.21] vs old [-0.25, 0.36]
- [x] Run binning optimization using training histograms (MVA_BDT_S/B)
- [x] Create optimizeBinning_fromTraining.py script (with lumi scaling)
- [x] Fixed TMVA normalization issue (S and B normalized to equal integrals)
- [x] Applied proper lumi scaling: S=3.47, B=125.49 from WH output
- [x] Tested multiple binning strategies: equal-BG, last-bin optimized, hybrid

## Phase 13: v0 vs v3 Comparison - COMPLETED ❌ v3 WORSE
- [x] Direct comparison of v0BDT (original) vs v3BDT (TTBB-trained)

### Critical Finding (2025-12-17 Session 10)
**v3BDT (TTBB-trained) has WORSE discrimination than v0BDT (original)!**

| Metric | v0BDT | v3BDT | Ratio |
|--------|-------|-------|-------|
| Signal-BG separation | 0.082 | 0.042 | **2.0x worse** |
| Signal RMS | 0.078 | 0.034 | Compressed |
| Top 20% signal S/B | 0.176 | 0.104 | **1.7x worse** |
| Top 50% signal S/B | 0.089 | 0.078 | 1.2x worse |
| Total S/√B | 1.160 | 0.841 | **1.4x worse** |
| Last bin S/B | 0.967 | 0.104 | **9.3x worse** |

**Root Cause Analysis**:
1. v3BDT signal is more compressed (RMS 0.034 vs 0.078)
2. More background leaks into high-BDT region in v3
3. Adding TTBB to training confused the BDT - TTBB kinematics overlap with tttt

## Phase 14: Training Improvement - Add New Variables - IN PROGRESS
**Approach**: Add 7 new discriminating variables to improve tttt vs TTBB separation

### Physics Rationale
- tttt: 4 top decays → 4 b-jets from tops
- TTBB: 2 tops + 2 b-jets from gluon splitting (softer, collinear)

### New Variables (added to existing 26 → total 33)
| Variable | Physics Reason |
|----------|----------------|
| bjetsT_num | Tight b-jet count - tttt should have more |
| bjetsT_1pt | 1st tight b-jet pt - harder in tttt |
| bjetsT_2pt | 2nd tight b-jet pt - harder in tttt |
| bjetsM_2pt | 2nd medium b-jet pt |
| bjetsM_3pt | 3rd medium b-jet pt |
| jets_4largestBscoreSum | Total b-flavor - differs between processes |
| jets_sphericity | Event isotropy - tttt more spherical |

### Implementation Status
- [x] Created `inputList_1tau1l_v4extended.csv` with 33 variables
- [x] Trained v4BDTttbb for 2018 1tau1l - **ROC = 0.796**
- [x] Trained v5BDTttbb without jets_4largestBscoreSum - **ROC = 0.780**
- [x] Compared all BDT versions

### Final Comparison Results (2025-12-17)
| Metric | v0BDT | v3BDT | v4BDT | v5BDT |
|--------|-------|-------|-------|-------|
| ROC integral | 0.777 | 0.778 | **0.796** | 0.780 |
| Signal RMS | **0.078** | 0.034 | 0.036 | 0.036 |
| Separation | 1.073 | 1.068 | **1.165** | 1.080 |
| Top 20% S/B | 0.184 | 0.074 | **0.223** | 0.157 |
| Top 20% S/√B | 0.317 | 0.190 | **0.331** | 0.290 |

### Key Findings
1. **v4BDT is the best** with ROC=0.796 and Top20% S/B=0.223
2. **jets_4largestBscoreSum is crucial**: removing it drops ROC from 0.796→0.780
3. **TTBB-trained BDTs (v3,v4,v5) compress signal RMS** compared to v0BDT
4. Despite compression, v4BDT has better discrimination overall

### Variable Importance (TMVA ranking)
1. jets_4largestBscoreSum (sep=0.248) - **NEW**
2. bjetsT_invariantMass (sep=0.155)
3. bjetsT_num (sep=0.145) - **NEW**
4. bjetsT_2pt (sep=0.118) - **NEW**
5. bjetsM_3pt (sep=0.111) - **NEW**

### Issue: Signal RMS Compression
TTBB training compresses signal distribution:
- v0BDT: Signal RMS = 0.078
- v4/v5BDT: Signal RMS = 0.036

**Root cause**: TTBB kinematics overlap with tttt, BDT finds compromise

### Issue: btag Shape Variables
`jets_4largestBscoreSum` is #1 ranked but introduces large systematics → avoid using

## Phase 14.2: Improvement Options Testing - IN PROGRESS

### Options to Test (without btag shape variables)
| Version | Changes | Status |
|---------|---------|--------|
| v6a | Signal upweight 2x | Pending |
| v6b | MaxDepth=4 | Pending |
| v6c | MaxDepth=5 | Pending |
| v6d | Combined (upweight + depth=4 + new vars) | Pending |

### New Variables for v6
- All from v5 (no jets_4largestBscoreSum)
- **+jets_average_deltaR** (sep=0.484 for tttt vs TTBB)
- **+jets_aplanarity** (sep=0.315)
- Total: 34 variables

### Variable List Created
- `inputList_1tau1l_v6extended.csv` (34 vars)

## Resolved Issues
1. **Global weight missing**: Added processScale ✓
2. **makeJob_WH.py data handling**: Fixed to include data by default for nominal ✓
3. **Workflow skills**: Updated stage3-wh.md and stage4-combine.md ✓
4. **tttt job timeout**: Completed successfully via screen session ✓
5. **Training selection mismatch**: Fixed PrepareTrainingAndTestTree to use SR cut ✓
6. **Version check mismatch**: Simplified to always use TTBB-trained BDT ✓
7. **Baseline cut mismatch**: Fixed conditional jets_HT/jets_6pt cut based on bjetsM_num ✓
8. **TMVA scaling**: Fixed lumi scaling in binning optimization ✓

### Entry Verification (v3BDTttbb)
| Process | Training | WH | Match |
|---------|----------|-----|-------|
| tttt | 78674 | 78674 | YES ✓ |
| fakeTau_data_ptMorphed | 640 | 640 | YES ✓ |
| fakeTau_MC_ptMorphed | 48850 | 48850 | YES ✓ |
| fakeLepton | 28 | 28 | YES ✓ |
| ttbar_2l | 541 | 541 | YES ✓ |
| TTBB_4f_TTTo2L2Nu | 848 | 848 | YES ✓ |

## Resolved Issues
1. **Global weight missing**: Added processScale ✓
2. **makeJob_WH.py data handling**: Fixed to include data by default for nominal ✓
3. **Workflow skills**: Updated stage3-wh.md and stage4-combine.md ✓
4. **tttt job timeout**: Completed successfully via screen session ✓
5. **Training selection mismatch**: Fixed PrepareTrainingAndTestTree to use SR cut ✓
6. **Version check mismatch**: Simplified to always use TTBB-trained BDT ✓
7. **Baseline cut mismatch**: Fixed conditional jets_HT/jets_6pt cut based on bjetsM_num ✓
