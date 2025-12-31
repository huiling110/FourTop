#!/usr/bin/env python3
"""
WH Job Completion Monitor.
Checks if WH jobs are complete for a given config/era.

Usage:
    python3 scripts/check_wh_jobs.py --config CONFIG --era ERA [--watch]
    python3 scripts/check_wh_jobs.py --config CONFIG --all [--watch]
"""

import os
import sys
import argparse
import subprocess
import yaml
import time
from pathlib import Path
from datetime import datetime

FOREVA_BASE = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
ERAS = ["2018", "2017", "2016preVFP", "2016postVFP"]

# Expected file counts
EXPECTED = {
    "nominal": 71,
    "TES": 472,      # 8 variations * 59 files
    "JER": 118,      # 2 variations * 59 files
    "MET": 118,      # 2 variations * 59 files
    "EleScale": 118, # 2 variations * 59 files
    "JES": 3540,     # 60 variations * 59 files
    "total_sys": 4366,  # All systematics
    "total": 4437,   # Nominal + all sys
}

def load_config(config_path):
    """Load YAML config."""
    with open(config_path) as f:
        return yaml.safe_load(f)

def count_files(path_pattern):
    """Count ROOT files matching pattern."""
    if not os.path.exists(path_pattern.split('*')[0].rsplit('/', 1)[0]):
        return 0
    return len(list(Path(path_pattern.rsplit('/', 1)[0]).glob("*.root")))

def get_running_jobs():
    """Get count of running WH jobs."""
    try:
        result = subprocess.run(
            ["hep_q", "-u", os.environ.get("USER", "huahuil")],
            capture_output=True, text=True, timeout=30
        )
        return result.stdout.count("WH_")
    except:
        return -1

def check_era_status(era, stage1, stage2, hist_version, verbose=True):
    """Check WH completion status for an era."""
    base = f"{FOREVA_BASE}/{era}"
    nominal_path = f"{base}/{stage2}_{stage1}/mc/variableHists_{hist_version}"

    results = {"era": era, "complete": False, "counts": {}}

    # Count nominal
    nominal_count = count_files(f"{nominal_path}/*.root")
    results["counts"]["nominal"] = nominal_count

    # Count systematics
    sys_paths = {
        "TES": [f"{base}/{stage2}_{stage1}_TES{dm}{ud}/mc/variableHists_{hist_version}"
                for dm in ["dm0", "dm1", "dm10", "dm11"] for ud in ["Up", "Down"]],
        "JER": [f"{base}/{stage2}_{stage1}_JER{ud}/mc/variableHists_{hist_version}"
                for ud in ["Up", "Down"]],
        "MET": [f"{base}/{stage2}_{stage1}_MET{ud}/mc/variableHists_{hist_version}"
                for ud in ["Up", "Down"]],
        "EleScale": [f"{base}/{stage2}_{stage1}_EleScale{ud}/mc/variableHists_{hist_version}"
                     for ud in ["Up", "Down"]],
    }

    for sys_type, paths in sys_paths.items():
        count = sum(count_files(f"{p}/*.root") for p in paths)
        results["counts"][sys_type] = count

    # JES is more complex - count directories
    jes_count = 0
    jes_pattern = f"{base}/{stage2}_JES*_{stage1}_*/mc/variableHists_{hist_version}"
    jes_dirs = list(Path(base).glob(f"{stage2}_JES*_{stage1}_*/mc/variableHists_{hist_version}"))
    for jes_dir in jes_dirs:
        jes_count += len(list(jes_dir.glob("*.root")))
    results["counts"]["JES"] = jes_count

    # Calculate total
    total = sum(results["counts"].values())
    results["counts"]["total"] = total
    results["complete"] = (total >= EXPECTED["total"] * 0.95)  # 95% threshold

    if verbose:
        print(f"\n{era}:")
        print(f"  Nominal: {nominal_count}/{EXPECTED['nominal']}")
        print(f"  TES:     {results['counts']['TES']}/{EXPECTED['TES']}")
        print(f"  JER:     {results['counts']['JER']}/{EXPECTED['JER']}")
        print(f"  MET:     {results['counts']['MET']}/{EXPECTED['MET']}")
        print(f"  EleScale:{results['counts']['EleScale']}/{EXPECTED['EleScale']}")
        print(f"  JES:     {results['counts']['JES']}/{EXPECTED['JES']}")
        print(f"  TOTAL:   {total}/{EXPECTED['total']} {'✓ COMPLETE' if results['complete'] else '...'}")

    return results

def main():
    parser = argparse.ArgumentParser(description="WH Job Completion Monitor")
    parser.add_argument("--config", required=True, help="Config file path")
    parser.add_argument("--era", help="Specific era to check")
    parser.add_argument("--all", action="store_true", help="Check all eras")
    parser.add_argument("--watch", action="store_true", help="Watch mode (refresh every 60s)")
    parser.add_argument("--quiet", action="store_true", help="Only show summary")
    args = parser.parse_args()

    config = load_config(args.config)
    versions = config.get('versions', {})
    stage1 = versions.get('stage1', '')
    stage2 = versions.get('stage2', 'v1baselineHadro')
    hist = versions.get('hist', '')
    channel = config.get('channel', 'unknown')

    eras_to_check = ERAS if args.all else ([args.era] if args.era else ERAS)

    while True:
        os.system('clear' if not args.quiet else ':')

        print(f"\n{'='*60}")
        print(f"WH Job Monitor: {channel}")
        print(f"Config: {args.config}")
        print(f"Time: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
        print(f"{'='*60}")

        running_jobs = get_running_jobs()
        print(f"\nRunning WH jobs in queue: {running_jobs}")

        all_complete = True
        for era in eras_to_check:
            result = check_era_status(era, stage1, stage2, hist, verbose=not args.quiet)
            if not result["complete"]:
                all_complete = False

        if all_complete:
            print(f"\n{'='*60}")
            print("✓ ALL ERAS COMPLETE! Ready for Stage 4.")
            print(f"{'='*60}\n")
            if args.watch:
                break

        if not args.watch:
            break

        print(f"\nRefreshing in 60 seconds... (Ctrl+C to exit)")
        try:
            time.sleep(60)
        except KeyboardInterrupt:
            print("\nExiting...")
            break

if __name__ == "__main__":
    main()
