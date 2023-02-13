import csv
import os
from ctypes import c_double
import math
from tokenize import Double, Number

import pandas as pd
import numpy as np
# import ROOT
import usefulFunc as uf
from ROOT import TFile
from ttttGlobleQuantity import (histoGramPerSample, lumiMap,
                                samplesCrossSection, summedProcessList)
from usefulFunc import getInputDic


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v44addSSLeptons/mc/variableHists_v0oldLepton/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v44addSSLeptons/mc/variableHists_v1SSLepton/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v44addSSLeptons/mc/variableHists_v2SSLepton/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v45newLepBugFixed/mc/variableHists_v0FR_oldLep/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v45newLepBugFixed/mc/variableHists_v0FR_newLep/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v45newLepBugFixed/mc/variableHists_v1FR_vetoNewLepL_repeat/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v2FR_vetoPOGlepL/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v2FR_vetoPOGMuLEleV/'

    # regionList = ["1tau0lSR", "1tau0lCR", "1tau0lCRLTau", "1tau0lVR", "1tau0lVRLTau"]
    # regionList = ["1tau0lSRGen", "1tau0lCRGen", "1tau0lCRLTauGen", "1tau0lVRGen", "1tau0lVRLTauGen"]
    # csvName = '1tau0lFakeRateTauGen'
    # csvName = '1tau0lFakeRate'
    # regionList = [ '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']
    # regionList = [ '1tau0lSR', '1tau1lSR', '1tau2lSR', '2tau0lSR', '2tau1lSR']
    # regionList = ['1tau1lSR', '1tau1lCR0', '1tau1lCR1','1tau1lCR2', '1tau1lCR3']
    # regionList = ['whInitial', 'baseline1', 'baseline2', 'baseline3',  '1tau0lSRmoun', '1tau0lSRele', '1tau0lSRtau', '1tau0lSRjet', '1tau0lSRbjet'] 
    # regionList = ['whInitial', 'baseline1', 'baseline2', 'baseline3', '1tau1lSRtau', '1tau1lSRlep', '1tau1lSRjet', '1tau1lSRbjet'] 
    # csvName = '1tau0lCutflow'
    # csvName = 'channelsEY'
    # csvName = '1tau0lCRs_withUncertInverted'
    # csvName = '1tau1lCRs_withUncertInverted'
    # regionList = [ '1tau0lSR','1tau1lSR']
    regionList = ['1tau0lSR', '1tau0lCR']
    
    ifUseFakeTau = False
    # csvName = '1tau0lFRMeasureRegions'
    csvName = 'eventYield'
    # ifUseFakeTau = True
    # csvName = '1tau0lFRMeasureRegions_fakeTau'





    variableList = ['eventCount']
    # inputDir = getInputDic(inVersion, histVersion, era)
    inputDirDic = {
        'mc': inputDir,
        'data': inputDir.replace('mc', 'data')
    }


    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    if not ifUseFakeTau:
        for ivar in variableList:
            sumProcessPerVar[ivar], sumProcessPerVarSys[ivar] = getSummedHists( inputDirDic, regionList, ivar )
    else:
        sumProcessPerVar['eventCount'] = {}
        for ire in regionList:
            ireCalList = [ ire, ire+'Gen', ire+'LTauNotT_Weighted', ire+'LTauNotTGen_Weighted']
            sumProcessPerVar_iCR = {}
            sumProcessPerVar_iCR['eventCount'] = {}
            sumProcessPerVar['eventCount'][ire] = {}
            isumProcessPerVarSys = {}
            sumProcessPerVar_iCR['eventCount'], isumProcessPerVarSys['eventCount'] = getSummedHists( inputDir, ireCalList, 'eventCount' )       
            replaceBgWithGen( inputDir, sumProcessPerVar_iCR['eventCount'], 'eventCount', ireCalList, 2, False, isumProcessPerVarSys['eventCount']  )
            sumProcessPerVar['eventCount'][ire] = sumProcessPerVar_iCR['eventCount'][ire].copy()
            
    print( sumProcessPerVar )
            
            
        
    # writeHistsToCSV( sumProcessPerVar,  inputDirDic['mc']+'results/', csvName+'.csv', False, True, ifUseFakeTau )

    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', csvName+'.csv', False, True )
    # writeHistsToCSV( sumProcessPerVar,  inputDir['mc']+'results/', csvName+'_rawEntries.csv', True, True )



    


def writeHistsToCSV( sumProcessPerVal, outDir , csvName, isRawEntries=False, writeData=False, ifFakeTau = False):
    print('\n')
    print('start to write hists to csv')
    uf.checkMakeDir( outDir )

    data = {}
    variable = list(sumProcessPerVal.keys())[0]
    firstRegion = list(sumProcessPerVal['eventCount'].keys())[0]
    for iregion in sumProcessPerVal[variable].keys():
        iList = [] #list of processes for i region
        # for iProcess in allProcesses:
        for iProcess in sumProcessPerVal['eventCount'][iregion].keys():
            if ifFakeTau and iProcess=='qcd': continue
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
    for iProcess in sumProcessPerVal['eventCount'][firstRegion].keys():
        if ifFakeTau and iProcess=='qcd': continue
        iListName.append(iProcess)
        iListName.append(iProcess+'Uncert')

    df = pd.DataFrame( data, index=iListName )
    if ifFakeTau:
        df.loc['bg'] = df.loc['tt'] + df.loc['fakeTau'] +df.loc['ttX'] +df.loc['VV']+ df.loc['singleTop'] +df.loc['WJets'] 
    else:
        df.loc['bg'] = df.loc['tt'] + df.loc['qcd'] +df.loc['ttX'] +df.loc['VV']+ df.loc['singleTop']+df.loc['WJets']
        
    df.loc['SandB'] = df.loc['bg'] + df.loc['tttt']
    df.loc['sensitivity'] = df.loc['tttt']/np.sqrt(df.loc['SandB'])
    df.loc['significance'] = np.sqrt( 2*( df.loc['SandB']*np.log(1+df.loc['tttt']/df.loc['bg']) - df.loc['tttt']) ) 


    if not writeData:
        df = df.drop('data')
    else:
        # df.loc["dataDivideTotalMC"] = df.loc["data"]/df.loc["totalMC"]
        df.loc["dataDivideTotalMC"] = df.loc["data"]/df.loc["bg"]

    df = df.transpose()
    # df.reset_index(inplace=True)
    df['regions'] = df.index


    # df['process'] = df.index
    print( df )

    df.to_csv( outDir+csvName, float_format='%.3f')
    pd.set_option('display.float_format','{:.3f}'.format)
    print( 'done writen csv file here: ', outDir+csvName )





def getSummedHists( inputDir, regionsList, variable='jetsNumber_forYieldCount', ifScale=False, era = '2016postVFP' ):
    allSubProcess = histoGramPerSample.keys()
    sumProcessHistsDict = {}
    sumProcessHistsDictSys = {}
    mcFileList = os.listdir( inputDir['mc'] )
    dataFileList = os.listdir ( inputDir['data'] )

    for ifile in mcFileList+dataFileList:
        ifileName = ifile.split('.root')[0]
        if not ifileName in allSubProcess: continue
        iProScale = 1.0
        if ifScale and (not 'jetHT' in ifileName):
            iProScale = getProcessScale( ifileName, era )
        print('ifileName: {}, scale: {}'.format( ifileName , iProScale) )
        isdata = False
        if 'jetHT' in ifileName:
            isdata = True
            iRootFile = TFile( inputDir['data']+ifile, 'READ' )
        else:
            iRootFile = TFile( inputDir['mc']+ifile, 'READ' ) 
        print('openning file: ', iRootFile.GetName() )
        for iRegion in regionsList:
            iHistName = iRegion + '_' + ifileName + '_' + variable
            if iRegion not in sumProcessHistsDict.keys(): 
                sumProcessHistsDict[iRegion]={}
                sumProcessHistsDictSys[iRegion]={}
            print('iHistName: ', iHistName )
            if histoGramPerSample[ifileName] not in sumProcessHistsDict[iRegion].keys():
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]] = iRootFile.Get( iHistName).Clone()
                if ifScale or not isdata: 
                    sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Scale(iProScale)
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].SetDirectory(0)
                print('sumProcessHistDic[{}][{}] get hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
                # sumProcessHistsDictSys[iRegion][histoGramPerSample[ifileName]] = {}
            else:
                itemp = iRootFile.Get( iHistName)
                if ifScale or not isdata: 
                    itemp.Scale(iProScale)
                # sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Add(iRootFile.Get( iHistName), iProScale )
                sumProcessHistsDict[iRegion][histoGramPerSample[ifileName]].Add( itemp)
                print('sumProcessHistDic[{}][{}] add hist: {}'.format( iRegion, histoGramPerSample[ifileName], iHistName ))
        iRootFile.Close()
        print( '\n')

    return sumProcessHistsDict, sumProcessHistsDictSys


def getProcessScale( processName, era ):
    # genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_2016postVFP.csv' )[processName]
    genWeight = uf.getGenSumDic( '../objectSelection/genWeightCSV/genSum_'+era+'.csv', era )[processName]
    scale = lumiMap[era]*samplesCrossSection[processName]/genWeight
    print( processName, ': ', 'genWeight= ', genWeight, ' lumi=', lumiMap[era], ' cross=', samplesCrossSection[processName],  ' scale= ', scale)
    return scale



def replaceBgWithGen(  inputDirDic, sumProcessIvar, var, regionList, ifGetFromMC=2, ifFR_syst=False, sumProcessIvarSys={}):
    #1tau0lCR relace with 1tauCRGen
    for ipro in sumProcessIvar[regionList[0]].keys():
        if ipro=='data': continue
        sumProcessIvar[regionList[0]][ipro] = sumProcessIvar[regionList[1]][ipro]
        
    if  ifGetFromMC==0:
        sumProcessIvar[regionList[0]]['fakeTau'] = sumProcessIvar[regionList[0]]['tttt'].Clone()
        sumProcessIvar[regionList[0]]['fakeTau'].Reset()
        sumProcessIvar[regionList[0]]['fakeTau'].Sumw2()
    #adding 'fakeTau' process from CRNotGen
        for ipro in sumProcessIvar[regionList[2]].keys():
            if ipro=='data' or ipro=='tttt': continue
            sumProcessIvar[regionList[0]]['fakeTau'].Add( sumProcessIvar[regionList[2]][ipro] ) #2 is gone 
    #scale to fake rate prediction
        sumProcessIvar[regionList[0]]['fakeTau'].Scale( fakeTauYiled[regionList[0]]/ sumProcessIvar[regionList[0]]['fakeTau'].Integral())
    if ifGetFromMC==1:
        #adding 'fakeTau' from CRLTauNotT data
        isVR = False
        if regionList[0]=='1tau0lVR': 
            isVR = True
        sumProcessIvar[regionList[0]]['fakeTau'] = getShapeFromData( inputDirDic, var,  isVR) 
        if 'eta' in var:
            ptBins = np.array( [0, 0.8, 1.6, 2.3])
        else:
            ptBins = np.array( [20.0, 30, 40.0, 50, 70.0, 90.0, 120.0,  300.0] )
        for ipro in sumProcessIvar[regionList[0]].keys() :
             sumProcessIvar[regionList[0]][ipro] = sumProcessIvar[regionList[0]][ipro].Rebin(len(ptBins)-1, '', ptBins)
    if ifGetFromMC==2:
         #get fake tau from FR weighted VVLNotT data - VVLNotTGen MC
        sumProcessIvar[regionList[0]]['fakeTau'] = histDateMinusGenBG( var, sumProcessIvar, regionList[2], regionList[3]) 
        # sumProcessIvar[regionList[0]]['fakeTau'] = sumProcessIvar[regionList[3]]['data']
        #FR sytematic
        if ifFR_syst:
            sumProcessIvarSys[regionList[0]]['fakeTau']={}
            sumProcessIvarSys[regionList[0]]['fakeTau']['FR_up'] = histDateMinusGenBG( var, sumProcessIvar, regionList[4], regionList[6] ) 
            sumProcessIvarSys[regionList[0]]['fakeTau']['FR_down'] = histDateMinusGenBG( var, sumProcessIvar, regionList[5], regionList[7] ) 
        
    #fake tau come from data
    # for ibin in range(sumProcessIvar[regionList[0]]['fakeTau'].GetNbinsX()):
    #     sumProcessIvar[regionList[0]]['fakeTau'].SetBinError(ibin+1, 0)
    print('checking data={}, fakeTau={} '.format(sumProcessIvar[regionList[0]]['data'].Integral(), sumProcessIvar[regionList[0]]['fakeTau'].Integral()))

def histDateMinusGenBG(var, sumProcessIVar, region, genRegion, isdataMC=False):
    if not isdataMC:
        h_data = sumProcessIVar[region]['data']
    else:
       h_data = addBGHist(sumProcessIVar, var, region, True) 
    h_data.Sumw2()
    h_bgGen = addBGHist(sumProcessIVar, var, genRegion) #???no requiring gen here???
    h_dataMBG = h_data - h_bgGen
    return h_dataMBG


def addBGHist(sumProcessIVar, var, region, includeQCD=False):
    sumHist = sumProcessIVar[region][summedProcessList[0]]
    sumHist.Reset()
    sumHist.Sumw2()
    sumHist.SetName(region+ '_bgSum_' + var )
    for ipro in summedProcessList:
        if not includeQCD:
            if ipro=='data' or ipro=='qcd' or ipro=='tttt': continue
        else:
            if ipro=='data' or ipro=='tttt': continue
        sumHist.Add( sumProcessIVar[region][ipro])
    return sumHist



if __name__=='__main__':
    main()

