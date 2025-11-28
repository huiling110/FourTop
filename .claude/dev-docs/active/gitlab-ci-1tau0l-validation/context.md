# Context: GitLab CI Validation for 1tau0l

**Created**: 2025-11-26 10:40
**Last Updated**: 2025-11-27 19:00

---

## Key Files

### GitLab Datacards Repository
- `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input/systematics_TOP24017.yml` - Lines 134-156: b-tag systematic definitions (MUST UPDATE)
- `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input/datacard_1tau0l_v19_unblind.txt` - New datacard (WILL CREATE)
- `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/check_names.py` - Local validation script
- `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/.gitlab-ci.yml` - CI configuration

### FourTop Repository
- `hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt` - Source datacard
- `writeHistGood/CMS_NAMING_CONVENTION_UPDATE.md` - Documentation (UPDATE after CI)

### Template Files (per era)
- Source: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/YEAR/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root`
- Destination: `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input/YEAR/`

---

### Decision 6: Tau Fake Rate Full Correlation
**Rationale**: User clarified tau fake rates should be fully correlated across ALL years (2016preVFP, 2016postVFP, 2017, 2018), not just within 2016 VFP eras
**Date**: 2025-11-27 (Session 7)
**Implementation**:
- SystematicManager.h: Set `isEraDependent = false` for both VSe and VSmu
- writeDatacard.py: Set `isCorrelated = True` in MCSys dictionary
- Result: Systematic names have no year suffix (e.g., `CMS_fake_t_DeepTau2017v2p1_VSe`)
**Impact**: Reduces number of nuisance parameters, assumes fake rates stable across Run 2

### Decision 7: Complete Tau ID CMS Naming Convention Update
**Rationale**: Discovered during implementation that tau ID systematics didn't follow CMS POG naming convention (missing algorithm name, incorrect dm/DM pattern)
**Date**: 2025-11-27 (Session 7)
**Reference**: https://gitlab.cern.ch/cms-analysis/general/systematics/-/blob/master/systematics_master.yml lines 539-559
**Changes**:
- Algorithm name added: `vsJet` → `DeepTau2017v2p1_VSjet`
- Statistical naming: `stat1_dm0` → `dm_stat1_DM0`
- Systematic naming: `syst_dm0` → `dm_syst_DM0`
- All eras naming: `syst_alleras` → `dm_syst_alleras`
**Impact**: Full CMS POG compliance, enables proper GitLab CI classification (class: tau_identification)

### Decision 8: Tau ID Keeps VFP-Specific Names (NOT Correlated)
**Rationale**: Tau ID efficiency uncertainties should keep separate names for 2016preVFP and 2016postVFP - they are NOT correlated across VFP eras, unlike electron reco, tau energy scale, and L1 prefiring
**Date**: 2025-11-28 (Session 9)
**Implementation**:
- writeDatacard.py: Removed tau ID from VFP mapping (lines 402-407)
- Tau ID systematics keep era-specific names: `_2016preVFP`, `_2016postVFP`
- VFP mapping now only applies to:
  * `CMS_eff_e_reco` (electron reco - correlated)
  * `CMS_scale_t_DeepTau2017v2p1_DM*` (tau energy scale - correlated)
  * `CMS_l1_ecal_prefiring` (L1 prefiring - correlated)
  * `CMS_fake_t_DeepTau2017v2p1_VS*` (tau fakes - fully correlated, no year suffix)
**Impact**: Correct physics treatment - tau ID efficiencies can differ between VFP eras

### Decision 9: VFP Correlation Mapping Only in Datacard Generation
**Rationale**: Template files must contain exact histogram names from ROOT files; VFP correlation should only be applied during datacard generation when combining eras
**Date**: 2025-11-28 (Session 9)
**Implementation**:
- addTemplateNew.py: Removed all VFP unmapping/remapping logic (lines 99-131, 170-185)
- Template files preserve VFP-specific names from C++ histogram generation
- writeDatacard.py::getSysDic() handles VFP→2016 mapping for correlated systematics
**Pattern**: Follows same approach as `CMS_eff_e_reco` which already worked correctly
**Impact**:
- Template generation now works correctly for 2016 VFP eras
- Clear separation: C++ generates VFP-specific hists → Templates preserve them → Datacards correlate them
**Commit**: 20861bb6

---

## Important Decisions

### Decision 1: Copy new template files
**Rationale**: Guarantees exact match with validated datacard, uses Git LFS for large ROOT files
**Date**: 2025-11-26 (Session 2)
**Impact**: ~8 MB of ROOT files to commit

### Decision 2: Commit uncommitted changes together
**Rationale**: Single coherent commit for v19 migration
**Date**: 2025-11-26 (Session 2)
**Impact**: Includes README.md updates and datacard_1tau1l_v16.txt deletion

### Decision 3: Push directly to master
**Rationale**: Standard workflow for datacards repository
**Date**: 2025-11-26 (Session 2)
**Impact**: Fast-track to CI validation

### Decision 4: Update systematics submodule to latest master
**Rationale**: CI was using outdated submodule (bb1b6446 from Nov 20, 2024) missing FlavorPure patterns, 2016preVFP/postVFP MET support, and pdf_alphas
**Date**: 2025-11-26 (Session 4)
**Impact**:
- Resolved 10 of 56 naming violations
- Updated from commit bb1b6446 → 251c9ac0 (latest master)
- Properly initialized systematics as git submodule (was manual directory copy)
- Will require CI pipeline to pull latest submodule on next run
**Alternative considered**: Add missing patterns to systematics_TOP24017.yml as "custom" class - rejected because master already has correct patterns

### Decision 5: Fix job submission scripts to source environment
**Rationale**: Job submission scripts failed with "ModuleNotFoundError: No module named 'usefulFunc'" because Python path not set
**Date**: 2025-11-27 (Session 5)
**Fix Applied**:
- Updated run_nominal_jobs.sh: Changed `python3 ${JOB_SCRIPT}` to `bash -c "source ../setEnv_newNew.sh && python3 ${JOB_SCRIPT}"`
- Updated run_makeJos_WH_forJES.sh: Re-enabled 2018 jobs and added environment sourcing to all eras
**Impact**: Successfully submitted 278 jobs (nominal + systematic for all 4 eras)
**Committed**: Commit 6a313504

---

## Technical Constraints

**CRITICAL BLOCKER**: systematics_TOP24017.yml uses old `CMS_btag_shape_*` naming
- Must be fixed before CI will pass
- Lines 134-156 need update

**Template file paths**: Datacard uses absolute `/publicfs/` paths
- Must be changed to relative paths (e.g., `2016preVFP/templatename.root`)
- Pattern: Replace long path with `./<YEAR>/`

**Git LFS**: Repository uses Git LFS for `.root` files
- Verify LFS is configured before committing templates
- Command: `git lfs ls-files` to check

---

## Input/Output Locations

### Inputs
- Validated datacard: `FourTop/hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt`
- Template files: `/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/` (4 eras)

### Outputs
- Updated systematics: `datacards/input/systematics_TOP24017.yml`
- New datacard: `datacards/input/datacard_1tau0l_v19_unblind.txt`
- Template copies: `datacards/input/YEAR/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root`
- CI results: GitLab pipeline URL (after push)

---

## Dependencies

**Blocked by**: Nothing (ready to start)
**Blocks**: 1tau1l and 1tau2l CI validation (user directive: only after 1tau0l passes)

---

## Reference Information

**Datacard Statistics** (combinationV19CMSNamingFix):
- Bins (imax): 4 eras
- Processes (jmax): 8 (tttt signal + 7 backgrounds)
- Systematics (kmax): 212 nuisance parameters
- All 26 b-tag systematics use CMS-compliant naming

**Physics Validation**: 1.86σ significance (identical to v0BDT reference)

**CI Pipeline URL**: https://gitlab.cern.ch/cms-analysis/top/top-24-017/datacards/-/pipelines

**GitLab API Token**: `/workfs2/cms/huahuil/.gitlab-token`
- Personal access token for programmatic CI access
- Token value: `glpat-oQfaSrVyYFhxhL_dx7Asom86MQp1OjJlMHYK.01.1003e0lwe`
- Use with: `cat /workfs2/cms/huahuil/.gitlab-token`

---

## Common Commands

### Job Submission (v9BDT Production)
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/writeHistGood

# Submit nominal jobs for all 4 eras
bash run_nominal_jobs.sh 1tau0l v9BDT1tau0l_CMSNamingComplete v94HadroPreJetVetoHemOnly

# Submit systematic variation jobs for all 4 eras
bash run_makeJos_WH_forJES.sh

# Monitor jobs
hep_q | grep huahuil | wc -l                    # Count total jobs
hep_q | grep huahuil | awk '{print $6}' | sort | uniq -c  # Status breakdown

# Check logs
tail -f log_2018_1tau0l.log
tail -f log_2017_1tau0l.log
tail -f log_2016preVFP_1tau0l.log
tail -f log_2016postVFP_1tau0l.log

# Check job results when complete
cd jobs/
python3 checkJobResult.py
```

### Check GitLab CI pipeline status
```bash
GITLAB_TOKEN=$(cat /afs/ihep.ac.cn/users/h/huahuil/.ssh/.gitlab-token)
curl --header "PRIVATE-TOKEN: $GITLAB_TOKEN" \
  "https://gitlab.cern.ch/api/v4/projects/cms-analysis%2Ftop%2Ftop-24-017%2Fdatacards/pipelines?per_page=5"
```

### Local validation
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards
python check_names.py --datacard input/datacard_1tau0l_v19_unblind.txt --systematics input/systematics_TOP24017.yml
```

### Copy template files
```bash
SOURCE="/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
DEST="/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input"
for era in 2016preVFP 2016postVFP 2017 2018; do
  cp ${SOURCE}/${era}/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/combine/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root ${DEST}/${era}/
done
```

### Git operations
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards
git status
git add input/systematics_TOP24017.yml input/datacard_1tau0l_v20_unblind.txt input/*/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root
git commit -m "Update to CMS-compliant systematic naming for 1tau0l channel (v20)"
git push origin master
```

---

## Current Status

**Last Updated**: 2025-11-27 23:00

### Session 7: Complete CMS Naming Convention Compliance (2025-11-27)

**Status**: ✅ **Phase 5.0-5.1 COMPLETE** - C++ and Python updates finished, ready for production

#### Progress:
1. **Discovered additional naming requirements**:
   - User clarified tau fake rates should be fully correlated across ALL years (not just 2016 VFP)
   - Discovered tau ID systematics need full CMS convention update (DeepTau2017v2p1_VSjet)

2. **C++ updates completed** (Phase 5.0):
   - Updated SystematicManager.h:
     - Tau fakes: Set `isEraDependent = false` for full correlation
     - L1 prefiring: Embedded VFP→2016 mapping in systematic name
     - Tau ID: Complete rename with algorithm name and dm/DM pattern
   - Updated functions.C: All histogram names match new systematic names
   - Built and tested successfully with multiple eras

3. **Python updates completed** (Phase 5.1):
   - Updated writeDatacard.py:
     - MCSys dictionary: All tau fake and tau ID keys updated
     - Tau fakes: Changed to `isCorrelated=True`
     - Tau ID: All stat1/stat2/syst variations updated
     - getSysDic(): Added VFP mapping for tau ID, removed for tau fakes
     - Added class documentation (fake_rate, tau_identification)

4. **Git commit created**: Commit 60847c6a with complete changes

#### Testing Results:
- ✅ 2018: `CMS_eff_t_DeepTau2017v2p1_VSjet_2018`, `CMS_fake_t_DeepTau2017v2p1_VSe` (no year)
- ✅ 2016preVFP: `CMS_l1_ecal_prefiring_2016`, tau ID correct
- ✅ 2016postVFP: `CMS_l1_ecal_prefiring_2016`, tau ID correct
- ✅ All stat1/stat2/syst variations: `dm_stat1_DM0`, `dm_syst_DM0`, etc.

#### Next Steps:
1. Update remaining Python scripts (addJESTemplatesToHistFile.py, addTemplateNew.py, smooth_systematics)
2. Regenerate histograms with v11BDT1tau0l_CMSNamingComplete
3. Template consolidation and datacard generation
4. Local validation (target: 0 issues)
5. GitLab CI validation

---

## Previous Status (2025-11-27 19:00) - JOBS COMPLETED

#### Progress:
1. **Disk quota resolved** (completed by publicfs-cleanup task):
   - Before: 970K files (97% quota)
   - After: 706K files (70.6% quota)
   - ✅ Safe to submit large production run

2. **Fixed job submission scripts**:
   - Issue: ModuleNotFoundError for usefulFunc module
   - Root cause: Environment not sourced before Python execution
   - Fix: Updated scripts to use `bash -c "source ../setEnv_newNew.sh && python3 ..."`
   - Files modified: run_nominal_jobs.sh, run_makeJos_WH_forJES.sh
   - Committed: 6a313504

3. **Successfully submitted all jobs**:
   - Nominal jobs: All 4 eras (2018, 2017, 2016preVFP, 2016postVFP)
   - Systematic jobs: All 4 eras (~68 variations per era)
   - **Total: 278 jobs** (225 running, 53 queued as of 19:00)

#### Next Steps:
- Monitor job completion (~3-6 hours estimated)
- Check for failed jobs with checkJobResult.py
- Consolidate templates (Phase 5.3)
- Generate datacards with new systematic names (Phase 5.5)
- Local validation: Target 0 issues (down from 46)

---

## Previous Status (2025-11-26 20:30) - SYSTEMATICS SUBMODULE UPDATED

**Session 4 Summary**: Root Cause Analysis & Submodule Fix

### Session 4: Root Cause Analysis & Submodule Fix (2025-11-26 20:00-20:30)

**✅ CRITICAL DISCOVERY**: The check_systematics failures were caused by an **outdated systematics submodule** in the datacards repository!

#### Root Cause Identified:
- **CI Pipeline**: Uses systematics submodule commit `bb1b6446` (Nov 20, 2024)
- **This commit was MISSING**:
  - FlavorPure JES patterns (CMS_scale_j_FlavorPure{Quark|Gluon|Charm|Bottom})
  - 2016preVFP/2016postVFP support for MET systematics
  - pdf_alphas pattern
- **Current master** (commit `251c9ac0`): HAS all these patterns

#### Fix Applied:
1. ✅ Removed manual systematics/ directory
2. ✅ Properly initialized systematics as git submodule
3. ✅ Updated to latest master (251c9ac0)
4. ✅ Committed: "Update systematics submodule to latest master (251c9ac0)"

#### Local Validation Results:
- **Before submodule update**: 56 nuisance parameter naming issues
- **After submodule update**: 46 nuisance parameter naming issues
- **✅ 10 issues resolved** by updating submodule!

### Summary of Work Completed (Previous Sessions)
Sessions 1-3 completed full datacard regeneration with CMS-compliant systematic naming for all 4 Run 2 eras.

### 1. Datacard Generation (All Eras)
**Status**: ✅ COMPLETE

Generated new datacards with CMS-compliant naming for all 4 eras:
- ✅ 2016preVFP: Generated at 14:32
- ✅ 2016postVFP: Generated at 14:33
- ✅ 2017: Generated at 14:34
- ✅ 2018: Generated at 14:35

**Output location**: `/publicfs/.../v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`

**Key fixes in generated datacards**:
- Luminosity systematics: `lumi_2016`, `lumi_2017`, `lumi_2018` (CMS convention)
- B-tag systematics: Already correct (`CMS_btag_*` not `CMS_btag_shape_*`)
- Process-specific QCDscale and ps_isr: Preserved as designed

### 2. Datacard Combination
**Status**: ✅ COMPLETE

Combined all 4 era datacards using `writeCombinationDatacard.py`:
- Input: 4 individual era datacards (each ~29 KB)
- Output: `hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt` (165 KB, 233 lines)
- Verified: Correct luminosity naming in combined datacard

### 3. Repository Commits
**Status**: ✅ COMPLETE

**FourTop Repository** (commit 37647982):
```
feat: Complete CMS naming convention compliance for 1tau0l datacards

- Updated writeDatacard.py to map VFP eras to year for luminosity naming (lumi_2016/2017/2018)
- Updated writeCombinationDatacard.py to use new datacards with CMS-compliant naming
- Generated datacards for all 4 eras with complete CMS compliance
```

**datacards Repository** (commits dc694df, 09b5537):
```
dc694df: feat: Update 1tau0l datacard with complete CMS naming compliance
09b5537: fix: Change template file paths from absolute to relative
```

### 4. GitLab CI Pipeline Results

**Pipeline #13451004** (commit dc694df) - FAILED:
- ❌ ValidateDatacards: FAILED (absolute paths issue)
- ❌ check_systematics: FAILED

**Pipeline #13451015** (commit 09b5537) - PARTIAL SUCCESS:
- ✅ ValidateDatacards: **SUCCESS** (fixed by relative paths!)
- ✅ T2W: SUCCESS
- ✅ CombineCards: SUCCESS
- ❌ check_systematics: **STILL FAILING**
- Status: "manual" (waiting for intervention)

### 5. Critical Fix Applied
**Issue**: Datacard had absolute paths `/publicfs/.../YEAR/...` for ROOT template files
**Fix**: Changed to relative paths `YEAR/templatesForCombine1tau0l_new_notMCFTau_unblind_smoothed.root`
**Result**: ValidateDatacards job now passes!

### Remaining Issues After Submodule Update (46 nuisances)

**Local check_systematics test identified remaining issues**:

1. **❌ B-tag systematics** (20 issues):
   - Current: `CMS_btag_cferr1`, `CMS_btag_hf`, `CMS_btag_lf`, `CMS_btag_hfstats1_YEAR`, `CMS_btag_lfstats1_YEAR`
   - Required: `CMS_btag_fullShape_*` patterns
   - Note: Our naming was based on older CMS recommendations

2. **❌ JES TimePtEta** (1 issue):
   - Current: `CMS_scale_j_TimePtEta` (no year suffix)
   - Required: `CMS_scale_j_TimePtEta_(2016preVFP|2016postVFP|2017|2018)`

3. **❌ Tau energy scale** (16 issues - all DM0/1/10/11 × 4 years):
   - Current: `CMS_scale_t_DM0_2016preVFP`, etc.
   - Required: `CMS_scale_t_(MVAoldDM2017v2|DeepTau2017v2p1)_DM0_genTau_(2016|2017|2018)`
   - Issues: Missing algorithm ID, missing genTau, no support for 2016preVFP/postVFP split

4. **❌ Tau fake rate** (4 issues):
   - Current: `CMS_fake_t_YEAR`
   - Required: `CMS_fake_t_DeepTau2017v2p1_VS{e|mu}`

5. **❌ L1 ECAL prefiring** (2 issues):
   - Current: `CMS_l1_ecal_prefiring_2016preVFP/postVFP`
   - Required: Only `2016` (no VFP split support)

6. **❌ Missing entry** (1 issue):
   - `CMS_l1_ecal_prefiring_2018` not in systematics_TOP24017.yml

### Next Steps
1. ✅ Submodule updated (resolved FlavorPure, MET, pdf_alphas)
2. ⏳ Document findings in Important Decisions
3. ⏳ Fix remaining 46 issues (b-tag naming most critical)
4. ⏳ Regenerate datacards with all fixes
5. ⏳ Push and verify CI passes
6. ⏳ Apply same workflow to 1tau1l and 1tau2l channels

## Files Modified This Session

**In datacards repository** (`/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/`):
- ✅ `input/systematics_TOP24017.yml` - Added missing systematics and fixed patterns (commit ff0699b)
- ✅ `input/datacard_1tau0l_v19_unblind.txt` - New combined datacard with CMS naming (commits dc694df, 09b5537)
  - First version: 165 KB with luminosity fixes
  - Second version: Fixed absolute→relative paths for ROOT templates

**In FourTop repository** (`/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/`):
- ✅ `plotting/writeDatacard.py` - Updated addLumi() function (commit 582c2535, 37647982)
  - Map VFP eras to year: `lumi_2016/2017/2018`
  - Changed `outVersion` to `v6AllSys_unblind_CMSnaming`
- ✅ `hua/combine/writeCombinationDatacard.py` - Updated paths (commit 37647982)
  - Point to new datacards with CMSnaming suffix

**Generated Files**:
- ✅ Individual era datacards (4 files, each ~29 KB):
  - `/publicfs/.../2016preVFP/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`
  - `/publicfs/.../2016postVFP/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`
  - `/publicfs/.../2017/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`
  - `/publicfs/.../2018/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt`
- ✅ Combined datacard (165 KB, 233 lines):
  - `hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt`

**Git Commits Summary**:
- datacards repo: ff0699b, dc694df, 09b5537, d2bb977 (4 commits)
  - d2bb977: Update systematics submodule to latest master (251c9ac0) - **NOT YET PUSHED**
- FourTop repo: 582c2535, 37647982 (2 commits)
- **Commits ff0699b through 37647982 pushed to origin/master**
- **Commit d2bb977 pending push (Session 4)**

## Validation Results

**B-tag systematic names in datacard** (all correct, no _shape suffix):
- CMS_btag_hf ✅
- CMS_btag_lf ✅
- CMS_btag_cferr1 ✅
- CMS_btag_cferr2 ✅
- CMS_btag_hfstats1_(2016preVFP|2016postVFP|2017|2018) ✅
- CMS_btag_hfstats2_(2016preVFP|2016postVFP|2017|2018) ✅
- CMS_btag_lfstats1_(2016preVFP|2016postVFP|2017|2018) ✅
- CMS_btag_lfstats2_(2016preVFP|2016postVFP|2017|2018) ✅

**Total**: 20 b-tag systematic variations (4 correlated + 4×4 year-specific)

## Notes

- This is the first GitLab CI validation for this analysis
- Physics results already validated locally - CI is for CMS compliance check
- Template files are large (~2.3 MB each) - Git LFS handles them
- After 1tau0l passes, apply same workflow to 1tau1l and 1tau2l
- SSH permission issue: Common with AFS home directories - manual push needed
