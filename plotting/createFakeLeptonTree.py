import ROOT
import os
#first have to run dataPDOverlapRemoval.py 
def main():
    # inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v84fakeLeptonUpdate/data/leptonSum_2018.root'
    inputData = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline1tau2l_v2_v84fakeLeptonUpdate/data/leptonSum_2018.root'
    
    AR = 'lepTopMVAF_isAR'
    df = ROOT.RDataFrame('newtree', inputData)
    df_AR = df.Filter(AR)
    print('AR entries: ', df_AR.Count().GetValue())
    
    inputDir = os.path.dirname(inputData)
    outFile = inputDir.replace('data', 'mc') + '/fakeLepton.root'
    df_AR.Snapshot('newtree', outFile)
    print(f'Output file: {outFile}')
    
    
    
if __name__ == '__main__':  
    main()
    