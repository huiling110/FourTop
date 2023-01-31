
import ROOT
from array import array

import sys
sys.path.append("/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/codeFromOthers/")
import mvaTOPreader as tl

def main():
    #xrootd for accessing data
    #redirector for Europe and Asia: rootd-cms.infn.it
    # nanoFile = '/store/mc/RunIISummer20UL18NanoAODv9/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/120000/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root'
    # inputFile = ROOT.TFile.Open("root://rootd-cms.infn.it//" + nanoFile )#???not working
    inputFile = ROOT.TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/nanoAOD/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root", "READ") #UL2018
    # inputFile = ROOT.TFile("/scratchfs/cms/huahuil/tauOfTTTT_NanoAOD/nanoAOD/2018/mc/tttt/outTree_1.root", "READ")
    
    tree = inputFile.Get("Events") 
    # tree.Print()
    tree.SetBranchStatus("Electron_pt", 1)
    tree.SetBranchStatus("*", 0)
    
    # pt = array('f', [0.])
    # tree.SetBranchAddress('Electron_pt', pt)
    
    # for i in range(tree.GetEntries()):
    for i in range( 20):
        tree.GetEntry(i)
        pt = tree.Electron_pt #Electron_pt
        print(pt)
    
    inputFile.Close()    

    
    
    
    

if __name__=='__main__':
    main()