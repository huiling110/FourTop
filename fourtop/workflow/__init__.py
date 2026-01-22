"""
FourTop Workflow Package
========================

Configuration loading, path building, and workflow state tracking.

Modules:
    config - YAML configuration loading and validation
    paths - Path builders for all analysis stages
    state - Workflow state tracking across sessions
"""

from fourtop.workflow.config import (
    load_config,
    get_channel,
    get_eras,
    get_options,
    get_regions,
    get_versions,
    get_template_suffix,
)
from fourtop.workflow.paths import (
    build_hist_path,
    build_hist_path_jes,
    build_template_path,
    build_datacard_path,
    build_stage1_input,
    build_stage1_output,
    build_stage2_path,
    build_stage2_output,
    build_combine_path,
)
