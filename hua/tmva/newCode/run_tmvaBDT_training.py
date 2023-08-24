import usefulFunc as uf 

def main():
    inputDir  = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v4forBDT1tau1lCut_v61fixesLepRemovalBug/mc/'
    
    varDir = inputDir + 'tmvaTraining/btagWP/'
    
    varList = varDir + 'variableList_15.csv'
    
    outDir = varDir 
    uf.checkMakeDir(outDir)
    
    command = './my_program ' 
    
    
    
if __name__=='__main__':
    main() 
    
    