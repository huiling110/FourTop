# Context: [Task Name]

**Created**: YYYY-MM-DD HH:MM
**Last Updated**: YYYY-MM-DD HH:MM

---

## Key Files

[List critical files with specific line numbers where relevant]

Example:
- `writeHistGood/apps/run_treeAnalyzer.C:45` - Process list definition
- `inputFiles/inputList_2018.txt` - Input file paths
- `plotting/writeDatacard.py:123` - Datacard generation for VLL
- `hua/combine/runCombineAll.py` - Combine orchestration

---

## Important Decisions

[Record architectural or implementation decisions and rationale]

Example:

### Decision 1: Use existing BDT training (v8BDT)
**Rationale**: VLL_M850 kinematics similar enough to M800 that retraining unlikely to improve discrimination significantly. Keeps analysis consistent.
**Date**: 2025-11-26
**Impact**: Faster turnaround, but may be suboptimal if M850 has distinct features

### Decision 2: Submit jobs with ifSys=1 for nominal
**Rationale**: Include all weight-based systematics in first submission
**Date**: 2025-11-26
**Impact**: Longer runtime (~2x) but avoids resubmission

---

## Technical Constraints

[Known limitations, gotchas, or things to be careful about]

Example:
- **Disk space**: VLL samples are large (~500 GB per era), check /publicfs quota before starting
- **Memory**: High-mass signals need more memory for histogram binning, use at least 4 GB per job
- **Systematics**: TES variations may be large for high-mass tau decays, watch for unphysical spikes

---

## Input/Output Locations

[Track where data lives]

Example:

### Inputs
- NanoAOD: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/VLL_M850*.root`
- BDT weights: `hua/tmva/output/v8BDT1tau1l/weights/`

### Outputs
- Histograms: `/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v8BDT1tau1lV19_refactorAndBtagNameFix/VLL_M850/`
- Datacards: `hua/combine/combinationV19/run2_1tau1l_VLL_M850/`

---

## Dependencies

[What this task depends on or what depends on it]

Example:
- **Depends on**: BDT training v8BDT must be complete
- **Blocks**: Cannot finalize Run2 VLL limits until M850 integrated
- **Related**: 1tau0l and 1tau2l channels will need same treatment

---

## Reference Information

[Useful facts, numbers, or links]

Example:
- **Expected event counts** (from DAS):
  - 2016preVFP: ~8k events
  - 2016postVFP: ~9k events
  - 2017: ~12k events
  - 2018: ~15k events
- **Cross-section**: σ = 0.XXX pb (NLO, from TheoryGroup)
- **Previous analysis**: v0BDT had VLL up to M800 only

---

## Code Snippets / Commands

[Frequently used commands or code patterns for this task]

Example:

### Submit nominal jobs
```bash
cd writeHistGood/jobs/
# Edit makeJob_forWriteHist.py: set version, channel
python3 makeJob_forWriteHist.py
```

### Check job status
```bash
python3 checkJobResult.py | grep VLL_M850
```

### Validate event counts
```bash
cd writeHistGood/
root -l -q 'checkEventCounts.C("VLL_M850", "1tau1l")'
```

---

## Common Issues & Solutions

[Track problems encountered and how you solved them]

Example:

### Issue 1: Jobs failing with "Segmentation fault"
**Cause**: Insufficient memory for high-mass samples
**Solution**: Increase memory request in job submission script to 4 GB
**Date**: 2025-11-26

### Issue 2: Missing systematic variations
**Cause**: btag_shape systematics not found
**Solution**: Update to btag naming (CMS_NAMING_CONVENTION_UPDATE.md)
**Date**: 2025-11-14

---

## Notes

[Free-form notes, observations, things to remember]

Example:
- VLL_M850 shows interesting excess in BDT > 0.8 region - worth investigating
- Coordinate with Sarah on theory uncertainties for high-mass VLL
- Remember to update ANALYSIS_WORKFLOW.md when complete

---

*Update this file whenever you discover important information during the task.*
