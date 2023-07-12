import os
import ROOT
import pandas as pd

import usefulFunc as uf

def main():
    osDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/ReReco2022PreEE/v1newCrab/'
   
   
    proHistDic = {}  
    getCutFlowForDir(osDir+'mc/', proHistDic)
    getCutFlowForDir(osDir+'data/', proHistDic)
    print(proHistDic)
   
    outDir = osDir+'mc/results/'
    uf.checkMakeDir(outDir) 
    writeProHistsToCSV(proHistDic, outDir)
   
def writeProHistsToCSV(proHistDic, outDir): 
    df = getDataFrameFromHistDic(proHistDic)
    print(df)
    
    writeDFtoCSV(df, outDir)
    
def  writeDFtoCSV(df, outDir):
    dataList = ['JetMet2022C', 'JetMet2022D', 'JetHT2022C']
    bgList = ['TTtoLNu2Q', 'TTto2L2Nu', 'TTto4Q']
    df['data'] = df[dataList].sum(axis=1) 
    df['bg'] = df[bgList].sum(axis=1)
    print(df)
   
   
# def addDF(colist,name, df):
#     for ilist in colist:
#         df.loc[name] =
        
     
    
    
def getDataFrameFromHistDic(histDic):
    data = {}
    for ipro in histDic.keys():
        icutflow = [histDic[ipro].GetBinContent(1), histDic[ipro].GetBinContent(2), histDic[ipro].GetBinContent(3), histDic[ipro].GetBinContent(4) ]
        data[ipro] = icutflow
    iListName = ['initial', 'Metfilter', 'HLT', 'preSelection']   
    df = pd.DataFrame( data, index=iListName )
    return df
    
    
     
    
    
    
    
    
        
    
def getCutFlowForDir(indir, proHistDic):
    # mcDir = osDir+'mc/'
    for ipro in os.listdir(indir):
        print(ipro)
        iCutflowHist = getCutFlowHist(indir+ipro+'/')
        iCutflowHist.Print()
        proHistDic[ipro] = iCutflowHist
     
  
def getCutFlowHist(dir):
    print('getting cutflow hist for: ', dir)
    summedHist = ROOT.TH1D()
    count = 0
    for ifile in os.listdir(dir):
        if not '.root' in ifile: continue
        rootf = ROOT.TFile(dir+ifile, 'READ')
        iHist = rootf.Get('OScutflow')
        # iHist.Print()
        if count==0:
            summedHist = iHist.Clone()
            summedHist.SetDirectory(0)
        else:
            summedHist.Add(iHist)
        rootf.Close()
        count+=1
    return summedHist
       
   
if __name__=='__main__':
    main() 
    
    