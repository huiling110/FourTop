#!/usr/bin/env python3
"""
extract_limits.py - Extract VLL limits from combine output and save to JSON

Usage:
    python3 plotting/extract_limits.py --output limits_VLL.json
"""

import argparse
import json
import ROOT

# Import cross section data
import sys
sys.path.append('/workfs2/cms/huahuil/CMSSW_14_1_0_pre4/src/FourTop/hua/src_py')
from ttttGlobleQuantity import crossSectionMap, histoGramPerSample


def read_limits_from_file(filename):
    """Read limits from a combine AsymptoticLimits ROOT file."""
    file = ROOT.TFile(filename, "READ")
    tree = file.Get("limit")
    if not tree:
        raise ValueError(f"TTree 'limit' not found in file {filename}")

    limits = {
        'observed': None,
        'expected': None,
        'expected_1sigma_up': None,
        'expected_1sigma_down': None,
        'expected_2sigma_up': None,
        'expected_2sigma_down': None,
    }

    for entry in tree:
        if entry.quantileExpected == -1:
            limits['observed'] = entry.limit
        elif abs(entry.quantileExpected - 0.5) < 1e-5:
            limits['expected'] = entry.limit
        elif abs(entry.quantileExpected - 0.84) < 1e-5:
            limits['expected_1sigma_up'] = entry.limit
        elif abs(entry.quantileExpected - 0.16) < 1e-5:
            limits['expected_1sigma_down'] = entry.limit
        elif abs(entry.quantileExpected - 0.975) < 1e-5:
            limits['expected_2sigma_up'] = entry.limit
        elif abs(entry.quantileExpected - 0.025) < 1e-5:
            limits['expected_2sigma_down'] = entry.limit

    file.Close()
    return limits


def get_theory_cross_section(mass):
    """Get theoretical cross section for VLL at given mass."""
    sum_pro = f'VLLm{mass}'
    sub_pros = [key for key, val in histoGramPerSample.items() if val == sum_pro]

    total_xs = 0
    for sub in sub_pros:
        if sub in crossSectionMap:
            total_xs += crossSectionMap[sub]

    return total_xs


def main():
    parser = argparse.ArgumentParser(description='Extract VLL limits to JSON')
    parser.add_argument('--output', '-o', type=str, default='limits_VLL.json',
                        help='Output JSON file')
    args = parser.parse_args()

    # Input files
    inputFile = {
        500: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm500/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        550: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm550/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        600: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm600/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        650: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm650/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        700: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm700/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        750: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm750/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        800: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm800/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        850: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm850/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        900: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm900/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        950: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm950/higgsCombine_datacard.AsymptoticLimits.mH120.root',
        1000: '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_14_1_0_pre4/src/FourTop/hua/combine/combinationV21/run2_total_v4_unblind_VLLm1000/higgsCombine_datacard.AsymptoticLimits.mH120.root',
    }

    # Extract data
    data = {
        'mass_points': [],
        'theory_xs': [],
        'observed_limit': [],      # mu values (signal strength)
        'expected_limit': [],
        'expected_1sigma_up': [],
        'expected_1sigma_down': [],
        'expected_2sigma_up': [],
        'expected_2sigma_down': [],
        'observed_xs': [],         # Cross section = mu * theory_xs
        'expected_xs': [],
        'expected_xs_1sigma_up': [],
        'expected_xs_1sigma_down': [],
        'expected_xs_2sigma_up': [],
        'expected_xs_2sigma_down': [],
    }

    print("Extracting limits...")
    for mass, filepath in sorted(inputFile.items()):
        print(f"  Mass {mass} GeV: {filepath}")

        try:
            limits = read_limits_from_file(filepath)
            theory_xs = get_theory_cross_section(mass)

            data['mass_points'].append(mass)
            data['theory_xs'].append(theory_xs)

            # Store mu values
            data['observed_limit'].append(limits['observed'])
            data['expected_limit'].append(limits['expected'])
            data['expected_1sigma_up'].append(limits['expected_1sigma_up'])
            data['expected_1sigma_down'].append(limits['expected_1sigma_down'])
            data['expected_2sigma_up'].append(limits['expected_2sigma_up'])
            data['expected_2sigma_down'].append(limits['expected_2sigma_down'])

            # Store cross sections (mu * theory_xs)
            data['observed_xs'].append(limits['observed'] * theory_xs if limits['observed'] else None)
            data['expected_xs'].append(limits['expected'] * theory_xs if limits['expected'] else None)
            data['expected_xs_1sigma_up'].append(limits['expected_1sigma_up'] * theory_xs if limits['expected_1sigma_up'] else None)
            data['expected_xs_1sigma_down'].append(limits['expected_1sigma_down'] * theory_xs if limits['expected_1sigma_down'] else None)
            data['expected_xs_2sigma_up'].append(limits['expected_2sigma_up'] * theory_xs if limits['expected_2sigma_up'] else None)
            data['expected_xs_2sigma_down'].append(limits['expected_2sigma_down'] * theory_xs if limits['expected_2sigma_down'] else None)

            print(f"    Theory XS: {theory_xs:.4f} pb")
            print(f"    Observed: {limits['observed']:.2f}, Expected: {limits['expected']:.2f}")

        except Exception as e:
            print(f"    Error: {e}")
            continue

    # Save to JSON
    with open(args.output, 'w') as f:
        json.dump(data, f, indent=2)

    print(f"\nSaved to {args.output}")
    print(f"Mass points: {data['mass_points']}")


if __name__ == "__main__":
    main()
