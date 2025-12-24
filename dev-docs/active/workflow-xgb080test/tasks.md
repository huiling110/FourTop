# Tasks: XGB080test Workflow

## Status Summary
| Era | S1 OS | S1.1 OS sys | S2 MV | S2.1 MV sys | S2.4 Fake | S3 WH | S4 |
|-----|-------|-------------|-------|-------------|-----------|-------|-----|
| 2018 | DONE | RUNNING | DONE | PENDING | DONE | Nominal | - |
| 2017 | DONE | PENDING | - | - | - | - | - |
| 2016preVFP | DONE | PENDING | - | - | - | - | - |
| 2016postVFP | RUNNING | - | - | - | - | - | - |

## Current Phase: Stage 1.1 OS Systematics (2018) + Stage 1 Nominal (2016postVFP)

### Completed
- [x] Verify 2018 Stage 1 OS nominal complete
- [x] Submit 2017, 2016preVFP, 2016postVFP Stage 1 OS nominal
- [x] Fix CLAUDE.md Stage 2.4 location and timestamp
- [x] Create hooks README.md
- [x] Update pre-tool-use.sh patterns
- [x] Update stage1-os.md skill (CentOS7 default, job duration, verification)
- [x] **Fix library mismatch** - created dual-environment myLibrary (OS7 + Linux9)
- [x] Add --confirm safety to archive_and_cleanup.sh
- [x] **Make stage1-os.md concise** (179 → ~60 lines)
- [x] **Create resubmit_held.sh** for memory-held jobs
- [x] **Fix resubmit_held.sh** - now uses `grep " H "` from hep_q output
- [x] **Remove ghost jobs** (2017 WJets, 2016preVFP TTZ completed but stuck in queue)
- [x] **2017 Stage 1 OS nominal** - all outputs verified
- [x] **2016preVFP Stage 1 OS nominal** - all outputs verified
- [x] **Submit 2018 OS systematics** (15 variations)
- [x] **Restructure workflow skills** - Split into 4 auto-discoverable stage skills

### Issues Fixed

#### Library Mismatch
- First OS job submissions failed with `GLIBCXX_3.4.32 not found`
- Root cause: `libcommenFunction.so` was recompiled for Linux9 on Dec 22
- Solution: Dual-library setup in myLibrary/

#### 2016postVFP jetHT_2016H Memory Issues
- jetHT_2016H jobs repeatedly held due to memory limits
- Jobs need ~8GB but default allocation insufficient
- Solution: `resubmit_held.sh` script to resubmit with higher memory (12GB)

#### Ghost Jobs
- 2017 WJets and 2016preVFP TTZ jobs showed "running" for 4+ hours
- Output files existed, jobs actually completed
- Condor didn't properly mark them as done
- Solution: Verified outputs exist, removed ghost jobs with `hep_rm`

### In Progress
- [ ] **2016postVFP jetHT_2016H** - 10 jobs with 12GB memory
- [ ] **2018 OS systematics** - 35156 jobs submitted (15 variations)

### Pending
- [ ] Submit Stage 1.1 OS systematics for 2017, 2016preVFP, 2016postVFP
- [ ] Submit Stage 2 MV nominal for all 4 eras
- [ ] Submit Stage 2.1 MV systematics for all 4 eras
- [ ] Run Stage 2.4 fake backgrounds for all 4 eras
- [ ] Submit Stage 3 WH with --systematic complete for all 4 eras
- [ ] Run Stage 4 pipeline

## Job Status (as of 11:20 Dec 24)
| Type | Running | Idle | Held | Total |
|------|---------|------|------|-------|
| 2016postVFP jetHT | 1 | 0 | 9 | 10 |
| 2018 Systematics | 0 | 0 | 0 | 0 (completed?) |
| **Total** | 1 | 0 | 9 | 10 |

**Note**: 2018 systematics jobs no longer in queue - need to verify completion.

## Key Scripts
- `objectSelectionOptimized/jobs/resubmit_held.sh` - Resubmit held jobs with higher memory
  - Usage: `./resubmit_held.sh 12000` (12GB)
  - Default: 10GB

## Code Improvements (Dec 24)
- **Workflow skills restructured** for auto-discovery:
  - `.claude/skills/workflow-stage1-os/SKILL.md`
  - `.claude/skills/workflow-stage2-mv/SKILL.md`
  - `.claude/skills/workflow-stage3-wh/SKILL.md`
  - `.claude/skills/workflow-stage4-combine/SKILL.md`
- Each skill has focused keywords in description for Claude to auto-discover

## Last Updated
2025-12-24 11:20
