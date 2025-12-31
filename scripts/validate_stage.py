#!/usr/bin/env python3
"""
Stage Validation - Check prerequisites before running each stage.

Usage:
    python3 scripts/validate_stage.py --stage STAGE --config CONFIG --era ERA

Stages:
    1: Object Selection (OS)
    2: Make Variables (MV)
    2.4: Fake backgrounds
    3: Write Histograms (WH)
    4.1: addJES
    4.2: addTemplate
    4.3: smooth
    4.4: writeDatacard
    4.5: combine fits
    4.7: pl.py plots
"""

import os
import sys
import argparse
import yaml
from pathlib import Path

FOREVA_BASE = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA"
ERAS = ["2018", "2017", "2016preVFP", "2016postVFP"]

def load_config(config_path):
    with open(config_path) as f:
        return yaml.safe_load(f)

def check_stage1(config, era):
    """Check OS prerequisites: NanoAOD input exists."""
    return True, "Stage 1 has no prerequisites"

def check_stage2(config, era):
    """Check MV prerequisites: Stage 1 output exists."""
    versions = config['versions']
    stage1 = versions['stage1']
    stage2 = versions['stage2']

    path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}/mc"
    if not os.path.exists(path):
        return False, f"Stage 1 output missing: {path}"

    # Check for tree files
    tree_files = list(Path(path).glob("*.root"))
    if len(tree_files) < 10:
        return False, f"Stage 1 incomplete: only {len(tree_files)} files in {path}"

    return True, f"Stage 1 complete: {len(tree_files)} files"

def check_stage2_4(config, era):
    """Check fake backgrounds prerequisites: Stage 2 output exists."""
    return check_stage2(config, era)

def check_stage3(config, era):
    """Check WH prerequisites: Stage 2 complete, fake tau if needed."""
    ok, msg = check_stage2(config, era)
    if not ok:
        return ok, msg

    # Check fake tau if enabled
    options = config.get('options', {})
    if options.get('fake_tau', False):
        versions = config['versions']
        stage1 = versions['stage1']
        stage2 = versions['stage2']
        # Fake tau files are in mc/ directory
        mc_path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}/mc"
        fake_tau_file = f"{mc_path}/fakeTau_data_ptMorphed.root"
        if not os.path.exists(fake_tau_file):
            return False, f"Fake tau output missing: {fake_tau_file}"

    return True, "Stage 2 complete, ready for WH"

def check_stage4_1(config, era):
    """Check addJES prerequisites: WH nominal + systematics complete."""
    versions = config['versions']
    stage1 = versions['stage1']
    stage2 = versions['stage2']
    hist = versions['hist']

    nominal_path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}/mc/variableHists_{hist}"
    if not os.path.exists(nominal_path):
        return False, f"WH nominal missing: {nominal_path}"

    root_files = list(Path(nominal_path).glob("*.root"))
    if len(root_files) < 71:
        return False, f"WH nominal incomplete: {len(root_files)}/71 files"

    # Check for systematics (at least TES)
    tes_path = f"{FOREVA_BASE}/{era}/{stage2}_{stage1}_TESdm0Up/mc/variableHists_{hist}"
    if not os.path.exists(tes_path):
        return False, f"WH systematics missing (TES): {tes_path}"

    return True, "WH complete, ready for addJES"

def check_stage4_2(config, era):
    """Check addTemplate prerequisites: addJES complete."""
    # Check template file exists with JES
    versions = config['versions']
    hist = versions['hist']
    template_path = f"plotting/templates_{hist}/template_{era}.root"

    if not os.path.exists(template_path):
        return False, f"Template missing: {template_path}. Run addJES first!"

    return True, "addJES complete, ready for addTemplate"

def check_stage4_3(config, era=None):
    """Check smooth prerequisites: ALL eras have templates."""
    versions = config['versions']
    hist = versions['hist']

    missing = []
    for e in ERAS:
        template_path = f"plotting/templates_{hist}/template_{e}.root"
        if not os.path.exists(template_path):
            missing.append(e)

    if missing:
        return False, f"Templates missing for: {', '.join(missing)}. Complete all eras first!"

    return True, "All era templates ready for smoothing"

def check_stage4_4(config, era):
    """Check writeDatacard prerequisites: smooth complete."""
    options = config.get('options', {})
    if options.get('smoothing', False):
        # Check for smoothed templates
        versions = config['versions']
        hist = versions['hist']
        template_path = f"plotting/templates_{hist}/template_{era}.root"
        # Note: smooth modifies in place, hard to verify completion
        if not os.path.exists(template_path):
            return False, f"Template missing: {template_path}"

    return True, "Ready for writeDatacard"

def check_stage4_5(config, era):
    """Check combine prerequisites: datacards exist."""
    versions = config['versions']
    hist = versions['hist']
    channel = config['channel']
    combination = versions['combination']

    if era == "run2":
        datacard_path = f"hua/combine/{combination}/run2_{channel}_v4/datacard.txt"
    else:
        datacard_path = f"plotting/datacard/{hist}/datacard_{era}.txt"

    if not os.path.exists(datacard_path):
        return False, f"Datacard missing: {datacard_path}"

    return True, "Datacard ready for combine"

def check_stage4_7(config, era):
    """Check pl.py prerequisites: WH complete, addJES if systematics."""
    options = config.get('options', {})

    # First check WH
    ok, msg = check_stage4_1(config, era)
    if not ok:
        return False, f"WH incomplete: {msg}"

    # If systematics enabled, check addJES
    if options.get('systematics', True):
        versions = config['versions']
        hist = versions['hist']
        template_path = f"plotting/templates_{hist}/template_{era}.root"
        if not os.path.exists(template_path):
            return False, f"addJES required for pl.py with systematics! Run Stage 4.1 first."

    return True, "Ready for pl.py"

STAGE_CHECKS = {
    "1": check_stage1,
    "2": check_stage2,
    "2.4": check_stage2_4,
    "3": check_stage3,
    "4.1": check_stage4_1,
    "4.2": check_stage4_2,
    "4.3": check_stage4_3,
    "4.4": check_stage4_4,
    "4.5": check_stage4_5,
    "4.7": check_stage4_7,
}

def main():
    parser = argparse.ArgumentParser(description="Stage prerequisite validation")
    parser.add_argument("--stage", required=True, help="Stage to validate")
    parser.add_argument("--config", required=True, help="Config file")
    parser.add_argument("--era", default="2018", help="Era to check")
    args = parser.parse_args()

    config = load_config(args.config)

    if args.stage not in STAGE_CHECKS:
        print(f"Unknown stage: {args.stage}")
        print(f"Valid stages: {', '.join(STAGE_CHECKS.keys())}")
        sys.exit(1)

    check_fn = STAGE_CHECKS[args.stage]

    # Stage 4.3 doesn't need era (checks all eras)
    if args.stage == "4.3":
        ok, msg = check_fn(config)
    else:
        ok, msg = check_fn(config, args.era)

    if ok:
        print(f"✓ Stage {args.stage} prerequisites OK: {msg}")
        sys.exit(0)
    else:
        print(f"✗ Stage {args.stage} prerequisites FAILED: {msg}")
        sys.exit(1)

if __name__ == "__main__":
    main()
