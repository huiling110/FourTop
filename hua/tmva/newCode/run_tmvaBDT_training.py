import usefulFunc as uf 
import subprocess
import os

def main():
    # inputDir  = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1NewHLTSF1tau1lCut_v64PreAndHLTSel/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau1l_v64PreAndHLTSel/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1l_v74AddMETPhi/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau1l_v75AddTauTTTTNoHTCut/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2tau1l1CutHT4006jetpt30_v75OverlapRemovalFTau/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Cut1tau1l_v75OverlapRemovalFTau/mc/'
    
   
    #1tau0l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v76WithVLLAllMass/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v79HadroPresel/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v80addTauJetVar/mc/'
    # varList = '/workfs2/cms/huahuil/4topCode/v2cut1tau0lSRTauF_v76WithVLLAllMass/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l.csv'
    # varList = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l.csv'
    # varList = '/workfs2/cms/huahuil/4topCode/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l_final26.csv' #!final list for 1tau0l
    # varList = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l_finalFinal26.csv'
    # varList = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_finalFinal25.csv'
    # g_weight = "event_allWeight_1tau0l" 
    # channel = '1tau0l'
    # outVersion = 'v0'
    # outVersion = 'v1final26Var'
    # outVersion = 'v2NoMET'
    # outVersion = 'v3NoTauF'
    # outVersion = 'v4finalFinal26Var'
    # outVersion = 'v5finalFinal25Var'
    
    #!1tau1l
    channel = '1tau1l'
    #inputDir = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baseline1tau0lForBDT_v81addSysSum_1tau0l_full/mc/'
    inputDir = '/publicfs/cms/user/turuobing/tauOfTTTT_NanoAODOfficial/forMVA/2018/v0baselineHardro_1tau1l_BDTSR_v86HadroPreSelWithGammaRemoval/mc/'
    # varList = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l_final30.csv'
    # varList = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l.csv'
    varList = '/afs/ihep.ac.cn/users/t/turuobing/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau1l_final.csv'
    g_weight = 'global_weight*EVENT_genWeight *EVENT_prefireWeight *PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagWPMT_weight'
    # outVersion = 'v0allVar'
    outVersion = 'tttt_GBDT_1tau1l'
    
    #1tau2l
    # channel = '1tau2l'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau2l_v76For1tau2l/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau2lSR_v84Pre1tau2lLepF2/mc/'
    # varList = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l_all.csv'
    # varList = '/workfs2/cms/huahuil/CMSSW_10_6_20/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau2l_final.csv'
    # g_weight = 'global_weight*EVENT_genWeight *EVENT_prefireWeight *PUweight_*tauT_IDSF_weight_new*elesTopMVAT_weight * musTopMVAT_weight * btagWPMT_weight'
    # outVersion = 'v0allVar'
    # outVersion = 'v1finalVar'
    
    ifVLL = 'VLLm600'
    
    outDir = inputDir + 'BDTTrain/' 
    uf.checkMakeDir(outDir)
    outDir = outDir + outVersion + '/'
    uf.checkMakeDir(outDir)
    
    command = './my_program {} {} 0 {} {} {} {}'.format(inputDir, outDir, varList, g_weight, channel, ifVLL) 
    logFile = outDir + 'training.log'
    print(command)
    try:
        with open(logFile, "w") as outfile:
            pro = subprocess.run(command, stdout=outfile, stderr=subprocess.STDOUT, text=True, check=True, shell=True)
            print(pro.stdout)
            print('\n')
            print("Program executed successfully. Output saved to", logFile)
    except subprocess.CalledProcessError as e:
        print("Error:", e)
    
    
def makeJobsSub(exeDir, command, jobDir):
    jobSubFile = jobDir + 'BDTtrain.sh'
    with open(jobSubFile, 'w') as job_script:
        job_script.write("#!/bin/bash\n")
        job_script.write(command)
    print('writen job sub: ', jobSubFile)

    
    
    
    
if __name__=='__main__':
    main() 
    
    