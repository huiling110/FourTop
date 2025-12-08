# Tasks: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-08 (Session 3)
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

## Phase 5: Stage 1-2 Integration

- [ ] makeJob_OS_fromRuobing2.py - Standardize config loading
- [ ] makeJob_makeVaribles_forBDT.py - Add --config support
- [ ] Add Stage 1 and 2 to run_workflow.py
- [ ] Test full pipeline from NanoAOD

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
- Next: 1tau1l channel testing (WH jobs for 2017, 2016)
