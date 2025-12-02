# Plan: FourTop Workflow Code Quality Improvements

**Created**: 2025-12-02
**Status**: In Progress
**Priority**: HIGH

---

## Executive Summary

Improve code quality across FourTop analysis workflow (Stage 3-4) by fixing duplicate code, adding --quiet flags to reduce verbose output, and archiving commented configuration paths. This will reduce token consumption, improve maintainability, and eliminate code bugs.

---

## Problem Statement

The plotting and datacard scripts have accumulated technical debt:
1. Duplicate function definition in `smooth_systematics_fourTops.py`
2. Verbose output printing ~130 systematics consuming tokens
3. ~500+ commented configuration paths scattered across scripts
4. No CLI flags to control verbosity

---

## Current State

| File | Issue |
|------|-------|
| `plotting/smooth_systematics_fourTops.py` | `get_smoothed_up_and_down()` defined twice (lines 303, 367) |
| `plotting/writeDatacard.py` | Prints entire MCSys dict (~130 items), no --quiet |
| `plotting/addTemplateNew.py` | Debug prints, no --quiet |
| `plotting/addJESTemplatesToHistFile.py` | ~300 commented nominalDir lines |
| `hua/combine/writeCombinationDatacard.py` | ~150 path dictionary entries |

---

## Desired State

- No duplicate function definitions
- All plotting scripts support `--quiet` flag
- Commented paths archived to `plotting/OLD_CONFIGS.md`
- Clean, maintainable codebase
- 50-70% reduction in output tokens when running scripts

---

## Approach

### Phase 1: Code Quality Fixes (Current)

**Goals**:
- Fix the duplicate function bug
- Add --quiet flags to reduce verbose output

**Tasks**:
1. Delete duplicate `get_smoothed_up_and_down()` at lines 367-388
2. Add `--quiet` flag to `writeDatacard.py`
3. Add `--quiet` flag to `addTemplateNew.py`
4. Add `--quiet` flag to `smooth_systematics_fourTops.py`

**Deliverables**:
- Bug-free smooth_systematics_fourTops.py
- All three scripts support --quiet flag

### Phase 2: Archive Commented Paths (Future)

**Goals**:
- Clean up commented configuration paths
- Create archive for historical reference

**Tasks**:
1. Create `plotting/OLD_CONFIGS.md`
2. Archive paths from writeDatacard.py
3. Archive paths from addJESTemplatesToHistFile.py
4. Archive paths from addTemplateNew.py
5. Archive paths from writeCombinationDatacard.py

**Deliverables**:
- OLD_CONFIGS.md with all historical paths
- Clean scripts with minimal commented code

---

## Risks and Mitigations

**Risk 1**: Breaking existing functionality when removing duplicate function
- **Likelihood**: Low
- **Impact**: Medium
- **Mitigation**: Keep the first definition (line 303), verify function signature matches all call sites

**Risk 2**: --quiet flag breaks existing scripts that parse output
- **Likelihood**: Low
- **Impact**: Low
- **Mitigation**: Default behavior unchanged (verbose), --quiet is opt-in

---

## Success Criteria

- [ ] No duplicate function definitions in codebase
- [ ] `python3 writeDatacard.py --quiet` produces minimal output
- [ ] `python3 addTemplateNew.py --quiet` produces minimal output
- [ ] `python3 smooth_systematics_fourTops.py --quiet` produces minimal output
- [ ] Scripts still function correctly without --quiet flag

---

## Timeline

- Phase 1: Current session
- Phase 2: Future session (when user requests)
