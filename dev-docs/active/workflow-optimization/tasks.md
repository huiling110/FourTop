# Tasks: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-09 (Session 7)
**Status**: IN PROGRESS

---

## Phase 1: Config Schema Cleanup ✅ COMPLETE

- [x] Define final minimal config schema → `config/analysis_config_template.yaml`
- [x] Update workflow_utils.py with all path builders
- [x] Add config validation (fail fast on missing keys)
- [x] Add backward compatibility with `_normalize_config()`
- [x] Test with existing Stage 4 scripts

**Commit**: `4ab2fd5a feat: Phase 1 workflow optimization - minimal config schema`

---

## Phase 2: Stage 4 Script Cleanup ✅ COMPLETE

- [x] createFaketauTree.py - Add argparse, remove ~35 commented paths
- [x] addJESTemplatesToHistFile.py - Make --config required, remove ~100 commented paths
- [x] addTemplateNew.py - Make --config required, remove ~75 commented paths
- [x] writeDatacard.py - Make --config required, remove ~110 commented paths
- [x] Create historical_paths_backup.txt (385 lines preserved)
- [ ] smooth_systematics_fourTops.py - Remove fallback paths (deferred)

**Commits**:
- `d976f909 feat: Phase 2 workflow optimization - createFaketauTree.py cleanup`
- `92637fe6 refactor: Clean up addJESTemplatesToHistFile.py for workflow optimization`
- `ae92a076 refactor: Clean up addTemplateNew.py for workflow optimization`
- `a0a9e5d7 refactor: Clean up writeDatacard.py for workflow optimization`

---

## Phase 3: Stage 2.4 Integration (Merged with Phase 2)

- [x] createFaketauTree.py - Add argparse (--config, --era, --quiet, --no-morph)
- [x] createFaketauTree.py - Integrate workflow_utils for config-based paths
- [ ] createFakeLeptonTree.py - Add argparse (pending)
- [ ] Add Stage 2.4 to run_workflow.py (pending)
- [ ] Test fake background generation (pending)

---

## Phase 4: Stage 3 Integration

- [ ] makeJob_forWriteHist.py - Add workflow_utils integration
- [ ] Remove temp script creation from run_workflow.py
- [ ] Update run_stage_3_3() to call script directly
- [ ] Test histogram production

---

## Phase 5: Stage 1-2 Integration ✅ COMPLETE

### Stage 1 (OS) ✅ COMPLETE
- [x] makeJob_OS_fromRuobing2.py - Complete rewrite with workflow_utils
  - Removed ~50 commented-out hardcoded paths
  - Added argparse: --config (required), --era, --sys, --dry-run, --quiet
  - Uses workflow_utils: load_config, get_eras, get_channel, build_stage1_input, build_stage1_output
- [x] Added Stage 1 functions to workflow_utils.py:
  - `build_stage1_input()`, `build_stage1_output()`, `get_channel_if1tau2l()`
  - `ERA_TO_UL`, `ERA_TO_NANOAOD` mapping dicts
- [x] Created batch submission scripts:
  - `submit_all_systematics.sh` - submits 15 systematic variations (JES, JER, MET, EleScale, TES by dm)
  - `check_systematic_jobs.sh` - monitors job status
- [x] Updated workflow skill with Stage 1 commands
- [x] Updated hooks (user-prompt-submit.sh) for OS script auto-triggering
- [x] OS systematic jobs for 2018 submitted (15 variations, in progress)

**Commit**: `14e2ae73 feat: Complete Phase 5 Stage 1 workflow integration`

### Stage 2 (MV) ✅ COMPLETE
- [x] makeJob_makeVaribles_forBDT.py - Complete rewrite with workflow_utils
  - Added argparse: --config (required), --era, --sys, --mc-only, --dry-run, --quiet
  - Uses workflow_utils: load_config, get_eras, get_channel, build_stage1_output, build_stage2_output
- [x] makeJob_MV_JESVariation.py - Batch submission script
  - Submits MV jobs for 14 systematic variations (TES×8, JER×2, MET×2, EleScale×2)
  - Supports --group option: TES, JER, MET, EleScale, all
- [x] Added `build_stage2_output()` to workflow_utils.py
- [x] Updated workflow skill with Stage 2 commands
- [x] Updated ANALYSIS_WORKFLOW.md with MV commands
- [x] MV systematic jobs for 2018 submitted (14 variations × 59 jobs = 826 jobs, running)

### run_workflow.py Integration ✅ COMPLETE
- [x] Added Stage 1, 1.1, 2, 2.1 to STAGES dict
- [x] Implemented run_stage_1(), run_stage_1_1(), run_stage_2(), run_stage_2_1()
- [x] Updated _run_era_stage() dispatcher
- [x] Config path stored in config dict for stage runners

**Commit**: `19300aed feat: Integrate Stage 1 (OS) and Stage 2 (MV) into run_workflow.py`

---

## Phase 6: Claude Integration ✅ COMPLETE

- [x] Create .claude/skills/workflow.md - Analysis pipeline skill
- [x] Create .claude/hooks/pre-tool-use.sh - Environment check, path validation
- [x] Create .claude/hooks/user-prompt-submit.sh - Auto-activation based on keywords
- [x] Update .claude/settings.json with hooks
- [x] Test skill triggering - works for stage/run/job/histogram keywords
- [x] Document workflow_utils pattern in skill

**Commits**:
- `dd63c875` - Create workflow skill and hooks
- `444ff113` - Update pl.py to read options from YAML config
- `cc1be1c7` - refactor: Clean up pl.py to use workflow_utils consistently
- `26037fa0` - docs: Update workflow skill with workflow_utils pattern

---

## Quality Checks

- [x] All Stage 4 scripts have consistent argparse pattern (--config required, --era required, --quiet optional)
- [x] ~320 commented-out paths removed from Stage 4 scripts
- [x] All Stage 4 path building uses workflow_utils
- [x] Config validation catches errors early (ValueError on missing --config)
- [ ] Full pipeline runs with single command (pending)

---

## Notes

**Session 1 (2025-12-08)**:
- Analyzed current config usage patterns across all stages
- Identified ~200+ commented paths to remove
- Created comprehensive plan with 6 phases
- User approved plan and requested historical paths backup

**Session 2 (2025-12-08)**:
- Completed Phase 1: Created minimal config schema with backward compatibility
- Completed Phase 2: Cleaned up 4 Stage 4 scripts, removed ~320 commented paths
- Historical paths saved to `config/historical_paths_backup.txt`
- All cleaned scripts now require --config and --era flags
- Ready to create Claude skill and hook for workflow automation
- User wants to test workflow with 1tau0l config (WH creation for 2017, then pl.py)

**Session 3 (2025-12-08)**:
- Completed Phase 6: Claude Integration
  - Created workflow skill with environment requirements, stage commands
  - Created pre-tool-use hook to catch setEnv path errors
  - Created user-prompt-submit hook for auto-activation
  - Added workflow_utils Python pattern documentation
- Updated 1tau0l config to new minimal format (versions section, normalized options)
- Refactored pl.py to use workflow_utils consistently (~200 lines removed)
- Tested WH jobs and pl.py for 1tau0l: 2017, 2016postVFP, 2016preVFP - all working
- Key finding: `systematics: false` in config skips JES systematic histogram lookup

**Session 4 (2025-12-08)**:
- Trimmed CLAUDE.md from ~330 to ~90 lines (removed duplication with workflow skill)
- Added rule 5: "Commit often after significant code changes"
- Renamed config: `analysis_config_1tau0l_full.yaml` → `analysis_config_1tau0l_TTBBtest.yaml`
- Completed 1tau1l channel testing:
  - WH jobs submitted and completed for 2017, 2016postVFP, 2016preVFP (71 files each)
  - pl.py validated for all three eras - BDT plots generated successfully
- Both 1tau0l and 1tau1l configs now use consistent `_TTBBtest` naming
- Workflow optimization Phase 1-6 working well for Stage 3 and Stage 4

**Session 5 (2025-12-08)**:
- Completed Phase 5 Stage 1 (OS) workflow integration:
  - Refactored makeJob_OS_fromRuobing2.py to use workflow_utils (~50 paths removed)
  - Added Stage 1 path functions to workflow_utils.py
  - Created batch scripts: submit_all_systematics.sh, check_systematic_jobs.sh
  - Supports 15 systematic variations (JES, JER, MET, EleScale, TES by decay mode)
  - TES by decay mode only (dm0, dm1, dm10, dm11), NOT total TESUp/TESDown
- Enabled systematics: true in 1tau0l config
- Submitted OS systematic jobs for 2018 (15 variations, running)
- Updated ANALYSIS_WORKFLOW.md Section 1.4 with new workflow
- Next: Wait for OS jobs (~2-3 hours), then MV + WH testing

**Session 6 (2025-12-08)**:
- Completed Phase 5 Stage 2 (MV) workflow integration:
  - Refactored makeJob_makeVaribles_forBDT.py to use workflow_utils
  - Refactored makeJob_MV_JESVariation.py for batch systematic submission
  - Added build_stage2_output() to workflow_utils.py
  - Supports 14 systematic variations (TES×8, JER×2, MET×2, EleScale×2)
- Integrated Stage 1 and Stage 2 into run_workflow.py:
  - Added Stage 1, 1.1, 2, 2.1 to STAGES dict
  - Implemented run_stage_1/1_1/2/2_1() functions
  - Updated _run_era_stage() dispatcher
  - Config path stored in config dict for script access
- Submitted MV systematic jobs for 2018 (14 variations × 59 jobs = 826 jobs, running)
- Updated workflow skill and ANALYSIS_WORKFLOW.md with MV commands
- Next: Wait for MV jobs, then Stage 3 (WH) testing with systematics

**Session 7 (2025-12-09)**:
- MV systematic jobs completed for 2018 (all 14 variations)
- Completed Phase 5 Stage 3.1 (WH systematics) workflow integration:
  - Refactored makeJob_WH_forJES.py to use workflow_utils
  - Added argparse: --config (required), --era, --group (TES/JER/MET/EleScale/all), --dry-run, --quiet
  - Removed all commented-out hardcoded paths
  - Tested dry run: 14 variations × 59 MC files = 826 jobs
- Documented Three Workflow Modes in .claude/skills/workflow.md:
  - Mode 1: Nominal Test Run (quick validation, systematics: false)
  - Mode 2: Add Systematics After Nominal (continue from Mode 1)
  - Mode 3: Full Workflow (production run with all systematics)
- Next: Submit WH systematic jobs for 2018, then Stage 4.1 to merge JES templates
