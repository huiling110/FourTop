import ROOT
import argparse
import os
import shutil
import zipfile
from pathlib import Path
from functools import partial

# Use fourtop package for centralized utilities
from fourtop.workflow import load_config, build_hist_path, build_hist_path_jes, get_channel, get_regions
from fourtop.utils import getEraFromDir
from fourtop.constants.jes import JESVariationList
from fourtop.stage4.systematics import (
    getMCSubPro, addJESToFile, addJERToFile, addTESToFile, addMETToFile, addEESToFile
)

WORKFLOW_UTILS_AVAILABLE = True

# Global config for use in addJESToFile when using workflow_utils
_CONFIG = None
_MODE = 'bdt'  # Global mode for use in find_systematic_directories

# Global quiet flag for controlling verbose output
QUIET = False

#add JES variation templates to WH root files
#add JER variation templetas to WH root files
#add TES variation templates to WH root files

# ============================================================================
# Systematic Directory Cleanup Functions
# ============================================================================

def find_systematic_directories(nominal_dir):
    """
    Find all systematic variation histogram directories by constructing paths exactly as
    addJESToFile(), addJERToFile(), addTESToFile(), addMETToFile(), addEESToFile() do.

    Args:
        nominal_dir: Nominal histogram directory path (e.g., .../mc/variableHists_XXX/)

    Returns:
        list: Paths to systematic variation histogram directories to delete
    """
    # import ttttGlobleQuantity as gq
    # import usefulFunc as uf

    sys_hist_dirs = []

    # Extract era from nominalDir
    era = getEraFromDir(nominal_dir)

    # Get the histogram directory name (e.g., 'variableHists_v8BDT1tau0l_refactorAndBtagNameFix')
    nominalHistDir = nominal_dir.split('mc/', 1)[1]

    # ========================================================================
    # 1. JES Variations (following addJESToFile logic, lines 563-612)
    # ========================================================================
    # Use workflow_utils for path building if config is available (same as addJESToFile)
    if _CONFIG is not None and WORKFLOW_UTILS_AVAILABLE:
        for jes_source in JESVariationList:
            jes_up_dir = build_hist_path_jes(_CONFIG, era, 'up', jes_source, mode=_MODE)
            jes_down_dir = build_hist_path_jes(_CONFIG, era, 'Down', jes_source, mode=_MODE)

            if os.path.exists(jes_up_dir):
                sys_hist_dirs.append(jes_up_dir)
            if os.path.exists(jes_down_dir):
                sys_hist_dirs.append(jes_down_dir)
    else:
        # Legacy path building (backward compatibility)
        # FIX: Extract full stage1 version, not just last component
        Version = nominal_dir.split('/')[-4]
        # Version format: {stage2}_{stage1}_{suffix}
        # e.g., v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest
        version_parts = Version.split('_')
        outVersion = version_parts[0]  # stage2: v1baselineHadro
        # stage1 is everything after stage2, before suffix
        # Join all parts except first and last: v94HadroPreJetVetoHemOnly
        stage1_parts = version_parts[1:-1]
        suffix = version_parts[-1]  # TTBBtest
        inVersion = '_'.join(stage1_parts + [suffix]) + '_JESPt22'  # v94HadroPreJetVetoHemOnly_TTBBtest_JESPt22
        inputDirBase = f'/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/'

        for jes_source in JESVariationList:
            jes_up_dir = f'{inputDirBase}{outVersion}_JESup_{jes_source}_{inVersion}/mc/{nominalHistDir}'
            jes_down_dir = f'{inputDirBase}{outVersion}_JESDown_{jes_source}_{inVersion}/mc/{nominalHistDir}'

            if os.path.exists(jes_up_dir):
                sys_hist_dirs.append(jes_up_dir)
            if os.path.exists(jes_down_dir):
                sys_hist_dirs.append(jes_down_dir)

    # ========================================================================
    # 2. JER Variations (following addJERToFile logic, lines 373-374)
    # ========================================================================
    jer_up_dir = nominal_dir.replace('/mc/', '_JERUp/mc/')
    jer_down_dir = nominal_dir.replace('/mc/', '_JERDown/mc/')

    if os.path.exists(jer_up_dir):
        sys_hist_dirs.append(jer_up_dir)
    if os.path.exists(jer_down_dir):
        sys_hist_dirs.append(jer_down_dir)

    # ========================================================================
    # 3. TES Variations (following addTESToFile logic, lines 360-362)
    # ========================================================================
    for dm in (0, 1, 10, 11):
        tes_up_dir = nominal_dir.replace('/mc/', f'_TESdm{dm}Up/mc/')
        tes_down_dir = nominal_dir.replace('/mc/', f'_TESdm{dm}Down/mc/')

        if os.path.exists(tes_up_dir):
            sys_hist_dirs.append(tes_up_dir)
        if os.path.exists(tes_down_dir):
            sys_hist_dirs.append(tes_down_dir)

    # ========================================================================
    # 4. MET Variations (following addMETToFile logic, lines 384-385)
    # ========================================================================
    met_up_dir = nominal_dir.replace('/mc/', '_METUp/mc/')
    met_down_dir = nominal_dir.replace('/mc/', '_METDown/mc/')

    if os.path.exists(met_up_dir):
        sys_hist_dirs.append(met_up_dir)
    if os.path.exists(met_down_dir):
        sys_hist_dirs.append(met_down_dir)

    # ========================================================================
    # 5. EES Variations (following addEESToFile logic, lines 394-395)
    # ========================================================================
    ees_up_dir = nominal_dir.replace('/mc/', '_EleScaleUp/mc/')
    ees_down_dir = nominal_dir.replace('/mc/', '_EleScaleDown/mc/')

    if os.path.exists(ees_up_dir):
        sys_hist_dirs.append(ees_up_dir)
    if os.path.exists(ees_down_dir):
        sys_hist_dirs.append(ees_down_dir)

    return sorted(sys_hist_dirs)


def zip_directory(dir_path):
    """
    Compress a directory into a zip file and remove the original directory.

    Args:
        dir_path: Path to directory to zip

    Returns:
        tuple: (zip_file_path, success)
    """
    if not os.path.isdir(dir_path):
        return (None, False)

    zip_file_path = f"{dir_path}.zip"

    with zipfile.ZipFile(zip_file_path, 'w', zipfile.ZIP_DEFLATED) as zipf:
        for root, _, files in os.walk(dir_path):
            for file in files:
                file_path = os.path.join(root, file)
                arcname = os.path.relpath(file_path, start=dir_path)
                zipf.write(file_path, arcname)

    # Remove the original directory after successful zip
    shutil.rmtree(dir_path)

    return (zip_file_path, True)


def cleanup_systematic_histogram_directory(sys_hist_dir, dry_run=True, quiet=False):
    """
    Clean up systematic histogram directory:
    1. Delete all ROOT files
    2. Delete jobSH/ directory
    3. Zip log/ directory

    Args:
        sys_hist_dir: Path to systematic histogram directory (e.g., .../JERUp/mc/variableHists_XXX/)
        dry_run: If True, only print what would be done
        quiet: If True, suppress output

    Returns:
        tuple: (num_root_files_deleted, disk_space_freed_MB)
    """
    dir_name = os.path.basename(sys_hist_dir)
    sys_var_name = Path(sys_hist_dir).parent.parent.name

    # Count ROOT files and estimate size
    root_files = list(Path(sys_hist_dir).rglob('*.root'))
    num_root_files = len(root_files)
    root_size_bytes = sum(f.stat().st_size for f in root_files)
    root_size_mb = root_size_bytes / (1024 * 1024)

    # Check for jobSH and log directories
    jobsh_dir = os.path.join(sys_hist_dir, 'jobSH')
    log_dir = os.path.join(sys_hist_dir, 'log')
    has_jobsh = os.path.isdir(jobsh_dir)
    has_log = os.path.isdir(log_dir)

    if dry_run:
        if not quiet:
            print(f"    [DRY-RUN] Would cleanup: {dir_name}")
            print(f"    Full path: {sys_hist_dir}")
            print(f"    Actions:")
            print(f"      - Delete {num_root_files} ROOT files (~{root_size_mb:.1f} MB)")
            if has_jobsh:
                print(f"      - Delete jobSH/ directory")
            if has_log:
                print(f"      - Zip log/ directory")
        return (num_root_files, root_size_mb)
    else:
        # 1. Delete ROOT files
        deleted_count = 0
        for root_file in root_files:
            os.remove(root_file)
            deleted_count += 1

        # 2. Delete jobSH directory
        if has_jobsh:
            shutil.rmtree(jobsh_dir)
            if not quiet:
                print(f"      ✓ Deleted jobSH/")

        # 3. Zip log directory
        if has_log:
            zip_path, success = zip_directory(log_dir)
            if not quiet:
                if success:
                    print(f"      ✓ Zipped log/ → {os.path.basename(zip_path)}")
                else:
                    print(f"      ✗ Failed to zip log/")

        if not quiet:
            print(f"    ✓ Cleaned: {dir_name} ({deleted_count} ROOT files, ~{root_size_mb:.1f} MB freed)")
        return (deleted_count, root_size_mb)


def cleanup_systematic_directories(nominal_dir, dry_run=True, quiet=False):
    """
    Clean up systematic histogram directories after consolidation.
    For each systematic histogram directory:
    - Delete ROOT files (already consolidated into nominal files)
    - Delete jobSH/ directory
    - Zip log/ directory to save space

    Args:
        nominal_dir: Nominal histogram directory path
        dry_run: If True, only print what would be done
        quiet: If True, suppress output
    """
    if not quiet:
        print("="*80)
        print("Systematic Histogram Directory Cleanup")
        print("="*80)
        print(f"Nominal directory: {nominal_dir}")
        print(f"Mode: {'DRY-RUN (safe, no deletions)' if dry_run else 'EXECUTE (will cleanup!)'}")
        print("="*80)

    # Find systematic histogram directories
    sys_hist_dirs = find_systematic_directories(nominal_dir)

    if not sys_hist_dirs:
        if not quiet:
            print("\nNo systematic variation histogram directories found.")
        return

    if not quiet:
        print(f"\nFound {len(sys_hist_dirs)} systematic histogram directories")
        print("\nFirst 5 directories (for verification):")
        for i, d in enumerate(sys_hist_dirs[:5], 1):
            print(f"  {i}. {d}")
        if len(sys_hist_dirs) > 5:
            print(f"  ... and {len(sys_hist_dirs) - 5} more")

        if dry_run:
            print("\n*** DRY-RUN MODE - No files will be deleted ***")
            print("Add --execute flag to actually cleanup\n")

    # Cleanup directories
    total_root_files = 0
    total_size_mb = 0.0

    for i, sys_hist_dir in enumerate(sys_hist_dirs, 1):
        if not quiet:
            print(f"\n[{i}/{len(sys_hist_dirs)}] {os.path.basename(sys_hist_dir)}")
        num_files, size_mb = cleanup_systematic_histogram_directory(sys_hist_dir, dry_run, quiet)
        total_root_files += num_files
        total_size_mb += size_mb

    # Summary
    if not quiet:
        print("\n" + "="*80)
        if dry_run:
            print(f"DRY-RUN Summary:")
            print(f"  Would cleanup: {len(sys_hist_dirs)} histogram directories")
            print(f"  Would delete: {total_root_files} ROOT files")
            print(f"  Would free: ~{total_size_mb:.1f} MB disk space")
            print(f"  Would zip: {len(sys_hist_dirs)} log/ directories")
            print(f"  Would delete: {len(sys_hist_dirs)} jobSH/ directories")
            print(f"\nTo actually cleanup, re-run with: --execute")
        else:
            print(f"✓ Cleanup Complete!")
            print(f"  Cleaned: {len(sys_hist_dirs)} histogram directories")
            print(f"  Deleted: {total_root_files} ROOT files")
            print(f"  Freed: ~{total_size_mb:.1f} MB disk space")
            print(f"  Zipped: log/ directories")
            print(f"  Deleted: jobSH/ directories")
        print("="*80)


# ============================================================================
# Main Function
# ============================================================================

def main():
    global QUIET
    # Parse command-line arguments
    parser = argparse.ArgumentParser(
        description='Add JES/JER/TES/MET/EES systematic variations to nominal histogram files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Basic usage (consolidate + preview cleanup in dry-run mode):
  python3 addJESTemplatesToHistFile.py --config CONFIG.yaml --era 2018

  # Consolidate + actually cleanup systematic directories:
  python3 addJESTemplatesToHistFile.py --config CONFIG.yaml --era 2018 --execute

  # Keep systematic directories (disable cleanup):
  python3 addJESTemplatesToHistFile.py --config CONFIG.yaml --era 2018 --keep-sys-dirs

Cleanup actions (enabled by default, requires --execute to actually delete):
  - Deletes ROOT files from systematic histogram directories (already consolidated)
  - Deletes jobSH/ directories
  - Zips log/ directories to save space
        """
    )
    parser.add_argument('--delete-sys-dirs', action='store_true', default=True,
                        help='Cleanup systematic histogram directories after consolidation (default: enabled)')
    parser.add_argument('--keep-sys-dirs', action='store_true',
                        help='Keep systematic directories (disable cleanup)')
    parser.add_argument('--execute', action='store_true',
                        help='Actually perform cleanup (default: dry-run for safety)')
    parser.add_argument('--config', '-c', type=str, required=True,
                        help='Path to YAML config file (required)')
    parser.add_argument('--era', '-e', type=str, required=True,
                        choices=['2018', '2017', '2016preVFP', '2016postVFP'],
                        help='Era to process (required)')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Suppress non-essential output')
    parser.add_argument('--mode', '-m', type=str, default='bdt',
                        choices=['bdt', 'variables'],
                        help='Mode: bdt (default) or variables (input variable histograms)')
    parser.add_argument('--variables', '-v', type=str, default=None,
                        help='Comma-separated list of variables (default: BDT for bdt mode, all for variables mode)')

    args = parser.parse_args()
    global QUIET
    QUIET = args.quiet

    # Validate workflow_utils is available
    if not WORKFLOW_UTILS_AVAILABLE:
        parser.error("workflow_utils not available. Install pyyaml: pip install pyyaml")

    # Load config and build paths
    global _CONFIG, _MODE
    config = load_config(args.config)
    _CONFIG = config  # Store config globally for use in addJESToFile
    _MODE = args.mode  # Store mode globally for find_systematic_directories
    nominalDir = build_hist_path(config, args.era, mode=args.mode)
    channel = get_channel(config)
    regionList = get_regions(config)

    if not args.quiet:
        print(f"Using config: {args.config}")
        print(f"Era: {args.era}")
        print(f"Channel: {channel}")
        print(f"Regions: {regionList}")
        print(f"Mode: {args.mode}")
        print(f"Nominal dir: {nominalDir}")

    # Set variables based on mode and --variables argument
    if args.variables:
        # User specified variables
        variables = [v.strip() for v in args.variables.split(',')]
    elif args.mode == 'bdt':
        variables = ['BDT']
    else:
        # For variables mode, we need to get variables from the histogram file
        # Default to a common subset for testing
        variables = ['tausT_1pt']  # Default for variables mode if not specified
        if not args.quiet:
            print(f"Variables mode: using default variable {variables}")
            print("Specify --variables to process specific variables")

    # Determine MC fake tau flag based on channel
    ifMCFTau = channel in ['1tau1l', '1tau2l']

    era = getEraFromDir(nominalDir)
    allSubProcesses = getMCSubPro(channel, era, args.quiet)

    # Track consolidation success for each systematic type
    consolidation_success = {
        'JES': False,
        'JER': False,
        'MET': False,
        'EES': False,
        'TES': False
    }
    consolidation_errors = []

    # Create mode-aware build_hist_path_jes wrapper
    build_hist_path_jes_with_mode = partial(build_hist_path_jes, mode=args.mode)

    # Consolidate systematics with error handling
    try:
        addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables,
                     config=config, build_hist_path_jes_func=build_hist_path_jes_with_mode, quiet=args.quiet)
        if ifMCFTau:
            addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables, '_MCFT',
                         config=config, build_hist_path_jes_func=build_hist_path_jes_with_mode, quiet=args.quiet)
            addJESToFile(allSubProcesses, channel, regionList, era, nominalDir, variables, '_NotMCFT',
                         config=config, build_hist_path_jes_func=build_hist_path_jes_with_mode, quiet=args.quiet)
        consolidation_success['JES'] = True
        if not args.quiet:
            print("✓ JES consolidation successful")
    except Exception as e:
        consolidation_errors.append(f"JES: {str(e)}")
        if not args.quiet:
            print(f"✗ JES consolidation failed: {e}")

    try:
        addJERToFile(allSubProcesses, regionList, era, nominalDir, variables, ifMCFTau, quiet=args.quiet)
        consolidation_success['JER'] = True
        if not args.quiet:
            print("✓ JER consolidation successful")
    except Exception as e:
        consolidation_errors.append(f"JER: {str(e)}")
        if not args.quiet:
            print(f"✗ JER consolidation failed: {e}")

    try:
        addMETToFile(allSubProcesses, regionList, era, nominalDir, variables, ifMCFTau, quiet=args.quiet)
        consolidation_success['MET'] = True
        if not args.quiet:
            print("✓ MET consolidation successful")
    except Exception as e:
        consolidation_errors.append(f"MET: {str(e)}")
        if not args.quiet:
            print(f"✗ MET consolidation failed: {e}")

    try:
        addEESToFile(allSubProcesses, regionList, era, nominalDir, variables, ifMCFTau, quiet=args.quiet)
        consolidation_success['EES'] = True
        if not args.quiet:
            print("✓ EES consolidation successful")
    except Exception as e:
        consolidation_errors.append(f"EES: {str(e)}")
        if not args.quiet:
            print(f"✗ EES consolidation failed: {e}")

    try:
        addTESToFile(allSubProcesses, regionList, era, nominalDir, variables, ifMCFTau, quiet=args.quiet)
        consolidation_success['TES'] = True
        if not args.quiet:
            print("✓ TES consolidation successful")
    except Exception as e:
        consolidation_errors.append(f"TES: {str(e)}")
        if not args.quiet:
            print(f"✗ TES consolidation failed: {e}")

    # Only cleanup if ALL consolidations succeeded
    all_succeeded = all(consolidation_success.values())
    cleanup_enabled = args.delete_sys_dirs and not args.keep_sys_dirs

    if consolidation_errors:
        if not args.quiet:
            print("\n" + "="*80)
            print("⚠ WARNING: Some systematic consolidations failed!")
            print("="*80)
            for error in consolidation_errors:
                print(f"  - {error}")
            print("\n✗ Cleanup SKIPPED to preserve systematic files")
            print("="*80)
        # Exit with error to indicate failure
        import sys
        sys.exit(1)

    if cleanup_enabled and all_succeeded:
        if not args.quiet:
            print("\n")
        cleanup_systematic_directories(
            nominal_dir=nominalDir,
            dry_run=not args.execute,
            quiet=args.quiet
        )
    elif not args.quiet:
        print("\n" + "="*80)
        print("✓ Consolidation complete!")
        succeeded_count = sum(consolidation_success.values())
        print(f"  Successfully consolidated: {succeeded_count}/5 systematic types")
        for sys_type, success in consolidation_success.items():
            status = "✓" if success else "✗"
            print(f"    {status} {sys_type}")
        print("\nSystematic histogram directories preserved (--keep-sys-dirs).")
        print("To enable cleanup, remove --keep-sys-dirs flag.")
        print("="*80)


# Note: Consolidation functions (addTESToFile, addJERToFile, addMETToFile, addEESToFile,
# addJESToFile, getMCSubPro, addUpDownToFile, add_histograms_to_rootfile, getJESHistForDir)
# are now imported from fourtop.stage4.systematics


if __name__ == '__main__':
    main()