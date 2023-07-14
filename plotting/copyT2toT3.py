import os

import usefulFunc as uf

def main():
    #set up voms first
    # T2Dir = '/cms/store/user/hhua/DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/'
    # T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto4Q_TuneCP5_13p6TeV_powheg-pythia8/'
    T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto2L2Nu/'
    # outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto4Q/'
    outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/'
    
    for ipro in os.listdir(T2Dir):
        print(ipro)
        iT2Dir = T2Dir + ipro + 'crab*/*/0000/'
        ioutDir = outDir + ipro.find('_')
        
   
    # copyT2ToT3(T2Dir, T3Dir)
   
   
def copyT2ToT3(T2Dir, T3Dir):
    # command = 'xrdcp -r --rm-bad-cksum --parallel 4 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ outDir #not working 
    command = 'gfal-copy -r -t 99999 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ T3Dir
    # xrdcp -r --rm-bad-cksum --parallel 4 root://ccsrm.ihep.ac.cn:1094///cms/store/user/akapoor/ ./
    uf.runCommand(command)
   
if __name__=='__main__':
    main() 