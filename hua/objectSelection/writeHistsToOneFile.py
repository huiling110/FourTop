
import os

import pandas as pd
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import (histoGramPerSample, lumiMap, samples,
                                samplesCrossSection, summedProcessList)

from makeJob_objectTSelectorForNanoAOD import (era, eraDic, inputBase,
                                               jobVersionName, outputBase)


def main():

    # iera = '2016postVFP'
    iera = '2016preVFP'
    # iera = '2016'
    inOutListMC = [ inputBase + era +'/' + 'mc/', outputBase + eraDic[era] + '/' +jobVersionName  + 'mc/' ]
    inOutListData = [ inputBase + era +'/' + 'data/',outputBase + eraDic[era] + '/' +jobVersionName  + 'data/' ]


    # genSumDic = getGenSumDic( 'genWeightCSV/genSum_2016postVFP.csv' )
    genSumDic = getGenSumDic( 'genWeightCSV/genSum_' +iera +'.csv', iera )
    lumi = lumiMap[iera]
    # fileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/' + jobVersionName
    fileDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/'+iera+'/objectSelectionResults/' + jobVersionName
    uf.checkMakeDir( fileDir )
    writeHistsOneFileOneProcess( inOutListMC[1], genSumDic, samplesCrossSection, lumi, fileDir+'mc/' )
    mergeRuns(inOutListMC[1], fileDir+'mc/')
    writeHistsOneFileOneProcess( inOutListData[1], genSumDic, samplesCrossSection, lumi, fileDir+'data/', True )


def mergeRuns( inputDir, outDir):
    uf.checkMakeDir( outDir )
    for iPro in os.listdir(outDir):
        print(iPro)
        iProcess = iPro.split('.root')[0]
        print(iProcess)
        iFile = ROOT.TFile( outDir+iPro, "UPDATE")
        iRuns = ROOT.TChain("Runs")
        iRuns.Add(inputDir+ iProcess + '/outTree*.root')
        print('merged Runs tree for ', iFile.GetName())
        iRuns.Merge(iFile, 2000)
        # iFile.Close()



#copied to 
def getGenSumDic( inputCsv, iera ):
    df = pd.read_csv( inputCsv )
    # genSumDic = pd.Series( df['2016postVFP'].values, index=df['process'] ).to_dict()
    genSumDic = pd.Series( df[iera].values, index=df['process'] ).to_dict()
    print( genSumDic )
    return genSumDic

def writeHistsOneFileOneProcess( indir, genSumDic, samplesCrossSection, lumi, outDir, isData=False ):
    uf.checkMakeDir( outDir )
    for iPro in os.listdir( indir ):
        print( iPro )
        iRootFile = ROOT.TFile( outDir+iPro+'.root', "RECREATE")
        iHist = ROOT.TH1D( 'OBinitial_' + iPro + '_' + 'forEventCount', 'initial_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHistHLT = ROOT.TH1D( 'OBHLT_' + iPro + '_' + 'forEventCount', 'HLT_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHistPre = ROOT.TH1D( 'OBpreSelection_' + iPro + '_' + 'forEventCount', 'preSelection_' + iPro + '_' + 'onlygenWeight', 2, -1, 1 )
        iHist.SetDirectory(iRootFile)

        # iRootFile.cd()
        # if 'jetHT' not in iPro:
        #     iRuns = ROOT.TChain("Runs")
        #     iRuns.SetDirectory(iRootFile)
        #     iRuns.Add( indir+iPro+ "/outTree*.root")
        #     iRuns.Merge( iRootFile, 2000);
        #     # iRuns.Print()



        for ifile in os.listdir( indir+iPro ):
            if 'log' in ifile: continue
            # print( ifile )
            iRoot = ROOT.TFile( indir+iPro+ '/'+ ifile, 'READ' )
            ihist_initial = iRoot.Get( 'h_initial' )
            ihist_HLT = iRoot.Get( 'h_afterHLT' )
            ihist_pre = iRoot.Get( 'h_afterpreSelection')
            iHist.Add( ihist_initial )
            iHistHLT.Add( ihist_HLT )
            iHistPre.Add( ihist_pre)
            # iHist.SetDirectory(iRootFile)
            iRoot.Close()

        if isData: 
            iProScale = 1.0
        else: 
            iProScale = lumi*samplesCrossSection[iPro]/genSumDic[iPro]
        iHist.Scale( iProScale )
        iHistHLT.Scale( iProScale )
        iHistPre.Scale( iProScale )
     


        iRootFile.Write()
        print( 'written: ', iRootFile.GetName() )
        iRootFile.Close()



if __name__=='__main__':
    main()
