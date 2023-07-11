import usefulFunc as uf

def main():
    #set up voms first
    # T2Dir = '/cms/store/user/hhua/DYJetsToLL_1J_TuneCP5_13TeV-amcatnloFXFX-pythia8/'
    T2Dir = '/cms/store/user/hhua/crabNanoPost/mc/TTto2L2Nu_TuneCP5_13p6TeV_powheg-pythia8/'
    outDir = '/publicfs/cms/data/TopQuark/nanoAOD/2022_13p6/TTto2L2Nu/'
    
    # command = 'xrdcp -r --rm-bad-cksum --parallel 4 root://ccsrm.ihep.ac.cn:1094/' + T2Dir + ' '+ outDir
    command = 'gfal-copy -r -t 99999 root://cceos.ihep.ac.cn:1094//eos/ihep/' + T2Dir + ' '+ outDir
    # xrdcp -r --rm-bad-cksum --parallel 4 root://ccsrm.ihep.ac.cn:1094///cms/store/user/akapoor/ ./
    uf.runCommand(command)
   
if __name__=='__main__':
    main() 