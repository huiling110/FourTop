"""
Configuration Loading and Validation
=====================================

Load and validate YAML configuration files for the FourTop analysis.

Supports two config formats:
- New minimal format (versions.stage1, versions.stage2, etc.)
- Legacy format (paths.out_version, paths.in_version, etc.)

Usage:
    from fourtop.workflow.config import load_config

    config = load_config('config/analysis_config_1tau0l.yaml')
    channel = config['channel']
    eras = config['eras']
"""

import os
import yaml
from typing import Dict, Any, List, Optional


def load_config(config_path: Optional[str] = None) -> Dict[str, Any]:
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

    Example:
        >>> config = load_config('config/analysis_config_1tau0l.yaml')
        >>> print(config['channel'])
        '1tau0l'
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

    Args:
        config: Raw config dictionary from YAML.

    Returns:
        Normalized config dictionary.
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

    Args:
        config: Normalized config dictionary.

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


def get_eras(config: Dict[str, Any]) -> List[str]:
    """
    Get list of eras from config.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        List of era strings.
    """
    return config.get('eras', ['2018', '2017', '2016preVFP', '2016postVFP'])


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


def get_versions(config: Dict[str, Any]) -> Dict[str, str]:
    """
    Get version strings from config.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Dictionary with stage1, stage2, hist, datacard, combination versions.
    """
    return config.get('versions', {})


def get_template_suffix(config: Dict[str, Any]) -> str:
    """
    Build template file suffix based on config options.

    Returns suffix like '_v3_notMCFTau_unblind' based on options.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Suffix string for template filename.
    """
    options = get_options(config)
    versions = config.get('versions', {})
    template_version = versions.get('template_file', 'v3')  # Default to v3
    suffix = f'_{template_version}'

    if not options.get('mc_fake_tau', False):
        suffix += '_notMCFTau'

    if not options.get('blind', True):
        suffix += '_unblind'

    return suffix
