
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
    # Electron_eta = array('f',[0.])
    # Electron_jetNDauCharged = array('f', [0.])
    # Electron_miniPFRelIso_chg = array('f',[0.])
    # Electron_miniPFRelIso_all = array('f',[0.])
    # Electron_jetPtRelv2 = array('f',[0.])
    # Electron_jetRelIso = array('f', [0.])# jetPtRatio},
    # Electron_pfRelIso03_all = array('f',[0.])
    # Jet_btagDeepB = array('f') # jetBTag},
    # Electron_jetIdx = array('f', [0.]) # jetBTag
    # Electron_sip3d = array('f',[0.])
    # Electron_dxy = array('f',[0.])
    # Electron_dz = array('f',[0.])
    # Electron_mvaFall17V2noIso = array('f',[0.])
    
    # tree.SetBranchAddress('Electron_pt', Electron_pt)
    # tree.SetBranchAddress('Electron_eta', Electron_eta)
    # tree.SetBranchAddress('Electron_jetNDauCharged', Electron_jetNDauCharged )
    # tree.SetBranchAddress('Electron_miniPFRelIso_chg', Electron_miniPFRelIso_chg)
    # tree.SetBranchAddress('Electron_miniPFRelIso_all', Electron_miniPFRelIso_all)
    # tree.SetBranchAddress('Electron_jetPtRelv2', Electron_jetPtRelv2)
    # tree.SetBranchAddress('Electron_jetRelIso', Electron_jetRelIso)
    # tree.SetBranchAddress('Electron_pfRelIso03_all', Electron_pfRelIso03_all)
    # tree.SetBranchAddress('Electron_sip3d', Electron_sip3d)
    # tree.SetBranchAddress('Electron_dxy', Electron_dxy)
    # tree.SetBranchAddress('Electron_dz', Electron_dz)
    # tree.SetBranchAddress('Electron_mvaFall17V2noIso',Electron_mvaFall17V2noIso )
    
    # for i in range(tree.GetEntries()):
    for i in range( 20):
        tree.GetEntry(i)
        pt = tree.Electron_pt #Electron_pt#???
        # print(pt)
        for ipt in pt:
            print(ipt)
            
        for ele in range()
        
        # lep = {} 
        # lep['pdgId'] = 11
        # lep["pt"] = Electron_pt[0]
        # lep["eta"] = Electron_eta[0]
        # lep["etNDauCharged"] = Electron_jetNDauCharged.At(j)},
        # lep["miniPFRelIso_chg"] = Electron_miniPFRelIso_chg[0]
        # lep["miniPFRelIso_all"] = Electron_miniPFRelIso_all[0]
        # lep["jetPtRelv2"] = Electron_jetPtRelv2[0]
        # lep["jetPtRatio"] = 1. / (Electron_jetRelIso[0] + 1.) 
        # lep["pfRelIso03_all"] = Electron_pfRelIso03_all[0]
        # lep["jetBTag"] = jetBTag},
        # lep["sip3d"] = Electron_sip3d[0]
        # lep["dxy"] = Electron_dxy[0]
        # lep["dz"] = Electron_dz[0]
        # lep["mvaFall17V2noIso"] = Electron_mvaFall17V2noIso[j]}};
        
        # top = mvaTOPreader('UL2018')
        
    inputFile.Close()   
    
    # with uprvoot.open('/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/nanoAOD/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root') as f:
    #     tree = f["Events"]
    #     events = tree.arrays(["Electron_pt"],library="pd") 
    #     print(events)

        

    
    
    
    

if __name__=='__main__':
    main()