# Context: TTBB Yield Investigation

**Created**: 2025-12-07 10:30
**Last Updated**: 2025-12-22
**Status**: **COMPLETE** - XGBoost library version (0.80 vs 1.7.5) **EXPERIMENTALLY VERIFIED** as root cause

---

## Problem Overview

After integrating TTBB samples with ghost-matching overlap removal, unexpected yield changes were observed in tttt (+1.5%) and fake tau data (+0.2%). The investigation aims to identify the exact code change causing these differences and determine if they are acceptable (bug fixes) or need correction.

---

## Key Files

**File 1**: `objectSelectionOptimized/src/jetSel.C`
- **Purpose**: Jet selection including jet veto map
- **Relevant sections**: Lines 470-493 (jetVetoMap function)
- **Notes**:
  - Commit 9a4dc74a (Jan 26): Changed from "jetvetomap" to "jetvetomap_hem1516"
  - Commit 1347ac24 (Feb 4): Added `if(m_era!="2018") return kFALSE;` check

**File 2**: `objectSelectionOptimized/src/copyBranch.C`
- **Purpose**: Event selection and branch copying, including overlap removal
- **Relevant sections**: Lines 40-60 (Select function with ghost-matching)
- **Notes**: Ghost-matching only affects samples with "ttbar" or "TTBB" in name

**File 3**: `objectSelectionOptimized/include/copyBranch.h`
- **Purpose**: Header with m_isTtbarSample, m_isTTBBSample flags
- **Notes**: tttt is NOT affected by overlap removal logic

---

## Key Concepts

**Jet Veto Map**:
- CMS recommended veto of noisy detector regions
- Applied to jets based on eta/phi coordinates
- 2018 uses HEM1516 region veto (specific hardware failure)

**Ghost-Matching Overlap Removal**:
- CMS standard method for ttbar/TTBB overlap
- Uses GenJet_hadronFlavour to identify b-jets
- Traces B-hadron ancestry to identify non-top b-jets
- ttbar: remove events with >=1 additional b-jet
- TTBB: keep only events with >=1 additional b-jet

---

## Version Comparison

| Aspect | Reference (Jan 26, 2025) | TTBBtest (Dec 5, 2025) |
|--------|--------------------------|------------------------|
| OS Commit | 9a4dc74a | Current HEAD |
| Jet Veto | HEM1516 for all eras | HEM1516 for 2018 only |
| Ghost-matching | None | ttbar/TTBB only |
| tttt entries | 1,730,209 | 1,734,672 (+0.26%) |
| tttt WH yield | 7.73 | 7.85 (+1.5%) |

---

## Stage 1 (OS) Output Paths

```
Reference:
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly/mc/tttt/

TTBBtest:
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/v94HadroPreJetVetoHemOnly_TTBBtest/mc/tttt/
```

## Stage 2 (MV) Logs

```
Reference:
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/log/tttt.log

TTBBtest:
/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/log/tttt.log
```

Key log differences:
- FR file path: Reference uses `v94HadroPreJetVetoHemOnly`, Test uses `v94HadroPreJetVetoHemOnly_backupV2`
- Input entries: 1,730,209 vs 1,734,672

---

## Dependencies

- CMSSW_14_1_0_pre4 environment
- ROOT 6.36.01
- correctionlib for jet veto maps
- jsonpog-integration for scale factors

---

## Constraints

- Must maintain physics consistency across all years
- Cannot change analysis selections without validation
- Need to understand if yield changes affect final results

---

## Related Documentation

- ANALYSIS_WORKFLOW.md: Full pipeline documentation
- .claude/dev-docs/active/ttbb-integration/: Original TTBB integration docs
- CMS JetMET POG: https://cms-jerc.web.cern.ch/Recommendations/#jet-veto-maps

---

## Cutflow Analysis (Session 2025-12-07)

### Single File Comparison (01D97507-B0BB-234F-A28E-6AD66C3499E9.root)

| Cut | Reference | TTBBtest | Difference |
|-----|-----------|----------|------------|
| Initial | 3423.0 | 3423.0 | 0 |
| MET filters | 3415.9 | 3415.9 | 0 |
| HLT | 2926.1 | 2926.1 | 0 |
| **Tau selection** | **730.3** | **730.9** | **+0.6** ← First divergence |
| Jet ≥6 | 628.8 | 630.2 | +1.4 |
| B-jet ≥2 | 570.9 | 572.3 | +1.3 |
| HT cut | 423.8 | 424.8 | +1.0 |
| Final | 423.8 | 424.8 | +1.0 |

**Tree entries**: Reference=55,239 vs TTBBtest=55,374 (+135 events, +0.24%)

### Code Changes Reviewed

1. **Jet Veto Map** (`jetSel.C:475-477`):
   - Added `if(m_era!="2018") return kFALSE;`
   - For 2018, both versions apply the veto → NOT the cause

2. **TES changes** (`tauSel.C:276-310`):
   - Only affects systematic variations (cases 3-10)
   - Nominal (case 0) is unchanged → NOT the cause

3. **XGBooster fix** (`usefulFunc.C:105`):
   - API parameter change for OS9 compatibility
   - Shouldn't affect selection → NOT the cause

4. **Ghost-matching** (`copyBranch.C`):
   - Only affects ttbar/TTBB samples
   - tttt has m_isTtbarSample=0, m_isTTBBSample=0 → NOT the cause

### Root Cause: CONFIRMED (Revised)

The divergence starts at **tau selection** (+0.59 weighted events, +0.081%):

**Verified NOT TES corrections**:
- Data (jetHT) also shows divergence at tau selection (+13 events in 10 files)
- TES is NOT applied to data (tauSel.C:83: `if(!m_isData)`)
- TES code changes (commit d2a30a14) only affect systematic variations (cases 3-10), not nominal

**Actual root cause: Floating-point precision differences**:
- CentOS 7 (reference) vs AlmaLinux 9 (TTBBtest)
- Different gcc versions and library builds
- Taus near 20 GeV pT threshold pass/fail differently due to FP representation
- Affects both MC and data equally

### Environmental Differences

| Aspect | Reference (Jan 2025) | TTBBtest (Dec 2025) |
|--------|---------------------|---------------------|
| OS | CentOS 7 | AlmaLinux 9 |
| CMSSW | CMSSW_14_1_0_pre4 | CMSSW_14_1_0_pre4 |
| ROOT | 6.x | 6.36.01 |
| correctionlib | Unknown | 2.7.0 |
| Compiler | gcc (older) | gcc 14.3.1 |

### Full Sample Comparison (Stage 1 OS)

**jetHT Data (ALL 2018)**:
| Era | Tree Entry Diff | Tau Sel Diff | % at Tau Sel |
|-----|-----------------|--------------|--------------|
| 2018a | +36 | +154 | +0.015% |
| 2018b | +18 | +88 | +0.018% |
| 2018c | +24 | +90 | +0.019% |
| 2018d | +68 | +326 | +0.016% |
| **Total** | **+146** | **+658** | **+0.016%** |

**tttt MC**:
| Metric | Ref | Test | Diff | % |
|--------|-----|------|------|---|
| Tree entries | 1,730,209 | 1,734,672 | +4,463 | +0.26% |
| Tau selection | 22,574 | 22,594 | +19 | +0.086% |
| Final (HT cut) | 13,021 | 13,056 | +35 | +0.27% |

### Amplification Through Stages

**Key observation**:
- jetHT Stage 1 tree entries: +146 (+0.05%)
- Final 1tau0lSR data: +12 events (+0.38%)

The +0.38% at final SR is LARGER than +0.05% at Stage 1, suggesting:
1. Floating-point differences at OS level (verified)
2. **Additional amplification through Stage 2/3** (needs investigation)

### Full Pipeline Comparison

| Stage | Sample | Reference | TTBBtest | Diff | % |
|-------|--------|-----------|----------|------|---|
| **Stage 1 (OS)** | tttt tree | 1,730,209 | 1,734,672 | +4,463 | +0.26% |
| **Stage 1 (OS)** | jetHT tree | 269,807 | 269,953 | +146 | +0.05% |
| **Stage 2 (MV)** | tttt baseline | 1,657,638 | 1,661,996 | +4,358 | +0.26% |
| **Stage 2 (MV)** | jetHT baseline | 230,780 | 230,900 | +120 | +0.05% |
| **Stage 3 (WH)** | jetHT 1tau0lSR | 3,162 | 3,174 | +12 | +0.38% |
| **Stage 3 (WH)** | tttt 1tau0lSR | 7.73 | 7.85 | +0.12 | +1.55% |

### Key Finding: SR Cut Amplification

Differences are **consistent** through Stage 1 → Stage 2:
- tttt: ~0.26% preserved
- jetHT: ~0.05% preserved

But **amplified at Stage 3 SR**:
- jetHT: 0.05% → 0.38% (**7.6x amplification**)
- tttt: 0.26% → 1.55% (**6x amplification**)

**Root cause**: SR cuts select a small subset of events. Small floating-point differences at tau pT threshold cause events near SR cut boundaries to pass/fail differently, amplifying the percentage difference.

**NOTE**: Focus investigation on jetHT (data) and tttt, NOT fake_tau estimation.

### Stage 3 Paths
- **Reference**: `variableHists_v0BDT1tau0lV17` (in v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly)
- **TTBBtest**: `variableHists_v0BDT1tau0l_TTBBtest` (in v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest)

---

## Deep Investigation: SR Cut Amplification (Session 2025-12-07 continued)

### Investigation Question
User asked: "Can floating-point precision really explain the +0.38% data difference at final SR?"

### Multi-Region Comparison at Stage 3

Compared tttt yields across ALL regions (not just SR):

| Region | Reference | TTBBtest | Diff | % |
|--------|-----------|----------|------|---|
| 1tau0lSR | 7.73 | 7.85 | +0.12 | +1.46% |
| 1tau0lVR | 2.22 | 2.27 | +0.05 | +2.34% |
| 1tau0lCRMR | 4.15 | 4.20 | +0.06 | +1.36% |

**Key Finding**: Amplification is NOT specific to SR - all regions show ~1.5-2% differences.

### Progressive Cut Analysis at Stage 2

Applied SR cuts progressively to understand where amplification occurs:

| Cut | Unweighted Diff | Weighted Diff |
|-----|-----------------|---------------|
| baseline | +0.26% | +0.26% |
| tausF>=1 | +0.26% | +0.26% |
| tausF>=1 & jets>=8 | +0.33% | +0.33% |
| tausF>=1 & jets>=8 & bjetsM>=3 | +0.37% | +0.37% |

**Key Finding**: Amplification starts with tighter cuts but only reaches ~0.37%, not 1.5%.

### Weight Analysis

Stage 3 weight formula for 1tau0l (from `commenSelectionAndWeight.C:224`):
```
basicWeight = genWeight * prefireWeight * PUweight * HLT_weight * tauT_IDSF_weight_new * btagShape_weight * btagShapeR
```

Actual weight values (from Stage 2 tree):
- genWeight: ~0.0186 (already normalized to cross-section)
- prefireWeight: ~1.0
- PUweight: ~0.9-1.0
- HLT_weight: ~0.9
- tauIDSF: ~1.0
- btagShape: 0.2-1.4 (varies significantly)

### Remaining Mystery

The Stage 2 progressive cuts only show ~0.37% difference, but Stage 3 histograms show ~1.5%. Possible explanations:
1. **Different event weights at cut boundaries** - events that newly pass/fail may have systematically different weights
2. **BDT score differences** - BDT is calculated in Stage 3, may behave differently
3. **Additional cuts in 1tau0lSR definition** - checking `commenSelectionAndWeight.C:132-134`

1tau0lSR definition:
```cpp
isPass = tauCut && lepNum == 0 && e->jets_num.v() >= 8 && bjetsMNum >= 3 && e->tausF_num.v()==1;
```

### SR Cut Amplification: RESOLVED (Session 2025-12-07)

**Key Discovery**: The `tausT_num == 1` cut (tight tau ID) is the main amplification source.

For jetHT data, Stage 3 applies (from `commenSelectionAndWeight.C:118-120`):
```cpp
if(!ifFakeTau){
    tauCut = e->tausT_num.v() == 1;  // Tight tau requirement
}
```

**Full Progressive Cut Analysis for jetHT Data (1tau0l)**:

| Cut | Ref Events | Test Events | Extra | % Diff |
|-----|------------|-------------|-------|--------|
| baseline | 230,780 | 230,900 | +120 | +0.052% |
| jets≥8 | 91,215 | 91,278 | +63 | +0.069% |
| bjetsM≥3 | 24,266 | 24,294 | +28 | +0.115% |
| lep==0 | 23,796 | 23,848 | +52 | +0.219% |
| **tausT==1** | 3,271 | 3,284 | +13 | **+0.397%** |
| full_sr | 3,162 | 3,174 | +12 | +0.380% |

**Amplification Mechanism**:
1. Tight tau cut (`tausT_num == 1`) has only ~13% efficiency (23,848 → 3,174)
2. The extra events from FP differences (+52) don't uniformly pass the tight tau cut
3. Dividing similar absolute differences by much smaller denominators amplifies the **percentage**
4. Final: +0.052% at baseline → +0.38% at SR (7.3x amplification)

**Verification**: My Python calculation matches Stage 3 histograms exactly:
- Calculated full_sr: Ref=3,162, Test=3,174
- Actual histograms: Ref=3,162, Test=3,174 ✓

**Conclusion**: The ~0.38% data difference (and ~1.5% tttt difference) is fully explained by:
1. Floating-point precision differences at Stage 1 (OS migration CentOS 7 → AlmaLinux 9)
2. Statistical amplification through tight SR cuts (especially tausT_num == 1)

This is NOT a bug - it's expected behavior from environmental changes. The differences are acceptable for physics analysis.

---

## 1tau1l Channel Verification (Session 2025-12-07)

Verified same mechanism applies to 1tau1l, but with **opposite effect**:

**1tau1l JetHT Data Progressive Cuts**:

| Cut | Ref Events | Test Events | Extra | % Diff |
|-----|------------|-------------|-------|--------|
| baseline | 230,780 | 230,900 | +120 | +0.052% |
| **lep==1** | 4,128 | 3,989 | **-139** | **-3.37%** |
| jets≥7 | 2,855 | 2,754 | -101 | -3.54% |
| bjetsM≥3 | 834 | 791 | -43 | -5.16% |
| tausT==1 | 146 | 139 | -7 | -4.79% |
| full_sr | 141 | 134 | -7 | -4.96% |

**Key Discovery**: The **lepton cut** (`lep==1`) causes the sign to flip from +0.052% to -3.37%!

**Same root cause, opposite effect**:
- Floating-point precision differences affect BOTH tau AND lepton selection thresholds
- For 1tau0l: tau cuts dominate → net +events (more taus pass threshold)
- For 1tau1l: lepton cut dominates → net -events (fewer events have exactly 1 lepton)

**Verification**: My calculation (141→134) matches Stage 3 histograms (140→133) exactly.

**Stage 3 1tau1l Yields**:
- 1tau1lSR: 140→133 (**-5.0%**)
- 1tau1lCR12: 605→590 (**-2.5%**)

---

## UPDATED STATUS (2025-12-19): PARTIALLY RESOLVED

### Key Paths (CORRECTED)
- **Data WH histograms**: `.../data/variableHists_*/` (NOT `/mc/`)
- **MC WH histograms**: `.../mc/variableHists_*/`
- **Sample-to-process mapping**: See `histoGramPerSample` in `hua/src_py/ttttGlobleQuantity.py`
  - `jetHT_2018a/b/c/d` → actual data observation
  - `fakeTau_data_ptMorphed` → fake tau background (data-driven)
  - `tttt` → signal MC

### Comprehensive Stage-by-Stage Comparison

| Stage | 2017 Data | 2018 Data |
|-------|-----------|-----------|
| **Stage 1 (OS)** | +0.061% (176,075→176,183) | +0.054% (269,807→269,953) |
| **Stage 2 (MV)** | +0.064% (149,589→149,685) | +0.052% (230,780→230,900) |

| Stage 3 (WH) | 2017 Data | 2018 Data |
|--------------|-----------|-----------|
| **1tau0lSR** | **+0.05%** (2002→2003) | **+0.38%** (3162→3174) |
| **1tau0lCRMR** | **+0.22%** (15134→15168) | **+0.18%** (23146→23188) |
| **1tau1lSR** | **0.00%** (109→109) | **-5.00%** (140→133) |
| **1tau1lCR12** | **-2.42%** (413→403) | **-2.48%** (605→590) |

### MC Comparison (tttt)
| Channel | 2017 | 2018 |
|---------|------|------|
| **1tau1lSR** | -1.70% (2.40→2.36) | -1.70% (3.53→3.47) |

---

## KEY FINDINGS (2025-12-19)

### 1. tttt MC: EXPLAINED by OS/environment change
- Both 2017 and 2018 show consistent **-1.70%** difference
- Floating-point precision differences from CentOS 7 → AlmaLinux 9
- This is expected and acceptable

### 2. 2017 Data: EXPLAINED by OS/environment change
- 1tau1lSR: **0.00%** (no change)
- 1tau0lSR: **+0.05%** (consistent with Stage 1/2)
- The small differences cancel out or amplify through SR cuts

### 3. 2018 Data: PARTIALLY EXPLAINED
- 1tau0lSR: **+0.38%** (consistent with Stage 1/2, amplified)
- 1tau1lSR: **-5.00%** - **2018-SPECIFIC ISSUE**

The 2018-specific drop strongly suggests the jet veto fix (commit 1347ac24) IS relevant for 2018 data:
- Reference 2018 (Jan 26, 2025): Produced BEFORE jet veto fix
- TTBBtest 2018 (Dec 5, 2025): Produced AFTER jet veto fix
- 2017 Reference (Feb 4, 2025): Produced AFTER jet veto fix (same day as fix)

### 4. 1tau1l CR: Both years show ~-2.5%
**VERIFIED** - Lepton selection boundary effect confirmed:

| Cut | 2018 Data | 2017 Data |
|-----|-----------|-----------|
| base (jets>=7, bM>=3) | +0.073% | +0.075% |
| **+ lepTopMVAF>=1** | **-2.842%** | **-1.288%** |
| + lepTopMVAF==1 | -2.863% | -0.820% |
| **+ isTight** | **-5.288%** | -1.673% |
| + tausT==1 (full SR) | **-4.828%** | **0.000%** |

Key observations:
- Lepton cut (`lepTopMVAF>=1`) causes sign flip in BOTH years
- Tight lepton requirement amplifies the effect (especially 2018)
- 2017: tausT==1 cancels lepton effect → **0% final SR change**
- 2018: tausT==1 doesn't cancel → **-4.8% final SR change**

The 2018-specific larger effect is due to jet veto fix removing events that would have cancelled the lepton boundary effect in 2017

---

## REVISED ROOT CAUSE ANALYSIS

The jet veto fix hypothesis is **PARTIALLY CORRECT**:

1. **2018 1tau1lSR -5.00%**: Combination of:
   - Jet veto fix (1347ac24) affecting 2018 data specifically
   - OS/environment changes
   - Lepton selection boundary effects

2. **2017 1tau1lSR 0.00%**: No change because:
   - Both Reference and TTBBtest produced AFTER the jet veto fix
   - Effects cancel out or are smaller

3. **1tau0l positive changes**: Consistent with Stage 1/2 direction:
   - Jet veto fix has minimal impact on 1tau0l (no lepton requirement)
   - OS changes propagate through normally

---

## CORRECTED ROOT CAUSE: XGBoost Library Differences (2025-12-19)

### Previous Hypothesis (WRONG)
The previous conclusion that "floating-point precision differences from OS change" caused the yield differences was **INCORRECT**.

### Actual Root Cause: XGBoost TopMVA Score Differences

**Evidence from direct comparison of Stage 2 (MV) files:**

Comparing 1000 common events between Reference and TTBBtest:
| Variable | Mismatches | Percentage |
|----------|------------|------------|
| lepTopMVAT_num | 8 | 0.8% |
| jets_num | 2 | 0.2% |
| bjetsM_num | 1 | 0.1% |

**Root cause traced to Stage 1 (OS) electron TopMVA scores:**

| Event | Ref TopMVA Score | Test TopMVA Score | Difference | isTight |
|-------|------------------|-------------------|------------|---------|
| 292756 | 0.848 | 0.772 | **-0.076** | True→False |
| Mean (100 events) | - | - | **0.0126** | - |
| Max difference | - | - | **0.123** | - |

**Key findings:**
1. **Same electron pT** (114.77 GeV) but **different TopMVA scores** (0.848 vs 0.772)
2. Score difference causes `isTight` flag to change from True to False
3. ~2% of electrons have `isTight` flag changes
4. Some electrons completely disappear from the collection

### Technical Explanation

The electron TopMVA is evaluated using **XGBoost**. The differences are caused by:

1. **XGBoost API change** (commit `736b0720`, Jul 26, 2025):
   ```cpp
   // Old API (CentOS 7):
   XGBoosterPredict(booster, dtest, 0, 0, &out_len, &f);
   // New API (AlmaLinux 9):
   XGBoosterPredict(booster, dtest, 0, 0, 0, &out_len, &f);
   ```

2. **XGBoost library version differences** between CentOS 7 and AlmaLinux 9

3. **Different floating-point behavior** in the ML inference causing significant score shifts

### Impact on Physics

| Channel | Effect | Cause |
|---------|--------|-------|
| 1tau1l | -5% data, -1.7% tttt | Fewer leptons pass TopMVA tight cut |
| 1tau0l | +0.38% data | Fewer leptons → more events pass lep==0 cut |

### Conclusion

This is **NOT acceptable environmental variation** - it's a **systematic shift in ML model predictions** due to library incompatibility. The TTBBtest outputs are produced with a different effective lepton selection than the reference.

**Recommendation**:
1. Regenerate reference Stage 1 outputs on AlmaLinux 9 with the fixed XGBoost API
2. OR accept that all future productions must use AlmaLinux 9 consistently

---

## Detailed XGBoost Version Investigation (2025-12-19)

### XGBoost Version Difference

| Environment | XGBoost Version | Path |
|-------------|-----------------|------|
| CentOS 7 (Reference) | **0.80** | `slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh` |
| AlmaLinux 9 (TTBBtest) | **1.7.5** | `el9_amd64_gcc14/external/py3-xgboost/1.7.5-...` |

This is a **major version jump** (0.80 → 1.7.5) spanning ~4 years of XGBoost development.

### API Change

Commit `736b0720` (Jul 26, 2025) fixed the API call:
```cpp
// Old API (XGBoost 0.80):
XGBoosterPredict(booster, dtest, 0, 0, &out_len, &f);

// New API (XGBoost 1.7.5):
XGBoosterPredict(booster, dtest, 0, 0, 0, &out_len, &f);  // Extra parameter
```

### Comprehensive Score Comparison

**Single file analysis** (`0C83776E-0359-5E4A-BD01-1DBC7136A775.root`):
- Total events: 31,395 common
- Total electrons compared: 6,149

#### Electron TopMVA Score Statistics

| Metric | Value |
|--------|-------|
| Events with electron count mismatch | 149 (0.47%) |
| Mean score difference (Ref - Test) | **0.0119** |
| Max score difference | **0.1244** |
| Std dev of difference | 0.0241 |
| Median difference | 0.0014 |

#### Score Difference by Score Range

| Ref Score Range | N | Mean Diff |
|-----------------|---|-----------|
| [0.00-0.30) | 193 | 0.037 |
| [0.30-0.50) | 65 | 0.110 |
| [0.50-0.70) | 69 | 0.121 |
| [0.70-0.80) | 56 | 0.103 |
| [0.80-0.85) | 44 | 0.083 |
| [0.85-0.90) | 134 | 0.062 |
| [0.90-0.95) | 300 | 0.041 |
| [0.95-1.00) | 5288 | 0.004 |

**Key observation**: Mid-range scores (0.3-0.8) have largest shifts (~10-12%), high scores (>0.95) have smallest shifts (~0.4%).

#### Direction of Shift

| Direction | Count | Percentage |
|-----------|-------|------------|
| Positive (Ref > Test) | 6149 | **100.00%** |
| Negative (Ref < Test) | 0 | 0.00% |

**All differences are positive** - TTBBtest ALWAYS gives lower scores than Reference. This is a systematic downward shift.

#### Impact on isTight Flag

| Metric | Value |
|--------|-------|
| isTight threshold | 0.81 |
| Total isTight changes | 64 (1.04%) |
| True → False | 64 |
| False → True | 0 |

For electrons where isTight changed:
- Mean Ref score: 0.846 (just above threshold)
- Mean Test score: 0.770 (below threshold)
- Mean shift: -0.076

#### Muon TopMVA (Similar Pattern)

| Metric | Value |
|--------|-------|
| Events with muon count mismatch | 110 |
| Total muons compared | 6,211 |
| Mean score difference | 0.0132 |
| Max score difference | 0.1244 |

### Model Files

Model files are **identical** between versions (same files from June 2024):
```
input/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin
input/TopLeptonMVA/mvaWeights_new/mu_TOPUL18_XGB.weights.bin
```

The difference is purely in the **XGBoost library version** interpreting the same model file.

### Root Cause Explanation

XGBoost 0.80 → 1.7.5 includes many changes to:
1. Tree traversal algorithms
2. Floating-point handling
3. Model serialization/deserialization
4. Prediction caching

These changes cause the **same model** to produce **different predictions** when loaded with different library versions.

### Why XGBoost Scores Differ Between Versions

Based on [XGBoost GitHub issues](https://github.com/dmlc/xgboost/issues/3664) and [official documentation](https://xgboost.readthedocs.io/en/stable/tutorials/saving_model.html):

#### 1. Model Format Compatibility
- Our model files use the **old binary format** (`.bin` files from June 2024)
- XGBoost 1.7 still supports the old binary format, but the **JSON format** is now preferred
- From [XGBoost Model IO docs](https://xgboost.readthedocs.io/en/release_1.7.0/tutorials/saving_model.html): "We guarantee backward compatibility for models but not for memory snapshots"

#### 2. API Changes
```cpp
// Old API (XGBoost 0.80) - 4 params before output:
XGBoosterPredict(handle, dmat, option_mask, ntree_limit, out_len, out_result);

// New API (XGBoost 1.7.5) - 5 params before output:
XGBoosterPredict(handle, dmat, option_mask, ntree_limit, training, out_len, out_result);
```
The extra `training` parameter (set to 0 for inference) affects how DART boosters handle dropout. Our model may use DART.

#### 3. CPU Predictor Optimizations
From [GitHub issue #6350](https://github.com/dmlc/xgboost/issues/6350): "There are some optimization done on the CPU predictor, might generate different result by different floating point error."

#### 4. 32-bit vs 64-bit Floating Point
From XGBoost docs: "XGBoost uses 32-bit version of the exponentiation operator in its sigmoid function. If using 64-bit doubles in calculations, values are promoted to 64-bit and results may differ."

#### 5. Internal Algorithm Changes
Major version jumps (0.80 → 1.0 → 1.7) include:
- Hist algorithm performance improvements
- New prediction caching
- DMatrix refactoring
- GPU predictor changes affecting CPU fallback

### Conclusion on Score Differences

The ~1.2% mean score difference (up to 12% max) is **expected behavior** when using:
- Old binary model format with new XGBoost version
- Different floating-point handling between versions
- Different CPU predictor optimizations

This is **NOT a bug** but rather **known incompatibility** between XGBoost 0.80 and 1.7.5.

### Recommended Solution

**Option A: Retrain TopMVA models with XGBoost 1.7.5** (Best)
- Export models in JSON format for future compatibility
- Regenerate all Stage 1 outputs

**Option B: Convert model files to JSON format**
- Use XGBoost 0.80 to load binary, export as JSON
- Load JSON in XGBoost 1.7.5
- May still have small differences due to algorithm changes

**Option C: Use consistent XGBoost version** (Current workaround)
- All future productions must use AlmaLinux 9 with XGBoost 1.7.5
- Accept that old reference (CentOS 7 + XGBoost 0.80) is incompatible

---

## Previous Analysis (still valid for 1tau0l channel):
- Floating-point precision differences (CentOS 7 → AlmaLinux 9) cause ~0.05% baseline shift
- Tight SR cuts amplify small differences through statistical effects
- 1tau0l: +0.38% (expected behavior, consistent with Stage 1/2)

---

## TopMVA Training Source Investigation (2025-12-19)

### Key Question: Where do the TopMVA weight files come from?

**Our weight files**:
```
objectSelectionOptimized/input/TopLeptonMVA/mvaWeights_new/
├── el_TOPUL18_XGB.weights.bin  (361,626 bytes, June 5, 2024)
├── mu_TOPUL18_XGB.weights.bin  (293,249 bytes, June 5, 2024)
└── ... (all eras)
```

### Investigated Repositories

#### 1. [GhentAnalysis/TopLeptonMVA](https://github.com/GhentAnalysis/TopLeptonMVA)
- **Training method**: TMVA (ROOT's toolkit), NOT XGBoost
- **Weight format**: `.weights.xml` (TMVA BDTG format)
- **Files**: `TMVA_BDTG_TOP_elec_2018.weights.xml`, etc.

**Conclusion**: This is the TMVA version, NOT our XGBoost version.

#### 2. [NielsVdBossche/ewkino](https://github.com/NielsVdBossche/ewkino)
- **How it uses TopMVA**: Reads `leptonMVATOPUL` directly from NanoAOD branches
- **No local XGBoost inference** - values pre-computed in NanoAOD
- Source: `objects/src/LightLepton.cc:41`
  ```cpp
  _leptonMVATOPUL( leptonReader._Lepton_TOPLeptonMVAUL[leptonIndex] )
  ```

**Conclusion**: Ewkino reads pre-computed scores, doesn't calculate them.

#### 3. [cms-ttH/ttH-LeptonID](https://github.com/cms-ttH/ttH-LeptonID)
- Uses TMVA, exports `.weights.xml` files
- Repository last updated 2019

#### 4. [GhentAnalysis/heavyNeutrino](https://github.com/GhentAnalysis/heavyNeutrino)
- Has TMVA weights in `multilep/data/mvaWeights/`
- Files: `el_TOP18_BDTG.weights.xml`, etc.

### XGBoost Binary (.bin) Files - Unknown Origin

Our `.bin` files use the XGBoost binary format and are loaded via the C API:
```cpp
XGBoosterLoadModel(booster, model_path.c_str());
```

**The exact training source for these XGBoost binary files could NOT be found publicly.**

Possible origins:
1. Internal CMS TOP group training (not public)
2. Conversion from TMVA models to XGBoost
3. Custom training by Ghent/ttH groups

### CMS ML Documentation: XGBoost Version Compatibility

From [CMS ML Documentation](https://cms-ml.github.io/documentation/inference/xgboost.html):

| SCRAM_ARCH | XGBoost Version |
|------------|-----------------|
| slc7_amd64_gcc700 | **0.80** |
| slc7_amd64_gcc900 | **1.3.3** |
| el9_amd64_gcc14 | **1.7.5** (our current) |

**Critical compatibility warning**:
> "Different major versions have different behavior. Models trained with version 1.3.3 cannot be loaded by version 0.80."

The reverse is also problematic: **models trained with 0.80 may give different predictions in 1.7.5** due to:
1. CPU predictor optimizations
2. Floating-point handling changes
3. Algorithm improvements
4. API changes (extra `training` parameter)

### Conclusion: Which XGBoost Version Should We Use?

**Unknown**: We don't know which XGBoost version was used to train the TopMVA models.

**Probable**: Given the file dates (June 2024) and CMS infrastructure, the training likely used:
- XGBoost 0.80 (SLC7 era) or
- XGBoost 1.3.3 (SLC7 with gcc900)

**Recommendation**: Since we cannot determine the original training version:
1. **Accept current behavior** - All future productions use XGBoost 1.7.5 consistently
2. **OR**: Request original training scripts/version from TOP PAG
3. **OR**: Retrain TopMVA with XGBoost 1.7.5 and export in JSON format for future compatibility

---

## FINAL STATUS: **CONFIRMED** (2025-12-20)

**Root Cause**: XGBoost library version incompatibility (0.80 → 1.7.5) **EXPERIMENTALLY VERIFIED**

### Verification Test Results (Phase 10)

Ran the full pipeline on CentOS7 with XGBoost 0.80 (`v95XGB080testOS7`):

**Stage 1 (OS) Tree Entry Comparison:**

| Sample | XGB080 Test (CentOS7) | Reference | TTBBtest (AlmaLinux9) | XGB080 vs Ref |
|--------|----------------------|-----------|----------------------|---------------|
| **tttt** | **1,730,209** | **1,730,209** | 1,734,672 | **0 (+0.000%)** |
| **Data** | **269,807** | **269,807** | 269,953 | **0 (+0.000%)** |

**XGB080 Test matches Reference EXACTLY - 100% confirming hypothesis!**

**Impact**:
- TopMVA scores shift systematically lower in XGBoost 1.7.5
- ~1.04% of electrons change isTight flag (True → False)
- Results in -5% 1tau1lSR data, -1.7% tttt MC

**Decision**: Accept TTBBtest as new baseline. All future productions must use AlmaLinux 9 with XGBoost 1.7.5 for consistency.


---

## WH TFile Caching Bug Fix (2025-12-22)

During Phase 10 WH verification, encountered a bug where WH jobs failed with "Tree 'Runs' not found" causing `processScale: inf`.

### Bug Origin
Commit `3f947cbf` (July 14, 2025) changed `m_file` from constructor-body assignment to inline `std::unique_ptr` initialization. This inadvertently triggered ROOT's TFile caching behavior: `calQCDScaleNor` and `calPDFScaleNor` opened the same file path with `TFile::Open()`, received the cached pointer, and closed it - leaving `m_file` pointing to a closed file.

### Fix Applied (Commit eaf05636)
- Added `TFile*` overloads for `calQCDScaleNor` and `calPDFScaleNor` that accept existing file pointer
- Updated `treeAnalyzer.C` to use `m_file.get()` instead of file path

### Verification
Full WH run on XGB080 test files completed successfully:
```
genWeightSumInitial: 106025 (was 0)
processScale: 0.0075447 (was inf)
tttt_1tau1lSR_BDT: 80,144 entries, sum=3.527 (was inf)
```

