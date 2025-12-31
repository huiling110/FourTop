---
name: status
description: Show multi-channel workflow status dashboard. Use to check progress of all channels/eras. Keywords: status, progress, dashboard, check, monitor.
---

# Workflow Status Skill

Shows unified status of all channels and eras.

## Usage

```
/status              # Show XGB080test configs (1tau0l, 1tau1l)
/status --all        # Show all analysis configs
/status --config X   # Show specific config
```

## Commands

```bash
# Multi-channel dashboard
python3 scripts/workflow_status.py

# All configs
python3 scripts/workflow_status.py --all

# Specific config
python3 scripts/workflow_status.py --config config/analysis_config_1tau1l_XGB080test.yaml

# WH job monitor (watch mode)
python3 scripts/check_wh_jobs.py --config CONFIG --all --watch

# Quick WH check
python3 scripts/check_wh_jobs.py --config CONFIG --all --quiet
```

## Output Example

```
######################################################################
# FourTop Workflow Status Dashboard
# Generated: 2025-12-31 15:45:00
######################################################################

======================================================================
Channel: 1tau1l | Config: analysis_config_1tau1l_XGB080test.yaml
Versions: stage1=v95XGB080testOS7, hist=v0BDT_XGB080testNew
======================================================================

Era          | S3 WH                | S4.1 addJES  | S4.4 DC
-------------+----------------------+--------------+-----------
2018         | DONE (nom+sys)       | DONE         | DONE
2017         | DONE (nom+sys)       | DONE         | DONE
2016preVFP   | DONE (nom+sys)       | DONE         | DONE
2016postVFP  | DONE (nom+sys)       | DONE         | DONE

Run2 Combine | RUNNING

======================================================================
Legend: PENDING=not started, RUNNING=in progress, DONE=complete
======================================================================
```

## Integration

When Claude needs to check workflow progress:
1. Run `python3 scripts/workflow_status.py` for overview
2. Run `python3 scripts/check_wh_jobs.py --config X --all` for detailed WH status
3. Check `hep_q -u huahuil | grep -c WH_` for running job count
