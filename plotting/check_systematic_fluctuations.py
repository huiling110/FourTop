#!/usr/bin/env python3
"""
Check Systematic Fluctuations in Template Files

Identifies systematic variations with large bin-by-bin fluctuations that may indicate
issues with smoothing or low statistics.

Usage:
    python3 plotting/check_systematic_fluctuations.py TEMPLATE.root [--threshold 0.1] [--output-dir plots/] [--channel 1tau1l]

    # Plot top 5 systematics per process for all processes
    python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --top-per-process 5

    # Compare smoothed vs unsmoothed templates
    python3 plotting/check_systematic_fluctuations.py TEMPLATE.root --compare-smoothed SMOOTHED.root

Example:
    python3 plotting/check_systematic_fluctuations.py /publicfs/.../templatesForCombine1tau1l_new_notMCFTau_unblind.root --top-per-process 5
"""

import ROOT
import os
import sys
import argparse
from collections import defaultdict
import math

# Suppress ROOT warnings
ROOT.gErrorIgnoreLevel = ROOT.kError
ROOT.gROOT.SetBatch(True)


def get_histogram_names(tfile):
    """Get all histogram names from ROOT file."""
    return [k.GetName() for k in tfile.GetListOfKeys()]


def parse_histogram_name(name, channel="1tau1l"):
    """Parse histogram name into process, region, systematic components."""
    # Expected format: process_region_BDT or process_region_systematicUp/Down_BDT
    # Example: tt_1tau1lSR_BDT, tt_1tau1lSR_CMS_scale_j_AbsoluteUp_BDT

    if not name.endswith("_BDT"):
        return None, None, None, None

    name = name[:-4]  # Remove _BDT suffix

    # Find region marker
    sr_marker = f"{channel}SR"
    cr_marker = f"{channel}CR"

    region = None
    process = None
    systematic_part = None

    if sr_marker in name:
        region = "SR"
        # Split on the region marker
        idx = name.find(f"_{sr_marker}")
        process = name[:idx]
        remainder = name[idx + len(f"_{sr_marker}"):]
        # Remove leading underscore if present
        systematic_part = remainder.lstrip("_") if remainder else ""
    elif cr_marker in name:
        region = "CR"
        idx = name.find(f"_{cr_marker}")
        process = name[:idx]
        remainder = name[idx + len(f"_{cr_marker}"):]
        systematic_part = remainder.lstrip("_").lstrip("12_") if remainder else ""
    else:
        return None, None, None, None

    if not process:
        return None, None, None, None

    if not systematic_part:
        # Nominal histogram
        return process, region, None, None

    systematic = systematic_part

    # Determine direction
    direction = None
    if systematic.endswith("Up"):
        direction = "Up"
        systematic = systematic[:-2]
    elif systematic.endswith("Down"):
        direction = "Down"
        systematic = systematic[:-4]

    return process, region, systematic, direction


def calculate_variation(nominal, varied, min_events=0.1):
    """Calculate bin-by-bin variation between nominal and varied histogram.

    Args:
        nominal: Nominal histogram
        varied: Varied histogram
        min_events: Minimum events in bin to calculate variation (avoid div by zero)
    """
    if not nominal or not varied:
        return None

    nbins = nominal.GetNbinsX()
    variations = []

    for i in range(1, nbins + 1):
        nom = nominal.GetBinContent(i)
        var = varied.GetBinContent(i)

        if nom > min_events:
            rel_var = (var / nom - 1) * 100  # Percentage
        else:
            # Skip bins with too few events - mark as None
            rel_var = None

        variations.append(rel_var)

    return variations


def calculate_fluctuation_score(variations):
    """
    Calculate a score indicating how much the variation fluctuates bin-to-bin.
    Higher score = more problematic fluctuations.

    Considers:
    1. Max absolute variation
    2. RMS of variations
    3. Max bin-to-bin change (derivative)
    """
    if not variations or len(variations) < 2:
        return 0, {}

    # Filter out None values (bins with too few events)
    finite_vars = [v for v in variations if v is not None and abs(v) < 1000]
    if len(finite_vars) < 2:
        return 0, {}

    max_var = max(abs(v) for v in finite_vars)
    mean_var = sum(finite_vars) / len(finite_vars)
    rms = math.sqrt(sum((v - mean_var)**2 for v in finite_vars) / len(finite_vars))

    # Calculate derivative (bin-to-bin changes) - only for consecutive valid bins
    derivatives = []
    for i in range(len(variations)-1):
        if variations[i] is not None and variations[i+1] is not None:
            derivatives.append(abs(variations[i+1] - variations[i]))
    max_deriv = max(derivatives) if derivatives else 0

    # Combined score: prioritize large bin-to-bin fluctuations
    # Large max_deriv indicates shape distortion (bad smoothing)
    score = max(max_var, max_deriv, rms * 2)

    # Format variations for display (replace None with '-')
    display_vars = [f"{v:.1f}%" if v is not None else "-" for v in variations]

    metrics = {
        'max_var': max_var,
        'rms': rms,
        'max_deriv': max_deriv,
        'mean': mean_var,
        'variations': variations,
        'display_vars': display_vars,
        'n_valid_bins': len(finite_vars)
    }

    return score, metrics


def analyze_template(tfile, channel="1tau1l", threshold=10.0):
    """Analyze all systematics in template file."""
    names = get_histogram_names(tfile)

    # Group histograms by process and systematic
    nominals = {}  # process_region -> histogram
    systematics = defaultdict(dict)  # (process, region, systematic) -> {Up: hist, Down: hist}

    for name in names:
        process, region, systematic, direction = parse_histogram_name(name, channel)
        if process is None:
            continue

        hist = tfile.Get(name)
        if not hist:
            continue

        key = f"{process}_{region}"

        if systematic is None:
            nominals[key] = hist
        else:
            sys_key = (process, region, systematic)
            systematics[sys_key][direction] = hist

    # Analyze each systematic
    results = []

    for (process, region, systematic), directions in systematics.items():
        key = f"{process}_{region}"
        nominal = nominals.get(key)

        if not nominal:
            continue

        for direction, varied in directions.items():
            if direction is None:
                continue

            variations = calculate_variation(nominal, varied)
            if variations is None:
                continue

            score, metrics = calculate_fluctuation_score(variations)

            if score >= threshold:
                results.append({
                    'process': process,
                    'region': region,
                    'systematic': systematic,
                    'direction': direction,
                    'score': score,
                    'metrics': metrics,
                    'nominal': nominal,
                    'varied': varied
                })

    # Sort by score (highest first)
    results.sort(key=lambda x: x['score'], reverse=True)

    return results


def plot_variation(result, output_dir, index):
    """Create a plot showing the systematic variation."""
    ROOT.gStyle.SetOptStat(0)

    canvas = ROOT.TCanvas(f"c_{index}", "", 800, 600)
    canvas.SetGrid()

    nominal = result['nominal']
    varied = result['varied']
    variations = result['metrics']['variations']

    nbins = nominal.GetNbinsX()

    # Create variation histogram
    h_var = ROOT.TH1F(f"h_var_{index}", "", nbins,
                       nominal.GetXaxis().GetXmin(),
                       nominal.GetXaxis().GetXmax())

    for i, var in enumerate(variations):
        if var is not None:
            h_var.SetBinContent(i + 1, var)
        else:
            h_var.SetBinContent(i + 1, 0)  # Empty bins show as 0

    # Style
    h_var.SetLineColor(ROOT.kBlue)
    h_var.SetLineWidth(2)
    h_var.SetFillColor(ROOT.kBlue - 9)
    h_var.SetFillStyle(3001)

    title = f"{result['process']} | {result['systematic']}{result['direction']}"
    h_var.SetTitle(f"{title};BDT bin;Variation [%]")

    # Set y-axis range - only consider valid variations
    valid_vars = [v for v in variations if v is not None]
    if valid_vars:
        max_var = max(abs(v) for v in valid_vars)
    else:
        max_var = 10
    h_var.GetYaxis().SetRangeUser(-max_var * 1.3, max_var * 1.3)

    h_var.Draw("HIST")

    # Add zero line
    line = ROOT.TLine(h_var.GetXaxis().GetXmin(), 0,
                       h_var.GetXaxis().GetXmax(), 0)
    line.SetLineColor(ROOT.kRed)
    line.SetLineStyle(2)
    line.Draw()

    # Add info box
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.035)
    latex.DrawLatex(0.15, 0.85, f"Max variation: {result['metrics']['max_var']:.1f}%")
    latex.DrawLatex(0.15, 0.80, f"RMS: {result['metrics']['rms']:.1f}%")
    latex.DrawLatex(0.15, 0.75, f"Max bin-to-bin: {result['metrics']['max_deriv']:.1f}%")
    latex.DrawLatex(0.15, 0.70, f"Score: {result['score']:.1f}")

    # Save
    safe_name = f"{result['process']}_{result['systematic']}_{result['direction']}"
    safe_name = safe_name.replace("/", "_")

    output_path = os.path.join(output_dir, f"fluctuation_{index:03d}_{safe_name}.png")
    canvas.SaveAs(output_path)

    return output_path


def plot_comparison(result, output_dir, index):
    """Create a plot comparing nominal and varied shapes (single direction)."""
    # This function is kept for backwards compatibility but not used
    pass


def plot_systematic_updown(process, region, systematic, nominal, varied_up, varied_down,
                           metrics_up, metrics_down, output_dir, index):
    """Create a plot comparing nominal with both Up and Down variations."""
    ROOT.gStyle.SetOptStat(0)

    canvas = ROOT.TCanvas(f"c_updown_{index}", "", 1000, 800)

    # Upper pad: shapes
    pad1 = ROOT.TPad(f"pad1_{index}", "", 0, 0.35, 1, 1)
    pad1.SetBottomMargin(0.02)
    pad1.SetGrid()
    pad1.Draw()

    # Lower pad: ratio
    pad2 = ROOT.TPad(f"pad2_{index}", "", 0, 0, 1, 0.35)
    pad2.SetTopMargin(0.02)
    pad2.SetBottomMargin(0.3)
    pad2.SetGrid()
    pad2.Draw()

    nom_clone = nominal.Clone(f"nom_clone_{index}")
    up_clone = varied_up.Clone(f"up_clone_{index}") if varied_up else None
    down_clone = varied_down.Clone(f"down_clone_{index}") if varied_down else None

    # Upper pad - shapes
    pad1.cd()

    nom_clone.SetLineColor(ROOT.kBlack)
    nom_clone.SetLineWidth(2)
    nom_clone.SetMarkerStyle(20)
    nom_clone.SetMarkerSize(0.8)

    if up_clone:
        up_clone.SetLineColor(ROOT.kRed)
        up_clone.SetLineWidth(2)
        up_clone.SetLineStyle(1)

    if down_clone:
        down_clone.SetLineColor(ROOT.kBlue)
        down_clone.SetLineWidth(2)
        down_clone.SetLineStyle(1)

    title = f"{process} | {systematic}"
    nom_clone.SetTitle(title)
    nom_clone.GetYaxis().SetTitle("Events")
    nom_clone.GetXaxis().SetLabelSize(0)

    max_val = nom_clone.GetMaximum()
    if up_clone:
        max_val = max(max_val, up_clone.GetMaximum())
    if down_clone:
        max_val = max(max_val, down_clone.GetMaximum())
    nom_clone.GetYaxis().SetRangeUser(0, max_val * 1.4)

    nom_clone.Draw("HIST E")
    if up_clone:
        up_clone.Draw("HIST SAME")
    if down_clone:
        down_clone.Draw("HIST SAME")

    # Legend
    leg = ROOT.TLegend(0.62, 0.68, 0.88, 0.88)
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.AddEntry(nom_clone, "Nominal", "l")
    if up_clone:
        leg.AddEntry(up_clone, "Up", "l")
    if down_clone:
        leg.AddEntry(down_clone, "Down", "l")
    leg.Draw()

    # Add info text
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.035)
    if metrics_up:
        latex.SetTextColor(ROOT.kRed)
        latex.DrawLatex(0.15, 0.85, f"Up: max={metrics_up['max_var']:.1f}%, RMS={metrics_up['rms']:.1f}%")
    if metrics_down:
        latex.SetTextColor(ROOT.kBlue)
        latex.DrawLatex(0.15, 0.80, f"Down: max={metrics_down['max_var']:.1f}%, RMS={metrics_down['rms']:.1f}%")

    # Lower pad - ratio
    pad2.cd()

    # Create ratio histograms
    if up_clone:
        ratio_up = up_clone.Clone(f"ratio_up_{index}")
        ratio_up.Divide(nom_clone)
        ratio_up.SetLineColor(ROOT.kRed)
        ratio_up.SetMarkerColor(ROOT.kRed)
        ratio_up.SetMarkerStyle(20)
        ratio_up.SetMarkerSize(0.6)

    if down_clone:
        ratio_down = down_clone.Clone(f"ratio_down_{index}")
        ratio_down.Divide(nom_clone)
        ratio_down.SetLineColor(ROOT.kBlue)
        ratio_down.SetMarkerColor(ROOT.kBlue)
        ratio_down.SetMarkerStyle(21)
        ratio_down.SetMarkerSize(0.6)

    # Determine y-axis range
    max_ratio = 1.5
    min_ratio = 0.5
    if up_clone:
        for i in range(1, ratio_up.GetNbinsX() + 1):
            val = ratio_up.GetBinContent(i)
            if val > 0:
                max_ratio = max(max_ratio, val * 1.1)
                min_ratio = min(min_ratio, val * 0.9)
    if down_clone:
        for i in range(1, ratio_down.GetNbinsX() + 1):
            val = ratio_down.GetBinContent(i)
            if val > 0:
                max_ratio = max(max_ratio, val * 1.1)
                min_ratio = min(min_ratio, val * 0.9)

    # Draw first histogram to set axes
    first_ratio = ratio_up if up_clone else ratio_down
    first_ratio.SetTitle("")
    first_ratio.GetYaxis().SetTitle("Var / Nom")
    first_ratio.GetYaxis().SetTitleSize(0.08)
    first_ratio.GetYaxis().SetTitleOffset(0.5)
    first_ratio.GetYaxis().SetLabelSize(0.07)
    first_ratio.GetXaxis().SetTitle("BDT bin")
    first_ratio.GetXaxis().SetTitleSize(0.1)
    first_ratio.GetXaxis().SetLabelSize(0.08)
    first_ratio.GetYaxis().SetRangeUser(min_ratio, max_ratio)

    first_ratio.Draw("P")
    if up_clone and down_clone:
        ratio_down.Draw("P SAME")

    # Unity line
    line = ROOT.TLine(first_ratio.GetXaxis().GetXmin(), 1,
                       first_ratio.GetXaxis().GetXmax(), 1)
    line.SetLineColor(ROOT.kBlack)
    line.SetLineStyle(2)
    line.SetLineWidth(2)
    line.Draw()

    # Save
    safe_name = f"{process}_{systematic}"
    safe_name = safe_name.replace("/", "_").replace(" ", "_")

    output_path = os.path.join(output_dir, f"systematic_{index:03d}_{safe_name}.png")
    canvas.SaveAs(output_path)

    return output_path


def plot_variation_updown(process, region, systematic, variations_up, variations_down,
                          metrics_up, metrics_down, nominal, output_dir, index):
    """Create a bar plot showing Up and Down variations side by side."""
    ROOT.gStyle.SetOptStat(0)

    canvas = ROOT.TCanvas(f"c_var_{index}", "", 900, 600)
    canvas.SetGrid()

    nbins = nominal.GetNbinsX()

    # Create histograms for variations
    h_up = ROOT.TH1F(f"h_up_{index}", "", nbins,
                      nominal.GetXaxis().GetXmin(),
                      nominal.GetXaxis().GetXmax())
    h_down = ROOT.TH1F(f"h_down_{index}", "", nbins,
                        nominal.GetXaxis().GetXmin(),
                        nominal.GetXaxis().GetXmax())

    for i in range(nbins):
        if variations_up and variations_up[i] is not None:
            h_up.SetBinContent(i + 1, variations_up[i])
        if variations_down and variations_down[i] is not None:
            h_down.SetBinContent(i + 1, variations_down[i])

    # Style
    h_up.SetLineColor(ROOT.kRed)
    h_up.SetLineWidth(2)
    h_up.SetFillColor(ROOT.kRed - 9)
    h_up.SetFillStyle(3004)

    h_down.SetLineColor(ROOT.kBlue)
    h_down.SetLineWidth(2)
    h_down.SetFillColor(ROOT.kBlue - 9)
    h_down.SetFillStyle(3005)

    title = f"{process} | {systematic}"
    h_up.SetTitle(f"{title};BDT bin;Variation [%]")

    # Determine y-axis range
    all_vars = []
    if variations_up:
        all_vars.extend([v for v in variations_up if v is not None])
    if variations_down:
        all_vars.extend([v for v in variations_down if v is not None])

    if all_vars:
        max_var = max(abs(v) for v in all_vars)
    else:
        max_var = 10
    h_up.GetYaxis().SetRangeUser(-max_var * 1.4, max_var * 1.4)

    h_up.Draw("HIST")
    h_down.Draw("HIST SAME")

    # Zero line
    line = ROOT.TLine(h_up.GetXaxis().GetXmin(), 0,
                       h_up.GetXaxis().GetXmax(), 0)
    line.SetLineColor(ROOT.kBlack)
    line.SetLineStyle(2)
    line.SetLineWidth(2)
    line.Draw()

    # Legend
    leg = ROOT.TLegend(0.7, 0.78, 0.88, 0.88)
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.AddEntry(h_up, "Up", "f")
    leg.AddEntry(h_down, "Down", "f")
    leg.Draw()

    # Info box
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.032)
    if metrics_up:
        latex.SetTextColor(ROOT.kRed)
        latex.DrawLatex(0.15, 0.85, f"Up: max={metrics_up['max_var']:.1f}%, maxΔ={metrics_up['max_deriv']:.1f}%")
    if metrics_down:
        latex.SetTextColor(ROOT.kBlue)
        latex.DrawLatex(0.15, 0.80, f"Down: max={metrics_down['max_var']:.1f}%, maxΔ={metrics_down['max_deriv']:.1f}%")

    # Save
    safe_name = f"{process}_{systematic}"
    safe_name = safe_name.replace("/", "_").replace(" ", "_")

    output_path = os.path.join(output_dir, f"variation_{index:03d}_{safe_name}.png")
    canvas.SaveAs(output_path)

    return output_path


def get_top_systematics_per_process(results, n_top=5, region="SR"):
    """Group results by process and return top N systematics for each process.

    Only considers results from the specified region to avoid mixing SR and CR.
    """
    from collections import defaultdict

    # Group by process, filtering by region
    by_process = defaultdict(list)
    for r in results:
        if r['region'] == region:
            by_process[r['process']].append(r)

    # For each process, group by systematic and get max score
    top_per_process = {}
    for process, proc_results in by_process.items():
        # Group by systematic
        by_syst = defaultdict(list)
        for r in proc_results:
            by_syst[r['systematic']].append(r)

        # Get max score for each systematic
        syst_scores = []
        for syst, syst_results in by_syst.items():
            max_score = max(r['score'] for r in syst_results)
            syst_scores.append((syst, max_score, syst_results))

        # Sort by score and take top N
        syst_scores.sort(key=lambda x: x[1], reverse=True)
        top_per_process[process] = syst_scores[:n_top]

    return top_per_process


def plot_top_systematics_for_process(process, top_systematics, nominals, tfile,
                                      output_dir, channel="1tau1l"):
    """Plot top N systematics for a single process on one canvas."""
    ROOT.gStyle.SetOptStat(0)

    n_syst = len(top_systematics)
    if n_syst == 0:
        return

    # Create canvas with subplots
    canvas = ROOT.TCanvas(f"c_{process}", f"{process} - Top Systematics", 1600, 400 * n_syst)
    canvas.Divide(2, n_syst)

    region = "SR"
    nominal_key = f"{process}_{region}"
    nominal = nominals.get(nominal_key)

    if not nominal:
        print(f"  Warning: No nominal histogram for {process}")
        return

    for i, (syst_name, score, syst_results) in enumerate(top_systematics):
        # Get Up and Down histograms
        up_hist = None
        down_hist = None
        up_result = None
        down_result = None

        for r in syst_results:
            if r['direction'] == 'Up':
                up_hist = r['varied']
                up_result = r
            elif r['direction'] == 'Down':
                down_hist = r['varied']
                down_result = r

        # Left panel: Shape comparison
        canvas.cd(2*i + 1)
        ROOT.gPad.SetGrid()
        ROOT.gPad.SetLeftMargin(0.12)
        ROOT.gPad.SetRightMargin(0.05)

        nom_clone = nominal.Clone(f"nom_{process}_{i}")
        nom_clone.SetLineColor(ROOT.kBlack)
        nom_clone.SetLineWidth(2)
        nom_clone.SetMarkerStyle(20)
        nom_clone.SetMarkerSize(0.8)

        # Create error band histogram for stat uncertainty
        nom_err_band = nominal.Clone(f"nom_err_{process}_{i}")
        nom_err_band.SetFillColor(ROOT.kGray)
        nom_err_band.SetFillStyle(3001)
        nom_err_band.SetLineColor(ROOT.kBlack)
        nom_err_band.SetMarkerSize(0)

        title = f"{process} | {syst_name} (score={score:.1f})"
        nom_clone.SetTitle(title)
        nom_clone.GetYaxis().SetTitle("Events")
        nom_clone.GetXaxis().SetTitle("BDT bin")

        max_val = nom_clone.GetMaximum()
        min_val = 0

        if up_hist:
            up_clone = up_hist.Clone(f"up_{process}_{i}")
            up_clone.SetLineColor(ROOT.kRed)
            up_clone.SetLineWidth(2)
            up_clone.SetLineStyle(1)
            max_val = max(max_val, up_clone.GetMaximum())

        if down_hist:
            down_clone = down_hist.Clone(f"down_{process}_{i}")
            down_clone.SetLineColor(ROOT.kBlue)
            down_clone.SetLineWidth(2)
            down_clone.SetLineStyle(1)
            max_val = max(max_val, down_clone.GetMaximum())

        nom_clone.GetYaxis().SetRangeUser(min_val, max_val * 1.5)
        nom_err_band.GetYaxis().SetRangeUser(min_val, max_val * 1.5)

        # Draw order: error band first, then histograms
        nom_err_band.Draw("E2")  # Error band
        nom_clone.Draw("HIST SAME")  # Nominal line

        if up_hist:
            up_clone.Draw("HIST SAME")
        if down_hist:
            down_clone.Draw("HIST SAME")

        # Redraw nominal on top for visibility
        nom_clone.Draw("HIST SAME")

        # Legend
        leg = ROOT.TLegend(0.55, 0.65, 0.92, 0.88)
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        leg.AddEntry(nom_err_band, "Nominal #pm stat.", "f")
        leg.AddEntry(nom_clone, "Nominal", "l")
        if up_hist:
            leg.AddEntry(up_clone, "Up", "l")
        if down_hist:
            leg.AddEntry(down_clone, "Down", "l")
        leg.Draw()

        # Add info about entries and integrals
        latex = ROOT.TLatex()
        latex.SetNDC()
        latex.SetTextSize(0.035)
        latex.SetTextColor(ROOT.kBlack)
        nom_int = nominal.Integral()
        nom_ent = nominal.GetEntries()
        latex.DrawLatex(0.15, 0.85, f"Nom: {nom_int:.1f} ({int(nom_ent)} ent)")
        if up_hist:
            latex.SetTextColor(ROOT.kRed)
            up_int = up_hist.Integral()
            up_ent = up_hist.GetEntries()
            latex.DrawLatex(0.15, 0.80, f"Up: {up_int:.1f} ({int(up_ent)} ent)")
        if down_hist:
            latex.SetTextColor(ROOT.kBlue)
            down_int = down_hist.Integral()
            down_ent = down_hist.GetEntries()
            latex.DrawLatex(0.15, 0.75, f"Down: {down_int:.1f} ({int(down_ent)} ent)")

        # Right panel: Variation percentages
        canvas.cd(2*i + 2)
        ROOT.gPad.SetGrid()
        ROOT.gPad.SetLeftMargin(0.12)
        ROOT.gPad.SetRightMargin(0.05)

        nbins = nominal.GetNbinsX()
        h_up = ROOT.TH1F(f"h_up_{process}_{i}", "", nbins,
                         nominal.GetXaxis().GetXmin(),
                         nominal.GetXaxis().GetXmax())
        h_down = ROOT.TH1F(f"h_down_{process}_{i}", "", nbins,
                           nominal.GetXaxis().GetXmin(),
                           nominal.GetXaxis().GetXmax())

        # Fill variation histograms
        if up_result and up_result['metrics'].get('variations'):
            for j, var in enumerate(up_result['metrics']['variations']):
                if var is not None:
                    h_up.SetBinContent(j + 1, var)

        if down_result and down_result['metrics'].get('variations'):
            for j, var in enumerate(down_result['metrics']['variations']):
                if var is not None:
                    h_down.SetBinContent(j + 1, var)

        h_up.SetLineColor(ROOT.kRed)
        h_up.SetLineWidth(2)
        h_up.SetFillColor(ROOT.kRed - 9)
        h_up.SetFillStyle(3004)

        h_down.SetLineColor(ROOT.kBlue)
        h_down.SetLineWidth(2)
        h_down.SetFillColor(ROOT.kBlue - 9)
        h_down.SetFillStyle(3005)

        h_up.SetTitle(f"{syst_name} variation [%]")
        h_up.GetYaxis().SetTitle("Variation [%]")
        h_up.GetXaxis().SetTitle("BDT bin")

        # Determine y-axis range
        all_vars = []
        if up_result and up_result['metrics'].get('variations'):
            all_vars.extend([v for v in up_result['metrics']['variations'] if v is not None])
        if down_result and down_result['metrics'].get('variations'):
            all_vars.extend([v for v in down_result['metrics']['variations'] if v is not None])

        if all_vars:
            max_var = max(abs(v) for v in all_vars)
        else:
            max_var = 10
        h_up.GetYaxis().SetRangeUser(-max_var * 1.4, max_var * 1.4)

        h_up.Draw("HIST")
        h_down.Draw("HIST SAME")

        # Zero line
        line = ROOT.TLine(h_up.GetXaxis().GetXmin(), 0,
                          h_up.GetXaxis().GetXmax(), 0)
        line.SetLineColor(ROOT.kBlack)
        line.SetLineStyle(2)
        line.SetLineWidth(2)
        line.Draw()

        # Add metrics text
        latex = ROOT.TLatex()
        latex.SetNDC()
        latex.SetTextSize(0.04)
        if up_result:
            latex.SetTextColor(ROOT.kRed)
            latex.DrawLatex(0.15, 0.85, f"Up: max={up_result['metrics']['max_var']:.1f}%")
        if down_result:
            latex.SetTextColor(ROOT.kBlue)
            latex.DrawLatex(0.15, 0.78, f"Down: max={down_result['metrics']['max_var']:.1f}%")

    # Save
    output_path = os.path.join(output_dir, f"top5_systematics_{process}.png")
    canvas.SaveAs(output_path)
    print(f"  Saved: {output_path}")

    return output_path


def parse_datacard_systematics(datacard_path):
    """Parse a Combine datacard to extract systematic names."""
    systematics = set()
    if not os.path.exists(datacard_path):
        return systematics

    with open(datacard_path, 'r') as f:
        for line in f:
            line = line.strip()
            # Shape systematics have format: syst_name shape ...
            # or lnN systematics: syst_name lnN ...
            parts = line.split()
            if len(parts) > 1 and parts[1] in ['shape', 'shapeN2', 'lnN']:
                systematics.add(parts[0])

    return systematics


def parse_datacard_processes(datacard_path):
    """Parse a Combine datacard to extract process names."""
    processes = []
    if not os.path.exists(datacard_path):
        return processes

    with open(datacard_path, 'r') as f:
        for line in f:
            line = line.strip()
            # Process line format: process   tttt   fakeTau   tt   ttbb ...
            if line.startswith('process') and not line[7:].strip().startswith('-') and not line[7:].strip()[0].isdigit():
                parts = line.split()
                if len(parts) > 1:
                    # Get unique process names (they repeat for each bin)
                    seen = set()
                    for p in parts[1:]:
                        if p not in seen:
                            processes.append(p)
                            seen.add(p)
                    break  # Only need the first process line

    return processes


def get_nominals_from_template(tfile, processes, channel="1tau1l", region="SR"):
    """Get nominal histograms from template file for given processes."""
    nominals = {}
    region_str = f"{channel}{region}"

    for process in processes:
        hist_name = f"{process}_{region_str}_BDT"
        hist = tfile.Get(hist_name)
        if hist:
            key = f"{process}_{region}"
            nominals[key] = hist.Clone(f"nominal_{process}_{region}")
            nominals[key].SetDirectory(0)

    return nominals


def plot_total_systematic(process, nominals, results, output_dir, channel="1tau1l",
                          datacard_systematics=None):
    """Plot nominal with total systematic uncertainty band for a process."""
    ROOT.gStyle.SetOptStat(0)

    region = "SR"
    nominal_key = f"{process}_{region}"
    nominal = nominals.get(nominal_key)

    if not nominal:
        print(f"  Warning: No nominal histogram for {process}")
        return None

    nbins = nominal.GetNbinsX()

    # Group results by systematic for this process
    from collections import defaultdict
    syst_variations = defaultdict(dict)  # systematic -> {Up: [vars], Down: [vars]}

    for r in results:
        if r['process'] != process or r['region'] != region:
            continue
        syst = r['systematic']
        direction = r['direction']

        # Filter by datacard systematics if provided
        if datacard_systematics and syst not in datacard_systematics:
            continue

        if direction in ['Up', 'Down']:
            syst_variations[syst][direction] = r['metrics'].get('variations', [])

    # Calculate total uncertainty per bin
    total_up = [0.0] * nbins
    total_down = [0.0] * nbins

    for syst, dirs in syst_variations.items():
        up_vars = dirs.get('Up', [])
        down_vars = dirs.get('Down', [])

        for i in range(nbins):
            up_val = up_vars[i] if i < len(up_vars) and up_vars[i] is not None else 0
            down_val = down_vars[i] if i < len(down_vars) and down_vars[i] is not None else 0

            # Add in quadrature (take max of up/down for each direction)
            if up_val > 0:
                total_up[i] = math.sqrt(total_up[i]**2 + up_val**2)
            else:
                total_down[i] = math.sqrt(total_down[i]**2 + up_val**2)

            if down_val < 0:
                total_down[i] = math.sqrt(total_down[i]**2 + down_val**2)
            else:
                total_up[i] = math.sqrt(total_up[i]**2 + down_val**2)

    # Create canvas
    canvas = ROOT.TCanvas(f"c_total_{process}", f"{process} - Total Systematic", 1200, 800)
    canvas.Divide(1, 2)

    # Top pad: nominal with error band
    canvas.cd(1)
    ROOT.gPad.SetPad(0, 0.35, 1, 1)
    ROOT.gPad.SetBottomMargin(0.02)
    ROOT.gPad.SetGrid()

    nom_clone = nominal.Clone(f"nom_total_{process}")

    # Create error band histogram
    h_band = nom_clone.Clone(f"h_band_{process}")
    for i in range(1, nbins + 1):
        nom_val = nominal.GetBinContent(i)
        stat_err = nominal.GetBinError(i)
        syst_up = nom_val * total_up[i-1] / 100 if total_up[i-1] else 0
        syst_down = nom_val * total_down[i-1] / 100 if total_down[i-1] else 0
        # Total error = sqrt(stat^2 + syst^2)
        total_err = math.sqrt(stat_err**2 + max(syst_up, syst_down)**2)
        h_band.SetBinError(i, total_err)

    h_band.SetFillColor(ROOT.kYellow - 9)
    h_band.SetFillStyle(1001)
    h_band.SetMarkerSize(0)
    h_band.SetTitle(f"{process} - Total Systematic Uncertainty;BDT bin;Events")

    # Create stat-only band
    h_stat_band = nom_clone.Clone(f"h_stat_band_{process}")
    h_stat_band.SetFillColor(ROOT.kGray)
    h_stat_band.SetFillStyle(3001)
    h_stat_band.SetMarkerSize(0)

    max_val = nom_clone.GetMaximum() * 1.5
    h_band.GetYaxis().SetRangeUser(0, max_val)
    h_band.Draw("E2")  # Stat+syst band (yellow)
    h_stat_band.Draw("E2 SAME")  # Stat-only band (gray) on top

    nom_clone.SetLineColor(ROOT.kBlack)
    nom_clone.SetLineWidth(2)
    nom_clone.SetMarkerStyle(20)
    nom_clone.SetMarkerSize(0.8)
    nom_clone.Draw("HIST SAME")

    # Legend
    leg = ROOT.TLegend(0.60, 0.65, 0.88, 0.88)
    leg.SetBorderSize(0)
    leg.SetFillStyle(0)
    leg.AddEntry(nom_clone, "Nominal", "l")
    leg.AddEntry(h_stat_band, "Stat only", "f")
    leg.AddEntry(h_band, "Stat #oplus Syst", "f")
    leg.Draw()

    # Add text with number of systematics
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.04)
    n_syst = len(syst_variations)
    latex.DrawLatex(0.15, 0.85, f"N systematics: {n_syst}")

    # Bottom pad: uncertainty percentage
    canvas.cd(2)
    ROOT.gPad.SetPad(0, 0, 1, 0.35)
    ROOT.gPad.SetTopMargin(0.02)
    ROOT.gPad.SetBottomMargin(0.25)
    ROOT.gPad.SetGrid()

    h_up_pct = ROOT.TH1F(f"h_up_pct_{process}", "", nbins,
                          nominal.GetXaxis().GetXmin(),
                          nominal.GetXaxis().GetXmax())
    h_down_pct = ROOT.TH1F(f"h_down_pct_{process}", "", nbins,
                            nominal.GetXaxis().GetXmin(),
                            nominal.GetXaxis().GetXmax())

    for i in range(nbins):
        h_up_pct.SetBinContent(i + 1, total_up[i])
        h_down_pct.SetBinContent(i + 1, -total_down[i])

    h_up_pct.SetLineColor(ROOT.kRed)
    h_up_pct.SetFillColor(ROOT.kRed - 9)
    h_up_pct.SetFillStyle(3004)
    h_up_pct.SetLineWidth(2)

    h_down_pct.SetLineColor(ROOT.kBlue)
    h_down_pct.SetFillColor(ROOT.kBlue - 9)
    h_down_pct.SetFillStyle(3005)
    h_down_pct.SetLineWidth(2)

    max_pct = max(max(total_up), max(total_down)) * 1.3 if total_up or total_down else 50
    h_up_pct.GetYaxis().SetRangeUser(-max_pct, max_pct)
    h_up_pct.SetTitle("")
    h_up_pct.GetYaxis().SetTitle("Total Syst [%]")
    h_up_pct.GetYaxis().SetTitleSize(0.08)
    h_up_pct.GetYaxis().SetTitleOffset(0.5)
    h_up_pct.GetYaxis().SetLabelSize(0.07)
    h_up_pct.GetXaxis().SetTitle("BDT bin")
    h_up_pct.GetXaxis().SetTitleSize(0.1)
    h_up_pct.GetXaxis().SetLabelSize(0.08)

    h_up_pct.Draw("HIST")
    h_down_pct.Draw("HIST SAME")

    # Zero line
    line = ROOT.TLine(h_up_pct.GetXaxis().GetXmin(), 0,
                       h_up_pct.GetXaxis().GetXmax(), 0)
    line.SetLineColor(ROOT.kBlack)
    line.SetLineStyle(2)
    line.SetLineWidth(2)
    line.Draw()

    # Save
    output_path = os.path.join(output_dir, f"total_systematic_{process}.png")
    canvas.SaveAs(output_path)
    print(f"  Saved: {output_path}")

    return output_path


def print_report(results, output_file=None):
    """Print a formatted report of problematic systematics."""
    lines = []
    lines.append("=" * 100)
    lines.append("SYSTEMATIC FLUCTUATION REPORT")
    lines.append("=" * 100)
    lines.append("")
    lines.append(f"Found {len(results)} systematic variations exceeding threshold")
    lines.append("")
    lines.append(f"{'Rank':<5} {'Process':<15} {'Systematic':<45} {'Dir':<5} {'Score':<8} {'Max%':<8} {'RMS%':<8}")
    lines.append("-" * 100)

    for i, r in enumerate(results[:50]):  # Top 50
        lines.append(f"{i+1:<5} {r['process']:<15} {r['systematic']:<45} {r['direction']:<5} "
                    f"{r['score']:<8.1f} {r['metrics']['max_var']:<8.1f} {r['metrics']['rms']:<8.1f}")

    lines.append("")
    lines.append("=" * 100)
    lines.append("DETAILED BIN-BY-BIN VARIATIONS (Top 20)")
    lines.append("=" * 100)

    for i, r in enumerate(results[:20]):
        lines.append("")
        lines.append(f"[{i+1}] {r['process']} | {r['systematic']}{r['direction']}")
        lines.append(f"    Score: {r['score']:.1f}, Max: {r['metrics']['max_var']:.1f}%, "
                    f"RMS: {r['metrics']['rms']:.1f}%, Max Δ: {r['metrics']['max_deriv']:.1f}%")
        vars_str = ", ".join(r['metrics'].get('display_vars', []))
        lines.append(f"    Bins: [{vars_str}]")

    report = "\n".join(lines)
    print(report)

    if output_file:
        with open(output_file, 'w') as f:
            f.write(report)
        print(f"\nReport saved to: {output_file}")


def group_results_by_systematic(results):
    """Group results by (process, region, systematic) to pair Up and Down."""
    grouped = {}
    for r in results:
        key = (r['process'], r['region'], r['systematic'])
        if key not in grouped:
            grouped[key] = {'Up': None, 'Down': None}
        grouped[key][r['direction']] = r
    return grouped


def main():
    parser = argparse.ArgumentParser(description="Check systematic fluctuations in templates")
    parser.add_argument("template", help="Path to template ROOT file")
    parser.add_argument("--threshold", type=float, default=10.0,
                        help="Minimum fluctuation score to report (default: 10%%)")
    parser.add_argument("--output-dir", default=None,
                        help="Output directory for plots (default: same dir as template)")
    parser.add_argument("--channel", default="1tau1l",
                        help="Channel name (default: 1tau1l)")
    parser.add_argument("--max-plots", type=int, default=30,
                        help="Maximum number of systematics to plot (default: 30)")
    parser.add_argument("--no-plots", action="store_true",
                        help="Skip plot generation, only print report")
    parser.add_argument("--top-per-process", type=int, default=0,
                        help="Plot top N systematics per process (default: 0, disabled)")
    parser.add_argument("--compare-smoothed", default=None,
                        help="Path to smoothed template for comparison")
    parser.add_argument("--datacard", default=None,
                        help="Path to datacard to filter systematics for total plot")
    parser.add_argument("--total-systematic", action="store_true",
                        help="Generate total systematic uncertainty plot per process")

    args = parser.parse_args()

    if not os.path.exists(args.template):
        print(f"Error: Template file not found: {args.template}")
        sys.exit(1)

    # Set output directory to template directory if not specified
    if args.output_dir is None:
        template_dir = os.path.dirname(os.path.abspath(args.template))
        args.output_dir = os.path.join(template_dir, "systematic_fluctuations")

    print(f"Analyzing: {args.template}")
    print(f"Channel: {args.channel}")
    print(f"Threshold: {args.threshold}%")
    print(f"Output: {args.output_dir}")
    print()

    tfile = ROOT.TFile(args.template)

    results = analyze_template(tfile, channel=args.channel, threshold=args.threshold)

    # Print report
    os.makedirs(args.output_dir, exist_ok=True)
    report_file = os.path.join(args.output_dir, "fluctuation_report.txt")
    print_report(results, report_file)

    # Generate plots with Up and Down together
    if not args.no_plots and results:
        # Group by systematic to plot Up/Down together
        grouped = group_results_by_systematic(results)

        # Sort by max score of either direction
        sorted_keys = sorted(grouped.keys(),
                            key=lambda k: max(
                                grouped[k]['Up']['score'] if grouped[k]['Up'] else 0,
                                grouped[k]['Down']['score'] if grouped[k]['Down'] else 0
                            ), reverse=True)

        print(f"\nGenerating plots for top {min(len(sorted_keys), args.max_plots)} systematics...")

        for i, key in enumerate(sorted_keys[:args.max_plots]):
            process, region, systematic = key
            up_result = grouped[key]['Up']
            down_result = grouped[key]['Down']

            # Get nominal and varied histograms
            nominal = up_result['nominal'] if up_result else down_result['nominal']
            varied_up = up_result['varied'] if up_result else None
            varied_down = down_result['varied'] if down_result else None
            metrics_up = up_result['metrics'] if up_result else None
            metrics_down = down_result['metrics'] if down_result else None
            variations_up = metrics_up['variations'] if metrics_up else None
            variations_down = metrics_down['variations'] if metrics_down else None

            # Plot shapes with Up/Down
            plot_systematic_updown(process, region, systematic, nominal,
                                  varied_up, varied_down,
                                  metrics_up, metrics_down,
                                  args.output_dir, i)

            # Plot variation percentages
            plot_variation_updown(process, region, systematic,
                                 variations_up, variations_down,
                                 metrics_up, metrics_down, nominal,
                                 args.output_dir, i)

        print(f"Plots saved to: {args.output_dir}/")

    # Generate top N systematics per process plots
    if args.top_per_process > 0 and results:
        print(f"\n=== Generating top {args.top_per_process} systematics per process ===")

        # Parse datacard for processes if provided
        datacard_processes = None
        if args.datacard:
            datacard_processes = parse_datacard_processes(args.datacard)
            print(f"Using {len(datacard_processes)} processes from datacard: {datacard_processes}")

        # Determine which processes to plot
        if datacard_processes:
            processes_to_plot = datacard_processes
            # Get nominals directly from template for all datacard processes
            nominals = get_nominals_from_template(tfile, processes_to_plot, args.channel)
        else:
            # Fall back to processes from results
            processes_to_plot = None
            # Build nominals dictionary from results (they already have the histogram)
            nominals = {}
            for r in results:
                key = f"{r['process']}_{r['region']}"
                if key not in nominals and r.get('nominal'):
                    nominals[key] = r['nominal']

        # Get top systematics per process
        top_per_process = get_top_systematics_per_process(results, n_top=args.top_per_process)

        # Determine processes to iterate
        if processes_to_plot:
            for process in processes_to_plot:
                top_systs = top_per_process.get(process, [])
                print(f"\nProcess: {process}")
                if top_systs:
                    for syst_name, score, _ in top_systs:
                        print(f"  - {syst_name}: score={score:.1f}")
                    plot_top_systematics_for_process(process, top_systs, nominals, tfile,
                                                      args.output_dir, args.channel)
                else:
                    print(f"  (no large fluctuations above threshold)")
        else:
            for process in sorted(top_per_process.keys()):
                top_systs = top_per_process[process]
                if top_systs:
                    print(f"\nProcess: {process}")
                    for syst_name, score, _ in top_systs:
                        print(f"  - {syst_name}: score={score:.1f}")
                    plot_top_systematics_for_process(process, top_systs, nominals, tfile,
                                                      args.output_dir, args.channel)

    # Generate total systematic plots
    if args.total_systematic and results:
        print(f"\n=== Generating total systematic uncertainty plots ===")

        # Parse datacard for systematics and processes if provided
        datacard_systematics = None
        datacard_processes = None
        if args.datacard:
            datacard_systematics = parse_datacard_systematics(args.datacard)
            datacard_processes = parse_datacard_processes(args.datacard)
            print(f"Filtering to {len(datacard_systematics)} systematics from datacard")
            print(f"Using {len(datacard_processes)} processes from datacard: {datacard_processes}")

        # Determine which processes to plot
        if datacard_processes:
            processes = datacard_processes
            # Get nominals directly from template for all datacard processes
            nominals = get_nominals_from_template(tfile, processes, args.channel)
        else:
            # Fall back to processes from results
            processes = sorted(set(r['process'] for r in results))
            # Build nominals dictionary from results
            nominals = {}
            for r in results:
                key = f"{r['process']}_{r['region']}"
                if key not in nominals and r.get('nominal'):
                    nominals[key] = r['nominal']

        for process in processes:
            plot_total_systematic(process, nominals, results, args.output_dir,
                                  args.channel, datacard_systematics)

    # Compare with smoothed template if provided
    if args.compare_smoothed and os.path.exists(args.compare_smoothed):
        print(f"\n=== Comparing with smoothed template ===")
        print(f"Smoothed: {args.compare_smoothed}")

        tfile_smoothed = ROOT.TFile(args.compare_smoothed)
        results_smoothed = analyze_template(tfile_smoothed, channel=args.channel, threshold=args.threshold)

        # Print comparison report
        print(f"\nUnsmoothed: {len(results)} variations > {args.threshold}%")
        print(f"Smoothed: {len(results_smoothed)} variations > {args.threshold}%")

        # Generate plots for smoothed template
        smoothed_output_dir = os.path.join(args.output_dir, "smoothed")
        os.makedirs(smoothed_output_dir, exist_ok=True)

        # Parse datacard for processes and systematics if provided
        datacard_processes = None
        datacard_systematics = None
        if args.datacard:
            datacard_processes = parse_datacard_processes(args.datacard)
            datacard_systematics = parse_datacard_systematics(args.datacard)
            print(f"Using {len(datacard_processes)} processes from datacard")

        if args.top_per_process > 0:
            # Determine which processes to plot
            if datacard_processes:
                processes_to_plot = datacard_processes
                nominals_smoothed = get_nominals_from_template(tfile_smoothed, processes_to_plot, args.channel)
            else:
                processes_to_plot = None
                # Build nominals dictionary from results
                nominals_smoothed = {}
                for r in results_smoothed:
                    key = f"{r['process']}_{r['region']}"
                    if key not in nominals_smoothed and r.get('nominal'):
                        nominals_smoothed[key] = r['nominal']

            top_per_process_smoothed = get_top_systematics_per_process(results_smoothed, n_top=args.top_per_process)

            if processes_to_plot:
                for process in processes_to_plot:
                    top_systs = top_per_process_smoothed.get(process, [])
                    print(f"\n[Smoothed] Process: {process}")
                    if top_systs:
                        for syst_name, score, _ in top_systs:
                            print(f"  - {syst_name}: score={score:.1f}")
                        plot_top_systematics_for_process(process, top_systs, nominals_smoothed, tfile_smoothed,
                                                          smoothed_output_dir, args.channel)
                    else:
                        print(f"  (no large fluctuations above threshold)")
            else:
                for process in sorted(top_per_process_smoothed.keys()):
                    top_systs = top_per_process_smoothed[process]
                    if top_systs:
                        print(f"\n[Smoothed] Process: {process}")
                        for syst_name, score, _ in top_systs:
                            print(f"  - {syst_name}: score={score:.1f}")
                        plot_top_systematics_for_process(process, top_systs, nominals_smoothed, tfile_smoothed,
                                                          smoothed_output_dir, args.channel)

        # Also generate total systematic plots for smoothed
        if args.total_systematic:
            print(f"\n=== Generating total systematic plots for smoothed ===")
            if datacard_processes:
                processes_smoothed = datacard_processes
                nominals_smoothed = get_nominals_from_template(tfile_smoothed, processes_smoothed, args.channel)
            else:
                processes_smoothed = sorted(set(r['process'] for r in results_smoothed))
                nominals_smoothed = {}
                for r in results_smoothed:
                    key = f"{r['process']}_{r['region']}"
                    if key not in nominals_smoothed and r.get('nominal'):
                        nominals_smoothed[key] = r['nominal']

            for process in processes_smoothed:
                plot_total_systematic(process, nominals_smoothed, results_smoothed,
                                      smoothed_output_dir, args.channel, datacard_systematics)

        tfile_smoothed.Close()

    tfile.Close()

    print(f"\nDone! Found {len(results)} problematic variations ({len(group_results_by_systematic(results))} systematics).")


if __name__ == "__main__":
    main()
