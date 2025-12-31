#!/usr/bin/env python3
"""
Multi-channel workflow status dashboard.
Shows unified view of all channels/eras progress.

Usage:
    python3 scripts/workflow_status.py [--config CONFIG] [--all]
"""

import os
import sys
import argparse
import yaml
from pathlib import Path
from datetime import datetime

# Base paths
FOREVA_BASE = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
ERAS = ["2018", "2017", "2016preVFP", "2016postVFP"]

def load_config(config_path):
    """Load YAML config file."""
    with open(config_path) as f:
        return yaml.safe_load(f)

def check_wh_status(era, stage1, stage2, hist_version):
    """Check WH output status for an era."""
    # Nominal path
    nominal_path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}/mc/variableHists_{hist_version}"

    if not os.path.exists(nominal_path):
        return "PENDING", 0

    # Count ROOT files
    root_files = list(Path(nominal_path).glob("*.root"))
    count = len(root_files)

    if count == 0:
        return "PENDING", 0
    elif count < 71:
        return f"RUNNING ({count}/71)", count
    else:
        # Check systematics
        sys_count = 0
        for sys_type in ["TESdm0Up", "TESdm0Down", "JERUp", "JERDown"]:
            sys_path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}_{sys_type}/mc/variableHists_{hist_version}"
            if os.path.exists(sys_path):
                sys_count += len(list(Path(sys_path).glob("*.root")))

        if sys_count > 0:
            return f"DONE (nom+sys)", count + sys_count
        else:
            return "DONE (nom)", count

def check_stage4_status(era, stage1, stage2, hist_version):
    """Check Stage 4 substages."""
    hist_path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}/mc/variableHists_{hist_version}"

    # Check addJES (look for JES histograms in nominal file)
    addjes = "?"
    template_path = f"plotting/templates_{hist_version}"
    if os.path.exists(template_path):
        template_files = list(Path(template_path).glob(f"*_{era}.root"))
        addjes = "DONE" if template_files else "PENDING"

    # Check datacard
    datacard_path = f"plotting/datacard/{hist_version}"
    datacard = "DONE" if os.path.exists(f"{datacard_path}/datacard_{era}.txt") else "PENDING"

    return addjes, datacard

def check_combine_status(combination_version, channel):
    """Check combine fit status."""
    combine_path = f"hua/combine/{combination_version}/run2_{channel}_v4"

    if not os.path.exists(combine_path):
        return "PENDING"

    # Check for key files
    if os.path.exists(f"{combine_path}/combineResults/impactResult/impacts.json"):
        return "DONE"
    elif os.path.exists(f"{combine_path}/combineResults"):
        return "RUNNING"
    elif os.path.exists(f"{combine_path}/datacard.txt"):
        return "DATACARD"
    else:
        return "PENDING"

def print_channel_status(config_path):
    """Print status for a single channel config."""
    config = load_config(config_path)

    channel = config.get('channel', 'unknown')
    versions = config.get('versions', {})
    stage1 = versions.get('stage1', '')
    stage2 = versions.get('stage2', 'v1baselineHadro')
    hist = versions.get('hist', '')
    combination = versions.get('combination', '')

    print(f"\n{'='*70}")
    print(f"Channel: {channel} | Config: {os.path.basename(config_path)}")
    print(f"Versions: stage1={stage1}, hist={hist}, combination={combination}")
    print(f"{'='*70}")

    print(f"\n{'Era':<12} | {'S3 WH':<20} | {'S4.1 addJES':<12} | {'S4.4 DC':<10}")
    print(f"{'-'*12}-+-{'-'*20}-+-{'-'*12}-+-{'-'*10}")

    for era in ERAS:
        wh_status, wh_count = check_wh_status(era, stage1, stage2, hist)
        addjes, datacard = check_stage4_status(era, stage1, stage2, hist)
        print(f"{era:<12} | {wh_status:<20} | {addjes:<12} | {datacard:<10}")

    # Run2 combine status
    combine_status = check_combine_status(combination, channel)
    print(f"\n{'Run2 Combine':<12} | {combine_status}")

def find_active_configs():
    """Find all analysis configs in config/ directory."""
    config_dir = Path("config")
    return sorted(config_dir.glob("analysis_config_*.yaml"))

def main():
    parser = argparse.ArgumentParser(description="Workflow status dashboard")
    parser.add_argument("--config", help="Specific config file to check")
    parser.add_argument("--all", action="store_true", help="Show all channels")
    args = parser.parse_args()

    print(f"\n{'#'*70}")
    print(f"# FourTop Workflow Status Dashboard")
    print(f"# Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"{'#'*70}")

    if args.config:
        print_channel_status(args.config)
    elif args.all:
        configs = find_active_configs()
        for config_path in configs:
            print_channel_status(str(config_path))
    else:
        # Default: show XGB080test configs
        for channel in ["1tau1l", "1tau0l"]:
            config_path = f"config/analysis_config_{channel}_XGB080test.yaml"
            if os.path.exists(config_path):
                print_channel_status(config_path)

    print(f"\n{'='*70}")
    print("Legend: PENDING=not started, RUNNING=in progress, DONE=complete")
    print(f"{'='*70}\n")

if __name__ == "__main__":
    main()
