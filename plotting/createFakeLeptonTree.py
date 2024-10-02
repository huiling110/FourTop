import ROOT
import os
#first have to run dataPDOverlapRemoval.py 
def main():
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v84fakeLeptonUpdate/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v2_v84fakeLeptonUpdate/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v2_v84fakeLeptonUpdateV2/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2lNotLepCut_v84Pre1tau2lNoLepCut/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2lNotLepCut_v84Pre1tau2lNoLepCut/data/leptonSum_2018.root'
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v84Pre1tau2lLepF2/data/leptonSum_2018.root'
    inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v84Pre1tau2lLepF2/data/leptonSum_2017.root'
    
    
    inputDir = os.path.dirname(inputData)
    outFile = inputDir.replace('data', 'mc') + '/fakeLepton.root'
    
    AR = 'lepTopMVAF_isAR'
    df = ROOT.RDataFrame('newtree', inputData)
    df_AR = df.Filter(AR)
    print('AR entries: ', df_AR.Count().GetValue())
   
    all_columns = df_AR.GetColumnNames() 
    #!replace lepTopMVAT_pt with lepTopMVAF_ptCorrected
    columns_to_remove = ["lepTopMVAT_1pt", "lepTopMVAT_2pt", "elesTopMVAT_1pt", "muonsTopMVAT_1pt", "muonsTopMVAT_2pt", "elesTopMVAT_2pt"]
    columns_to_keep = [col for col in all_columns if col not in columns_to_remove]
    # Create a new dataframe with the selected columns
    df_AR.Snapshot('newtree', outFile, columns_to_keep)
    
    df_new = ROOT.RDataFrame('newtree', outFile)
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
    