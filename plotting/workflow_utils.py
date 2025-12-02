"""
Workflow utilities for FourTop analysis.

Provides functions for loading YAML configuration and building paths
used across plotting and combine scripts.

Usage:
    from workflow_utils import load_config, build_hist_path, build_template_path

    config = load_config('config/analysis_config.yaml')
    hist_path = build_hist_path(config, '2018')
"""

import os
import yaml
from typing import Dict, Any, Optional, List


def load_config(config_path: str = None) -> Dict[str, Any]:
    """
    Load analysis configuration from YAML file.

    Args:
        config_path: Path to config YAML. If None, uses default location.

    Returns:
        Dictionary containing configuration.

    Raises:
        FileNotFoundError: If config file doesn't exist.
        yaml.YAMLError: If YAML parsing fails.
    """
    if config_path is None:
        # Default: look for config relative to FourTop root
        script_dir = os.path.dirname(os.path.abspath(__file__))
        project_root = os.path.dirname(script_dir)
        config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    if not os.path.exists(config_path):
        raise FileNotFoundError(f"Config file not found: {config_path}")

    with open(config_path, 'r') as f:
        config = yaml.safe_load(f)

    _validate_config(config)
    return config


def _validate_config(config: Dict[str, Any]) -> None:
    """
    Validate that required config keys exist.

    Raises:
        KeyError: If required keys are missing.
    """
    required_paths = ['base', 'out_version', 'in_version', 'hist_version']

    if 'paths' not in config:
        raise KeyError("Config missing 'paths' section")

    for key in required_paths:
        if key not in config['paths']:
            raise KeyError(f"Config missing required path: paths.{key}")


def build_hist_path(config: Dict[str, Any], era: str) -> str:
    """
    Build path to histogram directory for a given era.

    Pattern: {base}/{era}/{out_version}_{in_version}/mc/variableHists_{hist_version}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string (2018, 2017, 2016preVFP, 2016postVFP).

    Returns:
        Full path to histogram directory.
    """
    paths = config['paths']
    return os.path.join(
        paths['base'],
        era,
        f"{paths['out_version']}_{paths['in_version']}",
        'mc',
        f"variableHists_{paths['hist_version']}"
    )


def build_combine_path(config: Dict[str, Any], era: str) -> str:
    """
    Build path to combine directory for a given era.

    Pattern: {hist_path}/combine/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string.

    Returns:
        Full path to combine directory.
    """
    return os.path.join(build_hist_path(config, era), 'combine')


def build_template_path(
    config: Dict[str, Any],
    era: str,
    channel: str,
    suffix: str = '',
    smoothed: bool = False
) -> str:
    """
    Build path to template ROOT file for combine.

    Pattern: {combine_path}/templatesForCombine{channel}{suffix}.root

    Args:
        config: Configuration dictionary from load_config().
        era: Era string.
        channel: Channel name (1tau0l, 1tau1l, 1tau2l).
        suffix: Optional suffix like '_new_notMCFTau_unblind'.
        smoothed: If True, append '_smoothed' before .root.

    Returns:
        Full path to template ROOT file.
    """
    combine_path = build_combine_path(config, era)
    filename = f"templatesForCombine{channel}{suffix}"
    if smoothed:
        filename += '_smoothed'
    filename += '.root'
    return os.path.join(combine_path, filename)


def build_datacard_path(
    config: Dict[str, Any],
    era: str,
    channel: str
) -> str:
    """
    Build path to datacard output directory.

    Pattern: {combine_path}/datacardSys_{datacard_version}/

    Args:
        config: Configuration dictionary from load_config().
        era: Era string.
        channel: Channel name.

    Returns:
        Full path to datacard directory.
    """
    combine_path = build_combine_path(config, era)
    datacard_version = config['paths'].get('datacard_version', 'v6AllSys_unblind_CMSnaming')
    return os.path.join(combine_path, f"datacardSys_{datacard_version}")


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
        Channel name string.
    """
    return config.get('channel', {}).get('name', '1tau0l')


def get_options(config: Dict[str, Any]) -> Dict[str, bool]:
    """
    Get analysis options from config.

    Args:
        config: Configuration dictionary from load_config().

    Returns:
        Dictionary of option flags.
    """
    return config.get('options', {
        'ifFakeTau': True,
        'ifMCFTau': False,
        'ifBlind': False,
        'ifVLL': False
    })


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

    if not options.get('ifMCFTau', False):
        suffix += '_notMCFTau'

    if not options.get('ifBlind', True):
        suffix += '_unblind'

    return suffix
