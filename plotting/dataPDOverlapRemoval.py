import ROOT
import usefulFunc as uf

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v81for1tau2l_v2/data/'

    dataPDs = ['doubleMu', 'muonEG', 'eGamma', 'singleMu'] #for 2018
    
    era = uf.getEraFromDir(inputDir)
    print(era)
    dic = uf.getSubProDic(era, dataPDs) 
    for isum, list in dic.items():
        print(isum)
        for i in list:
            print(i)
        print('\n')
     
    # df_singleMu =  ROOT.RDataFrame("newtree", dic['singleMu'])
    
if __name__ == "__main__":
    main()
    
    
