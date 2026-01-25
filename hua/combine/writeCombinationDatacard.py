import subprocess
import os
import argparse

# Use fourtop package for config-based path building
try:
    from fourtop.workflow import (
        load_config, build_datacard_path, get_eras, get_channel
    )
    WORKFLOW_UTILS_AVAILABLE = True
except ImportError:
    WORKFLOW_UTILS_AVAILABLE = False

#!!!have to use python2 with combine
cardDic_1tau0l = {
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputs/combine/datacardSys/datacard_1tau0lSys.txt',

    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v1proNormAdd/datacard_1tau0l.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v1proNormAdd/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v1proNormAdd/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v1proNormAdd/datacard_1tau0l.txt',
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    
    #!v14
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',    

    #!v16
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/datacard_1tau0l.txt', 
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV16/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',
    
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys/datacard_1tau0l.txt',

    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',

    #!v8BDT1tau0l_refactorAndBtagNameFix (2025-11-25) - CMS naming conventions compliant
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v8BDT1tau0l_refactorAndBtagNameFix/combine/datacardSys_v6AllSys_unblind/datacard_1tau0l.txt',

    #!v9BDT1tau0l_CMSNamingComplete (2025-11-28) - Complete CMS naming with tau fakes/ID fixes
    'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt',
    'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt',
    'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt',
    'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v9BDT1tau0l_CMSNamingComplete/combine/datacardSys_v6AllSys_unblind_CMSnaming/datacard_1tau0l.txt',
    
}
cardDic1tau1l = {
#     'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',
#     'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',
#     'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',
#     'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',

    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau1l.txt',
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau1l.txt',
    
    #!v14
    # 'SR1t1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v3BasicAndJES/datacard_1tau1l.txt',
    # 'SR1t1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt' ,
    # 'SR1t1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1t1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    
    #!v16
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV16/combine/datacardSys_v6AllSys/datacard_1tau1l.txt', 
    
    # 'SR'
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    
    #!V18
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    
    'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau1l.txt',
    'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau1l.txt',
    'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau1l.txt',
    'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau1l.txt',
}

cardDic_1tau2l = {
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau2l.txt',
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau2l.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau2l.txt',
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/datacardSys_v6AllSysWithFR/datacard_1tau2l.txt',
    
    #!v14
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/datacard_1tau2l.txt',  
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/datacard_1tau2l.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/datacard_1tau2l.txt',
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV14/combine/datacardSys_v4BasicAndJESJER/datacard_1tau2l.txt',
    
    #!V16
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/datacard_1tau2l.txt',
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/datacard_1tau2l.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/datacard_1tau2l.txt',
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV16/combine/datacardSys_v5BasicAndJESJER/datacard_1tau2l.txt',
    
    #!V18
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau2l.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau2l.txt',
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau2l.txt',
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys/datacard_1tau2l.txt',
    
    #!V18 unblind
    'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau2l.txt',
    'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau2l.txt',
    'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau2l.txt',
    'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/combine/datacardSys_v6AllSys_unblind/datacard_1tau2l.txt',
}


def build_card_dic_from_config(config, channel=None, era_hist_overrides=None, variable='BDT'):
    """
    Build card dictionary from YAML config file.

    Args:
        config: Configuration dictionary from load_config()
        channel: Channel name (e.g., '1tau0l'). If None, uses config default.
        era_hist_overrides: Dict mapping era -> hist version for mixed templates.
                           E.g., {'2017': 'v0BDT1tau0l_XGB080testNew'}
        variable: Variable name (default: 'BDT'). Non-BDT variables use separate datacard directories.

    Returns:
        Dictionary mapping 'SR{channel}_{era}' to datacard file paths
    """
    if channel is None:
        channel = get_channel(config)

    eras = get_eras(config)
    card_dic = {}

    # Variable suffix for non-BDT variables
    var_suffix = '' if variable == 'BDT' else f'_{variable}'

    for era in eras:
        key = f'SR{channel}_{era}'

        # Use era-specific hist override if provided
        if era_hist_overrides and era in era_hist_overrides:
            # Create a modified config with the overridden hist version
            config_copy = config.copy()
            config_copy['versions'] = config['versions'].copy()
            config_copy['versions']['hist'] = era_hist_overrides[era]
            datacard_dir = build_datacard_path(config_copy, era)
        else:
            datacard_dir = build_datacard_path(config, era)

        # Add variable suffix to datacard directory for non-BDT variables
        if variable != 'BDT':
            # Insert variable suffix before the trailing slash
            # e.g., datacardSys_v6AllSys/ -> datacardSys_v6AllSys_tausT_1pt/
            datacard_dir = datacard_dir.rstrip('/') + var_suffix + '/'

        datacard_file = os.path.join(datacard_dir, 'datacard.txt')
        card_dic[key] = datacard_file

    return card_dic


def parse_era_hist_overrides(override_str):
    """
    Parse era-hist override string into dictionary.

    Format: "era1=hist1,era2=hist2" or "era1=hist1 era2=hist2"
    Example: "2017=v0BDT1tau0l_XGB080testNew,2016preVFP=v0BDT1tau0l_XGB080testNew"

    Returns:
        Dict mapping era -> hist version
    """
    if not override_str:
        return None

    overrides = {}
    # Split by comma or space
    parts = override_str.replace(',', ' ').split()
    for part in parts:
        if '=' in part:
            era, hist = part.split('=', 1)
            overrides[era.strip()] = hist.strip()

    return overrides if overrides else None


def main():
    parser = argparse.ArgumentParser(
        description='Combine datacards from multiple eras into a single Run2 datacard'
    )
    parser.add_argument(
        '--config', '-c',
        type=str,
        help='Path to YAML config file. If provided, builds paths from config.'
    )
    parser.add_argument(
        '--channel',
        type=str,
        choices=['1tau0l', '1tau1l', '1tau2l'],
        help='Channel to process. Overrides config channel if both provided.'
    )
    parser.add_argument(
        '--version',
        type=str,
        default='V20',
        help='Combination version (e.g., V20). Default: V20'
    )
    parser.add_argument(
        '--output-dir',
        type=str,
        help='Output directory name (e.g., run2_1tau0l_v4_unblind). Default: auto-generated.'
    )
    parser.add_argument(
        '--quiet', '-q',
        action='store_true',
        help='Suppress non-essential output'
    )
    parser.add_argument(
        '--era-hist',
        type=str,
        help='Era-specific hist version overrides. Format: "era1=hist1,era2=hist2". '
             'E.g., "2017=v0BDT1tau0l_XGB080testNew,2016preVFP=v0BDT1tau0l_XGB080testNew"'
    )
    parser.add_argument(
        '--variable',
        type=str,
        default='BDT',
        help='Variable name for datacard organization (default: BDT). '
             'Non-BDT variables create separate output directories.'
    )
    args = parser.parse_args()

    # Determine card dictionary and output settings
    if args.config:
        if not WORKFLOW_UTILS_AVAILABLE:
            print("ERROR: --config requires workflow_utils.py but import failed.")
            print("Make sure PyYAML is installed and workflow_utils.py exists.")
            sys.exit(1)

        config = load_config(args.config)

        # Get channel (CLI overrides config)
        channel = args.channel if args.channel else get_channel(config)

        # Parse era-specific hist overrides
        era_hist_overrides = parse_era_hist_overrides(args.era_hist)

        # Build card dictionary from config (with optional era-specific overrides)
        card_dic = build_card_dic_from_config(config, channel, era_hist_overrides, args.variable)

        if era_hist_overrides and not args.quiet:
            print(f"Using era-specific hist overrides: {era_hist_overrides}")

        # Get combination version from config or CLI
        # Config uses versions.combination (e.g., "combinationV21")
        config_version = config.get('versions', {}).get('combination', '')
        if config_version:
            # Extract version number (e.g., "combinationV21" -> "V21")
            config_version = config_version.replace('combination', '')
            combinationVersion = args.version if args.version != 'V20' else config_version
        else:
            combinationVersion = args.version

        # Auto-generate output directory name if not provided
        variable = args.variable
        var_suffix = '' if variable == 'BDT' else f'_{variable}'

        # Safety check: non-BDT variables must have suffix in path
        if variable != 'BDT':
            assert var_suffix, f"Safety check: non-BDT variable {variable} must have suffix"

        if args.output_dir:
            cardDir = args.output_dir
        else:
            blind_suffix = '' if config.get('options', {}).get('ifBlind', True) else '_unblind'
            cardDir = f'run2_{channel}_v4{var_suffix}{blind_suffix}'

        if not args.quiet:
            print(f"Using config-based paths from: {args.config}")
            print(f"Channel: {channel}, Version: {combinationVersion}")
            if variable != 'BDT':
                print(f"Variable: {variable}")
    else:
        # Legacy mode: use hardcoded dictionaries
        # combinationVersion = 'V11'
        # combinationVersion = 'V12'
        # combinationVersion = 'V13'
        # combinationVersion = 'V13_fakeTau'
        # combinationVersion = 'V14'
        # combinationVersion = 'V16'
        # combinationVersion = 'V17_smoothing'#smoothing
        # combinationVersion = 'V18'
        combinationVersion = args.version  # Default: V20
        # cardDir = 'run2_1tau1l'
        cardDir = args.output_dir if args.output_dir else 'run2_1tau0l_v4_unblind'
        # cardDir = 'run2_1tau0l'
        # cardDir = 'run2_1tau2l'
        # cardDir = 'run2_3years'
        # cardDir = 'run2_1tau1l_v4_unblind'
        # cardDir = 'run2_1tau0l_v4_unblind_smoothed'
        # cardDir = 'run2_1tau2l_v4_unblind'
        # cardDir = 'run2_3channels_v4_unblind'

        # Select card dictionary based on channel argument
        if args.channel == '1tau1l':
            card_dic = cardDic1tau1l
        elif args.channel == '1tau2l':
            card_dic = cardDic_1tau2l
        else:
            card_dic = cardDic_1tau0l  # Default to 1tau0l

        # cardDic1tau1l.update(cardDic_1tau0l)
        # cardDic1tau1l.update(cardDic_1tau2l)

    directory_path = 'combination'+combinationVersion+'/'+cardDir +'/'
    if not os.path.exists(directory_path):
        os.makedirs(directory_path)
        if not args.quiet:
            print("Directory created:", directory_path)

    comDatacard(card_dic, directory_path+'datacard.txt', quiet=args.quiet)

def comDatacard(cardDic, outCard, quiet=False):
    # command = 'combineCards.py SR1tau0l_2016={} SR1tau0l_2017={} SR1tau0l_2018={} > Run2_1tau0l_datacard.txt'.format(SR1tau0l_2016, SR1tau0l_2017, SR1tau0l_2018)
    command = 'combineCards.py '
    for iCard in cardDic.keys():
        command = command+ iCard + '='+ cardDic[iCard] + ' '
    # command = command +'> '+ 'Run2_1tau1l_datacard.txt'
    # command = command +'> '+ 'Run2_all_datacard.txt'
    command = command +'> '+ outCard


    # command = 'combineCards.py SR1tau1l={} SR1tau0l={} > 2016_1tau1lAnd1tau0l_datacard.txt'.format(SR1tau1l, SR1tau0l)
    if not quiet:
        print(command)
    process = subprocess.Popen( command, shell=True)
    out = process.communicate()
    if not quiet:
        print(out)

if __name__ == '__main__':
    main()