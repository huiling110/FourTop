# TTBB Integration Plan

**Last Updated**: 2025-12-07 12:25
**Status**: In Progress - Phase 5 (2018 complete, other years processing)

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

## Cross-Section Considerations

**Scaled from ttH(H→bb) AN**: σ_ttbb = 43.74 × (17.75/21.34) = 36.3 pb
- TTBB_4f_TTToHadronic: 16.52 pb (36.3 × 0.455)
- TTBB_4f_TTToSemiLeptonic: 15.97 pb (36.3 × 0.440)
- TTBB_4f_TTTo2L2Nu: 3.85 pb (36.3 × 0.106)
- **Total TTBB**: 36.3 pb

**TODO for final fit**:
1. **Verify cross-sections**: Check against XSDB or MC production cards
2. **Float TTBB normalization**: Add rate parameter in datacard to float TTBB in final fit
3. **Consider theory uncertainty**: TTBB cross-section has large theory uncertainty (~30-50%)
4. **Correlation with ttbar**: Decide if TTBB and ttbar normalizations should be correlated

**Implementation in datacard**:
```
# Add rate parameter for TTBB normalization
rateParam_ttbb rateParam * ttbb 1.0 [0.5,2.0]
```

## Reference

- Paper methodology: [JHEP02(2025)097](https://doi.org/10.1007/JHEP02(2025)097)
- Full plan: `/afs/ihep.ac.cn/users/h/huahuil/.claude/plans/temporal-toasting-biscuit.md`
