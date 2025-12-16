# BDT Retraining Tasks

## Status: In Progress
## Last Updated: 2025-12-16 Session 3

## Phase 1: Setup
- [x] Create feature branch `addBDTttbb`
- [x] Create dev-docs structure

## Phase 2: Link WH Code to TMVA
- [x] Modify TMVA Makefile (`hua/tmva/newCode/Makefile`)
  - Added WH include paths: `-I$(WH_DIR)/include -I$(WH_DIR)`
  - Link WH object files: `$(WH_DIR)/obj/commenSelectionAndWeight.o`
- [x] Refactor `tmvaBDT_training.C`
  - Include WH headers (`myEventClass.h`, `commenSelectionAndWeight.h`)
  - Updated process lists for 1tau1l and 1tau0l (matching proChannelDic)
  - Added helper functions: `getProcessType()`, `getWeightExpression()`, `getSelectionCut()`
  - Added TTBB samples to process lists
  - Added fakeTau and fakeLepton to process lists
- [x] Build TMVA code successfully
- [x] Add minimum events threshold (50) to prevent statistical fluctuations

## Phase 3: YAML Configs
- [x] Create `config/analysis_config_1tau1l_v1BDTttbb.yaml`
- [x] Create `config/analysis_config_1tau0l_v1BDTttbb.yaml`

## Phase 4: Build & Train
- [x] Build WH code (pre-existing)
- [x] Build TMVA training code
- [x] Add global weight (processScale = lumi*xsec/genWeightSum) - verified matches WH
- [x] Verify processScale matches WH:
  - tttt: 0.0075447 (TMVA) = 0.0075447 (WH) ✓
  - st_tchan: 0.000429314 (TMVA) = 0.000429314 (WH) ✓
  - fakeTau: processScale=1.0 (correct - uses FR_weight_final)
- [x] Verify event counts reasonable:
  - TMVA tttt: 78669 pass selection (baseline+SR)
  - TMVA fakeTau_data: 619 pass selection
- [x] Train 2018 BDT (1tau1l) - **ROC-integ = 0.977-0.978** ✓
  - Log: `logs_v1BDTttbb/training_1tau1l_2018.log`
  - Weight: `.../2018/.../BDTTrain/v1BDTttbb/inputList_1tau1l_final.csv/dataset/weight/TMVAClassification_BDT.weights.xml`
- [ ] **RUNNING (nohup)**: Train 2018 BDT (1tau0l)
  - Log: `logs_v1BDTttbb/training_1tau0l_2018.log`
- [ ] **RUNNING (nohup)**: Train 2017 BDT (1tau1l)
  - Log: `logs_v1BDTttbb/training_1tau1l_2017.log`
- [ ] **RUNNING (nohup)**: Train 2017 BDT (1tau0l)
  - Log: `logs_v1BDTttbb/training_1tau0l_2017.log`

## Phase 5: Integration
- [ ] Update `inputFileMap.h` with new BDT paths
- [ ] Update `treeAnalyzer.C` to use new maps

## Phase 6: Testing
- [ ] Verify training output (weight XML files)
- [ ] Check ROC curves
- [ ] Integration test with WH step
- [ ] Physics validation

## Phase 7: Finalize
- [ ] Commit changes
- [ ] Document results

## Resolved Issues
1. ~~**Global weight missing**~~: Added processScale (lumi*xsec/genWeightSum) for MC processes ✓
2. ~~**Variable lists**~~: Using same input lists as WH step ✓
3. ~~**Statistical fluctuations**~~: Added MIN_EVENTS_THRESHOLD=50 to skip low-stats processes ✓
