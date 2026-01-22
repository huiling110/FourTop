#!/usr/bin/env python3
"""Submit WH (Stage 3) jobs for systematic variations.

Supports TES, JER, MET, EleScale systematic variations.
JES variations are handled separately (require JES-specific OS/MV processing).

Usage:
    # Submit all systematics for 2018:
    python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

    # Submit only TES systematics:
    python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --group TES

    # Dry run to see what would be submitted:
    python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --dry-run

Via workflow runner:
    python3 run_workflow.py --config config/analysis_config_1tau0l_TTBBtest.yaml --stage 3.1 --era 2018
"""
import argparse
import os

import makeJob_forWriteHist as mj

# Use fourtop package for all imports
from fourtop.workflow import (
    load_config, build_stage2_output, get_channel, get_versions, get_workflow_state
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
    'JES': [],  # Populated below with Up/Down for each source
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
        description='Submit WH jobs for systematic variations (TES, JER, MET, EleScale)',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''
Examples:
  # All systematics for 2018:
  python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

  # Only TES for all eras:
  python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --group TES

  # Dry run:
  python3 makeJob_WH_forJES.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --dry-run
        '''
    )
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file')
    parser.add_argument('--era', '-e', type=str,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process (default: all from config)')
    parser.add_argument('--group', '-g', type=str,
                        choices=['TES', 'JER', 'MET', 'EleScale', 'JES', 'all'],
                        default='all',
                        help='Systematic group to submit (default: all). JES has 54 variations (27 sources × Up/Down)')
    parser.add_argument('--dry-run', action='store_true',
                        help='Show what would be done without submitting')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Reduce output verbosity')
    return parser


def get_systematics(group: str) -> list:
    """Get list of systematic variations for a group."""
    if group == 'all':
        systematics = []
        for g in SYSTEMATIC_GROUPS.values():
            systematics.extend(g)
        return systematics
    return SYSTEMATIC_GROUPS.get(group, [])


def _build_jes_input_path(config, era, jes_systematic):
    """
    Build JES input path with special format for WH.

    JES format: {output_base}/{era}/{stage2}_{jes_systematic}_{stage1}_JESPt22/

    Args:
        config: Configuration dictionary.
        era: Era string.
        jes_systematic: JES systematic (e.g., 'JESup_AbsoluteMPFBias_AK4PFchs').

    Returns:
        Path with trailing / (no mc/data subdirectory).
    """
    import os
    paths = config['paths']
    versions = config['versions']
    stage1 = versions['stage1']
    stage2 = versions['stage2']

    # Format: {stage2}_{jes_systematic}_{stage1}_JESPt22
    dir_name = f"{stage2}_{jes_systematic}_{stage1}_JESPt22"

    return os.path.join(paths['output_base'], era, dir_name) + '/'


def submit_systematic(config: dict, era: str, systematic: str, dry_run: bool = False, quiet: bool = False):
    """Submit WH jobs for a single systematic variation."""
    channel = get_channel(config)
    versions = get_versions(config)
    hist_version = versions['hist']

    # Build input path with systematic suffix
    # JES variations have special path format
    if systematic.startswith('JESup_') or systematic.startswith('JESDown_'):
        input_dir_base = _build_jes_input_path(config, era, systematic)
        input_dir = input_dir_base + 'mc/'
    else:
        input_dir = build_stage2_output(config, era, systematic=systematic, data_type='mc')
        # Remove trailing 'mc/' since mj.main() expects parent dir with trailing /
        if input_dir.endswith('/mc/'):
            input_dir_base = input_dir[:-3]  # Remove 'mc/' but keep trailing /
        elif input_dir.endswith('/mc'):
            input_dir_base = input_dir[:-2]  # Remove 'mc' but keep trailing /
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
        ifSys=0,  # No additional weight systematics for energy scale variations
        justMC=True  # Only MC for systematic variations
    )

    return file_count


def main():
    parser = create_parser()
    args = parser.parse_args()

    # Deprecation warning
    print("=" * 70)
    print("DEPRECATION WARNING:")
    print("  makeJob_WH_forJES.py is deprecated.")
    print("  Please use: makeJob_WH.py --systematic GROUP")
    print("  Example: python3 makeJob_WH.py --config CONFIG --era 2018 --systematic TES")
    print("=" * 70)
    print()

    config = load_config(args.config)
    eras = [args.era] if args.era else config['eras']
    systematics = get_systematics(args.group)

    channel = get_channel(config)
    versions = get_versions(config)

    if not args.quiet:
        print("=== WH Systematic Job Submission ===")
        print(f"Config: {args.config}")
        print(f"Channel: {channel}")
        print(f"Hist version: {versions['hist']}")
        print(f"Eras: {', '.join(eras)}")
        print(f"Systematic group: {args.group} ({len(systematics)} variations)")
        if args.dry_run:
            print("[DRY RUN MODE]")
        print()

    total_jobs = 0

    for era in eras:
        if not args.quiet:
            print(f"Era: {era}")

        for systematic in systematics:
            jobs = submit_systematic(config, era, systematic, args.dry_run, args.quiet)
            total_jobs += jobs

        if not args.quiet:
            print()

    if not args.quiet:
        print("=== Summary ===")
        print(f"Total eras: {len(eras)}")
        print(f"Total systematic variations: {len(systematics)}")
        print(f"Total jobs {'would be ' if args.dry_run else ''}submitted: {total_jobs}")
        print()
        print("Monitor with: hep_q -u $USER")

    # Update workflow state after submission (only if not dry run)
    if not args.dry_run and total_jobs > 0:
        try:
            state = get_workflow_state(channel, args.config)
            state.update_stage('3.1', eras[0] if len(eras) == 1 else 'multiple',
                             'submitted', f'WH_{args.group}_systematics')
            state.log_execution('3.1', eras[0] if len(eras) == 1 else 'multiple',
                              f'WH_{args.group}_systematics', 'submitted',
                              config=args.config, total_jobs=total_jobs,
                              variations=len(systematics), eras=eras)
            if not args.quiet:
                print(f"\n[WorkflowState] Updated: Stage 3.1, {args.group} systematics, submitted")
        except Exception as e:
            if not args.quiet:
                print(f"[WARNING] Could not update workflow state: {e}")


if __name__ == '__main__':
    main()
