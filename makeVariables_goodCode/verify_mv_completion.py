#!/usr/bin/env python3
"""
Verify Stage 2 MV completion for all systematic variations.
Checks that all expected output files exist for nominal and all 74 systematics.
Optionally validates ROOT file integrity.

Usage:
    # Quick check (files exist)
    python3 verify_mv_completion.py --config ../config/analysis_config.yaml --era 2018

    # Full validation (files exist + ROOT integrity)
    python3 verify_mv_completion.py --config ../config/analysis_config.yaml --era 2018 --validate

    # Nominal only
    python3 verify_mv_completion.py --config ../config/analysis_config.yaml --era 2017 --nominal-only
"""

import os
import argparse
from pathlib import Path
from collections import defaultdict

# Try to import ROOT for validation
try:
    import ROOT
    ROOT.gErrorIgnoreLevel = ROOT.kError  # Suppress warnings
    ROOT_AVAILABLE = True
except ImportError:
    ROOT_AVAILABLE = False

# Import workflow utilities from fourtop package
try:
    from fourtop.workflow import load_config, build_stage2_path
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False
    import yaml
    def load_config(path):
        with open(path) as f:
            return yaml.safe_load(f)

# Systematic variations
TES_VARIATIONS = [f"TESdm{dm}{ud}" for dm in ["0", "1", "10", "11"] for ud in ["Up", "Down"]]
OTHER_VARIATIONS = ["JERUp", "JERDown", "METUp", "METDown", "EleScaleUp", "EleScaleDown"]

# 60 JES sources
JES_SOURCES = [
    "Absolute", "AbsoluteCal", "AbsolutePt", "AbsoluteScale", "AbsoluteStat",
    "FlavorQCD", "Fragmentation", "PileUpDataMC", "PileUpPt22", "PileUpPtBB",
    "PileUpPtEC1", "PileUpPtEC2", "PileUpPtHF", "PileUpPtRef", "RelativeBal",
    "RelativeFSR", "RelativeJEREC1", "RelativeJEREC2", "RelativeJERHF",
    "RelativePtBB", "RelativePtEC1", "RelativePtEC2", "RelativePtHF",
    "RelativeSample", "RelativeStatEC", "RelativeStatFSR", "RelativeStatHF",
    "SinglePionECAL", "SinglePionHCAL", "TimePtEta"
]


def validate_root_file(filepath):
    """
    Validate a ROOT file is readable and has expected content.

    Returns:
        (is_valid, error_message)
    """
    if not ROOT_AVAILABLE:
        return True, None  # Skip validation if ROOT not available

    try:
        f = ROOT.TFile.Open(str(filepath))
        if not f or f.IsZombie():
            return False, "Zombie/corrupted file"

        # Check file has keys (not empty)
        keys = f.GetListOfKeys()
        if not keys or keys.GetSize() == 0:
            f.Close()
            return False, "Empty file (no keys)"

        # Check for expected tree
        tree = f.Get("newtree")
        if not tree:
            f.Close()
            return False, "Missing 'newtree' tree"

        # Check tree has entries
        entries = tree.GetEntries()
        if entries == 0:
            f.Close()
            return False, "Tree has 0 entries"

        f.Close()
        return True, None

    except Exception as e:
        return False, f"Exception: {str(e)}"


def get_expected_samples(stage1_path):
    """Get list of expected samples from Stage 1 output."""
    mc_path = Path(stage1_path) / "mc"
    if not mc_path.exists():
        return []

    samples = []
    for item in mc_path.iterdir():
        if item.is_dir():
            # Check if directory has .root files
            root_files = list(item.glob("*.root"))
            if root_files:
                samples.append(item.name)
    return sorted(samples)


def check_mv_output(base_path, samples, validate=False, verbose=False):
    """
    Check if MV output exists for all samples.

    Args:
        base_path: Base path to MV output
        samples: List of expected sample names
        validate: If True, validate ROOT file integrity
        verbose: If True, print detailed progress

    Returns:
        (found, missing, corrupted) where:
        - found: list of samples with valid output
        - missing: list of samples with no output
        - corrupted: list of (sample, error) tuples for invalid files
    """
    mc_path = Path(base_path) / "mc"
    if not mc_path.exists():
        return [], samples, []

    found = []
    missing = []
    corrupted = []

    for sample in samples:
        sample_path = mc_path / sample
        if sample_path.exists():
            root_files = list(sample_path.glob("*.root"))
            if root_files:
                if validate:
                    # Validate the first ROOT file (merged output)
                    is_valid, error = validate_root_file(root_files[0])
                    if is_valid:
                        found.append(sample)
                    else:
                        corrupted.append((sample, error))
                else:
                    found.append(sample)
            else:
                missing.append(sample)
        else:
            missing.append(sample)

    return found, missing, corrupted


def verify_era(config, era, validate=False, verbose=False):
    """Verify MV completion for a single era."""
    stage1_version = config['versions']['stage1']
    stage2_version = config['versions']['stage2']
    base_dir = config['paths']['forMVA_base']
    stage1_base = config['paths']['stage1_base']

    # Get expected samples from Stage 1
    stage1_path = f"{stage1_base}/UL{era}/{stage1_version}"
    expected_samples = get_expected_samples(stage1_path)

    if not expected_samples:
        print(f"  WARNING: No samples found in Stage 1: {stage1_path}")
        return {}

    print(f"  Expected samples: {len(expected_samples)}")
    if validate:
        print(f"  ROOT validation: ENABLED")

    results = {}

    # Check nominal
    nominal_path = f"{base_dir}/{era}/{stage2_version}_{stage1_version}"
    found, missing, corrupted = check_mv_output(nominal_path, expected_samples, validate, verbose)
    results['nominal'] = {'found': len(found), 'missing': missing, 'corrupted': corrupted, 'path': nominal_path}

    # Check TES/JER/MET/EleScale variations
    for var in TES_VARIATIONS + OTHER_VARIATIONS:
        var_path = f"{base_dir}/{era}/{stage2_version}_{stage1_version}_{var}"
        found, missing, corrupted = check_mv_output(var_path, expected_samples, validate, verbose)
        results[var] = {'found': len(found), 'missing': missing, 'corrupted': corrupted, 'path': var_path}

    # Check JES variations (60 sources x 2 directions = 120, but stored as 60 dirs with up/down)
    for source in JES_SOURCES:
        for direction in ["up", "Down"]:  # Note: up is lowercase, Down is uppercase
            var_name = f"JES{direction}_{source}"
            var_path = f"{base_dir}/{era}/{stage2_version}_JES{direction}_{source}_{stage1_version}_JESPt22"
            found, missing, corrupted = check_mv_output(var_path, expected_samples, validate, verbose)
            results[var_name] = {'found': len(found), 'missing': missing, 'corrupted': corrupted, 'path': var_path}

    return results


def print_summary(results, expected_count):
    """Print summary of verification results."""
    complete = []
    incomplete = []
    missing_dirs = []
    has_corrupted = []

    for var, data in results.items():
        corrupted = data.get('corrupted', [])
        if corrupted:
            has_corrupted.append((var, corrupted))
        if data['found'] == expected_count and not data['missing'] and not corrupted:
            complete.append(var)
        elif data['found'] == 0 and not corrupted:
            missing_dirs.append(var)
        elif data['missing'] or corrupted:
            incomplete.append((var, data['found'], data['missing'], corrupted))

    print(f"\n  Complete ({len(complete)}/{len(results)}):")
    if len(complete) <= 10:
        for var in complete:
            print(f"    - {var}")
    else:
        print(f"    [nominal + {len(complete)-1} systematics]")

    if has_corrupted:
        print(f"\n  CORRUPTED FILES ({len(has_corrupted)} variations affected):")
        for var, corrupted_list in has_corrupted:
            print(f"    - {var}:")
            for sample, error in corrupted_list[:5]:
                print(f"        {sample}: {error}")
            if len(corrupted_list) > 5:
                print(f"        ... and {len(corrupted_list) - 5} more")

    if incomplete:
        print(f"\n  Incomplete ({len(incomplete)}):")
        for var, found, missing, corrupted in incomplete:
            status_parts = []
            if missing:
                status_parts.append(f"missing: {len(missing)}")
            if corrupted:
                status_parts.append(f"corrupted: {len(corrupted)}")
            print(f"    - {var}: {found}/{expected_count} ({', '.join(status_parts)})")
            if len(missing) <= 5:
                for m in missing:
                    print(f"        [missing] {m}")

    if missing_dirs:
        print(f"\n  Missing directories ({len(missing_dirs)}):")
        for var in missing_dirs[:20]:
            print(f"    - {var}")
        if len(missing_dirs) > 20:
            print(f"    ... and {len(missing_dirs) - 20} more")

    all_valid = len(complete) == len(results) and not has_corrupted
    return all_valid


def main():
    parser = argparse.ArgumentParser(description='Verify MV completion for all systematics')
    parser.add_argument('--config', required=True, help='Path to analysis config YAML')
    parser.add_argument('--era', required=True, help='Era to check (2018, 2017, etc.)')
    parser.add_argument('--validate', action='store_true',
                        help='Validate ROOT file integrity (slower but catches corrupted files)')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')
    parser.add_argument('--nominal-only', action='store_true', help='Only check nominal')
    args = parser.parse_args()

    if args.validate and not ROOT_AVAILABLE:
        print("WARNING: --validate requires ROOT. Install PyROOT or run with CMSSW environment.")
        print("Continuing without validation...")
        args.validate = False

    config = load_config(args.config)

    print(f"\n{'='*60}")
    print(f"MV Verification: {args.era}")
    print(f"{'='*60}")
    print(f"Config: {args.config}")
    print(f"Stage1: {config['versions']['stage1']}")
    print(f"Stage2: {config['versions']['stage2']}")
    print(f"Validation: {'ENABLED' if args.validate else 'disabled (use --validate)'}")

    # Get expected sample count
    stage1_path = f"{config['paths']['stage1_base']}/UL{args.era}/{config['versions']['stage1']}"
    expected_samples = get_expected_samples(stage1_path)
    expected_count = len(expected_samples)

    results = verify_era(config, args.era, args.validate, args.verbose)

    if args.nominal_only:
        results = {'nominal': results.get('nominal', {})}

    all_complete = print_summary(results, expected_count)

    print(f"\n{'='*60}")
    if all_complete:
        print("STATUS: ALL COMPLETE" + (" (validated)" if args.validate else ""))
        return 0
    else:
        print("STATUS: INCOMPLETE")
        return 1


if __name__ == '__main__':
    sys.exit(main())
