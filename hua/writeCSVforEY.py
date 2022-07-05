# import ROOT
from ROOT import *

import csv
import os

from plotVaribles import  histoGramPerSample, summedProcessList

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/mc/variableHists_v0basicWeight/'
    regionList = [ '1tau1lSR', '1tau1lCR0', '1tau1lCR1', '1tau1lCR2', '1tau1lCR3' ]



    # baseDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/results/'



    sumProcessHistsDict = getSummedHists( inputDir, regionList )
    print( sumProcessHistsDict )

    writeHistsToCSV( sumProcessHistsDict,  inputDir+'results/', regionList )


def writeHistsToCSV( sumProcessHistDic, outDir , regionList):
    if not os.path.exists(outDir): os.mkdir(outDir)
    csvFile = open( outDir+'1tau1lCR_EY.csv', 'w')
    csvWriter = csv.writer( csvFile, delimiter=',')

    csvField = list(sumProcessHistDic.keys())
    csvField.insert(0, 'process')
    csvWriter.writerow( csvField )

    # for iProcess in sumProcessHistDic[csvField[1]].keys():
    for iProcess in summedProcessList:
        iProcessEYList = []
        for iRegion in regionList:
            print( iProcess, iRegion )
            iProcessEYList.append( '{:.2f}'.format( sumProcessHistDic[iRegion][iProcess].Integral() ) )
        iProcessEYList.insert(0, iProcess)
        print(iProcessEYList)
        csvWriter.writerow( iProcessEYList  )

    print(csvFile)
    csvFile.close()




def getSummedHists( inputDir, regionsList, variable='jetsNumber_forYieldCount' ):
    allSubProcess = histoGramPerSample.keys()
    sumProcessHistsDict = {}
    for ifile in os.listdir( inputDir ):
        ifileName = ifile.split('_variableHists')[0]
        print('ifileName: ', ifileName )
        if not ifileName in allSubProcess: continue
        iRootFile = TFile( inputDir+ifile, 'READ' )
        print('openning file: ', iRootFile.GetName() )
        # iRootFile.ls()
        for iRegion in regionsList:
            iHistName = iRegion + '_' + ifileName + '_' + variable
            if iRegion not in sumProcessHistsDict.keys(): sumProcessHistsDict[iRegion]={}
            print('iHistName: ', iHistName )
            if histoGramPerSample[ifileName] not in sumProcessHistsDict[iRegion].keys():
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]] = iRootFile.Get( iHistName).Clone()
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].SetDirectory(0)
                print('sumProcessHistDic[{}][{}] get hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
            else:
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Add(iRootFile.Get( iHistName))
                print('sumProcessHistDic[{}][{}] add hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
        iRootFile.Close()

    return sumProcessHistsDict



if __name__=='__main__':
    main()

