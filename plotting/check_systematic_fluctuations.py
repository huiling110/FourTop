#!/usr/bin/env python3
"""
Check Systematic Fluctuations in Template Files

Identifies systematic variations with large bin-by-bin fluctuations that may indicate
issues with smoothing or low statistics.

Usage:
    python3 plotting/check_systematic_fluctuations.py TEMPLATE.root [--threshold 0.1] [--output-dir plots/] [--channel 1tau1l]

Example:
    python3 plotting/check_systematic_fluctuations.py /publicfs/.../templatesForCombine1tau1l_new_notMCFTau_unblind_smoothed.root --threshold 0.1
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
    if sr_marker in name:
        region = "SR"
        parts = name.split(f"_{sr_marker}_")
    elif cr_marker in name:
        region = "CR"
        parts = name.split(f"_{cr_marker}")
        if len(parts) > 1:
            parts[1] = parts[1].lstrip("_").lstrip("12_")  # Handle CR12
    else:
        return None, None, None, None

    if len(parts) < 1:
        return None, None, None, None

    process = parts[0]

    if len(parts) == 1 or parts[1] == "":
        # Nominal histogram
        return process, region, None, None

    systematic = parts[1]

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

    output_path = os.path.join(output_dir, f"fluctuation_{index:03d}_{safe_name}.pdf")
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

    output_path = os.path.join(output_dir, f"systematic_{index:03d}_{safe_name}.pdf")
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

    output_path = os.path.join(output_dir, f"variation_{index:03d}_{safe_name}.pdf")
    canvas.SaveAs(output_path)

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

    tfile.Close()

    print(f"\nDone! Found {len(results)} problematic variations ({len(group_results_by_systematic(results))} systematics).")


if __name__ == "__main__":
    main()
