import usefulFunc as uf
import ttttGlobleQuantity as gq
import ROOT
import pandas as pd
import os

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450AddTauProng_v75OverlapRemovalFTau/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineAddFRWeight_v75OverlapRemovalFTau/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_newTriSFBinD_v75OverlapRemovalFTau/mc/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baselineHardro_FRweightSys_v76WithVLLSample/mc/'
    
    inputDirDic = uf.getDirDic(inputDir)  
    era = uf.getEraFromDir(inputDir)
    
    # cut1tau0l = 'jets_num>=8 && bjetsM_num>=3 && (elesTopMVAT_num+muonsTopMVAT_num==0) && jets_HT>450 && jets_6pt>32'
    cut1tau0l = 'tausF_num==1' #!no channel specific selection
    
    tauF = 'tausF_num==1'
    tauT = 'tausT_num!=0'
    branchesToExclude = ['jets_pt_', 'jets_eta_', 'jets_btags_', 'jets_btagsPN_', 'jets_btags_PN_', 'jets_btags_PT_', 'jets_flavour_', 'HLT_PF*']
    
    
    createDataTree(inputDirDic, era, cut1tau0l, tauF, tauT, branchesToExclude)
    createMCGenTree(inputDirDic, era, cut1tau0l, tauF, tauT)
  
    # makeOtherMCGen(inputDirDic, era) #for eazier BDT training later
    
     
def makeOtherMCGen(inputDirDic, era):
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt']
    for iPro in MCSum:
        isubPros = getAllSubPro(era, iPro, False)
        print(isubPros)
        for isubPro in isubPros:
            ifile = inputDirDic['mc']+ isubPro + '.root'
            iDF = ROOT.RDataFrame('newtree', ifile)
            # cut = iDF.Filter('tausT_genTauNum==1')
            cut = iDF.Filter('tausT_genTauNum==1&&tausT_num==1')
            cut = cut.Define('event_allWeight_1tau0l', 'global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new* btagShape_weight * btagShapeR')#!1tau0l
            
            cut.Snapshot('newtree', inputDirDic['mc']+ isubPro + '_tauGen.root')
            # os.remove(ifile)
            # os.rename(inputDirDic['mc']+ isubPro + 'temp.root', ifile)
            print('cut on tauTgen done on file: ',  inputDirDic['mc']+ isubPro + '_tauGen.root', '\n')
        
    

    
   
   
    
    
def createMCGenTree(inputDirDic, era, cut1tau0l, tauF, tauT): 
    #!MC needs to be properly scaled
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt']
    allMC = []
    for iMC in MCSum:
        allMC += getAllSubPro(era, iMC, False)
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMC]
    print(allMCFiles)
    
    mcDF = ROOT.RDataFrame('newtree', allMCFiles) 
    basicCut = mcDF.Filter(cut1tau0l+'&& tausF_genTauNum==1')
    tauF_mc = basicCut.Filter(tauF)
    tauT_mc = tauF_mc.Filter(tauT) 
    
    tauF_mc = tauF_mc.Define('FR_weight_final', '-1.*FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagWPMedium_weight')
    tauT_mc = tauT_mc.Define('FR_weight_final', 'FR_weight*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagWPMedium_weight')
    
    tauF_mc = tauF_mc.Define('FR_weight_final_up', '-1.*FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagWPMedium_weight')
    tauF_mc = tauF_mc.Define('FR_weight_final_down', '-1.*FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagWPMedium_weight')
    tauT_mc = tauT_mc.Define('FR_weight_final_up', 'FR_weight_up*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagWPMedium_weight')
    tauT_mc = tauT_mc.Define('FR_weight_final_down', 'FR_weight_down*global_weight*EVENT_genWeight*EVENT_prefireWeight*PUweight_*HLT_weight*tauT_IDSF_weight_new*btagWPMedium_weight')
    
    
    tauF_mc = tauF_mc.Define('event_allWeight_1tau0l', 'FR_weight_final')#for later BDT training
    tauT_mc = tauT_mc.Define('event_allWeight_1tau0l', 'FR_weight_final')
    
    tauF_mc.Snapshot('newtree', inputDirDic['mc']+ 'fakeTau_tauFGen.root')
    print(inputDirDic['mc']+ 'fakeTau_tauFGen.root' + ' done')
    tauT_mc.Snapshot('newtree', inputDirDic['mc']+ 'fakeTau_tauTGen.root')
    print(inputDirDic['mc']+ 'fakeTau_tauTGen.root' + ' done')
   
    

    

    
def createDataTree(inputDirDic, era, cut1tau0l, tauF, tauT, branchesToExclude = []): 
    allDataFiles = getAllSubPro(era, 'jetHT') 
    allDataFiles = [inputDirDic['data']+ ipro + '.root' for ipro in allDataFiles]
    print(allDataFiles)
    dataDF = ROOT.RDataFrame('newtree', allDataFiles) 
    basicCut = dataDF.Filter(cut1tau0l)
    tauF_data = basicCut.Filter(tauF)
    tauT_data = tauF_data.Filter(tauT)
    
    tauF_data = tauF_data.Define('FR_weight_final', "FR_weight")
    tauT_data = tauT_data.Define('FR_weight_final', '-1.* FR_weight')
    
    tauF_data = tauF_data.Define('FR_weight_final_up', "FR_weight_up")
    tauF_data = tauF_data.Define('FR_weight_final_down', "FR_weight_down")
    tauT_data = tauT_data.Define('FR_weight_final_up', '-1.* FR_weight_up')
    tauT_data = tauT_data.Define('FR_weight_final_down', '-1.* FR_weight_down')
    
    tauF_data = tauF_data.Define('event_allWeight_1tau0l', 'FR_weight_final')#for later BDT training
    tauT_data = tauT_data.Define('event_allWeight_1tau0l', 'FR_weight_final')
    # print(tauF_data.GetColumnNames())
    # print(tauT_data.GetColumnNames())
    tauF_data.Snapshot('newtree', inputDirDic['mc']+ 'fakeTau_tauF.root')
    print(inputDirDic['mc']+ 'fakeTau_tauF.root' + ' done')
    tauT_data.Snapshot('newtree', inputDirDic['mc']+ 'fakeTau_tauT.root')
    print(inputDirDic['mc']+ 'fakeTau_tauT.root' + ' done')
    print('\n')
    
    
def getAllSubPro(era, sumPro, isData=True):
    all = gq.histoGramPerSample
    if isData:
        return [key for key, value in all.items() if (value == sumPro and era in key)]
    else:
        return [key for key, value in all.items() if (value == sumPro)]
    
    
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
   
if __name__=='__main__':
    main()