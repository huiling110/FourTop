# Python System Refactoring - Implementation Plan

## Phase 1: Package Foundation

### Steps
1. Create new git branch `refactor-python-system`
2. Create `fourtop/` package skeleton with all `__init__.py` files
3. Update `setEnv_newNew.sh` to add PYTHONPATH
4. Move `workflow_utils.py` to `fourtop/workflow/config.py` and `paths.py`
5. Create wrapper in original location

### Verification
- `python3 -c "from fourtop.workflow import config, paths"` succeeds
- Original scripts still work via wrappers

---

## Phase 2: Constants Extraction

### Steps
1. Extract `fourtop/constants/era.py` (consolidate VFP mapping)
2. Extract `fourtop/constants/systematics.py` (MCSys from writeDatacard.py)
3. Split `ttttGlobleQuantity.py`:
   - `constants/physics.py` (lumiMap, crossSectionMap)
   - `constants/samples.py` (histoGramPerSample, proChannelDic)
   - `constants/jes.py` (JESVariationList, SKIP_SUBPROCESSES)
4. Update imports in consuming files

### Verification
- All constant values match original (unit tests)
- writeDatacard.py works with imported MCSys

---

## Phase 3: Utilities Refactoring

### Steps
1. Split `usefulFunc.py`:
   - `utils/io.py` (checkMakeDir, file operations)
   - `utils/histogram.py` (getSumHist, addBGHist, handle_negative_bins)
   - `utils/process.py` (isData, isBG, getAllSubPro, getSubProScale)
2. Create `utils/logging.py` with centralized logger setup
3. Update imports in consuming files

### Verification
- Histogram operations produce identical results
- Process filtering returns same lists

---

## Phase 4: Stage 4 Scripts (Part 1)

### Steps
1. Refactor `pl.py`:
   - `fourtop/plotting/style.py` (setTDRStyle functions)
   - `fourtop/plotting/stack.py` (makeStackPlotNew, getHists)
   - `fourtop/plotting/validation.py` (plotNormal, main)
2. Refactor `addTemplateNew.py` → `fourtop/stage4/templates.py`
3. Keep wrappers in original locations

### Verification
- Validation plots visually identical
- Template ROOT files bit-identical to golden

---

## Phase 5: Stage 4 Scripts (Part 2)

### Steps
1. Refactor `writeDatacard.py` → `fourtop/stage4/datacards.py`
2. Refactor `addJESTemplatesToHistFile.py` → `fourtop/stage4/systematics.py`
3. Refactor `runCombineAll.py` → `fourtop/stage4/combine.py`

### Verification
- Datacards text-identical
- Combine limits within 0.1%

---

## Phase 6: Job Scripts & Documentation

### Steps
1. Create `fourtop/jobs/base.py` with JobSubmitter class
2. Refactor stage 1/2/3 job makers to use base class
3. Add type hints throughout new package
4. Update CLAUDE.md with package documentation
5. Create final regression test suite

### Verification
- Full regression tests pass
- CLAUDE.md contains complete package docs

---

## Risk Mitigation

| Risk | Mitigation |
|------|------------|
| Silent physics change | Golden reference tests after each phase |
| Import cycles | Careful dependency ordering |
| Breaking scripts | Keep wrappers in original locations |
| ROOT compatibility | Test in CMSSW environment |
