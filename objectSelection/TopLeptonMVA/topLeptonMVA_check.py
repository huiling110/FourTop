
import ROOT
from array import array
# import uproot
# import pandas as pd
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
    # tree.SetBranchStatus("*", 0)
    # tree.SetBranchStatus("Electron_pt", 1)#???
    
    # Electron_pt = array('f', [0.])
    # tree.SetBranchAddress('Electron_mvaFall17V2noIso',Electron_mvaFall17V2noIso )
    
    # for i in range(tree.GetEntries()):
    for i in range( 20):
        tree.GetEntry(i)
        pt = tree.Electron_pt #Electron_pt#???
            
        for ele in range(tree.nElectron):
            lep = {} 
            lep['pdgId'] = 11
            lep["pt"] = tree.Electron_pt[ele]
            lep["eta"] = tree.Electron_eta[ele]
            lep["jetNDauCharged"] = tree.Electron_jetNDauCharged[ele]
            lep["miniPFRelIso_chg"] = tree.Electron_miniPFRelIso_chg[ele]
            lep["miniPFRelIso_all"] = tree.Electron_miniPFRelIso_all[ele]
            lep["jetPtRelv2"] = tree.Electron_jetPtRelv2[ele]
            lep["jetPtRatio"] = 1. / (tree.Electron_jetRelIso[ele] + 1.) 
            lep["pfRelIso03_all"] = tree.Electron_pfRelIso03_all[ele]
            lep["jetBTag"] = tree.Jet_btagDeepB[tree.Electron_jetIdx[ele]]
            lep["sip3d"] = tree.Electron_sip3d[ele]
            lep["dxy"] = tree.Electron_dxy[ele]
            lep["dz"] = tree.Electron_dz[ele]
            lep["mvaFall17V2noIso"] = tree.Electron_mvaFall17V2noIso[ele]
            print(lep)
        
            top = tl.mvaTOPreader('UL2018')
            print(top.getmvaTOPScore(lep))
        
    inputFile.Close()   
    
    # with uprvoot.open('/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/nanoAOD/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root') as f:
    #     tree = f["Events"]
    #     events = tree.arrays(["Electron_pt"],library="pd") 
    #     print(events)

        

    
    
    
    

if __name__=='__main__':
    main()