# Long-Running Job Integration Patterns

**Created**: 2025-12-10
**Status**: DRAFT
**Related**: Phase 7 of workflow-optimization

---

## Overview

Many analysis steps in the FourTop workflow take hours to complete:
- **Combine fits**: 10 minutes to several hours (impacts can take 2-4 hours)
- **Systematic variations**: 100-3000+ jobs × minutes per job
- **BDT training**: Minutes to hours depending on samples
- **Template generation**: Hours for full systematic set

This document defines patterns for handling these long-running tasks.

---

## Pattern 1: Background Job Submission with Monitoring

### Use Case
Scripts that submit HTCondor/batch jobs and need to track completion.

### Implementation Pattern

```python
# Job submission script (e.g., makeJob_MV_JESVariation.py)
def submit_jobs(config, era, systematic_group='all'):
    """Submit systematic variation jobs"""

    # 1. Calculate expected job count
    expected_jobs = calculate_job_count(config, systematic_group)

    # 2. Submit jobs with clear logging
    logger.info(f"Submitting {expected_jobs} jobs for {systematic_group}")
    submitted_clusters = []

    for systematic in get_systematics(systematic_group):
        cluster_id = submit_condor_job(systematic)
        submitted_clusters.append(cluster_id)
        logger.info(f"  Submitted {systematic}: cluster {cluster_id}")

    # 3. Print monitoring commands
    print(f"\n{'='*60}")
    print(f"Submitted {len(submitted_clusters)} job clusters")
    print(f"{'='*60}")
    print(f"\nMonitor progress:")
    print(f"  hep_q -u $USER | grep {get_job_prefix()}")
    print(f"\nCheck output:")
    print(f"  ls -lh {get_output_dir(config, era)}")
    print(f"\nExpected output: {expected_jobs} ROOT files")
    print(f"{'='*60}\n")

    return submitted_clusters
```

### Best Practices
1. **Always print monitoring commands** - User needs to check status
2. **Show expected output count** - User can verify completion
3. **Log cluster IDs** - Enables job cancellation if needed
4. **Fail fast on quota/permission errors** - Check before submitting all jobs

---

## Pattern 2: Combine Workflow (Multi-Step Background Process)

### Use Case
Statistical analysis with multiple dependent steps (workspace → significance → postfit → impacts).

### Current Implementation (`run_runCombineAll.sh`)

**Strengths**:
- Uses `nohup` for background execution
- Logs to dedicated file
- Provides monitoring commands

**Weaknesses**:
- No progress tracking between steps
- Errors only visible in log file
- Hard to resume from failed step

### Improved Pattern

```python
# hua/combine/runCombineAll.py
class CombineWorkflow:
    def __init__(self, card_dir, steps, blind=True):
        self.card_dir = card_dir
        self.steps = steps
        self.blind = blind
        self.state_file = os.path.join(card_dir, '.workflow_state.json')

    def run(self):
        """Run workflow with state tracking"""
        state = self.load_state()

        for step in self.steps:
            if step in state['completed']:
                logger.info(f"✓ Step '{step}' already complete, skipping")
                continue

            logger.info(f"Running step: {step}")
            start_time = time.time()

            try:
                self.run_step(step)
                elapsed = time.time() - start_time
                state['completed'].append(step)
                state['timings'][step] = elapsed
                self.save_state(state)
                logger.info(f"✓ Step '{step}' completed in {elapsed:.1f}s")
            except Exception as e:
                logger.error(f"✗ Step '{step}' failed: {e}")
                state['failed'] = step
                self.save_state(state)
                raise

    def load_state(self):
        """Load workflow state for resumption"""
        if os.path.exists(self.state_file):
            with open(self.state_file) as f:
                return json.load(f)
        return {'completed': [], 'failed': None, 'timings': {}}

    def save_state(self, state):
        """Save workflow state"""
        with open(self.state_file, 'w') as f:
            json.dump(state, f, indent=2)
```

**Benefits**:
- Resume from failed step without redoing work
- Track timing for each step
- State persists across sessions
- Clear progress indication

---

## Pattern 3: Staged Workflow with Checkpoints

### Use Case
Multi-stage pipeline where each stage takes minutes to hours (OS → MV → WH → PL → Combine).

### Implementation (`run_workflow.py`)

**Current Approach**:
```python
# User manually runs each stage
python3 run_workflow.py --stage 1 --config config.yaml  # OS: 30-60 min
# Wait for completion...
python3 run_workflow.py --stage 2 --config config.yaml  # MV: 20-40 min
# Wait for completion...
```

**Improved Pattern**:

```python
# run_workflow.py (enhanced)
def run_full_workflow(config_path, start_stage=1, end_stage=None, wait=True):
    """
    Run multi-stage workflow with automatic progression.

    Args:
        config_path: Path to YAML config
        start_stage: First stage to run (default: 1)
        end_stage: Last stage to run (default: all stages)
        wait: If True, wait for jobs to complete before next stage
    """
    stages = get_stages(start_stage, end_stage)

    for stage in stages:
        logger.info(f"\n{'='*60}")
        logger.info(f"STAGE {stage}: {STAGE_NAMES[stage]}")
        logger.info(f"{'='*60}\n")

        # Run stage
        job_clusters = run_stage(stage, config_path)

        if wait and job_clusters:
            # Wait for jobs to complete
            wait_for_jobs(job_clusters, stage_name=STAGE_NAMES[stage])
        elif job_clusters:
            # Print resume command
            print(f"\nTo continue after jobs complete:")
            print(f"  python3 run_workflow.py --config {config_path} --stage {stage+1}")
            break

    logger.info("\n✓ Workflow complete!")

def wait_for_jobs(clusters, stage_name, check_interval=60):
    """Poll HTCondor until all jobs complete"""
    logger.info(f"Waiting for {len(clusters)} job clusters to complete...")

    while True:
        running = get_running_jobs(clusters)
        if not running:
            logger.info(f"✓ All {stage_name} jobs complete")
            break

        logger.info(f"  {running} jobs still running...")
        time.sleep(check_interval)
```

**Usage**:
```bash
# Run full workflow with automatic waiting
python3 run_workflow.py --config config.yaml --full --wait

# Run stages 1-3, stop after each for manual checking
python3 run_workflow.py --config config.yaml --stages 1-3 --no-wait
```

---

## Pattern 4: Partial Failure Handling

### Use Case
When 95% of systematic jobs succeed but 5% fail, don't resubmit everything.

### Implementation

```python
def check_and_resubmit(config, era, stage):
    """Check for missing outputs and resubmit only failed jobs"""

    expected_files = get_expected_outputs(config, era, stage)
    existing_files = glob.glob(get_output_pattern(config, era, stage))

    missing = set(expected_files) - set(existing_files)

    if not missing:
        logger.info(f"✓ All {len(expected_files)} outputs present")
        return 0

    logger.warning(f"Missing {len(missing)}/{len(expected_files)} outputs:")
    for f in sorted(missing)[:10]:  # Show first 10
        logger.warning(f"  - {os.path.basename(f)}")

    if len(missing) > 10:
        logger.warning(f"  ... and {len(missing)-10} more")

    # Ask user before resubmitting
    response = input(f"\nResubmit {len(missing)} missing jobs? [y/N] ")
    if response.lower() != 'y':
        return len(missing)

    # Resubmit only missing
    for missing_file in missing:
        job_params = infer_job_params(missing_file)
        submit_single_job(**job_params)

    logger.info(f"Resubmitted {len(missing)} jobs")
    return len(missing)
```

---

## Pattern 5: Progress Reporting for Long Tasks

### Use Case
Impacts calculation (2-4 hours), user wants to see progress.

### Implementation

```python
def run_impacts(workspace, output_dir):
    """Run impacts with progress reporting"""

    # Get list of nuisance parameters
    nuisances = get_nuisance_parameters(workspace)
    total = len(nuisances)

    logger.info(f"Running impacts for {total} nuisance parameters")
    logger.info(f"Estimated time: {total * 2 / 60:.1f} hours (2min/parameter)")

    start_time = time.time()
    completed = 0

    for i, nuisance in enumerate(nuisances, 1):
        # Run impact fit for this parameter
        run_single_impact(workspace, nuisance, output_dir)
        completed += 1

        # Progress update every 10 parameters
        if i % 10 == 0 or i == total:
            elapsed = time.time() - start_time
            rate = completed / elapsed  # params/sec
            remaining = (total - completed) / rate if rate > 0 else 0

            logger.info(f"Progress: {i}/{total} ({i/total*100:.1f}%) | "
                       f"Elapsed: {elapsed/60:.1f}min | "
                       f"Remaining: ~{remaining/60:.1f}min")
```

---

## Recommendations for Future Development

### High Priority
1. **Add `--wait` flag to all job submission scripts** - Optionally block until jobs complete
2. **Implement state tracking in runCombineAll.py** - Enable resume from failed steps
3. **Add job count validation** - Check expected vs actual outputs before proceeding

### Medium Priority
4. **Create unified job monitoring tool** - Single command to check all running jobs
5. **Add timeout detection** - Alert if jobs haven't progressed in X hours
6. **Email notifications** - Alert when long workflows complete/fail

### Low Priority
7. **Parallel combine steps** - Run non-dependent steps (e.g., different channels) in parallel
8. **Automatic retries** - Retry failed jobs up to N times before giving up
9. **Resource estimation** - Predict memory/time requirements before submission

---

## Examples from Current Workflow

### Example 1: MV Systematic Jobs (Good Pattern)
```bash
# Submit 826 jobs (14 systematics × 59 files)
python3 makeJob_MV_JESVariation.py --config config.yaml --era 2018 --group all

# Output includes monitoring commands:
#   hep_q -u huahuil | grep MV_
#   ls -lh /path/to/output/*.root | wc -l
# Expected: 826 ROOT files
```

**Why it works**:
- Clear job count
- Monitoring commands provided
- Expected output count shown

### Example 2: Combine Workflow (Needs Improvement)
```bash
# Run full analysis
bash run_runCombineAll.sh

# Problem: If significance fails, must manually comment out workspace step
# and rerun entire script. No automatic resume.
```

**How to improve**:
```python
# Better approach
python3 runCombineAll.py --config config.yaml --steps workspace significance postfit
# If significance fails, resume with:
python3 runCombineAll.py --config config.yaml --steps significance postfit --resume
```

---

## Testing Checklist

When implementing long-running job patterns:
- [ ] Test with `--dry-run` flag first
- [ ] Verify monitoring commands work
- [ ] Test resume from partial failure
- [ ] Test with small job count first (e.g., 1 systematic)
- [ ] Document expected runtime in script help
- [ ] Add timeout protection (don't wait forever)

---

## References

- HTCondor job management: `hep_q`, `hep_rm`, `condor_q`
- Current job submission scripts: `objectSelectionOptimized/jobs/*.py`, `makeVariables_goodCode/jobs/*.py`
- Combine workflow: `hua/combine/runCombineAll.py`, `hua/combine/run_runCombineAll.sh`
