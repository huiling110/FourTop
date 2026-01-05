# Tasks: 1tau0l Workflow

## Active Configs
- `analysis_config_1tau0l_v1BDTttbb.yaml` - TTBB-trained BDT (blocked, no sys MV dirs)
- `analysis_config_1tau0l_XGB080test.yaml` - XGB080test (current)

---

## Status: XGB080test (Jan 4, 2026)

| Era | S1-2 OS/MV | S3 WH | S4.1 addJES | S4.2-4.3 | S4.4 datacard | S4.5 combine |
|-----|------------|-------|-------------|----------|---------------|--------------|
| 2018 | DONE | DONE (1966 files) | DONE | DONE | DONE | RUNNING |
| 2017 | DONE | DONE (1966 files) | DONE | DONE | DONE | RUNNING |
| 2016preVFP | DONE | DONE (1966 files) | DONE | DONE | DONE | RUNNING |
| 2016postVFP | DONE | DONE (1966 files) | DONE | DONE | DONE | RUNNING |

**Config:** `analysis_config_1tau0l_XGB080test.yaml`
**Hist version:** `v0BDT1tau0l_XGB080testNew`
**Template version:** `v3` (use `--template-version v3` for smooth/writeDatacard)
**Combine directory:** `hua/combine/combinationV22/run2_1tau0l_v4/`

## Completed Steps
1. WH complete (nominal + systematics): ~7,864 files per era
2. Stage 4.1 (addJES): Completed for all 4 eras
3. Stage 4.2 (addTemplate): Completed, created `templatesForCombine1tau0l_v3_notMCFTau_unblind.root`
4. Stage 4.3 (smooth): Completed with `--template-version v3`
5. Stage 4.4 (writeDatacard): Completed with `--template-version v3`
6. Stage 4.4.1 (Run2 combination): Completed at `combinationV22/run2_1tau0l_v4/datacard.txt`
7. Stage 4.5 (combine fits): **RUNNING** (started 2026-01-04 10:25)

## Next Steps
1. Wait for combine fits (~1-2 hours)
2. Check significance and signal strength results
3. Generate postfit plots if results look reasonable

## Key Learnings
- XGB080test uses v3 templates, requiring `--template-version v3` for smooth/writeDatacard
- This is different from 1tau1l which uses v3 naming natively

---

## Status: v1BDTttbb (Jan 3, 2026)

**BLOCKED** - No systematic MV directories exist for `v94HadroPreJetVetoHemOnly_TTBBtest`.

| Era | S1-2 OS/MV | S3 WH nominal | S3.1 WH sys | S4 |
|-----|------------|---------------|-------------|-----|
| 2018 | DONE | DONE (38 files) | BLOCKED | - |
| 2017 | DONE | DONE (38 files) | BLOCKED | - |
| 2016preVFP | DONE | DONE (38 files) | BLOCKED | - |
| 2016postVFP | DONE | DONE (38 files) | BLOCKED | - |

To unblock: Need to run systematic OS/MV with v1BDTttbb config from scratch.

## Last Updated
2026-01-04 10:30
