# Context: FourTop Workflow Code Quality Improvements

**Created**: 2025-12-02
**Last Updated**: 2025-12-02

---

## Problem Overview

The FourTop analysis workflow scripts have accumulated technical debt including duplicate code, verbose output, and hundreds of commented configuration paths. This makes the code harder to maintain and causes excessive token consumption when running with Claude.

---

## Key Files

**File 1**: `plotting/smooth_systematics_fourTops.py`
- **Purpose**: Apply LOWESS smoothing to systematic variations
- **Relevant sections**:
  - Lines 303-325: First definition of `get_smoothed_up_and_down()`
  - Lines 367-388: DUPLICATE definition (TO DELETE)
- **Notes**: The duplicate function shadows the first definition

**File 2**: `plotting/writeDatacard.py`
- **Purpose**: Generate CMS Combine datacards from template ROOT files
- **Relevant sections**:
  - Lines 1-50: Imports and setup (add argparse here)
  - Lines ~200-230: Verbose sysDic printing (wrap with --quiet check)
  - Lines 1-150: ~250 commented inputTemplate paths
- **Notes**: MCSys dictionary has ~130 systematics, all printed on every run

**File 3**: `plotting/addTemplateNew.py`
- **Purpose**: Create template ROOT files for Combine from histogram files
- **Relevant sections**:
  - Lines 1-30: Imports (add argparse)
  - Various print() statements throughout
- **Notes**: ~80 commented inputDir paths

**File 4**: `plotting/addJESTemplatesToHistFile.py`
- **Purpose**: Consolidate JES/JER/TES shape systematics into nominal histogram files
- **Relevant sections**:
  - Lines 1-300: ~300 commented nominalDir configurations
- **Notes**: Already has argparse for --delete-sys-dirs and --execute

**File 5**: `hua/combine/writeCombinationDatacard.py`
- **Purpose**: Combine datacards from multiple eras/channels
- **Relevant sections**:
  - pathDic dictionary: ~150 path entries
- **Notes**: Used for Run2 combination

---

## Key Concepts

**LOWESS Smoothing**: Local weighted scatterplot smoothing applied to systematic variations to reduce statistical fluctuations while preserving shape information.

**Datacards**: Text files defining signal/background processes, systematic uncertainties, and bin yields for CMS Combine statistical tool.

**Shape Systematics**: Systematic uncertainties that affect the shape of distributions (not just normalization), stored as up/down histogram variations.

---

## Dependencies

- `argparse`: Python standard library for CLI argument parsing
- All scripts already import necessary ROOT/numpy modules
- No external dependencies need to be added

---

## Constraints

- Must preserve backward compatibility (default behavior unchanged)
- Cannot modify function signatures that are called from other scripts
- Scripts must still work without --quiet flag (opt-in only)

---

## Related Documentation

- `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/ANALYSIS_WORKFLOW.md` - Stage 4 workflow details
- `/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/CLAUDE.md` - Project context and TODO for --quiet flags
- `/afs/ihep.ac.cn/users/h/huahuil/.claude/plans/moonlit-singing-naur.md` - Full improvement plan
