#!/usr/bin/env python3
"""
create_combined_histfile.py - Create combined histogram ROOT file from WH output

Creates a ROOT file similar to fitDiagnosticsTest.root structure with all processes
and their systematics combined into single uncertainty bands per histogram.

Usage:
    python3 plotting/create_combined_histfile.py \
        --input-dir /path/to/variableHists_.../ \
        --era 2018 \
        --channels 1tau0l 1tau1l \
        --variables-1tau0l tausT_1pt tausT_1eta tausT_1decayMode \
        --regions-1tau0l 1tau0lSR 1tau0lMR 1tau0lVR \
        --regions-1tau1l 1tau1lSR 1tau1lCR1 \
        --output combined_2018.root
"""

import argparse
import math
import os
import ROOT

from fourtop.utils import getInputDicNew, getEraFromDir
from fourtop.utils.process import getSumListFull, isData, checkIfOtherYear
from fourtop.constants.samples import histoGramPerSample, ttX_newMap
from fourtop.constants.jes import SKIP_SUBPROCESSES
from fourtop.stage4.datacards import getProSysDicForPlotting


def parse_args():
    """Parse command line arguments."""
    parser = argparse.ArgumentParser(
        description='Create combined histogram ROOT file from WH output',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__
    )

    parser.add_argument('--input-dir', '-i', type=str, required=True,
                        help='Path to WH output directory (variableHists_...) for single era, or base path with {era} placeholder')
    parser.add_argument('--era', '-e', type=str, nargs='+', default=['2018'],
                        help='Era(s) to process (default: 2018). Use "run2" for all Run2 eras.')
    parser.add_argument('--channels', nargs='+', default=['1tau0l', '1tau1l'],
                        help='Channels to process (default: 1tau0l 1tau1l)')
    parser.add_argument('--output', '-o', type=str, default='combined_histograms.root',
                        help='Output ROOT file path (default: combined_histograms.root)')
    parser.add_argument('--quiet', '-q', action='store_true',
                        help='Suppress verbose output')

    # Per-channel input directories (optional, overrides --input-dir)
    parser.add_argument('--input-dir-1tau2l', type=str, default=None,
                        help='Separate input directory for 1tau2l channel')

    # Per-channel variables
    parser.add_argument('--variables-1tau0l', nargs='+',
                        default=['tausF_1jetPt', 'tausT_1pt', 'tausT_1eta', 'tausT_1decayMode',
                                 'tausT_1jetEtaAbs', 'tausT_prongNum', 'jets_HT'],
                        help='Variables for 1tau0l channel')
    parser.add_argument('--variables-1tau1l', nargs='+',
                        default=['BDT'],
                        help='Variables for 1tau1l channel')
    parser.add_argument('--variables-1tau2l', nargs='+',
                        default=['tausF_1jetPt', 'tausT_1pt', 'tausT_1eta', 'tausT_1decayMode',
                                 'tausT_1jetEtaAbs', 'tausT_prongNum', 'jets_HT'],
                        help='Variables for 1tau2l channel')

    # Per-channel regions
    parser.add_argument('--regions-1tau0l', nargs='+',
                        default=['1tau0lSR', '1tau0lMR', '1tau0lVR'],
                        help='Regions for 1tau0l channel')
    parser.add_argument('--regions-1tau1l', nargs='+',
                        default=['1tau1lSR', '1tau1lCR1'],
                        help='Regions for 1tau1l channel')
    parser.add_argument('--regions-1tau2l', nargs='+',
                        default=['1tau2lCR3', '1tau2lCR4'],
                        help='Regions for 1tau2l channel (control regions only)')

    # Options
    parser.add_argument('--no-systematics', action='store_true',
                        help='Skip systematics (only nominal histograms)')
    parser.add_argument('--fake-tau', action='store_true', default=True,
                        help='Include fake tau background (default: True)')
    parser.add_argument('--mc-fake-tau', action='store_true', default=False,
                        help='Use MC fake tau instead of data-driven')

    return parser.parse_args()


def get_histograms_fast(rootFile, subPro, regions, variables, systematics, quiet=False):
    """
    Get all histograms from a ROOT file in a single pass (FAST).

    Opens file once, reads all needed histograms, closes file.

    Args:
        rootFile: Path to ROOT file
        subPro: Subprocess name (for histogram naming)
        regions: List of region names
        variables: List of variable names
        systematics: List of systematic names (without Up/Down suffix)
        quiet: Suppress output

    Returns:
        Tuple of (nominal_dict, sys_dict)
        - nominal_dict[var][region] = histogram
        - sys_dict[var][region][sys_name] = histogram
    """
    if not os.path.exists(rootFile):
        if not quiet:
            print(f"  File not found: {rootFile}")
        return {}, {}

    f = ROOT.TFile.Open(rootFile)
    if not f or f.IsZombie():
        if not quiet:
            print(f"  Cannot open: {rootFile}")
        return {}, {}

    nominal_dict = {}
    sys_dict = {}

    for var in variables:
        nominal_dict[var] = {}
        sys_dict[var] = {}

        for region in regions:
            sys_dict[var][region] = {}

            # Get nominal histogram
            hist_name = f'{subPro}_{region}_{var}'
            hist = f.Get(hist_name)
            if hist:
                clone = hist.Clone()
                clone.SetDirectory(0)
                nominal_dict[var][region] = clone

                # Get systematic histograms (all in one pass)
                for sys_name in systematics:
                    for direction in ['Up', 'Down']:
                        sys_hist_name = f'{subPro}_{region}_{sys_name}{direction}_{var}'
                        sys_hist = f.Get(sys_hist_name)
                        if sys_hist:
                            sys_clone = sys_hist.Clone()
                            sys_clone.SetDirectory(0)
                            sys_key = f'{sys_name}_{direction.lower()}'
                            sys_dict[var][region][sys_key] = sys_clone

    f.Close()
    return nominal_dict, sys_dict


def get_summed_histograms_fast(inputDirDic, regions, sumProList, sumProSys, variables,
                                era, skip_subprocesses=None, quiet=False):
    """
    Fast version of getSumHist - opens each file only once.

    Args:
        inputDirDic: Dict with 'mc' and 'data' directories
        regions: List of regions
        sumProList: List of summed process names
        sumProSys: Dict of systematics per summed process
        variables: List of variables
        era: Era string
        skip_subprocesses: List of subprocesses to skip
        quiet: Suppress output

    Returns:
        Tuple of (sumProHists, sumProHistsSys)
    """
    # Get sample-to-process mapping
    allDic = histoGramPerSample.copy()
    if 'ttX' not in sumProList:
        allDic.update(ttX_newMap)

    # Filter out skipped subprocesses
    if skip_subprocesses:
        for skip_sub in skip_subprocesses:
            if skip_sub in allDic:
                del allDic[skip_sub]

    # Initialize output dictionaries
    sumProHists = {var: {region: {} for region in regions} for var in variables}
    sumProHistsSys = {var: {region: {} for region in regions} for var in variables}

    # Process each subprocess
    for subPro, sumPro in allDic.items():
        if sumPro not in sumProList:
            continue

        is_data_sample = isData(subPro)
        if checkIfOtherYear(subPro, era, is_data_sample):
            continue

        # Get input directory and file
        inputDir = inputDirDic['data'] if is_data_sample else inputDirDic['mc']
        rootFile = os.path.join(inputDir, f'{subPro}.root')

        if not quiet:
            print(f"  Loading: {subPro} -> {sumPro}")

        # Get systematics for this summed process
        systematics = sumProSys.get(sumPro, [])

        # Load all histograms in one pass
        nominal, sys_hists = get_histograms_fast(
            rootFile, subPro, regions, variables, systematics, quiet
        )

        # Aggregate into summed process
        for var in variables:
            for region in regions:
                if region not in nominal.get(var, {}):
                    continue

                hist = nominal[var][region]

                # Add to summed process histogram
                if sumPro not in sumProHists[var][region]:
                    sumProHists[var][region][sumPro] = hist.Clone()
                    sumProHists[var][region][sumPro].SetName(
                        hist.GetName().replace(subPro, sumPro)
                    )
                else:
                    sumProHists[var][region][sumPro].Add(hist)

                # Add systematics
                if region in sys_hists.get(var, {}):
                    if sumPro not in sumProHistsSys[var][region]:
                        sumProHistsSys[var][region][sumPro] = {}

                    for sys_name, sys_hist in sys_hists[var][region].items():
                        if sys_name not in sumProHistsSys[var][region][sumPro]:
                            sumProHistsSys[var][region][sumPro][sys_name] = sys_hist.Clone()
                        else:
                            sumProHistsSys[var][region][sumPro][sys_name].Add(sys_hist)

    return sumProHists, sumProHistsSys


def combine_systematic_errors(nominal_hist, sys_hists, quiet=False):
    """
    Combine systematic variations into total uncertainty using error propagation.
    """
    result = nominal_hist.Clone(nominal_hist.GetName() + "_combined")
    nbins = nominal_hist.GetNbinsX()

    # Group up/down variations
    sys_pairs = {}

    for sys_name, hist in sys_hists.items():
        if sys_name.endswith('_up') or sys_name.endswith('Up'):
            base = sys_name.replace('_up', '').replace('Up', '')
            direction = 'up'
        elif sys_name.endswith('_down') or sys_name.endswith('Down'):
            base = sys_name.replace('_down', '').replace('Down', '')
            direction = 'down'
        else:
            base = sys_name
            direction = 'up'

        if base not in sys_pairs:
            sys_pairs[base] = {}
        sys_pairs[base][direction] = hist

    # Compute combined uncertainty per bin
    for ibin in range(1, nbins + 1):
        nom_val = nominal_hist.GetBinContent(ibin)
        stat_err = nominal_hist.GetBinError(ibin)
        sys_err_sq = 0.0

        for base_name, variations in sys_pairs.items():
            up_diff = 0.0
            down_diff = 0.0

            if 'up' in variations:
                up_diff = variations['up'].GetBinContent(ibin) - nom_val
            if 'down' in variations:
                down_diff = variations['down'].GetBinContent(ibin) - nom_val

            max_diff = max(abs(up_diff), abs(down_diff))
            sys_err_sq += max_diff ** 2

        total_err = math.sqrt(stat_err ** 2 + sys_err_sq)
        result.SetBinError(ibin, total_err)

    return result


def get_channel_config(channel, args):
    """Get variables and regions for a channel from args."""
    if channel == '1tau0l':
        return args.variables_1tau0l, args.regions_1tau0l
    elif channel == '1tau1l':
        return args.variables_1tau1l, args.regions_1tau1l
    elif channel == '1tau2l':
        return args.variables_1tau2l, args.regions_1tau2l
    else:
        raise ValueError(f"Unknown channel: {channel}")


def get_channel_input_dir(channel, base_input_dir, args):
    """Get input directory for a channel, using per-channel override if specified."""
    if channel == '1tau2l' and args.input_dir_1tau2l:
        return args.input_dir_1tau2l
    return base_input_dir


def group_ttX(sumProcessPerVar, sumProcessPerVarSys, variables, regions):
    """Group ttZ, ttW, ttH into ttX for output."""
    ttX_components = ['ttZ', 'ttW', 'ttH']

    for var in variables:
        for region in regions:
            if region not in sumProcessPerVar.get(var, {}):
                continue

            has_ttX_component = any(
                proc in sumProcessPerVar[var][region]
                for proc in ttX_components
            )

            if not has_ttX_component:
                continue

            # Create ttX by summing components (nominal)
            ttX_hist = None
            for proc in ttX_components:
                if proc in sumProcessPerVar[var][region]:
                    hist = sumProcessPerVar[var][region][proc]
                    if ttX_hist is None:
                        ttX_hist = hist.Clone()
                        ttX_hist.SetName(hist.GetName().replace(proc, 'ttX'))
                    else:
                        ttX_hist.Add(hist)
                    del sumProcessPerVar[var][region][proc]

            if ttX_hist:
                sumProcessPerVar[var][region]['ttX'] = ttX_hist

            # Do the same for systematics
            if region not in sumProcessPerVarSys.get(var, {}):
                continue

            all_sys_names = set()
            for proc in ttX_components:
                if proc in sumProcessPerVarSys[var][region]:
                    all_sys_names.update(sumProcessPerVarSys[var][region][proc].keys())

            ttX_sys = {}
            for sys_name in all_sys_names:
                sys_hist = None
                for proc in ttX_components:
                    if proc in sumProcessPerVarSys[var][region]:
                        if sys_name in sumProcessPerVarSys[var][region][proc]:
                            hist = sumProcessPerVarSys[var][region][proc][sys_name]
                            if sys_hist is None:
                                sys_hist = hist.Clone()
                                sys_hist.SetName(hist.GetName().replace(proc, 'ttX'))
                            else:
                                sys_hist.Add(hist)
                if sys_hist:
                    ttX_sys[sys_name] = sys_hist

            for proc in ttX_components:
                if proc in sumProcessPerVarSys[var][region]:
                    del sumProcessPerVarSys[var][region][proc]

            if ttX_sys:
                sumProcessPerVarSys[var][region]['ttX'] = ttX_sys


def get_input_dir_for_era(base_input_dir, era):
    """
    Derive input directory for a specific era from base path.

    If base path contains an era string, replace it with the target era.
    Otherwise, assume base path has {era} placeholder or is era-specific.
    """
    # Check if path contains a known era that can be replaced
    known_eras = ['2018', '2017', '2016preVFP', '2016postVFP']
    for known_era in known_eras:
        if f'/{known_era}/' in base_input_dir:
            return base_input_dir.replace(f'/{known_era}/', f'/{era}/')

    # Check for {era} placeholder
    if '{era}' in base_input_dir:
        return base_input_dir.format(era=era)

    # Return as-is (assume it's already era-specific)
    return base_input_dir


def main():
    args = parse_args()

    base_input_dir = args.input_dir

    # Expand "run2" to all Run2 eras
    eras = args.era
    if eras == ['run2'] or eras == ['Run2']:
        eras = ['2016preVFP', '2016postVFP', '2017', '2018']

    if not args.quiet:
        print(f"Base input directory: {base_input_dir}")
        print(f"Eras: {eras}")
        print(f"Channels: {args.channels}")
        print(f"Output: {args.output}")

    # Create output file (single file for all eras)
    outFile = ROOT.TFile(args.output, 'RECREATE')
    shapes_prefit = outFile.mkdir('shapes_prefit')

    # Process each era
    for era in eras:
        if not args.quiet:
            print(f"\n{'='*60}")
            print(f"Processing era: {era}")
            print(f"{'='*60}")

        # Process each channel
        for channel in args.channels:
            # Get channel-specific input directory
            channel_base_dir = get_channel_input_dir(channel, base_input_dir, args)
            inputDir = get_input_dir_for_era(channel_base_dir, era)

            if not args.quiet:
                print(f"\n  Channel: {channel}")
                print(f"  Input: {inputDir}")

            if not os.path.exists(inputDir):
                print(f"Warning: Input directory not found for {channel} {era}: {inputDir}")
                continue

            inputDirDic = getInputDicNew(inputDir)

            variables, regions = get_channel_config(channel, args)

            if not args.quiet:
                print(f"  Variables: {variables}")
                print(f"  Regions: {regions}")

            sumProList = getSumListFull(channel, args.fake_tau, '', args.mc_fake_tau, True)

            if args.no_systematics:
                sumProSys = {proc: [] for proc in sumProList}
            else:
                sumProSys = getProSysDicForPlotting(sumProList, True, channel, era, True)

            skip_subprocesses = SKIP_SUBPROCESSES.get(channel, [])

            # Use FAST histogram loading
            try:
                sumProcessPerVar, sumProcessPerVarSys = get_summed_histograms_fast(
                    inputDirDic, regions, sumProList, sumProSys, variables,
                    era, skip_subprocesses=skip_subprocesses, quiet=args.quiet
                )
            except Exception as e:
                print(f"Error loading histograms for {channel} {era}: {e}")
                import traceback
                traceback.print_exc()
                continue

            group_ttX(sumProcessPerVar, sumProcessPerVarSys, variables, regions)

            # Write histograms to output file
            for region in regions:
                region_dir_name = f"{region}_{era}"

                for var in variables:
                    if var not in sumProcessPerVar:
                        continue
                    if region not in sumProcessPerVar[var]:
                        continue

                    shapes_prefit.cd()

                    if not shapes_prefit.GetDirectory(region_dir_name):
                        shapes_prefit.mkdir(region_dir_name)
                    region_dir = shapes_prefit.GetDirectory(region_dir_name)

                    if not region_dir.GetDirectory(var):
                        region_dir.mkdir(var)
                    var_dir = region_dir.GetDirectory(var)
                    var_dir.cd()

                    total_hist = None
                    data_hist = None

                    for proc, hist in sumProcessPerVar[var][region].items():
                        sys_hists = {}
                        if proc in sumProcessPerVarSys.get(var, {}).get(region, {}):
                            sys_hists = sumProcessPerVarSys[var][region][proc]

                        if sys_hists:
                            combined_hist = combine_systematic_errors(hist, sys_hists, args.quiet)
                        else:
                            combined_hist = hist.Clone()

                        combined_hist.SetName(proc)
                        combined_hist.Write()

                        if proc in ['jetHT', 'leptonSum']:
                            data_hist = combined_hist.Clone('data')
                        elif proc != 'tttt':
                            if total_hist is None:
                                total_hist = combined_hist.Clone('total')
                            else:
                                total_hist.Add(combined_hist)

                    if total_hist:
                        total_hist.SetName('total')
                        total_hist.Write()

                    if data_hist:
                        data_hist.SetName('data')
                        data_hist.Write()
                    elif total_hist:
                        fake_data = total_hist.Clone('data')
                        fake_data.Write()

                    if not args.quiet:
                        integral = total_hist.Integral() if total_hist else 0
                        print(f"    {region_dir_name}/{var}: total = {integral:.1f}")

    outFile.Write()
    outFile.Close()
    print(f"\nOutput file created: {args.output}")


if __name__ == "__main__":
    main()
