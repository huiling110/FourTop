# BDT Retraining Tasks

## Status: In Progress - Binning Optimization Required
## Last Updated: 2025-12-17 Session 9

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

## Phase 12: Binning Optimization - IN PROGRESS
- [x] Check v3BDT score range from training output
- [x] Found: v3BDT range [-0.10, 0.21] vs old [-0.25, 0.36]
- [x] Run binning optimization using training histograms (MVA_BDT_S/B)
- [x] Create optimizeBinning_fromTraining.py script
- [x] Update treeAnalyzer.C with optimized bin edges
- [x] Commit: `ca7a778c feat: Optimize BDT binning for v3BDTttbb score range`
- [ ] Rebuild WH and submit 2018 1tau1l jobs
- [ ] Run pl.py and compare with pre-TTBB BDT
- [ ] If improved, apply to 2017 and 1tau0l

### Optimized Binning (v3BDTttbb)
```cpp
// Equal BG per bin, range [-0.10, 0.21]
std::vector<Double_t> bins1tau1l = {-0.100, 0.009, 0.033, 0.048, 0.064, 0.087, 0.119, 0.213};
```

From training output optimization:
| Bin | Signal | Background | S/sqrt(S+B) |
|-----|--------|------------|-------------|
| [-0.10, 0.01] | 2.0 | 20.7 | 0.43 |
| [0.01, 0.03] | 4.8 | 19.9 | 0.97 |
| [0.03, 0.05] | 5.9 | 20.0 | 1.16 |
| [0.05, 0.06] | 10.5 | 21.1 | 1.87 |
| [0.06, 0.09] | 28.7 | 19.1 | 4.15 |
| [0.09, 0.12] | 48.0 | 19.6 | 5.84 |
| [0.12, 0.21] | 28.0 | 7.4 | 4.70 |
| **Total** | | | **19.11** |

## Phase 13: Final Validation & 1tau0l - PENDING
- [ ] Verify optimized binning gives better S/sqrt(B)
- [ ] If good, retrain for 1tau0l channel
- [ ] Move training weights to workfs and update inputFileMap.h

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
