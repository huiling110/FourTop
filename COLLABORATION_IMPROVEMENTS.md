# Collaboration Improvements for FourTop Analysis

**Based on**: "Claude Code is a Beast – Tips from 6 Months of Hardcore Use"
**Source**: https://dev.to/diet-code103/claude-code-is-a-beast-tips-from-6-months-of-hardcore-use-572n
**Created**: 2025-11-26

---

## Overview

This document outlines improvements to our Claude Code workflow based on best practices from experienced users. It focuses on making our physics analysis collaboration more efficient, reducing errors, and maintaining context across sessions.

---

## Current Strengths ✅

### What We're Already Doing Well

1. **Comprehensive Documentation**
   - CLAUDE.md provides project context
   - ANALYSIS_WORKFLOW.md tracks detailed procedures
   - Specialized docs (CMS_NAMING_CONVENTION_UPDATE.md, BUILD_INSTRUCTIONS.md)

2. **Systematic Validation**
   - Physics result validation after code changes
   - Bit-for-bit comparison of outputs
   - End-to-end workflow testing

3. **Version Control Discipline**
   - Regular commits for major changes
   - Clear commit messages
   - Branch strategy (addVLL for development)

4. **Environment Management**
   - Dedicated setup script (`setEnv_newNew.sh`)
   - Clear documentation of environment requirements
   - Separation of CMSSW and Combine environments

---

## Priority Improvements

### 1. Auto-Activation System for Environment Setup

**Problem**: Easy to forget sourcing `setEnv_newNew.sh` before running code

**Solution**: Implement UserPromptSubmit hook

**Implementation**:
```typescript
// .claude/hooks/userPromptSubmit.ts
export async function userPromptSubmit(prompt: string) {
  // Detect analysis execution keywords
  const analysisKeywords = [
    'run', 'execute', 'build', 'make',
    'python', 'apps/run_treeAnalyzer',
    'writeHistGood', 'plotting'
  ];

  const needsEnv = analysisKeywords.some(kw =>
    prompt.toLowerCase().includes(kw)
  );

  if (needsEnv && !prompt.includes('source setEnv')) {
    return `IMPORTANT: This task requires sourcing the environment first.
Before executing, verify environment is sourced:
- For writeHistGood/plotting: source setEnv_newNew.sh
- For hua/combine: use cmsenv

User request: ${prompt}`;
  }

  return prompt;
}
```

**Benefit**: Never run code without proper environment setup

---

### 2. Custom Slash Commands

**Purpose**: Automate common physics analysis workflows

**Recommended Commands**:

#### `/run-nominal-jobs`
```markdown
Execute nominal job submission for histogram production.

Steps:
1. Verify we're in writeHistGood/jobs/
2. Ask user for channel (1tau0l, 1tau1l, 1tau2l)
3. Ask user for version tag
4. Show current settings in makeJob_forWriteHist.py
5. Ask for confirmation before submitting
6. Execute python3 makeJob_forWriteHist.py
7. Monitor initial job status
```

#### `/run-systematic-jobs`
```markdown
Execute systematic variation job submission.

Steps:
1. Verify we're in writeHistGood/
2. Ask user for channel and version parameters
3. Show current settings in run_makeJos_WH_forJES.sh
4. Ask for confirmation
5. Execute bash run_makeJos_WH_forJES.sh
6. Note the log file location
```

#### `/validate-physics`
```markdown
Compare physics results between two analysis versions.

Steps:
1. Ask user for two version directories to compare
2. Read event counts from both
3. Compare histogram bin contents for key distributions
4. Check systematic variation counts
5. Report any differences
6. If identical, confirm validation success
```

#### `/check-environment`
```markdown
Verify analysis environment is properly configured.

Checks:
1. Current working directory
2. CMSSW_BASE variable
3. ROOT version
4. Python version
5. Whether setEnv_newNew.sh has been sourced
6. Presence of required libraries (TBB, myLibrary)
```

#### `/update-workflow-docs`
```markdown
Update ANALYSIS_WORKFLOW.md with latest progress.

Steps:
1. Read current state of ANALYSIS_WORKFLOW.md
2. Ask user what stage/step was just completed
3. Ask for commands executed, parameters used, output locations
4. Update the relevant section
5. Mark step as complete with timestamp
6. Commit changes
```

**Create these in**: `.claude/commands/`

---

### 3. Build Verification Hook

**Purpose**: Catch compilation errors immediately after C++ edits

**Implementation**:
```typescript
// .claude/hooks/onStop.ts
export async function onStop(response: string, toolCalls: ToolCall[]) {
  // Check if any C++ files in writeHistGood were edited
  const editedCppFiles = toolCalls
    .filter(tc => tc.tool === 'Edit' || tc.tool === 'Write')
    .filter(tc => {
      const path = tc.parameters.file_path;
      return path.includes('writeHistGood') &&
             (path.endsWith('.h') || path.endsWith('.C') ||
              path.endsWith('.cpp') || path.endsWith('.cc'));
    });

  if (editedCppFiles.length > 0) {
    return `
⚠️ C++ files were modified in writeHistGood/

Recommendation: Run build verification
\`\`\`bash
cd writeHistGood/
make clean && make
\`\`\`

This will catch compilation errors before they cause runtime issues.
Should I run the build now? (This is a gentle reminder, not blocking)
`;
  }

  return null;
}
```

**Benefit**: Immediate feedback on C++ changes, prevents runtime surprises

---

### 4. Physics Safety Checks Hook

**Purpose**: Remind about validation after critical changes

**Implementation**:
```typescript
// .claude/hooks/onStop.ts (add to existing)
export async function onStop(response: string, toolCalls: ToolCall[]) {
  // ... existing C++ build check ...

  // Check for changes to physics-critical files
  const criticalPatterns = [
    'writeHistGood/src/',
    'writeHistGood/include/',
    'objectSelectionOptimized/',
    'makeVariables_goodCode/'
  ];

  const criticalEdits = toolCalls
    .filter(tc => tc.tool === 'Edit' || tc.tool === 'Write')
    .filter(tc => {
      const path = tc.parameters.file_path;
      return criticalPatterns.some(pattern => path.includes(pattern));
    });

  if (criticalEdits.length > 0) {
    return `
📊 Physics-critical code was modified

Best practice: Validate results haven't changed
- Run small test sample with both old and new code
- Compare event counts
- Compare histogram integrals
- Check for systematic variations

Reference: Your validation workflow in ANALYSIS_WORKFLOW.md
`;
  }

  return null;
}
```

---

### 5. Streamline CLAUDE.md

**Current**: ~400 lines with detailed workflow info
**Target**: ~200 lines focused on critical context

**Strategy**:
- Keep: Environment setup, build system, project structure, critical warnings
- Move to ANALYSIS_WORKFLOW.md: Detailed step-by-step procedures
- Move to separate docs: Job submission details, combine usage
- Keep concise: One-paragraph summaries instead of full explanations

**Benefits**:
- Faster context loading
- Easier to maintain
- More focused AI attention on critical info

**Action Items**:
- [ ] Review CLAUDE.md sections
- [ ] Identify content for ANALYSIS_WORKFLOW.md
- [ ] Create separate job submission guide if needed
- [ ] Rewrite CLAUDE.md to ~200 lines

---

### 6. Task Tracking Discipline

**Current State**: TodoWrite tool available but underutilized

**Improvement**: Use TodoWrite for multi-step workflows

**When to Use**:
- Job submission workflows (multiple eras/channels)
- Multi-stage analysis pipeline (Stage 4.1 → 4.5)
- Build → test → commit sequences
- Systematic debugging across multiple files

**Example**:
```json
[
  {
    "content": "Submit nominal jobs for 2016preVFP",
    "activeForm": "Submitting nominal jobs for 2016preVFP",
    "status": "completed"
  },
  {
    "content": "Submit nominal jobs for 2016postVFP",
    "activeForm": "Submitting nominal jobs for 2016postVFP",
    "status": "in_progress"
  },
  {
    "content": "Submit nominal jobs for 2017",
    "activeForm": "Submitting nominal jobs for 2017",
    "status": "pending"
  }
]
```

**Benefits**:
- Clear progress tracking
- No forgotten steps
- Easier to resume after context reset

---

### 7. Prompting Guidelines

**Based on Reddit Post Recommendations**

#### For User (You):

**Be Specific**:
- ❌ "Fix the datacard script"
- ✅ "Fix the datacard script in plotting/writeDatacard.py - it's using old btag_shape names instead of btag"

**Provide Context**:
- ❌ "Check if this is right"
- ✅ "I'm seeing different event counts in 2017 vs 2018 for tttt. Can you check if the input file paths are correct?"

**Ask Neutral Questions**:
- ❌ "This looks good, right?"
- ✅ "What do you think about this approach? Are there any issues?"

**Specify Validation Needs**:
- ❌ "Update the systematic names"
- ✅ "Update the systematic names, then validate that physics results are identical to v0BDT reference"

#### For Claude (Me):

**Ask Clarifying Questions First**:
- Before major changes, ask: channel? version? validation required?
- Confirm understanding of task scope
- Verify which files/directories are involved

**Show Options**:
- For ambiguous tasks, present 2-3 approaches
- Explain trade-offs
- Let you decide

**Explicit Validation Plans**:
- State what will be checked after changes
- Ask if additional validation is needed
- Don't assume "working" means "validated"

**Request Confirmation**:
- Before submitting jobs (costs compute time)
- Before modifying multiple files
- Before major refactoring

---

### 8. Dev Docs System for Major Tasks

**Purpose**: Maintain context through long analysis workflows

**Structure**:

```
FourTop/
├── .claude/
│   └── dev-docs/
│       ├── current-plan.md          # Approved strategy
│       ├── context.md                # Key files, decisions
│       └── tasks.md                  # Checklist
```

**Example: Major Analysis Update**

**current-plan.md**:
```markdown
# Plan: Add New Signal Sample (VLL 850 GeV)

## Goal
Integrate VLL_M850 signal sample into 1tau1l analysis

## Approach
1. Add input file paths to inputFiles/
2. Update process list in run_treeAnalyzer.C
3. Submit jobs for nominal + systematics
4. Validate event counts
5. Add to combine datacards
6. Re-run limits

## Validation
- Event counts match expected from DAS
- Systematics produce expected variations
- Combine runs without errors
```

**context.md**:
```markdown
# Context: VLL 850 GeV Integration

## Key Files
- writeHistGood/apps/run_treeAnalyzer.C:45 - Process list
- inputFiles/inputList_2018.txt - Input paths
- plotting/writeDatacard.py - Datacard generation

## Decisions
- Using v8BDT1tau1lV19 version for consistency
- Same systematic variations as other VLL masses
- Combining with existing Run2 datacard
```

**tasks.md**:
```markdown
# Tasks: VLL 850 GeV

- [x] Locate input files on /publicfs
- [x] Add to inputList_2018.txt
- [ ] Update run_treeAnalyzer.C process list
- [ ] Submit nominal jobs
- [ ] Submit systematic jobs
- [ ] Validate outputs
- [ ] Update datacard
- [ ] Run combine
```

**Usage**:
- Update before context compaction
- Reference in prompts: "Continue VLL 850 integration from dev-docs"
- Allows seamless resumption after breaks

---

### 9. Specialized Agents for Physics Analysis

**Potential Custom Agents**:

#### `physics-validator`
```markdown
Expert in validating CMS physics analysis results

Responsibilities:
- Compare event counts between versions
- Check histogram integrals
- Verify systematic variations are sensible
- Identify physics bugs (wrong sign, wrong branch, etc.)

Tools: Read, Grep, Bash (for ROOT commands)
```

#### `combine-helper`
```markdown
Expert in HiggsAnalysis CombinedLimit tool

Responsibilities:
- Run combine algorithms (limits, significance, impacts)
- Diagnose combine errors
- Interpret fit results
- Generate post-fit plots

Tools: Bash, Read, Write (for datacards)
```

#### `job-monitor`
```markdown
Expert in IHEP cluster job management

Responsibilities:
- Check job status with checkJobResult.py
- Identify failed jobs
- Generate resubmission scripts
- Monitor disk usage

Tools: Bash, Read, Glob
```

**Create in**: `.claude/agents/` (if supported) or as detailed skill files

---

### 10. Code Review Integration

**From Reddit Post**: "Have Claude review its own work periodically"

**Implementation**:

#### Add to workflow:
After completing major code changes:
```
"Before we finalize this, can you review the changes for:
1. Physics correctness (sign conventions, branch names, units)
2. CMS naming convention compliance
3. Potential memory issues
4. Edge cases not handled
5. Impact on existing analyses"
```

#### Create `/self-review` command:
```markdown
Review the code changes made in this session

Check for:
- Physics bugs (wrong signs, wrong formulas, wrong branches)
- CMS convention compliance
- Memory leaks or resource issues
- Error handling gaps
- Documentation needs
- Validation requirements

Provide:
1. Issues found (if any)
2. Recommendations
3. Validation checklist
```

---

## Action Plan

### Immediate (This Week)
- [ ] Create `/check-environment` slash command
- [ ] Create `/validate-physics` slash command
- [ ] Start using TodoWrite for multi-step tasks
- [ ] Implement better prompting practices (both sides)

### Short-term (This Month)
- [ ] Implement UserPromptSubmit hook for environment checks
- [ ] Create `/run-nominal-jobs` and `/run-systematic-jobs` commands
- [ ] Implement build verification hook
- [ ] Streamline CLAUDE.md to ~200 lines

### Medium-term (Next Analysis Iteration)
- [ ] Set up dev-docs system for major tasks
- [ ] Create specialized agents (physics-validator, combine-helper)
- [ ] Implement physics safety checks hook
- [ ] Create comprehensive workflow automation

### Continuous
- [ ] Update this document as we discover new patterns
- [ ] Track what works / what doesn't
- [ ] Iterate on hook implementations
- [ ] Refine slash commands based on usage

---

## Success Metrics

**How we'll know these improvements are working**:

1. **Fewer Environment Errors**: Never run code without sourcing environment
2. **Faster Workflows**: Common tasks automated via slash commands
3. **Better Context Retention**: Dev docs prevent losing direction
4. **Higher Code Quality**: Build/physics hooks catch issues immediately
5. **Clearer Communication**: Better prompting reduces back-and-forth
6. **Consistent Validation**: Never skip physics validation after changes

---

## Notes

- This is a living document - update as we implement and learn
- Not all improvements need to be implemented immediately
- Prioritize based on pain points in current workflow
- Test hooks/commands on small tasks before deploying to production workflows

---

**References**:
- Original post: https://dev.to/diet-code103/claude-code-is-a-beast-tips-from-6-months-of-hardcore-use-572n
- Example infrastructure: https://github.com/diet103/claude-code-infrastructure-showcase
- Claude Code docs: https://code.claude.com/docs/

**Last Updated**: 2025-11-26
**Next Review**: After first major analysis iteration with new workflow
