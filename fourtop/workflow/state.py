"""
Workflow State Tracking
=======================

Track workflow execution state across sessions for multi-session continuity.

Usage:
    from fourtop.workflow.state import WorkflowState, get_workflow_state

    state = get_workflow_state('1tau0l', 'config/analysis_config.yaml')
    state.update_stage('3.1', '2018', 'running', 'WH_systematics')

    # Later session
    current = state.get_current()  # Returns current stage info
"""

import json
from pathlib import Path
from datetime import datetime
from typing import Dict, Any, Optional


class WorkflowState:
    """
    Track workflow execution state across sessions.

    Persists pipeline state to .workflow_state.json for:
    - Knowing current stage/era after long waits (2-3 hour jobs)
    - Enabling hooks to inject context automatically
    - Multi-session continuity

    Attributes:
        project_root: Path to FourTop project root.
        state_file: Path to state JSON file.
        channel: Current analysis channel.
        config_path: Path to config file used.
    """

    def __init__(self, channel: Optional[str] = None, config_path: Optional[str] = None):
        """
        Initialize workflow state tracker.

        Args:
            channel: Analysis channel (1tau0l, 1tau1l, 1tau2l)
            config_path: Path to config file used
        """
        self.project_root = Path(__file__).parent.parent.parent
        self.state_file = self.project_root / '.workflow_state.json'
        self.channel = channel
        self.config_path = config_path
        self._load()

    def _load(self) -> None:
        """Load state from JSON file, create if doesn't exist."""
        if self.state_file.exists():
            with open(self.state_file) as f:
                self.state = json.load(f)
        else:
            self.state = {
                'channels': {},
                'history': []
            }

        # Ensure channel exists in state
        if self.channel and self.channel not in self.state['channels']:
            self.state['channels'][self.channel] = {
                'config': self.config_path,
                'current': None,
                'stage_status': {}
            }

    def _save(self) -> None:
        """Save state to JSON file atomically."""
        # Write to temp file first, then rename (atomic on POSIX)
        temp_file = self.state_file.with_suffix('.json.tmp')
        with open(temp_file, 'w') as f:
            json.dump(self.state, f, indent=2)
        temp_file.replace(self.state_file)

    def update_stage(self, stage: str, era: str, status: str,
                     operation: Optional[str] = None) -> None:
        """
        Update current stage status for the channel.

        Args:
            stage: Stage number (e.g., '3.1', '4.2')
            era: Analysis era (2018, 2017, etc.)
            status: Status string ('running', 'completed', 'failed')
            operation: Optional operation description
        """
        if not self.channel:
            raise ValueError("Channel must be set to update stage")

        channel_state = self.state['channels'][self.channel]
        channel_state['current'] = {
            'stage': stage,
            'era': era,
            'status': status,
            'operation': operation,
            'timestamp': datetime.utcnow().isoformat()
        }

        # Update stage_status matrix
        if stage not in channel_state['stage_status']:
            channel_state['stage_status'][stage] = {}
        channel_state['stage_status'][stage][era] = status

        self._save()

    def get_current(self, channel: Optional[str] = None) -> Optional[Dict[str, Any]]:
        """
        Get current pipeline state for a channel.

        Args:
            channel: Channel to query (uses self.channel if not provided)

        Returns:
            Dictionary with stage, era, status, operation, timestamp
            or None if no current state
        """
        ch = channel or self.channel
        if not ch or ch not in self.state['channels']:
            return None
        return self.state['channels'][ch].get('current')

    def get_stage_status(self, stage: str, era: str,
                         channel: Optional[str] = None) -> str:
        """
        Get status of a specific stage/era combination.

        Args:
            stage: Stage number (e.g., '3.1')
            era: Analysis era
            channel: Channel to query (uses self.channel if not provided)

        Returns:
            Status string ('pending', 'running', 'completed', 'failed')
        """
        ch = channel or self.channel
        if not ch or ch not in self.state['channels']:
            return 'pending'

        return (self.state['channels'][ch]
                .get('stage_status', {})
                .get(stage, {})
                .get(era, 'pending'))

    def log_execution(self, stage: str, era: str, operation: str,
                      status: str, **kwargs) -> None:
        """
        Log an execution event to history.

        Args:
            stage: Stage number
            era: Analysis era
            operation: Operation description
            status: Status ('started', 'completed', 'failed')
            **kwargs: Additional fields (duration, error, output_files, etc.)
        """
        entry = {
            'timestamp': datetime.utcnow().isoformat(),
            'channel': self.channel,
            'stage': stage,
            'era': era,
            'operation': operation,
            'status': status,
            **kwargs
        }
        self.state['history'].append(entry)

        # Keep only last 100 history entries to avoid bloat
        if len(self.state['history']) > 100:
            self.state['history'] = self.state['history'][-100:]

        self._save()


def get_workflow_state(channel: Optional[str] = None,
                       config_path: Optional[str] = None) -> WorkflowState:
    """
    Convenience function to get workflow state tracker.

    Args:
        channel: Analysis channel (1tau0l, 1tau1l, 1tau2l)
        config_path: Path to config file

    Returns:
        WorkflowState instance

    Example:
        state = get_workflow_state('1tau0l', 'config/analysis_config_1tau0l.yaml')
        state.update_stage('3.1', '2018', 'running', 'WH_systematics')
    """
    return WorkflowState(channel=channel, config_path=config_path)
