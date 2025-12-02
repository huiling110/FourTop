#!/usr/bin/env python3
"""
FourTop Analysis Workflow Runner

Master script for running the FourTop analysis pipeline from histogram
production through statistical analysis. Uses YAML configuration for
reproducible, version-controlled analysis runs.

Usage:
    # Run FULL pipeline (Stage 3 + Stage 4) - one command does everything!
    python3 run_workflow.py --stage all --config config/analysis_config_1tau1l.yaml -l workflow.log

    # Run only Stage 3 (histogram job submission + monitoring)
    python3 run_workflow.py --stage 3 --config config/analysis_config.yaml

    # Run only Stage 4 (templates → datacards → combine)
    python3 run_workflow.py --stage 4 --config config/analysis_config.yaml

    # Run specific substage for single era
    python3 run_workflow.py --stage 4.2 --era 2018 --config config/analysis_config.yaml

    # List available stages
    python3 run_workflow.py --list-stages

    # Save current config as version snapshot
    python3 run_workflow.py --save-version v9BDT1tau0l_CMSNamingComplete

Stage groups:
    "all" or "3-4" : Full pipeline (Stage 3 + Stage 4)
    "3"            : Histogram production (3.3 + 3.3.1 + 3.4)
    "4"            : Analysis workflow (4.1 + 4.2 + 4.2.5 + 4.3 + 4.4)
"""

import argparse
import logging
import os
import subprocess
import sys
import time
from concurrent.futures import ThreadPoolExecutor, as_completed
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
    },
    '4.5': {
        'name': 'Run Combine Analysis',
        'script': 'hua/combine/runCombineAll.py',
        'description': 'Run statistical analysis (workspace, limits, significance, postfit)',
        'requires_cmsenv': True
    },
    '4.6': {
        'name': 'Create Fit Plots',
        'script': 'plotting/pl_postFit.py',
        'description': 'Generate pre-fit and post-fit data/MC comparison plots'
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


def build_input_dir(config: dict, era: str) -> str:
    """
    Build the input directory path from config for a given era.

    Returns path like:
    /publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/
    """
    paths = config.get('paths', {})
    base = paths.get('base', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA')
    out_version = paths.get('out_version', 'v1baselineHadroBtagWeightAdded')
    in_version = paths.get('in_version', 'v94HadroPreJetVetoHemOnly')

    return f"{base}/{era}/{out_version}_{in_version}/"


def get_running_jobs() -> int:
    """
    Get count of running/idle jobs for current user using hep_q.

    Returns:
        Number of running + idle jobs
    """
    try:
        result = subprocess.run(
            ['hep_q', '-u'],
            capture_output=True,
            text=True,
            timeout=30
        )
        # Count non-header lines (each line = one job)
        lines = result.stdout.strip().split('\n')
        # Filter out header and empty lines
        job_lines = [l for l in lines if l.strip() and not l.startswith('--')
                     and 'OWNER' not in l and 'ID' not in l.split()[0] if l.split()]
        return len(job_lines)
    except Exception as e:
        logger.warning(f"Could not check job status: {e}")
        return -1


def run_stage_3_3(config: dict, era: str, quiet: bool = False) -> Tuple[int, str, str]:
    """
    Run Stage 3.3: Submit nominal histogram production jobs.

    This calls the job submission script with parameters derived from config.
    """
    project_root = get_project_root()

    # Build parameters from config
    input_dir = build_input_dir(config, era)
    channel = get_channel(config)
    hist_version = config.get('paths', {}).get('hist_version', 'v10BDT_WorkflowTest')

    # Stage 3 specific config
    stage3_cfg = config.get('stage3', {})
    exe = stage3_cfg.get('executable', './apps/run_treeAnalyzer.out')
    if_sys = stage3_cfg.get('ifSys', 1)
    just_mc = stage3_cfg.get('justMC', False)

    logger.info(f"Stage 3.3 | Era: {era}")
    logger.info(f"Stage 3.3 | Input dir: {input_dir}")
    logger.info(f"Stage 3.3 | Channel: {channel}, Version: {hist_version}")

    # Check input directory exists
    if not os.path.exists(input_dir):
        logger.error(f"Input directory does not exist: {input_dir}")
        return 1, '', 'Input directory not found'

    # Create job submission script dynamically
    job_script_content = f'''#!/usr/bin/env python3
import sys
sys.path.insert(0, "{project_root}/writeHistGood/jobs")
import makeJob_forWriteHist as mj

mj.main(
    inputDir="{input_dir}",
    channel="{channel}",
    version="{hist_version}",
    exe="{exe}",
    ifSys={if_sys},
    justMC={just_mc}
)
'''

    # Write temporary script
    temp_script = os.path.join(project_root, f'.tmp_submit_{era}.py')
    with open(temp_script, 'w') as f:
        f.write(job_script_content)

    # Run the script from writeHistGood directory (required for exe path)
    cmd = ['python3', temp_script]
    cwd = os.path.join(project_root, 'writeHistGood')

    result = run_command(cmd, cwd=cwd, quiet=quiet, capture_output=True)

    # Clean up temp script
    try:
        os.remove(temp_script)
    except:
        pass

    return result


def run_stage_3_3_1(config: dict, era: str, quiet: bool = False) -> Tuple[int, str, str]:
    """
    Run Stage 3.3.1: Submit shape systematic jobs (JES/JER/TES/MET/EES).

    This runs the systematic job submission for a single era.
    """
    project_root = get_project_root()

    # Build parameters from config
    channel = get_channel(config)
    hist_version = config.get('paths', {}).get('hist_version', 'v10BDT_WorkflowTest')
    in_version = config.get('paths', {}).get('in_version', 'v94HadroPreJetVetoHemOnly')

    logger.info(f"Stage 3.3.1 | Era: {era}")
    logger.info(f"Stage 3.3.1 | Channel: {channel}, Version: {hist_version}")

    # Get the input base path for this era
    base = config.get('paths', {}).get('base', '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA')
    input_dir_base = f"{base}/{era}/"
    out_version = config.get('paths', {}).get('out_version', 'v1baselineHadroBtagWeightAdded')

    # Run the JES job script
    script = os.path.join(project_root, 'writeHistGood', 'jobs', 'makeJob_WH_forJES.py')

    cmd = [
        'python3', script,
        '--inputDirBase', input_dir_base,
        '--inVersion', in_version,
        '--outVersion', out_version,
        '--channel', channel,
        '--version', hist_version
    ]

    cwd = os.path.join(project_root, 'writeHistGood')

    return run_command(cmd, cwd=cwd, quiet=quiet, capture_output=True)


def run_stage_3_4(config: dict, quiet: bool = False,
                  poll_interval: int = 60, max_wait: int = 7200) -> Tuple[int, str, str]:
    """
    Run Stage 3.4: Monitor jobs until completion.

    Polls hep_q every poll_interval seconds until no jobs are running,
    or max_wait seconds have elapsed.

    Args:
        config: Configuration dictionary
        quiet: Suppress output
        poll_interval: Seconds between status checks (default: 60)
        max_wait: Maximum seconds to wait (default: 7200 = 2 hours)

    Returns:
        (0, summary, '') on completion, (1, '', error) on timeout/error
    """
    logger.info("Stage 3.4 | Starting job monitoring")

    start_time = time.time()
    last_count = -1

    while True:
        elapsed = time.time() - start_time
        if elapsed > max_wait:
            logger.error(f"Stage 3.4 | Timeout after {max_wait}s")
            return 1, '', f'Timeout waiting for jobs after {max_wait}s'

        job_count = get_running_jobs()

        if job_count == 0:
            logger.info("Stage 3.4 | All jobs completed")
            return 0, f'All jobs completed in {elapsed:.0f}s', ''

        if job_count != last_count:
            logger.info(f"Stage 3.4 | {job_count} jobs running/pending ({elapsed:.0f}s elapsed)")
            last_count = job_count

        if not quiet:
            print(f"  Waiting... {job_count} jobs active ({int(elapsed)}s elapsed)",
                  end='\r', flush=True)

        time.sleep(poll_interval)


def get_output_paths(config: dict, era: str, stage: str) -> str:
    """
    Get the output path for a given stage.

    Returns a human-readable description of where output files are created.
    """
    hist_path = build_hist_path(config, era)
    channel = get_channel(config)
    options = get_options(config)

    # Build suffix for template files
    suffix_parts = ['new']
    if not options.get('mcFakeTau', True):
        suffix_parts.append('notMCFTau')
    if options.get('unblind', False):
        suffix_parts.append('unblind')
    suffix = '_'.join(suffix_parts)

    if stage == '4.1':
        return f"{hist_path}*.root (JES/JER/TES systematics added)"
    elif stage == '4.2':
        return f"{hist_path}combine/templatesForCombine{channel}_{suffix}.root"
    elif stage == '4.2.5':
        return f"{hist_path}combine/templatesForCombine{channel}_{suffix}_smoothed.root"
    elif stage == '4.3':
        datacard_version = config.get('datacard', {}).get('version', 'v1')
        return f"{hist_path}combine/datacardSys_{datacard_version}/datacard_{channel}.txt"
    elif stage == '4.4':
        comb = config.get('combination', {})
        return f"hua/combine/{comb.get('version', 'combinationV20')}/{comb.get('card_dir', 'run2')}/datacard.txt"
    elif stage == '4.5':
        comb = config.get('combination', {})
        return f"hua/combine/{comb.get('version', 'combinationV20')}/{comb.get('card_dir', 'run2')}/combineResults/"
    elif stage == '4.6':
        comb = config.get('combination', {})
        return f"hua/combine/{comb.get('version', 'combinationV20')}/{comb.get('card_dir', 'run2')}/plots/"
    return "Unknown"


def run_stage_4_1(config: dict, era: str, quiet: bool = False) -> int:
    """Run Stage 4.1: Consolidate shape systematics."""
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.1']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    cmd = ['python3', script, '--config', config_path, '--era', era]
    if quiet:
        cmd.append('--quiet')

    result = run_command(cmd, cwd=project_root, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        logger.info(f"Stage 4.1 | Output: {get_output_paths(config, era, '4.1')}")
    return result


def run_stage_4_2(config: dict, era: str, quiet: bool = False) -> int:
    """Run Stage 4.2: Create template files."""
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.2']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    cmd = ['python3', script, '--config', config_path, '--era', era]
    if quiet:
        cmd.append('--quiet')

    result = run_command(cmd, cwd=project_root, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        logger.info(f"Stage 4.2 | Output: {get_output_paths(config, era, '4.2')}")
    return result


def run_stage_4_2_5(config: dict, quiet: bool = False) -> int:
    """
    Run Stage 4.2.5: Smooth systematics.

    Note: This stage runs once for all eras (not per-era) because
    the smoothing script processes all years together.
    """
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.2.5']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    # Check if smoothing is enabled in config
    if not config.get('smoothing', {}).get('enabled', False):
        if not quiet:
            print("  Smoothing disabled in config, skipping")
        logger.info("Stage 4.2.5 | Skipped (smoothing disabled)")
        return 0

    cmd = ['python3', script, '--config', config_path]
    if quiet:
        cmd.append('--quiet')

    result = run_command(cmd, cwd=project_root, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        # Log output for all eras
        for era in get_eras(config):
            logger.info(f"Stage 4.2.5 | Output ({era}): {get_output_paths(config, era, '4.2.5')}")
    return result


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

    result = run_command(cmd, cwd=project_root, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        logger.info(f"Stage 4.3 | Output: {get_output_paths(config, era, '4.3')}")
    return result


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

    result = run_command(cmd, cwd=combine_dir, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        logger.info(f"Stage 4.4 | Output: {get_output_paths(config, '2018', '4.4')}")
    return result


def run_stage_4_5(config: dict, quiet: bool = False,
                  steps: List[str] = None, no_blind: bool = True) -> int:
    """
    Run Stage 4.5: Run Combine statistical analysis.

    This runs runCombineAll.py to perform:
    - Workspace creation (text2workspace)
    - Limit calculation (AsymptoticLimits)
    - Significance calculation
    - Post-fit diagnostics (FitDiagnostics)
    - Signal strength measurement

    Note: Requires cmsenv environment (not setEnv_newNew.sh).

    Args:
        config: Configuration dictionary
        quiet: Suppress output
        steps: List of steps to run (default: workspace, significance, limits, impacts, postfit, signal_strength)
        no_blind: If True, run unblinded analysis (default). If False, run blinded.
    """
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.5']['script'])
    combine_dir = os.path.join(project_root, 'hua', 'combine')

    # Get card directory from config
    combination = config.get('combination', {})
    comb_version = combination.get('version', 'combinationV20')
    channel = get_channel(config)
    card_subdir = combination.get('card_dir', f'run2_{channel}_v4_unblind')
    card_dir = f'{comb_version}/{card_subdir}/'

    # Default steps if not specified
    if steps is None:
        steps = ['workspace', 'significance', 'limits', 'impacts', 'postfit', 'signal_strength']

    cmd = ['python3', script, '--cardDir', card_dir, '--steps'] + steps

    if no_blind:
        cmd.append('--no-blind')
    else:
        cmd.append('--ifBlind')

    logger.info(f"Stage 4.5 | Card directory: {card_dir}")
    logger.info(f"Stage 4.5 | Steps: {steps}")
    logger.info(f"Stage 4.5 | Blinding: {'OFF' if no_blind else 'ON'}")

    if not quiet:
        print("  Note: Stage 4.5 requires cmsenv environment")
        print(f"  Card directory: {card_dir}")
        print(f"  Steps: {', '.join(steps)}")

    result = run_command(cmd, cwd=combine_dir, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        logger.info(f"Stage 4.5 | Output: {get_output_paths(config, '2018', '4.5')}")
    return result


def run_stage_4_6(config: dict, quiet: bool = False,
                  plot_type: str = 'both') -> int:
    """
    Run Stage 4.6: Generate pre-fit and/or post-fit plots.

    Args:
        config: Configuration dictionary
        quiet: Suppress output
        plot_type: 'prefit', 'postfit', or 'both' (default)
    """
    project_root = get_project_root()
    script = os.path.join(project_root, STAGES['4.6']['script'])
    config_path = os.path.join(project_root, 'config', 'analysis_config.yaml')

    cmd = ['python3', script, '--config', config_path, '--plot-type', plot_type]
    if quiet:
        cmd.append('--quiet')

    logger.info(f"Stage 4.6 | Plot type: {plot_type}")

    result = run_command(cmd, cwd=project_root, quiet=quiet)
    code = result[0] if isinstance(result, tuple) else result
    if code == 0:
        logger.info(f"Stage 4.6 | Output: {get_output_paths(config, '2018', '4.6')}")
    return result


def _get_result_code(result) -> int:
    """Extract exit code from result (may be tuple or int)."""
    return result[0] if isinstance(result, tuple) else result


def _run_era_stage(stage: str, config: dict, era: str,
                   quiet: bool, smoothed: bool) -> int:
    """Run a single stage for a single era. Returns exit code."""
    # Dispatch table for per-era stages
    era_runners = {
        '3.3': lambda: run_stage_3_3(config, era, quiet=quiet),
        '3.3.1': lambda: run_stage_3_3_1(config, era, quiet=quiet),
        '4.1': lambda: run_stage_4_1(config, era, quiet=quiet),
        '4.2': lambda: run_stage_4_2(config, era, quiet=quiet),
        '4.3': lambda: run_stage_4_3(config, era, quiet=quiet, smoothed=smoothed),
    }

    runner = era_runners.get(stage)
    if runner is None:
        print(f"  Stage {stage} runner not implemented")
        return 1

    return _get_result_code(runner())


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

    # Dispatch table for global stages (run once, not per-era)
    global_runners = {
        '4.2.5': lambda: run_stage_4_2_5(config, quiet=quiet),
        '4.4': lambda: run_stage_4_4(config, quiet=quiet),
        '4.5': lambda: run_stage_4_5(config, quiet=quiet),
        '4.6': lambda: run_stage_4_6(config, quiet=quiet),
        '3.4': lambda: run_stage_3_4(config, quiet=quiet),
    }

    if stage in global_runners:
        return _get_result_code(global_runners[stage]())

    # Per-era stages
    failed_eras = []
    for era in eras:
        if not quiet:
            print(f"\n--- Processing era: {era} ---")
        result = _run_era_stage(stage, config, era, quiet, smoothed)
        if result != 0:
            failed_eras.append(era)

    if failed_eras:
        print(f"\nWARNING: Stage {stage} failed for eras: {failed_eras}")
        return 1

    if not quiet:
        print(f"\nStage {stage} completed successfully for all eras")
    return 0


def run_stage_3_3_1_parallel(config: dict, eras: List[str], quiet: bool = False) -> int:
    """
    Run Stage 3.3.1 for all eras in parallel.

    This significantly speeds up systematic job submission by running
    all 4 eras concurrently instead of sequentially.
    """
    logger.info("Stage 3.3.1 | Starting parallel systematic job submission")
    logger.info(f"Stage 3.3.1 | Submitting for {len(eras)} eras concurrently")

    results = {}
    start_time = time.time()

    with ThreadPoolExecutor(max_workers=len(eras)) as executor:
        # Submit all eras in parallel
        future_to_era = {
            executor.submit(run_stage_3_3_1, config, era, quiet): era
            for era in eras
        }

        # Collect results as they complete
        for future in as_completed(future_to_era):
            era = future_to_era[future]
            try:
                result = future.result()
                code = result[0] if isinstance(result, tuple) else result
                results[era] = code
                if code == 0:
                    logger.info(f"Stage 3.3.1 | {era} completed successfully")
                else:
                    logger.error(f"Stage 3.3.1 | {era} failed with code {code}")
            except Exception as e:
                logger.error(f"Stage 3.3.1 | {era} raised exception: {e}")
                results[era] = 1

    duration = time.time() - start_time
    failed_eras = [era for era, code in results.items() if code != 0]

    if failed_eras:
        logger.error(f"Stage 3.3.1 | Failed for eras: {failed_eras}")
        return 1

    logger.info(f"Stage 3.3.1 | All eras completed in {duration:.1f}s")
    return 0


def run_full_stage_3(config: dict, eras: List[str], quiet: bool = False,
                     parallel_sys: bool = True) -> int:
    """
    Run all Stage 3 substages in order:
    3.3   - Submit nominal histogram jobs
    3.3.1 - Submit shape systematic jobs (parallel by default)
    3.4   - Monitor jobs until completion

    Args:
        parallel_sys: If True, submit systematic jobs for all eras in parallel
    """
    # Stage 3.3: Nominal jobs (sequential per era - fast enough)
    result = run_stage('3.3', config, eras, quiet=quiet)
    if result != 0:
        logger.error("Stage 3.3 failed. Stopping workflow.")
        return 1

    # Stage 3.3.1: Systematic jobs (parallel across eras for speed)
    if parallel_sys:
        result = run_stage_3_3_1_parallel(config, eras, quiet=quiet)
    else:
        result = run_stage('3.3.1', config, eras, quiet=quiet)
    if result != 0:
        logger.error("Stage 3.3.1 failed. Stopping workflow.")
        return 1

    # Stage 3.4: Monitor jobs
    result = run_stage('3.4', config, eras, quiet=quiet)
    if result != 0:
        logger.error("Stage 3.4 failed. Stopping workflow.")
        return 1

    logger.info("Full Stage 3 workflow completed successfully!")
    print("\n" + "="*60)
    print("Full Stage 3 workflow completed successfully!")
    print("="*60)
    return 0


def run_full_stage_4(config: dict, eras: List[str], quiet: bool = False,
                     include_combine: bool = True, include_plots: bool = True) -> int:
    """
    Run all Stage 4 substages in order.

    Args:
        config: Configuration dictionary
        eras: List of eras to process
        quiet: Suppress output
        include_combine: If True, run Stage 4.5 (combine analysis)
        include_plots: If True, run Stage 4.6 (fit plots)
    """
    # Core stages (always run)
    stages_to_run = ['4.1', '4.2', '4.2.5', '4.3', '4.4']

    # Optional stages
    if include_combine:
        stages_to_run.append('4.5')
    if include_plots:
        stages_to_run.append('4.6')

    for stage in stages_to_run:
        # For 4.3, check if smoothing was done and use smoothed templates
        smoothed = (stage == '4.3' and
                   config.get('smoothing', {}).get('enabled', False))

        result = run_stage(stage, config, eras, quiet=quiet, smoothed=smoothed)
        if result != 0:
            logger.error(f"Stage {stage} failed. Stopping workflow.")
            return 1

    logger.info("Full Stage 4 workflow completed successfully!")
    print("\n" + "="*60)
    print("Full Stage 4 workflow completed successfully!")
    if include_combine:
        print("  - Stage 4.5: Combine analysis ✓")
    if include_plots:
        print("  - Stage 4.6: Fit plots ✓")
    print("="*60)
    return 0


def run_full_pipeline(config: dict, eras: List[str], quiet: bool = False) -> int:
    """
    Run complete pipeline: Stage 3 (job submission + monitoring) → Stage 4 (analysis).

    This is the full end-to-end workflow from histogram production to combine results.
    """
    logger.info("="*60)
    logger.info("Starting full pipeline (Stage 3 → Stage 4)")
    logger.info("="*60)

    # Stage 3: Histogram production
    result = run_full_stage_3(config, eras, quiet=quiet)
    if result != 0:
        logger.error("Stage 3 failed. Pipeline stopped.")
        return 1

    # Stage 4: Analysis workflow
    result = run_full_stage_4(config, eras, quiet=quiet)
    if result != 0:
        logger.error("Stage 4 failed. Pipeline stopped.")
        return 1

    logger.info("="*60)
    logger.info("Full pipeline completed successfully!")
    logger.info("="*60)
    print("\n" + "="*60)
    print("FULL PIPELINE COMPLETED SUCCESSFULLY!")
    print("Stage 3: Histogram production ✓")
    print("Stage 4: Analysis workflow ✓")
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


def create_parser() -> argparse.ArgumentParser:
    """Create and configure the argument parser."""
    parser = argparse.ArgumentParser(
        description='FourTop Analysis Workflow Runner',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument(
        '--config', '-c', type=str,
        default='config/analysis_config.yaml',
        help='Path to YAML config file (default: config/analysis_config.yaml)'
    )
    parser.add_argument(
        '--stage', '-s', type=str,
        help='Stage to run: "all" (full pipeline), "3" (histogram jobs), '
             '"4" (analysis), or specific (3.3, 4.1, 4.2, etc.)'
    )
    parser.add_argument('--era', '-e', type=str,
                        help='Single era to process (default: all eras from config)')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Suppress non-essential output')
    parser.add_argument('--list-stages', action='store_true',
                        help='List available stages and exit')
    parser.add_argument('--save-version', type=str, metavar='NAME',
                        help='Save current config as version snapshot with given name')
    parser.add_argument('--smoothed', action='store_true',
                        help='Use smoothed templates for datacard creation (Stage 4.3)')
    parser.add_argument('--log-file', '-l', type=str, metavar='FILE',
                        help='Write detailed log to file (in addition to console)')
    parser.add_argument('--poll-interval', type=int, default=60,
                        help='Seconds between job status checks for Stage 3.4 (default: 60)')
    parser.add_argument('--max-wait', type=int, default=7200,
                        help='Maximum seconds to wait for jobs in Stage 3.4 (default: 7200=2h)')
    parser.add_argument('--no-combine', action='store_true',
                        help='Skip Stage 4.5 (combine analysis) in full Stage 4 run')
    parser.add_argument('--no-plots', action='store_true',
                        help='Skip Stage 4.6 (fit plots) in full Stage 4 run')
    parser.add_argument('--plot-type', type=str, choices=['prefit', 'postfit', 'both'],
                        default='both',
                        help='Type of plots to generate for Stage 4.6 (default: both)')
    parser.add_argument('--combine-steps', nargs='+',
                        choices=['workspace', 'limits', 'significance', 'impacts',
                                 'postfit', 'signal_strength', 'gof'],
                        default=['workspace', 'significance', 'limits', 'impacts', 'postfit', 'signal_strength'],
                        help='Steps to run for Stage 4.5')
    parser.add_argument('--blind', action='store_true',
                        help='Run blinded analysis for Stage 4.5 (default: unblinded)')

    return parser


def handle_special_commands(args) -> Optional[int]:
    """
    Handle special commands (--list-stages, --save-version).

    Returns:
        Exit code if command handled, None to continue normal workflow.
    """
    if args.list_stages:
        list_stages()
        return 0

    if args.save_version:
        return save_config_version(args.save_version, args.config)

    if not args.stage:
        print("ERROR: --stage is required to run workflow")
        print("Use --list-stages to see available stages")
        return 1

    return None


def load_workflow_config(args) -> Tuple[Optional[dict], Optional[List[str]]]:
    """
    Load config and determine eras to process.

    Returns:
        Tuple of (config, eras) or (None, None) on error.
    """
    if not WORKFLOW_UTILS_AVAILABLE:
        print("ERROR: workflow_utils not available. Install PyYAML:")
        print("  python3 -m pip install pyyaml")
        return None, None

    project_root = get_project_root()
    config_path = args.config
    if not os.path.isabs(config_path):
        config_path = os.path.join(project_root, config_path)

    try:
        config = load_config(config_path)
    except FileNotFoundError:
        print(f"ERROR: Config file not found: {config_path}")
        return None, None
    except Exception as e:
        print(f"ERROR loading config: {e}")
        return None, None

    eras = [args.era] if args.era else get_eras(config)

    if not args.quiet:
        channel = get_channel(config)
        print(f"Config: {config_path}")
        print(f"Channel: {channel}")
        print(f"Eras: {', '.join(eras)}")

    return config, eras


def run_requested_stage(args, config: dict, eras: List[str]) -> int:
    """Execute the requested stage(s) based on args."""
    if args.stage in ('all', 'full', '3-4'):
        return run_full_pipeline(config, eras, quiet=args.quiet)
    elif args.stage == '3':
        return run_full_stage_3(config, eras, quiet=args.quiet)
    elif args.stage == '4':
        return run_full_stage_4(config, eras, quiet=args.quiet,
                                include_combine=not args.no_combine,
                                include_plots=not args.no_plots)
    else:
        return run_stage(args.stage, config, eras,
                         quiet=args.quiet, smoothed=args.smoothed)


def main():
    """Main entry point for workflow runner."""
    parser = create_parser()
    args = parser.parse_args()

    # Handle special commands first
    result = handle_special_commands(args)
    if result is not None:
        return result

    # Setup logging
    setup_logging(log_file=args.log_file, quiet=args.quiet)

    # Load config and determine eras
    config, eras = load_workflow_config(args)
    if config is None:
        return 1

    # Run the requested stage(s)
    return run_requested_stage(args, config, eras)


if __name__ == '__main__':
    sys.exit(main())
