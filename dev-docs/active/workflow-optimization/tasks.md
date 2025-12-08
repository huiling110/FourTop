# Tasks: FourTop Workflow Optimization

**Created**: 2025-12-08
**Last Updated**: 2025-12-08
**Status**: PLANNING

---

## Phase 1: Config Schema Cleanup

- [ ] Define final minimal config schema
- [ ] Update workflow_utils.py with all path builders
- [ ] Add config validation (fail fast on missing keys)
- [ ] Create config migration script (optional)
- [ ] Test with existing Stage 4 scripts

---

## Phase 2: Stage 4 Script Cleanup

- [ ] addJESTemplatesToHistFile.py - Remove fallback paths, make --config required
- [ ] addTemplateNew.py - Remove fallback paths, make --config required
- [ ] writeDatacard.py - Remove fallback paths, make --config required
- [ ] smooth_systematics_fourTops.py - Remove fallback paths
- [ ] Test all Stage 4 scripts end-to-end

---

## Phase 3: Stage 2.4 Integration

- [ ] createFaketauTree.py - Add argparse (--config, --era, --quiet)
- [ ] createFaketauTree.py - Remove ~45 commented paths
- [ ] createFakeLeptonTree.py - Add argparse
- [ ] createFakeLeptonTree.py - Remove commented paths
- [ ] Add Stage 2.4 to run_workflow.py
- [ ] Test fake background generation

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

## Phase 6: Claude Integration

- [ ] Create .claude/skills/workflow.md
- [ ] Create .claude/hooks/pre-tool-use.sh (environment check)
- [ ] Test skill triggering
- [ ] Document in CLAUDE.md

---

## Quality Checks

- [ ] All scripts have consistent argparse pattern
- [ ] No commented-out paths remain in scripts
- [ ] All path building uses workflow_utils
- [ ] Config validation catches errors early
- [ ] Full pipeline runs with single command

---

## Notes

**Session 1 (2025-12-08)**:
- Analyzed current config usage patterns across all stages
- Identified ~200+ commented paths to remove
- Created comprehensive plan with 6 phases
- Waiting for user approval before implementation
