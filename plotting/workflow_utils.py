"""
Workflow utilities for FourTop analysis.

Provides functions for loading YAML configuration and building paths
used across plotting and combine scripts.

Supports two config formats:
- New minimal format (versions.stage1, versions.stage2, etc.)
- Legacy format (paths.out_version, paths.in_version, etc.)

Usage:
    from workflow_utils import load_config, build_hist_path, build_stage2_path

    config = load_config('config/analysis_config.yaml')
    hist_path = build_hist_path(config, '2018')

Standalone script usage:
    python3 script.py --config config/analysis_config.yaml --era 2018
"""

import os
import yaml
from typing import Dict, Any, Optional, List


def load_config(config_path: str = None) -> Dict[str, Any]:
    """
    Load analysis configuration from YAML file.

    Args:
        config_path: Path to config YAML. If None, raises error.

    Returns:
        Dictionary containing configuration (normalized to new format).

    Raises:
        FileNotFoundError: If config file doesn't exist.
        ValueError: If config_path is None (--config is required).
        yaml.YAMLError: If YAML parsing fails.
    """
    if config_path is None:
        raise ValueError(
            "Config path is required. Use --config flag.\n"
            "Example: python3 script.py --config config/analysis_config.yaml"
        )

    if not os.path.exists(config_path):
        raise FileNotFoundError(f"Config file not found: {config_path}")

    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)

    # Normalize to new format if using legacy format
    config = _normalize_config(config)
    _validate_config(config)
    return config


def _normalize_config(config: Dict[str, Any]) -> Dict[str, Any]:
    """
    Normalize legacy config format to new minimal format.

    Legacy format uses paths.out_version, paths.in_version, etc.
    New format uses versions.stage1, versions.stage2, etc.
    """
    # Check if already in new format
    if 'versions' in config:
        return config

    # Convert legacy format to new format
    paths = config.get('paths', {})

    # Create versions section from legacy paths
    config['versions'] = {
        'stage1': paths.get('in_version', 'v94HadroPreJetVetoHemOnly'),
        'stage2': paths.get('out_version', 'v1baselineHadro'),
        'hist': paths.get('hist_version', 'v0BDT'),
        'datacard': paths.get('datacard_version', 'v1'),
        'combination': config.get('combination', {}).get('version', 'combinationV21'),
    }

    # Normalize paths section
    config['paths'] = {
        'nanoaod_base': paths.get('nanoaod_base', '/publicfs/cms/data/TopQuark/nanoAOD'),
        'output_base': paths.get('base', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA'),
    }

    # Normalize channel (legacy uses channel.name, new uses channel directly)
    if isinstance(config.get('channel'), dict):
        config['channel'] = config['channel'].get('name', '1tau0l')

    # Normalize options (legacy uses different key names)
    legacy_opts = config.get('options', {})
    config['options'] = {
        'fake_tau': legacy_opts.get('ifFakeTau', legacy_opts.get('fake_tau', True)),
        'mc_fake_tau': legacy_opts.get('ifMCFTau', legacy_opts.get('mc_fake_tau', False)),
        'blind': legacy_opts.get('ifBlind', legacy_opts.get('blind', False)),
        'systematics': legacy_opts.get('systematics', True),
        'smoothing': config.get('smoothing', {}).get('enabled', False),
    }

    return config


def _validate_config(config: Dict[str, Any]) -> None:
    """
    Validate that required config keys exist.

    Raises:
        KeyError: If required keys are missing.
    """
    # Check versions section
    if 'versions' not in config:
        raise KeyError("Config missing 'versions' section")

    required_versions = ['stage1', 'stage2', 'hist']
    for key in required_versions:
        if key not in config['versions']:
            raise KeyError(f"Config missing required version: versions.{key}")

    # Check channel
    if 'channel' not in config:
        raise KeyError("Config missing 'channel'")

    # Check eras
    if 'eras' not in config:
        raise KeyError("Config missing 'eras' list")


# =============================================================================
# Path Building Functions
# =============================================================================

# Era mapping for Stage 1 paths
ERA_TO_UL = {
    '2016postVFP': 'UL2016_postVFP',
    '2016preVFP': 'UL2016_preVFP',
    '2016': 'UL2016_postVFP',
    '2016APV': 'UL2016_preVFP',
    '2017': 'UL2017',
    '2018': 'UL2018',
}

ERA_TO_NANOAOD = {
    '2016postVFP': '2016',
    '2016preVFP': '2016APV',
    '2016': '2016',
    '2016APV': '2016APV',
    '2017': '2017',
    '2018': '2018',
}


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


def build_stage1_output(config: Dict[str, Any], era: str, systematic: str = None) -> str:
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


def build_stage2_output(config: Dict[str, Any], era: str, systematic: str = None,
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
    channel: str = None,
    suffix: str = None,
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


# =============================================================================
# Config Accessor Functions
# =============================================================================

def get_eras(config: Dict[str, Any]) -> List[str]:
    """
    Get list of eras from config.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        List of era strings.
    """
    return config.get('eras', ['2018', '2017', '2016preVFP', '2016postVFP'])


def get_channel(config: Dict[str, Any]) -> str:
    """
    Get channel name from config.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Channel name string (e.g., '1tau0l', '1tau1l', '1tau2l').
    """
    channel = config.get('channel', '1tau0l')
    # Handle legacy format where channel is a dict
    if isinstance(channel, dict):
        return channel.get('name', '1tau0l')
    return channel


def get_regions(config: Dict[str, Any]) -> List[str]:
    """
    Get analysis regions for the channel.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        List of region names.
    """
    channel = get_channel(config)
    # Default regions per channel
    default_regions = {
        '1tau0l': ['1tau0lSR', '1tau0lCRMR', '1tau0lVR'],
        '1tau1l': ['1tau1lSR', '1tau1lCR12'],
        '1tau2l': ['1tau2lSR', '1tau2lCR3'],
    }
    return default_regions.get(channel, [])


def get_options(config: Dict[str, Any]) -> Dict[str, bool]:
    """
    Get analysis options from config.

    Returns normalized option names (fake_tau, mc_fake_tau, blind, etc.).

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Dictionary of option flags.
    """
    opts = config.get('options', {})
    return {
        'fake_tau': opts.get('fake_tau', True),
        'mc_fake_tau': opts.get('mc_fake_tau', False),
        'blind': opts.get('blind', False),
        'systematics': opts.get('systematics', True),
        'smoothing': opts.get('smoothing', False),
        # Legacy aliases for backward compatibility
        'ifFakeTau': opts.get('fake_tau', True),
        'ifMCFTau': opts.get('mc_fake_tau', False),
        'ifBlind': opts.get('blind', False),
    }


def get_template_suffix(config: Dict[str, Any]) -> str:
    """
    Build template file suffix based on config options.

    Returns suffix like '_new_notMCFTau_unblind' based on options.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Suffix string for template filename.
    """
    options = get_options(config)
    suffix = '_new'

    if not options.get('mc_fake_tau', False):
        suffix += '_notMCFTau'

    if not options.get('blind', True):
        suffix += '_unblind'

    return suffix


def get_versions(config: Dict[str, Any]) -> Dict[str, str]:
    """
    Get version strings from config.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Dictionary with stage1, stage2, hist, datacard, combination versions.
    """
    return config.get('versions', {})
