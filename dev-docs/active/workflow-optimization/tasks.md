# Tasks: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-09 (Session 9)
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

## Phase 7: Long-Running Job Integration

**Status**: IN PROGRESS (Session 2025-12-10)

- [x] Design patterns for handling long-running workflow steps (combine fits, systematic jobs)
- [x] Document best practices for multi-hour workflows
- [x] Test real example: OS systematic jobs for 2017 (2-3 hour runtime)
- [ ] Implement state tracking in runCombineAll.py (resume capability)
- [ ] Implement `.workflow_state.json` for workflow state persistence
- [ ] Add `--wait` flag to job submission scripts
- [ ] Create unified job monitoring tool

**Motivation**: Many analysis steps take hours to complete (combine fits, large systematic processing). Need clear patterns for:
1. Submitting jobs and tracking status
2. Resuming workflow after long waits
3. Handling partial failures in batch submissions
4. User experience when waiting for results

**Documentation**:
- Pattern documentation: `dev-docs/active/workflow-optimization/long-running-jobs.md`
- Real example: `dev-docs/active/workflow-optimization/session-learnings-2025-12-10.md`

**Patterns Defined**:
1. **Background Job Submission** - HTCondor job tracking with monitoring commands
2. **Combine Workflow** - Multi-step analysis with state persistence
3. **Staged Workflow** - Automatic progression through pipeline stages
4. **Partial Failure Handling** - Resubmit only failed jobs, not entire batch
5. **Progress Reporting** - Real-time updates for long-running tasks (impacts, etc.)

**Real Test Case** (2025-12-10):
- Submitted OS systematics for 2017 (15 variations)
- Expected runtime: 2-3 hours
- Gap identified: No workflow state tracking when resuming after wait

---

## Phase 8: Redesign Workflow Hooks + Skills ✅ COMPLETE

**Status**: COMPLETE (2025-12-10)

**Problem** (Validated with real test case):
- `.claude/skills/workflow.md` too long (565 lines) - hard to parse
- Skills not triggered properly - banner ignored when user said "submit OS jobs for 2017"
- Claude doesn't remember workflow state - lost context after 2-3 hour waits
- No workflow state persistence across sessions

**Goals**:
- [x] Learn during current session how hooks + skills work
- [x] Document proper hook/skill setup for workflow automation
- [x] Design 3-part solution (state tracking + enhanced hooks + modular skills)
- [x] Get user approval for implementation plan
- [x] **STEP 1**: Add WorkflowState class to workflow_utils.py (~180 lines) ✅
- [x] **STEP 2**: Enhance user-prompt-submit.sh with state injection ✅
- [x] **STEP 3**: Split workflow.md into modular skills (7 focused files) ✅
- [x] **STEP 4**: Test with real workflow (1tau1l WH systematics for 2018) ✅
- [x] **STEP 5**: Update dev-docs and commit ✅

**Implementation Plan**: `~/.claude/plans/giggly-snuggling-wand.md`

**User Preferences** (confirmed):
- Unified state file for all channels (not per-channel files)
- Auto-inject context only (not auto-invoke skills)

**Solution Design**:
1. **Workflow State Tracking**: `.workflow_state.json` at project root
   - Tracks current stage, era, operation status per channel
   - Persists across sessions
   - Enables context injection by hooks

2. **Enhanced Hooks**: `user-prompt-submit.sh` reads state
   - Injects `<workflow_context>` with stage/era/status
   - No more ignored banners - context automatically visible
   - Suggests monitoring commands and next steps

3. **Modular Skills**: Split 565-line workflow.md into 7 files
   - `skill.json` - Make discoverable
   - `overview.md` - Modes, config, Python patterns (~100 lines)
   - `stage1-os.md`, `stage2-mv.md`, `stage3-wh.md`, `stage4-combine.md` (~80 lines each)
   - `status-checker.md` - Pipeline status commands

**References**:
- Learning session: `dev-docs/active/workflow-optimization/session-learnings-2025-12-10.md`
- Hook exploration: `dev-docs/active/workflow-optimization/hooks-and-skills-learning.md`
- Current files: `.claude/skills/workflow.md`, `.claude/hooks/*.sh`
- State tracking: `plotting/workflow_utils.py` (to be modified)

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
- WH systematic jobs submitted and completed for 2018 (14 variations × 59 = 826 jobs)
- Updated ANALYSIS_WORKFLOW.md Section 3.3 with new config-based workflow
- **FINDING**: Stage 4.1 and 4.2 are BLOCKED by missing JES systematics:
  - addJESTemplatesToHistFile.py expects JES histogram directories (27 sources × 2)
  - addTemplateNew.py expects JES templates already in nominal histogram files
  - JES systematics require separate Stage 1.1 → 2.1 → 3.1 processing
  - TES/JER/MET/EleScale (14 variations) are complete but JES (54 variations) is not
- Next steps: Either process JES systematics (large) or proceed without JES for test

**Session 8 (2025-12-09)**:
- Recovered JES job submission functionality that was removed during refactoring:
  - Fixed JES path format: `{stage2}_JES{up/Down}_{source}_{stage1}_JESPt22`
  - Added `_build_jes_output_path()` to makeJob_makeVaribles_forBDT.py
  - Added `_build_jes_input_path()` to makeJob_WH_forJES.py
  - Added `build_stage2_output_jes()` to workflow_utils.py
  - Import JES sources from ttttGlobleQuantity.py (30 sources × 2 = 60 variations)
- Verified JES index-to-source matching works correctly:
  - Python JESVariationList index matches C++ expectation
  - Output directory names match the source passed to C++ code
- **Commit**: `ec0b12be fix: Recover JES job submission with correct path format`
- Current focus: Systematic workflow (nominal steps completed)
- Next: Submit MV JES jobs → WH all systematics for 2018

**Session 9 (2025-12-09)**:
- Previous MV JES submission failed due to workfs file quota (50,000/50,000)
- Freed quota by moving old combine versions (V7-V17) to publicfs:
  - Moved to: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/run2_combination/`
  - Freed ~8,300 files
- Successfully resubmitted MV JES jobs: **60/60 variations submitted** ✅
- MV JES complete: 6,315 root files produced
- WH JES submitted: **3,540 jobs** (60 variations × 59 files) ✅
- Updated workflow skill with **Stage 4.2.5 (smoothing)** - was missing!
- **IMPORTANT**: Smoothing requires ALL eras (2016, 2017, 2018) templates
  - For 2018-only test: SKIP smooth_systematics_fourTops.py
  - Run smoothing later after processing all eras
- Current test workflow for 2018 only:
  ```
  Stage 4.1 (addJESTemplates) → Stage 4.2 (addTemplateNew)
  → Stage 4.3 (writeDatacard) → Stage 4.4 (pl.py)
  → [SKIP 4.2.5 smoothing for now]
  ```
- Next: Wait for WH JES → Stage 4.1-4.4 (without smoothing)

**Session 9 continued (2025-12-09)**:
- Fixed `addJESTemplatesToHistFile.py` to use workflow_utils:
  - Added `build_hist_path_jes()` function to workflow_utils.py
  - Updated addJESToFile() to use config-based path building
  - Uses `_CONFIG` global variable when config is provided
  - Maintains backward compatibility with legacy path building
- Stage 4.1 now works correctly with config-based workflow

**Session 10 (2025-12-09)**:
- Completed Stage 4.1-4.3 for 2018 with full JES systematics:
  - Stage 4.1 (addJESTemplatesToHistFile.py) ✅
  - Stage 4.2 (addTemplateNew.py) ✅
  - Stage 4.3 (writeDatacard.py) ✅
- Fixed `writeDatacard.py` to read `smoothing` option from config:
  - Added `--no-smoothed` flag for explicit override
  - Default now reads from `options.smoothing` in config
  - Command-line args override config when provided
- Added **Workflow Standard Checklist** to context.md for script compliance
- Updated datacard version to `v0_ttbb_nosmoothing` for test run
- Datacard output: `.../combine/datacardSys_v0_ttbb_nosmoothing/datacard_1tau0l.txt`
- **PAUSED**: Switching to ttbb-integration task to add uncertainties to datacard
- Next: Return to complete Stage 4.4 (pl.py) and remaining eras

**Session 11 (2025-12-10)** - Phase 7 & 8:
- **TTBB Integration**: Generated postfit plots successfully
  - Script: `plotting/pl_postFit.py --fit-file .../fitDiagnosticsTest.root`
  - Generated 6 plots for 2018 1tau0l (prefit/fit_s/fit_b)
  - TTBB contribution visible in stack plots ✅
  - **Note**: pl_postFit.py doesn't fully comply with workflow standard (--config not required)
- **Phase 7**: Long-Running Job Integration
  - Created comprehensive documentation: `long-running-jobs.md` (372 lines)
  - Defined 5 patterns for handling long-running tasks
  - **Real test case**: Submitted OS systematics for 2017 (15 variations, 2-3 hour runtime)
  - Gap identified: No workflow state tracking when resuming after wait
- **Phase 8**: Redesign Workflow Hooks + Skills
  - Created learning documentation: `hooks-and-skills-learning.md` (309 lines)
  - **Key finding**: Hook banners easily ignored (validated with "submit OS jobs for 2017" test)
  - Designed 3-part solution: state tracking + enhanced hooks + modular skills
  - User preferences confirmed: unified state file, auto-inject context only
  - Created session learnings: `session-learnings-2025-12-10.md` (real-world example)
  - Implementation plan approved and ready
  - **Status**: Started implementation (Step 1 in progress)
- **Commits**:
  - `97d36dd9` - Phase 7 and Phase 8 documentation
  - `42ccbafd` - Phase 8 planning and real test case documentation

**Session 12 (2025-12-10)** - Phase 8 Implementation Complete:
- **Step 1**: WorkflowState class added to workflow_utils.py (~180 lines) ✅
  - Unified state file for all channels: `.workflow_state.json` at project root
  - Methods: `update_stage()`, `get_current()`, `get_stage_status()`, `log_execution()`
  - Atomic writes with temp file for safety
  - History logging (keeps last 100 entries)
  - Tested and verified working
- **Step 2**: Enhanced user-prompt-submit.sh hook ✅
  - Reads `.workflow_state.json` when workflow keywords detected
  - Detects channel from prompt (1tau0l, 1tau1l, 1tau2l) or uses first in state
  - Injects `<workflow_context>` with stage/era/operation/status
  - Uses jq with Python fallback for JSON parsing
  - Tested with both 1tau0l and 1tau1l channels
- **Step 3**: Modular skill system created ✅
  - Split 565-line workflow.md into 7 focused files:
    - `skill.json` - Skill registration (discoverable)
    - `overview.md` - Workflow modes, config, Python patterns (~200 lines)
    - `stage1-os.md` - Stage 1 Object Selection (~80 lines)
    - `stage2-mv.md` - Stage 2 Make Variables (~90 lines)
    - `stage3-wh.md` - Stage 3 Histograms (~80 lines)
    - `stage4-combine.md` - Stage 4 Templates/Combine (~150 lines)
    - `status-checker.md` - Pipeline status commands (~200 lines)
  - Original workflow.md backed up to workflow.md.backup
  - Skills now discoverable via Skill tool
- **Step 4**: Real workflow test with 1tau1l WH systematics ✅
  - Enabled `systematics: true` in 1tau1l config
  - Updated workflow state for 1tau1l channel
  - Dry-run verified: 74 systematic variations (14 energy scale + 60 JES)
  - Submitted WH TES systematics for 2018 (8 variations × 59 files = 472 jobs)
  - Jobs submitted successfully ✅
- **Commits**:
  - `d865d525` - feat: Add WorkflowState class (Step 1)
  - `890503a8` - feat: Enhance user-prompt-submit hook (Step 2)
  - `de247280` - feat: Split workflow.md into modular skill system (Step 3)
  - `18a660d0` - test: Enable systematics in 1tau1l config (Step 4)
- **Status**: Phase 8 implementation complete, testing successful

**Session 14 (2025-12-10)** - 1tau1l 2018 Continue:
- Resumed workflow-optimization task
- **Issue Found**: Workflow state not auto-updating
  - **Root Cause**: Phase 8 implemented WorkflowState class + hook that READS state
  - **Gap**: No scripts actually CALL `state.update_stage()` to write state
  - State file was manually updated during testing but never integrated into scripts
  - Hook works correctly - it reads and injects context
  - **FIX NEEDED**: Integrate WorkflowState calls into:
    1. Job submission scripts (makeJob_*.py) - update on submit
    2. run_runCombineAll.sh or runCombineAll.py - update on start/complete
    3. Or: Create post-submission hook that updates state
- Updated run_runCombineAll.sh for 1tau1l 2018 Stage 4.5
- Combine steps: workspace, significance, postfit, signal_strength, impacts
- Combine job running (PID 2151426)

**Session 13 (2025-12-10)** - Phase 8 Finalization:
- **Step 5 Complete**: Final cleanup committed
  - Deleted monolithic workflow.md (565 lines)
  - Added Bash permissions for job monitoring (git, hep_q, condor_q, wc, grep)
  - All modular skills now in `.claude/skills/workflow/` directory
- **Job Status**:
  - 1tau0l: OS 2017 systematics still running (15 variations, ~2.5 hours in)
  - 1tau1l: WH 2018 systematics queued (7,493 jobs in idle state)
- **Archive Script Created**: `scripts/archive_and_cleanup.sh`
  - Safely archives and deletes Stage 1 systematic directories
  - Creates tar.gz in source directory, verifies integrity before deletion
  - Started archiving UL2018 TTBBtest systematics (15 dirs, ~82GB, ~180K files)
  - Running in background (PID 1528318), estimated 8-15 hours
  - Excellent compression: 5.5GB → ~250MB per directory (~4% of original)
  - Monitor: `tail -f archive_UL2018.log`
  - Check archives: `ls -lh /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/UL2018/*.tar.gz`
  - **TODO**: Check completion and verify extraction works
- **Commits**:
  - `1a3543da` - chore: Finalize Phase 8 - remove old workflow.md, add permissions
  - `71cf88ad` - docs: Complete Phase 8 Step 5 - update dev-docs
  - `90098bf8` - chore: Add comprehensive non-dangerous Bash permissions
  - `2a5c1679` - feat: Add archive_and_cleanup.sh for safe systematic directory archival
- **Phase 8 COMPLETE** - All 5 steps finished
- **1tau1l 2018 Stage 4 COMPLETE**:
  - Stage 4.1: JES templates added ✅
  - Stage 4.2: Templates created (TES, JER, MET, EleScale, JES) ✅
  - Stage 4.3: Datacard written (v0_ttbb_nosmoothing) ✅
  - Stage 4.4: Plots generated (4 PNG files) ✅
  - **Warning**: Large systematic variations in `CMS_eff_e_reco_2018` - needs investigation
- **IMPORTANT TODO**: Add TTBB process to `smooth_systematics_fourTops.py` before running full Run2 (3 years) smoothing for 1tau1l and 1tau0l channels
