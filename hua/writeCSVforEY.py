import csv
import os
from ctypes import c_double
# from re import I
from tokenize import Double, Number

import pandas as pd
# import ROOT
import usefulFunc as uf
from ROOT import TFile
from ttttGlobleQuantity import (histoGramPerSample, lumiMap,
                                samplesCrossSection, summedProcessList)


def main():
    # era = '2016postVFP'
    # era = '2016preVFP'
    era = '2016'
    # era = '2018'
    # inVersion = 'v0noBaseline_v27noJERnoTESWithObjectRemoval'
    # inVersion = 'v0noBaseline_v28JERTESBack'
    # inVersion = 'v0noBaseline_v29LorentzProblemSolvedNoJERnoTES'
    # inVersion = 'v1baseline_v29LorentzProblemSolvedNoJERnoTES'
    # inVersion = 'v0noBaseline_v30TESnoJER'
    # inVersion = 'v0noBaseline_v31TESandJER'
    # inVersion = 'v1baseline_v33TESnoJERCodeOptimzation'
    # inVersion = 'v1baseline_v36TESandJERByHuiling'
    # inVersion = 'v1baseline_v38TESandJERTauPt20_preselection'
    inVersion = 'v1baseline_v38TESandJERTauPt20_preselection'
    # inVersion = 'v1baseline_v37TauPt30AndPreselection'
    # histVersion = 'variableHists_v0'
    # histVersion = 'variableHists_v0forCutFlow'
    # histVersion = 'variableHists_v1variables'
    # histVersion = 'variableHists_v1variablesUsingMyclass'
    # histVersion = 'variableHists_v2addingPileupWeight'
    # histVersion = 'variableHists_v3pileUpAndNewRange'
    histVersion = 'variableHists_v4forFakeRate'

    variableList = ['eventCount']
    regionList = ["1tau0lSR", "1tau0lCR", "1tau0lCRLTau", "1tau0lVR", "1tau0lVRLTau"]
    # regionList = ["1tau0lSRGen", "1tau0lCRGen", "1tau0lCRLTauGen", "1tau0lVRGen", "1tau0lVRLTauGen"]
    csvName = '1tau0lFakeRate'
    # csvName = '1tau0lFakeRateGenTau'
    # regionList = [ '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']
    # regionList = [ '1tau0lSR', '1tau1lSR', '1tau2lSR', '2tau0lSR', '2tau1lSR']
    # regionList = ['1tau1lSR', '1tau1lCR0', '1tau1lCR1','1tau1lCR2', '1tau1lCR3']
    # regionList = ['whInitial', 'baseline1', 'baseline2', 'baseline3',  '1tau0lSRmoun', '1tau0lSRele', '1tau0lSRtau', '1tau0lSRjet', '1tau0lSRbjet'] 
    # regionList = ['whInitial', 'baseline1', 'baseline2', 'baseline3', '1tau1lSRtau', '1tau1lSRlep', '1tau1lSRjet', '1tau1lSRbjet'] 
    # csvName = '1tau0lCutflow'
    # csvName = 'channelsEY'
    # csvName = '1tau0lCRs_withUncertInverted'
    # csvName = '1tau1lCRs_withUncertInverted'






    inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/' + era +'/'
    inputDir = {
        # 'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v20FixedSelectJetsBug/mc/variableHists_v0/',
        # 'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v20FixedSelectJetsBug/data/variableHists_v0/',
        'mc': inputDirBase + inVersion + '/mc/' + histVersion + '/',
        'data': inputDirBase + inVersion + '/data/' + histVersion + '/',
    }


    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDir, regionList, ivar )
    print( sumProcessPerVar )

    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', csvName+'.csv', False, True )
    writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', csvName+'_rawEntries.csv', True, True )



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
                iList.append(-1.0)#for uncert
            else: 
                if not isRawEntries:
                    iList.append( sumProcessPerVal[variable][iregion][iProcess].Integral() )
                    ierror = c_double(-1.0)
                    iIntergral = sumProcessPerVal[variable][iregion][iProcess].IntegralAndError(1,2,ierror, '') 
                    iList.append(ierror.value)
                else:
                    iList.append( sumProcessPerVal[variable][iregion][iProcess].GetEntries() )
                    iList.append( -1.0)
        data[iregion] = iList
     
    iListName = []
    for iProcess in summedProcessList:
        iListName.append(iProcess)
        iListName.append(iProcess+'Uncert')

    # df = pd.DataFrame( data, index=summedProcessList )
    df = pd.DataFrame( data, index=iListName )
    df.loc['totalMC'] = df.loc['tt'] + df.loc['qcd'] +df.loc['ttX'] +df.loc['VV']+ df.loc['singleTop']+df.loc['tttt']


    if not writeData:
        df = df.drop('data')
    else:
        df.loc["dataDivideTotalMC"] = df.loc["data"]/df.loc["totalMC"]

    df = df.transpose()
    # df.reset_index(inplace=True)
    df['regions'] = df.index


    # df['process'] = df.index
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

