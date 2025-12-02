# CLAUDE.md - AI Assistant Context for FourTop Analysis

**Last updated**: 2025-11-26

---

## ⚠️ CRITICAL: Environment Setup

**ALWAYS source the environment before running ANY Python or C++ code:**

```bash
source /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/setEnv_newNew.sh
```

**IMPORTANT EXCEPTION - hua/combine/ scripts**:
```bash
cd hua/combine/
cmsenv  # NOT source setEnv_newNew.sh
python3 script.py
```

**Reason**: Combine scripts require CombinedLimit environment from CMSSW

---

## 🔧 Current Work in Progress

**IMPORTANT**: Always update this section and referenced documentation as we make progress!

### Active Tasks

#### 1. CMS Naming Convention Migration
**Status**: ✅ **VALIDATED** (2025-11-25)
**Documentation**: [writeHistGood/CMS_NAMING_CONVENTION_UPDATE.md](writeHistGood/CMS_NAMING_CONVENTION_UPDATE.md)
**Version**: `v8BDT1tau0l_refactorAndBtagNameFix`

- Fixed: `btag_shape` → `btag`
- All 26 b-tag systematics use correct CMS names
- End-to-end validation: v8BDT = v0BDT results (identical)

#### 2. Analysis Workflow Documentation & Automation
**Status**: 🔄 Active
**Documentation**: [ANALYSIS_WORKFLOW.md](ANALYSIS_WORKFLOW.md)

- Documenting end-to-end pipeline from NanoAOD to physics results
- Current: 1tau0l channel complete through Stage 4.4 (Combine analysis)
- Next: Stage 4.5 (Results visualization)

### Reminder for AI Assistants
When working on these tasks:
1. Update progress in this section
2. Update detailed documentation in referenced .md files
3. Record all commands/scripts/parameters in ANALYSIS_WORKFLOW.md
4. Note issues, blockers, optimization opportunities
5. Mark completed tasks with date stamps

### TODO: Code Optimization for Token Efficiency
**Priority**: Medium
**Issue**: Python scripts (writeDatacard.py, smooth_systematics_fourTops.py) print verbose output to stdout when run, consuming many tokens when executed with Claude
**Examples**:
- `writeDatacard.py` prints entire MCSys dictionary (~100+ systematics) when run
- Running with `-h` flag outputs full dictionary instead of help message
**Solutions to implement**:
1. Add `--quiet` or `--silent` flag to suppress non-essential print statements
2. Redirect systematic dictionary printing to stderr or log file instead of stdout
3. Remove debug print statements from production code
4. Use Python logging module with configurable verbosity levels
**Benefits**: Significant token savings when running analysis workflows with Claude (estimated 50-70% reduction per script execution)

### Dev-Docs System for Major Tasks

**Location**: `.claude/dev-docs/active/[task-name]/`

**When to use**: For multi-session tasks (new signal samples, major refactoring, multi-channel analysis)

**Automatic creation**: When exiting plan mode with an accepted plan, automatically create dev-docs:
1. Ask user for task name (suggest from plan title)
2. Create directory: `.claude/dev-docs/active/[task-name]/`
3. Create `plan.md` from the accepted plan
4. Create `context.md` with key files identified during planning
5. Create `tasks.md` from plan steps
6. Inform user: "Dev-docs created at .claude/dev-docs/active/[task-name]/"

**Manual creation**: For tasks not starting from plan mode:
1. Create directory: `mkdir -p .claude/dev-docs/active/[task-name]/`
2. Copy templates: `TEMPLATE_plan.md`, `TEMPLATE_context.md`, `TEMPLATE_tasks.md`
3. Fill in details and begin work

**Continuing existing tasks**:
1. **Always check first**: Look in `.claude/dev-docs/active/` for existing task directories
2. **If task found**: Read `plan.md`, `context.md`, `tasks.md` from the task directory before proceeding
3. **Update regularly**:
   - Mark tasks complete immediately (don't batch)
   - Update "Last Updated" timestamps in each file
   - Archive to `completed/` when done

**User can resume with**: "Continue [task-name] from dev-docs"

**Benefit**: Per-task directories preserve full context across sessions, easy to manage multiple tasks

**IMPORTANT - Automatic Context Preservation**:
When context usage reaches ~10% remaining, Claude MUST automatically:
1. Update `tasks.md` with current progress (mark completed tasks, note in-progress work)
2. Update `context.md` with any new key files or decisions discovered
3. Add session notes to the Notes section with date stamp
4. Commit any uncommitted changes with descriptive message
5. Inform user: "Context low - dev-docs updated and changes committed for next session"

This ensures seamless continuation even if the session ends unexpectedly.

**IMPORTANT - Commit Changes Regularly**:
Claude should proactively commit changes during work sessions:
- After completing a logical unit of work (e.g., fixing a bug, adding a feature)
- After completing each phase or major task
- Before context gets low (~10% remaining)
- Use descriptive commit messages explaining what was done and why

**IMPORTANT - Test Code Before Committing**:
Claude MUST test code changes before considering a task complete:
- Run modified scripts with `--help` or `-h` to verify argparse works
- Run scripts with new flags (e.g., `--quiet`) to verify they function
- For Python: check syntax with `python3 -m py_compile script.py`
- For analysis scripts: run on a small test case if possible
- Document test results in dev-docs or commit message

---

## Project Overview

**CMS Four-Top Quark Physics Analysis** - Searches for rare four-top production (tttt) and Beyond Standard Model signals (VLL - Vector-Like Leptons) using CMS detector data.

**Key Analysis Channels**:
- `1tau0l`: One hadronic tau + 0 leptons
- `1tau1l`: One hadronic tau + 1 lepton
- `1tau2l`: One hadronic tau + 2 leptons

**Analysis Goals**:
- Measure tttt production cross-section
- Search for Vector-Like Lepton signals
- Use BDT/TMVA for signal discrimination
- Statistical inference with HiggsAnalysis CombinedLimit

---

## Project Structure

```
FourTop/
├── writeHistGood/          # Main histogram production (C++/ROOT)
│   ├── apps/               # Main executables
│   ├── include/            # C++ headers
│   ├── src/                # C++ source files
│   ├── Makefile            # Build system
│   └── jobs/               # Job submission scripts
├── hua/
│   ├── combine/            # Statistical analysis (CombinedLimit)
│   └── tmva/               # Machine learning training
├── plotting/               # Plotting scripts (Python/ROOT)
├── objectSelectionOptimized/  # Event selection code
├── makeVariables_goodCode/    # Variable calculation
├── inputFiles/             # Input ROOT files and configurations
├── myLibrary/              # Shared C++ utilities
├── .claude/
│   └── dev-docs/           # Task tracking system (plan, context, tasks)
├── README.md               # User-facing documentation
├── ANALYSIS_WORKFLOW.md    # Detailed end-to-end workflow
├── setEnv_newNew.sh        # Environment setup script
└── CLAUDE.md               # This file
```

---

## Analysis Workflow

**Complete workflow**: See [ANALYSIS_WORKFLOW.md](ANALYSIS_WORKFLOW.md)

**Pipeline**: `NanoAOD → Histogram Production → Datacards → Statistical Analysis → Results`

**Current version**: `v8BDT1tau1lV19_refactorAndBtagNameFix`
- ✅ CMS naming conventions compliant
- ✅ All 26 b-tag systematics working
- ✅ Refactored code validated

**Main components**:
1. **writeHistGood/**: NanoAOD → histograms with systematics
2. **hua/tmva/**: BDT training for signal/background separation
3. **hua/combine/**: Statistical analysis (limits, significance, fits)
4. **plotting/**: Visualization and validation plots

---

## Build System

**Technical stack**:
- Compiler: gcc 14.3.1
- ROOT: 6.36.01
- C++ Standard: C++20
- Dependencies: ROOT, TBB, myLibrary, JSON for Modern C++

**Build writeHistGood**:
```bash
cd writeHistGood/
source ../setEnv_newNew.sh  # MANDATORY
make clean && make
```

**Common issues**:
- Missing TBB: Ensure `TBBLIBS = -ltbb` in Makefile
- Wrong environment: Always source `setEnv_newNew.sh` from project root

---

## Job Submission (IHEP Cluster)

**Cluster**: IHEP HTCondor via `hep_sub` command

**Key scripts**:
- Nominal jobs: `writeHistGood/jobs/makeJob_forWriteHist.py`
- Systematic jobs: `writeHistGood/run_makeJos_WH_forJES.sh`
- Job monitoring: `writeHistGood/jobs/checkJobResult.py`

**Details**: See [ANALYSIS_WORKFLOW.md](ANALYSIS_WORKFLOW.md) Stage 2 & 3

---

## Git Workflow

- **Current branch**: `addVLL`
- **Main branch**: `master`
- **Commit policy**: Regular commits for major changes
- **Recent focus**: VLL analysis, code refactoring, documentation, build fixes

---

## Key Files Reference

**Critical files**:
- `writeHistGood/apps/run_treeAnalyzer.C` - Main analysis loop
- `writeHistGood/Makefile` - Build system
- `setEnv_newNew.sh` - Environment configuration
- `hua/combine/runCombineAll.py` - Statistical analysis orchestration

**Documentation**:
- `README.md` - User guide
- `ANALYSIS_WORKFLOW.md` - Detailed workflow procedures
- `SESSION_SUMMARY.md` - Development history
- `writeHistGood/BUILD_INSTRUCTIONS.md` - Build details
- `writeHistGood/CMS_NAMING_CONVENTION_UPDATE.md` - Systematic naming
- `COLLABORATION_IMPROVEMENTS.md` - AI workflow enhancements

---

## Questions to Ask When Context is Unclear

1. **Which component**? (writeHistGood / TMVA / combine / plotting)
2. **Which channel**? (1tau0l / 1tau1l / 1tau2l)
3. **Which process**? (tttt / VLL / backgrounds)
4. **Which version**? (v3BDT / V18 / combinationVX)
5. **Systematics enabled**? (affects runtime and output)

---

## User Preferences & Collaboration Guidelines

**Code modifications**:
- ✅ Preserve modern C++ patterns in refactored code
- ✅ Validate physics results unchanged after modifications
- ✅ Commit major changes regularly
- ✅ Update BASH_COMMANDS_EXPLAINED.md for new patterns

**Code review priorities**:
- **Safety**: Watch for physics bugs (wrong sign, wrong branch, off-by-one)
- **Consistency**: Maintain systematic naming conventions (CMS POG standards)
- **Performance**: Large datasets (~millions of events), be memory-conscious
- **Reproducibility**: Physics results must be deterministic

**Communication style**:
- User is physicist and experienced developer
- Can handle technical details and direct feedback
- Appreciates explanations of *why*, not just *how*
- Values code maintainability and long-term project health

**Best practices** (from COLLABORATION_IMPROVEMENTS.md):
- Ask clarifying questions before major tasks
- Use TodoWrite for multi-step workflows
- Verify environment before running code
- Validate physics results after critical changes
- Update documentation as work progresses

**Code quality**: Automated hooks enabled (`.claude/hooks/post-tool-use.sh`)
- Python: max 80 lines/function, max nesting depth 5
- See `.claude/settings.json` for full standards

---

## Resources

**Internal**:
- README.md - User workflow
- ANALYSIS_WORKFLOW.md - Detailed procedures
- SESSION_SUMMARY.md - Development notes
- COLLABORATION_IMPROVEMENTS.md - AI workflow best practices

**External**:
- CMS NanoAOD: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookNanoAOD
- HiggsAnalysis CombinedLimit: https://cms-analysis.github.io/HiggsAnalysis-CombinedLimit/
- ROOT: https://root.cern.ch/doc/master/
- CMSSW: https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookCMSSWFramework

---

*This document provides essential context for AI assistants. For detailed procedures, see ANALYSIS_WORKFLOW.md and other referenced documentation.*

*Maintained by: Claude Code AI Assistant*
