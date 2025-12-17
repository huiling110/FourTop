#!/usr/bin/env python3
"""
Binning optimization using TMVA training output histograms.
Uses MVA_BDT_S (signal) and MVA_BDT_B (background) from training ROOT file.

Usage:
    python3 optimizeBinning_fromTraining.py [training_root_file] [n_bins]
"""

import ROOT
import numpy as np
import sys

ROOT.gROOT.SetBatch(True)

def find_data_range(h):
    """Find actual data range (non-zero bins)"""
    first_bin = 1
    last_bin = h.GetNbinsX()
    for i in range(1, h.GetNbinsX()+1):
        if h.GetBinContent(i) > 0:
            first_bin = i
            break
    for i in range(h.GetNbinsX(), 0, -1):
        if h.GetBinContent(i) > 0:
            last_bin = i
            break
    return h.GetXaxis().GetBinLowEdge(first_bin), h.GetXaxis().GetBinUpEdge(last_bin)

def optimize_binning_equal_bg(h_sig, h_bg, n_bins=7):
    """Find bin edges that give roughly equal background events per bin"""
    total_bg = h_bg.Integral()
    target_per_bin = total_bg / n_bins

    bin_edges = [h_bg.GetXaxis().GetXmin()]
    current_sum = 0

    for i in range(1, h_bg.GetNbinsX() + 1):
        current_sum += h_bg.GetBinContent(i)
        if current_sum >= target_per_bin and len(bin_edges) < n_bins:
            bin_edges.append(h_bg.GetXaxis().GetBinUpEdge(i))
            current_sum = 0

    bin_edges.append(h_bg.GetXaxis().GetXmax())
    return bin_edges

def calc_significance(h_sig, h_bg, edges):
    """Calculate S/sqrt(S+B) for given bin edges"""
    sig_total = 0
    print("\n  Bin contents:")
    for i in range(len(edges)-1):
        bin_low = h_sig.GetXaxis().FindBin(edges[i])
        bin_high = h_sig.GetXaxis().FindBin(edges[i+1]) - 1
        if bin_high < bin_low:
            bin_high = bin_low

        s = h_sig.Integral(bin_low, bin_high)
        b = h_bg.Integral(bin_low, bin_high)

        sig = s / np.sqrt(s + b) if s + b > 0 else 0
        sig_total += sig

        print(f"    [{edges[i]:.3f}, {edges[i+1]:.3f}]: S={s:.1f}, B={b:.1f}, S/sqrt(S+B)={sig:.3f}")

    return sig_total

def main():
    # Default training file
    train_file = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/BDTTrain/v3BDTttbb/inputList_1tau1l_final.csv.root"
    n_bins = 7

    if len(sys.argv) > 1:
        train_file = sys.argv[1]
    if len(sys.argv) > 2:
        n_bins = int(sys.argv[2])

    print("=" * 70)
    print(f"Binning Optimization from Training Output")
    print(f"  Training file: {train_file}")
    print(f"  Number of bins: {n_bins}")
    print("=" * 70)

    f = ROOT.TFile.Open(train_file)
    if not f or f.IsZombie():
        print(f"ERROR: Cannot open file {train_file}")
        return

    h_sig = f.Get("dataset/Method_BDT/BDT/MVA_BDT_S")
    h_bg = f.Get("dataset/Method_BDT/BDT/MVA_BDT_B")

    if not h_sig or not h_bg:
        print("ERROR: Cannot find MVA_BDT_S or MVA_BDT_B histograms")
        return

    # Print histogram info
    print(f"\nSignal (MVA_BDT_S):")
    print(f"  Entries: {h_sig.GetEntries():.0f}")
    print(f"  Range: [{h_sig.GetXaxis().GetXmin():.4f}, {h_sig.GetXaxis().GetXmax():.4f}]")
    print(f"  Mean: {h_sig.GetMean():.4f}, RMS: {h_sig.GetRMS():.4f}")

    print(f"\nBackground (MVA_BDT_B):")
    print(f"  Entries: {h_bg.GetEntries():.0f}")
    print(f"  Range: [{h_bg.GetXaxis().GetXmin():.4f}, {h_bg.GetXaxis().GetXmax():.4f}]")
    print(f"  Mean: {h_bg.GetMean():.4f}, RMS: {h_bg.GetRMS():.4f}")

    sig_min, sig_max = find_data_range(h_sig)
    bg_min, bg_max = find_data_range(h_bg)
    print(f"\nActual data ranges:")
    print(f"  Signal: [{sig_min:.4f}, {sig_max:.4f}]")
    print(f"  Background: [{bg_min:.4f}, {bg_max:.4f}]")

    # Optimize binning
    print("\n" + "=" * 70)
    print(f"Optimized {n_bins} bins (equal BG per bin):")
    print("=" * 70)

    edges = optimize_binning_equal_bg(h_sig, h_bg, n_bins)
    print(f"\nEdges: {[f'{e:.4f}' for e in edges]}")

    sig_total = calc_significance(h_sig, h_bg, edges)
    print(f"\n  Total S/sqrt(S+B): {sig_total:.3f}")

    # Print C++ code
    print("\n" + "=" * 70)
    print("For treeAnalyzer.C:")
    print("=" * 70)
    print(f"std::vector<Double_t> bins1tau1l = {{{', '.join([f'{e:.3f}' for e in edges])}}};")

    f.Close()

if __name__ == "__main__":
    main()
