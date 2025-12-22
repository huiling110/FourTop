#!/usr/bin/env python3
"""
Create fake lepton background estimation files.

Standalone usage:
    python3 createFakeLeptonTree.py --config config/analysis_config.yaml --era 2018
    python3 createFakeLeptonTree.py --config config/analysis_config.yaml  # all eras

Via workflow runner:
    python3 run_workflow.py --stage 2.4 --config config/analysis_config.yaml

Note: Only needed for 1tau1l and 1tau2l channels (channels with lepton requirement).
"""
import argparse
import ROOT
import os
import sys

# Add parent directories to path for imports
script_dir = os.path.dirname(os.path.abspath(__file__))
parent_dir = os.path.dirname(script_dir)
plotting_dir = os.path.join(parent_dir, 'plotting')
hua_src_dir = os.path.join(parent_dir, 'hua', 'src_py')

for path in [plotting_dir, hua_src_dir]:
    if path not in sys.path:
        sys.path.insert(0, path)

# Import workflow utilities for config-based path building
try:
    from workflow_utils import load_config, build_stage2_path, get_channel, get_eras
    import usefulFunc as uf
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError as e:
    print(f"Import error: {e}")
    WORKFLOW_UTILS_AVAILABLE = False


def create_parser():
    """Create argument parser."""
    parser = argparse.ArgumentParser(
        description='Create fake lepton background estimation files',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )
    parser.add_argument('--config', '-c', required=True,
                        help='Path to YAML config file (required)')
    parser.add_argument('--era', '-e',
                        help='Era to process (default: all from config)')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Reduce output verbosity')
    parser.add_argument('--is-1tau2l', action='store_true',
                        help='Process for 1tau2l channel (uses leptonSum file)')
    return parser


def create_fake_lepton_tree(inputDir: str, era: str, is1tau2l: bool, quiet: bool = False):
    """
    Create fake lepton tree from anti-isolated region (AR).

    For 1tau1l: reads from jetHT data files
    For 1tau2l: reads from leptonSum_{era}.root

    Output: {baseDir}/mc/fakeLepton.root
    """
    # build_stage2_path returns .../mc/ - get parent directory
    if inputDir.endswith('/mc/') or inputDir.endswith('/mc'):
        baseDir = os.path.dirname(inputDir.rstrip('/'))
    else:
        baseDir = inputDir

    if not quiet:
        print(f"\n{'='*60}")
        print(f"Creating fake lepton tree")
        print(f"Era: {era}")
        print(f"Base dir: {baseDir}")
        print(f"1tau2l mode: {is1tau2l}")
        print(f"{'='*60}")

    # Build input path
    if is1tau2l:
        # For 1tau2l: use leptonSum file
        inputData = os.path.join(baseDir, 'data', f'leptonSum_{era}.root')
    else:
        # For 1tau1l: use data directory with jetHT files
        inputData = os.path.join(baseDir, 'data/')

    outFile = os.path.join(baseDir, 'mc', 'fakeLepton.root')

    if not quiet:
        print(f"Input data: {inputData}")
        print(f"Output file: {outFile}")

    # Create output directory if needed
    os.makedirs(os.path.dirname(outFile), exist_ok=True)

    # Anti-isolated region filter
    AR = 'lepTopMVAF_isAR'

    # Load data
    if is1tau2l:
        if not os.path.exists(inputData):
            print(f"ERROR: Input file not found: {inputData}")
            return False
        df = ROOT.RDataFrame('newtree', inputData)
    else:
        # Get jetHT sub-datasets for this era
        subDataList = uf.getSubProDic(uf.getEraFromDir(inputData), ['jetHT'])
        if not quiet:
            print(f'subDataList: {subDataList}')

        # Build list of input files
        input_files = [inputData + subData + '.root' for subData in subDataList['jetHT']]

        # Check files exist
        missing = [f for f in input_files if not os.path.exists(f)]
        if missing:
            print(f"ERROR: Missing input files: {missing[:3]}...")
            return False

        df = ROOT.RDataFrame('newtree', input_files)

    # Filter to anti-isolated region
    df_AR = df.Filter(AR)
    ar_count = df_AR.Count().GetValue()
    if not quiet:
        print(f'AR entries: {ar_count}')

    if ar_count == 0:
        print("WARNING: No entries in anti-isolated region!")
        return False

    # Get all columns and remove those we'll redefine
    all_columns = df_AR.GetColumnNames()
    columns_to_remove = [
        "lepTopMVAT_1pt", "lepTopMVAT_2pt",
        "elesTopMVAT_1pt", "muonsTopMVAT_1pt",
        "muonsTopMVAT_2pt", "elesTopMVAT_2pt"
    ]
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]

    # Create snapshot with filtered columns
    df_AR.Snapshot('newtree', outFile, columns_to_keep)

    # Reopen and add corrected pt columns
    df_new = ROOT.RDataFrame('newtree', outFile)

    # Replace leptonT pt with lepTopMVAF ptCorrected
    # (the leptonF pt in fake-tau region should be leptonT)
    df_new = df_new.Define("lepTopMVAT_1pt", "lepTopMVAF_1ptCorrected")
    df_new = df_new.Define("lepTopMVAT_2pt", "lepTopMVAF_2ptCorrected")
    df_new = df_new.Define("elesTopMVAT_1pt", "elesTopMVAF_1ptCorrected")
    df_new = df_new.Define("muonsTopMVAT_1pt", "muonsTopMVAF_1ptCorrected")
    df_new = df_new.Define("elesTopMVAT_2pt", "elesTopMVAF_2ptCorrected")
    df_new = df_new.Define("muonsTopMVAT_2pt", "muonsTopMVAF_2ptCorrected")

    if not quiet:
        print(f'New columns defined: {len(df_new.GetColumnNames())}')

    # Overwrite with corrected columns
    df_new.Snapshot('newtree', outFile)

    if not quiet:
        print(f'Output file: {outFile}')
        print(f'Fake lepton tree created successfully!')

    return True


def main():
    parser = create_parser()
    args = parser.parse_args()

    if not WORKFLOW_UTILS_AVAILABLE:
        parser.error("workflow_utils not available. Ensure you're in the correct environment.")

    # Load config
    config = load_config(args.config)

    # Determine eras to process
    eras = [args.era] if args.era else get_eras(config)

    # Determine channel settings
    channel = get_channel(config)
    is1tau2l = args.is_1tau2l or ('1tau2l' in channel)

    # Check if channel needs fake lepton
    if '1tau0l' in channel and not args.is_1tau2l:
        print(f"WARNING: Channel {channel} typically doesn't need fake lepton background.")
        print("Use --is-1tau2l if you want to force 1tau2l mode.")

    if not args.quiet:
        print(f"Config: {args.config}")
        print(f"Channel: {channel}")
        print(f"Eras: {eras}")
        print(f"1tau2l mode: {is1tau2l}")

    # Process each era
    success_count = 0
    for era in eras:
        inputDir = build_stage2_path(config, era)
        if create_fake_lepton_tree(inputDir, era, is1tau2l, args.quiet):
            success_count += 1

    if not args.quiet:
        print(f"\nCompleted: {success_count}/{len(eras)} eras processed successfully")

    return 0 if success_count == len(eras) else 1


if __name__ == '__main__':
    exit(main())
