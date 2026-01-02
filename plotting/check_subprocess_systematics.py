#!/usr/bin/env python3
"""
Check if systematic fluctuations in tt come from statistical fluctuations in WH subprocesses.
Plots:
1. Combined tt nominal with statistical uncertainty
2. Each subprocess with statistical uncertainty
3. Top 5 systematic variations for all subprocesses
"""

import ROOT
import os
import argparse
import numpy as np
from collections import defaultdict

ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

# Top 5 systematics for tt from check_systematic_fluctuations.py
TOP5_SYSTEMATICS_TT = [
    "CMS_scale_t_DeepTau2017v2p1_DM0_genTau_2018",
    "CMS_scale_j_TimePtEta_2018",
    "CMS_scale_met_unclustered_energy_2018",
    "CMS_res_j_2018",
    "CMS_scale_j_RelativeFSR",
]

# Subprocess mapping for tt process
TT_SUBPROCESSES = ["ttbar_0l", "ttbar_1l", "ttbar_2l"]

def get_wh_base_path(config_path, era):
    """Get the base WH output path from config."""
    import yaml
    with open(config_path) as f:
        config = yaml.safe_load(f)

    stage2_base = config.get('stage2_output_base', '')
    wh_version = config.get('wh_version', 'v0BDT1tau1l_XGB080testNew')
    stage1_version = config.get('os_version', 'v95XGB080testOS7')

    # Construct path
    base = f"/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/{era}/v1baselineHadro_{stage1_version}/mc/variableHists_{wh_version}"
    return base


def get_systematic_wh_paths(base_path, systematic, era):
    """Get WH paths for systematic variations."""
    # Directory structure:
    # Nominal: v1baselineHadro_v95XGB080testOS7/mc/variableHists_*/
    # JER: v1baselineHadro_v95XGB080testOS7_JERUp/mc/variableHists_*/
    # MET: v1baselineHadro_v95XGB080testOS7_METUp/mc/variableHists_*/
    # EleScale: v1baselineHadro_v95XGB080testOS7_EleScaleUp/mc/variableHists_*/
    # JES: v1baselineHadro_JESup_{source}_AK4PFchs_v95XGB080testOS7_JESPt22/mc/variableHists_*/

    if "scale_j_" in systematic:
        # JES systematic - separate directory
        # Format: v1baselineHadro_JESup_{source}_AK4PFchs_{stage1}_JESPt22
        syst_base = systematic.replace("CMS_scale_j_", "")
        # Remove era suffix if present
        for suffix in ["_2016preVFP", "_2016postVFP", "_2017", "_2018"]:
            syst_base = syst_base.replace(suffix, "")

        # base_path: .../v1baselineHadro_v95XGB080testOS7/mc/variableHists_xxx/
        # Split to get stage1 version
        import re
        match = re.search(r'v1baselineHadro_([^/]+)/mc/', base_path)
        if match:
            stage1 = match.group(1)  # e.g., v95XGB080testOS7
            up_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_JESup_{syst_base}_AK4PFchs_{stage1}_JESPt22/mc/")
            down_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_JESDown_{syst_base}_AK4PFchs_{stage1}_JESPt22/mc/")
        else:
            up_dir = base_path
            down_dir = base_path
        return {"Up": up_dir, "Down": down_dir, "type": "JES"}

    elif "res_j_" in systematic:
        # JER systematic - separate directory
        # Format: v1baselineHadro_{stage1}_JERUp
        import re
        match = re.search(r'v1baselineHadro_([^/]+)/mc/', base_path)
        if match:
            stage1 = match.group(1)
            up_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_{stage1}_JERUp/mc/")
            down_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_{stage1}_JERDown/mc/")
        else:
            up_dir = base_path
            down_dir = base_path
        return {"Up": up_dir, "Down": down_dir, "type": "JER"}

    elif "scale_met_" in systematic:
        # MET systematic - separate directory
        import re
        match = re.search(r'v1baselineHadro_([^/]+)/mc/', base_path)
        if match:
            stage1 = match.group(1)
            up_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_{stage1}_METUp/mc/")
            down_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_{stage1}_METDown/mc/")
        else:
            up_dir = base_path
            down_dir = base_path
        return {"Up": up_dir, "Down": down_dir, "type": "MET"}

    elif "scale_t_" in systematic:
        # TES systematic - in nominal WH file as weight variation
        return {"Up": base_path, "Down": base_path, "type": "weight"}

    elif "scale_e_" in systematic:
        # Electron scale - separate directory
        import re
        match = re.search(r'v1baselineHadro_([^/]+)/mc/', base_path)
        if match:
            stage1 = match.group(1)
            up_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_{stage1}_EleScaleUp/mc/")
            down_dir = base_path.replace(f"v1baselineHadro_{stage1}/mc/", f"v1baselineHadro_{stage1}_EleScaleDown/mc/")
        else:
            up_dir = base_path
            down_dir = base_path
        return {"Up": up_dir, "Down": down_dir, "type": "EleScale"}

    else:
        # Weight-based systematic in nominal file
        return {"Up": base_path, "Down": base_path, "type": "weight"}


def get_hist_from_wh(wh_dir, subprocess, region, systematic=None, direction=None):
    """Get histogram from WH file."""
    wh_file = os.path.join(wh_dir, f"{subprocess}.root")
    if not os.path.exists(wh_file):
        return None

    tfile = ROOT.TFile(wh_file)

    # Build histogram name
    if systematic and direction:
        # Check if it's a weight-based systematic (in nominal file)
        hist_name = f"{subprocess}_NotMCFT_{region}_{systematic}{direction}_BDT"
        hist = tfile.Get(hist_name)
        if not hist:
            # Try without NotMCFT suffix
            hist_name = f"{subprocess}_{region}_{systematic}{direction}_BDT"
            hist = tfile.Get(hist_name)
    else:
        # Nominal
        hist_name = f"{subprocess}_NotMCFT_{region}_BDT"
        hist = tfile.Get(hist_name)
        if not hist:
            hist_name = f"{subprocess}_{region}_BDT"
            hist = tfile.Get(hist_name)

    if hist:
        hist_clone = hist.Clone()
        hist_clone.SetDirectory(0)
        tfile.Close()
        return hist_clone

    tfile.Close()
    return None


def plot_subprocess_analysis(base_path, era, output_dir, channel="1tau1l"):
    """Create plots analyzing subprocess contributions to tt systematics."""

    region = f"{channel}SR"
    os.makedirs(output_dir, exist_ok=True)

    # Colors for subprocesses
    colors = {
        "ttbar_0l": ROOT.kRed,
        "ttbar_1l": ROOT.kBlue,
        "ttbar_2l": ROOT.kGreen+2,
    }

    # Get nominal histograms for each subprocess
    print(f"\n=== Loading nominal histograms from {base_path} ===")
    subprocess_nominals = {}
    for subprocess in TT_SUBPROCESSES:
        hist = get_hist_from_wh(base_path, subprocess, region)
        if hist:
            print(f"  {subprocess}: {hist.Integral():.2f} events, {int(hist.GetEntries())} entries")
            subprocess_nominals[subprocess] = hist
        else:
            print(f"  {subprocess}: NOT FOUND")

    if not subprocess_nominals:
        print("ERROR: No subprocess histograms found!")
        return

    # Create combined tt nominal
    tt_combined = None
    for subprocess, hist in subprocess_nominals.items():
        if tt_combined is None:
            tt_combined = hist.Clone("tt_combined_nominal")
        else:
            tt_combined.Add(hist)

    print(f"\n  Combined tt: {tt_combined.Integral():.2f} events")

    # ===== Plot 1: Subprocess contributions to tt nominal =====
    print(f"\n=== Creating subprocess contribution plot ===")

    canvas1 = ROOT.TCanvas("c1", "Subprocess Contributions", 1200, 800)
    canvas1.Divide(2, 1)

    # Left: Absolute yields
    canvas1.cd(1)
    ROOT.gPad.SetGrid()
    ROOT.gPad.SetLeftMargin(0.12)

    # Create stack
    stack = ROOT.THStack("hs", "tt Subprocess Contributions;BDT bin;Events")
    legend1 = ROOT.TLegend(0.65, 0.7, 0.88, 0.88)
    legend1.SetBorderSize(0)

    for subprocess in TT_SUBPROCESSES:
        if subprocess in subprocess_nominals:
            hist = subprocess_nominals[subprocess].Clone()
            hist.SetFillColor(colors[subprocess])
            hist.SetLineColor(colors[subprocess])
            stack.Add(hist)
            legend1.AddEntry(hist, f"{subprocess}: {hist.Integral():.1f}", "f")

    stack.Draw("HIST")
    stack.GetYaxis().SetTitle("Events")

    # Draw combined with error bars
    tt_combined_err = tt_combined.Clone("tt_err")
    tt_combined_err.SetFillStyle(3004)
    tt_combined_err.SetFillColor(ROOT.kBlack)
    tt_combined_err.Draw("E2 SAME")
    legend1.AddEntry(tt_combined_err, "Combined #pm stat", "f")

    legend1.Draw()

    # Right: Statistical uncertainties per bin
    canvas1.cd(2)
    ROOT.gPad.SetGrid()
    ROOT.gPad.SetLeftMargin(0.12)

    nbins = tt_combined.GetNbinsX()
    h_stat_pct = ROOT.TH1F("h_stat_pct", "Statistical Uncertainty;BDT bin;Stat. Error [%]",
                           nbins, tt_combined.GetXaxis().GetXmin(), tt_combined.GetXaxis().GetXmax())

    for i in range(1, nbins + 1):
        content = tt_combined.GetBinContent(i)
        error = tt_combined.GetBinError(i)
        if content > 0:
            h_stat_pct.SetBinContent(i, error / content * 100)

    h_stat_pct.SetLineColor(ROOT.kBlack)
    h_stat_pct.SetLineWidth(2)
    h_stat_pct.SetFillColor(ROOT.kGray)
    h_stat_pct.Draw("HIST")

    # Add text with per-bin info
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.03)
    for i in range(1, nbins + 1):
        content = tt_combined.GetBinContent(i)
        error = tt_combined.GetBinError(i)
        pct = error / content * 100 if content > 0 else 0
        latex.DrawLatex(0.15, 0.85 - 0.04 * (i - 1), f"Bin {i}: {content:.2f} #pm {error:.2f} ({pct:.1f}%)")

    canvas1.SaveAs(os.path.join(output_dir, "tt_subprocess_contributions.png"))
    print(f"  Saved: {output_dir}/tt_subprocess_contributions.png")

    # ===== Plot 2: Top 5 systematics for each subprocess =====
    print(f"\n=== Creating systematic comparison plots ===")

    for syst in TOP5_SYSTEMATICS_TT:
        print(f"\n  Processing: {syst}")

        # Get systematic paths
        syst_paths = get_systematic_wh_paths(base_path, syst, era)
        syst_type = syst_paths["type"]

        # Create canvas: 3 columns (one per subprocess) x 2 rows (abs + variation%)
        canvas2 = ROOT.TCanvas(f"c_{syst}", syst, 1800, 800)
        canvas2.Divide(3, 2)

        for idx, subprocess in enumerate(TT_SUBPROCESSES):
            # Get nominal
            nom_hist = subprocess_nominals.get(subprocess)
            if not nom_hist:
                continue

            # Get systematic variations
            if syst_type in ["JES", "JER", "MET", "EleScale"]:
                # Systematic from separate directory
                up_hist = get_hist_from_wh(syst_paths["Up"], subprocess, region)
                down_hist = get_hist_from_wh(syst_paths["Down"], subprocess, region)
            else:
                # Weight-based systematic in nominal file
                up_hist = get_hist_from_wh(base_path, subprocess, region, syst, "Up")
                down_hist = get_hist_from_wh(base_path, subprocess, region, syst, "Down")

            # Top row: Absolute histograms
            canvas2.cd(idx + 1)
            ROOT.gPad.SetGrid()
            ROOT.gPad.SetLeftMargin(0.12)

            nom_clone = nom_hist.Clone()
            nom_clone.SetLineColor(ROOT.kBlack)
            nom_clone.SetLineWidth(2)
            nom_clone.SetTitle(f"{subprocess} | {syst}")

            # Draw nominal with stat error band
            nom_err = nom_clone.Clone()
            nom_err.SetFillStyle(3001)
            nom_err.SetFillColor(ROOT.kGray)
            nom_err.Draw("E2")
            nom_clone.Draw("HIST SAME")

            if up_hist:
                up_hist.SetLineColor(ROOT.kRed)
                up_hist.SetLineWidth(2)
                up_hist.SetLineStyle(2)
                up_hist.Draw("HIST SAME")

            if down_hist:
                down_hist.SetLineColor(ROOT.kBlue)
                down_hist.SetLineWidth(2)
                down_hist.SetLineStyle(2)
                down_hist.Draw("HIST SAME")

            # Legend
            leg = ROOT.TLegend(0.55, 0.7, 0.88, 0.88)
            leg.SetBorderSize(0)
            leg.SetTextSize(0.03)
            nom_int = nom_clone.Integral()
            nom_ent = int(nom_clone.GetEntries())
            leg.AddEntry(nom_clone, f"Nom: {nom_int:.1f} ({nom_ent} ent)", "l")
            if up_hist:
                up_int = up_hist.Integral()
                up_ent = int(up_hist.GetEntries())
                leg.AddEntry(up_hist, f"Up: {up_int:.1f} ({up_ent} ent)", "l")
            if down_hist:
                down_int = down_hist.Integral()
                down_ent = int(down_hist.GetEntries())
                leg.AddEntry(down_hist, f"Down: {down_int:.1f} ({down_ent} ent)", "l")
            leg.Draw()

            # Bottom row: Variation percentages
            canvas2.cd(idx + 4)
            ROOT.gPad.SetGrid()
            ROOT.gPad.SetLeftMargin(0.12)

            h_var_up = ROOT.TH1F(f"h_var_up_{subprocess}_{syst}", f"{subprocess} | {syst} variation [%];BDT bin;Variation [%]",
                                 nbins, nom_hist.GetXaxis().GetXmin(), nom_hist.GetXaxis().GetXmax())
            h_var_down = ROOT.TH1F(f"h_var_down_{subprocess}_{syst}", "",
                                   nbins, nom_hist.GetXaxis().GetXmin(), nom_hist.GetXaxis().GetXmax())
            h_stat_band = ROOT.TH1F(f"h_stat_{subprocess}_{syst}", "",
                                    nbins, nom_hist.GetXaxis().GetXmin(), nom_hist.GetXaxis().GetXmax())

            for i in range(1, nbins + 1):
                nom_val = nom_hist.GetBinContent(i)
                nom_err_val = nom_hist.GetBinError(i)

                if nom_val > 0:
                    stat_pct = nom_err_val / nom_val * 100
                    h_stat_band.SetBinContent(i, 0)
                    h_stat_band.SetBinError(i, stat_pct)

                    if up_hist:
                        up_val = up_hist.GetBinContent(i)
                        h_var_up.SetBinContent(i, (up_val - nom_val) / nom_val * 100)
                    if down_hist:
                        down_val = down_hist.GetBinContent(i)
                        h_var_down.SetBinContent(i, (down_val - nom_val) / nom_val * 100)

            # Draw stat band
            h_stat_band.SetFillStyle(3001)
            h_stat_band.SetFillColor(ROOT.kGray)

            # Get y-axis range
            all_vals = []
            for i in range(1, nbins + 1):
                all_vals.append(h_var_up.GetBinContent(i))
                all_vals.append(h_var_down.GetBinContent(i))
                all_vals.append(h_stat_band.GetBinError(i))
                all_vals.append(-h_stat_band.GetBinError(i))

            non_zero_vals = [abs(v) for v in all_vals if v != 0]
            max_val = max(non_zero_vals) if non_zero_vals else 50
            h_var_up.GetYaxis().SetRangeUser(-max_val * 1.5, max_val * 1.5)

            h_var_up.SetLineColor(ROOT.kRed)
            h_var_up.SetLineWidth(2)
            h_var_up.SetFillColor(ROOT.kRed - 9)
            h_var_up.SetFillStyle(3004)

            h_var_down.SetLineColor(ROOT.kBlue)
            h_var_down.SetLineWidth(2)
            h_var_down.SetFillColor(ROOT.kBlue - 9)
            h_var_down.SetFillStyle(3005)

            h_var_up.Draw("HIST")
            h_stat_band.Draw("E2 SAME")
            h_var_down.Draw("HIST SAME")

            # Zero line
            line = ROOT.TLine(h_var_up.GetXaxis().GetXmin(), 0, h_var_up.GetXaxis().GetXmax(), 0)
            line.SetLineColor(ROOT.kBlack)
            line.SetLineStyle(2)
            line.Draw()

            # Text: max variations
            latex2 = ROOT.TLatex()
            latex2.SetNDC()
            latex2.SetTextSize(0.035)
            latex2.SetTextColor(ROOT.kRed)
            max_up = max(abs(h_var_up.GetBinContent(i)) for i in range(1, nbins + 1))
            latex2.DrawLatex(0.15, 0.85, f"Up: max={max_up:.1f}%")
            latex2.SetTextColor(ROOT.kBlue)
            max_down = max(abs(h_var_down.GetBinContent(i)) for i in range(1, nbins + 1))
            latex2.DrawLatex(0.15, 0.80, f"Down: max={max_down:.1f}%")
            latex2.SetTextColor(ROOT.kGray+2)
            max_stat = max(h_stat_band.GetBinError(i) for i in range(1, nbins + 1))
            latex2.DrawLatex(0.15, 0.75, f"Stat: max={max_stat:.1f}%")

        syst_short = syst.replace("CMS_", "").replace("_2018", "")
        canvas2.SaveAs(os.path.join(output_dir, f"tt_subprocess_{syst_short}.png"))
        print(f"    Saved: tt_subprocess_{syst_short}.png")

    # ===== Plot 3: Summary - all systematics per bin =====
    print(f"\n=== Creating summary plot ===")

    canvas3 = ROOT.TCanvas("c3", "Summary", 1400, 900)
    canvas3.Divide(4, 2)

    for bin_idx in range(1, min(8, nbins + 1)):
        canvas3.cd(bin_idx)
        ROOT.gPad.SetGrid()
        ROOT.gPad.SetLeftMargin(0.15)
        ROOT.gPad.SetBottomMargin(0.25)

        # Create bar chart for this bin
        n_syst = len(TOP5_SYSTEMATICS_TT)
        h_summary = ROOT.TH1F(f"h_summary_bin{bin_idx}", f"Bin {bin_idx}: Systematic Variations;Systematic;Variation [%]",
                              n_syst * 2, 0, n_syst * 2)

        for syst_idx, syst in enumerate(TOP5_SYSTEMATICS_TT):
            syst_paths = get_systematic_wh_paths(base_path, syst, era)
            syst_type = syst_paths["type"]

            # Sum variations from all subprocesses
            nom_sum = sum(subprocess_nominals[sp].GetBinContent(bin_idx) for sp in TT_SUBPROCESSES if sp in subprocess_nominals)

            up_sum = 0
            down_sum = 0
            for subprocess in TT_SUBPROCESSES:
                if subprocess not in subprocess_nominals:
                    continue

                if syst_type in ["JES", "JER", "MET", "EleScale"]:
                    up_hist = get_hist_from_wh(syst_paths["Up"], subprocess, region)
                    down_hist = get_hist_from_wh(syst_paths["Down"], subprocess, region)
                else:
                    up_hist = get_hist_from_wh(base_path, subprocess, region, syst, "Up")
                    down_hist = get_hist_from_wh(base_path, subprocess, region, syst, "Down")

                if up_hist:
                    up_sum += up_hist.GetBinContent(bin_idx)
                if down_hist:
                    down_sum += down_hist.GetBinContent(bin_idx)

            if nom_sum > 0:
                up_var = (up_sum - nom_sum) / nom_sum * 100
                down_var = (down_sum - nom_sum) / nom_sum * 100
            else:
                up_var = 0
                down_var = 0

            h_summary.SetBinContent(syst_idx * 2 + 1, up_var)
            h_summary.SetBinContent(syst_idx * 2 + 2, down_var)

            # Labels
            syst_short = syst.replace("CMS_", "").replace("_2018", "").replace("DeepTau2017v2p1_DM0_genTau", "TES_DM0")
            h_summary.GetXaxis().SetBinLabel(syst_idx * 2 + 1, f"{syst_short[:12]}_Up")
            h_summary.GetXaxis().SetBinLabel(syst_idx * 2 + 2, f"{syst_short[:12]}_Dn")

        h_summary.SetFillColor(ROOT.kAzure - 4)
        h_summary.GetXaxis().SetLabelSize(0.04)
        h_summary.GetXaxis().LabelsOption("v")
        h_summary.Draw("BAR")

        # Add stat error band
        nom_val = tt_combined.GetBinContent(bin_idx)
        nom_err = tt_combined.GetBinError(bin_idx)
        stat_pct = nom_err / nom_val * 100 if nom_val > 0 else 0

        box = ROOT.TBox(0, -stat_pct, n_syst * 2, stat_pct)
        box.SetFillStyle(3001)
        box.SetFillColor(ROOT.kGray)
        box.Draw()

        latex3 = ROOT.TLatex()
        latex3.SetNDC()
        latex3.SetTextSize(0.04)
        latex3.DrawLatex(0.2, 0.92, f"Nom: {nom_val:.2f} #pm {nom_err:.2f} ({stat_pct:.1f}%)")

    canvas3.SaveAs(os.path.join(output_dir, "tt_subprocess_summary.png"))
    print(f"  Saved: {output_dir}/tt_subprocess_summary.png")


def main():
    parser = argparse.ArgumentParser(description="Check subprocess systematic fluctuations")
    parser.add_argument("--config", default="../config/analysis_config_1tau1l_XGB080test.yaml",
                        help="Analysis config file")
    parser.add_argument("--era", default="2018", help="Era")
    parser.add_argument("--output", default=None, help="Output directory")
    parser.add_argument("--channel", default="1tau1l", help="Channel")
    args = parser.parse_args()

    # Get base path
    base_path = get_wh_base_path(args.config, args.era)
    print(f"WH base path: {base_path}")

    # Output directory
    if args.output is None:
        output_dir = os.path.join(base_path, "subprocess_systematics")
    else:
        output_dir = args.output

    plot_subprocess_analysis(base_path, args.era, output_dir, args.channel)

    print(f"\n=== Done! Plots saved to {output_dir} ===")


if __name__ == "__main__":
    main()
