# BDT Retraining with TTBB Samples - Context

## Created: 2025-12-16
## Branch: addBDTttbb
## Status: CLOSED - Reverted to v0 BDT (2025-12-19)

## Purpose
Retrain BDT for 1tau1l and 1tau0l channels with:
1. TTBB samples added to background (merged with TT)
2. Consistent selection/weight with WH step via linked code
3. Cross-era training pattern (2018 uses 2017 weights, 2017/2016 use 2018 weights)

## Key Decisions

### Process Selection
- Match `proChannelDic` in `ttttGlobleQuantity.py` exactly
- Include fakeTau and fakeLepton (with their specific selection/weight logic)
- Exclude only data samples (jetHT, leptonSum)

### Integration Approach
- Link WH code (`myEventClass.h`, `commenSelectionAndWeight.C`) to TMVA training
- Use event class for branch reading
- Call `baselineSelection()`, `SR1tau1lSel()`, `baseWeightCal()` directly

### Process-Specific Handling
| Process Type | isMC | isFakeTau | isFakeLepton | Weight Source |
|-------------|------|-----------|--------------|---------------|
| Regular MC | true | false | false | `baseWeightCal()` |
| fakeTau | false | true | false | `FR_weight_final` |
| fakeLepton | false | false | true | `lepTopMVAF_FRweight` |

## Key Files

### To Modify
- `hua/tmva/newCode/tmvaBDT_training.C`
- `hua/tmva/newCode/Makefile`
- `writeHistGood/include/inputFileMap.h`
- `writeHistGood/src/treeAnalyzer.C`

### To Create
- `config/analysis_config_1tau1l_v1BDTttbb.yaml`
- `config/analysis_config_1tau0l_v1BDTttbb.yaml`

### Reference (read-only)
- `writeHistGood/include/myEventClass.h`
- `writeHistGood/include/commenSelectionAndWeight.h`
- `writeHistGood/src/commenSelectionAndWeight.C`
- `hua/src_py/ttttGlobleQuantity.py` (for proChannelDic)

## Training Data
- 2018: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/`
- 2017: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/`

## Variable Lists (must match WH step)
- 1tau1l: `inputList_noTauTT.csv` (from WH inputFileMap.h)
- 1tau0l: `inputList_finalFinal25.csv` (25 variables)

## Progress Notes
- 2025-12-16: Plan approved, branch created, starting implementation
- 2025-12-16 Session 2:
  - Completed Makefile modification (WH include paths + object linking)
  - Completed tmvaBDT_training.C refactor:
    - Added WH headers (myEventClass.h, commenSelectionAndWeight.h)
    - Updated process lists to match proChannelDic exactly
    - Added helper functions: getProcessType(), getWeightExpression(), getSelectionCut()
    - Updated main() to accept channel parameter
  - Build successful (one minor warning fixed)
  - Created YAML configs for both channels
  - Added global weight (processScale = lumi*xsec/genWeightSum) - matches WH exactly
  - Removed unused g_weight parameter from function signature
  - **ProcessScale verification**:
    - tttt: 0.0075447 (matches WH log)
    - st_tchan: 0.000429314 (matches WH log)
    - fakeTau: processScale=1.0 (correct, uses FR_weight_final)
  - Test training completed: ROC-integ = 0.783
- 2025-12-16 Session 3:
  - Fixed PrepareTrainingAndTestTree to use empty cut (was causing FATAL error)
  - **Added minimum events threshold (50)** to prevent statistical fluctuations:
    - Skip background processes with <50 events after selection
    - Prints warnings for skipped processes + summary at end
  - **2018 1tau1l training running** with 10 processes skipped:
    - ttbar_0l (0), ttbar_1l (3), TTBB_4f_TTToHadronic (0), TTBB_4f_TTToSemiLeptonic (2)
    - TTWJetsToQQ (16), fakeLepton (27)
    - st_tW_antitop (3), st_tW_top (3), st_schan_lep (0), st_tchan (0)
  - Final training stats: signal=78669, background=57560
  - Log: `training_1tau1l_2018.log`
  - Output: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/BDTTrain/v1BDTttbb/`
- 2025-12-16 Session 4:
  - **2018 1tau1l training COMPLETE**: ROC-integ = 0.977-0.978 (excellent!)
  - Verified selection matches WH step (1tau1lSR and 1tau0lSR cuts consistent)
  - Fixed 1tau0l variable list path (was pointing to wrong directory)
  - Started all remaining trainings with nohup:
    - 2018 1tau0l, 2017 1tau1l, 2017 1tau0l
  - Logs saved to `logs_v1BDTttbb/` directory
  - Updated pre-tool-use hook to block all `rm -rf` commands
- 2025-12-17 Session 7:
  - **CRITICAL BUG FIXED**: Jobs were using OLD BDT weights (v1finalVar27) not v2BDTttbb
  - Root cause: `treeAnalyzer.C` checked `m_histVersion.Contains("v1BDTttbb")` but config had `v2BDTttbb_1tau1l`
  - Fix: Removed version check, always use `BDT1tau1l_TTBBtrain` / `BDT1tau0l_TTBBtrain` maps
  - Commit: `16369fd9 fix: Always use TTBB-trained BDT (v2) for all channels`
  - Resubmitted 314 WH jobs (76×2 for 2018, 81×2 for 2017)
  - Verified via log that jobs now use correct v2BDTttbb weights
- 2025-12-17 Session 8:
  - **CRITICAL BUG #2**: Training entries not matching WH exactly (2-3% fewer)
  - Root cause: Baseline cut mismatch
    - Training used: `jets_HT>500 && jets_6pt>40` (hard-coded)
    - WH uses conditional based on bjetsM_num:
      - If `bjetsM_num < 4`: `jets_HT > 500 && jets_6pt > 40`
      - If `bjetsM_num >= 4`: `jets_HT > 480 && jets_6pt > 38`
  - **v3BDTttbb training completed** with exact WH baseline match:
    - 2018 1tau1l: ROC-integ = 0.778
    - 2017 1tau1l: ROC-integ = 0.798
  - Entry verification: ALL processes match WH exactly (tttt: 78674, fakeTau: 640, etc.)
  - Commit: `a8b29626 fix: v3BDTttbb training with exact WH baseline cut match`
  - WH jobs resubmitted (76 for 2018, 81 for 2017)
- 2025-12-17 Session 9:
  - **Validation Issue**: v3BDTttbb with old binning showed -2.7% worse S/sqrt(B)
  - Root cause: Old binning [-0.25, 0.36] mismatched v3BDT score range [-0.10, 0.21]
  - **Binning optimization** using training output histograms (MVA_BDT_S/B)
  - New optimized binning: `{-0.100, 0.009, 0.033, 0.048, 0.064, 0.087, 0.119, 0.213}`
  - Created `optimizeBinning_fromTraining.py` script for future use
  - Commit: `ca7a778c feat: Optimize BDT binning for v3BDTttbb score range`
- 2025-12-17 Session 10-11:
  - **Phase 14 Testing**: Added 7 new variables to improve tttt vs TTBB separation
  - v4BDT (33 vars): ROC=0.796, Top20% S/B=0.223 (**BEST**)
  - v5BDT (32 vars, no BscoreSum): ROC=0.780
  - **Key finding**: `jets_4largestBscoreSum` adds +0.016 to ROC but introduces systematics
  - **Signal RMS compression**: TTBB training compresses signal (0.036 vs 0.078 in v0)
  - Created `analyzeSeparation_tttt_vs_ttbb.py` for variable ranking
  - Next: Testing options A (upweight), B (deeper trees), D (add vars) without btag shape
  - Commit: `4b97089e feat: Add extended variable lists and separation analysis`

## Key Commands

### Check job status
```bash
hep_q -u huahuil
```

### Check output file count
```bash
ls /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/variableHists_v2BDTttbb_1tau1l/*.root | wc -l
```

### Verify BDT weight in logs
```bash
grep "training input" /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/variableHists_v2BDTttbb_1tau1l/log/TTZToLLNuNu.log
```

## Binning Optimization Method: Hybrid Binning (PREFERRED)

**Key insight**: Use fewer bins in low-BDT region (background-dominated), finer bins in high-BDT region (signal-concentrated).

### Statistical Uncertainty in Optimization (IMPORTANT NOTE)
The `calSig_lastBin()` function in `optimizeBinning.py` has a commented-out option to consider statistical uncertainty:
```python
# dataLast = (sLast + bLast) - np.sqrt(sLast + bLast)  # conservative
dataLast = (sLast + bLast)  # used (no stat unc)
```

**Why NOT use stat uncertainty for optimization**:
- With low yields (S~2, B~3 after Run2 scale), √(S+B) ≈ 2.3 is comparable to signal
- After subtracting √(S+B), observed data can become **less than background**
- This makes p-value ≈ 1 (no significance), breaking the optimization

**Tested result** (v6a last bin, Run2 x3 scale):
| Method | Observed | Background | Z-score |
|--------|----------|------------|---------|
| No stat unc | 5.44 | 3.40 | 0.66 |
| With stat unc | 3.11 | 3.40 | -0.41 |

**Conclusion**: Use method WITHOUT stat uncertainty for binning optimization. The proper statistical treatment (Poisson likelihood) is handled by Combine during the fit.

### Hybrid Binning Algorithm
1. First bin covers entire low-BDT region (background dump)
2. Finer bins in signal region (BDT > 0.05) to capture signal shape
3. Last bin optimized for maximum S/B

### v6a 1tau1l Binning (8 bins, S/√B = 1.40)
```cpp
std::vector<Double_t> bins1tau1l = {-0.10, 0.02, 0.05, 0.065, 0.08, 0.095, 0.11, 0.13, 0.22};
```

| Bin Range | S | B | S/√B |
|-----------|---|---|------|
| [-0.10, 0.02] | 0.07 | 20.6 | 0.014 |
| [0.02, 0.05] | 0.22 | 29.1 | 0.042 |
| [0.05, 0.065] | 0.24 | 22.1 | 0.050 |
| [0.065, 0.08] | 0.40 | 16.7 | 0.097 |
| [0.08, 0.095] | 0.54 | 11.3 | 0.160 |
| [0.095, 0.11] | 0.67 | 15.8 | 0.168 |
| [0.11, 0.13] | 0.66 | 8.8 | 0.223 |
| [0.13, 0.22] | 0.68 | 1.1 | **0.640** |

**Comparison with other methods**:
| Method | S/√B | N_bins |
|--------|------|--------|
| Equal BG/bin | 1.22 | 7 |
| Even binning | 1.23 | 7 |
| **Hybrid** | **1.40** | **8** |
| Last-bin optimized | 1.60 | 19 (too many) |

## BDT Weight Paths (v6aBDTttbb - current)

| Era | Channel | Weight File | Status |
|-----|---------|-------------|--------|
| 2018 | 1tau1l | `.../2017/.../v6aBDTttbb/inputList_1tau1l_v6extended.csv/.../TMVAClassification_BDT.weights.xml` | ✓ Complete |
| 2017 | 1tau1l | `.../2018/.../v6aBDTttbb/inputList_1tau1l_v6extended.csv/.../TMVAClassification_BDT.weights.xml` | ✓ Complete |
| 2018 | 1tau0l | (pending v6a training) | Pending |
| 2017 | 1tau0l | (pending v6a training) | Pending |

## WH Production Status (v6aBDTttbb_1tau1l) - ABANDONED

| Era | Files | Status | Last Bin S/B |
|-----|-------|--------|--------------|
| 2018 | 71/71 | ✓ Complete | 0.42/2.54 |
| 2017 | 71/71 | ✓ Complete | 0.36/2.27 |
| 2016preVFP | - | Abandoned | - |
| 2016postVFP | - | Abandoned | - |

---

## Final Outcome (2025-12-19)

**Decision**: Reverted to original v0 BDT due to:
1. MC mismodeling of event shape variables (aplanarity, sphericity, average_deltaR)
2. Signal compression from TTBB kinematic overlap with tttt
3. Marginal ROC improvement not worth systematic uncertainty burden

**Production BDT**: v0 (original, without TTBB training)
- 1tau1l: `BDTTrainingMap` with binning `{-0.25, -0.067, -0.024, 0.018, 0.06, 0.1, 0.145, 0.36}`
- 1tau0l: `BDT1tau0l` with existing optimized binning

See `tasks.md` for full rationale and lessons learned.
