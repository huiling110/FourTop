#!/usr/bin/env python3
"""
FourTop Analysis Workflow Runner

Master script for running the FourTop analysis pipeline from histogram
production through statistical analysis. Uses YAML configuration for
reproducible, version-controlled analysis runs.

Usage:
    # Run all Stage 4 steps for all eras
    python3 run_workflow.py --config config/analysis_config.yaml --stage 4

    # Run specific stage for single era
    python3 run_workflow.py --config config/analysis_config.yaml --stage 4.2 --era 2018

    # Run full Stage 3-4 pipeline with logging
    python3 run_workflow.py --config config/analysis_config_1tau1l.yaml --stage 3 --log-file workflow.log

    # List available stages
    python3 run_workflow.py --list-stages

    # Save current config as version snapshot
    python3 run_workflow.py --save-version v9BDT1tau0l_CMSNamingComplete
"""

import argparse
import logging
import os
import subprocess
import sys
import time
from datetime import datetime
from typing import List, Optional, Tuple

# Add plotting directory to path for workflow_utils
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'plotting'))

try:
    from workflow_utils import (
        load_config, get_eras, get_channel, build_hist_path,
        build_combine_path, get_options
    )
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False
    print("WARNING: workflow_utils not available. Install PyYAML first.")


# Global logger
logger = logging.getLogger('workflow')


def setup_logging(log_file: Optional[str] = None, quiet: bool = False) -> None:
    """
    Setup logging with both console and file handlers.

    Args:
        log_file: Path to log file. If None, only console logging.
        quiet: If True, only log warnings and errors to console.
    """
    logger.setLevel(logging.DEBUG)

    # Clear existing handlers
    logger.handlers = []

    # Console handler
    console = logging.StreamHandler()
    console.setLevel(logging.WARNING if quiet else logging.INFO)
    console_fmt = logging.Formatter('[%(asctime)s] %(levelname)-5s | %(message)s',
                                    datefmt='%H:%M:%S')
    console.setFormatter(console_fmt)
    logger.addHandler(console)

    # File handler (if specified)
    if log_file:
        file_handler = logging.FileHandler(log_file, mode='w')
        file_handler.setLevel(logging.DEBUG)
        file_fmt = logging.Formatter(
            '[%(asctime)s] %(levelname)-5s | %(message)s',
            datefmt='%Y-%m-%d %H:%M:%S'
        )
        file_handler.setFormatter(file_fmt)
        logger.addHandler(file_handler)
        logger.info(f"Logging to file: {log_file}")


# Stage definitions
STAGES = {
    '3.3': {
        'name': 'Submit Nominal Histogram Jobs',
        'script': 'writeHistGood/jobs/makeJob_forWriteHist.py',
        'description': 'Submit nominal histogram production jobs via hep_sub'
    },
    '3.3.1': {
        'name': 'Submit Shape Systematic Jobs',
        'script': 'writeHistGood/run_makeJos_WH_forJES.sh',
        'description': 'Submit JES/JER/TES/MET/EES systematic jobs'
    },
    '3.4': {
        'name': 'Monitor Jobs',
        'script': 'writeHistGood/jobs/checkJobResult.py',
        'description': 'Wait for all submitted jobs to complete'
    },
    '4.1': {
        'name': 'Consolidate Shape Systematics',
        'script': 'plotting/addJESTemplatesToHistFile.py',
        'description': 'Add JES/JER/TES/MET systematics to nominal files'
    },
    '4.2': {
        'name': 'Create Template Files',
        'script': 'plotting/addTemplateNew.py',
        'description': 'Create template ROOT files for combine'
    },
    '4.2.5': {
        'name': 'Smooth Systematics',
        'script': 'plotting/smooth_systematics_fourTops.py',
        'description': 'Apply smoothing to problematic systematics'
    },
    '4.3': {
        'name': 'Write Datacards',
        'script': 'plotting/writeDatacard.py',
        'description': 'Generate combine datacards from templates'
    },
    '4.4': {
        'name': 'Combine Datacards',
        'script': 'hua/combine/writeCombinationDatacard.py',
        'description': 'Combine era datacards into Run2 datacard',
        'requires_cmsenv': True
    }
}


def get_project_root() -> str:
    """Get the FourTop project root directory."""
    return os.path.dirname(os.path.abspath(__file__))


def run_command(cmd: List[str], cwd: str = None, quiet: bool = False,
                capture_output: bool = False) -> Tuple[int, str, str]:
    """
    Run a shell command and return the exit code and output.

    Args:
        cmd: Command and arguments as list
        cwd: Working directory
        quiet: Suppress console output (still logs to file)
        capture_output: Capture stdout/stderr

    Returns:
        Tuple of (exit_code, stdout, stderr)
    """
    cmd_str = ' '.join(cmd)
    logger.debug(f"Running: {cmd_str}")
    if not quiet:
        logger.info(f"Running: {cmd_str[:100]}...")

    start_time = time.time()
    try:
        result = subprocess.run(
            cmd,
            cwd=cwd,
            capture_output=capture_output or quiet,
            text=True
        )
        duration = time.time() - start_time

        if result.returncode != 0:
            logger.error(f"Command failed (code {result.returncode}) after {duration:.1f}s")
            if result.stderr:
                logger.error(f"STDERR: {result.stderr[:500]}")
        else:
            logger.debug(f"Command succeeded in {duration:.1f}s")

        return result.returncode, result.stdout or '', result.stderr or ''
    except Exception as e:
        logger.error(f"Exception running command: {e}")
        return 1, '', str(e)


def run_stage_4_1(config: dict, era: str, quiet: bool = False) -> int:
    """Run Stage 4.1: Consolidate shape systematics."""
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.1']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    cmd = ['python3', script, '--config', config_path, '--era', era]
    if quiet:
        cmd.append('--quiet')

    return run_command(cmd, cwd=project_root, quiet=quiet)


def run_stage_4_2(config: dict, era: str, quiet: bool = False) -> int:
    """Run Stage 4.2: Create template files."""
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.2']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    cmd = ['python3', script, '--config', config_path, '--era', era]
    if quiet:
        cmd.append('--quiet')

    return run_command(cmd, cwd=project_root, quiet=quiet)


def run_stage_4_2_5(config: dict, era: str, quiet: bool = False) -> int:
    """Run Stage 4.2.5: Smooth systematics."""
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.2.5']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    # Check if smoothing is enabled in config
    if not config.get('smoothing', {}).get('enabled', False):
        if not quiet:
            print(f"  Smoothing disabled in config, skipping era {era}")
        return 0

    cmd = ['python3', script, '--config', config_path, '--era', era]
    if quiet:
        cmd.append('--quiet')

    return run_command(cmd, cwd=project_root, quiet=quiet)


def run_stage_4_3(config: dict, era: str, quiet: bool = False,
                  smoothed: bool = False) -> int:
    """Run Stage 4.3: Write datacards."""
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.3']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    cmd = ['python3', script, '--config', config_path, '--era', era]
    if smoothed:
        cmd.append('--smoothed')
    if quiet:
        cmd.append('--quiet')

    return run_command(cmd, cwd=project_root, quiet=quiet)


def run_stage_4_4(config: dict, quiet: bool = False) -> int:
    """
    Run Stage 4.4: Combine datacards across eras.

    Note: This stage runs once for all eras combined, not per-era.
    Requires cmsenv environment (not setEnv_newNew.sh).
    """
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.4']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')
    combine_dir = os.path.join(project_root, 'hua', 'combine')

    cmd = ['python3', script, '--config', config_path]
    if quiet:
        cmd.append('--quiet')

    if not quiet:
        print("  Note: Stage 4.4 requires cmsenv environment")

    return run_command(cmd, cwd=combine_dir, quiet=quiet)


def run_stage(stage: str, config: dict, eras: List[str],
              quiet: bool = False, smoothed: bool = False) -> int:
    """
    Run a specific stage for given eras.

    Args:
        stage: Stage identifier (e.g., '4.1', '4.2')
        config: Configuration dictionary
        eras: List of eras to process
        quiet: Suppress output
        smoothed: Use smoothed templates (for 4.3)

    Returns:
        0 if all successful, 1 if any failed
    """
    if stage not in STAGES:
        print(f"ERROR: Unknown stage '{stage}'")
        return 1

    stage_info = STAGES[stage]
    if not quiet:
        print(f"\n{'='*60}")
        print(f"Stage {stage}: {stage_info['name']}")
        print(f"{'='*60}")

    # Stage 4.4 runs once for all eras combined
    if stage == '4.4':
        return run_stage_4_4(config, quiet=quiet)

    # Other stages run per-era
    failed_eras = []
    for era in eras:
        if not quiet:
            print(f"\n--- Processing era: {era} ---")

        if stage == '4.1':
            result = run_stage_4_1(config, era, quiet=quiet)
        elif stage == '4.2':
            result = run_stage_4_2(config, era, quiet=quiet)
        elif stage == '4.2.5':
            result = run_stage_4_2_5(config, era, quiet=quiet)
        elif stage == '4.3':
            result = run_stage_4_3(config, era, quiet=quiet, smoothed=smoothed)
        else:
            print(f"  Stage {stage} runner not implemented")
            result = 1

        if result != 0:
            failed_eras.append(era)

    if failed_eras:
        print(f"\nWARNING: Stage {stage} failed for eras: {failed_eras}")
        return 1

    if not quiet:
        print(f"\nStage {stage} completed successfully for all eras")
    return 0


def run_full_stage_4(config: dict, eras: List[str], quiet: bool = False) -> int:
    """Run all Stage 4 substages in order."""
    stages_to_run = ['4.1', '4.2', '4.2.5', '4.3', '4.4']

    for stage in stages_to_run:
        # For 4.3, check if smoothing was done and use smoothed templates
        smoothed = (stage == '4.3' and
                   config.get('smoothing', {}).get('enabled', False))

        result = run_stage(stage, config, eras, quiet=quiet, smoothed=smoothed)
        if result != 0:
            print(f"\nERROR: Stage {stage} failed. Stopping workflow.")
            return 1

    print("\n" + "="*60)
    print("Full Stage 4 workflow completed successfully!")
    print("="*60)
    return 0


def save_config_version(version_name: str, config_path: str = None) -> int:
    """Save current config as a version snapshot."""
    import shutil

    project_root = get_project_root()
    if config_path is None:
        config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    versions_dir = os.path.join(project_root, 'config', 'versions')
    os.makedirs(versions_dir, exist_ok=True)

    dest_path = os.path.join(versions_dir, f'config_{version_name}.yaml')

    if os.path.exists(dest_path):
        print(f"WARNING: Version '{version_name}' already exists at {dest_path}")
        response = input("Overwrite? [y/N]: ")
        if response.lower() != 'y':
            print("Aborted.")
            return 1

    shutil.copy2(config_path, dest_path)
    print(f"Saved config version: {dest_path}")
    return 0


def list_stages():
    """Print available stages."""
    print("\nAvailable Stages:")
    print("-" * 60)
    for stage_id, info in sorted(STAGES.items()):
        cmsenv = " [requires cmsenv]" if info.get('requires_cmsenv') else ""
        print(f"  {stage_id:6s} - {info['name']}{cmsenv}")
        print(f"           {info['description']}")
        print(f"           Script: {info['script']}")
        print()


def main():
    parser = argparse.ArgumentParser(
        description='FourTop Analysis Workflow Runner',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument(
        '--config', '-c',
        type=str,
        default='config/analysis_config.yaml',
        help='Path to YAML config file (default: config/analysis_config.yaml)'
    )
    parser.add_argument(
        '--stage', '-s',
        type=str,
        help='Stage to run (e.g., 4.1, 4.2, 4.3, 4.4, or "4" for all)'
    )
    parser.add_argument(
        '--era', '-e',
        type=str,
        help='Single era to process (default: all eras from config)'
    )
    parser.add_argument(
        '--quiet', '-q',
        action='store_true',
        help='Suppress non-essential output'
    )
    parser.add_argument(
        '--list-stages',
        action='store_true',
        help='List available stages and exit'
    )
    parser.add_argument(
        '--save-version',
        type=str,
        metavar='NAME',
        help='Save current config as version snapshot with given name'
    )
    parser.add_argument(
        '--smoothed',
        action='store_true',
        help='Use smoothed templates for datacard creation (Stage 4.3)'
    )

    args = parser.parse_args()

    # Handle --list-stages
    if args.list_stages:
        list_stages()
        return 0

    # Handle --save-version
    if args.save_version:
        return save_config_version(args.save_version, args.config)

    # Require --stage for actual workflow runs
    if not args.stage:
        parser.print_help()
        print("\nERROR: --stage is required to run workflow")
        return 1

    # Check workflow_utils availability
    if not WORKFLOW_UTILS_AVAILABLE:
        print("ERROR: workflow_utils not available. Install PyYAML:")
        print("  python3 -m pip install pyyaml")
        return 1

    # Load config
    project_root = get_project_root()
    config_path = args.config
    if not os.path.isabs(config_path):
        config_path = os.path.join(project_root, config_path)

    try:
        config = load_config(config_path)
    except FileNotFoundError:
        print(f"ERROR: Config file not found: {config_path}")
        return 1
    except Exception as e:
        print(f"ERROR loading config: {e}")
        return 1

    # Determine eras to process
    if args.era:
        eras = [args.era]
    else:
        eras = get_eras(config)

    if not args.quiet:
        channel = get_channel(config)
        print(f"Config: {config_path}")
        print(f"Channel: {channel}")
        print(f"Eras: {', '.join(eras)}")

    # Run requested stage(s)
    if args.stage == '4':
        return run_full_stage_4(config, eras, quiet=args.quiet)
    else:
        return run_stage(args.stage, config, eras,
                        quiet=args.quiet, smoothed=args.smoothed)


if __name__ == '__main__':
    sys.exit(main())
