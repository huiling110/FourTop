"""
Path Building Functions
=======================

Build paths to analysis outputs for all stages.

All path functions follow consistent patterns:
- Take config dict and era as primary arguments
- Return paths with trailing slashes for directories
- Support systematic variations where applicable

Usage:
    from fourtop.workflow.paths import build_hist_path, build_template_path

    hist_path = build_hist_path(config, '2018')
    template_path = build_template_path(config, '2018')
"""

import os
from typing import Dict, Any, Optional

from fourtop.constants.era import ERA_TO_UL, ERA_TO_NANOAOD
from fourtop.workflow.config import get_channel, get_template_suffix


def build_stage1_input(config: Dict[str, Any], era: str) -> str:
    """
    Build path to Stage 1 input directory (NanoAOD).

    Pattern: {nanoaod_base}/{nanoaod_era}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).

    Returns:
        Full path to NanoAOD input directory (with trailing /).
    """
    nanoaod_base = config['paths'].get('nanoaod_base', '/publicfs/cms/data/TopQuark/nanoAOD')
    nanoaod_era = ERA_TO_NANOAOD.get(era, era)
    return os.path.join(nanoaod_base, nanoaod_era) + '/'


def build_stage1_output(config: Dict[str, Any], era: str, systematic: Optional[str] = None) -> str:
    """
    Build path to Stage 1 output directory (object selection).

    Pattern: {output_base_os}/{UL_era}/{stage1_version}[_systematic]/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).
        systematic: Optional systematic variation suffix (e.g., 'JESUp', 'JERDown').

    Returns:
        Full path to Stage 1 output directory (with trailing /).
    """
    # Stage 1 uses a different base path than Stage 2+
    output_base = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD'
    ul_era = ERA_TO_UL.get(era, f'UL{era}')
    version = config['versions']['stage1']
    if systematic:
        version = f"{version}_{systematic}"
    return os.path.join(output_base, ul_era, version) + '/'


def get_channel_if1tau2l(config: Dict[str, Any]) -> int:
    """
    Get if1tau2l flag from channel (for Stage 1 executable).

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        1 for 1tau2l channel, 0 for others.
    """
    channel = get_channel(config)
    return 1 if '1tau2l' in channel else 0


def build_stage2_path(config: Dict[str, Any], era: str) -> str:
    """
    Build path to Stage 2 output directory (variables for BDT).

    Pattern: {output_base}/{era}/{stage2_version}_{stage1_version}/mc/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).

    Returns:
        Full path to Stage 2 mc directory (with trailing /).
    """
    paths = config['paths']
    versions = config['versions']
    path = os.path.join(
        paths['output_base'],
        era,
        f"{versions['stage2']}_{versions['stage1']}",
        'mc'
    )
    return path + '/'


def build_stage2_output(config: Dict[str, Any], era: str, systematic: Optional[str] = None,
                        data_type: str = 'mc') -> str:
    """
    Build path to Stage 2 output directory with systematic support.

    Pattern: {output_base}/{era}/{stage2_version}_{stage1_version}[_systematic]/{data_type}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).
        systematic: Optional systematic variation suffix (e.g., 'JERUp', 'TESdm0Down').
        data_type: 'mc' or 'data' (default: 'mc').

    Returns:
        Full path to Stage 2 output directory (with trailing /).
    """
    paths = config['paths']
    versions = config['versions']
    stage1_version = versions['stage1']
    if systematic:
        stage1_version = f"{stage1_version}_{systematic}"
    path = os.path.join(
        paths['output_base'],
        era,
        f"{versions['stage2']}_{stage1_version}",
        data_type
    )
    return path + '/'


def build_stage2_output_jes(config: Dict[str, Any], era: str, jes_direction: str,
                            jes_source: str, data_type: str = 'mc') -> str:
    """
    Build path to Stage 2 output directory for JES variations.

    JES has a special format: {stage2}_JES{up/Down}_{source}_{stage1}_JESPt22/{data_type}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).
        jes_direction: 'up' or 'Down' (case matters for path matching).
        jes_source: JES source name (e.g., 'AbsoluteMPFBias_AK4PFchs').
        data_type: 'mc' or 'data' (default: 'mc').

    Returns:
        Full path to Stage 2 output directory for JES variation (with trailing /).
    """
    paths = config['paths']
    versions = config['versions']
    stage1_version = versions['stage1']
    stage2_version = versions['stage2']

    # Format: {stage2}_JES{up/Down}_{source}_{stage1}_JESPt22
    dir_name = f"{stage2_version}_JES{jes_direction}_{jes_source}_{stage1_version}_JESPt22"

    path = os.path.join(
        paths['output_base'],
        era,
        dir_name,
        data_type
    )
    return path + '/'


def build_hist_path(config: Dict[str, Any], era: str) -> str:
    """
    Build path to histogram directory for a given era.

    Pattern: {stage2_path}/variableHists_{hist_version}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).

    Returns:
        Full path to histogram directory (with trailing /).
    """
    stage2_path = build_stage2_path(config, era).rstrip('/')
    hist_version = config['versions']['hist']
    return os.path.join(stage2_path, f"variableHists_{hist_version}") + '/'


def build_hist_path_jes(config: Dict[str, Any], era: str, jes_direction: str,
                        jes_source: str) -> str:
    """
    Build path to histogram directory for JES systematic variations.

    Pattern: {stage2_jes_path}/variableHists_{hist_version}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).
        jes_direction: 'up' or 'Down' (case matters for path matching).
        jes_source: JES source name (e.g., 'AbsoluteMPFBias_AK4PFchs').

    Returns:
        Full path to JES histogram directory (with trailing /).
    """
    stage2_jes_path = build_stage2_output_jes(config, era, jes_direction, jes_source).rstrip('/')
    hist_version = config['versions']['hist']
    return os.path.join(stage2_jes_path, f"variableHists_{hist_version}") + '/'


def build_combine_path(config: Dict[str, Any], era: str) -> str:
    """
    Build path to combine directory for a given era.

    Pattern: {hist_path}/combine/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string.

    Returns:
        Full path to combine directory (with trailing /).
    """
    hist_path = build_hist_path(config, era).rstrip('/')
    return os.path.join(hist_path, 'combine') + '/'


def build_template_path(
    config: Dict[str, Any],
    era: str,
    channel: Optional[str] = None,
    suffix: Optional[str] = None,
    smoothed: bool = False
) -> str:
    """
    Build path to template ROOT file for combine.

    Pattern: {combine_path}/templatesForCombine{channel}{suffix}.root

    Args:
        config: Configuration dictionary from load_config().
        era: Era string.
        channel: Channel name. If None, uses config channel.
        suffix: Optional suffix. If None, builds from config options.
        smoothed: If True, append '_smoothed' before .root.

    Returns:
        Full path to template ROOT file.
    """
    combine_path = build_combine_path(config, era)
    if channel is None:
        channel = get_channel(config)
    if suffix is None:
        suffix = get_template_suffix(config)
    filename = f"templatesForCombine{channel}{suffix}"
    if smoothed:
        filename += '_smoothed'
    filename += '.root'
    return os.path.join(combine_path, filename)


def build_datacard_path(config: Dict[str, Any], era: str) -> str:
    """
    Build path to datacard output directory.

    Pattern: {combine_path}/datacardSys_{datacard_version}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string.

    Returns:
        Full path to datacard directory (with trailing /).
    """
    combine_path = build_combine_path(config, era).rstrip('/')
    datacard_version = config['versions'].get('datacard', 'v1')
    return os.path.join(combine_path, f"datacardSys_{datacard_version}") + '/'


def build_combination_path(config: Dict[str, Any]) -> str:
    """
    Build path to combination output directory (Stage 4.4/4.5).

    Pattern: hua/combine/{combination_version}/run2_{channel}_{datacard_version}/

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Relative path to combination directory (with trailing /).
    """
    versions = config['versions']
    channel = get_channel(config)
    comb_version = versions.get('combination', 'combinationV21')
    dc_version = versions.get('datacard', 'v1')
    return f"hua/combine/{comb_version}/run2_{channel}_{dc_version}/"
