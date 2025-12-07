# Tasks: [Task Name]

**Created**: YYYY-MM-DD HH:MM
**Last Updated**: YYYY-MM-DD HH:MM
**Status**: X / Y tasks completed

---

## Task List

### Phase 1: Preparation
- [ ] **Task 1.1**: Locate VLL_M850 NanoAOD files on /publicfs
  - Check all eras: 2016preVFP, 2016postVFP, 2017, 2018
  - Verify file integrity (no corrupted files)
  - Note: See context.md for expected event counts

- [ ] **Task 1.2**: Add file paths to inputFiles/ configuration
  - Update: `inputFiles/inputList_2018.txt` (and other eras)
  - Format: one file per line with full path

- [ ] **Task 1.3**: Update process list in run_treeAnalyzer.C
  - Location: `writeHistGood/apps/run_treeAnalyzer.C:45`
  - Add: VLL_M850 to signal processes

### Phase 2: Job Submission
- [ ] **Task 2.1**: Configure nominal job submission
  - Edit: `writeHistGood/jobs/makeJob_forWriteHist.py`
  - Set: channel='1tau1l', version='v8BDT1tau1lV19_refactorAndBtagNameFix'
  - Set: ifSys=1 (include weight systematics)

- [ ] **Task 2.2**: Submit nominal jobs (all eras)
  - [ ] 2016preVFP
  - [ ] 2016postVFP
  - [ ] 2017
  - [ ] 2018

- [ ] **Task 2.3**: Configure systematic variation jobs
  - Edit: `writeHistGood/run_makeJos_WH_forJES.sh`
  - Set parameters for JES, JER, TES, MET variations

- [ ] **Task 2.4**: Submit systematic jobs (all eras)
  - [ ] 2016preVFP
  - [ ] 2016postVFP
  - [ ] 2017
  - [ ] 2018

### Phase 3: Validation
- [ ] **Task 3.1**: Check job completion status
  - Run: `checkJobResult.py | grep VLL_M850`
  - Resubmit any failed jobs

- [ ] **Task 3.2**: Validate event counts
  - Compare: Output histograms vs DAS query
  - Expected: ~44k total events across Run2

- [ ] **Task 3.3**: Check histogram distributions
  - Plot: BDT score, key kinematic variables
  - Verify: Shapes reasonable, no unexpected spikes

- [ ] **Task 3.4**: Validate systematic variations
  - Check: All systematics present in output
  - Verify: Variations are sensible (±X% expected)

### Phase 4: Combine Integration
- [ ] **Task 4.1**: Create datacards for VLL_M850
  - Run: `plotting/writeDatacard.py` for each era
  - Output: `datacard_1tau1l_VLL_M850.txt`

- [ ] **Task 4.2**: Combine Run2 eras
  - Use: `hua/combine/writeCombinationDatacard.py`
  - Output: Combined Run2 datacard

- [ ] **Task 4.3**: Run Combine statistical analysis
  - Expected limits
  - Observed limits (if unblinded)
  - Significance

- [ ] **Task 4.4**: Generate post-fit plots
  - Signal vs background stacks
  - Pull distributions
  - Impact plots

### Phase 5: Documentation & Wrap-up
- [ ] **Task 5.1**: Update ANALYSIS_WORKFLOW.md
  - Document: Commands used, parameters, output locations

- [ ] **Task 5.2**: Update CLAUDE.md current work section
  - Mark: VLL_M850 integration as complete

- [ ] **Task 5.3**: Commit changes
  - Commit: Updated input lists, datacard scripts
  - Message: "feat: Add VLL_M850 signal to 1tau1l analysis"

- [ ] **Task 5.4**: Generate summary plots for presentation
  - Limits vs mass (including M850)
  - Significance vs mass

---

## Blockers / Issues

[Track anything blocking progress]

Example:
- **Blocker 1**: Waiting for VLL_M850 samples to finish NanoAOD production
  - Status: Expected 2025-12-01
  - Impact: Cannot start Phase 1 until resolved

---

## Notes

[Quick notes, reminders, things to follow up on]

Example:
- Remember to source environment before running scripts
- Cross-check M850 cross-section with theory team
- Consider re-running M800 with same BDT for fair comparison

---

## Completed Tasks Archive

[Optional: Move completed tasks here to keep main list clean]

---

*Mark tasks as [x] when completed. Update daily or before context compaction.*
