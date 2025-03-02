import subprocess
import os
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
    'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau0l.txt',
    
    
}
cardDic1tau1l = {
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau1l_28FP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAO8/2016postVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/datacard_1tau1lSys.txt',
    
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3JESadded/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3JESadded/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3JESadded/datacard_1tau1l.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v3JESadded/datacard_1tau1l.txt',
    
#     'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',
#     'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',
#     'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',
#     'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4NoJESForTTX/datacard_1tau1l.txt',

    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v4BasicAndJESJER/datacard_1tau1l.txt',
    'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
    'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v6AllSys/datacard_1tau1l.txt',
}

cardDic_1tau2l = {
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l_newMCSample/combine/datacardSys_v1proNormAdd/datacard_1tau2l.txt',
    # 'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v1proNormAdd/datacard_1tau2l.txt',
    # 'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v1proNormAdd/datacard_1tau2l.txt',
    # 'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v1proNormAdd/datacard_1tau2l.txt',
    
    'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
    'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/datacardSys_v6AllSys_noMinor/datacard_1tau2l.txt',
}


def main():
    # combinationVersion = 'V11'
    # combinationVersion = 'V12'
    combinationVersion = 'V13'
    # cardDir = 'run2_1tau1l'
    # cardDir = 'run2_1tau0l'
    cardDir = 'run2_1tau2l'
    # cardDir = 'run2_1tau2l_JESJER'
    # cardDir = 'run2_3years'
    # cardDic1tau1l.update(cardDic_1tau0l)
    # cardDic1tau1l.update(cardDic_1tau2l)
    
    
    directory_path = 'combination'+combinationVersion+'/'+cardDir +'/'
    if not os.path.exists(directory_path):
        os.makedirs(directory_path)
        print("Directory created:", directory_path)
    
    # outCard = f'combination{combinationVersion}/{cardDir}/datacard.txt'
    # comDatacard(cardDic1tau1l, directory_path+'datacard.txt')#!!!
    # comDatacard(cardDic_1tau0l, directory_path+'datacard.txt')
    comDatacard(cardDic_1tau2l, directory_path+'datacard.txt')

def comDatacard(cardDic, outCard):
    # command = 'combineCards.py SR1tau0l_2016={} SR1tau0l_2017={} SR1tau0l_2018={} > Run2_1tau0l_datacard.txt'.format(SR1tau0l_2016, SR1tau0l_2017, SR1tau0l_2018)
    command = 'combineCards.py '
    for iCard in cardDic.keys():
        command = command+ iCard + '='+ cardDic[iCard] + ' '
    # command = command +'> '+ 'Run2_1tau1l_datacard.txt'
    # command = command +'> '+ 'Run2_all_datacard.txt'
    command = command +'> '+ outCard
        

    # command = 'combineCards.py SR1tau1l={} SR1tau0l={} > 2016_1tau1lAnd1tau0l_datacard.txt'.format(SR1tau1l, SR1tau0l)
    print(command)
    process = subprocess.Popen( command, shell=True)
    out = process.communicate()
    print(out)

if __name__ == '__main__':
    main()