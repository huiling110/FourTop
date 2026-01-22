# Workflow Fix with XGB080test as Real Example

## Goal
Run full workflow for `analysis_config_1tau1l_XGB080test.yaml` across all 4 years with full systematics, using this as a learning exercise to improve workflow code and Claude Code setup.

## Config Info
- **Stage 1**: `v95XGB080testOS7` (CentOS7 mode for XGBoost 0.80)
- **Stage 2**: `v1baselineHadro`
- **Hist**: `v0BDT1tau1l_XGB080testNew`
- **Channel**: 1tau1l
- **Systematics**: FULL (TES×8, JER×2, MET×2, EleScale×2, JES×60)

## Workflow Stages (per era)
1. Stage 1 (OS) → Stage 1.1 (OS systematics - 15 variations)
2. Stage 2 (MV) → Stage 2.1 (MV systematics)
3. Stage 2.4 (Fake tau/lepton backgrounds)
4. Stage 3 (WH) with `--systematic complete` (~4,437 files per era)
5. Stage 4: addJES → addTemplate → smooth → writeDatacard → Run2 combine → fits

## Code Improvements
- Fix CLAUDE.md Stage 2.4 location (plotting/ → makeVariables_goodCode/)
- Create .claude/hooks/README.md
- Update pre-tool-use.sh patterns
- Add output validation helpers

## Full Plan
See: `~/.claude/plans/streamed-plotting-conway.md`
