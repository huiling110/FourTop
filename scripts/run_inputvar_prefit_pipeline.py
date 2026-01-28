#!/usr/bin/env python3
"""
Automated pipeline for input variable prefit plots.

Runs Stage 4.1-4.4 for input variables, creates Run2 combination,
runs FitDiagnostics, and generates prefit plots.

Usage:
    python scripts/run_inputvar_prefit_pipeline.py \
        --config config/analysis_config_1tau0l_XGB080test.yaml \
        --variable tausF_1jetPt \
        --regions SR CRMR VR

VERSION: 1.0 (2026-01-25)
"""

import argparse
import os
import sys
import subprocess
import yaml
from pathlib import Path


def run_cmd(cmd, description, dry_run=False, cwd=None):
    """Run a shell command with description."""
    print(f"\n{'='*60}")
    print(f">>> {description}")
    print(f"{'='*60}")
    print(f"CMD: {cmd}")

    if dry_run:
        print("[DRY-RUN] Skipping execution")
        return True

    try:
        result = subprocess.run(
            cmd, shell=True, check=True, cwd=cwd,
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True
        )
        # Print last 30 lines of output
        lines = result.stdout.strip().split('\n')
        if len(lines) > 30:
            print(f"... ({len(lines) - 30} lines omitted)")
        for line in lines[-30:]:
            print(line)
        return True
    except subprocess.CalledProcessError as e:
        print(f"ERROR: Command failed with return code {e.returncode}")
        print(e.output)
        return False


def load_config(config_path):
    """Load and return config dict."""
    with open(config_path) as f:
        return yaml.safe_load(f)


def get_base_path(cfg, era):
    """Get the base path for an era."""
    stage1 = cfg['versions']['stage1']
    stage2 = cfg['versions']['stage2']
    output_base = cfg['paths']['output_base']
    return f"{output_base}/{era}/{stage2}_{stage1}"


def get_inputvar_path(cfg, era):
    """Get the inputVarHists path for an era."""
    base = get_base_path(cfg, era)
    hist_version = cfg['versions']['hist']
    return f"{base}/mc/inputVarHists_{hist_version}"


def run_addjes(config_path, era, variable, base_dir, dry_run=False):
    """Run addJESTemplatesToHistFile.py for a variable."""
    cmd = (
        f"python3 plotting/addJESTemplatesToHistFile.py "
        f"--config {config_path} --era {era} "
        f"--mode variables --variables {variable} "
        f"--execute --quiet --keep-sys-dirs"  # CRITICAL: Keep dirs for other variables!
    )
    return run_cmd(cmd, f"addJES: {era} - {variable}", dry_run, cwd=base_dir)


def run_addtemplate(config_path, era, variable, base_dir, dry_run=False):
    """Run addTemplateNew.py for a variable."""
    cmd = (
        f"python3 plotting/addTemplateNew.py "
        f"--config {config_path} --era {era} "
        f"--mode variables --variables {variable}"
    )
    return run_cmd(cmd, f"addTemplate: {era} - {variable}", dry_run, cwd=base_dir)


def run_datacard(config_path, era, variable, region, base_dir, dry_run=False):
    """Run writeDatacard.py for a variable and region."""
    cmd = (
        f"python3 plotting/writeDatacard.py "
        f"--config {config_path} --era {era} "
        f"--mode variables --variable {variable} "
        f"--region {region} "
        f"--no-smoothed"
    )
    return run_cmd(cmd, f"writeDatacard: {era} - {variable} - {region}", dry_run, cwd=base_dir)


def create_combination(cfg, variable, region, combine_dir, eras, base_dir, dry_run=False):
    """Create Run2 combination datacard using combineCards.py."""
    channel = cfg['channel']
    datacard_version = cfg['versions']['datacard']

    # Build the combineCards command
    # Datacard path: {inputVarHists}/combine/datacardSys_{version}_{variable}[_{region}]/datacard.txt
    # Region suffix only added for non-SR regions
    cards = []
    for era in eras:
        inputvar_path = get_inputvar_path(cfg, era)
        # Datacard version includes variable, and region suffix for non-SR
        version_with_var = f"{datacard_version}_{variable}"
        if region != "SR":
            version_with_var = f"{version_with_var}_{region}"
        datacard_dir = f"{inputvar_path}/combine/datacardSys_{version_with_var}"
        datacard_path = f"{datacard_dir}/datacard.txt"

        # Check if datacard exists
        if not dry_run and not os.path.exists(datacard_path):
            print(f"WARNING: Datacard not found: {datacard_path}")
            continue

        # Channel name in combine: {region}{channel}_{era}
        ch_name = f"{region}{channel}_{era}"
        cards.append(f'{ch_name}="{datacard_path}"')

    if not cards:
        print("ERROR: No datacards found!")
        return False

    # Output directory
    out_dir = os.path.join(combine_dir, f"run2_{channel}_{variable}_{region}")
    os.makedirs(out_dir, exist_ok=True)

    # Create combineCards command
    cards_str = " ".join(cards)
    cmd = f"combineCards.py {cards_str} > {out_dir}/datacard.txt"

    return run_cmd(cmd, f"combineCards: {variable} - {region}", dry_run, cwd=base_dir)


def run_fitdiagnostics(combine_dir, variable, region, channel, base_dir, dry_run=False):
    """Run FitDiagnostics to get prefit shapes."""
    work_dir = os.path.join(combine_dir, f"run2_{channel}_{variable}_{region}")

    # Create workspace
    cmd1 = f"cd {work_dir} && text2workspace.py datacard.txt -o workspace.root 2>&1 | tail -10"
    if not run_cmd(cmd1, f"text2workspace: {variable} - {region}", dry_run, cwd=base_dir):
        return False

    # Run FitDiagnostics
    cmd2 = (
        f"cd {work_dir} && combine -M FitDiagnostics workspace.root "
        f"--saveShapes --saveWithUncertainties --skipBOnlyFit "
        f"-n _run2_{variable}_{region}_prefit -v 1 2>&1 | tail -30"
    )
    return run_cmd(cmd2, f"FitDiagnostics: {variable} - {region}", dry_run, cwd=base_dir)


def run_plotting(fitdiag_dir, variable, region, channel, output_dir, base_dir, dry_run=False):
    """Generate prefit plots."""
    fitdiag_file = os.path.join(
        fitdiag_dir,
        f"fitDiagnostics_run2_{variable}_{region}_prefit.root"
    )

    if not dry_run and not os.path.exists(fitdiag_file):
        print(f"ERROR: FitDiagnostics file not found: {fitdiag_file}")
        return False

    # Map region to channel name for plotting
    channel_name = f"{region}{channel}"

    cmd = (
        f"python3 plotting/plotting_paper/plot_prefit_inputvar.py "
        f"{fitdiag_file} "
        f"--variable {variable} "
        f"--channels {channel_name} "
        f"--output-dir {output_dir}"
    )
    return run_cmd(cmd, f"Plot prefit: {variable} - {region}", dry_run, cwd=base_dir)


def main():
    parser = argparse.ArgumentParser(
        description='Run input variable prefit pipeline',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    # Run full pipeline for tausF_1jetPt
    python scripts/run_inputvar_prefit_pipeline.py \\
        --config config/analysis_config_1tau0l_XGB080test.yaml \\
        --variable tausF_1jetPt \\
        --regions SR CRMR VR

    # Dry-run to see commands
    python scripts/run_inputvar_prefit_pipeline.py \\
        --config config/analysis_config_1tau0l_XGB080test.yaml \\
        --variable tausF_1jetPt --dry-run

    # Skip to combine step (if Stage 4.1-4.4 already done)
    python scripts/run_inputvar_prefit_pipeline.py \\
        --config config/analysis_config_1tau0l_XGB080test.yaml \\
        --variable tausF_1jetPt --start-from combine
        """
    )
    parser.add_argument('--config', required=True, help='Config YAML file')
    parser.add_argument('--variable', required=True, help='Variable name (e.g., tausF_1jetPt)')
    parser.add_argument('--regions', nargs='+', default=['SR', 'CRMR', 'VR'],
                       help='Regions to process (default: SR CRMR VR)')
    parser.add_argument('--eras', nargs='+', default=None,
                       help='Eras to process (default: from config)')
    parser.add_argument('--dry-run', action='store_true', help='Print commands without executing')
    parser.add_argument('--start-from', choices=['addjes', 'template', 'datacard', 'combine', 'fitdiag', 'plot'],
                       default='addjes', help='Start from this stage')
    parser.add_argument('--output-dir', default=None, help='Output directory for plots')
    args = parser.parse_args()

    # Determine base directory
    base_dir = Path(__file__).parent.parent.absolute()
    print(f"Base directory: {base_dir}")

    # Load config
    config_path = os.path.join(base_dir, args.config)
    cfg = load_config(config_path)

    channel = cfg['channel']
    eras = args.eras or cfg.get('eras', ['2018', '2017', '2016preVFP', '2016postVFP'])
    combination_version = cfg['versions']['combination']

    # Combine directory
    combine_dir = os.path.join(base_dir, 'hua', 'combine', combination_version)
    os.makedirs(combine_dir, exist_ok=True)

    # Output directory for plots
    output_dir = args.output_dir or os.path.join(base_dir, 'plotting', 'plotting_paper', 'inputvar_plots')

    print(f"\n{'#'*60}")
    print(f"# Input Variable Prefit Pipeline")
    print(f"# Variable: {args.variable}")
    print(f"# Regions: {args.regions}")
    print(f"# Eras: {eras}")
    print(f"# Start from: {args.start_from}")
    print(f"{'#'*60}")

    stages = ['addjes', 'template', 'datacard', 'combine', 'fitdiag', 'plot']
    start_idx = stages.index(args.start_from)

    success = True

    # Stage 4.1: addJES
    if start_idx <= 0:
        print(f"\n{'='*60}")
        print("STAGE 4.1: addJES")
        print(f"{'='*60}")
        for era in eras:
            if not run_addjes(config_path, era, args.variable, base_dir, args.dry_run):
                success = False
                if not args.dry_run:
                    print(f"ERROR: addJES failed for {era}")

    # Stage 4.2: addTemplate
    if start_idx <= 1:
        print(f"\n{'='*60}")
        print("STAGE 4.2: addTemplate")
        print(f"{'='*60}")
        for era in eras:
            if not run_addtemplate(config_path, era, args.variable, base_dir, args.dry_run):
                success = False
                if not args.dry_run:
                    print(f"ERROR: addTemplate failed for {era}")

    # Stage 4.4: writeDatacard (for each region)
    if start_idx <= 2:
        print(f"\n{'='*60}")
        print("STAGE 4.4: writeDatacard")
        print(f"{'='*60}")
        for era in eras:
            for region in args.regions:
                if not run_datacard(config_path, era, args.variable, region, base_dir, args.dry_run):
                    success = False
                    if not args.dry_run:
                        print(f"ERROR: writeDatacard failed for {era} - {region}")

    # Stage 4.4.1: Create Run2 combination (for each region)
    if start_idx <= 3:
        print(f"\n{'='*60}")
        print("STAGE 4.4.1: Run2 Combination")
        print(f"{'='*60}")
        for region in args.regions:
            if not create_combination(cfg, args.variable, region, combine_dir, eras, base_dir, args.dry_run):
                success = False
                if not args.dry_run:
                    print(f"ERROR: combineCards failed for {region}")

    # Stage 4.5: FitDiagnostics (for each region)
    if start_idx <= 4:
        print(f"\n{'='*60}")
        print("STAGE 4.5: FitDiagnostics")
        print(f"{'='*60}")
        for region in args.regions:
            if not run_fitdiagnostics(combine_dir, args.variable, region, channel, base_dir, args.dry_run):
                success = False
                if not args.dry_run:
                    print(f"ERROR: FitDiagnostics failed for {region}")

    # Stage 5: Plot prefit (for each region)
    if start_idx <= 5:
        print(f"\n{'='*60}")
        print("STAGE 5: Prefit Plots")
        print(f"{'='*60}")
        for region in args.regions:
            fitdiag_dir = os.path.join(combine_dir, f"run2_{channel}_{args.variable}_{region}")
            if not run_plotting(fitdiag_dir, args.variable, region, channel, output_dir, base_dir, args.dry_run):
                success = False
                if not args.dry_run:
                    print(f"ERROR: Plotting failed for {region}")

    # Summary
    print(f"\n{'#'*60}")
    if success:
        print("# Pipeline completed successfully!")
    else:
        print("# Pipeline completed with errors")
    print(f"# Output plots: {output_dir}")
    print(f"{'#'*60}")

    return 0 if success else 1


if __name__ == '__main__':
    sys.exit(main())
