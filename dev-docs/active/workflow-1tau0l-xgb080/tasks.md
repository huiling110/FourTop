# Tasks: 1tau0l Workflow

## Active Configs
- `analysis_config_1tau0l_v1BDTttbb.yaml` - TTBB-trained BDT (current work)
- `analysis_config_1tau0l_XGB080test.yaml` - XGB080test (shared OS/MV with 1tau1l)

---

## Status: v1BDTttbb (Jan 3, 2026)

| Era | S1-2 OS/MV | S3 WH nominal | S3.1 WH sys | S4 |
|-----|------------|---------------|-------------|-----|
| 2018 | ✅ DONE | ✅ 38 files | ❌ No sys MV dirs | - |
| 2017 | ✅ DONE | ✅ 38 files | ❌ No sys MV dirs | - |
| 2016preVFP | ✅ DONE | ✅ 38 files | ❌ No sys MV dirs | - |
| 2016postVFP | ✅ DONE | ✅ 38 files | ❌ No sys MV dirs | - |

**Issue:** Tried to run systematic WH but no systematic MV directories exist for v94HadroPreJetVetoHemOnly_TTBBtest.
Need to use correct config with existing systematics (XGB080test).

---

## Status: XGB080test (Jan 3, 2026)

| Era | S1-2 OS/MV | S3 WH | S4.1 addJES | S4.2-4.4 | S4.5 combine |
|-----|------------|-------|-------------|----------|--------------|
| 2018 | DONE (shared) | RUNNING (4,441 jobs) | - | - | - |
| 2017 | DONE (shared) | RUNNING (4,447 jobs) | - | - | - |
| 2016preVFP | DONE (shared) | RUNNING (4,443 jobs) | - | - | - |
| 2016postVFP | DONE (shared) | RUNNING (4,440 jobs) | - | - | - |

**Config:** `analysis_config_1tau0l_XGB080test.yaml`
**Hist version:** `v0BDT1tau0l_XGB080testNew`
**Total jobs:** 17,771 (75 variations × ~59 files × 4 eras)

## Next Steps
1. ~~Use XGB080test config for 1tau0l~~ ✓
2. ~~Submit WH for all eras with `--systematic complete`~~ ✓
3. Wait for WH completion (~2-4 hours)
4. Run Stage 4 (addJES → addTemplate → smooth → datacard → combine)

## Last Updated
2026-01-03 13:35
