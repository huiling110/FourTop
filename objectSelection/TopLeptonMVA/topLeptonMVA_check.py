import os
import ROOT
from ROOT import std
from array import array
# import uproot
# import pandas as pd

import sys
sys.path.append("/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/codeFromOthers/")
import mvaTOPreader as tl
import usefulFunc as uf

def main():
    
    # eventList = getEventNumFromSS()
    # print(eventList)
    
    # createRootFile( eventList)        
    createRootFile( )        
    
    
    
def getEventNumFromSS():
    inFile =  ROOT.TFile('/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/sync_objects_TT_UGent.root', 'READ')
    tree = inFile.Get('SyncObjects')
    eventNumberList = []
    for eve in range(tree.GetEntries()):
        # print(eve.EventNumber)
        tree.GetEntry(eve)
        eventNumberList.append(tree.EventNumber)
  
    inputTT = ROOT.TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/nanoAOD/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root", "READ")
    outFile = ROOT.TFile('/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/skimmedInputTT.root', 'recreate')
    oldTree = inputTT.Get('Events')
    newTree = oldTree.CloneTree(0) 
    for eve in range(oldTree.GetEntries()):
        oldTree.GetEntry(eve)
        if oldTree.event in eventNumberList:
            newTree.Fill()
    newTree.Print()
    outFile.Write()
    print('skimmed treee here: ', outFile.GetName())
        
    return eventNumberList 
    
    
# def createRootFile(eventList):
def createRootFile():
    #xrootd for accessing data
    #redirector for Europe and Asia: rootd-cms.infn.it
    # nanoFile = '/store/mc/RunIISummer20UL18NanoAODv9/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/NANOAODSIM/106X_upgrade2018_realistic_v16_L1v1-v1/120000/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root'
    # inputFile = ROOT.TFile.Open("root://rootd-cms.infn.it//" + nanoFile )#???not working
    # inputFile = ROOT.TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/nanoAOD/B8F4ECF8-1363-C14F-B6F4-D292106546A0.root", "READ") #UL2018
    inputFile = ROOT.TFile('/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/skimmedInputTT.root')
    
    tree = inputFile.Get("Events") 
    # tree.Print()
    # tree.SetBranchStatus("*", 0)
    # tree.SetBranchStatus("Electron_pt", 1)#???
    
    # for i in range(tree.GetEntries()):
    #     tree.GetEntry(i)
    #     if not (tree.event in eventList): continue
        
    outDir = os.path.dirname(os.path.realpath(__file__)) + '/output/'
    uf.checkMakeDir(outDir) 
    outFile = ROOT.TFile( outDir + 'syncWithSS.root', "RECREATE")
    outTree = ROOT.TTree('events', 'event tree for sync')
    
    event = array('L', [0])
    ele_topLeptonMVA = std.vector('float')()
    mu_topLeptonMVA = std.vector('float')()
    outTree.Branch('eventNumber', event, 'event/l')
    outTree.Branch('mu_topLeptonMVA', mu_topLeptonMVA)
    outTree.Branch('ele_topLeptonMVA', ele_topLeptonMVA)
    
    for i in range(tree.GetEntries()):
    # for i in range( 4000):
        tree.GetEntry(i)
        # if not (tree.event in eventList): continue
        
        event[0] = tree.event
        # print('eventNumber: ', tree.event)
        ele_topLeptonMVA.clear()
        mu_topLeptonMVA.clear()
        
        # ele_topLeptonMVA =  getLeptonVector(  )
                    
        for ele in range(tree.nElectron):
            lep = {} 
            lep['pdgId'] = 11
            lep["pt"] = tree.Electron_pt[ele]
            lep["eta"] = tree.Electron_eta[ele] #absolute or not?
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
            # print(lep)
        
            top = tl.mvaTOPreader('UL2018')
            # print(top.getmvaTOPScore(lep))
            ele_topLeptonMVA.push_back(top.getmvaTOPScore((lep))[0])
        
        for mu in range(tree.nMuon):
            lep = {} 
            lep['pdgId'] = 13
            lep["pt"] = tree.Muon_pt[mu]
            lep["eta"] = tree.Muon_eta[mu] #absolute or not?
            lep["jetNDauCharged"] = tree.Muon_jetNDauCharged[mu] #???
            lep["miniPFRelIso_chg"] = tree.Muon_miniPFRelIso_chg[mu]
            lep["miniPFRelIso_all"] = tree.Muon_miniPFRelIso_all[mu]
            lep["jetPtRelv2"] = tree.Muon_jetPtRelv2[mu]
            lep["jetPtRatio"] = 1. / (tree.Muon_jetRelIso[mu] + 1.) 
            lep["pfRelIso03_all"] = tree.Muon_pfRelIso03_all[mu]
            lep["jetBTag"] = tree.Jet_btagDeepB[tree.Muon_jetIdx[mu]]
            lep["sip3d"] = tree.Muon_sip3d[mu]
            lep["dxy"] = tree.Muon_dxy[mu]
            lep["dz"] = tree.Muon_dz[mu]
            lep["segmentComp"] = tree.Muon_segmentComp[mu]
            top = tl.mvaTOPreader('UL2018')
            mu_topLeptonMVA.push_back(top.getmvaTOPScore((lep))[0])
    
        
        outTree.Fill() 
        
    inputFile.Close()   
    
    outFile.Write()
    print('outFile here: ', outFile.GetName())
    outFile.Close()
    


    
    
    
    

if __name__=='__main__':
    main()