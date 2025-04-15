import ROOT
import os
import usefulFunc as uf


#!!!first have to run dataPDOverlapRemoval.py 
def main():
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/data/leptonSum_2017.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/data/leptonSum_2016preVFP.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/data/leptonSum_2016postVFP.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_v94LepPreJetVetoHemOnly/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/data/leptonSum_2017.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/data/leptonSum_2016preVFP.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/data/leptonSum_2016postVFP.root'
    # if1tau2l = True
   
    #1tau1l 
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v93HadroPreJetVetoPileupID/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v93HadroPreJetVetoPileupID/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFR_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/data/'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/data/'
    inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/data/'
    if1tau2l = False
   
   
   
    
    
    inputDir = os.path.dirname(inputData) if if1tau2l else inputData
    outFile = inputDir.replace('data', 'mc') + '/fakeLepton.root'
    
    AR = 'lepTopMVAF_isAR'
    if if1tau2l:
        df = ROOT.RDataFrame('newtree', inputData)
    else:
        # subDataList = uf.getAllSubPro(uf.getEraFromDir(inputData), ['jetHT'], True)
        subDataList = uf.getSubProDic(uf.getEraFromDir(inputData), ['jetHT'])
        print('subDataList: ', subDataList)
        df = ROOT.RDataFrame('newtree', [inputData+ subData+'.root' for subData in subDataList['jetHT']])
    df_AR = df.Filter(AR)
    print('AR entries: ', df_AR.Count().GetValue())
   
    all_columns = df_AR.GetColumnNames() 
    #!replace lepTopMVAT_pt with lepTopMVAF_ptCorrected
    columns_to_remove = ["lepTopMVAT_1pt", "lepTopMVAT_2pt", "elesTopMVAT_1pt", "muonsTopMVAT_1pt", "muonsTopMVAT_2pt", "elesTopMVAT_2pt"]
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    # Create a new dataframe with the selected columns
    df_AR.Snapshot('newtree', outFile, columns_to_keep)
    
    df_new = ROOT.RDataFrame('newtree', outFile)
    #!actually no need to replace leptoT pt with lepTopMVAF ptCorrected, the leptonF pt in FT region should be leptonT
    df_new = df_new.Define("lepTopMVAT_1pt", "lepTopMVAF_1ptCorrected")
    df_new = df_new.Define("lepTopMVAT_2pt", "lepTopMVAF_2ptCorrected")
    df_new = df_new.Define("elesTopMVAT_1pt", "elesTopMVAF_1ptCorrected")
    df_new = df_new.Define("muonsTopMVAT_1pt", "muonsTopMVAF_1ptCorrected")
    df_new = df_new.Define("elesTopMVAT_2pt", "elesTopMVAF_2ptCorrected")
    df_new = df_new.Define("muonsTopMVAT_2pt", "muonsTopMVAF_2ptCorrected")
    print('new columns: ', df_new.GetColumnNames())
    output_file = ROOT.TFile(outFile, "RECREATE")
    df_new.Snapshot('newtree', outFile)#overwrite the file
    print(f'Output file: {outFile}')
    
    
    
if __name__ == '__main__':  
    main()
    