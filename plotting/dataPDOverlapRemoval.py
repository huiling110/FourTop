import ROOT
import pandas as pd
import usefulFunc as uf

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v81for1tau2l_v2/data/'

    dataPDs = ['doubleMu', 'muonEG', 'eGamma', 'singleMu'] #for 2018
    
    era = uf.getEraFromDir(inputDir)
    print(era)
    dic = uf.getSubProDic(era, dataPDs) 
    for isum, ilist in dic.items():
        print(isum)
        for i in ilist:
            print(i)
        print('\n')
     
    df_singleMu =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['singleMu']])
    print('singleMu entries: ', df_singleMu.Count().GetValue())
    print('run min= ', df_singleMu.Min("run").GetValue(), 'run max= ', df_singleMu.Max("run").GetValue())
    
    columns = df_singleMu.GetColumnNames()
    # print(columns)
    columns_pre = list(columns)
    print(columns_pre)
    df_numpy = df_singleMu.AsNumpy(columns=columns_pre)
    # # df_pandas_pre = df_singleMu.AsNumpy(columns=columns)
    print("Column names in the numpy structure:")
    for col in df_numpy.keys():
        print(col)
    print("Numpy structure:")
    for col, array in df_numpy.items():
        print(f"Column: {col}")
        print(f"  Type: {array.dtype}")
        print(f"  Shape: {array.shape}")
        print(f"  First few values: {array[:5]}")
        print()


    # df_pandas = pd.DataFrame(df_pandas_pre)
    # print(df_pandas.head())
    # print(df_pandas.columns)
    # duplicates = df_pandas[df_pandas.duplicated(subset=['event'], keep=False)]
    # if not duplicates.empty:
    #     print("Entries with the same 'event' value:")
    #     print(duplicates)
    # else:
    #     print("No duplicate 'event' values found.")
    
    
    # df_doubleMu =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['doubleMu']])
    # print('doubleMu entries: ', df_doubleMu.Count().GetValue())
    # print('run min= ', df_doubleMu.Min("run").GetValue(), 'run max= ', df_doubleMu.Max("run").GetValue())
    
    # df_muonEG =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['muonEG']]) 
    # print('muonEG entries: ', df_muonEG.Count().GetValue())
    # print('run min= ', df_muonEG.Min("run").GetValue(), 'run max= ', df_muonEG.Max("run").GetValue())
    
    # df_eGamma =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['eGamma']])
    # print('eGamma entries: ', df_eGamma.Count().GetValue())
    # print('run min= ', df_eGamma.Min("run").GetValue(), 'run max= ', df_eGamma.Max("run").GetValue()) 
    
    
   
    
if __name__ == "__main__":
    main()
    
    
