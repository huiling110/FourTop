# tttt/VLL Analysis Plotting Scripts

Publication-quality plotting scripts for the four-top quark (tttt) and vector-like lepton (VLL) searches from the 4321 model.

**Last Updated:** 2025-01-25  
**Author:** Huiling  
**Analysis:** CMS TOP-24-017

---

## Quick Start

```bash
# Install dependencies
pip install numpy matplotlib uproot

# Generate VLL BDT plots for all regions
python plot_postfit_histograms.py fitDiagnostics.root --analysis vll --mass 600 \
    --channels SR1tau0l CRMR1tau0l VR1tau0l SR1tau1l CR121tau1l SR1tau2l

# Generate tttt BDT plots for signal regions
python plot_postfit_histograms.py fitDiagnostics.root --analysis tttt \
    --channels SR1tau0l SR1tau1l SR1tau2l

# Generate prefit input variable distributions
python plot_prefit_variables.py combined.root --variable tausF_1jetPt tausT_1pt \
    --channels 1tau0lCRMR 1tau0lVR
```

---

## Scripts Overview

| Script | Purpose | Input | Output |
|--------|---------|-------|--------|
| `plot_postfit_histograms.py` | BDT distributions (pre/post-fit) | `fitDiagnostics.root` | PDF + PNG |
| `plot_prefit_variables.py` | Prefit input variable distributions | `combined_*.root` | PDF + PNG |
| `plot_vll_limits.py` | VLL mass exclusion limits (Brazil band) | `limits_VLL.json` | PDF + PNG |
| `plot_impacts_twopanel.py` | Nuisance parameter impacts | `impacts.json` | PDF + PNG |
| `plot_combined_results.py` | Signal strength + significance summary | (edit values in script) | PDF + PNG |
| `plot_region_definitions.py` | Analysis region definitions | (none) | PDF + PNG |
| `plot_pie_charts.py` | tttt decay channel breakdown | (none) | PDF + PNG |

---

## Dependencies

```bash
pip install numpy matplotlib uproot
# Optional for VLL limits interpolation:
pip install scipy
```

---

## 1. BDT Distribution Plots (`plot_postfit_histograms.py`)

**Version:** 2.0 (2025-01-25)

Unified script for both tttt (signal stacked) and VLL (signal as line overlay) analyses.
Optimized font sizes for 2×3 panel paper figures.

### Features
- Automatic legend positioning based on histogram shape
- Dynamic y-axis headroom to prevent legend overlap
- Combines ttH+ttW+ttZ → ttX automatically
- Channel-specific process lists
- VLL: prefit signal shape overlaid on postfit background-only fit

### Usage

```bash
# tttt analysis (signal stacked, uses shapes_fit_s)
python plot_postfit_histograms.py fitDiagnostics.root --analysis tttt \
    --channels SR1tau0l SR1tau1l SR1tau2l

# VLL analysis (signal as line, uses shapes_fit_b for backgrounds)
python plot_postfit_histograms.py fitDiagnostics.root --analysis vll --mass 600 \
    --channels SR1tau0l CRMR1tau0l VR1tau0l SR1tau1l CR121tau1l SR1tau2l

# Specific fit type only
python plot_postfit_histograms.py fitDiagnostics.root --analysis vll --mass 600 \
    --channels SR1tau1l --fit-types prefit

# Custom output directory
python plot_postfit_histograms.py fitDiagnostics.root --analysis tttt \
    --channels SR1tau1l --output-dir ./my_plots
```

### Arguments

| Argument | Description | Default |
|----------|-------------|---------|
| `input_file` | Path to fitDiagnostics ROOT file | (required) |
| `--analysis` | Analysis type: `tttt` or `vll` | `tttt` |
| `--mass` | VLL mass point in GeV | `600` |
| `--channels` | List of channels to plot | `['SR1tau1l']` |
| `--output-dir` | Output directory | `./plots` |
| `--fit-types` | Fit types: `prefit`, `postfit`, or both | `['prefit', 'postfit']` |

### Channels Available

| Channel | Label | Processes |
|---------|-------|-----------|
| `SR1tau0l` | 1τh0ℓ SR | tt, ttbb, ttX, fakeTau, WJets, singleTop, tttt |
| `CRMR1tau0l` | 1τh0ℓ MR | tt, ttbb, ttX, fakeTau, WJets, singleTop, tttt |
| `VR1tau0l` | 1τh0ℓ VR | tt, ttbb, ttX, fakeTau, WJets, singleTop, tttt |
| `SR1tau1l` | 1τh1ℓ SR | tt, ttbb, ttX, fakeTau, fakeLepton, tttt |
| `CR121tau1l` | 1τh1ℓ CR1 | tt, ttbb, ttX, fakeTau, fakeLepton, tttt |
| `SR1tau2l` | 1τh2ℓ SR | ttX, fakeTau, fakeLepton, Minor, tttt (no tt) |

### Output Files
```
tttt_{channel}_{prefit|postfit}.pdf/png
vll_m{mass}_{channel}_{prefit|postfit}.pdf/png
```

---

## 2. Prefit Input Variables (`plot_prefit_variables.py`)

**Version:** 2.0 (2025-01-25)

Plots prefit distributions of input variables (τh pT, HT, etc.) for control/validation regions.
Uses linear y-axis (not log) and matches postfit BDT style exactly.

### Usage

```bash
# Single variable, single channel
python plot_prefit_variables.py combined.root --variable tausF_1jetPt --channels 1tau0lCRMR

# Multiple variables and channels
python plot_prefit_variables.py combined.root --variable tausF_1jetPt tausT_1pt jets_HT \
    --channels 1tau0lSR 1tau0lCRMR 1tau0lVR

# All variables for a channel
python plot_prefit_variables.py combined.root --all-vars --channels 1tau0lCRMR

# All channels and variables
python plot_prefit_variables.py combined.root --all-vars --all-channels
```

### Arguments

| Argument | Description | Default |
|----------|-------------|---------|
| `input_file` | Path to ROOT file with shapes_prefit | (required) |
| `--variable`, `-v` | Variable(s) to plot | `['tausF_1jetPt']` |
| `--channels`, `-c` | Channel(s) to plot | `['1tau0lCRMR']` |
| `--all-vars` | Plot all available variables | `False` |
| `--all-channels` | Plot all available channels | `False` |
| `--output-dir`, `-o` | Output directory | `./plots` |

### Available Variables

| Variable | Label |
|----------|-------|
| `tausF_1jetPt` | Fake τh candidate jet pT [GeV] |
| `tausT_1pt` | τh pT [GeV] |
| `tausT_1eta` | τh η |
| `tausT_1decayMode` | τh decay mode |
| `tausT_prongNum` | τh prong number |
| `tausT_1jetEtaAbs` | τh jet \|η\| |
| `jets_HT` | HT [GeV] |

### Available Channels

| Channel | Label |
|---------|-------|
| `1tau0lSR` | 1τh0ℓ SR |
| `1tau0lCRMR` | 1τh0ℓ MR |
| `1tau0lVR` | 1τh0ℓ VR |
| `1tau1lSR` | 1τh1ℓ SR |
| `1tau1lCR12` | 1τh1ℓ CR1 |
| `1tau2lCR3` | 1τh2ℓ CR |

### Output Files
```
prefit_{channel}_{variable}.pdf/png
```

---

## 3. VLL Mass Limits (`plot_vll_limits.py`)

**Version:** 2.4 (2025-01-25)

Creates Brazil band exclusion limit plot for vector-like lepton search with 4321 model theory prediction.

### Usage

```bash
# Default orange style (recommended for paper)
python plot_vll_limits.py limits_VLL.json

# With exclusion mass marker
python plot_vll_limits.py limits_VLL.json --style orange_v2

# Standard CMS green/yellow Brazil band
python plot_vll_limits.py limits_VLL.json --style standard

# Hide exclusion line
python plot_vll_limits.py limits_VLL.json --no-exclusion-line
```

### Color Schemes

| Style | 68% Band | 95% Band | Use Case |
|-------|----------|----------|----------|
| `orange` | #FF9800 | #FFE082 | Paper (default) |
| `orange_v2` | #FF9800 | #FFECB3 | Paper with lighter 95% |
| `standard` | #00CC00 | #FFCC00 | CMS review compliance |

### JSON Input Format

```json
{
    "mass_points": [500, 550, 600, 650, 700, 750, 800],
    "theory_xs": [0.050, 0.030, 0.020, 0.013, 0.009, 0.006, 0.004],
    "observed_xs": [0.008, 0.005, 0.004, 0.003, 0.003, 0.002, 0.002],
    "expected_xs": [0.007, 0.004, 0.003, 0.003, 0.002, 0.002, 0.002],
    "expected_xs_1sigma_up": [...],
    "expected_xs_1sigma_down": [...],
    "expected_xs_2sigma_up": [...],
    "expected_xs_2sigma_down": [...]
}
```

---

## 4. Impact Plots (`plot_impacts_twopanel.py`)

Two-panel nuisance parameter impact plot (pulls + Δμ).

### Usage

```bash
# Default (top 20 parameters)
python plot_impacts_twopanel.py impacts.json

# Top 30 parameters
python plot_impacts_twopanel.py impacts.json --top 30

# Custom colors and output
python plot_impacts_twopanel.py impacts.json --top 25 -o my_impacts \
    --color-up '#CC3333' --color-down '#FF9900'
```

### Arguments

| Argument | Description | Default |
|----------|-------------|---------|
| `json_file` | Path to impacts.json | (required) |
| `--top`, `-n` | Number of parameters to show | `20` |
| `--output`, `-o` | Output filename prefix | `impacts_top{n}` |
| `--color-up` | Color for +1σ impact | `#CC3333` |
| `--color-down` | Color for -1σ impact | `#FF9900` |

---

## 5. Combined Results (`plot_combined_results.py`)

Signal strength and significance summary plot for all channels.

### Usage

```bash
# Default CMS style
python plot_combined_results.py

# Ultra-minimal Tufte style
python plot_combined_results.py --style tufte

# Custom output
python plot_combined_results.py -o my_results
```

**Note:** Edit the data values directly in the script before running:
```python
# Signal strength values (μ = σ/σ_SM)
r_observed = [0.00, 1.21, 1.44, 1.21]
r_obs_err_up = [5.88, 2.20, 1.97, 1.35]
r_obs_err_down = [0.00, 2.11, 1.34, 1.10]

# Significance values (in standard deviations)
sig_expected = [0.17, 0.54, 0.80, 0.99]
sig_observed = [0.00, 0.57, 0.96, 1.05]
```

---

## 6. Region Definitions (`plot_region_definitions.py`)

Schematic showing SR, CR, VR, MR regions in njet vs nb-jet space.

### Usage

```bash
python plot_region_definitions.py
python plot_region_definitions.py -o my_regions
```

---

## 7. Pie Charts (`plot_pie_charts.py`)

tttt decay channel breakdown pie charts.

### Usage

```bash
python plot_pie_charts.py
python plot_pie_charts.py -o my_pies
```

### Output Files
```
pie_tttt_channels.pdf/png    # All tttt decay channels
pie_tau_channels.pdf/png     # ≥1τh subcategories
```

---

## 8. Prefit Input Variables from Combine (`plot_prefit_inputvar.py`)

**Version:** 1.0 (2026-01-25)

Plots prefit distributions of input variables from combine FitDiagnostics output.
Uses **linear y-axis** and **no event counts in legend** (different from BDT plots).
Same CMS publication styling as `plot_postfit_histograms.py`.

### Key Differences from BDT Plots

| Aspect | BDT (`plot_postfit_histograms.py`) | Input Variables (`plot_prefit_inputvar.py`) |
|--------|-----------------------------------|---------------------------------------------|
| Y-axis | Logarithmic | Linear |
| Legend | Shows event counts `[N]` | No counts (cleaner for publication) |
| X-label | "BDT score" | Variable name (e.g., "τh pT [GeV]") |
| Input | fitDiagnostics.root | fitDiagnostics.root (same format) |

### Usage

```bash
# Single channel, single variable
python plot_prefit_inputvar.py fitDiagnostics.root \
    --variable tausT_1pt --channels SR1tau0l --output-dir ./plots

# Multiple channels (Run2 combination)
python plot_prefit_inputvar.py fitDiagnostics_run2.root \
    --variable tausT_1pt --channels SR1tau0l SR1tau1l SR1tau2l
```

### Arguments

| Argument | Description | Default |
|----------|-------------|---------|
| `input_file` | Path to fitDiagnostics ROOT file | (required) |
| `--variable` | Variable name for x-axis label | `tausT_1pt` |
| `--channels` | Channel(s) to plot | `['SR1tau0l']` |
| `--output-dir` | Output directory | `./plots` |

### Available Variables (x-axis labels)

| Variable | Label |
|----------|-------|
| `tausT_1pt` | τh pT [GeV] |
| `jets_HT` | HT [GeV] |
| `MET_pt` | pTmiss [GeV] |
| `bjetsM_num` | Number of b-jets |
| `jets_num` | Number of jets |
| `tausT_1eta` | τh η |
| `tausT_1decayMode` | τh decay mode |
| `lepsT_1pt` | Lepton pT [GeV] |

### Workflow

1. Run WH with `--mode variables` (Stage 3)
2. Run addJES, addTemplate, writeDatacard (Stage 4.1-4.4)
3. Create Run2 combination with combineCards.py
4. Run FitDiagnostics with `--saveShapes --saveWithUncertainties`
5. Run this script to plot prefit distributions

### Output Files
```
prefit_inputvar_{channel}_{variable}.pdf/png
```

---

## Color Scheme

Consistent colors across all plots:

| Process | Color | Hex |
|---------|-------|-----|
| tt̄ | Dark red | `#CC3333` |
| tt̄bb̄ | Brown/maroon | `#A52A2A` |
| Fake τh | Golden yellow | `#FFBB33` |
| Fake lepton | Light coral | `#FFAAA0` |
| tt̄X | Light green | `#98df8a` |
| tt̄tt̄ | Deep blue | `#0066CC` |
| Minor | Gold | `#FFD700` |
| W+jets | Dark orange | `#E07000` |
| Single top | Light red | `#FF6B6B` |
| Multijet (data) | Purple | `#9467bd` |
| VLL signal | Magenta | `#FF00FF` |

### Stacking Order (bottom to top)
```
tttt → Minor → singleTop → WJets → fakeLepton → ttX → tt → ttbb → jetHT → fakeTau
```

---

## Example Workflow

```bash
# 1. Generate all tttt BDT plots
python plot_postfit_histograms.py fitDiagnostics_tttt.root --analysis tttt \
    --channels SR1tau0l SR1tau1l SR1tau2l --output-dir tttt_plots/

# 2. Generate all VLL BDT plots
python plot_postfit_histograms.py fitDiagnostics_vll.root --analysis vll --mass 600 \
    --channels SR1tau0l CRMR1tau0l VR1tau0l SR1tau1l CR121tau1l SR1tau2l \
    --output-dir vll_plots/

# 3. Generate prefit input variable plots
python plot_prefit_variables.py combined_allChannels_run2.root \
    --variable tausF_1jetPt tausT_1pt jets_HT \
    --channels 1tau0lCRMR 1tau0lVR 1tau1lCR12 --output-dir prefit_plots/

# 4. Generate VLL mass limits (all three styles for comparison)
python plot_vll_limits.py limits_VLL.json --style orange -o vll_limit_orange
python plot_vll_limits.py limits_VLL.json --style standard -o vll_limit_standard

# 5. Generate impact plot
python plot_impacts_twopanel.py impacts.json --top 25 -o impacts_top25

# 6. Generate auxiliary plots
python plot_region_definitions.py
python plot_pie_charts.py
python plot_combined_results.py
```

---

## Tips for Claude Code

When using these scripts with Claude Code:

1. **Direct editing**: Claude Code can modify scripts in place without upload/download cycles

2. **Quick iteration**: Ask for small tweaks like:
   - "Increase the CMS label font size to 26"
   - "Change ttbb color to darker brown"
   - "Move the legend to upper left"

3. **Batch processing**: Run multiple plots with shell commands:
   ```bash
   for mass in 500 550 600 650 700; do
       python plot_postfit_histograms.py fitDiag_m${mass}.root \
           --analysis vll --mass $mass --channels SR1tau1l
   done
   ```

4. **Version control**: After changes, commit with meaningful messages:
   ```bash
   git add plot_postfit_histograms.py
   git commit -m "Increase font sizes for 2x3 panel figures"
   ```

---

## Notes

- **tttt analysis**: Uses `shapes_fit_s` (signal+background fit) for postfit
- **VLL analysis**: Uses `shapes_fit_b` (background-only fit) for postfit, with prefit VLL signal overlaid
- **1tau2l channel**: Does not include tt process (different background composition)
- **Path format**: tttt uses `{channel}_{channel}_{year}`, VLL uses `{channel}_{year}`
- **All scripts output both PDF and PNG** at 300 DPI
