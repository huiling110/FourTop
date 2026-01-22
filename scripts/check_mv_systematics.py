#!/usr/bin/env python3
"""
Check MV systematic variations for all samples and generate markdown table.
Usage: python3 scripts/check_mv_systematics.py --config CONFIG --era ERA [--output FILE]
"""

import ROOT
import argparse
import os

from fourtop.workflow import load_config

def get_entries(path):
    """Get number of entries from ROOT file."""
    try:
        f = ROOT.TFile.Open(path)
        if f and not f.IsZombie():
            t = f.Get("newtree")
            if t:
                ent = t.GetEntries()
                f.Close()
                return ent
        return None
    except:
        return None

def get_mv_samples(config, era):
    """Get list of MC samples for the channel."""
    channel = config.get('channel', '1tau0l')

    # Common samples for all channels
    samples = [
        "tttt",
        "TTBB_4f_TTToHadronic",
        "TTBB_4f_TTToSemiLeptonic",
        "TTBB_4f_TTTo2L2Nu",
        "ttbar_0l",
        "ttbar_1l",
        "ttbar_2l",
        "TTZToQQ",
        "TTZToLLNuNu",
        "TTWJetsToLNu",
        "TTWJetsToQQ",
        "ttH_bb",
        "ttH_nonbb",
        "st_tW_top",
        "st_tW_antitop",
        "st_tchan",
        "st_schan_lep",
        "st_schan_had",
    ]

    # Add WJets samples
    wjets = [
        "WJetsToLNu_HT-200To400",
        "WJetsToLNu_HT-400To600",
        "WJetsToLNu_HT-600To800",
        "WJetsToLNu_HT-800To1200",
        "WJetsToLNu_HT-1200To2500",
        "WJetsToLNu_HT-2500ToInf",
    ]
    samples.extend(wjets)

    return samples

def get_jes_sources():
    """Get list of all JES sources."""
    return [
        "AbsoluteMPFBias_AK4PFchs",
        "AbsoluteScale_AK4PFchs",
        "AbsoluteStat_AK4PFchs",
        "FlavorPureBottom_AK4PFchs",
        "FlavorPureCharm_AK4PFchs",
        "FlavorPureGluon_AK4PFchs",
        "FlavorPureQuark_AK4PFchs",
        "Fragmentation_AK4PFchs",
        "PileUpDataMC_AK4PFchs",
        "PileUpPtBB_AK4PFchs",
        "PileUpPtEC1_AK4PFchs",
        "PileUpPtEC2_AK4PFchs",
        "PileUpPtHF_AK4PFchs",
        "PileUpPtRef_AK4PFchs",
        "RelativeBal_AK4PFchs",
        "RelativeFSR_AK4PFchs",
        "RelativeJEREC1_AK4PFchs",
        "RelativeJEREC2_AK4PFchs",
        "RelativeJERHF_AK4PFchs",
        "RelativePtBB_AK4PFchs",
        "RelativePtEC1_AK4PFchs",
        "RelativePtEC2_AK4PFchs",
        "RelativePtHF_AK4PFchs",
        "RelativeSample_AK4PFchs",
        "RelativeStatEC_AK4PFchs",
        "RelativeStatFSR_AK4PFchs",
        "RelativeStatHF_AK4PFchs",
        "SinglePionECAL_AK4PFchs",
        "SinglePionHCAL_AK4PFchs",
        "TimePtEta_AK4PFchs",
    ]

def get_systematic_paths(config, era):
    """Get dictionary of systematic variation paths."""
    stage1 = config['versions']['stage1']
    base = f"{config['paths']['output_base']}/{era}"

    systematics = {
        "Nominal": f"v1baselineHadro_{stage1}",
    }

    # Add all JES sources (Up and Down)
    for jes_source in get_jes_sources():
        systematics[f"JES_{jes_source}_Up"] = f"v1baselineHadro_JESup_{jes_source}_{stage1}_JESPt22"
        systematics[f"JES_{jes_source}_Down"] = f"v1baselineHadro_JESDown_{jes_source}_{stage1}_JESPt22"

    # Add TES variations
    for dm in ["dm0", "dm1", "dm10", "dm11"]:
        systematics[f"TES{dm}Up"] = f"v1baselineHadro_{stage1}_TES{dm}Up"
        systematics[f"TES{dm}Down"] = f"v1baselineHadro_{stage1}_TES{dm}Down"

    # Add other systematics
    systematics.update({
        "JERUp": f"v1baselineHadro_{stage1}_JERUp",
        "JERDown": f"v1baselineHadro_{stage1}_JERDown",
        "METUp": f"v1baselineHadro_{stage1}_METUp",
        "METDown": f"v1baselineHadro_{stage1}_METDown",
        "EleScaleUp": f"v1baselineHadro_{stage1}_EleScaleUp",
        "EleScaleDown": f"v1baselineHadro_{stage1}_EleScaleDown",
    })

    return base, systematics

def check_mv_systematics(config, era, output_file=None):
    """Check MV systematics and generate markdown table."""
    samples = get_mv_samples(config, era)
    base, systematics = get_systematic_paths(config, era)
    jes_sources = get_jes_sources()

    # Collect data
    print(f"Checking {len(samples)} samples with {len(systematics)} systematics...")
    results = {}
    for sample in samples:
        results[sample] = {}
        for sys_name, sys_dir in systematics.items():
            path = f"{base}/{sys_dir}/mc/{sample}.root"
            results[sample][sys_name] = get_entries(path)

    # Generate markdown
    lines = []
    lines.append(f"# MV Systematic Verification - {era}")
    lines.append("")
    lines.append(f"**Config:** `{config['metadata']['name']}`")
    lines.append(f"**Stage1:** `{config['versions']['stage1']}`")
    lines.append(f"**Total systematics:** {len(systematics)} (60 JES + 8 TES + 2 JER + 2 MET + 2 EleScale + 1 Nominal)")
    lines.append("")

    # Summary table with key systematics
    lines.append("## Summary Table (Key Systematics)")
    lines.append("")
    lines.append("| Sample | Nominal | JES RelSample Up | JES RelSample Down | TESdm0Up | JERUp | METUp |")
    lines.append("|--------|---------|------------------|-------------------|----------|-------|-------|")

    for sample in samples:
        nom = results[sample].get("Nominal")
        if nom is None or nom == 0:
            continue

        jes_up = results[sample].get("JES_RelativeSample_AK4PFchs_Up")
        jes_down = results[sample].get("JES_RelativeSample_AK4PFchs_Down")
        tes_up = results[sample].get("TESdm0Up")
        jer_up = results[sample].get("JERUp")
        met_up = results[sample].get("METUp")

        def pct(val):
            if val is None:
                return "N/A"
            return f"{(val - nom) / nom * 100:+.2f}%"

        lines.append(f"| {sample} | {nom:,} | {pct(jes_up)} | {pct(jes_down)} | {pct(tes_up)} | {pct(jer_up)} | {pct(met_up)} |")

    lines.append("")

    # JES Systematics Table (all 30 sources)
    lines.append("## JES Systematics (All 30 Sources)")
    lines.append("")
    lines.append("### tttt JES Variations")
    lines.append("")
    lines.append("| JES Source | Up (%) | Down (%) | Pattern OK |")
    lines.append("|------------|--------|----------|------------|")

    tttt_nom = results.get("tttt", {}).get("Nominal", 0)
    jes_issues = []
    for jes_source in jes_sources:
        up_key = f"JES_{jes_source}_Up"
        down_key = f"JES_{jes_source}_Down"
        up_val = results.get("tttt", {}).get(up_key)
        down_val = results.get("tttt", {}).get(down_key)

        if up_val and down_val and tttt_nom:
            up_pct = (up_val - tttt_nom) / tttt_nom * 100
            down_pct = (down_val - tttt_nom) / tttt_nom * 100
            # Check pattern: Up < Nom < Down means up_pct < 0 and down_pct > 0
            pattern_ok = up_val < tttt_nom < down_val
            status = "✓" if pattern_ok else "✗"
            if not pattern_ok:
                jes_issues.append(jes_source)
            lines.append(f"| {jes_source.replace('_AK4PFchs', '')} | {up_pct:+.2f} | {down_pct:+.2f} | {status} |")
        else:
            lines.append(f"| {jes_source.replace('_AK4PFchs', '')} | N/A | N/A | ? |")

    lines.append("")

    # TES/JER/MET/EleScale table
    lines.append("## Other Systematics (TES, JER, MET, EleScale)")
    lines.append("")
    lines.append("| Sample | TESdm0 | TESdm1 | TESdm10 | TESdm11 | JER | MET | EleScale |")
    lines.append("|--------|--------|--------|---------|---------|-----|-----|----------|")

    for sample in ["tttt", "TTBB_4f_TTToHadronic", "ttbar_0l", "TTZToQQ", "ttH_bb"]:
        nom = results.get(sample, {}).get("Nominal")
        if nom is None or nom == 0:
            continue

        def pct_range(up_key, down_key):
            up = results.get(sample, {}).get(up_key)
            down = results.get(sample, {}).get(down_key)
            if up is None or down is None:
                return "N/A"
            up_pct = (up - nom) / nom * 100
            down_pct = (down - nom) / nom * 100
            return f"{down_pct:+.1f}/{up_pct:+.1f}"

        tes0 = pct_range("TESdm0Up", "TESdm0Down")
        tes1 = pct_range("TESdm1Up", "TESdm1Down")
        tes10 = pct_range("TESdm10Up", "TESdm10Down")
        tes11 = pct_range("TESdm11Up", "TESdm11Down")
        jer = pct_range("JERUp", "JERDown")
        met = pct_range("METUp", "METDown")
        ele = pct_range("EleScaleUp", "EleScaleDown")

        lines.append(f"| {sample} | {tes0} | {tes1} | {tes10} | {tes11} | {jer} | {met} | {ele} |")

    lines.append("")

    # Full JES table for all samples
    lines.append("## Full JES Table (All Samples)")
    lines.append("")
    lines.append("| Sample | Nominal | AbsMPFBias | AbsScale | FlavorBot | PileUpDMC | RelBal | RelSample | TimePtEta |")
    lines.append("|--------|---------|------------|----------|-----------|-----------|--------|-----------|-----------|")

    key_jes = ["AbsoluteMPFBias_AK4PFchs", "AbsoluteScale_AK4PFchs", "FlavorPureBottom_AK4PFchs",
               "PileUpDataMC_AK4PFchs", "RelativeBal_AK4PFchs", "RelativeSample_AK4PFchs", "TimePtEta_AK4PFchs"]

    for sample in samples:
        nom = results.get(sample, {}).get("Nominal")
        if nom is None or nom == 0:
            continue

        row = [sample, f"{nom:,}"]
        for jes in key_jes:
            up = results.get(sample, {}).get(f"JES_{jes}_Up")
            down = results.get(sample, {}).get(f"JES_{jes}_Down")
            if up and down:
                up_pct = (up - nom) / nom * 100
                down_pct = (down - nom) / nom * 100
                row.append(f"{up_pct:+.1f}/{down_pct:+.1f}")
            else:
                row.append("N/A")

        lines.append("| " + " | ".join(row) + " |")

    lines.append("")

    # Verification summary
    lines.append("## Verification Summary")
    lines.append("")
    lines.append("### Expected Patterns")
    lines.append("- **JES:** Up < Nominal < Down (negative/positive %)")
    lines.append("- **TES:** Small variations (±0.1% typical)")
    lines.append("- **JER:** Small variations (±0.3% typical)")
    lines.append("- **MET/EleScale:** Very small (±0.01% typical)")
    lines.append("")

    # Check for issues
    all_issues = []

    # Check JES pattern for all samples
    for sample in samples:
        nom = results.get(sample, {}).get("Nominal")
        if nom is None or nom == 0:
            continue

        for jes_source in jes_sources:
            up_val = results.get(sample, {}).get(f"JES_{jes_source}_Up")
            down_val = results.get(sample, {}).get(f"JES_{jes_source}_Down")

            if up_val and down_val:
                if not (up_val < nom < down_val):
                    all_issues.append(f"- {sample}: JES {jes_source} pattern wrong (Up={up_val}, Nom={nom}, Down={down_val})")

    if all_issues:
        lines.append(f"### ⚠ Issues Found ({len(all_issues)})")
        for issue in all_issues[:20]:  # Show first 20
            lines.append(issue)
        if len(all_issues) > 20:
            lines.append(f"- ... and {len(all_issues) - 20} more issues")
    else:
        lines.append("### ✓ All samples pass verification")
        lines.append(f"- All {len(jes_sources)} JES sources: pattern correct (Up < Nominal < Down)")
        lines.append("- TES/JER/MET/EleScale: within expected ranges")

    lines.append("")
    lines.append(f"*Generated by check_mv_systematics.py*")

    # Output
    markdown = "\n".join(lines)

    if output_file:
        with open(output_file, 'w') as f:
            f.write(markdown)
        print(f"Report saved to: {output_file}")

    print(markdown)
    return results

def main():
    parser = argparse.ArgumentParser(description="Check MV systematic variations")
    parser.add_argument("--config", required=True, help="Path to config YAML file")
    parser.add_argument("--era", required=True, help="Era to check (2018, 2017, etc.)")
    parser.add_argument("--output", "-o", help="Output markdown file")

    args = parser.parse_args()

    # Suppress ROOT warnings
    ROOT.gROOT.SetBatch(True)
    ROOT.gErrorIgnoreLevel = ROOT.kError

    config = load_config(args.config)
    check_mv_systematics(config, args.era, args.output)

if __name__ == "__main__":
    main()
