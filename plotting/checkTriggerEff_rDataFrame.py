import ROOT

# Create an RDataFrame for the dataset
# input = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/output/2022preEE/tree_1.root'
input = '/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelectionOptimized/output/2018/outTree_0.root'



df = ROOT.RDataFrame('tree', input)

def checkTrig1tau1l(df):
    tauT1Cut =  df.Filter('tausT_pt.size()==1')
    tau1l1Cut = tauT1Cut.Filter('muonsTopMVAT_pt.size()+elesTopMVAT_pt.size()==1')
    tau1l1CutCount = tau1l1Cut.Count()
    
    tauTCut = df.Filter('tausT_pt.size()>0')
    
    
    harTrigger = 'HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_'
    harTriggerCut = tau1l1Cut.Filter(harTrigger)
    
    
    print('initial=', df.Count().GetValue(), '1tau1l=', tau1l1CutCount.GetValue(), 'BR=', tau1l1CutCount.GetValue()/df.Count().GetValue())
    print('initial=', df.Count().GetValue(), '>=1tauT=', tauTCut.Count().GetValue(), 'BR=', tauTCut.Count().GetValue()/df.Count().GetValue())
    
    


def checkDileptonTri(df):
    tau12lCut = df.Filter('tausT_pt.size()==1 && muonsTopMVAT_pt.size()+elesTopMVAT_pt.size()==2')
    
    dileptonTri = 'HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ || HLT_Mu12_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ_ || HLT_Mu23_TrkIsoVVL_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_ || HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ_'
    dileptonTriSel = tau12lCut.Filter(dileptonTri)
    dileptonCount = dileptonTriSel.Count().GetValue()
    tau12lCutCount = tau12lCut.Count()
    
    hardronicTrigger = 'HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59_ || HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94_ || HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5_'
    hardronicTriggerSel = tau12lCut.Filter(hardronicTrigger)
    hardronicTriggerSelCount = hardronicTriggerSel.Count()
    
    dileptonAndSig = dileptonTri+'||HLT_IsoMu27_||HLT_Ele32_WPTight_Gsf_'
    dileptonAndSigSel = tau12lCut.Filter(dileptonAndSig)
    dileptonAndSigSelCount = dileptonAndSigSel.Count()
    print('1tau2l=', tau12lCutCount.GetValue(), ' dileptonAndSigTri|1tau2l=', dileptonAndSigSelCount.GetValue(), ' triggerEff=', dileptonAndSigSelCount.GetValue()/tau12lCutCount.GetValue())
    
    print('1tau2l=', tau12lCutCount.GetValue(), ' dileptonTri|1tau2l=', dileptonCount, ' triggerEff=', dileptonCount/tau12lCutCount.GetValue())
    print('1tau2l=', tau12lCutCount.GetValue(), ' hardronicTriggerSel=', hardronicTriggerSelCount.GetValue(), ' triggerEff=', hardronicTriggerSelCount.GetValue()/tau12lCutCount.GetValue())

def checkHardronicTrigger(df):
    #offline cut
    mediumTauSel = df.Filter('tausT_pt.size()>0')
    tightTauSel = df.Filter('tausTT_pt.size()>0')
    tightTTauSel = df.Filter('tausTTT_pt.size()>0')
    tau1Lep1 = mediumTauSel.Filter('muonsT_pt.size()+elesMVAT_pt.size()==1')
    tau1Lep0 = mediumTauSel.Filter('muonsT_pt.size()+elesMVAT_pt.size()==0')
    tau1Lep1T = tightTauSel.Filter('muonsT_pt.size()+elesMVAT_pt.size()==1')
    tau1Lep0T = tightTauSel.Filter('muonsT_pt.size()+elesMVAT_pt.size()==0')
    tauTT1Lep1 = tightTTauSel.Filter('muonsT_pt.size()+elesMVAT_pt.size()==1')
    # tau1Mu1 = mediumTauSel.Filter('muonsT_pt.size()==1')
    # tau1Ele1 = mediumTauSel.Filter('elesMVAT_pt.size()==1')


    #triggers
    hardronicTrigger = 'HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59_ ||HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94_||HLT_PFJet500_'
    hardronicTriggerSel = mediumTauSel.Filter(hardronicTrigger)
    hardonicTriggerSelTT = tightTauSel.Filter(hardronicTrigger)
    harTri_1tau1l = tau1Lep1.Filter(hardronicTrigger)
    harTri_1tau1lT = tau1Lep1T.Filter(hardronicTrigger)
    #tau triggers 
    tauLepTrigger = 'HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_||HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1_'
    singleTauTrigger = 'HLT_LooseDeepTauPFTauHPS180_L2NN_eta2p1_'
    tauLepTriggerSel = tau1Lep1.Filter(tauLepTrigger)
    tauLepTriggerSelT = tau1Lep1T.Filter(tauLepTrigger)
    tauLepSinTriggerSel = tau1Lep1.Filter(tauLepTrigger+'||'+singleTauTrigger)
    tauLepSinTriggerSelT = tau1Lep1T.Filter(tauLepTrigger+'||'+singleTauTrigger)
    tauLepTriggerRaw = df.Filter(tauLepTrigger)
    # tauMuTrigger = tau1Mu1.Filter('HLT_IsoMu20_eta2p1_LooseDeepTauPFTauHPS27_eta2p1_CrossL1_')
    # tauEleTrigger = tau1Ele1.Filter('HLT_Ele24_eta2p1_WPTight_Gsf_LooseDeepTauPFTauHPS30_eta2p1_CrossL1_')
    tauLepTri_TTtau = tauTT1Lep1.Filter(tauLepTrigger)

    # print('1tau1mu=', tau1Mu1.Count().GetValue(), ' tauMuTrigger=', tauMuTrigger.Count().GetValue(), ' triggerEff=', tauMuTrigger.Count().GetValue()/tau1Mu1.Count().GetValue())
    # print('1tau1ele=', tau1Ele1.Count().GetValue(), ' tauEleTrigger=', tauEleTrigger.Count().GetValue(), ' triggerEff=', tauEleTrigger.Count().GetValue()/tau1Ele1.Count().GetValue())



    initial = df.Count().GetValue()
    mediumTauSelCount = mediumTauSel.Count()
    tightTauSelCount = tightTauSel.Count()
    hardronicTriggerSelCount = hardronicTriggerSel.Count()
    tau1Lep1Count = tau1Lep1.Count()
    tau1Lep0Count = tau1Lep0.Count()
    tau1Lep1TCount = tau1Lep1T.Count()
    tau1Lep0TCount = tau1Lep0T.Count()

    print('Initial=', initial, ' mediumTauSel=', mediumTauSelCount.GetValue(), ' hardronicTriggerSel: ', hardronicTriggerSelCount.GetValue(), '  triggerEff=', hardronicTriggerSelCount.GetValue()/mediumTauSelCount.GetValue())
    print('Initial=', initial, ' mediumTauSel=', mediumTauSelCount.GetValue(), ' tauLepTriggerSel=', tauLepTriggerSel.Count().GetValue(), ' trigggerEff=', tauLepTriggerSel.Count().GetValue()/mediumTauSelCount.GetValue())

    print('\n')

    print('Initial=', initial, ' tightTauSel=', tightTauSel.Count().GetValue(), ' hardonicTriggerSelTT=', hardonicTriggerSelTT.Count().GetValue(), ' trigggerEff=', hardonicTriggerSelTT.Count().GetValue()/tightTauSel.Count().GetValue())
    print('Initial=', initial, ' tightTauSel=', tightTauSelCount.GetValue(), 'lepTauTriggerSel=', tauLepTriggerSelT.Count().GetValue(), ' triggerEff=', tauLepTriggerSelT.Count().GetValue()/tightTauSelCount.GetValue())


    print('1Mtau1l=', tau1Lep1Count.GetValue(), ' tauLepTrigger=', tauLepTriggerSel.Count().GetValue(), ' triggerEff=', tauLepTriggerSel.Count().GetValue()/tau1Lep1Count.GetValue())
    print('1Mtau1l=', tau1Lep1Count.GetValue(), ' tauLep+sinTrigger=', tauLepSinTriggerSel.Count().GetValue(), ' triggerEff=', tauLepSinTriggerSel.Count().GetValue()/tau1Lep1Count.GetValue())
    print('1Mtau1l=', tau1Lep1Count.GetValue(), ' harTri_1tau1l=', harTri_1tau1l.Count().GetValue(), ' triggerEff=', harTri_1tau1l.Count().GetValue()/tau1Lep1Count.GetValue())

    print('\n')

    print('1Ttau1l=', tau1Lep1TCount.GetValue(), ' tauLepTrigger=', tauLepTriggerSelT.Count().GetValue(), ' triggerEff=', tauLepTriggerSelT.Count().GetValue()/tau1Lep1TCount.GetValue())
    print('1Ttau1l=', tau1Lep1TCount.GetValue(), ' tauLep+sinTrigger=', tauLepSinTriggerSelT.Count().GetValue(), ' triggerEff=', tauLepSinTriggerSelT.Count().GetValue()/tau1Lep1TCount.GetValue())
    print('1TTau1l=', tau1Lep1TCount.GetValue(), ' harTri_1tau1lT=', harTri_1tau1lT.Count().GetValue(), ' triggerEff=', harTri_1tau1lT.Count().GetValue()/tau1Lep1TCount.GetValue())

    print('\n')

    print('1TTtau1l=', tauTT1Lep1.Count().GetValue(), ' tauLepTrigger=', tauLepTri_TTtau.Count().GetValue(), ' triggerEff=', tauLepTri_TTtau.Count().GetValue()/tauTT1Lep1.Count().GetValue())

    print('tauLepRaw=', tauLepTriggerRaw.Count().GetValue())



    df.Report().Print()
    print('done\n')


if __name__=='__main__':
    checkDileptonTri(df)
    # checkTrig1tau1l(df)
    


