#!/usr/bin/env python3
"""Unified WH (Stage 3) job submission script.

Handles both nominal and systematic variations in one interface.

Usage:
    # Nominal histograms (Stage 3):
    python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic nominal

    # All systematics (Stage 3.1):
    python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic all

    # Specific systematic group:
    python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic TES

    # Dry run:
    python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic nominal --dry-run
"""
import argparse
import os

import makeJob_forWriteHist as mj

# Use fourtop package for all imports
from fourtop.workflow import (
    load_config, build_stage2_path, build_stage2_output, get_channel, get_versions, get_workflow_state
)
from fourtop.constants.jes import JESVariationList as JES_SOURCES

# Systematic variations by group
SYSTEMATIC_GROUPS = {
    'TES': [
        'TESdm0Up', 'TESdm0Down',
        'TESdm1Up', 'TESdm1Down',
        'TESdm10Up', 'TESdm10Down',
        'TESdm11Up', 'TESdm11Down',
    ],
    'JER': ['JERUp', 'JERDown'],
    'MET': ['METUp', 'METDown'],
    'EleScale': ['EleScaleUp', 'EleScaleDown'],
    'JES': [],  # Populated below
}

# Generate JES variations (27 sources × 2 directions = 54 variations)
for source in JES_SOURCES:
    SYSTEMATIC_GROUPS['JES'].append(f'JESup_{source}')
    SYSTEMATIC_GROUPS['JES'].append(f'JESDown_{source}')

# Default executable
EXE = './apps/run_treeAnalyzer.out'


def create_parser():
    """Create argument parser."""
    parser = argparse.ArgumentParser(
        description='Submit WH (Stage 3) jobs - nominal and systematic variations',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Examples:
  # Nominal histograms:
  python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic nominal

  # Skip data processing (nominal includes data by default):
  python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic nominal --no-data

  # All systematics:
  python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic all

  # Specific systematic group:
  python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic TES

  # Dry run:
  python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --systematic nominal --dry-run
        '''
    )
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file')
    parser.add_argument('--era', '-e', type=str,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process (default: all from config)')
    parser.add_argument('--systematic', '-s', type=str,
                        choices=['nominal', 'TES', 'JER', 'MET', 'EleScale', 'JES', 'all', 'complete'],
                        default='nominal',
                        help='Systematic to submit (default: nominal). Use "all" for all systematics, "complete" for nominal+all systematics')
    parser.add_argument('--no-data', action='store_true',
                        help='Skip data processing (nominal includes data by default)')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be done without submitting')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Reduce output verbosity')
    return parser


def get_systematics(systematic_arg: str) -> list:
    """Get list of systematic variations."""
    if systematic_arg == 'nominal':
        return ['nominal']
    elif systematic_arg == 'complete':
        # Both nominal and all systematics
        systematics = ['nominal']
        for g in SYSTEMATIC_GROUPS.values():
            systematics.extend(g)
        return systematics
    elif systematic_arg == 'all':
        systematics = []
        for g in SYSTEMATIC_GROUPS.values():
            systematics.extend(g)
        return systematics
    return SYSTEMATIC_GROUPS.get(systematic_arg, [])


def _build_jes_input_path(config, era, jes_systematic):
    """
    Build JES input path with special format for WH.

    JES format: {output_base}/{era}/{stage2}_{jes_systematic}_{stage1}_JESPt22/
    """
    import os
    paths = config['paths']
    versions = config['versions']
    stage1 = versions['stage1']
    stage2 = versions['stage2']

    dir_name = f"{stage2}_{jes_systematic}_{stage1}_JESPt22"
    return os.path.join(paths['output_base'], era, dir_name) + '/'


def get_ifVLL(config: dict) -> bool:
    """Get ifVLL option from config (default True)."""
    options = config.get('options', {})
    return options.get('ifVLL', True)


def submit_nominal(config: dict, era: str, process_data: bool = False,
                   dry_run: bool = False, quiet: bool = False):
    """Submit WH jobs for nominal (no systematic variations)."""
    channel = get_channel(config)
    versions = get_versions(config)
    hist_version = versions['hist']
    ifVLL = get_ifVLL(config)

    # Build input path (nominal - no systematic suffix)
    input_dir = build_stage2_path(config, era)
    # Remove trailing 'mc/' since mj.main() expects parent dir
    if input_dir.endswith('/mc/'):
        input_dir = input_dir[:-3]
    elif input_dir.endswith('/mc'):
        input_dir = input_dir[:-2]

    # Count input files
    mc_dir = input_dir + 'mc/' if not input_dir.endswith('/') else input_dir + '/mc/'
    mc_files = [f for f in os.listdir(mc_dir) if f.endswith('.root')] if os.path.isdir(mc_dir) else []

    data_files = []
    if process_data:
        data_dir = input_dir + 'data/' if not input_dir.endswith('/') else input_dir + '/data/'
        data_files = [f for f in os.listdir(data_dir) if f.endswith('.root')] if os.path.isdir(data_dir) else []

    if not quiet:
        print(f"  [nominal] {len(mc_files)} MC files")
        if process_data:
            print(f"  [nominal] {len(data_files)} data files")

    if dry_run:
        if not quiet:
            print(f"    [DRY RUN] Would submit {len(mc_files) + len(data_files)} jobs")
        return len(mc_files) + len(data_files)

    # Submit jobs
    mj.main(
        inputDir=input_dir,
        channel=channel,
        version=hist_version,
        exe=EXE,
        ifSys=1,  # Enable weight systematics for nominal
        justMC=not process_data,
        quiet=quiet,
        ifVLL=ifVLL
    )

    return len(mc_files) + len(data_files)


def submit_systematic(config: dict, era: str, systematic: str,
                      dry_run: bool = False, quiet: bool = False):
    """Submit WH jobs for a single systematic variation."""
    channel = get_channel(config)
    versions = get_versions(config)
    hist_version = versions['hist']
    ifVLL = get_ifVLL(config)

    # Build input path with systematic suffix
    # JES variations have special path format
    if systematic.startswith('JESup_') or systematic.startswith('JESDown_'):
        input_dir_base = _build_jes_input_path(config, era, systematic)
        input_dir = input_dir_base + 'mc/'
    else:
        input_dir = build_stage2_output(config, era, systematic=systematic, data_type='mc')
        # Remove trailing 'mc/' since mj.main() expects parent dir with trailing /
        if input_dir.endswith('/mc/'):
            input_dir_base = input_dir[:-3]
        elif input_dir.endswith('/mc'):
            input_dir_base = input_dir[:-2]
        else:
            input_dir_base = input_dir
        # Ensure trailing /
        if not input_dir_base.endswith('/'):
            input_dir_base += '/'

    # Check if input directory exists
    if not os.path.isdir(input_dir):
        if not quiet:
            print(f"  SKIP: {systematic} - directory not found: {input_dir}")
        return 0

    # Count input files
    mc_files = [f for f in os.listdir(input_dir) if f.endswith('.root')]
    file_count = len(mc_files)

    if not quiet:
        print(f"  [{systematic}] {file_count} MC files")

    if dry_run:
        if not quiet:
            print(f"    [DRY RUN] Would submit {file_count} jobs")
        return file_count

    # Submit jobs
    mj.main(
        inputDir=input_dir_base,
        channel=channel,
        version=hist_version,
        exe=EXE,
        ifSys=0,  # No weight systematics for energy scale variations
        justMC=True,  # Only MC for systematic variations
        quiet=quiet,
        ifVLL=ifVLL
    )

    return file_count


def main():
    parser = create_parser()
    args = parser.parse_args()

    # Validate arguments
    if args.no_data and args.systematic not in ['nominal', 'complete']:
        parser.error("--no-data only applies to nominal (systematics never include data)")

    config = load_config(args.config)
    eras = [args.era] if args.era else config['eras']
    systematics = get_systematics(args.systematic)

    channel = get_channel(config)
    versions = get_versions(config)

    is_nominal_only = args.systematic == 'nominal'
    is_complete = args.systematic == 'complete'
    has_nominal = 'nominal' in systematics

    if not args.quiet:
        print("=== WH Job Submission ===")
        print(f"Config: {args.config}")
        print(f"Channel: {channel}")
        print(f"Hist version: {versions['hist']}")
        print(f"Eras: {', '.join(eras)}")
        if is_nominal_only:
            print(f"Mode: Nominal only (Stage 3)")
            if args.no_data:
                print(f"Processing: MC only")
            else:
                print(f"Processing: MC + Data")
        elif is_complete:
            print(f"Mode: Complete (Nominal + All Systematics)")
            print(f"Stage 3: Nominal")
            print(f"Stage 3.1: {len(systematics) - 1} systematic variations")
            if args.no_data:
                print(f"Processing: MC only")
            else:
                print(f"Processing: MC + Data (nominal), MC only (systematics)")
        else:
            print(f"Mode: Systematics only (Stage 3.1)")
            print(f"Systematic group: {args.systematic} ({len(systematics)} variations)")
        if args.dry_run:
            print("[DRY RUN MODE]")
        print()

    total_jobs = 0

    for era in eras:
        if not args.quiet:
            print(f"Era: {era}")

        era_jobs = 0
        skipped = 0
        for systematic in systematics:
            if systematic == 'nominal':
                jobs = submit_nominal(config, era, not args.no_data, args.dry_run, args.quiet)
                era_jobs += jobs
            else:
                # For systematics, always use quiet=True to suppress per-file output
                jobs = submit_systematic(config, era, systematic, args.dry_run, quiet=True)
                era_jobs += jobs
                if jobs == 0:
                    skipped += 1

        total_jobs += era_jobs
        if not args.quiet:
            if len(systematics) > 1:
                print(f"  Submitted: {len(systematics) - skipped} variations, {era_jobs} jobs" + (f" (skipped {skipped})" if skipped else ""))
            print()

    if not args.quiet:
        print("=== Summary ===")
        print(f"Total eras: {len(eras)}")
        if is_nominal_only:
            print(f"Mode: Nominal only")
        elif is_complete:
            print(f"Mode: Complete (nominal + {len(systematics) - 1} systematics)")
        else:
            print(f"Total systematic variations: {len(systematics)}")
        print(f"Total jobs {'would be ' if args.dry_run else ''}submitted: {total_jobs}")
        print()
        print("Monitor with: hep_q -u $USER")

    # Update workflow state after submission (only if not dry run)
    if not args.dry_run and total_jobs > 0:
        try:
            state = get_workflow_state(channel, args.config)

            if is_complete:
                # Update both Stage 3 and 3.1
                state.update_stage('3', eras[0] if len(eras) == 1 else 'multiple',
                                 'submitted', 'WH_nominal')
                state.update_stage('3.1', eras[0] if len(eras) == 1 else 'multiple',
                                 'submitted', 'WH_all_systematics')
                state.log_execution('3+3.1', eras[0] if len(eras) == 1 else 'multiple',
                                  'WH_complete', 'submitted',
                                  config=args.config, total_jobs=total_jobs,
                                  variations=len(systematics), eras=eras)
                if not args.quiet:
                    print(f"\n[WorkflowState] Updated: Stage 3+3.1, WH_complete, submitted")
            elif is_nominal_only:
                state.update_stage('3', eras[0] if len(eras) == 1 else 'multiple',
                                 'submitted', 'WH_nominal')
                state.log_execution('3', eras[0] if len(eras) == 1 else 'multiple',
                                  'WH_nominal', 'submitted',
                                  config=args.config, total_jobs=total_jobs, eras=eras)
                if not args.quiet:
                    print(f"\n[WorkflowState] Updated: Stage 3, WH_nominal, submitted")
            else:
                state.update_stage('3.1', eras[0] if len(eras) == 1 else 'multiple',
                                 'submitted', f'WH_{args.systematic}_systematics')
                state.log_execution('3.1', eras[0] if len(eras) == 1 else 'multiple',
                                  f'WH_{args.systematic}_systematics', 'submitted',
                                  config=args.config, total_jobs=total_jobs,
                                  variations=len(systematics), eras=eras)
                if not args.quiet:
                    print(f"\n[WorkflowState] Updated: Stage 3.1, {args.systematic} systematics, submitted")
        except Exception as e:
            if not args.quiet:
                print(f"[WARNING] Could not update workflow state: {e}")


if __name__ == '__main__':
    main()
