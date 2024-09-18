import ROOT
import pandas as pd
# from root_pandas import to_root

import usefulFunc as uf


ROOT.gInterpreter.Declare("""
#include <unordered_set>

std::unordered_set<ULong64_t> seen_events;

Bool_t mark_duplicates(ULong64_t event) {
    if (seen_events.find(event) == seen_events.end()) {
        seen_events.insert(event);
        return kFALSE;
    } else {
        return kTRUE;
    }
}
""")



def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v81for1tau2l_v2/data/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v82for1tau2l/data/'

    dataPDs = ['doubleMu', 'muonEG', 'eGamma', 'singleMu'] #for 2018
    
    era = uf.getEraFromDir(inputDir)
    print(era)
    dic = uf.getSubProDic(era, dataPDs) 
    for isum, ilist in dic.items():
        print(isum)
        for i in ilist:
            print(i)
        print('\n')
        
    
    df = ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['doubleMu'] + dic['muonEG'] + dic['eGamma'] + dic['singleMu']])
    print('combined df entries: ', df.Count().GetValue())
    
    # Use Define to create the 'is_duplicate' column
    df = df.Define("is_duplicate", "mark_duplicates(event)")
    print('is_duplicate type in df: ', df.GetColumnType('is_duplicate'))
    df.Display("is_duplicate", 100).Print()
    df.Snapshot('newtree', inputDir + 'leptonSumAll.root')
    print(f'Output file: {inputDir}leptonSumAll.root\n')
    
    
    # # Filter out the duplicates
    # df_filtered = df.Filter("!is_duplicate")
    df_filtered = df.Filter("is_duplicate")#!seems strange filtering behavior happens here
    print('is_duplicate type in df_filtered: ', df_filtered.GetColumnType('is_duplicate'))
    # column_names = df_filtered.GetColumnNames()
    # print("Columns in the RDataFrame:")
    # for column in column_names:
    #     column_type = df_filtered.GetColumnType(column)
    #     print(f"{column}: {column_type}")
    # exclude_columns = ['is_duplicate', 'jets_pt_', 'jets_eta_', 'jets_btags_', 'jets_btagsPN_', 'jets_btagsPT_', 'jets_flavour_']
    # include_columns = [col for col in column_names if col not in exclude_columns]
    # display = df_filtered.Display(exclude_columns,10)
    # display.Print()
    print('filtered df entries: ', df_filtered.Count().GetValue())
    df_filtered.Snapshot('newtree', inputDir + 'leptonSum.root')#!somehow not working with vector branches?
    # df_filtered.Snapshot('newtree', inputDir + 'leptonSum.root', include_columns)#!somehow not working with vector branches?
    print(f'Output file: {inputDir}leptonSum.root')

def getROOTDF(inputDir, dic, dataPD='singleMu'):
    df_singleMu =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic[dataPD]])
    print(f'{dataPD} entries: ', df_singleMu.Count().GetValue())
    print('run min= ', df_singleMu.Min("run").GetValue(), 'run max= ', df_singleMu.Max("run").GetValue())
    return df_singleMu
    
    

   
def filterWithPandas(inputDir, dic):   
    df_singleMu = getPandasDF(inputDir, dic, dataPD='singleMu')
    df_doubleMu = getPandasDF(inputDir, dic, dataPD='doubleMu')
    df_muonEG = getPandasDF(inputDir, dic, dataPD='muonEG')
    df_eGamma = getPandasDF(inputDir, dic, dataPD='eGamma')
    #seems no overlaping event in each PD with regard to 'event' value
    
    df_lepton = pd.concat([df_singleMu, df_doubleMu, df_muonEG, df_eGamma], axis=0)
    print('lepton entries: ', df_lepton.shape[0])
    
    #!check if only filtering by 'event' is enough to remove the overlap  
    duplicates = df_lepton[df_lepton.duplicated(subset='event', keep=False)]
    print('Entries with the same event value:', duplicates.shape[0])
    # Print the rows that have duplicate 'event' values
    duplicates.sort_values(by='event', inplace=True)
    print(duplicates[['event', 'run', 'jets_1pt', 'HLT_PFHT450_SixJet40_BTagCSV_p056']])
    
    df_unique = df_lepton.drop_duplicates(subset='event', keep='first')
    print('unique lepton entries: ', df_unique.shape[0])
    
    output_file = inputDir + 'leptonSum.root'
    # rdf = ROOT.RDF.MakeNumpyDataFrame(df_unique.to_dict(orient='list'))#not working
    # rdf = ROOT.RDF.MakeNumpyDataFrame(data)
    # rdf.Snapshot("newtree", output_file)
    # Convert DataFrame to a dictionary of arrays

    # Convert DataFrame to Awkward Array
    # ak_array = ak.from_iter(df_unique.to_dict(orient='list'))

    # # Create a new ROOT file and write the DataFrame to it
    # with uproot.recreate("output.root") as file:
    #     file["tree"] = {key: ak_array[key] for key in ak_array.fields}

    print(f'Output file: {output_file}')
   
   
 
     
def getPandasDF(inputDir, dic, dataPD='singleMu'):
    df_singleMu =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic[dataPD]])
    print(f'{dataPD} entries: ', df_singleMu.Count().GetValue())
    print('run min= ', df_singleMu.Min("run").GetValue(), 'run max= ', df_singleMu.Max("run").GetValue())
    
    columns = df_singleMu.GetColumnNames()
    # columns_pre = list(columns)
    columns_pre = [str(col) for col in columns]#!have to manuelly convert the column names to string
    df_numpy = df_singleMu.AsNumpy(columns=columns_pre)
    # for col in df_numpy.keys():
    #     print(col)
    # print("Numpy structure:")
    # for col, array in df_numpy.items():
    #     print(f"Column: {col}")
    #     print(f"  Type: {col.__class__}")
    #     print(f"  Type: {array.dtype}")
    #     print(f"  Shape: {array.shape}")
    #     print(f"  First few values: {array[:5]}")

    df_pandas = pd.DataFrame(df_numpy)
    # print(df_pandas.head())
    # print(df_pandas.columns)
    duplicates = df_pandas[df_pandas.duplicated(subset=['event'], keep=False)]
    if not duplicates.empty:
        print("Entries with the same 'event' value:")
        print(duplicates)
    else:
        print("No duplicate 'event' values found.")
    
    print('\n')
    return df_pandas 
    
    
    # df_muonEG =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['muonEG']]) 
    # print('muonEG entries: ', df_muonEG.Count().GetValue())
    # print('run min= ', df_muonEG.Min("run").GetValue(), 'run max= ', df_muonEG.Max("run").GetValue())
    
    # df_eGamma =  ROOT.RDataFrame("newtree", [f"{inputDir}{sub}.root" for sub in dic['eGamma']])
    # print('eGamma entries: ', df_eGamma.Count().GetValue())
    # print('run min= ', df_eGamma.Min("run").GetValue(), 'run max= ', df_eGamma.Max("run").GetValue()) 
 
    
   
    
if __name__ == "__main__":
    main()
    
    
