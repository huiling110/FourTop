# Tasks: 1tau0l Workflow

## Active Config
- `analysis_config_1tau0l_XGB080test.yaml` - XGB080test (current)

---

## Status: XGB080test (Jan 5, 2026)

| Era | S1-2 OS/MV | S3 WH | S4.1 addJES | S4.2-4.3 | S4.4 datacard | S4.5 combine |
|-----|------------|-------|-------------|----------|---------------|--------------|
| 2018 | DONE | DONE | DONE | DONE | DONE | DONE |
| 2017 | DONE | DONE | DONE | DONE | DONE | DONE |
| 2016preVFP | DONE | DONE | DONE | DONE | DONE | DONE |
| 2016postVFP | DONE | DONE | DONE | DONE | DONE | DONE |

**Config:** `analysis_config_1tau0l_XGB080test.yaml`
**Hist version:** `v0BDT1tau0l_XGB080testNew`
**Template version:** `v3` (use `--template-version v3` for smooth/writeDatacard)
**Combine directory:** `hua/combine/combinationV22/run2_1tau0l_v4/`

## Results (V22)
- Observed significance: **0** (no excess)
- Expected significance: **0.176σ**
- Signal strength: r = 0.001 +5.816/-0.001

## Completed Steps
1. WH complete (nominal + systematics): ~7,864 files per era
2. Stage 4.1 (addJES): Completed
3. Stage 4.2 (addTemplate): Completed
4. Stage 4.3 (smooth): Completed with expanded systematics (pdf_00, btag_lf, TES, etc.)
5. Stage 4.4 (writeDatacard): Completed
6. Stage 4.4.1 (Run2 combination): Completed
7. Stage 4.5 (combine fits): Completed
8. Postfit plots: Generated

## Key Findings
- **pdf_00 smoothing**: Reduced bin 12 variation from +22.5%/-42.7% to +9.4%/-17.7%
- **Expected significance decreased** after smoothing (0.196 → 0.176) - unexpected
- Added expanded smoothing config: pdf_00, btag_lf, btag_cferr, TES, MET, SinglePion JES

## Output Locations
- Impacts: `hua/combine/combinationV22/run2_1tau0l_v4/combineResults/impactResult/impacts.pdf`
- Postfit: `hua/combine/combinationV22/run2_1tau0l_v4/combineResults/postfitPlots/`

## Last Updated
2026-01-05 10:25
