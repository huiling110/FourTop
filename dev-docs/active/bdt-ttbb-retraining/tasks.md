# BDT Retraining Tasks

## Status: In Progress - Testing
## Last Updated: 2025-12-16 Session 6

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

## Phase 9: Full Production - READY
- [ ] Submit full WH jobs for 2017/2018 with v2BDTttbb_1tau1l version
- [ ] Generate datacards
- [ ] Run combine fits

## Resolved Issues
1. **Global weight missing**: Added processScale ✓
2. **makeJob_WH.py data handling**: Fixed to include data by default for nominal ✓
3. **Workflow skills**: Updated stage3-wh.md and stage4-combine.md ✓
4. **tttt job timeout**: Completed successfully via screen session ✓
5. **Training selection mismatch**: Fixed PrepareTrainingAndTestTree to use SR cut ✓
