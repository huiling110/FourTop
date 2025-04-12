import usefulFunc as uf
import ttttGlobleQuantity as gq
import ROOT
import pandas as pd
import os

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFR_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_tauFMorphMass_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/'
    is1tau2l = False 
    # is1tau2l = True 
    # ifMorphTauPt = False
    ifMorphTauPt = True
   
    
    
    inputDirDic = uf.getDirDic(inputDir)  
    era = uf.getEraFromDir(inputDir)
    print(era)
    
    postFix = '_ptMorphed' if ifMorphTauPt else ''
    createFakeTauTree(inputDirDic, era, is1tau2l, '', postFix, ifMorphTauPt ) 
    createFakeTauTree_mc(inputDirDic, era, is1tau2l, '', postFix, ifMorphTauPt) 
    
    # makeOtherMCGen(inputDirDic, era) #!for BDT training, MC processes have to be gen tau
   
    #!For testing fake tau in 1tau1l and 1tau2l
    # lep1Cut = '(elesTopMVAF_1isTight || muonsTopMVAF_1isTight) && lepTopMVAF_num==1'
    # channelSel = f'{lep1Cut} && jets_num>=6 && bjetsM_num>=2'   
    # channelSel = f'{lep1Cut} && jets_num>=7 && bjetsM_num>=3'
    # postFix = '_1tau1lAllRegion'
    
    # lepPreSel = 'jets_num>=2 && bjetsM_num>=1 && jets_HT>200. && lepTopMVAT_1pt>25. && lepTopMVAT_2pt>13.  && !lepTopMVAT_2ifZVeto'
    # isTight_2L = '(elesTopMVAF_1isTight && elesTopMVAF_2isTight) || (muonsTopMVAF_1isTight && muonsTopMVAF_2isTight) || (elesTopMVAF_1isTight && muonsTopMVAF_1isTight) || (elesTopMVAF_2isTight && muonsTopMVAF_2isTight)'
    # lep2Cut = f'lepTopMVAF_num==2 && ({isTight_2L})'
    # channelSel = f'&& {lep2Cut} && jets_num>=4 && bjetsM_num>=2 && {lepPreSel}'
    # postFix = '_1tau2lSR'
    # channelSel = f'&& {lep2Cut} && !(jets_num>=4 && bjetsM_num>=2) && {lepPreSel}'
    # postFix = '_1tau2lCR2'
    # createFakeTauTree_Gen(inputDirDic, era, is1tau2l, channelSel, postFix)#fakeTau from gen jet, to be compared with faketau from data-driven
    # channelSel = '&& (elesTopMVAT_num==0 && muonsTopMVAT_num==0) && jets_num<8 && bjetsM_num>2'
    # postFix = '_1tau0lVRHTCut500'
    # channelSel = '&& (elesTopMVAT_num==0 && muonsTopMVAT_num==0) && jets_num>7 && bjetsM_num>2'
    # postFix = '_1tau0lSRHTCut500'
    # postFix = '_1tau0lMR'
    # postFix = '_1tau0lMRHTCut300'
    # channelSel = '&& (elesTopMVAT_num==0 && muonsTopMVAT_num==0) && jets_num>=6 && bjetsM_num==2'
    # postFix = '_1tau0lMRHTCut500'
    # postFix = postFix + '_onlyTT'
    # postFix = postFix + '_onlyQCD'
    # createFakeTauTree_Gen(inputDirDic, era, is1tau2l, channelSel, postFix)#fakeTau from gen jet, to be compared with faketau from data-driven
    # createFakeTauTree(inputDirDic, era, is1tau2l, channelSel, postFix, True)
    # createFakeTauTree_mc(inputDirDic, era, is1tau2l, channelSel, postFix, True)
    
    
  
    
     
def makeOtherMCGen(inputDirDic, era):
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt','VLLm500', 'VLLm550','VLLm600','VLLm650','VLLm700','VLLm750','VLLm800','VLLm850','VLLm900','VLLm950','VLLm1000']
    for iPro in MCSum:
        isubPros = uf.getAllSubPro(era, iPro, False)
        print(isubPros)
        for isubPro in isubPros:
            ifile = inputDirDic['mc']+ isubPro + '.root'
            iDF = ROOT.RDataFrame('newtree', ifile)
            # cut = iDF.Filter('tausT_genTauNum==1&&tausT_num==1')
            cut = iDF.Filter('tausF_num==1 && tausF_1isTight && tausF_1genFlavour!=0')
            cut = cut.Define('event_allWeight_1tau0l', 'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new* btagShape_weight * btagShapeR')#!1tau0l
            
            cut.Snapshot('newtree', inputDirDic['mc']+ isubPro + '_tauGen.root')
            print('cut on tauTgen done on file: ',  inputDirDic['mc']+ isubPro + '_tauGen.root', '\n')
        
    

    
   
   
    
    
   
    
def createFakeTauTree(inputDirDic, era, is1tau2l = False, extraSel='', extraPostfix = '', ifMorphTauPt = False):
    sumData='leptonSum' if is1tau2l else 'jetHT' 
    print('sumData: ', sumData)
    allDataFiles = uf.getAllSubPro(era, [sumData])
    print('all data files: ', allDataFiles)
    allDataFiles = [inputDirDic['data']+ ipro + '.root' for ipro in allDataFiles]
    print('all data files: ', allDataFiles)
    
    dataDF = ROOT.RDataFrame('newtree', allDataFiles)
    dataAR  = dataDF.Filter(f'tausF_num==1 && !tausF_1isTight{extraSel}') 
    print('extra selection: ', extraSel)
    
    print('AR entries: ', dataAR.Count().GetValue())
    
    # all_columns = dataAR.GetColumnNames() 
    dataAR = dataAR.Define('FR_weight_final', 'FR_weight')
    dataAR = dataAR.Define('FR_weight_final_up', 'FR_weight_up')
    dataAR = dataAR.Define('FR_weight_final_down', 'FR_weight_down')
    #!!!Reweight fake tau based on tau pt to account for the residual dependance of tau pt
    #create a new branch depending on tau pt, and reweight the fake tau based on this branch
    
    outFile = inputDirDic['mc'] + f'fakeTau_data{extraPostfix}.root' 
    dataAR.Snapshot('newtree', outFile)
    
    if ifMorphTauPt:
        # correctTausF_1pt(outFile)
        replaceTauTVar(outFile)
    print('fakeTau_data file: ', outFile, ' done')
     
  
def createFakeTauTree_mc(inputDirDic, era, is1tau2l=False, extraSel='', extraPostfix = '', ifMorphTauPt = False): 
    #creat MC fake tau tree
    #!Should probably add tttt to be subtracted too
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'Minor']#!not subtracting qcd here, it is okay because we only estimate fake tau in 0 lepton channel
    # MCSum = ['tt', 'ttX', 'WJets', 'singleTop']#!not subtracting qcd here, it is okay because we only estimate fake tau in 0 lepton channel
    # if is1tau2l:
        # MCSum.append('Minor')
    allMC = []
    allMC += uf.getAllSubPro(era, MCSum, False)
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMC]
    print(allMCFiles)
    
    df = ROOT.RDataFrame('newtree', allMCFiles)
    tauFCut = f'tausF_num==1 && !tausF_1isTight && tausF_1genFlavour!=0' #not prompt tau and prompt e or mu 
    df_tauF = df.Filter(tauFCut)
    
    print('all entries: ', df.Count().GetValue())
    print('tauF entries: ', df_tauF.Count().GetValue())
    
    
    btagHLTWeight = 'triggerSFLep_weight*btagWPMT_weight*elesTopMVAT_weight_new*musTopMVAT_weight_new' if is1tau2l else  'btagShape_weight*btagShapeR*HLT_weight'
    # df_tauF_new = df_tauF_new.Define('FR_weight_final', '-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    # df_tauF_new = df_tauF_new.Define('FR_weight_final_up', '-1.*FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    # df_tauF_new = df_tauF_new.Define('FR_weight_final_down', '-1.*FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    df_tauF = df_tauF.Define('FR_weight_final', f'-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
    df_tauF = df_tauF.Define('FR_weight_final_up', f'-1.*FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
    df_tauF = df_tauF.Define('FR_weight_final_down', f'-1.*FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
     
    df_tauF = df_tauF.Define('event_allWeight_1tau0l', 'FR_weight_final')#for later BDT training
    
    outFile = inputDirDic['mc'] + f'fakeTau_MC{extraPostfix}.root'
    df_tauF.Snapshot('newtree', outFile)
    
    if ifMorphTauPt:
        # correctTausF_1pt(outFile)
        replaceTauTVar(outFile)
    print(inputDirDic['mc']+ outFile) 
    
    
def createFakeTauTree_Gen(inputDirDic, era, is1tau2l=False, extraSel='lepTopMVAT_num==0', postfix = '_1tau1l'):
    MCSum = ['tt', 'ttX', 'qcd', 'WJets', 'singleTop'] 
    # MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt', 'Minor']
    # MCSum = ['qcd']
    allMCList = uf.getAllSubPro(era, MCSum, False)
    #remove qcd low HT files
    allMCList.remove('qcd_50to100')
    allMCList.remove('qcd_100to200')
    allMCList.remove('qcd_200to300')
    allMCList.remove('qcd_300to500')
        
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMCList] 
    print(allMCFiles)
   
    df = ROOT.RDataFrame('newtree', allMCFiles)
    tauFCut = f'tausF_num==1 && tausF_1isTight && tausF_1genFlavour==0 {extraSel}' #prompt tau and prompt e or mu  
    # tauFCut = f'tausF_num==1 && tausF_1isTight && !(tausF_1genFlavour==5 || tausF_1genFlavour==1 ||tausF_1genFlavour==3) {extraSel}' #not prompt tau and prompt e or mu  
    df_tauF = df.Filter(tauFCut)
    
    if is1tau2l:
        btagHLTWeight = 'triggerSFLep_weight'
    else:
        btagHLTWeight = 'HLT_weight'
    df_tauF = df_tauF.Define('event_allWeight_1tau1l', f'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*{btagHLTWeight}*tauT_IDSF_weight_new*elesTopMVAT_weight_new*musTopMVAT_weight_new*btagWPMT_weight*elesTopMVAT_reoSF_weight')#!1tau1l
    print('eventWeight: ', f'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*{btagHLTWeight}*tauT_IDSF_weight_new*elesTopMVAT_weight_new*musTopMVAT_weight_new*btagWPMT_weight*elesTopMVAT_reoSF_weight')
     
                        
    outFile = inputDirDic['mc']+ f'fakeTau_fromGen{postfix}.root'
    df_tauF.Snapshot('newtree', outFile)
    print(inputDirDic['mc']+ outFile)    
    
     

    
    
def countFR(tauF_data):    
    df_pd = tauF_data.AsNumpy()
    pd_tauF = pd.DataFrame(df_pd) 
    
    bins = [0, 0.8, 1.5, 3]
    labels = ['0-0.8', '0.8-1.5', '1.5-2.4']
    # pd_tauF['TauF_eta_region'] = pd.cut(pd_tauF['tausF_1jetEtaAbs'], bins=bins, labels=labels, right=False)
    pd_tauF['TauF_eta_region'] = pd.cut(abs(pd_tauF['tausF_1jetEtaAbs']), bins=bins, labels=labels, right=False)
    
    tauJetPtBins = [20.0, 30, 40.0, 50, 70.0, 90.0, 120.0,  1000.] 
    labels = ['20-30', '30-40', '40-50', '50-70', '70-90', '90-120', '120-1000']
    pd_tauF['TauF_jetPt_region'] = pd.cut(pd_tauF['tausF_1jetPt'], bins=tauJetPtBins, labels=labels, right=False)
    
    
    # grouped_counts = pd_tauF.groupby(['TauF_jetPt_region', 'TauF_eta_region'])['tausF_prongNum'].count().reset_index(name='FRCount')
    # grouped_counts = pd_tauF.groupby(['TauF_jetPt_region', 'TauF_eta_region', 'tauF_prongNum'])['tausF_prongNum'].count().reset_index(name='FRCount')
    #Grouping by multiple columns means that for each unique combination of values in these two columns, pandas will treat all rows with that combination as a single group.
    pd_tauF['FRCount'] = pd_tauF.groupby(['TauF_jetPt_region', 'TauF_eta_region', 'tausF_prongNum'])['tausF_prongNum'].transform('count')
    
    pd_tauF['combination_code'] = pd_tauF['TauF_jetPt_region'].astype(str) + '_' + pd_tauF['TauF_eta_region'].astype(str) + '_' + pd_tauF['tausF_prongNum'].astype(str)

    # df['tauCount'] = df['eta_region'].map(region_counts)
    # pd_tauF = pd.merge(pd_tauF, grouped_counts, on=['TauF_jetPt_region', 'TauF_eta_region'], how='left')
     
    # print(pd_tauF)
    pd.set_option('display.max_rows', 50)
    print(pd_tauF.head(30)[['tausF_1jetEtaAbs', 'tausF_1jetPt', 'TauF_eta_region', 'TauF_jetPt_region', 'tausF_prongNum', 'FRCount', 'combination_code']])
    
    return pd_tauF

def correctTausF_1pt(fakeTauFile):
    # mapping_expression = (
    # f"tausF_1pt * (TMath::Exp({0.00034} + {0.00172}*tausF_1pt) + {0.00172}) + {0.00172}"
    # )
    # mapping_expression = (
    # f"tausF_1pt * (TMath::Exp({-0.00036} + {0.00105}*tausF_1pt) + {0.00105}) + {0.00105}"
    # )
    # mapping_expression = (
    # f"tausF_1pt *((-{33.24302} * TMath::Exp(-{0.30112} * tausF_1pt)) + {1.08058})"
    # )# tausF pt and related variables morphed in MV step 

    df_tauF = ROOT.RDataFrame('newtree', fakeTauFile)
    # df_tauF = df_tauF.Define('tausF_1pt_corrected', mapping_expression)
    
    # ['tausT_1lepton1_charge', 'tausT_leptons_charge', 'tausT_1lepton1_deltaR', 'tausT_1phi']
    # all_columns = list(df_tauF.GetColumnNames()) + ['tausF_1pt_corrected']
    # df_tauF_new = df_tauF_new.Define('tausF_1pt', 'tausF_1pt_corrected')
    
    
    #!replace tausT variables with tausFMorphed variabels too, so that fakeTau can be used in BDT application
    
    

    # df_tauF_data = ROOT.RDataFrame('newtree', inputDataFile)
    # all_columns = list(df_tauF_data.GetColumnNames()) + ['tausF_1pt_corrected']
    # df_tauF_data_new = df_tauF_data_new.Define('tausF_1pt_corrected', mapping_expression)
    # print('tausF_1pt morphed!!!' )


def replaceTauTVar(fakeTauFile):
    df_tauF = ROOT.RDataFrame('newtree', fakeTauFile)
    #!replace tauT pt related variables with tausFMophed relatec variables
    all_columns = df_tauF.GetColumnNames() 
    VarToTausFMorph = [ 'tausT_leptonsT_invariantMass', 'tausT_invariantMass', 'tausT_1Met_transMass', 'tausT_1lepton1Met1_stransMass', 'tausT_1pt', 'jets_tausT_invariantMass', 'tausT_MHT', 'tausT_HT', 'tausT_jet1_Met_transMass', 'tausT_jet_invariantMass', 'tausT_leptonsT_transMass']#rariables to be replaced with tausFMorphed variables
    
    extraVarsFromF = ['tausT_1lepton1_deltaR', 'tausT_leptons_charge', 'tausT_1phi', 'tausT_1lepton1_charge', 'tausT_1jetEtaAbs' , 'bjetsM_tausT_minDeltaR'] #Variables to be replaced with tausF variables
    exex = [  'tausT_1eta',  'tausT_leptonsTMVA_minDeltaR', 'tausT_leptonsTopMVA_chargeMulti',  'tausT_1decayMode', 'tausT_1prongNum',   'tausT_1jetPt',  'tausT_1charge', 'tausT_1neutralIso']
    extraVarsFromF = extraVarsFromF + exex
    
    # tausF_features = ["tausF_1pt", "tausF_MHT", "tausF_HT", "tausF_invariantMass", "tausF_1Met_transMass"]#for 1tau0l BDT
    tausF_features=[]#!testing
    columns_to_remove = VarToTausFMorph + extraVarsFromF + tausF_features
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    # print('all columns now: ', df_tauF.GetColumnNames())
    df_tauF.Snapshot('newtree', fakeTauFile, columns_to_keep)
    
    df_tauF_new = ROOT.RDataFrame('newtree', fakeTauFile)
    for itauV in VarToTausFMorph:
        newBranch = itauV.replace('tausT', 'tausFMorph')
        df_tauF_new = df_tauF_new.Define(itauV, newBranch)
    for ivar in extraVarsFromF:
        newBranch = ivar.replace('tausT', 'tausF')
        df_tauF_new = df_tauF_new.Define(ivar, newBranch)
        
    for iVar in tausF_features:
        newBranch = iVar.replace('tausF', 'tausFMorph')
        df_tauF_new = df_tauF_new.Define(iVar, newBranch)
        
        
    df_tauF_new.Snapshot('newtree', fakeTauFile)
    print('tausT variables replaced with tausFMorphed variables!!!')
    print('tausT variables replaced with tausF variables!!!')
    print('tauF variables replaced with tauFMorphed variables!!!')
    print('file: ', fakeTauFile)
    


 
if __name__=='__main__':
    main()