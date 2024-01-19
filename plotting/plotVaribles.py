
import math
import os
from array import array
import numpy as np

import usefulFunc as uf
from plotForFakeRate import getFRAndARNotTList, getFTFromLNotTData
from ROOT import *
# from ttttGlobleQuantity import (histoGramPerSample, lumiMap, samples,
                                # samplesCrossSection, summedProcessList)
# from writeCSVforEY import replaceBgWithGen
import writeCSVforEY as wc
import setTDRStyle as ss


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v2_btagCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v0_BDT1tau1lCRs/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v6baseline_v56preselection/mc/variableHists_v0BDT_SR30Bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v0BDT_SR30Bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/mc/variableHists_v0BDT_SR30Bins/'
    
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v0Testing/mc/variableHists_v0allRegions/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v1newCrab/mc/variableHists_v0allRegions/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v1newCrab/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightAdded_v59newOScode/mc/variableHists_v0_dataMCBeforeBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/mc/variableHists_v0_dataMCBeforeBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/mc/variableHists_v1_dataMCafterBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3btagWPWeightGood_v60fixeJetBtagBug/mc/variableHists_v2AllButBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5newBtagEff_v60fixeJetBtagBug/mc/variableHists_v4newBtagEff/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5newBtagEff_v60fixeJetBtagBug/mc/variableHists_v5OldBtagR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6updatedBtagR_v60fixeJetBtagBug/mc/variableHists_v7newBtagRApp/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v0btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    
    #Run3
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0preSel/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v0preSel/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0baseline_v0preSel/mc/variableHists_v2SR1tau1l/' #!copied tttt.root from 2016

    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v0dataMC_btagWPsf/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt45/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt40/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt42/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt42/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v63smallFixJER/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSF_v64PreAndHLTSel/mc/variableHists_v2dataMC_HT600HLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinD_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT600HLTSFBinD/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSF_v64PreAndHLTSel/mc/variableHists_v2dataMC_HT600/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinE_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT600HLTSFBinE/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT500BinE_v64PreAndHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinE/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT550HLTSFBinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT550HLTSFBinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT550HLTSFBinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0for2022baseline/mc/variableHists_v0dataMC_noCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0for2022baseline/mc/variableHists_v0dataMC_noCorrection_MCHadded/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0dataMC_noCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v2leptonsNameChange/mc/variableHists_v1dataMC_eleSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0NoSystematic/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0NoSystematic/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v2leptonsNameChange/mc/variableHists_v0dataMC_noCorrection/'

    # for 1tau1l
    # variables = ['jets_num']
    # variables = ['tausT_1pt']
    # variables = ['jets_HT']
    # variables = ['bjetsM_num']
    # variables = ['jets_6pt']
    # variables = ['jets_6pt', 'jets_num', 'bjetsM_num', 'jets_HT']
    # variables = [ 'jets_HT', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', "jets_7pt", 'jets_num',  "jets_bScore", "jets_rationHT_4toRest", "jets_transMass", "jets_average_deltaR", 'jets_1btag', 'jets_2btag', 'jets_3btag', 'jets_4btag', 'jets_5btag', 'jets_6btag']
    variables = ['tausT_leptonsTopMVA_chargeMulti','tausT_leptonsT_invariantMass', 'tausT_MHT', 'tausT_1pt', 'tausT_1eta', 'tausT_leptonsTopMVA_chargeMulti','bjetsM_HT', 'bjetsM_MHT', 'bjetsM_minDeltaR', 'bjetsM_invariantMass', 'bjetsM_2pt', 'bjetsM_num', 'bjetsM_1pt', 'muonsTopMVAT_1pt', 'elesTopMVAT_1pt'] #for 1tau1l BDT input
    # variables = ['bjetsM_HT', 'bjetsM_MHT', 'bjetsM_minDeltaR', 'bjetsM_invariantMass', 'bjetsM_2pt', 'bjetsM_num', 'bjetsM_1pt']
    regionList = ['1tau1lCR1', '1tau1lCR2']
    # regionList = ['1tau0lSR']
    # regionList = ['1tau1lSR']
    # variables = ['BDT']
    # regionList = ['1tau0lSR', '1tau0lMR', '1tau0lVR', '1tau0lCR']
    ifFR_sys = False
    plotName = 'dataVsMC'
  
    #1tau0l
    # variables = ['jets_bScore' ]
    # variables = ['bjetsM_num', 'jets_bScore']
    # variables = ['tausF_1jetPtFRWeight']
    # variables = [ 'tausF_prongNum', 'tausF_charge', 'tausF_1decayMode', 'tausL_1ptFRWeight', 'tausL_1etaAbsFRWeight' , 'tausF_1jetPtFRWeight', 'tausF_1eta', 'PV_npvs', 'tausF_1pt', 'jets_HT', 'jets_bScore', 'jets_bScoreMultiply', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'bjetsM_invariantMass', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', 'jets_num', 'bjetsM_num']  
    # variables = ['jets_HT', 'jets_bScore', 'jets_bScoreMultiply', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'bjetsM_invariantMass', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', 'jets_num', 'bjetsM_num', ] #1tau0l
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRNotGen']
    # regionList = ['1tau0lCR', '1tau0lCRGen', '1tau0lCRLTauNotT_Weighted', '1tau0lCRLTauNotTGen_Weighted']
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRLTauNotT_Weighted', '1tau0lVRLTauNotTGen_Weighted'] # new MR
    # regionList = ['1tau0lCRb', '1tau0lCRbGen', '1tau0lCRbLTauNotT_Weighted', '1tau0lCRbLTauNotTGen_Weighted'] # new CR
    # regionList = ['1tau0lCRc', '1tau0lCRcGen', '1tau0lCRcLTauNotT_Weighted', '1tau0lCRcLTauNotTGen_Weighted'] # new VR
    # regionList = ['1tau0lSR', '1tau0lSRGen',  '1tau0lSRLTauNotT_Weighted', '1tau0lSRLTauNotTGen_Weighted']
    # ifFR_sys = True 
    # plotName = 'dataVsMC_fakeTauFromData'

    
    era = uf.getEraFromDir(inputDir)
    print('era=', era)
    isRun3 = uf.isRun3(inputDir)
    # regionList = appendSYSRegions( ifFR_sys, regionList) 

    inputDirDic = uf.getInputDicNew( inputDir)
    #sumProcessPerVar[var][region][sumedProcess] = hist
    #sumProcessPerVarSys[var][region][sumedProcess][isysVariation] = hist
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    for ivar in variables:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar] = uf.getSummedHists( inputDirDic, regionList, ivar , False, era, False, isRun3)       
    print( sumProcessPerVar )
    print( sumProcessPerVarSys )
    print('\n')

    # remove 'singleMu'
    sumProcessPerVar = removeSingleMu(sumProcessPerVar)


    # legendOrder = ['tt', 'ttX', 'singleTop', 'VV', 'WJets', 'qcd']
    # legendOrder = ['tt', 'qcd', 'tttt'] #!!!need to improve here
    legendOrder = ['tt', 'tttt'] #!!!need to improve here
    
    hasFakeTau = checkRegionGen(regionList)
    # if hasFakeTau:
    #     print('has fake')
    #     for ivar in sumProcessPerVar:
    #         wc.replaceBgWithGen( inputDirDic, sumProcessPerVar[ivar], ivar, regionList, 2, ifFR_sys, sumProcessPerVarSys[ivar]  )
    #     legendOrder.remove('qcd')
    #     legendOrder.insert(0, 'fakeTau')
    #     sumProcessPerVar[ivar][regionList[0]].pop('qcd')
   
    # remove qcd for 1tau1l 
    sumProcessPerVar, legendOrder = removeQCD(sumProcessPerVar, legendOrder)
    print( sumProcessPerVar )
    print( legendOrder)
    
    
    #???should we add hists like this?
    if hasFakeTau and regionList[0]=='1tau0lSR' and 'jets_bScore' in variables: 
        writeTemplatesForCombine(sumProcessPerVar, sumProcessPerVarSys, inputDirDic['mc'], regionList[0]) 
    if (not hasFakeTau) and regionList[0]=='1tau1lSR' and 'BDT' in variables: 
        writeTemplatesForCombine(sumProcessPerVar, sumProcessPerVarSys, inputDirDic['mc'], regionList[0]) 
    

    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir( plotDir)
    for variable in variables:
        if not hasFakeTau:
            for iRegion in regionList:       
                makeStackPlot(sumProcessPerVar[variable][iRegion], sumProcessPerVarSys[variable][iRegion], variable, iRegion, plotDir, legendOrder, False, plotName, era, True, 100 ) 
        else:
            # print(regionList)
            makeStackPlot(sumProcessPerVar[variable][regionList[0]], sumProcessPerVarSys[variable][regionList[0]], variable, regionList[0], plotDir,legendOrder, True, plotName, era, True,1000)



def writeTemplatesForCombine(sumProcessPerVar,sumProcessPerVaySys, inputDir, region, channel='1tau0l') :
    outDir = inputDir + channel + '_templatesForCombine/'
    uf.checkMakeDir( outDir )
    outFile = TFile( outDir+'templates.root', 'RECREATE')
    for ivar in sumProcessPerVar.keys():
        dataHist = TH1D('data_obs_'+ivar, 'data_obs', sumProcessPerVar[ivar][region]['tttt'].GetNbinsX(), sumProcessPerVar[ivar][region]['tttt'].GetXaxis().GetXmin(), sumProcessPerVar[ivar][region]['tttt'].GetXaxis().GetXmax() )
        dataHist.Reset()
        dataHist.Sumw2()
        for ipro in sumProcessPerVar[ivar][region].keys():
            itempName = ipro + '_' + ivar 
            ihist = sumProcessPerVar[ivar][region][ipro].Clone(itempName)
            ihist.Write()
            if (not ipro=='tttt')  and (not ipro=='qcd'):
                dataHist.Add(ihist)
                print('add data:', ihist)
                
                for isys in sumProcessPerVaySys[ivar][region][ipro].keys():
                    ihistSys = sumProcessPerVaySys[ivar][region][ipro][isys].Clone(itempName+'_'+isys)
                    ihistSys.Write()
        dataHist.Write()
    print('writen templates for combine here', outFile.GetName())
    print('\n')
    outFile.Close()    
  

 
def removeQCD(sumProcessPerVar, legendOrder):
    variables = list(sumProcessPerVar.keys()) 
    regionList = list(sumProcessPerVar[variables[0]].keys())
    for (i,ire) in enumerate( regionList):
        if '1tau1l' in ire:
        # if '1tau1lSR' in ire:
            print('remove qcd for 1tau1l')
            for ivar in variables:
                # if i==0:
                #     legendOrder.remove('qcd')     
                if not 'qcd' in sumProcessPerVar[ivar][ire].keys(): continue
                sumProcessPerVar[ivar][ire].pop('qcd')
    if '1tau1l' in regionList:
        legendOrder.remove('qcd') 
    return sumProcessPerVar, legendOrder
 
    
    
 
def removeSingleMu(sumProcessPerVar):
    variables = list(sumProcessPerVar.keys())
    regionList = sumProcessPerVar[variables[0]].keys()
    for (i,ire) in enumerate( regionList):
        for ivar in variables:
            if 'singleMu' in sumProcessPerVar[ivar][ire].keys():
                sumProcessPerVar[ivar][ire].pop('singleMu')
    return sumProcessPerVar
            
def checkRegionGen(regionList):
    hasFakeTau = False
    for ire in regionList:
        if 'Gen' in ire:
            hasFakeTau = True
    return hasFakeTau
                

#moved to 1tau0l plotting
# def appendSYSRegions( ifFR_sys, regionList) :
#     if ifFR_sys:
#         regionList.append(regionList[2]+'_up')
#         regionList.append(regionList[2]+'_down')
#         regionList.append(regionList[3]+'_up')
#         regionList.append(regionList[3]+'_down')
#     return regionList 
 
 
def getShapeFromData( inputDirDic, var, isVR=False):
    # ptBins = np.array( [20.0, 40.0, 60.0, 80.0, 120.0,  250.0] )
    # variableDic = {
    #     'tausL_1pt': ptBins,
    # }
    ptBins = np.array( [20.0, 30, 40.0, 50, 70.0, 90.0, 120.0,  300.0] )
    variableDic = {
        'tausF_1jetPt': ptBins,
    }
    FR_ptInEtaList, tauPtEtaListAR = getFRAndARNotTList( inputDirDic, variableDic, isVR, False)
    
    ifPtBin = True
    if 'eta' in var:
        ifPtBin = False
    fakeTauFromData = getFTFromLNotTData(FR_ptInEtaList, tauPtEtaListAR, ifPtBin)
    
    return fakeTauFromData
        
        
        
        


def checkHists( histsDict ):
    for ikey in histsDict.keys():
        print('iProcess: ', ikey )
        histsDict[ikey].Print()







def makeStackPlot(nominal,systHists,name,region,outDir, legendOrder, ifFakeTau, savePost = "", era='2016', includeDataInStack=True, signalScale = 1000):
    '''
    nominal is a dic of distribution for all processes including data
    nominal: nominal[iprocess]
    sysHists: sysHists[iprocess]['prefiring_up']
    '''
    #name is variable name
    print( 'start plotting data/mc plot for {}'.format(name))
    myStyle = ss.setMyStyle()
    myStyle.cd() #???not sure why the gStyle is not affecting the sedond pad
    
    canvasName = '{}_{}'.format( region, name )
    canvy = TCanvas( canvasName, canvasName, 1000,1000)
    
    #it seems text size  is scaled to pad size
    upPad = TPad('up', 'up', 0, 0., 1, 1)
    downPad = TPad('down', 'down', 0., 0, 1, 1)
    upPad.SetBottomMargin(0.3)
    downPad.SetTopMargin(0.72)
    # downPad.SetBottomMargin(0.2)
    upPad.Draw()
    downPad.SetFillColor(0)
    downPad.SetFillStyle(0) #set the empty space to be empty, so that not cover the upPad
    downPad.SetGridy(1)
    downPad.Draw()
    
    upPad.cd() #???cd() pad causing stack to be not accessble???

    doSystmatic = ifDoSystmatic( systHists)
    dataHist, systsUp, systsDown, sumHist, stack, signal, hasDataHist = getHists(nominal, systHists, doSystmatic, ifFakeTau, legendOrder)

    #add sytematic uncertainty
    systsUp, systsDown = addStatisticUncer( sumHist, systsUp, systsDown )

    #get the uncertainty for stack MC
    assymErrorPlot = getErrorPlot(sumHist,systsUp,systsDown)
    #systsUp and systsDown are the total bin up and down uncertainty, not n+-uncertainty

    #set y axix maxi
    if sumHist.GetMaximum()> signalScale*signal.GetMaximum():
        maxi = 1.7* sumHist.GetMaximum()
    else:
        maxi = 1.7* signalScale*signal.GetMaximum()  
    # if hasDataHist:
    #     if dataHist.GetMaximum()>0:
    #         maxi = 1.7* dataHist.GetMaximum()
    #     else:
    #         maxi = 1.7* sumHist.GetMaximum()
    # else:
    #     maxi = 1.7* sumHist.GetMaximum()
    if maxi<=0 :
        print(name, ' variable empty')
        print('\n')
        return
    # if (maxi-sumHist.GetBinContent(sumHist.GetNbinsX()))/maxi < 0.6:
    #     maxi = maxi*1.7
    stack.SetMaximum(maxi) #Set the minimum / maximum value for the Y axis (1-D histograms) or Z axis (2-D histograms)  By default the maximum / minimum value used in drawing is the maximum / minimum value of the histogram
    stack.Draw("hist")
    stack.GetXaxis().SetLabelSize(0.0)
    stack.GetYaxis().SetTitle('Events')
    stack.GetYaxis().SetTitleOffset(1.2)
    stack.GetYaxis().SetTitleSize(0.06)
    stack.GetYaxis().SetLabelSize(0.033)


    if includeDataInStack and hasDataHist:
        dataHist.SetLineWidth(1)
        dataHist.SetMarkerSize(1.5)
        dataHist.Draw("e0 same")
        
    signal.Scale(signalScale)
    # signal.SetLineColor(kMagenta)
    signal.SetLineColor(kBlue)
    signal.SetLineStyle(kSolid)
    signal.SetLineWidth(3)
    signal.SetFillStyle(0)
    signal.GetXaxis().SetLabelSize(0.0)
    signal.Draw("SAME HIST ")
    
    assymErrorPlot.SetFillStyle(3013)
    assymErrorPlot.SetFillColor(14)
    assymErrorPlot.GetXaxis().SetLabelSize(0.0)
    assymErrorPlot.Draw("e2 SAME")
    
    upPad.Update()


    downPad.cd()
    myStyle.cd()
    myStyle.SetOptTitle(0)
    if hasDataHist:
        sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)
    else:
        sumHistoData = sumHist.Clone() 
        sumHistoData.Reset()
    sumHistoData.GetYaxis().SetTitle("Data/pred.")
    # sumHistoData.GetYaxis().SetTitleOffset(1.3)
    # ratioCanvy.cd()
    # SetOwnership(sumHistoData,False)
    sumHistoData.SetMinimum(0.5)
    # sumHistoData.SetMaximum(1.2)
    sumHistoData.SetMaximum(1.5)
    sumHistoData.GetXaxis().SetTitle(signal.GetTitle())
    sumHistoData.GetXaxis().SetLabelSize(0.04)
    sumHistoData.GetXaxis().SetTitleSize(0.06)
    sumHistoData.GetYaxis().SetNdivisions(6)
    sumHistoData.GetYaxis().SetTitleSize(0.05)
    sumHistoData.GetYaxis().SetLabelSize(0.04)
    sumHistoData.SetTitle("")
    sumHistoData.Draw("E1X0")
    
    assymErrorPlotRatio = getErrorPlot(sumHist,systsUp,systsDown,True)

    assymErrorPlotRatio.SetFillStyle(3013)
    assymErrorPlotRatio.SetFillColor(14) 
    assymErrorPlotRatio.SetTitle("")
    assymErrorPlotRatio.Draw("e2 same")

    
    
    #legend
    leggy =  getLegend(nominal, dataHist, assymErrorPlot, signal, signalScale, legendOrder)
    leggy.SetNColumns(2) 
    # leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    # leggy.SetFillColor(kWhite)
    # leggy.SetMarkerSize(2)
    leggy.SetTextFont(42)
    leggy.Draw()
    
    #text above the plot
    # ss.addCMSTextToCan(canvy, 0.24, 0.46, 0.9,0.94, era, isRun3=True)     # good for run2
    ss.addCMSTextToCan(canvy, 0.24, 0.56, 0.9,0.94, era)     # good for 2022
    
    
    canvy.Update()

    canvy.SaveAs(outDir+"{}_{}_{}.png".format(region,name, savePost))
    canvy.SaveAs(outDir+"{}_{}_{}.pdf".format(region,name, savePost))
    myStyle.Reset()
    print( 'done plotting data/mc plot for {}\n'.format(name))
    print('\n')
    
def getLegend(nominal,  dataHist, assymErrorPlot, signal, signalScale, legendOrder):
    # x1,y1,x2,y2 are the coordinates of the Legend in the current pad (in normalised coordinates by default)
    leggy = TLegend(0.18,0.75,0.89,0.90)
    if "jetHT" in nominal.keys():
        # nominal['jetHT'].SetMarkerSize(2)
        # leggy.AddEntry(nominal['jetHT'],"Data[{:.1f}]".format(getIntegral(nominal['jetHT'])),"ep")
        leggy.AddEntry(dataHist,"Data[{:.1f}]".format(getIntegral(dataHist)),"ep")
    for entry in legendOrder:
        legText = '{}[{:.1f}]'.format(entry, getIntegral(nominal[entry]))
        # leggy.AddEntry(nominal[entry],entry,"f")
        leggy.AddEntry(nominal[entry], legText,"f")
    leggy.AddEntry(assymErrorPlot,"Stat. unc","f")
    signalEntry = 'tttt*{}[{:.1f}]'.format(signalScale, getIntegral(nominal['tttt']))
    leggy.AddEntry( signal, signalEntry, 'l')
    return leggy
  
def getIntegral(histogram):
    integral = histogram.Integral(0, histogram.GetNbinsX() + 1, "overflow") 
    return integral
    

def ifDoSystmatic(systHists):
    doSystmatic = False
    for ipro in systHists.keys():
        if systHists[ipro]:
            doSystmatic = True
    print( 'doSystmatic: ', doSystmatic )
    return doSystmatic
    
def getHists(nominal, systHists, doSystmatic, ifFakeTau, legendOrder):
    #here we get dataHist and add all MC for sumHist    
    keyList = list(nominal.keys()) #process list
    colourPerSample = {
        'tttt':kBlue,
        'tt': TColor.GetColor("#f03b20"),
        'qcd': TColor.GetColor("#ffeda0"),
        'ttX': TColor.GetColor("#fc9272"),
        'singleTop': TColor.GetColor("#91bfdb"),
        'VV': TColor.GetColor("#edf8b1"),
        'WJets': TColor.GetColor("#998ec3"),
        # 'fakeTau': TColor.GetColor("#ffeda0"),
        'fakeTau': TColor.GetColor("#fec44f"),
    }
    
    sumHist = nominal[keyList[0]].Clone()
    sumHist.Reset()
    systsUp = nominal[keyList[0]].Clone("systsUp")
    systsUp.Reset()
    systsDown = nominal[keyList[0]].Clone("systsDown")
    systsDown.Reset()
    dataHist = 0
    hasDataHist = True
    if not 'jetHT' in nominal.keys():
        hasDataHist = False
    for i in nominal.keys():
        # i is i summed MC
        if i == "jetHT" and hasDataHist:
            dataHist = nominal["jetHT"].Clone()
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            dataHist.SetLineColor(kBlack)
            dataHist.SetTitleSize(0.0)
            continue
        if ifFakeTau and i=='qcd': 
            continue
        if i == 'tttt' or i=='singleMu':
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetTitleSize(0.01)
        nominal[i].GetXaxis().SetLabelSize(0.0)
        nominal[i].GetYaxis().SetTitle('Events')
        sumHist.Add(nominal[i]) #sumHist is all bg
        if doSystmatic and  systHists[i]:
            print('cal sys for: ', i)
            tempUp,tempDown = getSystVariation(nominal[i],systHists[i] )
            systsUp.Add(tempUp) #adding various processes, 
            systsDown.Add(tempDown)
            
    #add bgs for stack
    # legendOrder = ['tt']
    legendOrder.reverse()
    for ipro in legendOrder:
        if not ipro in nominal.keys():
            print( 'this prcess not get: ', ipro )
            legendOrder.remove(ipro)
    # stack = THStack( canvasName, canvasName )
    stack = THStack( 'stack', 'stack' )
    for entry in legendOrder:
        stack.Add(nominal[entry])
    legendOrder.reverse()
    
    
    #scale tttt
    if 'tttt' in nominal.keys():
        signal = nominal['tttt'].Clone()
    else:
        signal = nominal['tt'].Clone()
        signal.Reset()
    
            
    return dataHist, systsUp, systsDown, sumHist, stack, signal, hasDataHist 


def getErrorPlot(totalMC,systUp,systDown,isRatio = False):
    # for the data/mc ratio or the error bar in the stack for MC
    x = array('d',[])
    y = array('d',[])
    exl = array('d',[])
    exh = array('d',[])
    eyl = array('d',[])
    eyh = array('d',[])
    xAxis = systUp.GetXaxis()
    for i in range(1,xAxis.GetNbins()+1):
        x.append(xAxis.GetBinCenter(i)) # x is the x value
        if not isRatio: y.append(totalMC.GetBinContent(i))
        else: y.append(1.)
        exl.append(xAxis.GetBinCenter(i) - xAxis.GetBinLowEdge(i))
        exh.append(xAxis.GetBinLowEdge(i)+xAxis.GetBinWidth(i)-xAxis.GetBinCenter(i))
        if not isRatio:
            eyl.append(systDown.GetBinContent(i))
            eyh.append(systUp.GetBinContent(i))
        else:
            if not totalMC.GetBinContent(i)==0 :
                eyl.append(systDown.GetBinContent(i)/totalMC.GetBinContent(i))
                eyh.append(systUp.GetBinContent(i)/totalMC.GetBinContent(i))
            #???can you simply divide error like this? i think it's wrong
            else: 
                #???set to 0 by me
                eyl.append(0)
                eyh.append(0)
    errors = TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    return errors


def getSystVariation(nominalHist,systHists):
    '''
    # to calculate the total sysHistUp and down for one process from variaus uncertainty source
    sysHistUp and systHistDown bincontent is the sigma_total for each bin from various sources
    '''
    #here the input nominalHist and systHists are for one summed process
    # systHists include 'up' and 'down' for varias sources, but it's just for one process
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()
    
    for systHi in systHists.keys():
    #systHi is 'up' or 'down' for varias sources
    #so this is to sum the sytstmatic variation for sources of systematic uncertainty
        print( 'doing sytematic calculation for: ',systHi )
        # if "bTag" in systHi: continue
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist,-1)
        # syst.Divide(nominalHist)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            if "up" in syst.GetName():
                # print( 'sytHistUp: ', systHistUp.GetBinContent() )
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
    # for i in range(1,systHistUp.GetXaxis().GetNbins()+1):
        # systHistUp.SetBinContent(i,(math.sqrt(systHistUp.GetBinContent(i)))*nominalHist.GetBinContent(i))
        # systHistDown.SetBinContent(i,(math.sqrt(systHistDown.GetBinContent(i)))*nominalHist.GetBinContent(i))
        #no need to divide and multiply

    return systHistUp,systHistDown


def getSystVariation_my(nominalHist,systHists):
    # to calculate the total sysHistUp and down
    #here the input nominalHist and systHists are for one summed process
    # systHists include 'up' and 'down' for varias sources, but it's just for one process
    #???the calculation seems wrong
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()

    for systHi in systHists.keys():
    #systHi is 'up' or 'down' for varias sources for this process
    #so this is to sum the systematic variation for sources of systematic uncertainty
        print( systHi )
        if "bTag" in systHi: continue
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist,-1)
        syst.Divide(nominalHist)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            if "up" in syst.GetName():
                # print( 'sytHistUp: ', systHistUp.GetBinContent() )
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
    for i in range(1,systHistUp.GetXaxis().GetNbins()+1):
        systHistUp.SetBinContent(i,(math.sqrt(systHistUp.GetBinContent(i)))*nominalHist.GetBinContent(i))
        systHistDown.SetBinContent(i,(math.sqrt(systHistDown.GetBinContent(i)))*nominalHist.GetBinContent(i))
    return systHistUp,systHistDown


def addStatisticUncer(sumHist, systsUp, systsDown ):
    for i in range(1,sumHist.GetXaxis().GetNbins()+1):
        # systsUp.SetBinContent(i, math.sqrt( systsUp.GetBinContent(i)*systsUp.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        # systsDown.SetBinContent(i, math.sqrt( systsDown.GetBinContent(i)*systsDown.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        systsUp.SetBinContent(i, math.sqrt( systsUp.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        systsDown.SetBinContent(i, math.sqrt( systsDown.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
    return systsUp,systsDown



if __name__ == "__main__":
    main()
