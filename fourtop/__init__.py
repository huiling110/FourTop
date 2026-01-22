"""
FourTop Analysis Python Package
===============================

Centralized utilities for CMS four-top (tttt) measurement and VLL search
in hadronic tau channels.

Subpackages:
    constants - Physics constants, systematic definitions, era mappings
    utils - File I/O, histogram operations, process filtering
    workflow - Configuration loading, path building, state tracking
    plotting - ROOT plotting utilities, validation plots
    stage4 - Template generation, datacards, combine fits
    jobs - Job submission utilities

Usage:
    from fourtop.workflow import config, paths
    from fourtop.constants import physics, systematics
    from fourtop.utils import histogram, process

    cfg = config.load_config('config/analysis_config_1tau0l.yaml')
    hist_path = paths.build_hist_path(cfg, '2018')
"""

__version__ = '1.0.0'
__author__ = 'FourTop Analysis Team'

# Convenience imports
from fourtop.workflow.config import load_config
from fourtop.workflow.paths import (
    build_hist_path,
    build_template_path,
    build_datacard_path,
    build_stage1_output,
    build_stage2_path,
)
