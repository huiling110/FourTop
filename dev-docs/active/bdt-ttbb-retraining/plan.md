# Plan: BDT Retraining with TTBB Samples

## Overview
Retrain BDT for 1tau1l and 1tau0l channels with TTBB samples added as background, using consistent selection and weights with WH step by **linking WH code directly to TMVA training**.

## User Requirements
1. Update processes to match WH step exactly (MC only, excluding fake estimation processes)
2. **Link WH code (event class, selection functions) to TMVA training** for perfect consistency
3. Weight calculation via WH's `baseWeightCal()` function
4. Cross-era training: Train 2017 & 2018 separately; 2018 uses 2017 weights, 2017/2016 use 2018 weights
5. New YAML configs with hist version prefix `v1BDTttbb_`
6. Test in new branch

## Verified Prerequisites
- TTBB samples exist in Stage 2 output for both 2017 and 2018:
  - `TTBB_4f_TTToHadronic.root`, `TTBB_4f_TTToSemiLeptonic.root`, `TTBB_4f_TTTo2L2Nu.root`
- WH step handles TTBB via `histoGramPerSample` mapping to 'ttbb' category
- Cross-era BDT pattern implemented for 1tau0l in `inputFileMap.h`

## Key Point: Include All Processes from proChannelDic
- Process lists MUST match `proChannelDic` in `ttttGlobleQuantity.py` exactly
- Exclude only data samples (jetHT, leptonSum)
- **fakeTau** and **fakeLepton** ARE included with their specific selection/weight logic

---

## Phase 1: Setup

### 1.1 Create Feature Branch
```bash
git checkout -b addBDTttbb addVLL
```

### 1.2 Create Dev-Docs Structure
```
dev-docs/active/bdt-ttbb-retraining/
├── plan.md
├── context.md
└── tasks.md
```

---

## Phase 2: Link WH Code to TMVA Training

### 2.1 Modify TMVA Makefile

**File:** `hua/tmva/newCode/Makefile`

Add WH include paths and link WH object files:

```makefile
# Add WH directories
WH_DIR = ../../../writeHistGood
WH_INC = -I$(WH_DIR)/include
WH_OBJ = $(WH_DIR)/obj/commenSelectionAndWeight.o

CXXFLAGS += $(WH_INC)
LIBS += $(WH_OBJ)
```

### 2.2 Update Process Lists in `tmvaBDT_training.C`

**File:** `hua/tmva/newCode/tmvaBDT_training.C`

Update `getProcessesVec()` to match `proChannelDic` in `ttttGlobleQuantity.py` exactly:

**proChannelDic reference:**
```python
'1tau1l': ['fakeTau', 'tt', 'ttbb', 'ttX', 'fakeLepton', 'singleTop', 'tttt', 'jetHT']
'1tau0l': ['fakeTau', 'tt', 'ttbb', 'ttX', 'singleTop', 'WJets', 'tttt', 'jetHT']
```

For **1tau1l** (from proChannelDic, excluding jetHT data):
```cpp
{"1tau1l", {
    "tttt",  // signal (index 0)
    // fakeTau category
    "fakeTau_data_ptMorphed",  // data-driven fake tau
    "fakeTau_MC_ptMorphed",    // MC fake tau
    // tt category
    "ttbar_0l", "ttbar_1l", "ttbar_2l",
    // ttbb category (NEW)
    "TTBB_4f_TTToHadronic", "TTBB_4f_TTToSemiLeptonic", "TTBB_4f_TTTo2L2Nu",
    // ttX category
    "TTZToLLNuNu", "TTZToQQ", "TTWJetsToLNu", "TTWJetsToQQ", "ttH_bb", "ttH_nonbb",
    // fakeLepton category (1tau1l specific)
    "fakeLepton",
    // singleTop category
    "st_tW_antitop", "st_tW_top", "st_schan_lep", "st_tchan",
    // NOTE: No WJets in 1tau1l per proChannelDic
    // NOTE: No jetHT (data)
}},
```

For **1tau0l** (includes WJets, no fakeLepton):
```cpp
{"1tau0l", {
    "tttt",  // signal (index 0)
    // fakeTau category
    "fakeTau_data_ptMorphed", "fakeTau_MC_ptMorphed",
    // tt + ttbb
    "ttbar_0l", "ttbar_1l", "ttbar_2l",
    "TTBB_4f_TTToHadronic", "TTBB_4f_TTToSemiLeptonic", "TTBB_4f_TTTo2L2Nu",
    // ttX
    "TTZToLLNuNu", "TTZToQQ", "TTWJetsToLNu", "TTWJetsToQQ", "ttH_bb", "ttH_nonbb",
    // singleTop
    "st_tW_antitop", "st_tW_top", "st_schan_lep", "st_tchan",
    // WJets (1tau0l specific)
    "WJetsToLNu_HT-200To400", "WJetsToLNu_HT-400To600", "WJetsToLNu_HT-600To800",
    "WJetsToLNu_HT-800To1200", "WJetsToLNu_HT-1200To2500", "WJetsToLNu_HT-2500ToInf",
    // NOTE: No fakeLepton in 1tau0l per proChannelDic
    // NOTE: No jetHT (data)
}},
```

### 2.3 Refactor Training Loop to Use WH Selection & Weights

**Major change:** Replace TMVA's simple tree addition with event-by-event loop using WH `event` class.

Include WH headers:
```cpp
#include "writeHistGood/include/myEventClass.h"
#include "writeHistGood/include/commenSelectionAndWeight.h"
```

**Process-specific parameters for WH functions:**

| Process Type | isMC | isFakeTau | isFakeLepton | Weight Source |
|-------------|------|-----------|--------------|---------------|
| Regular MC (tttt, tt, ttbb, ttX, singleTop, WJets) | true | false | false | `baseWeightCal()` |
| fakeTau (fakeTau_data_ptMorphed, fakeTau_MC_ptMorphed) | false | **true** | false | `FR_weight_final` branch |
| fakeLepton | false | false | **true** | `lepTopMVAF_FRweight` branch |

Refactor process loading to apply WH selection with process-specific parameters:
```cpp
// Determine process type from filename
Bool_t isFakeTau = processName.Contains("fakeTau");
Bool_t isFakeLepton = processName.Contains("fakeLepton");
Bool_t isMC = !isFakeTau && !isFakeLepton;  // MC = not fake estimation

// For each process file
TFile *file = TFile::Open(filename);
TTree *tree = (TTree*)file->Get("newtree");
event *evt = new event(tree);

// Apply WH selection per event
for(Long64_t i = 0; i < tree->GetEntries(); i++) {
    tree->GetEntry(i);

    // Apply baseline selection
    if(!baselineSelection(evt, false /*isRun3*/, false /*is1tau2l*/)) continue;

    // Apply SR selection with process-specific flags
    // SR1tau1lSel(evt, channel, isRun3, isFakeTau, isFakeLepton, isMC, ifFakeTau)
    if(!SR1tau1lSel(evt, channelInt, false, isFakeTau, isFakeLepton, isMC, true)) continue;

    // Calculate weight with process-specific flags
    // baseWeightCal(evt, entry, isRun3, isData, channel, isFakeTau, isFakeLepton)
    Double_t weight = baseWeightCal(evt, i, false, false, channelInt, isFakeTau, isFakeLepton);

    // Fill filtered tree with weight
    // ...
}
```

**Selection logic difference (from `commenSelectionAndWeight.C`):**
- **Regular MC**: `isTightPrompt` for leptons, `genFlavour!=0` for taus
- **fakeTau**: `!isTight` for taus (application region)
- **fakeLepton**: `isAR` (application region) for leptons

---

## Phase 3: Create New YAML Configs

### 3.1 Create `config/analysis_config_1tau1l_v1BDTttbb.yaml`

```yaml
metadata:
  name: "1tau1l_v1BDTttbb"
  description: "BDT retrained with TTBB samples included, consistent with WH step"
  created: "2025-12-16"

versions:
  stage1: "v94HadroPreJetVetoHemOnly_TTBBtest"
  stage2: "v1baselineHadro"
  hist: "v1BDTttbb_1tau1l"
  datacard: "v1_ttbb_bdtretrain"
  combination: "combinationV22"

channel: "1tau1l"

eras:
  - "2018"
  - "2017"
  - "2016postVFP"
  - "2016preVFP"

options:
  fake_tau: true
  mc_fake_tau: false
  blind: false
  systematics: true
  smoothing: true
  ifVLL: false

paths:
  nanoaod_base: "/publicfs/cms/data/TopQuark/nanoAOD"
  output_base: "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
```

### 3.2 Create `config/analysis_config_1tau0l_v1BDTttbb.yaml`

Same structure with `channel: "1tau0l"` and `hist: "v1BDTttbb_1tau0l"`

---

## Phase 4: Execute Training

### 4.1 Training Directories

Input (Stage 2 output):
- 2018: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/`
- 2017: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/`

Output (new training):
- 2018 training: `.../2018/.../BDTTrain/v1BDTttbb/`
- 2017 training: `.../2017/.../BDTTrain/v1BDTttbb/`

### 4.2 Training Execution Order

1. **Train 2018 BDT** (will be applied to 2017/2016preVFP/2016postVFP)
2. **Train 2017 BDT** (will be applied to 2018)

For each channel (1tau1l, 1tau0l):
```bash
cd hua/tmva/newCode
source ../../setEnv_newNew.sh
make clean && make

# Train 2018
./my_program \
    /publicfs/.../2018/.../mc/ \
    /publicfs/.../2018/.../mc/BDTTrain/v1BDTttbb/ \
    0 \
    /workfs2/.../inputList/inputlist_1tau1l_leading7.csv \
    "${g_weight_1tau1l}" \
    1tau1l \
    ""

# Train 2017 (similar)
```

---

## Phase 5: Update inputFileMap.h

**File:** `writeHistGood/include/inputFileMap.h`

Add new BDT maps for TTBB-trained weights with cross-era application:

```cpp
// 1tau1l with TTBB training
inline const std::map<TString, std::array<TString, 2>> BDT1tau1l_TTBBtrain = {
    {"2018", {
        "/workfs2/.../inputList/inputlist_1tau1l_leading7.csv",
        "/publicfs/.../2017/.../BDTTrain/v1BDTttbb/dataset/weight/TMVAClassification_BDT.weights.xml"  // 2018 uses 2017 training
    }},
    {"2017", {
        "/workfs2/.../inputList/inputlist_1tau1l_leading7.csv",
        "/publicfs/.../2018/.../BDTTrain/v1BDTttbb/dataset/weight/TMVAClassification_BDT.weights.xml"  // 2017 uses 2018 training
    }},
    {"2016preVFP", {/* same as 2017 */}},
    {"2016postVFP", {/* same as 2017 */}},
};

// 1tau0l similar structure
inline const std::map<TString, std::array<TString, 2>> BDT1tau0l_TTBBtrain = {
    // ...
};
```

Also update `treeAnalyzer.C` to use these new maps when hist version contains "v1BDTttbb".

---

## Phase 6: Testing

### 6.1 Verify Training Output
- Check weight XML files exist
- Verify ROC curves in training output (AUC > 0.7 expected)
- Compare BDT score distributions before/after TTBB

### 6.2 Integration Test
```bash
cd writeHistGood && make
./apps/run_treeAnalyzer.out \
    /publicfs/.../2018/.../mc/ \
    tttt \
    1tau1l \
    v1BDTttbb_test \
    0 1 2018
```

### 6.3 Physics Validation
- Compare yields with previous training
- Check TTBB discrimination
- Verify signal efficiency maintained

---

## Files to Modify

| File | Changes |
|------|---------|
| `hua/tmva/newCode/tmvaBDT_training.C` | Major refactor: include WH event class, use WH selection/weight functions, update process lists |
| `hua/tmva/newCode/Makefile` | Add WH include paths and link WH object files |
| `writeHistGood/include/inputFileMap.h` | New BDT maps for cross-era weights |
| `writeHistGood/src/treeAnalyzer.C` | Logic to select new BDT maps based on hist version |
| `config/analysis_config_1tau1l_v1BDTttbb.yaml` | New config file |
| `config/analysis_config_1tau0l_v1BDTttbb.yaml` | New config file |

### Key WH Files to Include (read-only)

| File | Purpose |
|------|---------|
| `writeHistGood/include/myEventClass.h` | Event class with branch reading (`myBranch<T>` template) |
| `writeHistGood/include/commenSelectionAndWeight.h` | Selection and weight function declarations |
| `writeHistGood/src/commenSelectionAndWeight.C` | Selection (`baselineSelection`, `SR1tau1lSel`) and weight (`baseWeightCal`) implementations |

---

## Risks and Mitigations

| Risk | Mitigation |
|------|------------|
| WH code compilation issues | Ensure WH is built first; verify include paths and object file availability |
| Selection perfectly consistent | Using WH functions directly guarantees consistency |
| Weight perfectly consistent | Using `baseWeightCal()` function guarantees consistency |
| TTBB overlap with TT | Already handled by ghost-matching at Stage 1 |
| Cross-era BDT degradation | Compare ROC curves; era-specific training already planned |
| Event class initialization | Ensure all required branches exist in training input files |

---

## Repercussions

1. **Stage 2 (MV)**: No changes needed - MV doesn't apply BDT scoring
2. **Stage 3 (WH)**: Must use updated `inputFileMap.h` to load new BDT weights when hist version contains "v1BDTttbb"
3. **Stage 4+ (Combine)**: No changes - uses hist output with new version string
4. **Fake estimation**: Remains unchanged - fake tau/lepton use data-driven methods
5. **TMVA training dependency**: Now depends on WH code being compiled first

---

## Execution Summary

1. Create branch `addBDTttbb`
2. Modify TMVA Makefile to link WH code
3. Refactor `tmvaBDT_training.C` to use WH event class and selection/weight functions
4. Build: `cd writeHistGood && make` (ensure WH compiled first)
5. Build: `cd hua/tmva/newCode && make`
6. Train 2018 BDT for 1tau1l and 1tau0l
7. Train 2017 BDT for 1tau1l and 1tau0l
8. Update `inputFileMap.h` with new BDT weight paths (cross-era)
9. Create new YAML configs
10. Test WH step with new BDT weights
11. Commit and document
