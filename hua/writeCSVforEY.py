# import ROOT
from ROOT import *

import csv
import os
import pandas as pd

# from plotVaribles import  histoGramPerSample, summedProcessList
from ttttGlobleQuantity import  histoGramPerSample, summedProcessList
import usefulFunc as uf

def main():
    inputDir = {
        # 'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baseline_v18HLTSelection/mc/variableHists_v0forCutFlow/',
        # 'data' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baseline_v18HLTSelection/data/variableHists_v0forCutFlow/',
        # 'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/mc/variableHists_v0forCutFlow/',
        # 'data' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/data/variableHists_v0forCutFlow/',
        # 'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/mc/variableHists_v1FixedSumgenWeight/',
        # 'data' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/data/variableHists_v1FixedSumgenWeight/',
        # 'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/mc/variableHists_v2SwitchedCRVR/',
        # 'data' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v18HLTSelection/data/variableHists_v2SwitchedCRVR/',
        # 'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v19HLTSelection/mc/variableHists_v0/',
        # 'data' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v19HLTSelection/data/variableHists_v0/',
        # 'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v19HLTSelection/mc/',
        # 'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/objectSelectionResults/v19HLTSelection/data/'
        'mc' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v19HLTSelection/mc/variableHists_v3onlyGenWeight/',
        'data' : '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v19HLTSelection/data/variableHists_v3onlyGenWeight/',
    }
    # variableList = [ 'jetsNumber_initial', 'jetsNumber_HLT', 'jetsNumber_baseline' ]
    # regionList = [ '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4'] 
    # regionList = [ '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']
    regionList = [ '1tau1lSR', '1tau1lCR0', '1tau1lCR1', '1tau1lCR2', '1tau1lCR3', 'baseline' ]

    # variableList = ['jetsNumber_forYieldCount']
    variableList = ['onlyGenWeight']
    # regionList = [ 'baseline', '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']

    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDir, regionList, ivar )
    print( sumProcessPerVar )

    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', '1tau0lEYinRegions.csv' )
    # writeHistsToCSV_cutflow( sumProcessPerVar, inputDir['mc']+'results/', 'preChannelCutflow_2016Pre.csv', False, True )
    # writeHistsToCSV_cutflow( sumProcessPerVar, inputDir['mc']+'results/', 'preChannelCutflow_2016Post_withRaw.csv', True )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'cutFlow_objectSelection.csv')
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'cutFlowRaw_objectSelection.csv', True )



def writeHistsToCSV_cutflow(  sumProcessPerVar , outDir, fileName, includeRaw=False, includeEfficiency=True ):
    print('\n')
    print('start to write hists to csv')
    if not os.path.exists( outDir ): os.mkdir( outDir )
    firstVar = list(sumProcessPerVar.keys())[0]
    region = list(sumProcessPerVar[firstVar].keys())[0]

    data = {}
    for iVar in sumProcessPerVar.keys():
        iList = []
        iListRaw = []
        # iListEfficiency = []
        # for iProcess in sumProcessPerVar[iVar][region].keys():
        for iProcess in summedProcessList:
            iList.append( sumProcessPerVar[iVar][region][iProcess].Integral() )
            iListRaw.append( sumProcessPerVar[iVar][region][iProcess].GetEntries() )
        data[iVar] = iList
        if includeRaw:  data[ iVar+'rawEntries'] = iListRaw 
    # print( data )
    df = pd.DataFrame(data, summedProcessList )
    df.loc["totalMC"] =  df.drop("data").sum(axis=0, numeric_only=True)        
    df.loc["data/totalMC"] = df.loc["data"]/df.loc["totalMC"]
    

    # if includeEfficiency:
    #     df['HLTEff'] = df['jetsNumber_HLT']/df['jetsNumber_initial']
    #     df['baselineEff'] = df['jetsNumber_baseline']/df['jetsNumber_HLT']

    pd.set_option('display.float_format','{:.2f}'.format)
    print(df)

    df.to_csv( outDir + fileName ) 

    print( 'done writen csv file here: ', outDir+fileName )


def writeHistsToCSV( sumProcessPerVal, outDir , csvName, isRawEntries=False):
    print('\n')
    print('start to write hists to csv')
    uf.checkMakeDir( outDir )

    data = {}
    variable = list(sumProcessPerVal.keys())[0]
    for iregion in sumProcessPerVal[variable].keys():
        iList = []
        for iProcess in summedProcessList:
            if ('SR' in iregion) and iProcess=='data':
                iList.append('-1')
            else: 
                if not isRawEntries:
                    iList.append( sumProcessPerVal[variable][iregion][iProcess].Integral() )
                else:
                    iList.append( sumProcessPerVal[variable][iregion][iProcess].GetEntries() )
        data[iregion] = iList

    df = pd.DataFrame( data, index=summedProcessList )
    # df.loc['totalBG'] = df.drop('data', 'tttt').sum(axis=0, numeric_only=True)       
    df.loc["totalMC"] =  df.drop("data").sum(axis=0, numeric_only=True)
    df.loc['totalbg'] = df.loc['tt'] + df.loc['qcd'] +df.loc['ttX'] +df.loc['VV']+ df.loc['singleTop']
    df.loc["data/totalMC"] = df.loc["data"]/df.loc["totalMC"]

    # df['HLTeff'] = df['HLT']/df['initial']
    # df['preeff'] = df['preSelection']/df['HLT']

    df['process'] = df.index
    pd.set_option('display.float_format','{:.2f}'.format)
    print( df )

    df.to_csv( outDir+csvName, float_format='%.2f')
    print( 'done writen csv file here: ', outDir+csvName )





def getSummedHists( inputDir, regionsList, variable='jetsNumber_forYieldCount' ):
    allSubProcess = histoGramPerSample.keys()
    sumProcessHistsDict = {}
    mcFileList = os.listdir( inputDir['mc'] )
    dataFileList = os.listdir ( inputDir['data'] )

    # for ifile in os.listdir( inputDir ):
    for ifile in mcFileList+dataFileList:
        ifileName = ifile.split('_variableHists')[0]
        print('ifileName: ', ifileName )
        if not ifileName in allSubProcess: continue
        if 'jetHT' in ifileName:
            iRootFile = TFile( inputDir['data']+ifile, 'READ' )
        else:
            iRootFile = TFile( inputDir['mc']+ifile, 'READ' ) 
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

