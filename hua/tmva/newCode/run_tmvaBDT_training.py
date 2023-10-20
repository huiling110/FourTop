import usefulFunc as uf 
import subprocess

def main():
    # inputDir  = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/'
    inputDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1NewHLTSF1tau1lCut_v64PreAndHLTSel/mc/",
   
   
    # g_weight = "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight*btagWPMedium_weight" 
    # varDir = inputDir + 'tmvaTraining/btagWP/'
    # varList = varDir + 'variableList_15.csv'
    
    # g_weight = "EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*elesTopMVAT_weight*musTopMVAT_weight*btagShape_weight*btagShapeR"
    varDir = inputDir + 'tmvaTraining/btagShape/'
    varList = varDir + 'variableList_16.csv'
    
    outDir = varDir 
    uf.checkMakeDir(outDir)
    
    command = './my_program {} {} {} {} 0'.format(inputDir, outDir, varList, g_weight ) 
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
    
    
    
    
if __name__=='__main__':
    main() 
    
    