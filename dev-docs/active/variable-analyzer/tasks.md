# Task Status

## Implementation

| Task | Status | Notes |
|------|--------|-------|
| Copy functions.C from Ruobing | Completed | Updated binning, fixed branch names |
| Create variableAnalyzer.h | Completed | Header with SystematicManager |
| Create variableAnalyzer.C | Completed | Full implementation |
| Create run_variableAnalyzer.C | Completed | Entry point |
| Add SystematicManager methods | Completed | 3 new methods for variable vectors |
| Update Makefile | Completed | `make variables` target |
| Update makeJob_forWriteHist.py | Completed | `--mode variables` option |
| Build and test | Completed | Successfully built |
| Update WH skill | Completed | Added variableAnalyzer section |

## Session Notes

### 2025-01-25
- Plan approved for Option C (new variableAnalyzer.C)
- Using Ruobing's binning from functions.C
- No MC fake tau separation
- Output directory: `inputVarHists_{version}/` (not `variableHists_` to avoid BDT conflict)

### Session Completion
- All files created and built successfully
- Fixed missing branches in Ruobing's functions.C:
  - `tausF_prongNum` → use `tausT_prongNum`
  - `tausF_1genPartonFlavour` → removed (not in event class)
- Added TFile* overloaded versions of `calQCDScaleNor` and `calPDFScaleNor`
- Restored myLibrary from git (was accidentally deleted)
- Stage 3 WH skill updated with variableAnalyzer documentation

## Verification Results (2026-01-25)

### 2018 Nominal Jobs
- **Submitted**: 75 jobs (71 MC + 4 data, VLL skipped)
- **Completed**: 37/38 MC + 4/4 data
- **Note**: tttt nominal job stuck at initialization (60+ min) - may need resubmit
- **Comparison with BDT output**: ✅ Passed
  - Same histogram count per process (40,734)
  - Same regions (1tau0lSR, VR, CRMR)
  - b-tag systematics: 11,388 histograms ✅
  - Tau ID systematics: 13,140 histograms ✅
  - MC fake tau systematics: 876 histograms ✅

### Energy Scale Variations
- **TES (8 variations)**: 26 files each ✅ (all completed)
- **JER (2 variations)**: 26 files each ✅
- **MET (2 variations)**: 26 files each ✅
- **EleScale (2 variations)**: 26 files each ✅
- Note: 26 files = 59 source - 33 VLL (correctly skipped)

### Output Paths
- Nominal: `.../v1baselineHadro_v95XGB080testOS7/mc/inputVarHists_v0BDT1tau0l_XGB080testNew/`
- TES: `.../v1baselineHadro_v95XGB080testOS7_TESdm{0,1,10,11}{Up,Down}/mc/inputVarHists_*/`
- JER/MET/EleScale: `.../v1baselineHadro_v95XGB080testOS7_{JER,MET,EleScale}{Up,Down}/mc/inputVarHists_*/`

## Stage 4 Integration (2026-01-25)

### Scripts Updated for `--mode variables`
| Script | Status | Notes |
|--------|--------|-------|
| fourtop/workflow/paths.py | Completed | Added mode param to build_hist_path, build_combine_path, build_template_path, build_datacard_path |
| fourtop/stage4/systematics.py | Completed | Added variables param to addTESToFile, addMETToFile, addEESToFile |
| plotting/addJESTemplatesToHistFile.py | Completed | Added --mode and --variables arguments |
| plotting/addTemplateNew.py | Completed | Added --mode argument |
| plotting/writeDatacard.py | Completed | Added --mode argument |

### Tested Workflow (2018 tausT_1pt)
1. **addJES**: JES failed (see below), JER/TES/MET/EES all successful ✅
2. **addTemplate**: Created template with 1848 histograms (30 nominal, 1818 systematic) ✅
3. **writeDatacard**: Created datacard with all systematics ✅

### JES Failure Analysis
**Why JES failed**: JES requires a different workflow than TES/JER/MET/EleScale:
- TES/JER/MET/EleScale: Use **nominal** Stage 2 MV output, variation applied at Stage 3 WH
- JES: Requires **separate** Stage 2 MV jobs first, then Stage 3 WH

**Status**: Stage 2 MV JES directories **exist** for v95XGB080testOS7. What was missing:
- Stage 3 WH variableAnalyzer on JES outputs (`inputVarHists_*` in JES directories)

**Fix applied (2026-01-25)**:
```bash
cd writeHistGood/jobs/
python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_XGB080test.yaml --era 2018 --systematic JES --mode variables
# Submitted: 60 variations × 59 MC = 3540 jobs
```

**Full JES workflow for input variables**:
1. Stage 2 MV JES: Already exists (from previous BDT workflow)
2. Stage 3 WH JES: `makeJob_WH.py --systematic JES --mode variables` ← Completed (3540 jobs)
3. addJES/addTemplate/writeDatacard: ✅ All completed with 30 JES sources

**Final verification (2026-01-25)**:
- Template: 180 JES histograms for tausT_1pt (30 sources × 2 directions × 3 regions)
- Datacard: All JES systematics (CMS_scale_j_*) properly configured

### Output Files
- Template: `inputVarHists_*/combine/templatesForCombine1tau0l_v3_tausT_1pt_notMCFTau_unblind.root`
- Datacard: `inputVarHists_*/combine/datacardSys_v1_xgb080_test_tausT_1pt/datacard.txt`

### Stage 5 Skill Created
- `.claude/skills/workflow-stage5-paper/SKILL.md` - Documents input variable prefit workflow

## Next Steps

1. Re-submit stuck tttt nominal job if needed
2. Submit variableAnalyzer for other eras (2017, 2016preVFP, 2016postVFP)
3. Submit variableAnalyzer for other channels (1tau1l, 1tau2l)
4. Move this task to `dev-docs/finished/` when complete

## Files Created/Modified

Created:
- `writeHistGood/include/variableAnalyzer.h`
- `writeHistGood/src/variableAnalyzer.C`
- `writeHistGood/apps/run_variableAnalyzer.C`
- `dev-docs/active/variable-analyzer/plan.md`

Modified:
- `writeHistGood/src/functions.C` - From Ruobing + TFile* functions + branch fixes
- `writeHistGood/include/SystematicManager.h` - Added 3 methods for variable vectors
- `writeHistGood/Makefile` - Added `make variables` target
- `writeHistGood/jobs/makeJob_forWriteHist.py` - Added `--mode variables`
- `writeHistGood/jobs/makeJob_WH.py` - Added `--mode variables` option (main submission script)
- `.claude/skills/workflow-stage3-wh/SKILL.md` - Added variableAnalyzer section
