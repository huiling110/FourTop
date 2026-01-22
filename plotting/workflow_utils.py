"""
Workflow utilities for FourTop analysis - THIN WRAPPER.

This module provides backward-compatible imports from the fourtop package.
All implementations are now in fourtop.workflow.

Usage:
    from workflow_utils import load_config, build_hist_path, build_stage2_path

    config = load_config('config/analysis_config.yaml')
    hist_path = build_hist_path(config, '2018')

Standalone script usage:
    python3 script.py --config config/analysis_config.yaml --era 2018

NOTE: This is a thin wrapper for backward compatibility.
      New code should import directly from fourtop.workflow.
"""

# Re-export everything from fourtop.workflow
from fourtop.workflow import (
    # Config functions
    load_config,
    get_channel,
    get_eras,
    get_options,
    get_regions,
    get_versions,
    get_template_suffix,

    # Path builders
    build_hist_path,
    build_hist_path_jes,
    build_template_path,
    build_datacard_path,
    build_stage1_input,
    build_stage1_output,
    build_stage2_path,
    build_stage2_output,
    build_stage2_output_jes,
    build_combine_path,
    build_combination_path,
    get_channel_if1tau2l,

    # Era mappings
    ERA_TO_UL,
    ERA_TO_NANOAOD,

    # Workflow state
    WorkflowState,
    get_workflow_state,
)

# For backward compatibility, ensure typing is available
from typing import Dict, Any, Optional, List

__all__ = [
    # Config functions
    'load_config',
    'get_channel',
    'get_eras',
    'get_options',
    'get_regions',
    'get_versions',
    'get_template_suffix',
    # Path builders
    'build_hist_path',
    'build_hist_path_jes',
    'build_template_path',
    'build_datacard_path',
    'build_stage1_input',
    'build_stage1_output',
    'build_stage2_path',
    'build_stage2_output',
    'build_stage2_output_jes',
    'build_combine_path',
    'build_combination_path',
    'get_channel_if1tau2l',
    # Era mappings
    'ERA_TO_UL',
    'ERA_TO_NANOAOD',
    # Workflow state
    'WorkflowState',
    'get_workflow_state',
]
