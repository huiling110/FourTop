# Plan: [Task Name]

**Created**: YYYY-MM-DD
**Status**: [Active | Completed | Blocked]
**Owner**: [Your name or "Claude Code"]

---

## Goal

[1-2 sentences describing what you're trying to achieve]

Example:
> Integrate VLL_M850 signal sample into 1tau1l analysis for Run2 combination

---

## Background

[Brief context - why are we doing this?]

Example:
> Need to extend VLL search mass range to 850 GeV to improve sensitivity to high-mass BSM signals

---

## Approach

[High-level strategy - how will you achieve the goal?]

Example:
1. Locate VLL_M850 NanoAOD samples on /publicfs
2. Add input file paths to inputFiles/ configuration
3. Update process list in run_treeAnalyzer.C
4. Submit nominal + systematic variation jobs
5. Validate event counts and distributions
6. Integrate into combine datacards
7. Re-run statistical analysis (limits, significance)

---

## Technical Details

[Important technical considerations]

Example:
- **Version**: Using v8BDT1tau1lV19 for consistency with other masses
- **Systematics**: Apply same variations as VLL_M500-800
- **Cross-section**: σ(VLL_M850) = 0.XXX pb (from theory)
- **Files**: ~50k events expected per era

---

## Validation Plan

[How will you verify success?]

Example:
- [ ] Event counts match DAS query results
- [ ] Systematic variations produce expected ±X% changes
- [ ] BDT distributions similar shape to other VLL masses
- [ ] Combine runs without errors
- [ ] Expected limits within reasonable range of M800

---

## Open Questions

[Things you need to figure out or decisions to make]

Example:
- Which BDT training to use? (v8BDT or retrain including M850?)
- Should we re-optimize event selection for higher mass?

---

## Timeline / Milestones

[Optional: High-level phases, not specific dates]

Example:
1. **Phase 1**: Job submission and processing
2. **Phase 2**: Validation and QA
3. **Phase 3**: Combine integration
4. **Phase 4**: Results and documentation

---

## Notes

[Any additional context, links to references, etc.]

Example:
- Theory paper: arXiv:XXXX.XXXXX
- Similar work for M800: See combinationV18 results
- Contact John for cross-section values if needed

---

*Update this plan as the approach evolves. Mark status as Completed when done.*
