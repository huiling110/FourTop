import usefulFunc as uf
import ttttGlobleQuantity as gq
import ROOT
import pandas as pd
import os

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHardro_FRweightSys_v79HadroPresel/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHardro_FRweightSys_v79HadroPresel/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardro_btagMTWeight_v76WithVLLAllMass/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2cut1tau0lSRTauF_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2cut1tau0lSRTauF_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v80addTauJetVar/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroFRUpdated_v85HadroPreselTauOverlap0.5/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithGammaRemoval/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHardroFRUpdated_v86HadroPreSelWithTTWTTZNLO/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v93HadroPreJetVetoPileupID/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v93HadroPreJetVetoPileupID/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFR_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/mc/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/mc/'
    is1tau2l = False 
    # is1tau2l = True 
    ifMorphTauPt = False
    # ifMorphTauPt = True
   
    
    
    inputDirDic = uf.getDirDic(inputDir)  
    era = uf.getEraFromDir(inputDir)
    
    print(era)
    
    postFix = '_ptNotMorphed'
    createFakeTauTree(inputDirDic, era, is1tau2l, '', postFix, ifMorphTauPt ) 
    createFakeTauTree_mc(inputDirDic, era, is1tau2l, '', postFix, ifMorphTauPt) 
    
    # makeOtherMCGen(inputDirDic, era) #!for BDT training, MC processes have to be gen tau
   
    #!For testing fake tau in 1tau1l and 1tau2l
    # lep1Cut = '(elesTopMVAF_1isTight || muonsTopMVAF_1isTight) && lepTopMVAF_num==1'
    # channelSel = f'{lep1Cut} && jets_num>=6 && bjetsM_num>=2'   
    # channelSel = f'{lep1Cut} && jets_num>=7 && bjetsM_num>=3'
    # postFix = '_1tau1lAllRegion'
    
    # channelSel = '(elesTopMVAT_num==0 && muonsTopMVAT_num==0) && jets_num>=6 && bjetsM_num==2'
    # postFix = '_1tau0lMR'
    
    # lepPreSel = 'jets_num>=2 && bjetsM_num>=1 && jets_HT>200. && lepTopMVAT_1pt>25. && lepTopMVAT_2pt>13.  && !lepTopMVAT_2ifZVeto'
    # isTight_2L = '(elesTopMVAF_1isTight && elesTopMVAF_2isTight) || (muonsTopMVAF_1isTight && muonsTopMVAF_2isTight) || (elesTopMVAF_1isTight && muonsTopMVAF_1isTight) || (elesTopMVAF_2isTight && muonsTopMVAF_2isTight)'
    # lep2Cut = f'lepTopMVAF_num==2 && ({isTight_2L})'
    # channelSel = f'&& {lep2Cut} && jets_num>=4 && bjetsM_num>=2 && {lepPreSel}'
    # postFix = '_1tau2lSR'
    # channelSel = f'&& {lep2Cut} && !(jets_num>=4 && bjetsM_num>=2) && {lepPreSel}'
    # postFix = '_1tau2lCR2'
    # createFakeTauTree(inputDirDic, era, is1tau2l, channelSel, postFix)
    # createFakeTauTree_mc(inputDirDic, era, is1tau2l, channelSel, postFix)
    # createFakeTauTree_Gen(inputDirDic, era, is1tau2l, channelSel, postFix)#fakeTau from gen jet, to be compared with faketau from data-driven
    
    
    
  
    
     
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
    allDataFiles = [inputDirDic['data']+ ipro + '.root' for ipro in allDataFiles]
    print('all data files: ', allDataFiles)
    
    dataDF = ROOT.RDataFrame('newtree', allDataFiles)
    dataAR  = dataDF.Filter(f'tausF_num==1 && !tausF_1isTight{extraSel}') 
    print('extra selection: ', extraSel)
    
    print('AR entries: ', dataAR.Count().GetValue())
    
    all_columns = dataAR.GetColumnNames() 
    columns_to_remove = ['tausT_1pt', 'tausT_1eta', 'tausT_1mass', 'tausT_1phi', 'tausT_1decayMode']
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    
    dataAR.Snapshot('newtree', inputDirDic['mc']+ 'fakeTau_data.root', columns_to_keep)
    
    dataAR_new = ROOT.RDataFrame('newtree', inputDirDic['mc']+ 'fakeTau_data.root')
    dataAR_new = dataAR_new.Define('tausT_1pt', 'tausF_1pt') #!No need for this, as from data tauF quantities are tauT quantities
    dataAR_new = dataAR_new.Define('tausT_1eta', 'tausF_1eta')
    dataAR_new = dataAR_new.Define('tausT_1phi', 'tausF_1phi')
    dataAR_new = dataAR_new.Define('tausT_1decayMode', 'tausF_1decayMode')
    
    dataAR_new = dataAR_new.Define('FR_weight_final', 'FR_weight')
    dataAR_new = dataAR_new.Define('FR_weight_final_up', 'FR_weight_up')
    dataAR_new = dataAR_new.Define('FR_weight_final_down', 'FR_weight_down')
    #!!!Reweight fake tau based on tau pt to account for the residual dependance of tau pt
    #create a new branch depending on tau pt, and reweight the fake tau based on this branch
    
    outFile = inputDirDic['mc'] + f'fakeTau_data{extraPostfix}.root' 
    dataAR_new.Snapshot('newtree', outFile)
    
    if ifMorphTauPt:
        correctTausF_1pt(outFile)
    print('fakeTau_data file: ', outFile, ' done')
     
  
def createFakeTauTree_mc(inputDirDic, era, is1tau2l=False, extraSel='', extraPostfix = '', ifMorphTauPt = False): 
    #creat MC fake tau tree
    #todo: consider more filtering, currently 4Million events afrer filtering
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'Minor']#!not subtracting qcd here, it is okay because we only estimate fake tau in 0 lepton channel
    allMC = []
    allMC += uf.getAllSubPro(era, MCSum, False)
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMC]
    print(allMCFiles)
    
    df = ROOT.RDataFrame('newtree', allMCFiles)
    tauFCut = f'tausF_num==1 && !tausF_1isTight && tausF_1genFlavour!=0' #not prompt tau and prompt e or mu 
    df_tauF = df.Filter(tauFCut)
    
    print('all entries: ', df.Count().GetValue())
    print('tauF entries: ', df_tauF.Count().GetValue())
    
    #have to replace tauT varibles for MC too
    all_columns = df_tauF.GetColumnNames() 
    columns_to_remove = ['tausT_1pt', 'tausT_1eta', 'tausT_1mass', 'tausT_1phi', 'tausT_1decayMode']
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    df_tauF.Snapshot('newtree', inputDirDic['mc']+ 'fakeTau_MC.root', columns_to_keep)
    
    df_tauF_new = ROOT.RDataFrame('newtree', inputDirDic['mc']+ 'fakeTau_MC.root') 
    df_tauF_new = df_tauF_new.Define('tausT_1pt', 'tausF_1pt') #!use tausF kinematic for tauT
    df_tauF_new = df_tauF_new.Define('tausT_1eta', 'tausF_1eta')
    df_tauF_new = df_tauF_new.Define('tausT_1phi', 'tausF_1phi')
    df_tauF_new = df_tauF_new.Define('tausT_1decayMode', 'tausF_1decayMode')
    
    btagHLTWeight = 'triggerSFLep_weight*btagWPMT_weight*elesTopMVAT_weight_new*musTopMVAT_weight_new' if is1tau2l else  'btagShape_weight*btagShapeR*HLT_weight'
    # df_tauF_new = df_tauF_new.Define('FR_weight_final', '-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    # df_tauF_new = df_tauF_new.Define('FR_weight_final_up', '-1.*FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    # df_tauF_new = df_tauF_new.Define('FR_weight_final_down', '-1.*FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagShape_weight*btagShapeR')
    df_tauF_new = df_tauF_new.Define('FR_weight_final', f'-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*tauT_IDSF_weight_new*{btagHLTWeight}')
     
    df_tauF_new = df_tauF_new.Define('event_allWeight_1tau0l', 'FR_weight_final')#for later BDT training
    
    outFile = inputDirDic['mc'] + f'fakeTau_MC{extraPostfix}.root'
    df_tauF_new.Snapshot('newtree', outFile)
    
    if ifMorphTauPt:
        correctTausF_1pt(outFile)
    print(inputDirDic['mc']+ outFile) 
    
    
def createFakeTauTree_Gen(inputDirDic, era, is1tau2l=False, extraSel='lepTopMVAT_num==0', postfix = '_1tau1l'):
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt', 'Minor']
    allMCList = uf.getAllSubPro(era, MCSum, False)
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMCList] 
    print(allMCFiles)
   
    df = ROOT.RDataFrame('newtree', allMCFiles)
    # tauFCut = f'tausF_num==1 && tausF_1isTight && tausF_1genFlavour==0 {extraSel}' #prompt tau and prompt e or mu  
    tauFCut = f'tausF_num==1 && tausF_1isTight && !(tausF_1genFlavour==5 || tausF_1genFlavour==1 ||tausF_1genFlavour==3) {extraSel}' #prompt tau and prompt e or mu  
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

# def correctTausF_1pt(df_tauF_data_new, inputDirDic):
def correctTausF_1pt(fakeTauFile):
    # mapping_expression = (
    # f"tausF_1pt * (TMath::Exp({0.00034} + {0.00172}*tausF_1pt) + {0.00172}) + {0.00172}"
    # )
    mapping_expression = (
    f"tausF_1pt * (TMath::Exp({-0.00036} + {0.00105}*tausF_1pt) + {0.00105}) + {0.00105}"
    )

    df_tauF = ROOT.RDataFrame('newtree', fakeTauFile)
    all_columns = list(df_tauF.GetColumnNames()) + ['tausF_1pt_corrected']
    df_tauF = df_tauF.Define('tausF_1pt_corrected', mapping_expression)
    columns_to_remove = ['tausF_1pt']
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    df_tauF.Snapshot('newtree', fakeTauFile, columns_to_keep)
    
    df_tauF_new = ROOT.RDataFrame('newtree', fakeTauFile)
    df_tauF_new = df_tauF_new.Define('tausF_1pt', 'tausF_1pt_corrected')
    df_tauF_new.Snapshot('newtree', fakeTauFile)

    # df_tauF_data = ROOT.RDataFrame('newtree', inputDataFile)
    # all_columns = list(df_tauF_data.GetColumnNames()) + ['tausF_1pt_corrected']
    # df_tauF_data_new = df_tauF_data_new.Define('tausF_1pt_corrected', mapping_expression)
    print('tausF_1pt morphed!!!' )



 
if __name__=='__main__':
    main()