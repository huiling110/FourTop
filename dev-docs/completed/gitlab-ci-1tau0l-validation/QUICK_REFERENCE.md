# Quick Reference: 1tau0l CMS Naming Compliance

**Last Updated**: 2025-11-26 14:50
**Status**: 95% Complete - Awaiting final check_systematics verification

---

## What Was Done Today ✅

1. **Regenerated all 4 era datacards** with CMS-compliant luminosity naming
   - `lumi_2016` (combines preVFP+postVFP)
   - `lumi_2017`
   - `lumi_2018`

2. **Combined into single Run 2 datacard** (165 KB, 233 lines)

3. **Fixed critical CI blocker**: Changed absolute→relative paths for ROOT templates

4. **GitLab CI Progress**:
   - ✅ ValidateDatacards: NOW PASSING
   - ✅ T2W, CombineCards: PASSING
   - ❌ check_systematics: Still failing (unknown violations)

---

## Key File Locations

### Datacards
```bash
# Individual era datacards (new with CMS naming)
/publicfs/.../2016preVFP/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt
/publicfs/.../2016postVFP/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt
/publicfs/.../2017/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt
/publicfs/.../2018/.../datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt

# Combined datacard
FourTop/hua/combine/combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt

# Datacard in datacards repository (for CI)
datacards/input/datacard_1tau0l_v19_unblind.txt
```

### Modified Code
```bash
FourTop/plotting/writeDatacard.py              # Luminosity naming fix
FourTop/hua/combine/writeCombinationDatacard.py  # Path updates
datacards/input/systematics_TOP24017.yml        # Missing systematics added
```

---

## Git Commits (All Pushed)

**datacards repo**:
- `ff0699b`: Added missing JES/tau systematics to YAML
- `dc694df`: Updated datacard with CMS luminosity naming
- `09b5537`: Fixed template paths (absolute→relative)

**FourTop repo**:
- `582c2535`: Initial lumi naming fix
- `37647982`: Complete CMS compliance implementation

---

## GitLab CI Status

**Current Pipeline**: #13451015 (commit 09b5537)
**URL**: https://gitlab.cern.ch/cms-analysis/top/top-24-017/datacards/-/pipelines/13451015

**Job Status**:
- ✅ ValidateDatacards: SUCCESS (was failing, now fixed!)
- ✅ T2W: SUCCESS
- ✅ CombineCards: SUCCESS
- ❌ check_systematics: FAILED (reason unknown, need to inspect logs)

---

## What check_systematics Validates

This job checks that all systematic names in the datacard match CMS naming conventions defined in `systematics_TOP24017.yml`.

**Fixes Already Applied**:
1. ✅ Luminosity: `lumi_2016/2017/2018` (not `lumi_13TeV_YEAR`)
2. ✅ B-tag: `CMS_btag_*` (not `CMS_btag_shape_*`)
3. ✅ Process-specific QCD/PS: Classified as "custom" class
4. ✅ JES: Added FlavorPure* and TimePtEta patterns
5. ✅ Tau scale: Extended to 2016preVFP/postVFP patterns

**Still Unknown**: What violations remain in check_systematics job

---

## Next Steps (When GitLab Access Restored)

1. **Access Pipeline #13451015**:
   ```bash
   https://gitlab.cern.ch/cms-analysis/top/top-24-017/datacards/-/pipelines/13451015
   ```

2. **Check check_systematics job**:
   - View job log
   - Download validation.json artifact if available
   - Identify remaining naming violations

3. **Apply fixes** based on violations found

4. **Re-push and verify** all jobs pass

5. **Apply same workflow to 1tau1l and 1tau2l**

---

## How to Regenerate Datacards (If Needed)

```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/plotting

# 1. Update writeDatacard.py to select era (line ~190)
# Uncomment the desired era, comment others

# 2. Generate datacard
source ../setEnv_newNew.sh
python3 writeDatacard.py

# 3. Repeat for all 4 eras (2016preVFP, 2016postVFP, 2017, 2018)

# 4. Combine datacards
cd ../hua/combine
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
python3 writeCombinationDatacard.py

# 5. Copy to datacards repo
cp combinationV19CMSNamingFix/run2_1tau0l_v4_unblind/datacard.txt \
   /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input/datacard_1tau0l_v19_unblind.txt

# 6. Fix paths (absolute→relative)
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards/input
sed -i 's|/publicfs/cms/user/.../\([0-9a-zA-Z]*\)/.*combine/|\1/|g' datacard_1tau0l_v19_unblind.txt

# 7. Commit and push
git add datacard_1tau0l_v19_unblind.txt
git commit -m "Update datacard with CMS naming fixes"
git push origin master
```

---

## Verification Commands

### Check luminosity naming in datacard
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards
grep "^lumi" input/datacard_1tau0l_v19_unblind.txt
```

Expected: `lumi_2016`, `lumi_2017`, `lumi_2018`, `lumi_13TeV_correlated`, `lumi_13TeV_1718`

### Check template paths (must be relative)
```bash
grep "^shapes" input/datacard_1tau0l_v19_unblind.txt
```

Expected: `2016preVFP/templatesForCombine...` (not `/publicfs/...`)

### Local validation
```bash
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/datacards
python check_names.py --datacard input/datacard_1tau0l_v19_unblind.txt \
                      --systematics input/systematics_TOP24017.yml
```

---

## Key Decisions Made

1. **Luminosity era mapping**: 2016preVFP and 2016postVFP both map to `lumi_2016`
   - Rationale: CMS convention combines VFP periods for luminosity uncertainty
   - Impact: Simpler datacard structure, matches other CMS analyses

2. **Process-specific systematics**: QCDscale_ren/fac and ps_isr kept process-specific
   - Rationale: Analysis design choice for decorrelated treatment
   - Solution: Classified as "custom" class in validation YAML

3. **Template paths**: Use relative paths in datacards
   - Rationale: GitLab CI requirement for portability
   - Impact: Must ensure templates copied to datacards/input/YEAR/ directories

---

## Troubleshooting

### Issue: ValidateDatacards fails with "file not found"
**Cause**: Absolute paths in datacard
**Fix**: Convert to relative paths using sed command above

### Issue: check_systematics fails with "unknown systematic"
**Cause**: Systematic name not in systematics_TOP24017.yml
**Fix**: Add pattern to YAML or update systematic name in datacard

### Issue: Datacard has wrong luminosity naming
**Cause**: Old writeDatacard.py version
**Fix**: Update to version with yearMap in addLumi() function (commit 582c2535+)

---

## Contact Points

**Dev-docs**: `.claude/dev-docs/active/gitlab-ci-1tau0l-validation/`
**Detailed summary**: `session_summary_2025-11-26.md`
**Current status**: `context.md`
**This file**: `QUICK_REFERENCE.md`

**GitLab**: https://gitlab.cern.ch/cms-analysis/top/top-24-017/datacards
**Pipeline**: #13451015 (current)
