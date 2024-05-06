import usefulFunc as uf
import ttttGlobleQuantity as gq
import ROOT
import pandas as pd

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450AddTauProng_v75OverlapRemovalFTau/mc/'
    
    inputDirDic = uf.getDirDic(inputDir)  
    era = uf.getEraFromDir(inputDir)
    
    cut1tau0l = 'jets_num>=8 && bjetsM_num>=3 && (elesTopMVAT_num+muonsTopMVAT_num==0) && jets_HT>450 && jets_6pt>32'
    
    tauF = 'tausF_num==1'
    notausT = 'tausT_num==0'
    tauT = 'tausT_num!=0'
    branchesToExclude = ['jets_pt_', 'jets_eta_', 'jets_btags_', 'jets_btagsPN_', 'jets_btags_PN_', 'jets_btags_PT_', 'jets_flavour_', 'HLT_PF*']
    
    
    # tauF_data,  tauT_data = createDataTree(inputDirDic, era, cut1tau0l, tauF, tauT, branchesToExclude)
    tauFGen_mc, tauTGen_mc =  createMCGenTree(inputDirDic, era, cut1tau0l, tauF, notausT)
  
    
     
    # createFRMap(tauF_data, tauT_data, tauFGen_mc, tauTGen_mc)

    

    
def createFRMap(tauF_data, tauT_data, tauFGen_mc, tauTGen_mc):
    tauF_data_pd = countFR(tauF_data)
    # tauFGen_mc_pd = countFR(tauFGen_mc)
   
   
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
    # print(pd_tauF[['tausF_1jetEtaAbs', 'tausF_1jetPt', 'TauF_eta_region', 'TauF_jetPt_region', 'tausF_prongNum', 'FRCount']])
    print(pd_tauF.head(30)[['tausF_1jetEtaAbs', 'tausF_1jetPt', 'TauF_eta_region', 'TauF_jetPt_region', 'tausF_prongNum', 'FRCount', 'combination_code']])
    
    return pd_tauF
    
    
def createMCGenTree(inputDirDic, era, cut1tau0l, tauF, tauT): 
    #!MC needs to be properly scaled
    MCSum = ['tt', 'ttX', 'WJets', 'singleTop', 'tttt']
    allMCFiles = []
    for iMC in MCSum:
        allMCFiles += getAllSubPro(era, iMC, False)
    allMCFiles = [inputDirDic['mc']+ ipro + '.root' for ipro in allMCFiles]
    print(allMCFiles)
    
    mcDF = ROOT.RDataFrame('newtree', allMCFiles)
    cut1tau0l = cut1tau0l+'&&tausF_genTauNum==1'
    basicCut = mcDF.Filter(cut1tau0l)
    tauF_mc = basicCut.Filter(tauF)
    tauT_mc = tauF_mc.Filter(tauT)
    
    proWeight = {
        'tt':
    }
    
    return tauF_mc, tauT_mc
    
def createDataTree(inputDirDic, era, cut1tau0l, tauF, tauT, branchesToExclude = []): 
    allDataFiles = getAllSubPro(era, 'jetHT') 
    allDataFiles = [inputDirDic['data']+ ipro + '.root' for ipro in allDataFiles]
    print(allDataFiles)
    dataDF = ROOT.RDataFrame('newtree', allDataFiles) 
    basicCut = dataDF.Filter(cut1tau0l)
    tauF_data = basicCut.Filter(tauF)
    tauT_data = tauF_data.Filter(tauT)
    
    tauT_data.Define('FR_weight_new', '-FR_weight')
    tauF_data.Define('FR_weight_new', 'FR_weight')
    
    # outDir = inputDirDic['mc']+ 'fakeTau/'
    # uf.checkMakeDir(outDir)
    # all_branches =  dataDF.GetColumnNames()
    # branches_to_include = [branch for branch in all_branches if branch not in branchesToExclude]
    # tauF_data.Snapshot('newtree', outDir+'tausF1tau0lSR.root', branches_to_include)
    # tauT_data.Snapshot('newtree', outDir+'tausFT1tau0lSR.root', branches_to_include)
    return tauF_data, tauT_data
    
    
def getAllSubPro(era, sumPro, isData=True):
    all = gq.histoGramPerSample
    if isData:
        return [key for key, value in all.items() if (value == sumPro and era in key)]
    else:
        return [key for key, value in all.items() if (value == sumPro)]
    
    
   
if __name__=='__main__':
    main()