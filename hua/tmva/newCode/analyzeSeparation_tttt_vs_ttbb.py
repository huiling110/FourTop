#!/usr/bin/env python3
"""
Analyze separation power of all variables for tttt vs TTBB discrimination.
Creates a ranking and plots distributions of top discriminating variables.
"""

import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)
import numpy as np
import os

# Input files
TTTT_FILE = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/tttt.root"
TTBB_FILE = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadro_v94HadroPreJetVetoHemOnly_TTBBtest/mc/TTBB_4f_TTTo2L2Nu.root"

# SR cut (matching WH for 1tau1l MC)
# Baseline + 1tau1lSR selection
BASELINE_CUT = "(jets_num>=6 && bjetsM_num>=2) && ((bjetsM_num<4 && jets_HT>500 && jets_6pt>40) || (bjetsM_num>=4 && jets_HT>480 && jets_6pt>38))"
SR_1TAU1L_MC = "(tausF_1isTight && tausF_1genFlavour!=0 && tausF_num==1) && ((elesTopMVAF_1isTightPrompt || muonsTopMVAF_1isTightPrompt) && lepTopMVAF_num==1) && jets_num>=7 && bjetsM_num>=3"
SR_CUT = f"({BASELINE_CUT}) && ({SR_1TAU1L_MC})"

# Output directory
OUTPUT_DIR = "separation_plots"

def get_all_branches(tree):
    """Get all numeric branches from tree"""
    branches = []
    skip_patterns = ['EVENT_', 'weight', 'Weight', 'SF', 'sf_', 'HLT_', 'genWeight',
                     'scale_', 'pdf_', 'isMatched', 'isTight', 'genFlavour', 'charge',
                     'Sum$', 'Alt$', 'max_', 'min_', 'nGenJet', 'nJet']

    for b in tree.GetListOfBranches():
        name = b.GetName()
        # Skip non-physics branches
        skip = False
        for pattern in skip_patterns:
            if pattern in name:
                skip = True
                break
        if skip:
            continue

        # Only include certain types
        if any(x in name for x in ['_num', '_pt', '_eta', '_phi', '_mass',
                                    '_HT', '_MHT', 'deltaR', 'Delta', 'invariant',
                                    'sphericity', 'aplanarity', 'centrality',
                                    'Bscore', 'Score', 'ratio', 'Divide',
                                    'strange', 'trans', 'MET']):
            branches.append(name)

    return branches

def get_quantile_range(tree1, tree2, var, cut, q_low=0.01, q_high=0.99):
    """Get range based on quantiles, excluding -99 padding"""
    values = []

    # Collect values from both trees
    for tree in [tree1, tree2]:
        n_entries = tree.Draw(var, cut, "goff")
        if n_entries > 0:
            v1 = tree.GetV1()
            for i in range(min(n_entries, 100000)):  # Limit for memory
                val = v1[i]
                if val > -90:  # Exclude -99 padding
                    values.append(val)

    if len(values) < 100:
        return None, None

    values = np.array(values)
    xmin = np.quantile(values, q_low)
    xmax = np.quantile(values, q_high)

    # Add small margin
    margin = (xmax - xmin) * 0.05
    return xmin - margin, xmax + margin

def calculate_separation(tree1, tree2, var, cut, n_bins=50):
    """Calculate separation power between two samples for a variable"""

    # Get proper range using quantiles
    result = get_quantile_range(tree1, tree2, var, cut)
    if result[0] is None:
        return None, None, None

    xmin, xmax = result

    # Ensure reasonable range
    if xmax - xmin < 1e-6:
        return None, None, None

    # Create histograms
    h1 = ROOT.TH1F(f"h1_{var}", "", n_bins, xmin, xmax)
    h2 = ROOT.TH1F(f"h2_{var}", "", n_bins, xmin, xmax)

    tree1.Draw(f"{var}>>h1_{var}", cut, "goff")
    tree2.Draw(f"{var}>>h2_{var}", cut, "goff")

    n1 = h1.GetEntries()
    n2 = h2.GetEntries()

    if n1 < 50 or n2 < 50:
        h1.Delete()
        h2.Delete()
        return None, None, None

    # Normalize
    if h1.Integral() > 0:
        h1.Scale(1.0 / h1.Integral())
    if h2.Integral() > 0:
        h2.Scale(1.0 / h2.Integral())

    # Calculate separation = (mean1 - mean2) / sqrt(0.5*(rms1^2 + rms2^2))
    mean1, mean2 = h1.GetMean(), h2.GetMean()
    rms1, rms2 = h1.GetRMS(), h2.GetRMS()

    avg_rms = np.sqrt(0.5 * (rms1**2 + rms2**2))
    if avg_rms > 0:
        separation = abs(mean1 - mean2) / avg_rms
    else:
        separation = 0

    # Also calculate overlap (KL divergence proxy)
    overlap = 0
    for i in range(1, n_bins + 1):
        p1 = h1.GetBinContent(i)
        p2 = h2.GetBinContent(i)
        overlap += min(p1, p2)

    h1.Delete()
    h2.Delete()

    return separation, 1 - overlap, (mean1, mean2, rms1, rms2)

def plot_variable(tree1, tree2, var, cut, output_dir, rank, separation):
    """Plot variable distribution for tttt vs TTBB"""

    # Get proper range using quantiles
    result = get_quantile_range(tree1, tree2, var, cut)
    if result[0] is None:
        print(f"  Skipping plot for {var} - not enough data")
        return

    xmin, xmax = result

    h_tttt = ROOT.TH1F(f"h_tttt_{var}", "", 50, xmin, xmax)
    h_ttbb = ROOT.TH1F(f"h_ttbb_{var}", "", 50, xmin, xmax)

    tree1.Draw(f"{var}>>h_tttt_{var}", cut, "goff")
    tree2.Draw(f"{var}>>h_ttbb_{var}", cut, "goff")

    # Normalize
    if h_tttt.Integral() > 0:
        h_tttt.Scale(1.0 / h_tttt.Integral())
    if h_ttbb.Integral() > 0:
        h_ttbb.Scale(1.0 / h_ttbb.Integral())

    # Style
    h_tttt.SetLineColor(ROOT.kRed)
    h_tttt.SetLineWidth(2)
    h_tttt.SetFillColor(ROOT.kRed)
    h_tttt.SetFillStyle(3004)

    h_ttbb.SetLineColor(ROOT.kBlue)
    h_ttbb.SetLineWidth(2)
    h_ttbb.SetFillColor(ROOT.kBlue)
    h_ttbb.SetFillStyle(3005)

    # Canvas
    c = ROOT.TCanvas("c", "", 800, 600)
    c.SetLeftMargin(0.12)
    c.SetRightMargin(0.05)

    # Draw
    max_y = max(h_tttt.GetMaximum(), h_ttbb.GetMaximum()) * 1.3
    h_tttt.SetMaximum(max_y)
    h_tttt.SetTitle(f"Rank #{rank}: {var} (sep={separation:.3f})")
    h_tttt.GetXaxis().SetTitle(var)
    h_tttt.GetYaxis().SetTitle("Normalized")

    h_tttt.Draw("hist")
    h_ttbb.Draw("hist same")

    # Legend
    leg = ROOT.TLegend(0.65, 0.75, 0.92, 0.88)
    leg.SetBorderSize(0)
    leg.AddEntry(h_tttt, "tttt (signal)", "f")
    leg.AddEntry(h_ttbb, "TTBB (background)", "f")
    leg.Draw()

    # Save
    c.SaveAs(f"{output_dir}/rank{rank:02d}_{var}.png")
    c.SaveAs(f"{output_dir}/rank{rank:02d}_{var}.pdf")

    h_tttt.Delete()
    h_ttbb.Delete()
    c.Close()

def main():
    # Create output directory
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    # Open files
    print("Loading files...")
    f_tttt = ROOT.TFile(TTTT_FILE)
    f_ttbb = ROOT.TFile(TTBB_FILE)

    tree_tttt = f_tttt.Get("newtree")
    tree_ttbb = f_ttbb.Get("newtree")

    # Get all branches
    print("Getting branches...")
    branches = get_all_branches(tree_tttt)
    print(f"Found {len(branches)} candidate variables")

    # Calculate separation for each variable
    print("\nCalculating separation power...")
    results = []

    for i, var in enumerate(branches):
        if (i + 1) % 50 == 0:
            print(f"  Processing {i+1}/{len(branches)}...")

        try:
            sep, non_overlap, stats = calculate_separation(tree_tttt, tree_ttbb, var, SR_CUT)
            if sep is not None:
                results.append((var, sep, non_overlap, stats))
        except Exception as e:
            pass

    # Sort by separation
    results.sort(key=lambda x: x[1], reverse=True)

    # Print ranking
    print("\n" + "=" * 80)
    print("VARIABLE SEPARATION RANKING: tttt vs TTBB")
    print("=" * 80)
    print(f"{'Rank':<6} {'Variable':<35} {'Separation':>12} {'Non-overlap':>12}")
    print("-" * 80)

    for i, (var, sep, non_overlap, stats) in enumerate(results[:50]):
        print(f"{i+1:<6} {var:<35} {sep:>12.3f} {non_overlap:>12.3f}")

    # Plot top 20 variables
    print(f"\nPlotting top 20 variables to {OUTPUT_DIR}/...")
    for i, (var, sep, non_overlap, stats) in enumerate(results[:20]):
        plot_variable(tree_tttt, tree_ttbb, var, SR_CUT, OUTPUT_DIR, i+1, sep)
        print(f"  Plotted: {var}")

    # Save full results to file
    with open(f"{OUTPUT_DIR}/separation_ranking.txt", "w") as f:
        f.write("=" * 80 + "\n")
        f.write("VARIABLE SEPARATION RANKING: tttt vs TTBB\n")
        f.write("=" * 80 + "\n")
        f.write(f"{'Rank':<6} {'Variable':<35} {'Separation':>12} {'tttt_mean':>12} {'TTBB_mean':>12}\n")
        f.write("-" * 80 + "\n")
        for i, (var, sep, non_overlap, stats) in enumerate(results):
            f.write(f"{i+1:<6} {var:<35} {sep:>12.3f} {stats[0]:>12.3f} {stats[1]:>12.3f}\n")

    print(f"\nResults saved to {OUTPUT_DIR}/separation_ranking.txt")
    print(f"Plots saved to {OUTPUT_DIR}/")

    f_tttt.Close()
    f_ttbb.Close()

if __name__ == "__main__":
    main()
