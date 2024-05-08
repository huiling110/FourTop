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
    # outVersion = 'v0'
    # outVersion = 'v1AllCorrection'
    # outVersion = 'v2NoBtag'
    
    #!testing
    # varList = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/plotting/branch_names.csv"
    # varList = "./inputList/inputList_notTauTT.csv"
    # varList = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_noTauTT.csv'
   
    # g_weight = "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight*btagWPMedium_weight" 
    # varDir = inputDir + 'tmvaTraining/btagWP/'
    # varList = varDir + 'variableList_15.csv'
    # varList = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2017/v8tau1elCut_v60fixeJetBtagBug/1tau1l_v1/variableList/varibleList_16.csv"
    
    # g_weight = "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight*btagShape_weight*btagShapeR"
    # varDir = inputDir + 'tmvaTraining/btagShape/'
    # varList = varDir + 'variableList_16.csv'
    
    #1tau0l
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/'
    varList = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_1tau0l.csv'
    g_weight = "event_allWeight_1tau0l" 
    outVersion = 'v0'
    
    # g_weight = "EVENT_genWeight*PUweight_*EVENT_prefireWeight" 
    # g_weight = "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight*btagWPMedium_weight" 
    # varList = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_tauTT.csv'
    # varList = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/tmva/newCode/inputList/inputList_noBtagShape.csv'
    
    
    outDir = inputDir + 'BDTTrain/' 
    uf.checkMakeDir(outDir)
    outDir = outDir + outVersion + '/'
    uf.checkMakeDir(outDir)
    
    command = './my_program {} {} 0 {} {}'.format(inputDir, outDir, varList, g_weight) 
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
    
    # jobDir = './'
    # exeDir = current_file_path = __file__
# Get the directory of the current file
    # current_dir = os.path.dirname(__file__)
    # makeJobsSub(current_dir, command, jobDir)
    
def makeJobsSub(exeDir, command, jobDir):
    jobSubFile = jobDir + 'BDTtrain.sh'
    with open(jobSubFile, 'w') as job_script:
        job_script.write("#!/bin/bash\n")
        job_script.write(command)
    print('writen job sub: ', jobSubFile)

    
    
    
    
if __name__=='__main__':
    main() 
    
    