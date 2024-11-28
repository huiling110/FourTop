import subprocess
import os
#!!!have to use python2 with combine
cardDic_1tau0l = {
    # 'SR1tau0l_2016' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/1tau0ltemplates_Sum_jets_bScore_datacard.txt',
    # 'SR1tau0l_2017' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/1tau0ltemplates_Sum_jets_bScore_datacard.txt',
    # 'SR1tau0l_2018' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baseline_v42fixedChargeType/mc/variableHists_v0forVariables1tau0l/1tau0l_templatesForCombine/datacard/sumDC_10/1tau0ltemplates_Sum_jets_bScore_datacard.txt',
    #combinationV8:
    # 'SR1tau0l_2016' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0l_bScore/combine/datacard/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2017' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0l_bScore/combine/datacard/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2018' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0systematic1tau0l_bScore/combine/datacard/datacard_1tau0lSys.txt',
    
    # 'SR1tau0l_2016': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v67TheoryWeightAdded/mc/variableHists_v0theorecticalHistsAdd1tau0l/combine/datacardTheoSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v67TheoryWeightAdded/mc/variableHists_v0theorecticalHistsAdd1tau0l/combine/datacardTheoSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v66TheoryWeightAdded/mc/variableHists_v0theorecticalHistsAdd1tau0lNew/combine/datacardTheoSys/datacard_1tau0lSys.txt',
    
    # 'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputsWith2018train/combine/datacardSys/datacard_1tau0lSys.txt',
    # 'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/variableHists_v2BDT25inputs/combine/datacardSys/datacard_1tau0lSys.txt',

    'SR1tau0l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v2JESadded/datacard_1tau0l.txt',
    'SR1tau0l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v2JESadded/datacard_1tau0l.txt',
    'SR1tau0l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v2JESadded/datacard_1tau0l.txt',
    'SR1tau0l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/datacardSys_v2JESadded/datacard_1tau0l.txt',
    
    
}
cardDic = {
    # 'SR1tau1l_2016': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v3extra1tau1lCut_v41addVertexSelection/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/TMVApp_1tau1l_10var_Sum_datacard.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/TMVApp_1tau1l_10var_Sum_datacard.txt',
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2018/v6Cut1tau1lVariableFixed_v42fixedChargeType/1tau1l_v0/AppResults_30bins/datacard/sumDC_10/TMVApp_1tau1l_10var_Sum_datacard.txt',
    #combinationV8
    # 'SR1tau1l_2016': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/combine/datacard/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/combine/datacard/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic/combine/datacardJECTESAdded/datacard_1tau1lSys.txt',

    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v66TheoryWeightAdded/mc/variableHists_v0theorecticalHistsAdd/combine/datacardSys/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v67TheoryWeightAdded/mc/variableHists_v0theorecticalHistsAdd/combine/datacardSys/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2016': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v67TheoryWeightAdded/mc/variableHists_v0theorecticalHistsAdd/combine/datacardSys/datacard_1tau1lSys.txt',
    
    # 'SR1tau1l_2022post': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0NoSystematic/combine/datacardNoSys/datacard_1tau1l.txt',
    # 'SR1tau1l_2022pre': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0NoSystematic/combine/datacardNoSys/datacard_1tau1l.txt',
    
    # 'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/datacard_1tau1lSys.txt',
    # 'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v84HadroPresel/mc/variableHists_v0BDT1tau1lBinGv2/combine/datacard_sys/datacard_1tau1lSys.txt',
    
    'SR1tau1l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    'SR1tau1l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    'SR1tau1l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
    'SR1tau1l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/datacardSys_v1proNormAdd/datacard_1tau1l.txt', 
}

cardDic_1tau2l = {
    'SR1tau2l_2018': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    'SR1tau2l_2017': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    'SR1tau2l_2016preVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
    'SR1tau2l_2016postVFP': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v84Pre1tau2lLepF2V2/mc/variableHists_v1BDT1tau2lBinC/combine/datacard_sys/datacard_1tau1lSys.txt',
}


def main():
    # cardDic.update(cardDic_1tau0l)
    # cardDic.update(cardDic_1tau2l)
    # combinationVersion = 'V11'
    combinationVersion = 'V12'
    # cardDir = 'run2_1tau1l'
    cardDir = 'run2_1tau0l'
    # outCard = 'combinationV8/run2_1tau0l/datacard_1tau0lCom.txt'
    # outCard = 'combinationV9/run2_1tau0l/datacard_1tau0lCom.txt'
    # outCard = 'combinationV9/run2_1tau1l/datacard_1tau1lCom.txt'
    # outCard = 'combinationV9/2022_1tau1l/datacard.txt'
    # outCard = 'combinationV9/run2AndRun3/datacard.txt'
    # outCard = 'combinationV10/run2_1tau2l/datacard_1tau2l.txt'
    # outCard = 'combinationV10/run2_1tau1l/datacard_1tau1l.txt'
    # outCard = 'combinationV10/run2_1tau0l/datacard_1tau0l.txt'
    # outCard = 'combinationV10/run2_3channels/datacard_run2.txt'
    
    
    directory_path = 'combination'+combinationVersion+'/'+cardDir +'/'
    if not os.path.exists(directory_path):
        os.makedirs(directory_path)
        print("Directory created:", directory_path)
    
    # outCard = f'combination{combinationVersion}/{cardDir}/datacard.txt'
    # comDatacard(cardDic, directory_path+'datacard.txt')
    comDatacard(cardDic_1tau0l, directory_path+'datacard.txt')
    # comDatacard(cardDic_1tau0l, outCard)
    # comDatacard(cardDic1tau2l, outCard)

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