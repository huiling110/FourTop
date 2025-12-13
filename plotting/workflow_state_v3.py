#!/usr/bin/env python3
"""
Compact Workflow State Manager (V3)

Provides simple per-era status tracking for the FourTop analysis workflow.
Designed for easy reading/debugging and hook integration.

Key Feature: Stores concrete paths in state.json for immediate access
without needing to read config or build paths manually.

Usage:
    from workflow_state_v3 import CompactWorkflowState

    state = CompactWorkflowState()
    state.initialize('1tau1l', 'config/analysis_config_1tau1l_TTBBtest.yaml', ['2017'])
    state.update_era('2017', '3', 'running', jobs=897)
    print(state.get_summary())

    # Get concrete paths for an era
    paths = state.get_era_paths('2017')
    print(paths['hist_dir'])  # Full path to histogram directory
"""

import json
import os
from datetime import datetime
from pathlib import Path
from typing import Dict, List, Optional

# Import workflow_utils for path building
try:
    import sys
    # Add plotting directory to path if needed
    plotting_dir = Path(__file__).resolve().parent
    if str(plotting_dir) not in sys.path:
        sys.path.insert(0, str(plotting_dir))
    from workflow_utils import load_config, build_hist_path, build_stage2_path
    HAS_WORKFLOW_UTILS = True
except ImportError:
    HAS_WORKFLOW_UTILS = False


class CompactWorkflowState:
    """Compact workflow state manager for V3."""

    STATE_DIR = ".workflow"
    STATE_FILE = "state.json"

    # Stage order for progression
    # Per-era stages: 1-4.4, then sync point 4.4.1, then 4.5-4.7
    STAGE_ORDER = ['1', '1.1', '2', '2.1', '3', '3.1', '4.1', '4.2', '4.3', '4.4', '4.4.1', '4.5', '4.6', '4.7', 'complete']

    # Stages that require all eras to complete before proceeding
    SYNC_STAGES = ['4.4.1']  # Run2 combination needs all 4 eras

    # Human-readable stage names
    STAGE_NAMES = {
        '1': 'OS nominal',
        '1.1': 'OS systematics',
        '2': 'MV nominal',
        '2.1': 'MV systematics',
        '3': 'WH nominal',
        '3.1': 'WH systematics',
        '4.1': 'addJES',
        '4.2': 'addTemplate',
        '4.3': 'smooth',
        '4.4': 'writeDatacard',
        '4.4.1': 'Run2 combination',
        '4.5': 'combine fits',
        '4.6': 'postfit',
        '4.7': 'plots',
        'complete': 'done'
    }

    def __init__(self, project_root: Optional[str] = None):
        """
        Initialize state manager.

        Args:
            project_root: Project root directory. Auto-detected if None.
        """
        if project_root:
            self.project_root = Path(project_root)
        else:
            # Auto-detect: look for FourTop directory
            current = Path(__file__).resolve().parent
            while current.name != 'FourTop' and current != current.parent:
                current = current.parent
            self.project_root = current

        self.state_dir = self.project_root / self.STATE_DIR
        self.state_file = self.state_dir / self.STATE_FILE
        self._ensure_directory()
        self._load()

    def _ensure_directory(self):
        """Create .workflow directory if needed."""
        self.state_dir.mkdir(exist_ok=True)

    def _load(self):
        """Load state from file or create default."""
        if self.state_file.exists():
            try:
                with open(self.state_file) as f:
                    self.state = json.load(f)
            except json.JSONDecodeError:
                print(f"Warning: Invalid state file, creating new")
                self.state = self._default_state()
        else:
            self.state = self._default_state()

    def _default_state(self) -> Dict:
        """Return default empty state."""
        return {
            "channel": None,
            "config": None,
            "eras": {},
            "next_action": "initialize workflow",
            "last_update": self._timestamp(),
            "version": "v3"
        }

    def _timestamp(self) -> str:
        """Get current ISO timestamp."""
        return datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%SZ")

    def _save(self):
        """Save state to file."""
        self.state["last_update"] = self._timestamp()
        with open(self.state_file, 'w') as f:
            json.dump(self.state, f, indent=2)

    def initialize(self, channel: str, config: str, eras: List[str],
                   start_stage: str = '1') -> None:
        """
        Initialize workflow for a channel.

        Automatically computes and stores concrete paths for each era.

        Args:
            channel: Analysis channel (1tau0l, 1tau1l, 1tau2l)
            config: Path to config file
            eras: List of eras to process
            start_stage: Starting stage (default: '1')
        """
        self.state = {
            "channel": channel,
            "config": config,
            "eras": {
                era: {"stage": start_stage, "status": "pending", "jobs": 0}
                for era in eras
            },
            "next_action": f"submit {eras[0]} stage {start_stage}",
            "last_update": self._timestamp(),
            "version": "v3"
        }
        self._save()

        # Compute and store paths for each era (V3.1 enhancement)
        self.refresh_paths()

        print(f"Initialized workflow for {channel} with eras: {', '.join(eras)}")
        if self.state.get("versions"):
            print(f"  Hist version: {self.state['versions'].get('hist', 'N/A')}")

    def update_era(self, era: str, stage: str, status: str, jobs: int = 0) -> None:
        """
        Update single era status.

        Args:
            era: Era to update (2017, 2018, 2016preVFP, 2016postVFP)
            stage: Current stage (1, 1.1, 2, 2.1, 3, 3.1, 4.1-4.6, complete)
            status: Status (pending, submitting, running, done, failed)
            jobs: Number of jobs (for running status)
        """
        if era not in self.state["eras"]:
            self.state["eras"][era] = {}

        self.state["eras"][era] = {
            "stage": stage,
            "status": status,
            "jobs": jobs,
            "updated": self._timestamp()
        }

        self._update_next_action()
        self._save()

    def get_era_status(self, era: str) -> Dict:
        """Get status for single era."""
        return self.state["eras"].get(era, {"stage": "0", "status": "unknown"})

    def get_channel(self) -> Optional[str]:
        """Get current channel."""
        return self.state.get("channel")

    def get_config(self) -> Optional[str]:
        """Get config file path."""
        return self.state.get("config")

    def get_summary(self) -> str:
        """
        Get one-line summary for hook injection.

        Returns:
            Summary string like "Channel: 1tau1l | 2017: S3 running (897) | 2018: complete"
        """
        channel = self.state.get("channel", "unknown")
        parts = [f"Channel: {channel}"]

        for era in sorted(self.state.get("eras", {}).keys()):
            info = self.state["eras"][era]
            stage = info.get("stage", "?")
            status = info.get("status", "?")
            jobs = info.get("jobs", 0)

            stage_name = self.STAGE_NAMES.get(stage, stage)

            if stage == "complete":
                parts.append(f"{era}: complete")
            elif jobs > 0 and status == "running":
                parts.append(f"{era}: S{stage} {status} ({jobs} jobs)")
            else:
                parts.append(f"{era}: S{stage} {status}")

        return " | ".join(parts)

    def get_next_action(self) -> str:
        """Get next action description."""
        return self.state.get("next_action", "check status")

    def get_next_command(self) -> Optional[str]:
        """
        Get suggested next command based on state.

        Returns:
            Command string or None if no suggestion
        """
        config = self.state.get("config", "CONFIG")
        channel = self.state.get("channel", "CHANNEL")

        for era in sorted(self.state.get("eras", {}).keys()):
            info = self.state["eras"][era]
            status = info.get("status", "unknown")
            stage = info.get("stage", "0")

            if status == "running":
                return f"hep_q -u $USER  # Check {era} S{stage} jobs"

            if status == "pending" or status == "done":
                next_stage = self._get_next_stage(stage) if status == "done" else stage
                if next_stage:
                    return self._get_stage_command(next_stage, era, config, channel)

        return None

    def _update_next_action(self):
        """Determine next action from era states."""
        # Check for running jobs first
        for era in sorted(self.state.get("eras", {}).keys()):
            info = self.state["eras"][era]
            if info.get("status") == "running":
                stage = info.get("stage", "?")
                jobs = info.get("jobs", 0)
                self.state["next_action"] = f"wait for {era} S{stage} jobs ({jobs} running)"
                return

        # Find first incomplete era
        for era in sorted(self.state.get("eras", {}).keys()):
            info = self.state["eras"][era]
            stage = info.get("stage", "0")
            status = info.get("status", "unknown")

            if stage == "complete":
                continue

            if status == "done":
                next_stage = self._get_next_stage(stage)
                if next_stage:
                    self.state["next_action"] = f"run {era} S{next_stage} ({self.STAGE_NAMES.get(next_stage, next_stage)})"
                    return
            else:
                self.state["next_action"] = f"run {era} S{stage} ({self.STAGE_NAMES.get(stage, stage)})"
                return

        self.state["next_action"] = "all eras complete"

    def _get_next_stage(self, current_stage: str) -> Optional[str]:
        """Get next stage in sequence."""
        try:
            idx = self.STAGE_ORDER.index(current_stage)
            if idx + 1 < len(self.STAGE_ORDER):
                return self.STAGE_ORDER[idx + 1]
        except ValueError:
            pass
        return None

    def _get_stage_command(self, stage: str, era: str, config: str, channel: str) -> str:
        """Get command for a specific stage."""
        commands = {
            '1': f"python3 objectSelectionOptimized/jobs/makeJob_OS_fromRuobing2.py --config {config} --era {era}",
            '1.1': f"bash objectSelectionOptimized/jobs/submit_all_systematics.sh {config} {era}",
            '2': f"python3 makeVariables_goodCode/jobs/makeJob_makeVaribles_forBDT.py --config {config} --era {era}",
            '2.1': f"python3 makeVariables_goodCode/jobs/makeJob_MV_JESVariation.py --config {config} --era {era}",
            '3': f"python3 writeHistGood/jobs/makeJob_WH.py --config {config} --era {era} --systematic nominal",
            '3.1': f"python3 writeHistGood/jobs/makeJob_WH.py --config {config} --era {era} --systematic all",
            '4.1': f"python3 plotting/addJESTemplatesToHistFile.py --config {config} --era {era} --execute --quiet",
            '4.2': f"python3 plotting/addTemplateNew.py --config {config} --era {era} --quiet",
            '4.3': f"python3 plotting/writeDatacard.py --config {config} --era {era}",
            '4.4': f"python3 plotting/pl.py --config {config} --era {era}",
            '4.5': f"cd hua/combine/ && bash run_combine_fits.sh ../../{config} {era} {channel}",
            '4.6': f"python3 plotting/pl_postFit.py --config {config} --era {era}",
        }
        return commands.get(stage, f"# Unknown stage {stage}")

    def mark_complete(self, era: str) -> None:
        """Mark an era as complete."""
        self.update_era(era, "complete", "done", 0)

    def to_dict(self) -> Dict:
        """Return state as dictionary."""
        return self.state.copy()

    def __str__(self) -> str:
        """String representation."""
        return self.get_summary()

    # =========================================================================
    # Path Management (V3.1 Enhancement)
    # =========================================================================

    def compute_paths(self, era: str, config: Dict = None) -> Dict[str, str]:
        """
        Compute concrete paths for an era from config.

        Args:
            era: Era string (2017, 2018, 2016preVFP, 2016postVFP)
            config: Config dict (loaded if not provided)

        Returns:
            Dictionary with paths:
            - hist_dir: Histogram output directory
            - log_dir: Job log directory
            - job_dir: Job script directory
            - templates: Template file pattern
        """
        if not HAS_WORKFLOW_UTILS:
            return {"error": "workflow_utils not available"}

        # Load config if not provided
        if config is None:
            config_path = self.state.get("config")
            if not config_path:
                return {"error": "no config in state"}
            # Make path absolute if relative
            if not os.path.isabs(config_path):
                config_path = self.project_root / config_path
            config = load_config(str(config_path))

        channel = config.get('channel', self.state.get('channel', '1tau1l'))

        # Build paths
        hist_dir = build_hist_path(config, era).rstrip('/')

        return {
            "hist_dir": hist_dir,
            "log_dir": f"{hist_dir}/log",
            "job_dir": f"{hist_dir}/jobSH",
            "combine_dir": f"{hist_dir}/combine",
            "templates": f"{hist_dir}/combine/templatesForCombine{channel}_*.root",
            "channel": channel,
        }

    def refresh_paths(self) -> None:
        """
        Recompute and store paths for all eras in state.

        Call this after config changes or to ensure paths are current.
        """
        config_path = self.state.get("config")
        if not config_path or not HAS_WORKFLOW_UTILS:
            return

        # Load config once
        try:
            if not os.path.isabs(config_path):
                config_path = str(self.project_root / config_path)
            config = load_config(config_path)
        except Exception as e:
            print(f"Warning: Could not load config: {e}")
            return

        # Store versions for reference
        self.state["versions"] = {
            "stage1": config['versions'].get('stage1', ''),
            "stage2": config['versions'].get('stage2', ''),
            "hist": config['versions'].get('hist', ''),
        }

        # Compute paths for each era
        for era in self.state.get("eras", {}).keys():
            paths = self.compute_paths(era, config)
            if "error" not in paths:
                self.state["eras"][era]["paths"] = paths

        self._save()

    def get_era_paths(self, era: str) -> Dict[str, str]:
        """
        Get stored paths for an era.

        Returns cached paths from state, or computes them if not stored.

        Args:
            era: Era string

        Returns:
            Dictionary with hist_dir, log_dir, job_dir, templates keys
        """
        era_info = self.state.get("eras", {}).get(era, {})
        paths = era_info.get("paths")

        if paths and "hist_dir" in paths:
            return paths

        # Compute if not stored
        paths = self.compute_paths(era)
        if "error" not in paths:
            # Store for future use
            if era in self.state.get("eras", {}):
                self.state["eras"][era]["paths"] = paths
                self._save()
        return paths

    def get_verification_commands(self, era: str) -> Dict[str, str]:
        """
        Get commands to verify job completion for an era.

        Args:
            era: Era string

        Returns:
            Dictionary with verification commands
        """
        paths = self.get_era_paths(era)
        if "error" in paths:
            return {"error": paths["error"]}

        hist_dir = paths["hist_dir"]
        channel = paths.get("channel", "1tau1l")
        return {
            "count_histograms": f"ls {hist_dir}/*.root 2>/dev/null | wc -l",
            "count_templates": f"ls {hist_dir}/combine/templatesForCombine{channel}_*.root 2>/dev/null | wc -l",
            "check_errors": f"ls {hist_dir}/log/*.err 2>/dev/null | xargs grep -l 'Error\\|error\\|Segmentation' | head -5",
            "expected_nominal": "71",
            "expected_with_sys": "559+",
        }


def main():
    """CLI for state management."""
    import argparse

    parser = argparse.ArgumentParser(description='Workflow State Manager V3')
    parser.add_argument('--init', action='store_true', help='Initialize workflow')
    parser.add_argument('--channel', type=str, help='Channel (1tau0l, 1tau1l, 1tau2l)')
    parser.add_argument('--config', type=str, help='Config file path')
    parser.add_argument('--eras', nargs='+', help='Eras to process')
    parser.add_argument('--start-stage', type=str, default='1', help='Starting stage')
    parser.add_argument('--status', action='store_true', help='Show current status')
    parser.add_argument('--update', nargs=4, metavar=('ERA', 'STAGE', 'STATUS', 'JOBS'),
                        help='Update era status')
    parser.add_argument('--summary', action='store_true', help='One-line summary')
    parser.add_argument('--next', action='store_true', help='Show next command')
    parser.add_argument('--refresh-paths', action='store_true',
                        help='Recompute and store paths from config')
    parser.add_argument('--paths', type=str, metavar='ERA',
                        help='Show paths for specific era')

    args = parser.parse_args()

    state = CompactWorkflowState()

    if args.init:
        if not all([args.channel, args.config, args.eras]):
            print("Error: --init requires --channel, --config, and --eras")
            return 1
        state.initialize(args.channel, args.config, args.eras, args.start_stage)

    elif args.update:
        era, stage, status, jobs = args.update
        state.update_era(era, stage, status, int(jobs))
        print(f"Updated {era}: stage={stage}, status={status}, jobs={jobs}")

    elif args.summary:
        print(state.get_summary())

    elif args.next:
        cmd = state.get_next_command()
        if cmd:
            print(f"Next: {state.get_next_action()}")
            print(f"Cmd: {cmd}")
        else:
            print("No next command (workflow complete or not initialized)")

    elif args.refresh_paths:
        print("Refreshing paths from config...")
        state.refresh_paths()
        print("Paths updated. Use --paths ERA to view.")

    elif args.paths:
        era = args.paths
        paths = state.get_era_paths(era)
        if "error" in paths:
            print(f"Error: {paths['error']}")
        else:
            print(f"Paths for {era}:")
            for key, value in paths.items():
                print(f"  {key}: {value}")
            print(f"\nVerification commands:")
            verify = state.get_verification_commands(era)
            for key, value in verify.items():
                if not key.startswith("expected"):
                    print(f"  {key}:")
                    print(f"    {value}")
                else:
                    print(f"  {key}: {value}")

    elif args.status:
        print(f"Channel: {state.get_channel()}")
        print(f"Config: {state.get_config()}")
        versions = state.state.get("versions", {})
        if versions:
            print(f"Versions: hist={versions.get('hist', 'N/A')}")
        print(f"Status: {state.get_summary()}")
        print(f"Next: {state.get_next_action()}")
        cmd = state.get_next_command()
        if cmd:
            print(f"Cmd: {cmd}")

    else:
        # Default: show status
        print(state.get_summary())

    return 0


if __name__ == '__main__':
    exit(main())
