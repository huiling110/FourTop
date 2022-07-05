# import ROOT
from ROOT import *

import csv
import os

from plotVaribles import samples, histoGramPerSample

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v16_HLTselection/mc/variableHists_v0basicWeight/'
    regionList = [ '1tau1lSR', '1tau1lCR0', '1tau1lCR1', '1tau1lCR2', '1tau1lCR3' ]

    # regionsList = [ 'SR1tau0l', 'CR1tau0l', 'VR1tau0l', 'CR21tau0l', 'CR31tau0l', 'CR41tau0l' ]

    bgsAndSignalNameList = [ 'TTTT', 'TT', 'TTX', 'VV', 'SingleTop', 'QCD', 'allBg' ]
    variable = 'jets_number'

    # baseDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baselineSelection_fromV15/results/'
    # csvFile = open( baseDir+'1tau0lCR_EY.csv', 'w')
    # csvWriter = csv.writer( csvFile, delimiter=',')

    # csvField = regionsList.copy()
    # csvField.insert(0, 'process')
    # print(regionsList)
    # csvWriter.writerow( csvField )

    # inputFile = ROOT.TFile( baseDir+'DisForEY.root', 'READ')
    # inputFile.ls()


    sumProcessHistsDict = getSummedHists( inputDir, regionList )
    print( sumProcessHistsDict )





# for iProcess in bgsAndSignalNameList:
#     print( iProcess )
#     iProcessEYList = []
#     for iRegion in regionsList:
#         iHistName = iRegion +'_'+ iProcess +'_'+variable
#         iHist = inputFile.Get( iHistName )
#         iHist.Print()
#         iProcessEYList.append(  '{:.2f}'.format( iHist.Integral()*g_lumi2016 ) ) 
#     iProcessEYList.insert(0, iProcess)
#     csvWriter.writerow( iProcessEYList  )


# print(csvFile)
# csvFile.close()




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

