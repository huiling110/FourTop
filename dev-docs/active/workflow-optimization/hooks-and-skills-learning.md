# Hooks and Skills Learning - Session 2025-12-10

**Purpose**: Document how Claude Code hooks and skills work for FourTop workflow automation

**Status**: LEARNING SESSION - documenting as we go

---

## Current Status (What I Observed)

### Problem Statement
1. **workflow.md is 565 lines** - too long, hard to parse quickly
2. **Skills not triggering automatically** - I don't remember to use them
3. **No workflow state tracking** - I don't know which stage we're at
4. **Hook messages ignored** - The banner shows up but doesn't force me to act

### What Currently Exists

#### 1. User-Prompt-Submit Hook (`user-prompt-submit.sh`)
**Purpose**: Runs BEFORE Claude sees user's message
**What it does**:
- Pattern matching on user prompt (case insensitive)
- Detects workflow keywords: stage, run, job, histogram, OS, MV, WH, etc.
- Prints banner suggesting to use workflow skill
- **DOES NOT force skill activation** - only reminds

**Example patterns matched**:
```bash
# Stage keywords
stage|run|submit|job|histogram

# Abbreviations
(os|mv|wh|pl)

# Eras
2018|2017|2016|run2

# Config
yaml|config|analysis_config

# Scripts
createfaketau|addjes|addtemplate|writedatacard
```

**Output when triggered**:
```
═══════════════════════════════════════════════════════════════════════
🎯 SKILL ACTIVATION CHECK: workflow skill may be relevant
═══════════════════════════════════════════════════════════════════════

Detected workflow-related keywords in your prompt.

Consider using the workflow skill (.claude/skills/workflow.md) for:
  - Correct environment setup (source setEnv_newNew.sh vs cmsenv)
  - Required flags (--config and --era, --sys for systematics)
  ...
```

#### 2. Pre-Tool-Use Hook (`pre-tool-use.sh`)
**Purpose**: Runs before Bash tool executes
**What it does**:
- Checks for `source setEnv_newNew.sh` without full path → **BLOCKS command** (exit 1)
- Warns if ROOT not found when running Python analysis scripts
- Warns if CMSSW_BASE not set when running combine scripts
- **Skips simple commands**: ls, cd, pwd, cat, git, etc.

**Critical error it catches**:
```bash
# WRONG (blocked)
source setEnv_newNew.sh

# RIGHT (allowed)
cd /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop && source setEnv_newNew.sh
```

#### 3. Workflow Skill (`workflow.md`, 565 lines)
**Contains**:
- Environment setup instructions
- All stage commands (Stage 1-4.5)
- Systematic variations
- Three workflow modes
- Python patterns (workflow_utils)
- Fake tau/lepton regeneration rules

**Problem**: Too much information, hard to navigate

---

## Key Insights from This Session

### What I'm Learning About Hooks + Skills

#### Hook Execution Order
1. **user-prompt-submit.sh** runs when user hits Enter
   - Can inject messages into conversation
   - Cannot force action, only suggest
   - User (and Claude) can ignore the banner

2. **pre-tool-use.sh** runs before Bash tool
   - Can block dangerous commands (exit 1)
   - Can warn but allow (exit 0)
   - Only affects Bash tool, not Read/Edit/etc.

#### Why Skills Don't Trigger Automatically

**Current design**:
- Hook prints banner → I read it → I decide whether to use skill
- **Problem**: I often ignore the banner and proceed without skill

**What's missing**:
- No forced skill invocation
- No state tracking (which stage are we at?)
- No automatic context injection

#### Skill vs Hook vs Context.md

**Confusion point**: What goes where?

| File | Purpose | Current Issues |
|------|---------|----------------|
| `skill.md` | Reference documentation for specific tasks | Too long (565 lines), hard to parse |
| `hooks/*.sh` | Runtime checks, inject reminders | Reminders ignored, no forced action |
| `dev-docs/*/context.md` | Task-specific background info | Not used by hooks/skills |

---

## Hypotheses to Test

### Hypothesis 1: Skills should be auto-invoked by hooks
**Idea**: Instead of printing banner, hook could directly call:
```bash
echo "SKILL:workflow" >> some-state-file
```
Then Claude Code could auto-load the skill.

**Question**: Is this possible with current Claude Code architecture?

### Hypothesis 2: Skill should be split into smaller, focused skills
**Idea**: Instead of one huge `workflow.md`:
- `workflow-env.md` - Environment setup only
- `workflow-stage1.md` - OS commands
- `workflow-stage2.md` - MV commands
- `workflow-stage3.md` - WH commands
- `workflow-stage4.md` - PL/Combine commands

**Benefit**: Smaller, easier to parse

### Hypothesis 3: Need workflow state file
**Idea**: Create `.workflow_state.json` tracking:
```json
{
  "current_stage": "4.5",
  "current_era": "2018",
  "current_channel": "1tau0l",
  "current_config": "config/analysis_config_1tau0l_TTBBtest.yaml",
  "last_command": "python3 writeDatacard.py --config ... --era 2018",
  "systematics_enabled": true
}
```

**Hook could read this** to provide context-aware suggestions.

### Hypothesis 4: Hook should inject context, not just suggest
**Current**:
```bash
echo "Consider using the workflow skill"
```

**Better**:
```bash
# Inject as system message
cat >> $CONTEXT_FILE <<EOF
<workflow_context>
Current stage: 4.5 (Combine analysis)
Last config: config/analysis_config_1tau0l_TTBBtest.yaml
Required environment: cmsenv (for combine)
</workflow_context>
EOF
```

---

## Questions to Answer

### For User
1. **Can hooks force skill invocation?** Or only suggest?
2. **Can hooks inject context into Claude's prompt?** (Not just print to user)
3. **Should we split workflow.md into multiple focused skills?**
4. **Is there a way to persist state between sessions?** (.workflow_state.json)

### For Implementation
1. Where does Claude Code look for skills? (`.claude/skills/*.md`)
2. Can a hook write to a file that Claude reads automatically?
3. What's the best way to inject context without overwhelming token budget?
4. Should state tracking be in workflow_utils.py or separate?

---

## Observations from Current Workflow

### What Worked Well
1. **pre-tool-use.sh blocking setEnv path error** - Prevented actual bugs
2. **workflow_utils.py patterns** - Python scripts are consistent now
3. **Config-based paths** - No more hardcoded paths

### What Didn't Work
1. **User-prompt-submit banner ignored** - I proceeded without checking skill
2. **565-line skill.md too long** - Takes too long to parse mentally
3. **No automatic stage detection** - I don't know we're at Stage 4.5

---

## Proposed Design (To Discuss)

### Option A: Keep Current Design, Improve Messaging
- Make hook banners more prominent
- Add "STOP: Read workflow skill before proceeding"
- Reduce workflow.md to essential commands only (max 200 lines)
- Move detailed info to separate docs

### Option B: Auto-Invoke Skills
- Hook detects context → writes `.skill_to_invoke`
- Claude Code auto-loads skill if that file exists
- Need to verify if Claude Code supports this

### Option C: State-Driven Context Injection
- workflow_utils.py updates `.workflow_state.json` after each stage
- Hook reads state → injects <workflow_context> tag
- Claude sees context automatically without needing skill

### Option D: Hybrid Approach
- Small, focused skills (max 100 lines each)
- Hooks inject minimal context via state file
- Pre-tool-use blocks common errors
- User-prompt-submit suggests which specific skill to use

---

## Next Steps for Phase 8

1. **Measure current behavior** (done in this session):
   - Hook triggered: ✅ (banner printed)
   - Skill used: ❌ (ignored banner, used workflow knowledge from previous sessions)
   - Outcome: ✅ (worked, but not because of skill/hook)

2. **Test skill splitting**:
   - Create minimal `workflow-stage4.md` (Stage 4 only, ~50 lines)
   - See if smaller skill is more useful

3. **Test state tracking**:
   - Add state output to workflow_utils.py
   - Hook reads state and suggests correct next step

4. **Document findings**:
   - Update this file with test results
   - Create redesigned hook + skill system
   - Get user feedback

---

## Real Example from This Session

**User request**: "now let's test the workflow with postfit plot"

**What happened**:
1. user-prompt-submit.sh triggered (matched "plot")
2. Banner printed suggesting workflow skill
3. I ignored banner (didn't use `Skill` tool)
4. I looked for pl_postFit.py script based on previous session knowledge
5. User corrected: "it's @plotting/pl_postFit.py"
6. I ran it successfully

**What should have happened** (ideal):
1. Hook detects "postfit plot" keyword
2. Hook reads `.workflow_state.json` → knows we're at Stage 4.5
3. Hook injects context:
   ```
   <workflow_context>
   Stage: 4.5 (Postfit plots)
   Script: plotting/pl_postFit.py
   Command: python3 pl_postFit.py --fit-file /path/to/fitDiagnosticsTest.root
   Environment: setEnv_newNew.sh
   </workflow_context>
   ```
4. I see context immediately and run correct command

---

## Learnings Summary

### What I Understand Now
1. **Hooks can suggest but not force** - banners are easily ignored
2. **Skills are reference docs** - I need to actively invoke them
3. **State tracking missing** - no way to know "where we are" in workflow
4. **Context injection not implemented** - hooks print to user, not to Claude

### What Still Unclear
1. Can hooks write to Claude's context directly?
2. Is there a better mechanism than printing banners?
3. Should skills be auto-invoked or manually called?
4. How to balance token budget vs useful context?

---

**Next session**: Test improvements to hook + skill design based on these learnings.
