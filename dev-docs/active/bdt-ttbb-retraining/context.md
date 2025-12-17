# BDT Retraining with TTBB Samples - Context

## Created: 2025-12-16
## Branch: addBDTttbb

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

## BDT Weight Paths (v3BDTttbb - current)

| Era | Channel | Weight File |
|-----|---------|-------------|
| 2018 | 1tau1l | `.../2017/.../v3BDTttbb/inputList_1tau1l_final.csv/.../TMVAClassification_BDT.weights.xml` |
| 2017 | 1tau1l | `.../2018/.../v3BDTttbb/inputList_1tau1l_final.csv/.../TMVAClassification_BDT.weights.xml` |
| 2018 | 1tau0l | (pending v3 training) |
| 2017 | 1tau0l | (pending v3 training) |
