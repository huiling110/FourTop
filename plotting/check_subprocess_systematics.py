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

# Subprocess mapping for each process (from ttttGlobleQuantity.py histoGramPerSample)
PROCESS_SUBPROCESSES = {
    "tt": ["ttbar_0l", "ttbar_1l", "ttbar_2l"],
    "ttbb": ["TTBB_4f_TTTo2L2Nu", "TTBB_4f_TTToHadronic", "TTBB_4f_TTToSemiLeptonic"],
    "singleTop": ["st_schan_had", "st_schan_lep", "st_tchan", "st_tW_antitop", "st_tW_top"],
    "ttW": ["TTWJetsToLNu", "TTWJetsToQQ"],
    "ttZ": ["TTZToLLNuNu", "TTZToQQ"],
    "ttH": ["ttH_bb", "ttH_nonbb"],
    "tttt": ["tttt"],
    "fakeTau": ["fakeTau_data_ptMorphed"],
    "fakeLepton": ["fakeLepton"],
    "Minor": ["zz", "WWW", "WWZ", "WZZ", "ZZZ", "ZGToLLG", "ttG", "ggH_bb", "ggH_WW_2l", "ggH_ZZ_2l", "ggH_ZZ_4l"],
    "WJets": ["WJetsToLNu_HT-200To400", "WJetsToLNu_HT-400To600", "WJetsToLNu_HT-600To800",
              "WJetsToLNu_HT-800To1200", "WJetsToLNu_HT-1200To2500", "WJetsToLNu_HT-2500ToInf"],
    "DY": ["DYJetsToLL_M-10to50", "DYJetsToLL_M-50"],
}

# For backward compatibility
TT_SUBPROCESSES = PROCESS_SUBPROCESSES["tt"]

# Default top 5 systematics (will be overridden by --top-systematics or auto-detected)
DEFAULT_TOP5_SYSTEMATICS = [
    "CMS_scale_t_DeepTau2017v2p1_DM0_genTau_2018",
    "CMS_scale_j_TimePtEta_2018",
    "CMS_scale_met_unclustered_energy_2018",
    "CMS_res_j_2018",
    "CMS_scale_j_RelativeFSR",
]
TOP5_SYSTEMATICS_TT = DEFAULT_TOP5_SYSTEMATICS  # Alias for backward compat

def parse_fluctuation_report(report_path, process, n_top=5):
    """Parse the fluctuation report and extract top N systematics for a process.

    Returns unique systematics (not distinguished by Up/Down direction).
    """
    if not os.path.exists(report_path):
        print(f"  WARNING: Fluctuation report not found: {report_path}")
        return []

    systematics = []
    seen = set()

    with open(report_path, 'r') as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            # Parse lines like: "1     singleTop       ps_fsr                                        Down  294.0..."
            parts = line.split()
            if len(parts) < 5:
                continue
            try:
                rank = int(parts[0])
            except ValueError:
                continue

            proc = parts[1]
            syst = parts[2]

            # Check if this is for our process
            if proc == process:
                if syst not in seen:
                    seen.add(syst)
                    systematics.append(syst)
                    if len(systematics) >= n_top:
                        break

    return systematics

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


def plot_systematic_comparison(syst, base_path, era, subprocess_nominals, combined,
                                output_dir, channel="1tau1l", region="SR", process="tt"):
    """Create a side-by-side comparison plot for process combined vs subprocesses.

    Format matches check_systematic_fluctuations.py:
    - N rows: Combined, subprocess_1, subprocess_2, ...
    - 2 columns: Left = shape, Right = variation %
    """
    ROOT.gStyle.SetOptStat(0)

    region_str = f"{channel}{region}"
    nbins = combined.GetNbinsX()

    # Get list of subprocesses that have histograms
    subprocesses = list(subprocess_nominals.keys())

    # Get systematic paths
    syst_paths = get_systematic_wh_paths(base_path, syst, era)
    syst_type = syst_paths["type"]

    print(f"    Syst type: {syst_type}")
    if syst_type in ["JES", "JER", "MET", "EleScale"]:
        print(f"    Up dir: {syst_paths['Up']}")
        print(f"    Down dir: {syst_paths['Down']}")

    # Subprocesses to plot (in order): combined + all subprocesses with data
    combined_name = f"{process}_combined"
    subprocesses_to_plot = [combined_name] + subprocesses[:2]  # Limit to 2 subprocesses for 3-row layout

    # Get histograms for each
    nominals = {combined_name: combined}
    up_hists = {}
    down_hists = {}

    for subprocess in subprocess_nominals:
        nominals[subprocess] = subprocess_nominals[subprocess]

    # Get systematic variations for combined
    # NOTE: All systematics are stored in the nominal WH file as histogram variations
    comb_up = None
    comb_down = None
    for subprocess in subprocesses:
        if subprocess not in subprocess_nominals:
            continue
        # All systematics are in nominal file with name: {subprocess}_{region}_{syst}Up/Down_BDT
        up_hist = get_hist_from_wh(base_path, subprocess, region_str, syst, "Up")
        down_hist = get_hist_from_wh(base_path, subprocess, region_str, syst, "Down")

        if up_hist:
            print(f"      {subprocess} Up: {up_hist.Integral():.2f} events ({int(up_hist.GetEntries())} ent)")
        else:
            print(f"      {subprocess} Up: NOT FOUND")
        if down_hist:
            print(f"      {subprocess} Down: {down_hist.Integral():.2f} events ({int(down_hist.GetEntries())} ent)")
        else:
            print(f"      {subprocess} Down: NOT FOUND")

        if up_hist:
            if comb_up is None:
                comb_up = up_hist.Clone(f"{process}_combined_up")
            else:
                comb_up.Add(up_hist)
        if down_hist:
            if comb_down is None:
                comb_down = down_hist.Clone(f"{process}_combined_down")
            else:
                comb_down.Add(down_hist)

        # Store individual subprocess variations
        up_hists[subprocess] = up_hist
        down_hists[subprocess] = down_hist

    up_hists[combined_name] = comb_up
    down_hists[combined_name] = comb_down

    # Create canvas with N rows x 2 columns (N = number of subprocesses to plot)
    n_rows = len(subprocesses_to_plot)
    canvas = ROOT.TCanvas(f"c_compare_{process}_{region}_{syst}", syst, 1600, 400 * n_rows)
    canvas.Divide(2, n_rows)

    syst_short = syst.replace("CMS_", "").replace("_2018", "")

    # Keep references to prevent garbage collection
    keep_alive = []

    # Debug: print what we have before drawing
    print(f"    Drawing with:")
    for sp in subprocesses_to_plot:
        nom = nominals.get(sp)
        up = up_hists.get(sp)
        down = down_hists.get(sp)
        nom_str = f"{nom.Integral():.2f}" if nom else "None"
        up_str = f"{up.Integral():.2f}" if up else "None"
        down_str = f"{down.Integral():.2f}" if down else "None"
        print(f"      {sp}: nom={nom_str}, up={up_str}, down={down_str}")

    for row_idx, sp in enumerate(subprocesses_to_plot):
        nom_hist = nominals.get(sp)
        up_hist = up_hists.get(sp)
        down_hist = down_hists.get(sp)

        # Left column: Shape comparison
        pad_num = row_idx * 2 + 1
        print(f"      Drawing {sp} to pad {pad_num}")
        canvas.cd(pad_num)
        ROOT.gPad.SetGrid()
        ROOT.gPad.SetLeftMargin(0.12)
        ROOT.gPad.SetRightMargin(0.05)

        if nom_hist is None or nom_hist.Integral() < 0.001:
            # Empty subplot
            latex = ROOT.TLatex()
            latex.SetNDC()
            latex.SetTextSize(0.08)
            latex.DrawLatex(0.3, 0.5, f"{sp}: No events")
            continue

        nom_clone = nom_hist.Clone(f"nom_{sp}_{syst}")
        nom_clone.SetDirectory(0)
        nom_clone.SetLineColor(ROOT.kBlack)
        nom_clone.SetLineWidth(2)
        nom_clone.SetMarkerStyle(20)
        nom_clone.SetMarkerSize(0.8)
        keep_alive.append(nom_clone)

        # Create error band for stat uncertainty
        nom_err_band = nom_hist.Clone(f"nom_err_{sp}_{syst}")
        nom_err_band.SetDirectory(0)
        nom_err_band.SetFillColor(ROOT.kGray)
        nom_err_band.SetFillStyle(3001)
        nom_err_band.SetLineColor(ROOT.kBlack)
        nom_err_band.SetMarkerSize(0)
        keep_alive.append(nom_err_band)

        title = f"{sp} | {syst_short}"
        nom_clone.SetTitle(title)
        nom_clone.GetYaxis().SetTitle("Events")
        nom_clone.GetXaxis().SetTitle("BDT bin")

        max_val = nom_clone.GetMaximum()
        up_clone = None
        down_clone = None
        if up_hist:
            up_clone = up_hist.Clone(f"up_{sp}_{syst}")
            up_clone.SetDirectory(0)
            up_clone.SetLineColor(ROOT.kRed)
            up_clone.SetLineWidth(2)
            max_val = max(max_val, up_clone.GetMaximum())
            keep_alive.append(up_clone)
        if down_hist:
            down_clone = down_hist.Clone(f"down_{sp}_{syst}")
            down_clone.SetDirectory(0)
            down_clone.SetLineColor(ROOT.kBlue)
            down_clone.SetLineWidth(2)
            max_val = max(max_val, down_clone.GetMaximum())
            keep_alive.append(down_clone)

        nom_clone.GetYaxis().SetRangeUser(0, max_val * 1.5)
        nom_err_band.GetYaxis().SetRangeUser(0, max_val * 1.5)

        # Draw
        nom_err_band.Draw("E2")
        nom_clone.Draw("HIST SAME")
        if up_clone:
            up_clone.Draw("HIST SAME")
        if down_clone:
            down_clone.Draw("HIST SAME")
        nom_clone.Draw("HIST SAME")  # Redraw on top

        # Legend
        leg = ROOT.TLegend(0.55, 0.65, 0.92, 0.88)
        leg.SetBorderSize(0)
        leg.SetFillStyle(0)
        nom_int = nom_clone.Integral()
        nom_ent = int(nom_clone.GetEntries())
        leg.AddEntry(nom_err_band, f"Nom #pm stat", "f")
        leg.AddEntry(nom_clone, f"Nom: {nom_int:.1f} ({nom_ent} ent)", "l")
        if up_clone:
            up_int = up_clone.Integral()
            up_ent = int(up_clone.GetEntries())
            leg.AddEntry(up_clone, f"Up: {up_int:.1f} ({up_ent} ent)", "l")
        if down_clone:
            down_int = down_clone.Integral()
            down_ent = int(down_clone.GetEntries())
            leg.AddEntry(down_clone, f"Down: {down_int:.1f} ({down_ent} ent)", "l")
        leg.Draw()
        keep_alive.append(leg)

        # Right column: Variation percentages
        canvas.cd(row_idx * 2 + 2)
        ROOT.gPad.SetGrid()
        ROOT.gPad.SetLeftMargin(0.12)
        ROOT.gPad.SetRightMargin(0.05)

        h_up = ROOT.TH1F(f"h_up_var_{sp}_{syst}", "", nbins,
                         nom_hist.GetXaxis().GetXmin(),
                         nom_hist.GetXaxis().GetXmax())
        h_up.SetDirectory(0)
        h_down = ROOT.TH1F(f"h_down_var_{sp}_{syst}", "", nbins,
                           nom_hist.GetXaxis().GetXmin(),
                           nom_hist.GetXaxis().GetXmax())
        h_down.SetDirectory(0)
        keep_alive.append(h_up)
        keep_alive.append(h_down)

        # Fill variation histograms
        for i in range(1, nbins + 1):
            nom_val = nom_hist.GetBinContent(i)
            if nom_val > 0.001:
                if up_hist:
                    up_val = up_hist.GetBinContent(i)
                    h_up.SetBinContent(i, (up_val - nom_val) / nom_val * 100)
                if down_hist:
                    down_val = down_hist.GetBinContent(i)
                    h_down.SetBinContent(i, (down_val - nom_val) / nom_val * 100)

        h_up.SetLineColor(ROOT.kRed)
        h_up.SetLineWidth(2)
        h_up.SetFillColor(ROOT.kRed - 9)
        h_up.SetFillStyle(3004)

        h_down.SetLineColor(ROOT.kBlue)
        h_down.SetLineWidth(2)
        h_down.SetFillColor(ROOT.kBlue - 9)
        h_down.SetFillStyle(3005)

        h_up.SetTitle(f"{sp} | {syst_short} variation [%]")
        h_up.GetYaxis().SetTitle("Variation [%]")
        h_up.GetXaxis().SetTitle("BDT bin")

        # Determine y-axis range
        all_vars = []
        for i in range(1, nbins + 1):
            all_vars.append(h_up.GetBinContent(i))
            all_vars.append(h_down.GetBinContent(i))

        non_zero = [abs(v) for v in all_vars if v != 0]
        max_var = max(non_zero) if non_zero else 50
        h_up.GetYaxis().SetRangeUser(-max_var * 1.4, max_var * 1.4)

        h_up.Draw("HIST")
        h_down.Draw("HIST SAME")

        # Zero line
        line = ROOT.TLine(h_up.GetXaxis().GetXmin(), 0, h_up.GetXaxis().GetXmax(), 0)
        line.SetLineColor(ROOT.kBlack)
        line.SetLineStyle(2)
        line.SetLineWidth(2)
        line.Draw()

        # Legend
        leg2 = ROOT.TLegend(0.7, 0.78, 0.88, 0.88)
        leg2.SetBorderSize(0)
        leg2.SetFillStyle(0)
        leg2.AddEntry(h_up, "Up", "f")
        leg2.AddEntry(h_down, "Down", "f")
        leg2.Draw()

        # Add max variation text
        latex = ROOT.TLatex()
        latex.SetNDC()
        latex.SetTextSize(0.04)
        max_up = max(abs(h_up.GetBinContent(i)) for i in range(1, nbins + 1))
        max_down = max(abs(h_down.GetBinContent(i)) for i in range(1, nbins + 1))
        latex.SetTextColor(ROOT.kRed)
        latex.DrawLatex(0.15, 0.85, f"Up: max={max_up:.1f}%")
        latex.SetTextColor(ROOT.kBlue)
        latex.DrawLatex(0.15, 0.78, f"Down: max={max_down:.1f}%")

        # Update pads
        ROOT.gPad.Update()

    # Update canvas before saving
    canvas.Update()

    # Save
    output_path = os.path.join(output_dir, f"compare_{process}_{region}_{syst_short}.png")
    canvas.SaveAs(output_path)
    print(f"    Saved: compare_{process}_{region}_{syst_short}.png")

    return output_path


# Color palette for subprocesses (up to 12 colors)
SUBPROCESS_COLORS = [
    ROOT.kRed, ROOT.kBlue, ROOT.kGreen+2, ROOT.kOrange+1, ROOT.kMagenta+1,
    ROOT.kCyan+1, ROOT.kYellow+1, ROOT.kViolet+1, ROOT.kTeal+1, ROOT.kPink+1,
    ROOT.kAzure+1, ROOT.kSpring+1
]


def plot_subprocess_contributions(process, base_path, era, output_dir, channel="1tau1l", region="SR"):
    """Create subprocess contribution plot for any process.

    Left panel: Stacked histogram of subprocess contributions
    Right panel: Statistical uncertainty per bin for combined and subprocesses
    """
    if process not in PROCESS_SUBPROCESSES:
        print(f"  WARNING: No subprocess mapping for {process}, skipping contributions plot")
        return

    subprocesses = PROCESS_SUBPROCESSES[process]
    region_str = f"{channel}{region}"
    os.makedirs(output_dir, exist_ok=True)

    # Get nominal histograms for each subprocess
    subprocess_nominals = {}
    for subprocess in subprocesses:
        hist = get_hist_from_wh(base_path, subprocess, region_str)
        if hist and (hist.Integral() > 0.001 or hist.GetEntries() > 0):
            subprocess_nominals[subprocess] = hist

    if not subprocess_nominals:
        print(f"  No subprocess histograms found for {process} in {region_str}")
        return

    # Create combined nominal
    combined = None
    for subprocess, hist in subprocess_nominals.items():
        if combined is None:
            combined = hist.Clone(f"{process}_combined_nominal")
        else:
            combined.Add(hist)

    nbins = combined.GetNbinsX()

    # Keep references to prevent garbage collection
    keep_alive = []

    # Create canvas
    canvas = ROOT.TCanvas(f"c_{process}_{region}_contrib",
                          f"{process} Subprocess Contributions ({region})", 1200, 800)
    canvas.Divide(2, 1)

    # ===== Left panel: Stacked histogram =====
    canvas.cd(1)
    ROOT.gPad.SetGrid()
    ROOT.gPad.SetLeftMargin(0.12)
    ROOT.gPad.SetRightMargin(0.05)

    stack = ROOT.THStack(f"hs_{process}_{region}",
                         f"{process} Subprocess Contributions ({region});BDT bin;Events")
    legend = ROOT.TLegend(0.55, 0.65, 0.92, 0.88)
    legend.SetBorderSize(0)
    legend.SetFillStyle(0)
    keep_alive.append(legend)

    # Add subprocesses to stack
    for idx, subprocess in enumerate(subprocesses):
        if subprocess in subprocess_nominals:
            hist = subprocess_nominals[subprocess].Clone(f"{subprocess}_stack")
            hist.SetDirectory(0)
            color = SUBPROCESS_COLORS[idx % len(SUBPROCESS_COLORS)]
            hist.SetFillColor(color)
            hist.SetLineColor(color)
            stack.Add(hist)
            # Shorten subprocess name for legend
            short_name = subprocess.replace("TTBB_4f_", "").replace("WJetsToLNu_", "WJ_")
            legend.AddEntry(hist, f"{short_name}: {hist.Integral():.1f}", "f")
            keep_alive.append(hist)

    stack.Draw("HIST")
    stack.GetYaxis().SetTitle("Events")
    stack.GetXaxis().SetTitle("BDT bin")
    keep_alive.append(stack)

    # Draw combined with error bars
    combined_err = combined.Clone(f"{process}_combined_err")
    combined_err.SetDirectory(0)
    combined_err.SetFillStyle(3004)
    combined_err.SetFillColor(ROOT.kBlack)
    combined_err.Draw("E2 SAME")
    legend.AddEntry(combined_err, f"Combined: {combined.Integral():.1f} #pm stat", "f")
    keep_alive.append(combined_err)

    legend.Draw()

    # ===== Right panel: Statistical uncertainties =====
    canvas.cd(2)
    ROOT.gPad.SetGrid()
    ROOT.gPad.SetLeftMargin(0.12)
    ROOT.gPad.SetRightMargin(0.05)

    # Create stat uncertainty histogram for combined
    h_stat_combined = ROOT.TH1F(f"h_stat_{process}_{region}_combined",
                                 f"Statistical Uncertainty ({region});BDT bin;Stat. Error [%]",
                                 nbins, combined.GetXaxis().GetXmin(), combined.GetXaxis().GetXmax())
    h_stat_combined.SetDirectory(0)
    keep_alive.append(h_stat_combined)

    for i in range(1, nbins + 1):
        content = combined.GetBinContent(i)
        error = combined.GetBinError(i)
        if content > 0:
            h_stat_combined.SetBinContent(i, error / content * 100)

    h_stat_combined.SetLineColor(ROOT.kBlack)
    h_stat_combined.SetLineWidth(3)
    h_stat_combined.SetFillColor(ROOT.kGray)
    h_stat_combined.SetFillStyle(3001)

    # Find max for y-axis
    max_stat = h_stat_combined.GetMaximum()

    # Create stat uncertainty histograms for subprocesses
    stat_hists = []
    for idx, subprocess in enumerate(subprocesses):
        if subprocess in subprocess_nominals:
            hist = subprocess_nominals[subprocess]
            h_stat = ROOT.TH1F(f"h_stat_{subprocess}_{region}", "",
                               nbins, combined.GetXaxis().GetXmin(), combined.GetXaxis().GetXmax())
            h_stat.SetDirectory(0)
            for i in range(1, nbins + 1):
                content = hist.GetBinContent(i)
                error = hist.GetBinError(i)
                if content > 0:
                    h_stat.SetBinContent(i, error / content * 100)
            color = SUBPROCESS_COLORS[idx % len(SUBPROCESS_COLORS)]
            h_stat.SetLineColor(color)
            h_stat.SetLineWidth(2)
            h_stat.SetLineStyle(2)
            stat_hists.append((subprocess, h_stat))
            max_stat = max(max_stat, h_stat.GetMaximum())
            keep_alive.append(h_stat)

    h_stat_combined.GetYaxis().SetRangeUser(0, max_stat * 1.3)
    h_stat_combined.Draw("HIST")

    for subprocess, h_stat in stat_hists:
        h_stat.Draw("HIST SAME")

    # Legend for stat uncertainties
    leg_stat = ROOT.TLegend(0.55, 0.55, 0.92, 0.88)
    leg_stat.SetBorderSize(0)
    leg_stat.SetFillStyle(0)
    leg_stat.AddEntry(h_stat_combined, f"{process} combined", "f")
    for subprocess, h_stat in stat_hists[:5]:  # Limit to top 5 for readability
        short_name = subprocess.replace("TTBB_4f_", "").replace("WJetsToLNu_", "WJ_")
        leg_stat.AddEntry(h_stat, short_name, "l")
    leg_stat.Draw()
    keep_alive.append(leg_stat)

    # Add per-bin info for combined
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.025)
    for i in range(1, min(nbins + 1, 8)):
        content = combined.GetBinContent(i)
        error = combined.GetBinError(i)
        pct = error / content * 100 if content > 0 else 0
        latex.DrawLatex(0.15, 0.88 - 0.03 * (i - 1),
                        f"Bin {i}: {content:.2f} #pm {error:.2f} ({pct:.1f}%)")

    canvas.Update()

    # Save
    output_path = os.path.join(output_dir, f"{process}_{region}_subprocess_contributions.png")
    canvas.SaveAs(output_path)
    print(f"  Saved: {process}_{region}_subprocess_contributions.png")

    return output_path


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

    nbins = tt_combined.GetNbinsX()

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

    # Right: Statistical uncertainties per bin for each subprocess
    canvas1.cd(2)
    ROOT.gPad.SetGrid()
    ROOT.gPad.SetLeftMargin(0.12)
    ROOT.gPad.SetRightMargin(0.05)

    # Create histograms for each subprocess stat uncertainty
    h_stat_combined = ROOT.TH1F("h_stat_combined", "Statistical Uncertainty;BDT bin;Stat. Error [%]",
                                 nbins, tt_combined.GetXaxis().GetXmin(), tt_combined.GetXaxis().GetXmax())
    h_stat_2l = ROOT.TH1F("h_stat_2l", "", nbins,
                           tt_combined.GetXaxis().GetXmin(), tt_combined.GetXaxis().GetXmax())
    h_stat_1l = ROOT.TH1F("h_stat_1l", "", nbins,
                           tt_combined.GetXaxis().GetXmin(), tt_combined.GetXaxis().GetXmax())
    h_stat_0l = ROOT.TH1F("h_stat_0l", "", nbins,
                           tt_combined.GetXaxis().GetXmin(), tt_combined.GetXaxis().GetXmax())

    # Fill combined tt stat uncertainty
    for i in range(1, nbins + 1):
        content = tt_combined.GetBinContent(i)
        error = tt_combined.GetBinError(i)
        if content > 0:
            h_stat_combined.SetBinContent(i, error / content * 100)

    # Fill each subprocess stat uncertainty
    for subprocess, h_stat, color in [("ttbar_2l", h_stat_2l, ROOT.kGreen+2),
                                       ("ttbar_1l", h_stat_1l, ROOT.kBlue),
                                       ("ttbar_0l", h_stat_0l, ROOT.kRed)]:
        if subprocess in subprocess_nominals:
            hist = subprocess_nominals[subprocess]
            for i in range(1, nbins + 1):
                content = hist.GetBinContent(i)
                error = hist.GetBinError(i)
                if content > 0:
                    h_stat.SetBinContent(i, error / content * 100)
        h_stat.SetLineColor(color)
        h_stat.SetLineWidth(2)
        h_stat.SetLineStyle(2)

    # Style combined
    h_stat_combined.SetLineColor(ROOT.kBlack)
    h_stat_combined.SetLineWidth(3)
    h_stat_combined.SetFillColor(ROOT.kGray)
    h_stat_combined.SetFillStyle(3001)

    # Find max for y-axis
    max_stat = max(h_stat_combined.GetMaximum(), h_stat_2l.GetMaximum(),
                   h_stat_1l.GetMaximum(), h_stat_0l.GetMaximum())
    h_stat_combined.GetYaxis().SetRangeUser(0, max_stat * 1.3)

    h_stat_combined.Draw("HIST")
    h_stat_2l.Draw("HIST SAME")
    h_stat_1l.Draw("HIST SAME")

    # Legend for stat uncertainties
    leg_stat = ROOT.TLegend(0.55, 0.65, 0.92, 0.88)
    leg_stat.SetBorderSize(0)
    leg_stat.SetFillStyle(0)
    leg_stat.AddEntry(h_stat_combined, "tt combined", "f")
    leg_stat.AddEntry(h_stat_2l, "ttbar_2l", "l")
    leg_stat.AddEntry(h_stat_1l, "ttbar_1l", "l")
    leg_stat.Draw()

    # Add text with per-bin info for combined
    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.028)
    for i in range(1, min(nbins + 1, 8)):  # Limit to first 7 bins to fit
        content = tt_combined.GetBinContent(i)
        error = tt_combined.GetBinError(i)
        pct = error / content * 100 if content > 0 else 0
        latex.DrawLatex(0.15, 0.85 - 0.035 * (i - 1), f"Bin {i}: {content:.2f} #pm {error:.2f} ({pct:.1f}%)")

    canvas1.SaveAs(os.path.join(output_dir, "tt_subprocess_contributions.png"))
    print(f"  Saved: {output_dir}/tt_subprocess_contributions.png")

    # ===== Plot 2: Side-by-side comparison plots (tt vs ttbar_2l vs ttbar_1l) =====
    print(f"\n=== Creating systematic comparison plots (matching total plot format) ===")

    for syst in TOP5_SYSTEMATICS_TT:
        print(f"\n  Processing: {syst}")
        plot_systematic_comparison(syst, base_path, era, subprocess_nominals, tt_combined,
                                   output_dir, channel)

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
            # Sum variations from all subprocesses
            nom_sum = sum(subprocess_nominals[sp].GetBinContent(bin_idx) for sp in TT_SUBPROCESSES if sp in subprocess_nominals)

            up_sum = 0
            down_sum = 0
            for subprocess in TT_SUBPROCESSES:
                if subprocess not in subprocess_nominals:
                    continue

                # All systematics are in nominal WH file
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


def plot_process_subprocess_analysis(process, systematics, base_path, era, output_dir,
                                      channel="1tau1l", region="SR"):
    """Analyze subprocess systematics for a specific process."""

    if process not in PROCESS_SUBPROCESSES:
        print(f"  WARNING: No subprocess mapping for {process}, skipping")
        return

    subprocesses = PROCESS_SUBPROCESSES[process]
    if not subprocesses:
        print(f"  WARNING: Empty subprocess list for {process}, skipping")
        return

    region_str = f"{channel}{region}"
    os.makedirs(output_dir, exist_ok=True)

    print(f"\n=== Processing {process} in {region_str} ===")
    print(f"  Subprocesses: {subprocesses}")

    # Get nominal histograms for each subprocess
    subprocess_nominals = {}
    for subprocess in subprocesses:
        hist = get_hist_from_wh(base_path, subprocess, region_str)
        if hist:
            integral = hist.Integral()
            entries = int(hist.GetEntries())
            if integral > 0.001 or entries > 0:
                print(f"    {subprocess}: {integral:.2f} events, {entries} entries")
                subprocess_nominals[subprocess] = hist
            else:
                print(f"    {subprocess}: 0 events (skipped)")
        else:
            print(f"    {subprocess}: NOT FOUND")

    if not subprocess_nominals:
        print(f"  No subprocess histograms found for {process}")
        return

    # Create combined nominal
    combined = None
    for subprocess, hist in subprocess_nominals.items():
        if combined is None:
            combined = hist.Clone(f"{process}_combined_nominal")
        else:
            combined.Add(hist)

    print(f"  Combined {process}: {combined.Integral():.2f} events")

    # Plot subprocess contributions
    print(f"\n  Creating subprocess contributions plot...")
    plot_subprocess_contributions(process, base_path, era, output_dir, channel, region)

    # Plot each systematic
    for syst in systematics:
        print(f"\n  Systematic: {syst}")
        plot_systematic_comparison(syst, base_path, era, subprocess_nominals, combined,
                                   output_dir, channel, region, process)

    print(f"\n  Plots saved to {output_dir}")


def main():
    parser = argparse.ArgumentParser(description="Check subprocess systematic fluctuations")
    parser.add_argument("--config", default="../config/analysis_config_1tau1l_XGB080test.yaml",
                        help="Analysis config file")
    parser.add_argument("--era", default="2018", help="Era")
    parser.add_argument("--output", default=None, help="Output directory")
    parser.add_argument("--channel", default="1tau1l", help="Channel")
    parser.add_argument("--process", default="tt", help="Process to analyze (or 'all')")
    parser.add_argument("--region", default="SR", help="Region (SR or CR12, or 'all')")
    parser.add_argument("--systematics", default=None, nargs="+",
                        help="List of systematics to check")
    parser.add_argument("--auto-top5", action="store_true",
                        help="Auto-detect top 5 systematics per process from fluctuation_report.txt")
    args = parser.parse_args()

    # Get base path
    base_path = get_wh_base_path(args.config, args.era)
    print(f"WH base path: {base_path}")

    # Output directory
    if args.output is None:
        output_dir = os.path.join(base_path, "subprocess_systematics")
    else:
        output_dir = args.output
    os.makedirs(output_dir, exist_ok=True)

    # Determine processes
    if args.process == "all":
        # Only processes that have multiple subprocesses
        processes = ["tt", "ttbb", "singleTop", "ttW", "ttZ", "ttH"]
    else:
        processes = [args.process]

    # Determine regions
    if args.region == "all":
        regions = ["SR", "CR12"]
    else:
        regions = [args.region]

    # Path to fluctuation report (for auto-detection)
    fluct_report = os.path.join(base_path, "combine/systematic_fluctuations/fluctuation_report.txt")

    # Run for backward compatibility mode (tt only, SR only, no --auto-top5)
    if args.process == "tt" and args.region == "SR" and not args.systematics and not args.auto_top5:
        # Original behavior
        plot_subprocess_analysis(base_path, args.era, output_dir, args.channel)
    else:
        # New multi-process, multi-region mode
        for process in processes:
            # Determine systematics for this process
            if args.systematics:
                systematics = args.systematics
            elif args.auto_top5:
                systematics = parse_fluctuation_report(fluct_report, process, n_top=5)
                if not systematics:
                    print(f"\n  No systematics found for {process} in fluctuation report, using defaults")
                    systematics = DEFAULT_TOP5_SYSTEMATICS
                elif len(systematics) < 5:
                    # Fill with defaults if less than 5 found
                    print(f"\n  Top {len(systematics)} systematics for {process}: {systematics}")
                    print(f"  Filling remaining {5 - len(systematics)} with defaults")
                    for s in DEFAULT_TOP5_SYSTEMATICS:
                        if s not in systematics:
                            systematics.append(s)
                            if len(systematics) >= 5:
                                break
                else:
                    print(f"\n  Top 5 systematics for {process}: {systematics}")
            else:
                systematics = DEFAULT_TOP5_SYSTEMATICS

            for region in regions:
                region_output = os.path.join(output_dir, f"{process}_{region}")
                plot_process_subprocess_analysis(process, systematics, base_path, args.era,
                                                  region_output, args.channel, region)

    print(f"\n=== Done! Plots saved to {output_dir} ===")


if __name__ == "__main__":
    main()
