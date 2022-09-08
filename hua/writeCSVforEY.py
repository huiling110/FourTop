import csv
import os

import pandas as pd
import ROOT
import usefulFunc as uf
from ROOT import TFile
# from ROOT import *
# from plotVaribles import  histoGramPerSample, summedProcessList
from ttttGlobleQuantity import (histoGramPerSample, lumiMap,
                                samplesCrossSection, summedProcessList)


def main():
    era = '2016postVFP'
    # era = '2016preVFP'
    # inVersion = 'v0baseline_v22addedRunsTree'
    # inVersion = 'v0noBaseline_v24noJER'
    # inVersion = 'v0noBaseline_v25noJERNOTES'
    # inVersion = 'v0noBaseline_v27noJERnoTESWithObjectRemoval'
    # inVersion = 'v0noBaseline_v28JERTESBack'
    inVersion = 'v0noBaseline_v29LorentzProblemSolvedNoJERnoTES'
    # histVersion = 'variableHists_v0'
    # histVersion = 'variableHists_v2cutflow1tau0l'
    # histVersion = 'variableHists_v0forCutFlow'
    histVersion = 'variableHists_v1variables'

    variableList = ['eventCount']
    regionList = [ '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3']
    # regionList = [ '1tau0lSR', '1tau1lSR', '1tau2lSR', '2tau0lSR', '2tau1lSR']
    # regionList = ['whInitial', 'baseline1', 'baseline2', 'baseline3',  '1tau0lSRmoun', '1tau0lSRele', '1tau0lSRtau', '1tau0lSRjet', '1tau0lSRbjet'] 
    # regionList = ['whInitial', 'baseline1', 'baseline2', 'baseline3', '1tau1lSRtau', '1tau1lSRlep', '1tau1lSRjet', '1tau1lSRbjet'] 
    # csvName = '1tau1lCutflow'
    # csvName = 'channelsEY'
    csvName = '1tau0lCRs'


    # inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/'
    inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/' + era +'/'
    inputDir = {
        # 'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v20FixedSelectJetsBug/mc/variableHists_v0/',
        # 'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v20FixedSelectJetsBug/data/variableHists_v0/',
        'mc': inputDirBase + inVersion + '/mc/' + histVersion + '/',
        'data': inputDirBase + inVersion + '/data/' + histVersion + '/',
    }
    # regionList = [ '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4'] 
    # regionList = [ '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']
    # regionList = [ '1tau1lSR', '1tau1lCR0', '1tau1lCR1', '1tau1lCR2', '1tau1lCR3' ]
    # regionList = ['baseline1', 'baseline2', 'baseline3']
    # regionList = ['baseline1']


    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDir, regionList, ivar )
    print( sumProcessPerVar )

    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', csvName+'.csv' )
    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', csvName+'_rawEntries.csv', True )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'subchannels.csv' )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', 'subchannels_rawEntries.csv', True )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', '1tau0lCutflow.csv' )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', '1tau0lCutflow_rawEntries.csv', True )
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


def writeHistsToCSV( sumProcessPerVal, outDir , csvName, isRawEntries=False, writeData=False):
    print('\n')
    print('start to write hists to csv')
    uf.checkMakeDir( outDir )

    data = {}
    variable = list(sumProcessPerVal.keys())[0]
    for iregion in sumProcessPerVal[variable].keys():
        iList = []
        for iProcess in summedProcessList:
            if ('SR' in iregion) and iProcess=='data':
                iList.append(-1.0)
            else: 
                if not isRawEntries:
                    iList.append( sumProcessPerVal[variable][iregion][iProcess].Integral() )
                else:
                    iList.append( sumProcessPerVal[variable][iregion][iProcess].GetEntries() )
        data[iregion] = iList

    df = pd.DataFrame( data, index=summedProcessList )
    # df.loc['totalBG'] = df.drop('data', 'tttt').sum(axis=0, numeric_only=True)       
    # df.loc["totalMC"] =  df.drop("data").sum(axis=0, numeric_only=True)
    df.loc['totalbg'] = df.loc['tt'] + df.loc['qcd'] +df.loc['ttX'] +df.loc['VV']+ df.loc['singleTop']
    df.loc['totalMC'] = df.loc['totalbg'] + df.loc['tttt']
    # df.loc["data/totalMC"] = df.loc["data"]/df.loc["totalMC"]

    # df['HLTeff'] = df['HLT']/df['initial']
    # df['preeff'] = df['preSelection']/df['HLT']

    if not writeData:
        # df = df.drop(labels=6, axis=0)
        df = df.drop('data')

    df['process'] = df.index
    print( df )

    df.to_csv( outDir+csvName, float_format='%.2f')
    pd.set_option('display.float_format','{:.2f}'.format)
    print( 'done writen csv file here: ', outDir+csvName )





def getSummedHists( inputDir, regionsList, variable='jetsNumber_forYieldCount', ifScale=False, era = '2016postVFP' ):
    allSubProcess = histoGramPerSample.keys()
    sumProcessHistsDict = {}
    mcFileList = os.listdir( inputDir['mc'] )
    dataFileList = os.listdir ( inputDir['data'] )

    # for ifile in os.listdir( inputDir ):
    for ifile in mcFileList+dataFileList:
        # ifileName = ifile.split('_variableHists')[0]
        ifileName = ifile.split('.root')[0]
        if not ifileName in allSubProcess: continue
        iProScale = 1.0
        if ifScale and (not 'jetHT' in ifileName):
            # iProScale = getProcessScale( ifileName, '2016postVFP' )
            iProScale = getProcessScale( ifileName, era )
        print('ifileName: {}, scale: {}'.format( ifileName , iProScale) )
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
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Scale(iProScale)
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].SetDirectory(0)
                print('sumProcessHistDic[{}][{}] get hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
            else:
                itemp = iRootFile.Get( iHistName)
                itemp.Scale(iProScale)
                # sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Add(iRootFile.Get( iHistName), iProScale )
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Add( itemp)
                print('sumProcessHistDic[{}][{}] add hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
        iRootFile.Close()
        print( '\n')

    return sumProcessHistsDict


def getProcessScale( processName, era ):
    # genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_2016postVFP.csv' )[processName]
    genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_'+era+'.csv', era )[processName]
    scale = lumiMap[era]*samplesCrossSection[processName]/genWeight
    print( processName, ': ', 'genWeight= ', genWeight, ' lumi=', lumiMap[era], ' cross=', samplesCrossSection[processName],  ' scale= ', scale)
    return scale


if __name__=='__main__':
    main()

