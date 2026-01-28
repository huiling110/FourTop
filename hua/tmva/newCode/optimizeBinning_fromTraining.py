#!/usr/bin/env python3
"""
Binning optimization using TMVA training output histograms.
Uses MVA_BDT_S (signal) and MVA_BDT_B (background) from training ROOT file.

IMPORTANT: TMVA normalizes S and B to equal integrals. This script applies
proper luminosity scaling from WH output to get realistic S/sqrt(B).

Usage:
    python3 optimizeBinning_fromTraining.py [training_root_file] [n_bins]
"""

import ROOT
import numpy as np
import scipy.stats as stats
import sys
import os

ROOT.gROOT.SetBatch(True)

# Luminosity-scaled yields from WH (v0BDT 1tau1lSR, 2018)
# These are the TRUE yields we want to scale to
WH_YIELDS = {
    '1tau1l': {
        'signal': 3.47,      # tttt
        'background': 125.49  # fakeTau + tt + ttbb + ttX + singleTop + fakeLepton
    },
    '1tau0l': {
        'signal': 1.5,       # tttt (estimate)
        'background': 80.0   # (estimate - update when known)
    }
}

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

def scale_histogram(h_orig, scale_factor, name_suffix="_scaled"):
    """Create a scaled copy of histogram"""
    h_scaled = h_orig.Clone(h_orig.GetName() + name_suffix)
    h_scaled.Scale(scale_factor)
    return h_scaled

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

def adaptive_binning(h_background, target_bin_content):
    """Create bins with target background content per bin (from plotting/optimizeBinning.py)"""
    bin_edges = [h_background.GetXaxis().GetXmin()]
    current_bin_bg = 0

    for i in range(1, h_background.GetNbinsX() + 1):
        current_bin_bg += h_background.GetBinContent(i)

        if current_bin_bg >= target_bin_content or i == h_background.GetNbinsX():
            bin_edges.append(h_background.GetXaxis().GetBinUpEdge(i))
            current_bin_bg = 0

    return bin_edges

def calSig_lastBin(h_signal, h_background, scale=1.):
    """Calculate significance in last bin using Poisson p-value (from plotting/optimizeBinning.py)"""
    sLast = h_signal.GetBinContent(h_signal.GetNbinsX()) * scale
    bLast = h_background.GetBinContent(h_background.GetNbinsX()) * scale

    if bLast <= 0:
        return 0

    dataLast = sLast + bLast
    p_value = 1 - stats.poisson.cdf(dataLast - 1, bLast)

    # Avoid inf for very small p-values
    if p_value <= 0:
        return 10.0

    significance = stats.norm.ppf(1 - p_value)
    return significance

def optimize_binning_lastbin(h_sig, h_bg, scale=3.0):
    """
    Optimize binning to maximize last-bin significance (from plotting/optimizeBinning.py).
    Tries many different target_bin_content values.
    scale: luminosity scale factor (3.0 for Run2)
    """
    best_significance = 0
    best_bin_edges = []
    best_target = 0

    max_target = int(h_bg.Integral() / 2)

    print(f"\n  Scanning target_bin_content from 1 to {max_target}...")

    for target_bin_content in range(1, max_target + 1, 1):
        bin_edges = adaptive_binning(h_bg, target_bin_content)
        h_rebinned_signal = rebin_histogram(h_sig, bin_edges)
        h_rebinned_background = rebin_histogram(h_bg, bin_edges)

        significance = calSig_lastBin(h_rebinned_signal, h_rebinned_background, scale)

        if significance > best_significance:
            best_significance = significance
            best_bin_edges = bin_edges
            best_target = target_bin_content

    print(f"  Best: target_bin_content={best_target}, last-bin significance={best_significance:.3f}")
    print(f"  Number of bins: {len(best_bin_edges) - 1}")

    return best_bin_edges, best_significance

def calc_significance(h_sig, h_bg, edges, verbose=True):
    """Calculate S/sqrt(B) and S/sqrt(S+B) for given bin edges"""
    sig_sqrtB_total = 0
    sig_sqrtSB_total = 0

    if verbose:
        print("\n  Bin-by-bin breakdown:")
        print(f"  {'Bin Range':<20} {'S':>8} {'B':>10} {'S/sqrt(B)':>12} {'S/sqrt(S+B)':>12}")
        print("  " + "-" * 66)

    for i in range(len(edges)-1):
        bin_low = h_sig.GetXaxis().FindBin(edges[i])
        bin_high = h_sig.GetXaxis().FindBin(edges[i+1]) - 1
        if bin_high < bin_low:
            bin_high = bin_low

        s = h_sig.Integral(bin_low, bin_high)
        b = h_bg.Integral(bin_low, bin_high)

        sig_sqrtB = s / np.sqrt(b) if b > 0 else 0
        sig_sqrtSB = s / np.sqrt(s + b) if s + b > 0 else 0

        sig_sqrtB_total += sig_sqrtB
        sig_sqrtSB_total += sig_sqrtSB

        if verbose:
            print(f"  [{edges[i]:>7.3f}, {edges[i+1]:>6.3f}] {s:>8.2f} {b:>10.2f} {sig_sqrtB:>12.3f} {sig_sqrtSB:>12.3f}")

    if verbose:
        print("  " + "-" * 66)
        print(f"  {'TOTAL':>20} {h_sig.Integral():>8.2f} {h_bg.Integral():>10.2f} {sig_sqrtB_total:>12.3f} {sig_sqrtSB_total:>12.3f}")

    return sig_sqrtB_total, sig_sqrtSB_total

def rebin_histogram(histo, bin_edges):
    """Rebin histogram to new bin edges"""
    new_histo = ROOT.TH1D(histo.GetName() + "_rebin", histo.GetTitle(),
                          len(bin_edges) - 1, np.array(bin_edges))
    for i in range(1, histo.GetNbinsX() + 1):
        new_histo.Fill(histo.GetBinCenter(i), histo.GetBinContent(i))
    return new_histo

def plot_distributions(h_sig, h_bg, edges, output_dir, tag=""):
    """Plot S and B distributions with binning overlay"""
    ROOT.gStyle.SetOptStat(0)

    # Create rebinned histograms
    h_sig_rebin = rebin_histogram(h_sig, edges)
    h_bg_rebin = rebin_histogram(h_bg, edges)

    # --- Plot 1: Original fine binning ---
    c1 = ROOT.TCanvas("c1", "BDT Distributions", 1200, 500)
    c1.Divide(2, 1)

    # Left: linear scale
    c1.cd(1)
    h_bg_draw = h_bg.Clone("h_bg_draw")
    h_sig_draw = h_sig.Clone("h_sig_draw")

    h_bg_draw.SetLineColor(ROOT.kBlue)
    h_bg_draw.SetFillColor(ROOT.kBlue)
    h_bg_draw.SetFillStyle(3004)
    h_sig_draw.SetLineColor(ROOT.kRed)
    h_sig_draw.SetLineWidth(2)

    h_bg_draw.SetTitle(f"BDT Score Distribution (lumi-scaled){tag};BDT Score;Events")
    h_bg_draw.Draw("HIST")
    h_sig_draw.Draw("HIST SAME")

    # Draw bin edges as vertical lines
    lines = []
    for edge in edges[1:-1]:
        line = ROOT.TLine(edge, 0, edge, h_bg_draw.GetMaximum() * 0.8)
        line.SetLineColor(ROOT.kGray+2)
        line.SetLineStyle(2)
        line.Draw()
        lines.append(line)

    leg1 = ROOT.TLegend(0.15, 0.7, 0.45, 0.88)
    leg1.AddEntry(h_sig_draw, f"Signal (tttt): {h_sig.Integral():.2f}", "l")
    leg1.AddEntry(h_bg_draw, f"Background: {h_bg.Integral():.2f}", "f")
    leg1.Draw()

    # Right: log scale
    c1.cd(2)
    ROOT.gPad.SetLogy()
    h_bg_draw2 = h_bg.Clone("h_bg_draw2")
    h_sig_draw2 = h_sig.Clone("h_sig_draw2")
    h_bg_draw2.SetLineColor(ROOT.kBlue)
    h_bg_draw2.SetFillColor(ROOT.kBlue)
    h_bg_draw2.SetFillStyle(3004)
    h_sig_draw2.SetLineColor(ROOT.kRed)
    h_sig_draw2.SetLineWidth(2)
    h_bg_draw2.SetTitle(f"BDT Score Distribution (log scale){tag};BDT Score;Events")
    h_bg_draw2.SetMinimum(0.001)
    h_bg_draw2.Draw("HIST")
    h_sig_draw2.Draw("HIST SAME")

    for edge in edges[1:-1]:
        line = ROOT.TLine(edge, 0.001, edge, h_bg_draw2.GetMaximum() * 0.5)
        line.SetLineColor(ROOT.kGray+2)
        line.SetLineStyle(2)
        line.Draw()

    c1.SaveAs(f"{output_dir}/BDT_distribution_fine{tag}.png")
    c1.SaveAs(f"{output_dir}/BDT_distribution_fine{tag}.pdf")

    # --- Plot 2: Rebinned histograms ---
    c2 = ROOT.TCanvas("c2", "BDT Rebinned", 800, 600)
    ROOT.gPad.SetLogy()

    h_bg_rebin.SetLineColor(ROOT.kBlue)
    h_bg_rebin.SetFillColor(ROOT.kBlue)
    h_bg_rebin.SetFillStyle(3004)
    h_sig_rebin.SetLineColor(ROOT.kRed)
    h_sig_rebin.SetLineWidth(2)
    h_sig_rebin.SetFillColor(ROOT.kRed)
    h_sig_rebin.SetFillStyle(3005)

    h_bg_rebin.SetTitle(f"BDT Score (Optimized {len(edges)-1} bins){tag};BDT Score;Events")
    h_bg_rebin.SetMinimum(0.01)
    h_bg_rebin.Draw("HIST")
    h_sig_rebin.Draw("HIST SAME")

    leg2 = ROOT.TLegend(0.15, 0.75, 0.5, 0.88)
    leg2.AddEntry(h_sig_rebin, f"Signal (tttt): {h_sig_rebin.Integral():.2f}", "f")
    leg2.AddEntry(h_bg_rebin, f"Background: {h_bg_rebin.Integral():.2f}", "f")
    leg2.Draw()

    c2.SaveAs(f"{output_dir}/BDT_rebinned{tag}.png")
    c2.SaveAs(f"{output_dir}/BDT_rebinned{tag}.pdf")

    print(f"\n  Plots saved to {output_dir}/")

def main():
    # Default training file
    train_file = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/BDTTrain/v3BDTttbb/inputList_1tau1l_final.csv.root"
    n_bins = 7
    channel = '1tau1l'

    if len(sys.argv) > 1:
        train_file = sys.argv[1]
    if len(sys.argv) > 2:
        n_bins = int(sys.argv[2])
    if len(sys.argv) > 3:
        channel = sys.argv[3]

    # Output directory
    output_dir = os.path.dirname(train_file)
    if not output_dir:
        output_dir = "."

    print("=" * 70)
    print("Binning Optimization from Training Output (with lumi scaling)")
    print("=" * 70)
    print(f"  Training file: {train_file}")
    print(f"  Channel: {channel}")
    print(f"  Number of bins: {n_bins}")
    print(f"  Output dir: {output_dir}")

    f = ROOT.TFile.Open(train_file)
    if not f or f.IsZombie():
        print(f"ERROR: Cannot open file {train_file}")
        return

    h_sig_orig = f.Get("dataset/Method_BDT/BDT/MVA_BDT_S")
    h_bg_orig = f.Get("dataset/Method_BDT/BDT/MVA_BDT_B")

    if not h_sig_orig or not h_bg_orig:
        print("ERROR: Cannot find MVA_BDT_S or MVA_BDT_B histograms")
        return

    # Get scale factors
    train_sig_integral = h_sig_orig.Integral()
    train_bg_integral = h_bg_orig.Integral()

    target_sig = WH_YIELDS[channel]['signal']
    target_bg = WH_YIELDS[channel]['background']

    scale_sig = target_sig / train_sig_integral
    scale_bg = target_bg / train_bg_integral

    print("\n" + "=" * 70)
    print("Scaling Information")
    print("=" * 70)
    print(f"\n  Training integrals (TMVA normalized):")
    print(f"    Signal: {train_sig_integral:.2f}")
    print(f"    Background: {train_bg_integral:.2f}")
    print(f"\n  Target yields (from WH 1tau1lSR):")
    print(f"    Signal (tttt): {target_sig:.2f}")
    print(f"    Background: {target_bg:.2f}")
    print(f"\n  Scale factors:")
    print(f"    Signal: {scale_sig:.4f}")
    print(f"    Background: {scale_bg:.4f}")

    # Create scaled histograms
    h_sig = scale_histogram(h_sig_orig, scale_sig)
    h_bg = scale_histogram(h_bg_orig, scale_bg)

    # Print histogram info
    print("\n" + "=" * 70)
    print("Scaled Histogram Info")
    print("=" * 70)
    print(f"\n  Signal (scaled):")
    print(f"    Integral: {h_sig.Integral():.2f}")
    print(f"    Mean: {h_sig.GetMean():.4f}, RMS: {h_sig.GetRMS():.4f}")

    print(f"\n  Background (scaled):")
    print(f"    Integral: {h_bg.Integral():.2f}")
    print(f"    Mean: {h_bg.GetMean():.4f}, RMS: {h_bg.GetRMS():.4f}")

    sig_min, sig_max = find_data_range(h_sig)
    bg_min, bg_max = find_data_range(h_bg)
    print(f"\n  Actual data ranges:")
    print(f"    Signal: [{sig_min:.4f}, {sig_max:.4f}]")
    print(f"    Background: [{bg_min:.4f}, {bg_max:.4f}]")

    # Method 1: Equal BG per bin (fixed n_bins)
    print("\n" + "=" * 70)
    print(f"Method 1: Equal BG per bin ({n_bins} bins)")
    print("=" * 70)

    edges_equal = optimize_binning_equal_bg(h_sig, h_bg, n_bins)
    print(f"\n  Bin edges: {[f'{e:.3f}' for e in edges_equal]}")
    sig_sqrtB_eq, sig_sqrtSB_eq = calc_significance(h_sig, h_bg, edges_equal)

    # Method 2: Optimize for last-bin significance (like plotting/optimizeBinning.py)
    print("\n" + "=" * 70)
    print("Method 2: Optimize last-bin significance (Run2 scale=3x)")
    print("=" * 70)

    edges_lastbin, lastbin_sig = optimize_binning_lastbin(h_sig, h_bg, scale=3.0)
    print(f"\n  Bin edges: {[f'{e:.3f}' for e in edges_lastbin]}")
    sig_sqrtB_lb, sig_sqrtSB_lb = calc_significance(h_sig, h_bg, edges_lastbin)

    # Method 3: Even binning for comparison
    print("\n" + "=" * 70)
    print(f"Method 3: Even {n_bins} bins (for comparison)")
    print("=" * 70)
    even_edges = list(np.linspace(sig_min, sig_max, n_bins + 1))
    print(f"\n  Bin edges: {[f'{e:.3f}' for e in even_edges]}")
    even_sqrtB, even_sqrtSB = calc_significance(h_sig, h_bg, even_edges)

    # Summary
    print("\n" + "=" * 70)
    print("SUMMARY")
    print("=" * 70)
    print(f"\n  {'Method':<30} {'S/sqrt(B)':>12} {'S/sqrt(S+B)':>14} {'N_bins':>8}")
    print("  " + "-" * 68)
    print(f"  {'Equal BG/bin':<30} {sig_sqrtB_eq:>12.3f} {sig_sqrtSB_eq:>14.3f} {len(edges_equal)-1:>8}")
    print(f"  {'Last-bin optimized (x3)':<30} {sig_sqrtB_lb:>12.3f} {sig_sqrtSB_lb:>14.3f} {len(edges_lastbin)-1:>8}")
    print(f"  {'Even binning':<30} {even_sqrtB:>12.3f} {even_sqrtSB:>14.3f} {n_bins:>8}")

    # Use the best method (last-bin optimized)
    best_edges = edges_lastbin
    print(f"\n  Recommended: Last-bin optimized binning")

    # Print C++ code
    print("\n" + "=" * 70)
    print("For treeAnalyzer.C (last-bin optimized):")
    print("=" * 70)
    print(f"std::vector<Double_t> bins{channel} = {{{', '.join([f'{e:.3f}' for e in best_edges])}}};")

    # Generate plots for best method
    plot_distributions(h_sig, h_bg, best_edges, output_dir, f"_{channel}_lastbin")
    plot_distributions(h_sig, h_bg, edges_equal, output_dir, f"_{channel}_equalBG")

    f.Close()

if __name__ == "__main__":
    main()
