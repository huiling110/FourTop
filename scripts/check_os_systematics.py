#!/usr/bin/env python3
"""
Check OS outputs for corrupted, missing, or TRUNCATED files.
Compares outputs against NOMINAL to detect truncated files (incomplete processing).

Usage:
    python3 check_os_systematics.py --config CONFIG --era 2018 [--fix]
    python3 check_os_systematics.py --config CONFIG --era 2018 --systematic JESPt22 [--fix]
    python3 check_os_systematics.py --config CONFIG --era 2018 --nominal-only [--fix]
    python3 check_os_systematics.py --config CONFIG --era 2018 --summary  # Show total entries comparison

The script detects:
- Missing files (in input but not in output)
- Corrupted files (can't read ROOT tree)
- Truncated files (significantly fewer entries than nominal - indicates job failure)

Summary mode (--summary) shows total entries comparison: nominal vs each systematic per sample.
"""

import os
import argparse
import subprocess
from typing import Dict, List, Tuple, Optional

from fourtop.workflow import (
    load_config, build_stage1_output, build_stage1_input,
    ERA_TO_UL, ERA_TO_NANOAOD, get_channel_if1tau2l
)

# Threshold for truncation detection (files with < this % of nominal events are truncated)
TRUNCATION_THRESHOLD = 0.90  # 90% - flag if systematic has <90% of nominal entries
# For JES (22 GeV cut vs 25 GeV), systematic should have MORE entries
JES_MIN_RATIO = 0.98  # JES should have at least 98% of nominal (usually more)

# All systematic variations
SYSTEMATICS = {
    'JES': ['JESPt22'],
    'TES': ['TESdm0Up', 'TESdm0Down', 'TESdm1Up', 'TESdm1Down',
            'TESdm10Up', 'TESdm10Down', 'TESdm11Up', 'TESdm11Down'],
    'JER': ['JERUp', 'JERDown'],
    'MET': ['METUp', 'METDown'],
    'EleScale': ['EleScaleUp', 'EleScaleDown'],
}

ALL_SYSTEMATICS = []
for group in SYSTEMATICS.values():
    ALL_SYSTEMATICS.extend(group)


def get_expected_samples(config: dict, era: str, systematic: str = None) -> set:
    """
    Get set of sample names that were actually submitted (have job scripts).

    Uses the job scripts directory to determine what was submitted,
    not the input directory (which may have more samples).
    """
    # Get output directory where job scripts are stored
    output_dir = build_stage1_output(config, era, systematic)
    jobs_dir = os.path.join(output_dir, 'jobs_eachYear')

    era_ul = ERA_TO_UL.get(era, f'UL{era}')
    era_jobs_dir = os.path.join(jobs_dir, era_ul)

    if not os.path.exists(era_jobs_dir):
        return set()

    expected = set()
    for item in os.listdir(era_jobs_dir):
        item_path = os.path.join(era_jobs_dir, item)
        # Sample directories contain job scripts, skip .sh and .csv files
        if os.path.isdir(item_path):
            expected.add(item)

    return expected


def get_file_entries(filepath: str) -> int:
    """Get number of entries in a ROOT file's tree."""
    try:
        import ROOT
        ROOT.gROOT.SetBatch(True)
        ROOT.gErrorIgnoreLevel = ROOT.kError

        f = ROOT.TFile.Open(filepath)
        if not f or f.IsZombie():
            return -1

        t = f.Get("tree")
        if not t:
            f.Close()
            return -1

        entries = t.GetEntries()
        f.Close()
        return entries
    except Exception as e:
        return -1


def get_input_files(config: dict, era: str, sample: str) -> List[str]:
    """Get list of input NanoAOD files for a sample."""
    ul_era = ERA_TO_UL.get(era, f'UL{era}')
    input_base = f"/publicfs/cms/data/TopQuark/nanoAOD/{ul_era}_v9"
    sample_dir = os.path.join(input_base, sample)

    if not os.path.exists(sample_dir):
        return []

    return [f for f in os.listdir(sample_dir) if f.endswith('.root')]


def get_nominal_entries_cache(config: dict, era: str, verbose: bool = True) -> Dict[str, int]:
    """
    Build a cache of nominal entries for all files.
    Returns dict: {sample/filename: entries}
    """
    cache = {}
    nominal_dir = build_stage1_output(config, era, None)  # None = nominal
    nominal_mc = os.path.join(nominal_dir, 'mc')

    if not os.path.exists(nominal_mc):
        if verbose:
            print(f"  Warning: Nominal directory not found: {nominal_mc}")
        return cache

    for sample in os.listdir(nominal_mc):
        sample_dir = os.path.join(nominal_mc, sample)
        if not os.path.isdir(sample_dir):
            continue

        for f in os.listdir(sample_dir):
            if f.endswith('.root'):
                filepath = os.path.join(sample_dir, f)
                entries = get_file_entries(filepath)
                if entries > 0:
                    cache[f"{sample}/{f}"] = entries

    return cache


def check_os_output(config: dict, era: str, systematic: Optional[str],
                    verbose: bool = True, nominal_cache: Dict[str, int] = None) -> Dict[str, List[Tuple[str, int, int, float]]]:
    """
    Check OS output against NOMINAL files to detect truncated/incomplete files.

    Compares systematic output against nominal to detect:
    - Missing files (in nominal but not in systematic)
    - Corrupted files (can't read ROOT tree)
    - Truncated files (significantly fewer entries than nominal)

    Args:
        config: Config dict
        era: Era string
        systematic: Systematic name (None for nominal)
        verbose: Print progress
        nominal_cache: Pre-built cache of nominal entries (optional)

    Returns dict with:
        'missing': [(filename, nom_entries), ...]
        'corrupted': [(filename, nom_entries, 0, 0.0), ...]
        'truncated': [(filename, nom_entries, sys_entries, ratio), ...]
        'ok': [(filename, nom_entries, sys_entries, ratio), ...]
    """
    results = {'missing': [], 'corrupted': [], 'truncated': [], 'ok': [], 'extra': []}

    # Get expected samples from job scripts directory
    expected_samples = get_expected_samples(config, era, systematic)

    if not expected_samples:
        if verbose:
            print(f"  No expected samples found")
        return results

    # Get output directory for this systematic
    output_dir = build_stage1_output(config, era, systematic)
    output_mc = os.path.join(output_dir, 'mc')

    if not os.path.exists(output_mc):
        if verbose:
            print(f"  Output directory not found (may be archived): {output_mc}")
        return results

    # For nominal check, compare against input files
    if systematic is None:
        input_dir = build_stage1_input(config, era)
        input_mc = os.path.join(input_dir, 'mc')

        if not os.path.exists(input_mc):
            if verbose:
                print(f"  Input directory not found: {input_mc}")
            return results

        # Check each expected sample against input
        for sample in sorted(expected_samples):
            input_sample_dir = os.path.join(input_mc, sample)
            output_sample_dir = os.path.join(output_mc, sample)

            if not os.path.exists(input_sample_dir):
                continue

            input_files = set(f for f in os.listdir(input_sample_dir) if f.endswith('.root'))
            if not input_files:
                continue

            if not os.path.exists(output_sample_dir):
                for f in input_files:
                    results['missing'].append((f"{sample}/{f}", 1))
                continue

            output_files = set(f for f in os.listdir(output_sample_dir) if f.endswith('.root'))

            for f in input_files - output_files:
                results['missing'].append((f"{sample}/{f}", 1))

            for f in input_files & output_files:
                output_path = os.path.join(output_sample_dir, f)
                entries = get_file_entries(output_path)
                if entries < 0:
                    results['corrupted'].append((f"{sample}/{f}", 1, 0, 0.0))
                else:
                    results['ok'].append((f"{sample}/{f}", 1, entries, 1.0))

        return results

    # For systematic variations, compare against NOMINAL
    # Build nominal cache if not provided
    if nominal_cache is None:
        if verbose:
            print(f"  Building nominal entries cache...")
        nominal_cache = get_nominal_entries_cache(config, era, verbose=False)

    if not nominal_cache:
        if verbose:
            print(f"  Warning: No nominal entries found for comparison")
        return results

    # Determine threshold based on systematic type
    is_jes = systematic == 'JESPt22'
    threshold = JES_MIN_RATIO if is_jes else TRUNCATION_THRESHOLD

    # Check each expected sample
    for sample in sorted(expected_samples):
        output_sample_dir = os.path.join(output_mc, sample)

        # Get nominal files for this sample
        sample_nominal_files = {k: v for k, v in nominal_cache.items() if k.startswith(f"{sample}/")}

        if not sample_nominal_files:
            continue  # No nominal files for this sample

        if not os.path.exists(output_sample_dir):
            # Entire sample missing in systematic output
            for filepath, nom_entries in sample_nominal_files.items():
                results['missing'].append((filepath, nom_entries))
            continue

        # Get output files
        output_files = set(f for f in os.listdir(output_sample_dir) if f.endswith('.root'))

        # Check each nominal file
        for filepath, nom_entries in sample_nominal_files.items():
            filename = filepath.split('/', 1)[1]  # Remove sample prefix

            if filename not in output_files:
                results['missing'].append((filepath, nom_entries))
                continue

            # Check entries
            output_path = os.path.join(output_sample_dir, filename)
            sys_entries = get_file_entries(output_path)

            if sys_entries < 0:
                results['corrupted'].append((filepath, nom_entries, 0, 0.0))
            elif nom_entries > 0:
                ratio = sys_entries / nom_entries
                if ratio < threshold:
                    # Truncated - significantly fewer entries than nominal
                    results['truncated'].append((filepath, nom_entries, sys_entries, ratio))
                else:
                    results['ok'].append((filepath, nom_entries, sys_entries, ratio))
            else:
                results['ok'].append((filepath, nom_entries, sys_entries, 1.0))

    return results


def check_systematic(config: dict, era: str, systematic: str,
                     verbose: bool = True) -> Dict[str, List[Tuple[str, int, int, float]]]:
    """
    Check a systematic variation against INPUT files.
    Wrapper for backwards compatibility.
    """
    return check_os_output(config, era, systematic, verbose)


def get_sample_total_entries(config: dict, era: str, systematic: Optional[str] = None,
                             exclude_qcd: bool = True) -> Dict[str, int]:
    """
    Get total entries per sample for a given systematic (or nominal).

    Args:
        config: Config dict
        era: Era string
        systematic: Systematic name (None for nominal)
        exclude_qcd: Skip QCD samples (data-driven, no MC systematics)

    Returns:
        Dict mapping sample name to total entries
    """
    import ROOT
    ROOT.gROOT.SetBatch(True)
    ROOT.gErrorIgnoreLevel = ROOT.kError

    output_dir = build_stage1_output(config, era, systematic)
    output_mc = os.path.join(output_dir, 'mc')

    totals = {}

    if not os.path.exists(output_mc):
        return totals

    for sample in os.listdir(output_mc):
        if exclude_qcd and sample.startswith('qcd'):
            continue

        sample_dir = os.path.join(output_mc, sample)
        if not os.path.isdir(sample_dir):
            continue

        total = 0
        for f in os.listdir(sample_dir):
            if not f.endswith('.root'):
                continue
            filepath = os.path.join(sample_dir, f)
            entries = get_file_entries(filepath)
            if entries > 0:
                total += entries

        totals[sample] = total

    return totals


def print_summary_report(config: dict, era: str, systematics: List[str],
                         exclude_qcd: bool = True, key_processes: List[str] = None):
    """
    Print summary report comparing nominal vs systematic total entries per sample.

    Args:
        config: Config dict
        era: Era string
        systematics: List of systematic names to compare
        exclude_qcd: Skip QCD samples
        key_processes: If provided, show these processes first with details
    """
    print("\n" + "=" * 100)
    print(f"ENTRY COMPARISON SUMMARY: Nominal vs Systematics ({era})")
    print("=" * 100)

    # Get nominal entries
    print("Loading nominal entries...")
    nominal_totals = get_sample_total_entries(config, era, None, exclude_qcd)

    if not nominal_totals:
        print("  ERROR: No nominal entries found!")
        return

    # Get systematic entries
    sys_totals = {}
    for sys in systematics:
        if sys is None:
            continue
        print(f"Loading {sys}...")
        sys_totals[sys] = get_sample_total_entries(config, era, sys, exclude_qcd)

    # Default key processes if not provided
    if key_processes is None:
        key_processes = ['tttt', 'ttbar_0l', 'ttbar_1l', 'ttbar_2l',
                        'TTBB_4f_TTToHadronic', 'TTBB_4f_TTToSemiLeptonic']

    all_samples = sorted(nominal_totals.keys())

    # Print header
    print("\n" + "-" * 100)
    print(f"{'Sample':<35} {'Nominal':>12}", end='')
    for sys in systematics:
        if sys:
            short_name = sys[:10] if len(sys) > 10 else sys
            print(f" {short_name:>10}", end='')
    print()
    print("-" * 100)

    # Track issues
    issues = []

    # Print key processes first
    for sample in key_processes:
        if sample not in nominal_totals:
            continue
        nom = nominal_totals[sample]
        print(f"{sample:<35} {nom:>12,}", end='')

        for sys in systematics:
            if sys is None:
                continue
            sys_entries = sys_totals.get(sys, {}).get(sample, 0)
            if nom > 0:
                ratio = sys_entries / nom
                # Color coding via status
                if sys == 'JESPt22':
                    status = '' if ratio >= 1.0 else '*' if ratio >= 0.98 else '!'
                else:
                    status = '' if ratio >= 0.95 else '*' if ratio >= 0.90 else '!'
                print(f" {sys_entries:>9,}{status}", end='')

                if status == '!':
                    issues.append((sample, sys, nom, sys_entries, ratio))
            else:
                print(f" {sys_entries:>10,}", end='')
        print()

    # Print separator
    if key_processes:
        print("-" * 100)

    # Print remaining samples
    for sample in all_samples:
        if sample in key_processes:
            continue
        nom = nominal_totals[sample]
        if nom == 0:
            continue

        print(f"{sample:<35} {nom:>12,}", end='')

        for sys in systematics:
            if sys is None:
                continue
            sys_entries = sys_totals.get(sys, {}).get(sample, 0)
            if nom > 0:
                ratio = sys_entries / nom
                if sys == 'JESPt22':
                    status = '' if ratio >= 1.0 else '*' if ratio >= 0.98 else '!'
                else:
                    status = '' if ratio >= 0.95 else '*' if ratio >= 0.90 else '!'
                print(f" {sys_entries:>9,}{status}", end='')

                if status == '!':
                    issues.append((sample, sys, nom, sys_entries, ratio))
            else:
                print(f" {sys_entries:>10,}", end='')
        print()

    # Print totals
    print("-" * 100)
    total_nom = sum(nominal_totals.values())
    print(f"{'TOTAL':<35} {total_nom:>12,}", end='')
    for sys in systematics:
        if sys is None:
            continue
        total_sys = sum(sys_totals.get(sys, {}).values())
        ratio = total_sys / total_nom if total_nom > 0 else 0
        print(f" {total_sys:>10,}", end='')
    print()

    # Print ratio row
    print(f"{'RATIO vs Nominal':<35} {'100.0%':>12}", end='')
    for sys in systematics:
        if sys is None:
            continue
        total_sys = sum(sys_totals.get(sys, {}).values())
        ratio = total_sys / total_nom * 100 if total_nom > 0 else 0
        print(f" {ratio:>9.1f}%", end='')
    print()

    # Print legend and issues
    print("\n" + "=" * 100)
    print("Legend: * = 90-95% of nominal (monitor), ! = <90% of nominal (ISSUE)")
    print("        For JES: * = 98-100%, ! = <98% (JES uses lower pt cut, should have MORE entries)")

    if issues:
        print("\n" + "-" * 100)
        print(f"ISSUES FOUND ({len(issues)}):")
        for sample, sys, nom, actual, ratio in sorted(issues, key=lambda x: x[4]):
            print(f"  {sample}/{sys}: {actual:,} vs {nom:,} nominal ({ratio*100:.1f}%)")
    else:
        print("\nAll samples OK - no significant entry deficits detected.")

    print("=" * 100)


def generate_resubmit_script(config: dict, era: str, systematic: str,
                             files: List[Tuple[str, int]], output_path: str) -> str:
    """Generate a job script to rerun specific files."""

    versions = config['versions']
    stage1 = versions['stage1']
    channel = config.get('channel', '1tau0l')
    if1tau2l = 1 if '1tau2l' in channel else 0

    # Determine systematic parameters
    TES, eleScale, JESSys, JERSys, METSys = 0, 0, 0, 0, 0

    if systematic == 'JESPt22':
        JESSys = 1  # Enable JES mode (22 GeV cut)
    elif systematic.startswith('TES'):
        TES_MAP = {
            'TESdm0Up': 3, 'TESdm0Down': 4,
            'TESdm1Up': 5, 'TESdm1Down': 6,
            'TESdm10Up': 7, 'TESdm10Down': 8,
            'TESdm11Up': 9, 'TESdm11Down': 10,
        }
        TES = TES_MAP.get(systematic, 0)
    elif systematic.startswith('JER'):
        JERSys = 1 if 'Up' in systematic else 2
    elif systematic.startswith('MET'):
        METSys = 1 if 'Up' in systematic else 2
    elif systematic.startswith('EleScale'):
        eleScale = 1 if 'Up' in systematic else 2

    # Build paths
    nanoaod_era = ERA_TO_NANOAOD.get(era, era)
    ul_era = ERA_TO_UL.get(era, f'UL{era}')
    input_base = f"/publicfs/cms/data/TopQuark/nanoAOD/{nanoaod_era}/mc"
    output_base = f"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/{ul_era}"
    output_dir = f"{output_base}/{stage1}_{systematic}" if systematic else f"{output_base}/{stage1}"

    sys_name = systematic if systematic else "nominal"
    app_dir = "/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/objectSelectionOptimized"

    script_lines = [
        "#!/bin/bash",
        f"# Resubmit script for {era} {sys_name}",
        f"# Generated for {len(files)} files",
        "",
        f"cd {app_dir}",
        "source /workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/setEnv_centos7.sh",
        "",
    ]

    for filepath, nom_entries in files:
        sample, filename = filepath.split('/', 1)
        input_dir = f"{input_base}/{sample}"
        sample_output = f"{output_dir}/mc/{sample}"

        cmd = (f"./apps/run_objectSelection.out {input_dir} {filename} {sample_output} "
               f"{TES} {eleScale} {JESSys} {JERSys} {METSys} {if1tau2l} 0")

        script_lines.append(f"# {filepath} (nominal: {nom_entries} entries)")
        script_lines.append(f"mkdir -p {sample_output}")
        script_lines.append(cmd)
        script_lines.append("")

    script_content = '\n'.join(script_lines)

    with open(output_path, 'w') as f:
        f.write(script_content)
    os.chmod(output_path, 0o755)

    return output_path


def main():
    parser = argparse.ArgumentParser(description='Check OS outputs against input files')
    parser.add_argument('--config', '-c', required=True, help='Config file path')
    parser.add_argument('--era', '-e', required=True, help='Era (2018, 2017, etc.)')
    parser.add_argument('--systematic', '-s', help='Specific systematic to check')
    parser.add_argument('--nominal-only', action='store_true', help='Check only nominal (no systematics)')
    parser.add_argument('--summary', action='store_true',
                       help='Show summary table: total entries per sample, nominal vs all systematics')
    parser.add_argument('--fix', action='store_true', help='Generate resubmit scripts')
    parser.add_argument('--submit', action='store_true', help='Actually submit jobs (requires --fix)')
    parser.add_argument('--quiet', '-q', action='store_true', help='Less verbose output')
    args = parser.parse_args()

    config = load_config(args.config)

    # Determine which variations to check
    if args.nominal_only:
        systematics = [None]  # None means nominal
    elif args.systematic:
        systematics = [args.systematic]
    else:
        systematics = [None] + ALL_SYSTEMATICS  # Check nominal + all systematics

    # Summary mode - just show total entries comparison
    if args.summary:
        print_summary_report(config, args.era, ALL_SYSTEMATICS)
        return

    print(f"Checking OS outputs for {args.era}")
    print("=" * 70)

    all_issues = {}

    # Build nominal cache once for efficiency
    print("Building nominal entries cache...")
    nominal_cache = get_nominal_entries_cache(config, args.era, verbose=True)
    print(f"  Cached {len(nominal_cache)} nominal files\n")

    for sys in systematics:
        sys_name = sys if sys else "nominal"
        print(f"[{sys_name}]")
        results = check_os_output(config, args.era, sys, verbose=not args.quiet, nominal_cache=nominal_cache)

        n_missing = len(results['missing'])
        n_corrupted = len(results['corrupted'])
        n_truncated = len(results.get('truncated', []))
        n_ok = len(results['ok'])

        if n_missing == 0 and n_corrupted == 0 and n_truncated == 0 and n_ok == 0:
            print("  Directory not found (archived?)")
            continue

        status = "OK" if (n_missing == 0 and n_corrupted == 0 and n_truncated == 0) else "ISSUES"
        print(f"  OK: {n_ok}, Missing: {n_missing}, Corrupted: {n_corrupted}, Truncated: {n_truncated} [{status}]")

        if n_truncated > 0:
            print(f"  TRUNCATED files (incomplete processing):")
            for filepath, nom_n, sys_n, ratio in sorted(results['truncated'], key=lambda x: x[3])[:5]:
                print(f"    {filepath}: {sys_n:,}/{nom_n:,} ({ratio*100:.1f}%)")
            if n_truncated > 5:
                print(f"    ... and {n_truncated - 5} more")

        if n_corrupted > 0:
            print(f"  CORRUPTED files (can't read):")
            for filepath, nom_n, sys_n, ratio in results['corrupted'][:5]:
                print(f"    {filepath}")
            if n_corrupted > 5:
                print(f"    ... and {n_corrupted - 5} more")

        if n_missing > 0:
            print(f"  MISSING files:")
            for filepath, nom_n in results['missing'][:3]:
                print(f"    {filepath}")
            if n_missing > 3:
                print(f"    ... and {n_missing - 3} more")

        if n_missing > 0 or n_corrupted > 0 or n_truncated > 0:
            all_issues[sys_name] = (sys, results)  # Store both name and systematic value

    # Generate fix scripts if requested
    if args.fix and all_issues:
        print("\n" + "=" * 70)
        print("Generating resubmit scripts...")

        scripts_dir = os.path.join(os.path.dirname(__file__), '..', 'objectSelectionOptimized', 'jobs', 'resubmit')
        os.makedirs(scripts_dir, exist_ok=True)

        for sys_name, (sys_value, results) in all_issues.items():
            # Include truncated files in the fix list
            files_to_fix = (
                results['corrupted'] +
                results.get('truncated', []) +
                [(f, n) for f, n in results['missing']]
            )
            if not files_to_fix:
                continue

            # Convert tuples to (filepath, entries) format
            files_list = []
            for item in files_to_fix:
                if len(item) == 4:  # corrupted/truncated: (filepath, expected, actual, ratio)
                    files_list.append((item[0], item[1]))
                else:  # missing: (filepath, input_exists)
                    files_list.append(item)

            script_path = os.path.join(scripts_dir, f"resubmit_{args.era}_{sys_name}.sh")
            generate_resubmit_script(config, args.era, sys_value, files_list, script_path)
            print(f"  Created: {script_path} ({len(files_list)} files)")

            if args.submit:
                print(f"  Submitting {script_path}...")
                # For now, just run directly (for small number of files)
                # For larger jobs, would need to submit to batch system
                if len(files_list) <= 5:
                    subprocess.run(['bash', script_path])
                else:
                    print(f"    Too many files ({len(files_list)}), submit manually or use batch system")

    # Summary
    print("\n" + "=" * 70)
    if all_issues:
        total_corrupted = sum(len(r[1]['corrupted']) for r in all_issues.values())
        total_truncated = sum(len(r[1].get('truncated', [])) for r in all_issues.values())
        total_missing = sum(len(r[1]['missing']) for r in all_issues.values())
        print(f"SUMMARY: {total_corrupted} corrupted, {total_truncated} truncated, {total_missing} missing files")
        print(f"Affected variations: {', '.join(all_issues.keys())}")
        if not args.fix:
            print("\nRun with --fix to generate resubmit scripts")
    else:
        print("All outputs OK!")


if __name__ == '__main__':
    main()
