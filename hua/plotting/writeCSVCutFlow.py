import os
import ROOT
import pandas as pd

import usefulFunc as uf
import ttttGlobleQuantity as gq

def main():
    osDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/ReReco2022PreEE/v1newCrab/'
   
   
    proHistDic = {}  
    getCutFlowForDir(osDir+'mc/', proHistDic, False)
    getCutFlowForDir(osDir+'data/', proHistDic, True)
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
    
def getCutFlowForDir(indir, proHistDic, isData):
    # mcDir = osDir+'mc/'
    for ipro in os.listdir(indir):
        if ipro=='results': continue
        print(ipro)
        iCutflowHist = getCutFlowHist(indir+ipro+'/', ipro, isData)
        iCutflowHist.Print()
        proHistDic[ipro] = iCutflowHist
     
  
def getCutFlowHist(dir,proName, isData=False):
    print('getting cutflow hist for: ', dir)
    summedHist = ROOT.TH1D()
    summedSumWeight = 0
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
           
        iSumWeight = getSumWeight(rootf, isData)
        summedSumWeight = summedSumWeight+iSumWeight
        rootf.Close()
        count+=1
    scaleHist(summedHist, proName, summedSumWeight, '2022', isData) 
    
    return summedHist


def getSumWeight(rootf, isData):
    sumWeight = 0
    if not isData:
        runs = rootf.Get('Runs')
        for event in runs:
            sumWeight = sumWeight+event.genEventSumw
    return sumWeight
        
    
      
def scaleHist(summedHist, proName, sumWeight, era='2022', isData=False):
    if not isData:
        scale = (gq.lumiMap[era] * gq.samplesCrossSection[proName] )/sumWeight
        print('genSum={} lumi={} cross={}'.format(sumWeight, gq.lumiMap[era] , gq.samplesCrossSection[proName] ))
        print ('scale for ', proName,'=', scale)
        summedHist.Scale()
    
     
   
if __name__=='__main__':
    main() 
    
    