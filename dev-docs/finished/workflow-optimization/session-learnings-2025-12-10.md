# Session Learnings - 2025-12-10

**Session Focus**: Testing hooks/skills triggering + long-running task workflow patterns

---

## Test Case 1: OS Systematic Job Submission for 2017

### User Prompt
```
"let's first submit OS jobs for 2017 with systematic variation(see? this prompt should automatic trigger our workflow skills so you immediatly remembers how to run this and what's the next steps)"
```

### What Should Have Happened (Ideal)
1. **Hook triggered**: user-prompt-submit.sh detects "submit OS jobs", "2017", "systematic"
2. **Skill auto-invoked**: Workflow skill loaded automatically
3. **Context provided**:
   - Current stage: Stage 1.1 (OS systematics)
   - Script: `objectSelectionOptimized/jobs/submit_all_systematics.sh`
   - Command: `bash submit_all_systematics.sh CONFIG ERA`
   - Expected: 15 systematic variations
   - Runtime: 2-3 hours for jobs to complete
4. **Next steps shown**:
   - Monitor: `hep_q -u $USER | grep OS_`
   - Wait for completion
   - Then: Stage 2.1 (MV systematics)

### What Actually Happened
1. ✅ Hook likely triggered (banner printed, but not shown in conversation)
2. ❌ I did NOT invoke Skill tool
3. ❌ I had to recall workflow from memory
4. ❌ Made initial error: `python3 submit_all_systematics.sh` (wrong interpreter)
5. ✅ Corrected to: `bash submit_all_systematics.sh CONFIG ERA`
6. ⚠️ Job submission running in background (takes long time)

### Problems Identified
1. **Skill not triggered automatically** - I ignored/didn't see the hook banner
2. **No workflow state tracking** - System doesn't know we just finished 2018 OS systematics
3. **No command template** - I had to remember the exact syntax
4. **Long-running task pattern missing** - No guidance on what to do while waiting

### User's Key Observation
> "see? this prompt should automatic trigger our workflow skills so you immediatly remembers how to run this and what's the next steps"

**This is exactly the problem Phase 8 should solve!**

---

## Long-Running Task Workflow Pattern (Real Example)

### Current Situation
- **Task**: Submit OS systematic jobs for 2017
- **Script**: `objectSelectionOptimized/jobs/submit_all_systematics.sh`
- **Systematics**: 15 variations (JES, JER, MET, EleScale, TES dm0/dm1/dm10/dm11)
- **Expected runtime**: 2-3 hours for jobs to complete
- **Status**: Running in background (bash_id: 52c8bb)

### What Happens Now (Traditional Workflow)
1. User says "submit OS jobs for 2017"
2. I submit jobs → script takes long to run
3. I wait... or user interrupts
4. 2-3 hours later, jobs complete
5. User comes back: "what's next?"
6. **Problem**: No memory of where we were, must re-explain context

### What SHOULD Happen (Improved Workflow)

#### Before Submission
```
<workflow_state>
Current: Stage 1.0 completed for 2017 (nominal)
Next: Stage 1.1 (systematic variations)
Command: bash submit_all_systematics.sh CONFIG 2017
Expected: 15 job clusters, 2-3 hours runtime
After: Stage 2.1 (MV systematics)
</workflow_state>
```

#### During Submission (Monitoring)
```
Submitted 15 systematic variations for 2017

Monitor progress:
  hep_q -u $USER | grep OS_
  bash check_systematic_jobs.sh 2017

Expected output:
  /publicfs/.../2017/v1baselineHadro_.../OS_*/*.root

When complete, next step:
  Stage 2.1: bash makeJob_MV_JESVariation.py --config CONFIG --era 2017 --group all
```

#### After Completion (Resume Point)
```
<workflow_state>
Completed: Stage 1.1 (OS systematics) for 2017
Files: 15 systematic variations × N samples
Next: Stage 2.1 (MV systematics for 2017)
Command: python3 makeJob_MV_JESVariation.py --config CONFIG --era 2017 --group all
</workflow_state>
```

### State Tracking Proposal

Create `.workflow_state.json`:
```json
{
  "current_task": "OS systematics 2017",
  "stage": "1.1",
  "era": "2017",
  "channel": "1tau0l",
  "config": "config/analysis_config_1tau0l_TTBBtest.yaml",
  "systematics_enabled": true,
  "last_command": "bash submit_all_systematics.sh CONFIG 2017",
  "last_timestamp": "2025-12-10T02:59:00Z",
  "status": "running",
  "expected_completion": "2025-12-10T05:00:00Z",
  "jobs_submitted": 15,
  "next_step": {
    "stage": "2.1",
    "description": "MV systematics for 2017",
    "command": "python3 makeJob_MV_JESVariation.py --config CONFIG --era 2017 --group all"
  },
  "completed_eras": {
    "2018": {
      "stage_1": "complete",
      "stage_1.1": "complete",
      "stage_2": "complete",
      "stage_2.1": "complete",
      "stage_3": "complete",
      "stage_3.1": "complete",
      "stage_4": "complete"
    },
    "2017": {
      "stage_1": "complete",
      "stage_1.1": "running"
    }
  }
}
```

---

## Hook Redesign Insights

### Current Hook Behavior (user-prompt-submit.sh)
```bash
if [[ "$prompt_lower" =~ (stage|run|submit|job) ]]; then
    echo "🎯 SKILL ACTIVATION CHECK: workflow skill may be relevant"
    echo "Consider using the workflow skill..."
fi
```

**Problem**: Prints banner → I can ignore it

### Improved Hook Behavior (Proposal)
```bash
if [[ "$prompt_lower" =~ (stage|run|submit|job) ]]; then
    # Read current workflow state
    STATE=$(cat .workflow_state.json 2>/dev/null || echo "{}")
    CURRENT_STAGE=$(echo "$STATE" | jq -r '.stage // "unknown"')
    NEXT_COMMAND=$(echo "$STATE" | jq -r '.next_step.command // "unknown"')

    # Inject context into Claude's prompt
    cat <<EOF

<workflow_context>
Current Stage: $CURRENT_STAGE
Last Command: $(echo "$STATE" | jq -r '.last_command')
Next Step: $(echo "$STATE" | jq -r '.next_step.description')
Command: $NEXT_COMMAND

Workflow Skill: .claude/skills/workflow-stage${CURRENT_STAGE%%.*}.md
</workflow_context>

EOF
fi
```

**Benefit**: Context automatically injected, not just suggested

---

## Action Items for Phase 8

### Immediate (This Session)
- [x] Document this real example of skill NOT triggering
- [x] Document the 2-3 hour waiting pattern
- [ ] Monitor OS job submission completion
- [ ] Update hooks-and-skills-learning.md with this example

### Short-term (Next Session)
- [ ] Implement `.workflow_state.json` tracking
- [ ] Update workflow_utils.py to write state after each stage
- [ ] Test improved hook that reads state and injects context
- [ ] Split workflow.md into stage-specific skills (max 100 lines each)

### Long-term
- [ ] Add `--wait` flag to all job submission scripts
- [ ] Implement automatic progression (submit jobs → wait → next stage)
- [ ] Add resume capability for long workflows

---

## Key Quote from User

> "this prompt should automatic trigger our workflow skills so you immediatly remembers how to run this and what's the next steps"

**This is the core requirement for Phase 8 success.**

Current state: ❌ Failed to auto-trigger
Target state: ✅ Auto-inject context with exact next command

---

## Real-Time Learning: While Jobs Run

**Current time**: 2025-12-10 ~03:00 UTC
**Expected completion**: 2025-12-10 ~05:00-06:00 UTC
**What to do now**: Document learnings, prepare for next steps

This is exactly the "long-running job" pattern from Phase 7 documentation!

### Pattern Applied: Background Job Submission with Monitoring

From long-running-jobs.md Pattern 1:
1. ✅ Calculate expected job count (15 variations)
2. ✅ Submit jobs with logging
3. ⚠️ Print monitoring commands (should have been more prominent)
4. ⏳ User waits 2-3 hours
5. ❓ What happens when user returns?

**Gap**: No persistent state for resume!
