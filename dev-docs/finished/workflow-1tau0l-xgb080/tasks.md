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

## CRITICAL ISSUE: 2018 JES Systematics (Jan 6, 2026)

**Problem:** Almost ALL JES systematics in 2018 show Up and Down variations going in the **SAME direction** (both decrease events), which is physically wrong.

**Evidence at MV level (tttt RelativeSample):**
| Era | Up variation | Down variation | Normal? |
|-----|-------------|----------------|---------|
| 2018 | -4.85% | -1.98% | **NO - both negative!** |
| 2017 | -0.22% | +0.18% | Yes - opposite directions |

**Affected systematics (2018 tttt):**
- RelativeSample_2018: Up +0.8%, Down +5.5% (at WH/template level)
- TimePtEta_2018, RelativeBal, FlavorPureBottom, PileUpDataMC, AbsoluteMPFBias...
- ~25 JES systematics show SAME_DIR behavior

**Impact:**
- tttt uncertainty in bin 12: +33.7%/-11.1% (2018) vs +14.0%/-13.0% (2017)
- Inflated total uncertainty in 2018 prefit

**Root cause:** Issue originates at MV step (or earlier at OS). Both Up and Down MV jobs read from same OS input (`v95XGB080testOS7_JESPt22`) but produce abnormal variations.

**Detailed analysis (Jan 6):**

| Stage | 2018 | 2017 | Notes |
|-------|------|------|-------|
| OS JES input | 1,698,204 | 1,436,306 | OS with 22 GeV jet cut |
| MV JES Up | 1,577,226 (92.9%) | 1,355,927 (94.4%) | Should be HIGHER |
| MV JES Down | 1,624,756 (95.7%) | 1,361,372 (94.8%) | Should be LOWER |

**The logic is inverted in 2018:**
- JES Up should increase jet pt → MORE events pass cuts
- JES Down should decrease jet pt → FEWER events pass cuts
- But 2018 shows: JES Down > JES Up (backwards!)

**ROOT CAUSE IDENTIFIED (Jan 6) - UPDATED:**

The 2018 OS JES input (`v95XGB080testOS7_JESPt22`) has **FEWER events** than nominal, which is **WRONG**:

| Era | OS Nominal (25 GeV) | OS JES (22 GeV) | Difference |
|-----|---------------------|-----------------|------------|
| **2018** | 1,730,210 | 1,698,200 | **-32,010 (-1.85%)** ← WRONG! |
| **2017** | 1,415,590 | 1,436,310 | **+20,720 (+1.47%)** ← Correct |

**Why this is wrong:**
- JES input uses 22 GeV jet pt cut (lower threshold for headroom)
- Lower threshold → MORE jets pass → MORE events should pass baseline
- 2017 shows correct behavior: JES input > Nominal input
- 2018 shows inverted behavior: JES input < Nominal input

**Effect:** Both JES Up and Down MV outputs are compared against nominal's higher baseline, causing both to appear as "reductions" relative to nominal.

**Possible causes:**
1. **Most likely: 2018 OS JES jobs incomplete** - some input files not processed
2. 2018 OS JES job was run with wrong settings (e.g., wrong jet cut)
3. 2018 OS JES files were corrupted or incomplete
4. Different input samples were used for 2018 OS JES
5. Bug in OS JES processing specific to 2018

**FIX OPTIONS:**
1. **Rerun ALL 2018 OS systematic jobs** - Full fix, need to reprocess all systematics (TES, JER, MET, EleScale, JES)
2. **Rerun only missing tttt files for 2018** - Partial fix, merge with existing outputs
3. **Use 2017 systematic shapes for 2018** - Workaround, assume similar systematic behavior
4. **Drop problematic systematics for 2018** - Quick fix but loses sensitivity

**Investigation status (Jan 6):**

1. **OS code verified correct** (`objectSelectionOptimized/src/jetSel.C:102`):
   ```cpp
   Double_t jetPtCut = (m_JESSys== 0)? 25. : 22.; // Correct: 22 GeV for JES
   ```

2. **ALL 2018 systematic OS outputs have ~3% fewer events** (tttt):
   | Systematic | 2018 vs Nom | 2017 vs Nom | Status |
   |------------|-------------|-------------|--------|
   | JES | -1.85% | +1.47% | ❌ Wrong |
   | TESdm0Up/Down | -3.1% to -3.2% | ±0.06% | ❌ Wrong |
   | TESdm1Down | -0.06% | -0.06% | ✓ OK |
   | JERUp/Down | -3.2% | -0.07%/-2.2% | ❌ Wrong |
   | MET Up/Down | -3.2% | 0% | ❌ Wrong |
   | EleScale Up/Down | -3.2% | 0% | ❌ Wrong |

3. **ROOT CAUSE: WIDESPREAD corruption across ALL systematics**
   - Same file `7B9FC545-2062-9347-9D38-BA36D11D3BB7.root` corrupted in ALL systematics
   - tttt: 9 issues (same file in JES, TES, JER, MET, EleScale)
   - TTBB samples: 44-18 issues each
   - TTZ: 98 issues
   - TTW: 38 issues
   - Many files show "ERROR" (can't read ROOT tree) - more corrupted than initially thought

4. **Files to resubmit:**
   - JESPt22: 925 files (394 corrupted + 531 missing)
   - TES/JER/MET/EleScale: Similar numbers expected

5. **FIX: Rerun ALL corrupted OS files across ALL systematics**
   - Use `scripts/check_os_systematics.py --fix` to generate resubmit scripts
   - Submit via `scripts/submit_os_resubmit.py`
   - After OS fix: rerun MV/WH/Stage4 for all systematics

**Next steps:**
1. ✅ Identified corrupted file: `7B9FC545-2062-9347-9D38-BA36D11D3BB7.root`
2. ✅ Checked all systematics - widespread corruption confirmed
3. ✅ Fixed `check_os_systematics.py` to compare against INPUT files (not nominal)
4. ✅ Fixed `check_os_systematics.py` to only check expected samples per channel
5. ✅ Rewrote `submit_os_resubmit.py` to use existing job scripts from makeJob_OS
6. ✅ **Submitted ALL resubmit jobs** (see status table below)
7. ⏳ Monitor jobs: `hep_q -u $USER | grep OS_UL2018`
8. After OS complete: Rerun check script to verify all files OK
9. Rerun MV for affected systematics (JES, TESdm0/dm1Up, JER, MET, EleScale)
10. Rerun WH for affected systematics
11. Regenerate Stage 4 (addJES, templates, datacards, combine)

**Commands to check/resubmit:**
```bash
# Check specific systematic
python3 scripts/check_os_systematics.py --config config/analysis_config_1tau0l_XGB080test.yaml --era 2018 --systematic JESPt22

# Resubmit corrupted files (uses existing job scripts)
python3 scripts/submit_os_resubmit.py --config config/analysis_config_1tau0l_XGB080test.yaml --era 2018 --systematic JESPt22

# Monitor jobs
hep_q -u $USER | grep OS_UL2018
```

## Output Locations
- Impacts: `hua/combine/combinationV22/run2_1tau0l_v4/combineResults/impactResult/impacts.pdf`
- Postfit: `hua/combine/combinationV22/run2_1tau0l_v4/combineResults/postfitPlots/`

## Last Updated
2026-01-07 10:30

**Session notes (Jan 6 continued):**
- **WIDESPREAD CORRUPTION FOUND** across all 2018 OS systematics
- Same file `7B9FC545-2062-...` corrupted in ALL systematics (JES, TES, JER, MET, EleScale)
- **Total: 3,796 corrupted + 7,965 missing = 11,761 files to resubmit**
- Created `scripts/check_os_systematics.py` to detect and generate resubmit scripts
- Created `scripts/submit_os_resubmit.py` to submit resubmit scripts to batch system
- Updated stage1 skill with mandatory corruption check and resubmit script usage

**FIXES APPLIED (Jan 6):**
1. Fixed `check_os_systematics.py`:
   - Now compares against INPUT files (not nominal which could also fail)
   - Only checks expected samples based on channel config (uses same skip logic as makeJob_OS)
   - Uses correct input path: `/publicfs/cms/data/TopQuark/nanoAOD/2018/mc/` (not UL2018_v9)
2. Fixed `submit_os_resubmit.py`:
   - Added `-os CentOS7` flag for XGBoost 0.80 compatibility
   - Batch scripts now stored on `/publicfs` to avoid file quota issues on `/workfs2`

**CURRENT STATUS (Jan 7, 15:55) - PROBLEM NOT SOLVED:**

| Stage | Status | Details |
|-------|--------|---------|
| OS 2018 resubmit | ✅ Complete | Corrupted files fixed |
| MV 2018 systematics | ❌ **NOT RE-RUN** | Still using OLD corrupted data! |
| WH 2018 | ❓ Unknown | May be using old MV output |
| Stage 4.1-4.5 | ✅ Complete | But based on wrong MV data |

**CRITICAL FINDING (Jan 7, 16:05):**

The MV files **STILL show wrong JES behavior** after the OS fix:
```
JES Up:   1,577,226 entries (-4.85% vs Nominal) ← WRONG! Should be POSITIVE
JES Down: 1,624,756 entries (-1.98% vs Nominal) ← WRONG! Should be MORE negative
Nominal:  1,657,638 entries
```

**ROOT CAUSE: TIMING MISMATCH**
- MV JES ran: **Jan 7, 09:08-09:22**
- OS JES fix completed: **Jan 7, 11:44**
- MV ran **BEFORE** the OS fix was complete!

**OS is now CORRECT** (verified after fix):
```
Same file (7B9FC545...):
  OS Nominal (25 GeV): 211,997 entries
  OS JES (22 GeV):     212,863 entries (+0.4%) ✓ CORRECT
```

**FIX REQUIRED:** Re-run MV for ALL systematics using the fixed OS files.

**ACTION TAKEN (Jan 7, 17:00):**
- Submitted ALL 74 MV systematic variations:
  - TES×8, JER×2, MET×2, EleScale×2, JES×60
- Jobs submitted to cluster, ~85 running
- Expected completion: ~1 hour

**NEXT STEPS:**
1. Wait for MV jobs to complete
2. Verify ALL systematics for ALL processes (check entry counts)
3. Re-run WH for systematics
4. Re-run Stage 4.1-4.5
5. Run2 combine with correct data

**Run2 Combine Results (still wrong due to old MV):**
- Expected significance: **0.176σ** (unchanged from before fix)
- Observed significance: **0** (no excess)

**Symlink Solution (Jan 7):**
Instead of mixed templates, created symlinks so 2018 uses new v2_sysFix content while config uses consistent naming:
```
v0BDT1tau0l_XGB080testNew/ -> v2BDT1tau0l_XGB080testNew_sysFix/
```
- MC: `/publicfs/.../2018/v1baselineHadro_v95XGB080testOS7/mc/variableHists_v0BDT1tau0l_XGB080testNew`
- Data: `/publicfs/.../2018/v1baselineHadro_v95XGB080testOS7/data/variableHists_v0BDT1tau0l_XGB080testNew`
- Old directories renamed to `*_old`

**Key fixes made:**
- `check_os_systematics.py`: Now uses job scripts directory to find expected samples (not input dir)
- `submit_os_resubmit.py`: Uses existing makeJob_OS scripts, maps corrupted files to script indices
- `writeCombinationDatacard.py`: Added `--era-hist` argument for mixed templates (not used with symlink approach)
