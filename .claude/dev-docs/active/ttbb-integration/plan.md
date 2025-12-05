# TTBB Integration Plan

**Last Updated**: 2025-12-05 18:00
**Status**: In Progress - Phase 5 (Re-running Stage 1 with corrected ghost-matching)

## Overview

Add TTBB (tt+bb) samples to the Four-Top analysis with proper overlap removal from inclusive ttbar samples.

## User Requirements

1. Subtract TTBB from ttbar based on particle-level jet flavor (≥1 additional b-jet not from top decays)
2. Keep TTBB as separate process category ('ttbb')
3. Process all Run2 years (2016preVFP, 2016postVFP, 2017, 2018)
4. Include in all channels (1tau0l, 1tau1l, 1tau2l)

## Implementation Strategy

### Overlap Handling

**Approach**: CMS Standard Ghost-Matching (from ttH paper)
- Use GenJets with `hadronFlavour == 5` (b-jets identified via ghost-matching)
- GenJet requirements: pT > 20 GeV, |η| < 2.4
- Match B-hadrons to GenJets (ΔR < 0.4), trace ancestry to check if from top
- For ttbar: REMOVE events with ≥1 additional b-jet (covered by TTBB)
- For TTBB: KEEP ONLY events with ≥1 additional b-jet (correct phase space)

### Phases

1. **Documentation Update** - Update ANALYSIS_WORKFLOW.md, create dev-docs
2. **Sample Preparation** - Create symlinks, calculate genSumWeights
3. **Configuration Updates** - Cross-sections, process groupings, genSumMap
4. **Overlap Subtraction** - Implement in copyBranch.C
5. **Full Processing** - Run Stages 1-4 for all years/channels
6. **Datacard Updates** - Add TTBB normalization uncertainty

## Key Decisions

| Decision | Choice | Rationale |
|----------|--------|-----------|
| Overlap threshold | ≥1 additional b-jet | More aggressive removal for cleaner separation |
| Implementation stage | Stage 1 (objectSelection) | Cleanest approach, no negative bins |
| TTBB grouping | Separate 'ttbb' category | Better visibility, separate uncertainty |

## Reference

- Paper methodology: [JHEP02(2025)097](https://doi.org/10.1007/JHEP02(2025)097)
- Full plan: `/afs/ihep.ac.cn/users/h/huahuil/.claude/plans/temporal-toasting-biscuit.md`
