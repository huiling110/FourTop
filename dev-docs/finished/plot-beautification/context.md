# Plot Beautification - Context

## Goal
Create publication-quality post-fit and pre-fit BDT plots for paper submission.

## Key Files
- `plotting/pl_postFit.py` - Post-fit plotting script
- `plotting/pl.py` - Main plotting functions (makeStackPlotNew, addLegend)
- `fourtop/plotting/style.py` - ROOT styling functions
- `fourtop/plotting/labels.py` - NEW: Label mappings for paper

## Example Plot
`hua/combine/combinationV22/run2_3channels_v4/combineResults/postfitResult/postfitPlots/SR1tau2l_BDT_logy_BDT_SR1tau2l_fit_s_Run2.png`

## Environment
```bash
source setEnv_newNew.sh
```

## Paper Conventions (User Requirements)
| Element | Convention |
|---------|------------|
| ttX label | Keep as "ttX" |
| fakeTau | "fake τ_h" (`fake #tau_{h}`) |
| Signal | "tt̄tt̄ × 100" |
| CMS label | "CMS" only (no Preliminary) |
| Region labels | Add "SR 1τ₀ℓ" etc. on plot |
| Fit type | Add "Pre-fit" or "Post-fit" text |
| Output | Save to `publication/` subfolder |

## Critical Notes
- Don't modify existing plots - create in `publication/` subfolder
- Show yields in legend brackets
- Keep S/B text as optional parameter
- Reduce ratio y-axis divisions (less crowded)
