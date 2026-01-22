#!/usr/bin/env python3
"""
Submit Stage 2 (MV) jobs for all systematic variations.

Submits MV jobs for: TES (by decay mode), JER, MET, EleScale variations.
JES variations with 27 sources are handled separately.

Usage:
    # All systematics for all eras in config
    python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml

    # Specific era
    python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018

    # Specific systematic group
    python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --group TES

    # Dry run
    python3 makeJob_MV_JESVariation.py --config ../../config/analysis_config_1tau0l_TTBBtest.yaml --era 2018 --dry-run
"""
import argparse
import os
import subprocess

# Use fourtop package for all imports
from fourtop.workflow import load_config, get_eras
from fourtop.constants.jes import JESVariationList as JES_SOURCES, validate_jes_list

# Validate C++/Python JES list synchronization at import time
# This prevents submitting jobs with mismatched JES indices
validate_jes_list()

# Import the main submission script
import makeJob_makeVaribles_forBDT as mj

# Systematic variations by group
SYSTEMATICS = {
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
    SYSTEMATICS['JES'].append(f'JESup_{source}')
    SYSTEMATICS['JES'].append(f'JESDown_{source}')

ALL_SYSTEMATICS = []
for group in SYSTEMATICS.values():
    ALL_SYSTEMATICS.extend(group)


def create_parser():
    """Create argument parser."""
    parser = argparse.ArgumentParser(
        description='Submit Stage 2 (MV) jobs for systematic variations',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument(
        '--config', '-c', required=True,
        help='Path to YAML config file (required)'
    )
    parser.add_argument(
        '--era', '-e',
        help='Era to process (default: all from config)'
    )
    parser.add_argument(
        '--group', '-g', choices=['TES', 'JER', 'MET', 'EleScale', 'JES', 'all'],
        default='all',
        help='Systematic group to process (default: all). JES has 54 variations (27 sources × Up/Down)'
    )
    parser.add_argument(
        '--mc-only', action='store_true', default=True,
        help='Process only MC samples (default: True for systematics)'
    )
    parser.add_argument(
        '--dry-run', '-n', action='store_true',
        help='Show commands without submitting jobs'
    )
    parser.add_argument(
        '--quiet', '-q', action='store_true',
        help='Reduce output verbosity'
    )
    return parser


def submit_systematic(config_path, era, systematic, mc_only=True, dry_run=False, quiet=False):
    """Submit MV jobs for a single systematic variation.

    For JES variations (JESup_* or JESDown_*), uses special handling:
    - Input: --sys JESPt22
    - JES type: --jes-type 1 (up) or 2 (down)
    - JES index: --jes-variation INDEX
    """
    cmd = [
        sys.executable,
        os.path.join(os.path.dirname(__file__), 'makeJob_makeVaribles_forBDT.py'),
        '--config', config_path,
        '--mc-only',
    ]

    # Handle JES variations specially
    # JES uses different input (JESPt22) and output (JESup_SOURCE or JESDown_SOURCE) paths
    if systematic.startswith('JESup_') or systematic.startswith('JESDown_'):
        # Parse JES variation: JESup_SOURCE or JESDown_SOURCE
        if systematic.startswith('JESup_'):
            source = systematic[6:]  # Remove 'JESup_'
            jes_type = '1'  # up
        else:
            source = systematic[8:]  # Remove 'JESDown_'
            jes_type = '2'  # down

        # Find source index
        try:
            jes_index = JES_SOURCES.index(source)
        except ValueError:
            if not quiet:
                print(f"  ERROR: Unknown JES source: {source}")
            return False

        # Input: _JESPt22, Output: _JESup_SOURCE or _JESDown_SOURCE
        cmd.extend(['--sys', 'JESPt22'])
        cmd.extend(['--output-sys', systematic])  # e.g., JESup_AbsoluteMPFBias_AK4PFchs
        cmd.extend(['--jes-type', jes_type])
        cmd.extend(['--jes-variation', str(jes_index)])
    else:
        # Standard systematics (TES, JER, MET, EleScale)
        cmd.extend(['--sys', systematic])

    if era:
        cmd.extend(['--era', era])
    if dry_run:
        cmd.append('--dry-run')
    if quiet:
        cmd.append('--quiet')

    if not quiet:
        print(f"\n{'='*60}")
        print(f"Submitting: {systematic}")
        print(f"{'='*60}")

    result = subprocess.run(cmd, check=False)
    return result.returncode == 0


def main():
    args = create_parser().parse_args()

    # Load config to validate and show info
    config = load_config(args.config)

    # Get systematics to process
    if args.group == 'all':
        systematics = ALL_SYSTEMATICS
    else:
        systematics = SYSTEMATICS[args.group]

    if not args.quiet:
        print(f"=== Stage 2 (MV) Systematic Variations ===")
        print(f"Config: {args.config}")
        print(f"Era: {args.era or 'all from config'}")
        print(f"Group: {args.group}")
        print(f"Systematics to process: {len(systematics)}")
        for sys in systematics:
            print(f"  - {sys}")
        print()

    if args.dry_run:
        print("[DRY RUN MODE]")
        print()

    # Submit jobs for each systematic
    success_count = 0
    failed = []

    for systematic in systematics:
        success = submit_systematic(
            args.config, args.era, systematic,
            mc_only=args.mc_only, dry_run=args.dry_run, quiet=args.quiet
        )
        if success:
            success_count += 1
        else:
            failed.append(systematic)

    # Summary
    print(f"\n{'='*60}")
    print(f"Summary: {success_count}/{len(systematics)} successful")
    if failed:
        print(f"Failed: {', '.join(failed)}")
    print(f"{'='*60}")


if __name__ == '__main__':
    main()
