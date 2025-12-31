# Tasks: 1tau0l XGB080test Workflow

## Status Summary
| Era | S1-2 OS/MV | S3 WH | S3.1 sys | S4.1 addJES | S4.2-4.4 | S4.5 combine |
|-----|------------|-------|----------|-------------|----------|--------------|
| 2018 | DONE (shared) | PENDING | - | - | - | - |
| 2017 | DONE (shared) | PENDING | - | - | - | - |
| 2016preVFP | DONE (shared) | PENDING | - | - | - | - |
| 2016postVFP | DONE (shared) | PENDING | - | - | - | - |
| **Run2** | - | - | - | - | - | PENDING |

## Current Phase: Setup complete, ready for WH submission

### Session Dec 31 - Task Creation

**Setup Complete:**
- [x] Created `config/analysis_config_1tau0l_XGB080test.yaml`
- [x] Created dev-docs structure
- [x] Verified Stage 1-2 shared with 1tau1l (v95XGB080testOS7)

**Next Steps:**
- [ ] Submit WH for all 4 eras (use screen, `--systematic complete`)
- [ ] Wait for WH completion
- [ ] Run Stage 4

**Commands:**
```bash
# In screen sessions:
source setEnv_newNew.sh
cd writeHistGood/jobs/

# Era 2018
screen -S wh_1tau0l_2018
python3 makeJob_WH.py --config ../../config/analysis_config_1tau0l_XGB080test.yaml --era 2018 --systematic complete

# Similar for 2017, 2016preVFP, 2016postVFP
```

## Last Updated
2025-12-31 15:30
