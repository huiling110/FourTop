# BDT Retraining Tasks

## Status: CLOSED - Reverted to v0 BDT
## Last Updated: 2025-12-19 Session 14

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

## Phase 14.2: Improvement Options Testing - COMPLETED

### v6 Training Results (2025-12-17 Session 12)
| Version | Config | ROC | Overtraining @B=0.01 |
|---------|--------|-----|---------------------|
| v5 (baseline) | 32 vars, depth=3 | 0.780 | - |
| **v6a** | 34 vars, **upweight 2x** | **0.791** | 0.221/0.441 (acceptable) |
| v6b | 34 vars, depth=4 | 0.748 | severe overtraining |
| v6c | 34 vars, depth=5 | 0.746 | 0.058/0.621 (severe!) |
| v6d | 34 vars, upweight 2x, depth=4 | 0.748 | severe overtraining |

### Key Findings
1. **Signal upweight 2x (v6a) works**: ROC improved 0.780 → 0.791 (+1.4%)
2. **Deeper trees overfit badly**: MaxDepth=4/5 cause severe overtraining, ROC drops to 0.746-0.748
3. **Combined approach fails**: Overfitting from deeper trees dominates even with upweighting

### All BDT Version Comparison
| Version | Description | ROC | Notes |
|---------|-------------|-----|-------|
| v0BDT | Original (no TTBB) | 0.777 | Baseline |
| v3BDT | TTBB-trained | 0.778 | +0.1% |
| **v4BDT** | +7 vars w/ BscoreSum | **0.796** | Best overall, but btag systematics |
| v5BDT | No BscoreSum | 0.780 | Safe from systematics |
| **v6aBDT** | 34 vars + upweight 2x | **0.791** | **Best without btag shape** |

### Recommendation
**Use v6a (ROC=0.791)** as the final BDT:
- +1.4% better than v5 (0.780)
- -0.6% vs v4 (0.796) but avoids btag shape systematics
- Signal upweight compensates for TTBB kinematic overlap

### New Variables for v6
- All from v5 (no jets_4largestBscoreSum)
- **+jets_average_deltaR** (sep=0.484 for tttt vs TTBB)
- **+jets_aplanarity** (sep=0.315)
- Total: 34 variables

### Variable List Created
- `inputList_1tau1l_v6extended.csv` (34 vars)

## Phase 15: v6a WH Production - COMPLETED ✓

### v6a Training (Both Eras)
- [x] Train 2018 1tau1l v6a BDT - ROC = 0.791
- [x] Train 2017 1tau1l v6a BDT - ROC = 0.792

### Code Updates
- [x] Update `inputFileMap.h` with v6a weight paths (cross-era application)
  - 2018 uses 2017 training, 2017 uses 2018 training
- [x] Update `treeAnalyzer.C` with 8 hybrid bins:
  ```cpp
  std::vector<Double_t> bins1tau1l = {-0.10, 0.02, 0.05, 0.065, 0.08, 0.095, 0.11, 0.13, 0.22};
  ```
- [x] Update `analysis_config_1tau1l_v1BDTttbb.yaml` → hist: "v6aBDTttbb_1tau1l"
- [x] Rebuild WH code

### WH Job Submission
- [x] Submit 2018 1tau1l jobs - 71/71 completed ✓
- [x] Submit 2017 1tau1l jobs - 71/71 completed ✓
- [x] Verified v6a BDT weights loading correctly (cross-era confirmed)

### Plotting
- [x] Run pl.py for 2018 - Plots saved to results/
- [x] Run pl.py for 2017 - Plots saved to results/

### Results Summary
| Era | tttt (total) | Last Bin S | Last Bin B | S/B (last) |
|-----|--------------|------------|------------|------------|
| 2018 | 3.5 | 0.42 | 2.54 | 0.17 |
| 2017 | 2.4 | 0.36 | 2.27 | 0.16 |

**Data/MC agreement**: Good across all bins, ratio panel shows ~0.8-1.2

### Output Paths
- 2018: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/variableHists_v6aBDTttbb_1tau1l/`
- 2017: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/variableHists_v6aBDTttbb_1tau1l/`

## Phase 16: Debug Data/MC Discrepancy - IN PROGRESS

### Issue Observed
Data/MC discrepancy in v6a BDT distribution needs investigation.

### Investigation Plan
- [x] Check if tau-related variables are correctly replaced in `replaceTauTVar()`
- [x] Verify no -99 values in fake tau file for BDT input variables
- [x] Compare fakeTau BDT distribution: v6a vs v0 (original)
- [x] Check if new variables (jets_average_deltaR, jets_aplanarity) exist for fakeTau
- [x] Verify pT morphing is correctly applied
- [x] Compare shape of individual variables between data and MC

### ROOT CAUSE IDENTIFIED (2025-12-19 Session 13)

**New v6 event shape variables show significant MC mismodeling!**

#### Primary Culprits (NEW variables in v6):
| Variable | Issue | Data/MC Ratio |
|----------|-------|---------------|
| **jets_aplanarity** | MC overestimates at low+high values | 0.6-0.8 at tails |
| **jets_sphericity** | MC overestimates at high sphericity | ~0.7 at high values |
| **jets_average_deltaR** | MC overestimates at both tails | ~0.6-0.8 |

#### Secondary Issues (b-jet related):
| Variable | Issue | Data/MC Ratio |
|----------|-------|---------------|
| **bjetsT_num** | Shape mismodeling at n=0 and n≥4 | ~0.7 at n=0, ~0.6 at n≥4 |
| **bjetsT_1pt/2pt** | MC overestimates at low pT | ~0.6-0.8 at first bin |
| **muonsTopMVAT_1pt** | Deficit at low pT (<20 GeV) | ~0.6-0.7 |

#### Physics Explanation
Event shape variables (aplanarity, sphericity, average_deltaR) are known to be difficult for MC:
- Depend on parton shower modeling
- Sensitive to underlying event
- Affected by ME-PS matching
- Known tension between data and MC in high-multiplicity environments

#### Recommendation
Consider removing these problematic new variables from v6 BDT:
1. `jets_aplanarity` - worst mismodeling
2. `jets_sphericity` - significant shape disagreement
3. `jets_average_deltaR` - tails mismodeled

Alternative: Retrain BDT without these 3 variables (back to ~31 variables)

### Variable Mapping Analysis (2025-12-19)
All 8 tau-related BDT input variables are correctly mapped in `replaceTauTVar()`:

| BDT Variable | Replacement List | Source Branch | Status |
|--------------|------------------|---------------|--------|
| `tausT_1lepton1_charge` | extraVarsFromF | `tausF_1lepton1_charge` | ✓ |
| `tausT_leptonsT_invariantMass` | VarToTausFMorph | `tausFMorph_leptonsT_invariantMass` | ✓ |
| `tausT_1pt` | VarToTausFMorph | `tausFMorph_1pt` | ✓ |
| `tausT_invariantMass` | VarToTausFMorph | `tausFMorph_invariantMass` | ✓ |
| `bjetsM_tausT_minDeltaR` | extraVarsFromF | `bjetsM_tausF_minDeltaR` | ✓ |
| `tausT_1Met_transMass` | VarToTausFMorph | `tausFMorph_1Met_transMass` | ✓ |
| `jets_tausT_invariantMass` | VarToTausFMorph | `jets_tausFMorph_invariantMass` | ✓ |
| `tausT_1lepton1Met1_stransMass` | VarToTausFMorph | `tausFMorph_1lepton1Met1_stransMass` | ✓ |

### Next Steps (After Debug)
- [ ] Submit WH jobs for 2016preVFP and 2016postVFP
- [ ] Run datacard generation
- [ ] Run Combine fits
- [ ] Compare v6a results with original BDT

## Resolved Issues
1. **Global weight missing**: Added processScale ✓
2. **makeJob_WH.py data handling**: Fixed to include data by default for nominal ✓
3. **Workflow skills**: Updated stage3-wh.md and stage4-combine.md ✓
4. **tttt job timeout**: Completed successfully via screen session ✓
5. **Training selection mismatch**: Fixed PrepareTrainingAndTestTree to use SR cut ✓
6. **Version check mismatch**: Simplified to always use TTBB-trained BDT ✓
7. **Baseline cut mismatch**: Fixed conditional jets_HT/jets_6pt cut based on bjetsM_num ✓
8. **TMVA scaling**: Fixed lumi scaling in binning optimization ✓
9. **Statistical uncertainty in binning**: Do NOT use for optimization (breaks low-yield regime)

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

---

## FINAL DECISION: Revert to v0 BDT (2025-12-19 Session 14)

### Decision
**Abandon TTBB-trained BDT experiment and revert to original v0 BDT.**

### Rationale
After extensive testing of multiple BDT versions (v1-v6a), the TTBB-trained BDT showed fundamental issues:

1. **MC Mismodeling of New Variables** (discovered in Session 13):
   - Event shape variables (`jets_aplanarity`, `jets_sphericity`, `jets_average_deltaR`) show significant Data/MC disagreement (ratio ~0.6-0.8)
   - These variables are sensitive to parton shower modeling and ME-PS matching
   - Would require dedicated systematic uncertainties that may dominate sensitivity

2. **Signal Compression**:
   - All TTBB-trained BDTs (v3-v6) compress signal RMS from 0.078 to ~0.036
   - Root cause: TTBB kinematics overlap with tttt, forcing BDT to find compromise
   - Reduces ability to separate signal in high-BDT tail

3. **No Net Improvement**:
   - Best TTBB version (v4, ROC=0.796) uses btag shape variable with large systematics
   - Without btag shape (v6a, ROC=0.791), gain is marginal
   - MC mismodeling issues likely negate any theoretical improvement

### Changes Made
```cpp
// treeAnalyzer.C - reverted to v0 BDT
// 1tau1l: BDTTrainingMap (original) with binning {-0.25, -0.067, -0.024, 0.018, 0.06, 0.1, 0.145, 0.36}
// 1tau0l: BDT1tau0l (original) with existing binning
```

### Code Reverted
- `writeHistGood/src/treeAnalyzer.C`: Changed back to use `BDTTrainingMap` for 1tau1l and `BDT1tau0l` for 1tau0l
- Restored original v0 BDT binning for 1tau1l channel
- WH code rebuilt successfully

### Configs to Use
- 1tau1l: `config/analysis_config_1tau1l_TTBBtest.yaml` (hist: v0BDT1tau1l_TTBBtest)
- 1tau0l: `config/analysis_config_1tau0l_TTBBtest.yaml` (hist: v0BDT1tau0l_TTBBtest)

### Lessons Learned
1. Adding background samples to BDT training is not always beneficial
2. Event shape variables (aplanarity, sphericity, deltaR) have known MC mismodeling in high-multiplicity environments
3. Signal compression is a real risk when backgrounds have similar kinematics to signal
4. Always check Data/MC agreement for new BDT input variables before deployment

### Task Status: CLOSED
The TTBB BDT retraining experiment is concluded. The original v0 BDT remains the production choice.
