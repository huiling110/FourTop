# Tasks: XGB080test Workflow

## Status Summary
| Era | S1 OS | S1.1 OS sys | S2 MV | S2.1 MV sys | S2.4 Fake | S3 WH | S3.1 WH sys | S4 |
|-----|-------|-------------|-------|-------------|-----------|-------|-------------|-----|
| 2018 | DONE | ARCHIVED | DONE | DONE (75) | DONE | DONE | MERGED | DONE |
| 2017 | DONE | ARCHIVED (15) | DONE | DONE (75) | PENDING | - | - | - |
| 2016preVFP | DONE | DONE (15) | DONE | JES SUBMIT | - | - | - | - |
| 2016postVFP | DONE | DONE (15) | DONE | JES SUBMIT | - | - | - | - |

## Current Phase: 2016 JES MV + 2017 Fakes

### Session Dec 30 - 2016 JES MV Submission + Skill Enforcement

**Skill Enforcement Improvement:**
- Added path blocking in `pre-tool-use.sh` for stage path checks
- Hook warns if skill not invoked within 30 mins (marker file system)
- Updated CLAUDE.md with "Forced Eval" 3-step protocol
- Added workflow skills to settings.json auto-allow list

**2016 MV JES Submission:**
- [x] Verified 2016preVFP: 15/75 variations done (non-JES complete)
- [x] Verified 2016postVFP: 15/75 variations done (non-JES complete)
- [ ] Submitting 2016preVFP JES (60 variations) - IN PROGRESS
- [ ] Submitting 2016postVFP JES (60 variations) - IN PROGRESS

**2017 Status:**
- [x] MV complete: 75/75 variations (all nominal + systematics)
- [ ] Stage 2.4 fakes pending

**TTBB Investigation:**
- TTBB in TES (59 files) but not in JER/MET/EleScale (56 files) - EXPECTED
- TES affects TTBB physics, JER/MET/EleScale don't significantly impact it
- Different systematics affect different samples - correct behavior

### Session Dec 29 - 2017 Completion + 2016 Systematics

**2018 Status (Complete):**
- [x] All stages through Stage 4 complete
- [x] WH systematics run, merged via addJES, cleaned up
- [x] OS systematics archived (15 tar.gz files)

**2017 Progress:**
- [x] OS nominal complete (59 processes)
- [x] OS systematics complete (15 variations, 59 processes each)
- [x] MV nominal complete (68 files)
- [x] MV systematics: TES×8, JER×2, MET×2, EleScale×2 complete
- [x] MV JES: Resubmitted 15 missing variations (was 45/60) - RUNNING
- [ ] OS systematics archiving in progress (2/15) (`screen -r archive_2017`)
- [ ] Run fakes (createFaketauTree, createFakeLeptonTree)
- [ ] Run WH with `--systematic complete`

**2016 Progress:**
- [x] 2016preVFP TES OS systematics submitted (8 variations)
- [x] 2016postVFP TES OS systematics submitted (8 variations)
- [ ] Unzip v94 archives for JES/JER/MET/EleScale → v95 (waiting for 2017 archive to free file quota)

**Strategy for 2016 OS systematics:**
- TES: Submit new jobs (TES corrections changed between v94/v95)
- JES/JER/MET/EleScale: Reuse v94 by unzipping and renaming to v95 (no changes needed)
- Source: `/publicfs/.../UL2016_preVFP/v94HadroPreJetVetoHemOnly_*.zip` (with underscore)
- Target: `/publicfs/.../UL2016preVFP/v95XGB080testOS7_*/` (no underscore)

**Code Improvements:**
- [x] Added ROOT validation to verify_mv_completion.py (`--validate` flag)
- [x] Updated stage2-mv skill with validation docs
- [x] Updated misc skill: verify MV before archiving OS

### Session Dec 26 - Hook Improvements + Archiving

**2018 OS Systematics Archiving:**
- [x] All 15 archives complete

**2017 OS Systematics:**
- [x] All 15 variations complete

**Claude Code Improvements:**
- [x] Hook now injects skill content (not just hints)
- [x] Fixed archive_and_cleanup.sh bug (find -type d)
- [x] Created misc skill for archive script
- [x] Updated CLAUDE.md with Option C rules (proactive skill reading)

### Earlier Dec 26 - Stage 4 Workflow

**Verified complete for 2018:**
- [x] Stage 1 OS nominal (68 samples)
- [x] Stage 1.1 OS systematics (15 variations)
- [x] Stage 2 MV nominal (71 files)
- [x] Stage 2.1 MV systematics (74 variations: TES×8, JER×2, MET×2, EleScale×2, JES×60)
- [x] Stage 2.4 Fake backgrounds (fakeTau_data, fakeTau_MC, fakeLepton)
- [x] Stage 3 WH nominal (71 histogram files)

**Needs Verification:**
- [ ] Stage 3.1 WH systematics - check with correct path structure

**Pending (Stage 4 workflow):**
- [ ] Stage 4.1 addJES - merge JES/JER/TES/MET/EES templates
- [ ] Stage 4.2 addTemplate
- [ ] Stage 4.3 smooth_systematics (if smoothing: true)
- [ ] Stage 4.4 writeDatacard
- [ ] Stage 4.5 combine fits (workspace, significance, limits)
- [ ] Stage 4.7 pl.py (plots)

### Code Fixes (Dec 26)
- [x] **Fixed makeJob_forWriteHist.py** - now reads `ifVLL` from YAML config
- [x] **Updated hook** - injects full skill content on stage keywords
- [x] **Updated CLAUDE.md** - Option C: explicit rules to read skills proactively
- [x] **Fixed archive_and_cleanup.sh** - use `find -type d` not `ls -d`
- [x] **Created misc skill** - `.claude/skills/misc/SKILL.md`

### Previous Sessions (Dec 24)

#### Completed
- [x] Verify 2018 Stage 1 OS nominal complete
- [x] Submit 2017, 2016preVFP, 2016postVFP Stage 1 OS nominal
- [x] Fix library mismatch - dual-environment myLibrary (OS7 + Linux9)
- [x] Create resubmit_held.sh for memory-held jobs
- [x] Restructure workflow skills into 4 auto-discoverable stage skills

#### Issues Fixed
- Library mismatch: `GLIBCXX_3.4.32 not found` - dual-library setup
- 2016postVFP jetHT_2016H memory issues - resubmit with 12GB
- Ghost jobs - verified outputs, removed with hep_rm

## Key Commands

```bash
# Stage 3.1 WH systematics
python3 writeHistGood/jobs/makeJob_WH.py --config config/analysis_config_1tau1l_XGB080test.yaml --era 2018 --systematic all

# Stage 4.1 addJES (after WH sys complete)
python3 plotting/addJESTemplatesToHistFile.py --config config/analysis_config_1tau1l_XGB080test.yaml --era 2018 --execute --quiet

# Stage 4.7 pl.py
python3 plotting/pl.py --config config/analysis_config_1tau1l_XGB080test.yaml --era 2018 --unblind
```

## Last Updated
2025-12-30 09:50
