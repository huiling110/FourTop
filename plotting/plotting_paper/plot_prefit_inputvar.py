#!/usr/bin/env python3
"""
Prefit input variable plotter using combine FitDiagnostics output.

Key differences from plot_postfit_histograms.py:
  - Linear y-axis (not log) - appropriate for input variable distributions
  - No event counts in legend - cleaner for publication
  - Variable name as x-axis label

VERSION: 1.0 (2026-01-25)

FEATURES:
    - Reads shapes_prefit from fitDiagnostics.root (same format as BDT)
    - Same CMS publication styling as plot_postfit_histograms.py
    - Auto-detects channel format and combines years
    - Automatic legend positioning based on histogram shape

Usage:
    # Single channel
    python plot_prefit_inputvar.py fitDiagnostics.root \\
        --variable tausT_1pt --channels SR1tau0l --output-dir ./plots

    # Multiple channels (for Run2 combination)
    python plot_prefit_inputvar.py fitDiagnostics_run2.root \\
        --variable tausT_1pt --channels SR1tau0l SR1tau1l SR1tau2l

Arguments:
    input_file          Path to fitDiagnostics ROOT file (required)
    --variable          Variable name for x-axis label (default: tausT_1pt)
    --channels          List of channels to plot (default: SR1tau0l)
    --output-dir        Output directory (default: ./plots)
"""

import argparse
import os
import uproot
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.lines import Line2D


# =============================================================================
# COLOR SCHEME - Consistent across all analysis plots
# =============================================================================
COLORS = {
    'tttt': '#0066CC',      # Deep blue (signal - stands out)
    'tt': '#CC3333',        # Dark red
    'ttbb': '#A52A2A',      # Brown/maroon
    'ttX': '#98df8a',       # Light green (combined ttH+ttW+ttZ)
    'fakeTau': '#FFBB33',   # Golden yellow
    'fakeLepton': '#FFAAA0', # Light coral/salmon
    'ttH': '#98df8a',       # Same as ttX
    'ttW': '#98df8a',
    'ttZ': '#98df8a',
    'WJets': '#E07000',     # Darker orange
    'singleTop': '#FF6B6B', # Light red
    'Minor': '#FFD700',     # Gold
}

LEGEND_LABELS = {
    'fakeTau': r'Fake $\tau_{\mathrm{h}}$', 'ttbb': r'$t\bar{t}b\bar{b}$',
    'tt': r'$t\bar{t}$', 'ttX': r'$t\bar{t}X$', 'ttH': r'$t\bar{t}H$',
    'ttW': r'$t\bar{t}W$', 'ttZ': r'$t\bar{t}Z$', 'fakeLepton': 'Fake lepton',
    'tttt': r'$t\bar{t}t\bar{t}$', 'WJets': 'W+jets', 'singleTop': 'Single top',
    'Minor': 'Minor bkg.',
}

CHANNEL_LABELS = {
    'SR1tau1l': r'$1\tau_{\mathrm{h}}1\ell$ SR', 'CR121tau1l': r'$1\tau_{\mathrm{h}}1\ell$ CR1',
    'SR1tau0l': r'$1\tau_{\mathrm{h}}0\ell$ SR', 'CRMR1tau0l': r'$1\tau_{\mathrm{h}}0\ell$ MR',
    'VR1tau0l': r'$1\tau_{\mathrm{h}}0\ell$ VR', 'SR1tau2l': r'$1\tau_{\mathrm{h}}2\ell$ SR',
    'CR31tau2l': r'$1\tau_{\mathrm{h}}2\ell$ CR2',
}

# X-axis labels for input variables
VARIABLE_LABELS = {
    'tausT_1pt': r'$\tau_{\mathrm{h}}$ $p_{\mathrm{T}}$ [GeV]',
    'tausF_1jetPt': r'$\tau_{\mathrm{h}}$ jet $p_{\mathrm{T}}$ [GeV]',
    'jets_HT': r'$H_{\mathrm{T}}$ [GeV]',
    'MET_pt': r'$p_{\mathrm{T}}^{\mathrm{miss}}$ [GeV]',
    'bjetsM_num': r'Number of b-jets',
    'jets_num': r'Number of jets',
    'tausT_1eta': r'$\tau_{\mathrm{h}}$ $\eta$',
    'tausT_1decayMode': r'$\tau_{\mathrm{h}}$ decay mode',
    'lepsT_1pt': r'Lepton $p_{\mathrm{T}}$ [GeV]',
    'lepsT_1eta': r'Lepton $\eta$',
    'bjetsM_1pt': r'Leading b-jet $p_{\mathrm{T}}$ [GeV]',
    'jets_1pt': r'Leading jet $p_{\mathrm{T}}$ [GeV]',
    'tausT_prongNum': r'$\tau_{\mathrm{h}}$ prong number',
    'tausF_1prongNum': r'$\tau_{\mathrm{h}}$ prong number',
    'tausF_1jetEtaAbs': r'$\tau_{\mathrm{h}}$ jet $|\eta|$',
    'tausT_1jetEtaAbs': r'$\tau_{\mathrm{h}}$ jet $|\eta|$',
}

# Original binning for input variables (combine FitDiagnostics loses this info)
# Format: (variable, region_pattern) -> bin_edges
# region_pattern: 'SR', 'CRMR', 'VR', 'CR2', 'CR3', or None for all regions
VARIABLE_BINNING = {
    # tausF_1jetPt: 10 bins, 0-200 GeV (20 GeV bins)
    ('tausF_1jetPt', None): np.linspace(0, 200, 11),
    # tausT_1pt: 10 bins, 0-200 GeV
    ('tausT_1pt', None): np.linspace(0, 200, 11),
    # jets_HT: 10 bins, 400-2000 GeV
    ('jets_HT', None): np.linspace(400, 2000, 11),
    # tausF_1prongNum: 10 bins, shift by -0.5 so prong 1,3 appear at 1,3 not 1.5,3.5
    ('tausF_1prongNum', None): np.linspace(-0.5, 9.5, 11),
    # tausT_prongNum: 10 bins, shift by -0.5
    ('tausT_prongNum', None): np.linspace(-0.5, 9.5, 11),
    # tausF_1jetEtaAbs: 5 bins, 0-2.4
    ('tausF_1jetEtaAbs', None): np.linspace(0, 2.4, 6),
    # tausT_1jetEtaAbs: 5 bins, 0-2.4
    ('tausT_1jetEtaAbs', None): np.linspace(0, 2.4, 6),
    # bjetsM_num: 8 bins, -0.5 to 7.5 (integer bins 0-7)
    ('bjetsM_num', None): np.linspace(-0.5, 7.5, 9),
}

# X-axis display limits (for zooming into relevant range)
# Format: variable -> (xmin, xmax)
VARIABLE_XLIM = {
    'tausF_1prongNum': (0.5, 3.5),  # Only prong 1 and 3 are populated
    'tausT_prongNum': (0.5, 3.5),
    'tausF_1jetEtaAbs': (0, 2.4),
    'tausT_1jetEtaAbs': (0, 2.4),
    'bjetsM_num': (0.5, 3.5),  # Show b-jet multiplicities 1-3
}

def get_original_binning(variable, channel):
    """Get original bin edges for a variable/channel combination."""
    # Extract region from channel (e.g., 'VR1tau0l' -> 'VR')
    region = None
    for r in ['SR', 'CRMR', 'VR', 'CR2', 'CR3', 'CR12']:
        if channel.startswith(r):
            region = r
            break

    # Try specific region first, then fall back to general
    if (variable, region) in VARIABLE_BINNING:
        return VARIABLE_BINNING[(variable, region)]
    if (variable, None) in VARIABLE_BINNING:
        return VARIABLE_BINNING[(variable, None)]
    return None


def load_channel_data(root_file, shapes_dir, channel_base, years, processes):
    """Load and sum histograms across years."""
    shapes = root_file[shapes_dir]
    combined = {'data': None, 'processes': {}, 'total': None, 'total_err': None, 'edges': None}

    for year in years:
        # Try both naming conventions:
        # 1. Simple format from writeDatacard.py: SR1tau0l_2018
        # 2. Doubled format from writeCombinationDatacard.py: SR1tau0l_SR1tau0l_2018
        ch_name_simple = f"{channel_base}_{year}"
        ch_name_doubled = f"{channel_base}_{channel_base}_{year}"

        ch_dir = None
        for ch_name in [ch_name_simple, ch_name_doubled]:
            try:
                ch_dir = shapes[ch_name]
                break
            except KeyError:
                continue

        if ch_dir is None:
            continue

        # Data (TGraphAsymmErrors)
        try:
            data_obj = ch_dir['data']
            data_vals = np.array(data_obj.member('fY')) if hasattr(data_obj, 'member') else data_obj.values()
            combined['data'] = data_vals.copy() if combined['data'] is None else combined['data'] + data_vals
        except:
            pass

        # Processes
        for proc in processes:
            try:
                hist = ch_dir[proc]
                vals, edges = hist.to_numpy() if hasattr(hist, 'to_numpy') else (hist.values(), hist.axis().edges())
                if combined['edges'] is None:
                    combined['edges'] = edges
                combined['processes'][proc] = vals.copy() if proc not in combined['processes'] else combined['processes'][proc] + vals
            except:
                pass

        # Total and covariance
        try:
            total_hist = ch_dir['total']
            total_vals, edges = total_hist.to_numpy()
            if combined['edges'] is None:
                combined['edges'] = edges
            combined['total'] = total_vals.copy() if combined['total'] is None else combined['total'] + total_vals

            try:
                covar = ch_dir['total_covar'].values()
                var = np.diag(covar)
                combined['total_err'] = var.copy() if combined['total_err'] is None else combined['total_err'] + var
            except:
                pass
        except:
            pass

    if combined['total_err'] is not None:
        combined['total_err'] = np.sqrt(combined['total_err'])

    return combined


def plot_channel(data, channel, variable, output_dir):
    """Create prefit variable plot - linear y-axis, no counts in legend."""

    # Publication-quality font sizes (optimized for multi-panel figures)
    plt.rcParams.update({
        'font.family': 'serif',
        'font.size': 16,
        'axes.labelsize': 22,
        'xtick.labelsize': 18,
        'ytick.labelsize': 18,
        'xtick.direction': 'in',
        'ytick.direction': 'in',
        'xtick.top': True,
        'ytick.right': True,
        'xtick.major.size': 8,
        'ytick.major.size': 8,
        'xtick.minor.size': 4,
        'ytick.minor.size': 4,
    })

    fig, (ax_main, ax_ratio) = plt.subplots(2, 1, figsize=(8, 8),
                                             gridspec_kw={'height_ratios': [3, 1], 'hspace': 0.05},
                                             sharex=True)

    # Get original binning if available (combine FitDiagnostics loses x-axis info)
    original_edges = get_original_binning(variable, channel)
    edges = data['edges']
    n_bins = len(data['total'])

    # Use original binning if available and bin count matches
    if original_edges is not None and len(original_edges) == len(edges):
        edges = original_edges
        print(f"  Using original binning: {edges[0]:.1f} to {edges[-1]:.1f}")

    bin_centers = (edges[:-1] + edges[1:]) / 2
    data_vals = data['data']
    total_vals = data['total']

    # Combine ttH, ttW, ttZ into ttX
    ttX_vals = np.zeros(n_bins)
    for proc in ['ttH', 'ttW', 'ttZ']:
        if proc in data['processes']:
            ttX_vals += data['processes'][proc]
    if np.sum(ttX_vals) > 0.01:
        data['processes']['ttX'] = ttX_vals

    # Stack order: bottom to top (smallest to largest background)
    stack_order = ['tttt', 'Minor', 'singleTop', 'WJets', 'fakeLepton', 'ttX', 'tt', 'ttbb', 'fakeTau']

    # Build stacks
    cumulative = np.zeros(n_bins)
    plotted_procs = []

    for proc in stack_order:
        if proc not in data['processes']:
            continue
        vals = data['processes'][proc]
        if np.sum(vals) < 0.01:
            continue

        color = COLORS.get(proc, '#888888')
        ax_main.bar(bin_centers, vals, width=np.diff(edges), bottom=cumulative,
                   color=color, edgecolor='black', linewidth=0.5)
        cumulative += vals
        plotted_procs.append((proc, np.sum(vals)))

    # Uncertainty band
    if data['total_err'] is not None:
        for i in range(n_bins):
            ax_main.fill_between([edges[i], edges[i+1]],
                                [total_vals[i] - data['total_err'][i]]*2,
                                [total_vals[i] + data['total_err'][i]]*2,
                                color='gray', alpha=0.3, hatch='///', linewidth=0)

    # Data points
    data_err = np.sqrt(data_vals)
    ax_main.errorbar(bin_centers, data_vals, yerr=data_err, fmt='ko',
                    markersize=8, capsize=0, zorder=10, elinewidth=1.5)

    # === STYLING ===
    max_val = max(data_vals.max(), total_vals.max())

    # Determine legend position based on where histogram is lower
    third = max(1, len(total_vals) // 3)
    left_region_max = total_vals[:third].max() if third > 0 else total_vals.max()
    right_region_max = total_vals[-third:].max() if third > 0 else total_vals.max()

    if right_region_max < left_region_max:
        legend_loc = 'upper right'
        legend_bbox = (0.98, 0.98)
    else:
        legend_loc = 'upper left'
        legend_bbox = (0.02, 0.98)

    # === KEY CHANGE 1: Linear y-axis ===
    ax_main.set_ylim(0, max_val * 1.6)  # 60% headroom for legend
    # Use custom xlim if defined for this variable
    if variable in VARIABLE_XLIM:
        ax_main.set_xlim(*VARIABLE_XLIM[variable])
    else:
        ax_main.set_xlim(edges[0], edges[-1])
    ax_main.set_ylabel('Events', fontsize=22, fontweight='medium')
    ax_main.tick_params(axis='x', labelbottom=False)
    ax_main.yaxis.grid(True, linestyle='-', alpha=0.2, which='major')

    # CMS label and luminosity
    ax_main.text(0.0, 1.01, r'$\mathbf{CMS}$', transform=ax_main.transAxes,
                fontsize=24, fontweight='bold', va='bottom', ha='left')
    ax_main.text(1.0, 1.01, r'138 fb$^{-1}$ (13 TeV)', transform=ax_main.transAxes,
                fontsize=18, va='bottom', ha='right')

    # Channel label (top left, below CMS) - region and Pre-fit on separate lines
    channel_text = f"{CHANNEL_LABELS.get(channel, channel)}\nPre-fit"
    ax_main.text(0.02, 0.95, channel_text, transform=ax_main.transAxes,
                fontsize=18, va='top', ha='left', fontweight='medium',
                bbox=dict(boxstyle='round,pad=0.3', facecolor='white', alpha=0.85, edgecolor='none'))

    # === KEY CHANGE 2: No event counts in legend ===
    legend_handles = []
    for proc, yield_sum in reversed(plotted_procs):
        legend_handles.append(
            mpatches.Patch(facecolor=COLORS.get(proc, '#888888'), edgecolor='black', linewidth=0.5,
                          label=LEGEND_LABELS.get(proc, proc))  # No [yield]
        )

    # Uncertainty in legend
    legend_handles.append(
        mpatches.Patch(facecolor='gray', alpha=0.3, hatch='///', edgecolor='gray',
                      label='Pre-fit unc.')
    )

    # Data in legend (no count)
    legend_handles.append(
        Line2D([0], [0], marker='o', color='w', markerfacecolor='black', markersize=10,
              label='Data')
    )

    ax_main.legend(handles=legend_handles, loc=legend_loc, ncol=2, frameon=True,
                  fancybox=False, edgecolor='none', framealpha=0.9, fontsize=17,
                  columnspacing=0.8, handletextpad=0.5, labelspacing=0.4,
                  bbox_to_anchor=legend_bbox)

    # === RATIO PANEL ===
    ratio = np.divide(data_vals, total_vals, out=np.ones_like(data_vals), where=total_vals > 0)
    ratio_err = np.divide(data_err, total_vals, out=np.zeros_like(data_err), where=total_vals > 0)
    ax_ratio.errorbar(bin_centers, ratio, yerr=ratio_err, fmt='ko', markersize=8, capsize=0, elinewidth=1.5)

    # Uncertainty band in ratio
    if data['total_err'] is not None:
        rel_err = np.divide(data['total_err'], total_vals, out=np.zeros_like(data['total_err']), where=total_vals > 0)
        for i in range(n_bins):
            ax_ratio.fill_between([edges[i], edges[i+1]], [1 - rel_err[i]]*2, [1 + rel_err[i]]*2,
                                 color='gray', alpha=0.3, hatch='///', linewidth=0)

    ax_ratio.axhline(y=1, color='black', linestyle='-', linewidth=1)
    # Use custom xlim if defined for this variable
    if variable in VARIABLE_XLIM:
        ax_ratio.set_xlim(*VARIABLE_XLIM[variable])
    else:
        ax_ratio.set_xlim(edges[0], edges[-1])
    ax_ratio.set_ylim(0.5, 1.5)

    # === KEY CHANGE 3: Variable name as x-axis label ===
    ax_ratio.set_xlabel(VARIABLE_LABELS.get(variable, variable), fontsize=22, fontweight='medium')
    ax_ratio.set_ylabel('Data/Pred.', fontsize=18)
    ax_ratio.set_yticks([0.6, 0.8, 1.0, 1.2, 1.4])
    ax_ratio.yaxis.grid(True, linestyle='-', alpha=0.2)

    # === KEY CHANGE 4: Output filename with variable ===
    os.makedirs(output_dir, exist_ok=True)
    for ext in ['pdf', 'png']:
        plt.savefig(os.path.join(output_dir, f'prefit_inputvar_{channel}_{variable}.{ext}'),
                   dpi=300, bbox_inches='tight', facecolor='white')
    plt.close()

    return int(np.sum(data_vals)), np.sum(total_vals)


def main():
    parser = argparse.ArgumentParser(
        description='Plot prefit input variable distributions from combine FitDiagnostics output.',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
    python plot_prefit_inputvar.py fitDiagnostics.root --variable tausT_1pt --channels SR1tau0l
    python plot_prefit_inputvar.py fitDiagnostics.root --variable jets_HT --channels SR1tau0l SR1tau1l
        """
    )
    parser.add_argument('input_file', help='Path to fitDiagnostics ROOT file')
    parser.add_argument('--variable', default='tausT_1pt',
                       help='Variable name for x-axis label (default: tausT_1pt)')
    parser.add_argument('--channels', nargs='+', default=['SR1tau0l'],
                       help='Channel(s) to plot (default: SR1tau0l)')
    parser.add_argument('--output-dir', default='./plots',
                       help='Output directory (default: ./plots)')
    args = parser.parse_args()

    root_file = uproot.open(args.input_file)
    years = ['2016preVFP', '2016postVFP', '2017', '2018']

    # Process lists by channel type
    procs_1tau1l = ['tt', 'ttbb', 'ttH', 'ttW', 'ttZ', 'fakeTau', 'fakeLepton', 'tttt']
    procs_1tau0l = ['tt', 'ttbb', 'ttH', 'ttW', 'ttZ', 'fakeTau', 'WJets', 'singleTop', 'tttt']
    procs_1tau2l = ['ttH', 'ttW', 'ttZ', 'fakeTau', 'fakeLepton', 'Minor', 'tttt']

    channel_procs = {
        'SR1tau1l': procs_1tau1l, 'CR121tau1l': procs_1tau1l,
        'SR1tau0l': procs_1tau0l, 'CRMR1tau0l': procs_1tau0l, 'VR1tau0l': procs_1tau0l,
        'SR1tau2l': procs_1tau2l,
    }

    print(f"\n{'='*60}")
    print(f"Prefit Input Variable: {args.variable}")
    print(f"{'='*60}")

    for channel in args.channels:
        processes = channel_procs.get(channel, procs_1tau0l)
        data = load_channel_data(root_file, 'shapes_prefit', channel, years, processes)

        if data['total'] is None:
            print(f"  {channel}: No data found")
            continue

        data_n, total_n = plot_channel(data, channel, args.variable, args.output_dir)
        print(f"{channel:12}: Data={data_n:5}, Total={total_n:.1f}")

    print(f"\nPlots saved to: {args.output_dir}")


if __name__ == '__main__':
    main()
