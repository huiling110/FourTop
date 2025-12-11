# Tasks: Workflow Optimization V2

**Created**: 2025-12-11
**Last Updated**: 2025-12-11
**Status**: IN PROGRESS

---

## Part A: Fix Bash Permissions ⚡ IMMEDIATE PRIORITY

- [ ] Backup current settings files
  - `cp .claude/settings.json .claude/settings.json.backup-20251211`
  - `mv .claude/settings.local.json .claude/settings.local.json.backup`
- [ ] Simplify .claude/settings.json
  - Keep all deny rules (lines 3-45)
  - Replace allow section with: `Bash(*)`, `Edit(*)`, `Write(*)`, `Read(*)`, `Glob(**)`, `Grep(**)`
  - Keep hooks section unchanged
- [ ] Create empty settings.local.json: `echo '{}' > .claude/settings.local.json`
- [ ] Test with common commands
  - `ls | grep`, `find . -name`, `python3 script.py && echo done`
  - Verify zero prompts
- [ ] Commit changes

**Success**: Zero permission prompts for normal workflow commands

---

## Part B: Complete 1tau1l 2018 Testing

- [ ] Monitor WH systematic jobs completion
  - Check: `hep_q -u $USER | grep 1tau1l`
  - Verify TES/MET/EleScale histogram files (14 variations × 59 files = 826)
- [ ] Run Stage 4.1: addJES consolidation
  - `python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018 --execute --quiet`
  - Verify all 74 systematic variations consolidated
- [ ] Run Stage 4.2: addTemplate (all systematics)
  - `python3 plotting/addTemplateNew.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018 --quiet`
- [ ] Run Stage 4.3: writeDatacard
  - `python3 plotting/writeDatacard.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018`
- [ ] Run Stage 4.4: pl.py plots
  - `python3 plotting/pl.py --config config/analysis_config_1tau1l_TTBBtest.yaml --era 2018`
- [ ] Verify outputs
  - Check datacard: `.../combine/datacardSys_v0_ttbb_nosmoothing/datacard_1tau1l.txt`
  - Check plots exist
- [ ] Commit results
- [ ] Update workflow state to mark 1tau1l 2018 complete

**Success**: 1tau1l 2018 complete with all 74 systematics, ready for production

---

## Part C: Create and Test 1tau2l 2018

- [ ] Create 1tau2l config
  - `cp config/analysis_config_1tau1l_TTBBtest.yaml config/analysis_config_1tau2l_TTBBtest.yaml`
  - Change `channel: "1tau2l"`
  - Keep all version strings same as 1tau1l
  - Set `systematics: false` for initial test
  - Commit config
- [ ] Run Stage 3 (WH nominal)
  - `source setEnv_newNew.sh`
  - `cd writeHistGood/jobs/`
  - `python3 makeJob_forWriteHist.py --config ../../config/analysis_config_1tau2l_TTBBtest.yaml --era 2018`
  - Monitor jobs: `hep_q -u $USER | grep 1tau2l`
- [ ] Run Stage 4.2: addTemplate (no systematics for test)
  - `python3 plotting/addTemplateNew.py --config config/analysis_config_1tau2l_TTBBtest.yaml --era 2018 --quiet`
- [ ] Run Stage 4.3: writeDatacard
  - `python3 plotting/writeDatacard.py --config config/analysis_config_1tau2l_TTBBtest.yaml --era 2018`
- [ ] Run Stage 4.4: pl.py plots
  - `python3 plotting/pl.py --config config/analysis_config_1tau2l_TTBBtest.yaml --era 2018`
- [ ] Verify 1tau2l-specific outputs
  - Regions: 1tau2lSR, 1tau2lCR3
  - No TTBB process in templates/datacards
- [ ] Commit results

**Success**: 1tau2l 2018 nominal workflow validated

---

## Part D: Production Runs (Multi-Year)

### D1: 1tau1l Production (4 Years)

**Eras to Complete**: 2016preVFP, 2016postVFP, 2017 (2018 done in Part B)

For each era:
- [ ] 2016preVFP:
  - [ ] Check Stage 1-2 data exists, run if needed
  - [ ] Run Stage 3.1 WH with systematics (74 variations)
  - [ ] Run Stage 4.1-4.4 full pipeline
- [ ] 2016postVFP:
  - [ ] Check Stage 1-2 data exists, run if needed
  - [ ] Run Stage 3.1 WH with systematics
  - [ ] Run Stage 4.1-4.4 full pipeline
- [ ] 2017:
  - [ ] Check Stage 1-2 data exists, run if needed
  - [ ] Run Stage 3.1 WH with systematics
  - [ ] Run Stage 4.1-4.4 full pipeline

After all 4 years complete:
- [ ] Update smooth_systematics_fourTops.py to support TTBB process
- [ ] Run smoothing: `python3 plotting/smooth_systematics_fourTops.py --config config/analysis_config_1tau1l_TTBBtest.yaml --all-eras`
- [ ] Verify runCombineAll.py supports `--combine-years`
- [ ] Combine 4 years: `cd hua/combine/ && python3 runCombineAll.py --config ../../config/analysis_config_1tau1l_TTBBtest.yaml --combine-years`
- [ ] Commit 1tau1l production complete

### D2: 1tau0l Production (4 Years)

**Eras**: 2016preVFP, 2016postVFP, 2017, 2018

Same steps as D1 for 1tau0l channel.

- [ ] 2016preVFP: Stage 1-4 with systematics
- [ ] 2016postVFP: Stage 1-4 with systematics
- [ ] 2017: Stage 1-4 with systematics
- [ ] 2018: Stage 1-4 with systematics
- [ ] Smoothing (all 4 years)
- [ ] Year combination
- [ ] Commit 1tau0l production complete

### D3: 1tau2l Production (4 Years, Stage 3 Onwards)

**Eras to Complete**: 2016preVFP, 2016postVFP, 2017 (2018 done in Part C)

**QUESTION**: Run with systematics or nominal only? (need user clarification)

For each era:
- [ ] 2016preVFP: Stage 3 WH + Stage 4 pipeline
- [ ] 2016postVFP: Stage 3 WH + Stage 4 pipeline
- [ ] 2017: Stage 3 WH + Stage 4 pipeline

After all 4 years:
- [ ] Smoothing? (TBD - check if needed for 1tau2l)
- [ ] Year combination
- [ ] Commit 1tau2l production complete

---

## Part E: V21 Combination (3 Channels)

**Prerequisites**: All channels complete for all years with smoothing and per-channel combinations

- [ ] Verify all per-channel year combinations exist
  - 1tau1l Run2 combined datacard
  - 1tau0l Run2 combined datacard
  - 1tau2l Run2 combined datacard
- [ ] Verify runCombineAll.py supports `--combine-channels`
  - If not, write wrapper script
- [ ] Run 3-channel combination
  - `cd hua/combine/`
  - `python3 runCombineAll.py --combine-channels --channels 1tau1l,1tau0l,1tau2l --version V21`
- [ ] Generate final results
  - Significance
  - Limits
  - Postfit plots
  - Impacts for key systematics
- [ ] Validate results
- [ ] Commit V21 final results

**Success**: V21 3-channel combination complete with final physics results

---

## Part F: Dev-Docs Maintenance

- [x] Create dev-docs structure
- [x] Create plan.md
- [x] Create context.md
- [x] Create tasks.md (this file)
- [ ] Update tasks.md as work progresses
- [ ] Update .workflow_state.json for each major step
- [ ] Link to workflow-optimization parent task
- [ ] Final summary when V21 complete

---

## Progress Tracking

**Parts Complete**: 0/6 (A-F)
**Current Focus**: Part A (Bash permissions)

**1tau1l 2018**: Stage 3.1 running → Stage 4.1-4.4 pending
**1tau2l 2018**: Config creation pending

**Estimated Completion**: ~3-4 weeks from start

---

**Last Updated**: 2025-12-11
