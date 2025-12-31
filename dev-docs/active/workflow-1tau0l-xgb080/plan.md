# Plan: 1tau0l XGB080test Workflow

## Phases

### Phase 1: Setup (DONE)
- [x] Create `analysis_config_1tau0l_XGB080test.yaml`
- [x] Create dev-docs structure

### Phase 2: Stage 3 WH (4 eras)
Since Stage 1-2 shared with 1tau1l:
1. Submit WH for 2018 with `--systematic complete`
2. Submit WH for 2017 with `--systematic complete`
3. Submit WH for 2016preVFP with `--systematic complete`
4. Submit WH for 2016postVFP with `--systematic complete`
5. Wait for completion (~4400 jobs per era, ~10 min each)

### Phase 3: Stage 4 (All Eras)
1. addJES for all 4 eras
2. addTemplate for all 4 eras
3. smooth (sync point)
4. writeDatacard for all 4 eras

### Phase 4: 1tau0l Run2 Combination
1. writeCombinationDatacard.py --channel 1tau0l
2. Create symlink in /publicfs/.../run2_combination/
3. Run combine fits (1-2 hours)

### Phase 5: 3-Channel Combination
1. Verify 1tau1l complete
2. Check 1tau2l status
3. Create 3-channel combined datacard
4. Run final combine fits

## Dependencies
- 1tau1l XGB080test must complete for 3-channel
- 1tau2l status unknown - may need separate run
