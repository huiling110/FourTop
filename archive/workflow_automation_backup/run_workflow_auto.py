#!/usr/bin/env python3
"""
Workflow Automation Script (V3)

Provides automatic stage progression with resume capability.
Designed to run in screen session for long-running workflows.

Usage:
    # Initialize workflow for channel
    python3 run_workflow_auto.py --init --channel 1tau1l \
        --config config/analysis_config_1tau1l_TTBBtest.yaml --eras 2017

    # Run automation (submit, wait, next stage)
    python3 run_workflow_auto.py --run --poll-interval 60

    # Check status only
    python3 run_workflow_auto.py --status

    # Resume from interruption
    python3 run_workflow_auto.py --resume

    # Run from specific stage
    python3 run_workflow_auto.py --run --eras 2017 --start-stage 4.1

Stage Groups:
    "1"     : Object Selection (NanoAOD → skimmed ntuples)
    "1.1"   : OS systematic variations (15 variations)
    "2"     : Make Variables (skimmed → BDT input)
    "2.1"   : MV systematic variations (14 variations)
    "3"     : Histogram production (nominal + 74 systematics, submitted together)
    "4.1"   : Consolidate JES systematics
    "4.2"   : Create templates
    "4.3"   : Smooth systematics (requires ALL eras templates, mandatory for 1tau1l/1tau0l)
    "4.4"   : Write datacards
    "4.5"   : Run combine (significance, limits)
    "4.6"   : Post-fit plots
    "4.7"   : Generate plots
"""

import argparse
import os
import subprocess
import sys
import time
from datetime import datetime
from pathlib import Path
from typing import List, Optional, Tuple

# Add plotting to path for workflow utilities
sys.path.insert(0, str(Path(__file__).parent / 'plotting'))

try:
    from workflow_state_v3 import CompactWorkflowState
except ImportError:
    print("Error: Cannot import workflow_state_v3. Run from FourTop directory.")
    sys.exit(1)


class WorkflowAutomation:
    """Automated workflow progression with state tracking."""

    # Stage order for progression
    # Note: Stage 3 submits nominal+systematics together (--systematic complete) for parallel execution
    # Note: Stage 4.3 (smooth) requires ALL eras to have templates - it's a sync point
    # Note: Stage 4.4.1 (combineDatacard) combines 4 eras into 1-channel Run2 datacard
    # Note: Stage 4.4.2 (combineDatacard 3-channel) combines 3 channels' Run2 datacards
    STAGE_ORDER = ['1', '1.1', '2', '2.1', '3', '4.1', '4.2', '4.3', '4.4', '4.4.1', '4.5', '4.6', '4.7', 'complete']

    # Stages that submit jobs and require waiting
    JOB_STAGES = {'1', '1.1', '2', '2.1', '3'}

    # Stages that require all eras to be at the same point (sync points)
    SYNC_STAGES = {'4.3', '4.4.1'}  # smooth_systematics and combineDatacard need all eras

    # Stages that require all channels to be at the same point (cross-channel sync)
    CROSS_CHANNEL_STAGES = {'4.4.2'}  # 3-channel combination

    # Channels that require smoothing (mandatory)
    SMOOTH_CHANNELS = {'1tau1l', '1tau0l'}

    # Stage descriptions
    STAGE_NAMES = {
        '1': 'OS nominal',
        '1.1': 'OS systematics',
        '2': 'MV nominal',
        '2.1': 'MV systematics',
        '3': 'WH complete (nominal+systematics)',
        '4.1': 'addJES consolidation',
        '4.2': 'addTemplate',
        '4.3': 'smooth systematics',
        '4.4': 'writeDatacard',
        '4.4.1': 'combineDatacard (1-channel Run2)',
        '4.5': 'combine',
        '4.6': 'postfit plots',
        '4.7': 'plots',
        'complete': 'done'
    }

    def __init__(self, poll_interval: int = 60, max_wait: int = 14400, log_file: Optional[Path] = None):
        """
        Initialize automation.

        Args:
            poll_interval: Seconds between job status checks (default: 60)
            max_wait: Maximum wait time for jobs in seconds (default: 14400 = 4 hours)
            log_file: Optional log file path (default: .workflow/auto_TIMESTAMP.log)
        """
        self.state = CompactWorkflowState()
        self.poll_interval = poll_interval
        self.max_wait = max_wait
        self.project_root = Path(__file__).parent

        # Setup log file
        if log_file:
            self.log_file = Path(log_file)
        else:
            log_dir = self.project_root / ".workflow"
            log_dir.mkdir(exist_ok=True)
            timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
            self.log_file = log_dir / f"auto_{timestamp}.log"

        self._log_handle = open(self.log_file, 'w')
        self.log(f"Log file: {self.log_file}")

    def __del__(self):
        """Close log file on cleanup."""
        if hasattr(self, '_log_handle') and self._log_handle:
            self._log_handle.close()

    def log(self, message: str, level: str = "INFO"):
        """Log with timestamp to stdout and file."""
        timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        log_line = f"[{timestamp}] {level}: {message}"
        print(log_line)
        if hasattr(self, '_log_handle') and self._log_handle:
            self._log_handle.write(log_line + '\n')
            self._log_handle.flush()

    def get_running_jobs(self) -> int:
        """
        Get count of running/pending jobs via hep_q.

        Returns:
            Number of jobs, or -1 on error
        """
        try:
            result = subprocess.run(
                ['hep_q', '-u'],
                capture_output=True,
                text=True,
                timeout=30
            )
            # Count non-header lines
            lines = result.stdout.strip().split('\n')
            job_lines = [l for l in lines if l.strip()
                        and 'OWNER' not in l
                        and 'JOBID' not in l
                        and not l.startswith('-')]
            return len(job_lines)
        except Exception as e:
            self.log(f"Error checking jobs: {e}", "WARNING")
            return -1

    def wait_for_jobs(self, era: str, stage: str) -> bool:
        """
        Wait for jobs to complete, updating state periodically.

        Args:
            era: Era being processed
            stage: Current stage

        Returns:
            True if jobs completed, False on timeout/error
        """
        start = time.time()
        last_count = -1

        self.log(f"Waiting for {era} S{stage} jobs to complete...")

        while True:
            elapsed = time.time() - start

            if elapsed > self.max_wait:
                self.log(f"TIMEOUT: {era} S{stage} jobs exceeded {self.max_wait}s", "ERROR")
                self.state.update_era(era, stage, "timeout", 0)
                return False

            count = self.get_running_jobs()

            if count == 0:
                self.log(f"COMPLETE: {era} S{stage} - all jobs finished in {elapsed:.0f}s")
                self.state.update_era(era, stage, "done", 0)
                return True

            if count == -1:
                self.log("Warning: Could not check job count, retrying...", "WARNING")
                time.sleep(self.poll_interval)
                continue

            if count != last_count:
                self.log(f"WAITING: {era} S{stage} - {count} jobs ({elapsed:.0f}s elapsed)")
                self.state.update_era(era, stage, "running", count)
                last_count = count

            time.sleep(self.poll_interval)

    def run_command(self, cmd: List[str], cwd: Optional[Path] = None,
                    shell: bool = False, env_type: str = 'analysis') -> Tuple[int, str, str]:
        """
        Run a command and return result.

        Args:
            cmd: Command as list of strings
            cwd: Working directory
            shell: Use shell execution
            env_type: 'analysis' for setEnv_newNew.sh, 'combine' for cmsenv, 'none' for raw

        Returns:
            Tuple of (return_code, stdout, stderr)
        """
        try:
            work_dir = cwd or self.project_root

            # Wrap command with environment setup
            if env_type == 'analysis':
                # Source setEnv_newNew.sh for stages 1-4.4
                cmd_str = f"cd {self.project_root} && source setEnv_newNew.sh && {' '.join(cmd)}"
                result = subprocess.run(
                    ['bash', '-c', cmd_str],
                    cwd=work_dir,
                    capture_output=True,
                    text=True
                )
            elif env_type == 'combine':
                # cmsenv handled separately in _run_combine
                cmd_str = ' '.join(cmd)
                result = subprocess.run(
                    cmd_str,
                    shell=True,
                    cwd=work_dir,
                    capture_output=True,
                    text=True
                )
            else:
                # No environment wrapping
                if shell:
                    result = subprocess.run(
                        ' '.join(cmd),
                        shell=True,
                        cwd=work_dir,
                        capture_output=True,
                        text=True
                    )
                else:
                    result = subprocess.run(
                        cmd,
                        cwd=work_dir,
                        capture_output=True,
                        text=True
                    )
            return result.returncode, result.stdout, result.stderr
        except Exception as e:
            return 1, '', str(e)

    def submit_stage(self, era: str, stage: str) -> bool:
        """
        Submit/run a stage for an era.

        Args:
            era: Era to process
            stage: Stage to run

        Returns:
            True if successful, False otherwise
        """
        config = self.state.get_config()
        channel = self.state.get_channel()

        if not config or not channel:
            self.log("Error: Workflow not initialized (no config/channel)", "ERROR")
            return False

        self.log(f"STARTING: {era} S{stage} ({self.STAGE_NAMES.get(stage, stage)})")
        self.state.update_era(era, stage, "submitting", 0)

        # Build command based on stage
        cmd = self._get_stage_command(stage, era, config, channel)

        if not cmd:
            self.log(f"Unknown stage: {stage}", "ERROR")
            return False

        # Run command
        self.log(f"Running: {' '.join(cmd[:5])}...")  # First 5 parts for readability

        # Stage 3 with systematics takes ~10-20 mins to submit - run in background
        if stage == '3':
            return self._submit_wh_background(era, config, channel)

        returncode, stdout, stderr = self.run_command(cmd)

        if returncode == 0:
            if stage in self.JOB_STAGES:
                # Job submission stages - check job count
                jobs = self.get_running_jobs()
                self.state.update_era(era, stage, "running", jobs)
                self.log(f"SUBMITTED: {era} S{stage} - {jobs} jobs in queue")
            else:
                # Immediate stages (4.1-4.4, 4.6)
                self.state.update_era(era, stage, "done", 0)
                self.log(f"DONE: {era} S{stage}")
            return True
        else:
            self.log(f"FAILED: {era} S{stage}", "ERROR")
            self.log(f"stderr: {stderr[:500]}", "ERROR")
            self.state.update_era(era, stage, "failed", 0)
            return False

    def _get_stage_command(self, stage: str, era: str, config: str,
                           channel: str) -> Optional[List[str]]:
        """Get command for a specific stage."""
        commands = {
            '1': ['python3', 'objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py',
                  '--config', config, '--era', era],
            '1.1': ['bash', 'objectSelectionOptimized/jobs/submit_all_systematics.sh',
                    config, era],
            '2': ['python3', 'makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py',
                  '--config', config, '--era', era],
            '2.1': ['python3', 'makeVariables_goodCode/jobs/makeJob_MV_JESVariation.py',
                    '--config', config, '--era', era, '--group', 'all'],
            '3': ['python3', 'writeHistGood/jobs/makeJob_WH.py',
                  '--config', config, '--era', era, '--systematic', 'complete'],
            '4.1': ['python3', 'plotting/addJESTemplatesToHistFile.py',
                    '--config', config, '--era', era, '--execute', '--quiet'],
            '4.2': ['python3', 'plotting/addTemplateNew.py',
                    '--config', config, '--era', era, '--quiet'],
            # 4.3 smooth_systematics: runs once for all eras (not per-era)
            '4.3': ['python3', 'plotting/smooth_systematics_fourTops.py',
                    '--config', config, '--quiet'],
            '4.4': ['python3', 'plotting/writeDatacard.py',
                    '--config', config, '--era', era],
            # 4.5 combine: handled specially by run_combine()
            '4.6': ['python3', 'plotting/pl_postFit.py',
                    '--config', config, '--era', era],
            '4.7': ['python3', 'plotting/pl.py',
                    '--config', config, '--era', era],
        }
        return commands.get(stage)

    def _submit_wh_background(self, era: str, config: str, channel: str) -> bool:
        """
        Submit Stage 3 (WH) jobs in background.

        WH with systematics takes 10-20 minutes to submit all jobs.
        This method starts submission in background and polls for job appearances.

        Args:
            era: Era to process
            config: Config file path
            channel: Channel name

        Returns:
            True if submission started successfully
        """
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        log_file = self.project_root / ".workflow" / f"wh_{channel}_{era}_{timestamp}.log"

        # Build command
        cmd = f'''
cd {self.project_root}
source setEnv_newNew.sh
cd writeHistGood/jobs
python3 makeJob_WH.py --config ../../{config} --era {era} --systematic complete --quiet
'''

        self.log(f"Starting WH submission in background (log: {log_file})")
        self.state.update_era(era, "3", "submitting", 0)

        try:
            with open(log_file, 'w') as f:
                process = subprocess.Popen(
                    ['bash', '-c', cmd],
                    stdout=f,
                    stderr=subprocess.STDOUT,
                    cwd=self.project_root
                )

            # Poll for jobs to appear (check every 30s for up to 25 mins)
            max_wait = 1500  # 25 minutes
            poll_interval = 30
            start_time = time.time()
            initial_jobs = self.get_running_jobs()

            while time.time() - start_time < max_wait:
                time.sleep(poll_interval)

                # Check if process finished
                if process.poll() is not None:
                    if process.returncode == 0:
                        jobs = self.get_running_jobs()
                        self.state.update_era(era, "3", "running", jobs)
                        self.log(f"SUBMITTED: {era} S3 - {jobs} jobs in queue")
                        return True
                    else:
                        self.log(f"WH submission failed (exit code {process.returncode})", "ERROR")
                        self.state.update_era(era, "3", "failed", 0)
                        return False

                # Check for new jobs
                current_jobs = self.get_running_jobs()
                if current_jobs > initial_jobs:
                    elapsed = int(time.time() - start_time)
                    self.log(f"WH submission in progress: {current_jobs} jobs ({elapsed}s elapsed)")
                    self.state.update_era(era, "3", "submitting", current_jobs)

            self.log("WH submission timeout (25 min)", "ERROR")
            return False

        except Exception as e:
            self.log(f"Error starting WH submission: {e}", "ERROR")
            return False

    def run_combine(self, era: str) -> bool:
        """
        Run Stage 4.6 (combine) with proper CMSSW environment.

        This stage requires special handling:
        - Different environment (cmsenv vs setEnv_newNew.sh)
        - Long running time (~1-2 hours)
        - Log monitoring for completion

        Args:
            era: Era to process

        Returns:
            True if successful, False otherwise
        """
        config = self.state.get_config()
        channel = self.state.get_channel()

        if not config or not channel:
            self.log("Error: Workflow not initialized", "ERROR")
            return False

        self.log(f"STARTING: {era} S4.5 (combine) - this may take 1-2 hours")
        self.state.update_era(era, "4.5", "running", 0)

        # Create log file
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        log_file = self.project_root / "hua" / "combine" / f"combine_{channel}_{era}_{timestamp}.log"

        # Build command with CMSSW environment
        # Note: We use bash -c to handle environment setup
        cmd = f'''
cd {self.project_root}/hua/combine/
source /cvmfs/cms.cern.ch/cmsset_default.sh
cmsenv
bash run_combine_fits.sh ../../{config} {era} {channel}
'''

        self.log(f"Log file: {log_file}")

        try:
            # Run in subprocess with output to log file
            with open(log_file, 'w') as f:
                process = subprocess.Popen(
                    ['bash', '-c', cmd],
                    stdout=f,
                    stderr=subprocess.STDOUT,
                    cwd=self.project_root
                )

            # Wait for completion with monitoring
            return self._wait_for_combine(log_file, process, era)

        except Exception as e:
            self.log(f"Error running combine: {e}", "ERROR")
            self.state.update_era(era, "4.5", "failed", 0)
            return False

    def _wait_for_combine(self, log_file: Path, process: subprocess.Popen,
                          era: str, timeout: int = 14400) -> bool:
        """
        Wait for combine to complete by monitoring process and log.

        Args:
            log_file: Path to log file
            process: Subprocess Popen object
            era: Era being processed
            timeout: Maximum wait time in seconds

        Returns:
            True if completed successfully, False otherwise
        """
        start = time.time()
        last_check = ""

        while process.poll() is None:  # Process still running
            elapsed = time.time() - start

            if elapsed > timeout:
                self.log(f"TIMEOUT: combine exceeded {timeout}s, killing...", "ERROR")
                process.kill()
                self.state.update_era(era, "4.5", "timeout", 0)
                return False

            # Check log file for progress
            if log_file.exists():
                try:
                    with open(log_file) as f:
                        content = f.read()

                    # Look for completion markers
                    if "Done in" in content and "Done in" not in last_check:
                        self.log("Combine completed (found 'Done in' marker)")
                    if "Significance:" in content and "Significance:" not in last_check:
                        # Extract significance
                        for line in content.split('\n'):
                            if "Significance:" in line:
                                self.log(f"Result: {line.strip()}")

                    last_check = content
                except:
                    pass

            # Progress update every 5 minutes
            if int(elapsed) % 300 == 0 and int(elapsed) > 0:
                self.log(f"Combine running... {int(elapsed/60)} minutes elapsed")

            time.sleep(60)  # Check every minute

        # Process finished
        if process.returncode == 0:
            self.log(f"DONE: {era} S4.5 (combine) completed successfully")
            self.state.update_era(era, "4.5", "done", 0)
            return True
        else:
            self.log(f"FAILED: {era} S4.5 (combine) exited with code {process.returncode}", "ERROR")
            self.state.update_era(era, "4.5", "failed", 0)
            return False

    def run_combine_datacard(self) -> bool:
        """
        Run Stage 4.4.1: Combine 4 eras into 1-channel Run2 datacard.

        This is a sync point - requires all eras to have completed Stage 4.4.
        Uses CMSSW environment for combineCards.py.

        Returns:
            True if successful, False otherwise
        """
        config = self.state.get_config()
        channel = self.state.get_channel()

        if not config or not channel:
            self.log("Error: Workflow not initialized", "ERROR")
            return False

        self.log(f"STARTING: S4.4.1 (combineDatacard) - combining 4 eras for {channel}")

        # Build command with CMSSW environment
        cmd = f'''
cd {self.project_root}/hua/combine/
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
python3 writeCombinationDatacard.py --config ../../{config} --channel {channel} --quiet
'''

        try:
            result = subprocess.run(
                ['bash', '-c', cmd],
                cwd=self.project_root,
                capture_output=True,
                text=True,
                timeout=600  # 10 minute timeout
            )

            if result.returncode == 0:
                self.log(f"DONE: S4.4.1 (combineDatacard) for {channel}")
                # Update all eras to 4.4.1 done
                for era in self.state.get_eras():
                    self.state.update_era(era, "4.4.1", "done", 0)
                return True
            else:
                self.log(f"FAILED: S4.4.1 (combineDatacard)", "ERROR")
                self.log(f"stderr: {result.stderr[:500]}", "ERROR")
                return False

        except subprocess.TimeoutExpired:
            self.log(f"TIMEOUT: S4.4.1 (combineDatacard) exceeded 10 minutes", "ERROR")
            return False
        except Exception as e:
            self.log(f"Error running combineDatacard: {e}", "ERROR")
            return False

    def get_next_stage(self, current_stage: str) -> Optional[str]:
        """Get next stage in sequence."""
        try:
            idx = self.STAGE_ORDER.index(current_stage)
            if idx + 1 < len(self.STAGE_ORDER):
                return self.STAGE_ORDER[idx + 1]
        except ValueError:
            pass
        return None

    def run(self, eras: Optional[List[str]] = None,
            start_stage: Optional[str] = None) -> bool:
        """
        Run automation loop for specified eras.

        Args:
            eras: List of eras to process (default: all from state)
            start_stage: Override starting stage (default: from state)

        Returns:
            True if all completed successfully, False otherwise
        """
        if eras is None:
            eras = list(self.state.state.get("eras", {}).keys())

        if not eras:
            self.log("No eras specified and none in state file", "ERROR")
            return False

        self.log(f"Starting automation for eras: {', '.join(eras)}")
        self.log(f"Poll interval: {self.poll_interval}s, Max wait: {self.max_wait}s")

        all_success = True

        for era in eras:
            self.log(f"\n{'='*60}")
            self.log(f"Processing era: {era}")
            self.log(f"{'='*60}")

            era_state = self.state.get_era_status(era)
            current_stage = start_stage or era_state.get("stage", "1")
            status = era_state.get("status", "pending")

            # If start_stage is explicitly provided, treat as pending to run that stage
            if start_stage and start_stage != era_state.get("stage"):
                status = "pending"

            # Handle running state - wait for completion first
            if status == "running" and current_stage in self.JOB_STAGES:
                self.log(f"Found {era} S{current_stage} in running state, waiting...")
                if not self.wait_for_jobs(era, current_stage):
                    all_success = False
                    continue
                status = "done"

            # Progress through stages
            while True:
                # Determine next stage
                if status == "done":
                    next_stage = self.get_next_stage(current_stage)
                else:
                    next_stage = current_stage

                if next_stage is None or next_stage == "complete":
                    self.log(f"{era}: All stages complete!")
                    self.state.mark_complete(era)
                    break

                # Handle Stage 4.4.1 specially (combineDatacard - sync point)
                if next_stage == "4.4.1":
                    # Check if all eras are at 4.4 done before running
                    all_eras_ready = all(
                        self.state.get_era_status(e).get("stage") == "4.4" and
                        self.state.get_era_status(e).get("status") == "done"
                        for e in self.state.get_eras()
                    )
                    if not all_eras_ready:
                        self.log(f"Skipping {era} S4.4.1 - not all eras at S4.4 done yet")
                        break
                    if not self.run_combine_datacard():
                        all_success = False
                        break
                # Handle Stage 4.5 specially (combine fits)
                elif next_stage == "4.5":
                    if not self.run_combine(era):
                        all_success = False
                        break
                else:
                    # Submit/run the stage
                    if not self.submit_stage(era, next_stage):
                        all_success = False
                        break

                    # Wait for job stages
                    if next_stage in self.JOB_STAGES:
                        if not self.wait_for_jobs(era, next_stage):
                            all_success = False
                            break

                current_stage = next_stage
                status = "done"

        self.log(f"\n{'='*60}")
        if all_success:
            self.log("Workflow automation completed successfully!")
        else:
            self.log("Workflow automation completed with errors", "WARNING")
        self.log(f"{'='*60}")

        return all_success


def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(
        description='Workflow Automation V3',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    # Mode selection
    mode_group = parser.add_mutually_exclusive_group()
    mode_group.add_argument('--init', action='store_true',
                           help='Initialize workflow state')
    mode_group.add_argument('--run', action='store_true',
                           help='Run automation')
    mode_group.add_argument('--resume', action='store_true',
                           help='Resume from current state')
    mode_group.add_argument('--status', action='store_true',
                           help='Show current status')

    # Initialization options
    parser.add_argument('--channel', type=str,
                       help='Channel (1tau0l, 1tau1l, 1tau2l)')
    parser.add_argument('--config', type=str,
                       help='Config file path')
    parser.add_argument('--eras', nargs='+',
                       help='Eras to process')
    parser.add_argument('--start-stage', type=str,
                       help='Starting stage')

    # Runtime options
    parser.add_argument('--poll-interval', type=int, default=60,
                       help='Job poll interval in seconds (default: 60)')
    parser.add_argument('--max-wait', type=int, default=14400,
                       help='Max wait for jobs in seconds (default: 14400 = 4h)')
    parser.add_argument('--log', type=str,
                       help='Log file path (default: .workflow/auto_TIMESTAMP.log)')

    args = parser.parse_args()

    if args.init:
        if not all([args.channel, args.config, args.eras]):
            print("Error: --init requires --channel, --config, and --eras")
            return 1
        state = CompactWorkflowState()
        state.initialize(args.channel, args.config, args.eras,
                        args.start_stage or '1')
        print(f"Initialized workflow for {args.channel}")
        print(f"State file: .workflow/state.json")
        return 0

    elif args.status:
        state = CompactWorkflowState()
        print(f"Channel: {state.get_channel()}")
        print(f"Config: {state.get_config()}")
        print(f"Status: {state.get_summary()}")
        print(f"Next: {state.get_next_action()}")
        cmd = state.get_next_command()
        if cmd:
            print(f"Cmd: {cmd}")
        return 0

    elif args.run or args.resume:
        auto = WorkflowAutomation(
            poll_interval=args.poll_interval,
            max_wait=args.max_wait,
            log_file=args.log
        )
        success = auto.run(
            eras=args.eras,
            start_stage=args.start_stage
        )
        return 0 if success else 1

    else:
        # Default: show status
        state = CompactWorkflowState()
        print(state.get_summary())
        print(f"\nUse --help for options")
        return 0


if __name__ == '__main__':
    sys.exit(main())
