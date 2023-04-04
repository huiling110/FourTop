
import math
import os
# import sys
from array import array

import numpy as np
import usefulFunc as uf
from plotForFakeRate import getFRAndARNotTList, getFTFromLNotTData
from ROOT import *
from setTDRStyle import addCMSTextToCan, setTDRStyle
from ttttGlobleQuantity import (histoGramPerSample, lumiMap, samples,
                                samplesCrossSection, summedProcessList)
from writeCSVforEY import replaceBgWithGen

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v51TESNewLepObjectRemovalCorrected/mc/variableHists_v4FR_application/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v52noHLTButPreSelection/mc/variableHists_v1pileupWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_v52noHLTButPreSelection/mc/variableHists_v2HLTweight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_re_v52noHLTButPreSelection/mc/variableHists_v2HLTweight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baseline_re_v52noHLTButPreSelection/mc/variableHists_v1pileupWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v1pileupWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v2HLTweight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v1FR_application/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v1FR_applicationNewTitle/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v1FR_applicationNewTitle/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3HLTBaseline_v54noHLTButPre/mc/variableHists_v2HLTweight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baseline_v55ojectRemovalwithTight/mc/variableHists_v2HLTweight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v2HLTSFWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v4basicWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v5HLTSFWeightNoBtag/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v6allCorrectionButBtag/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v7btagShapeRWeight/'

    # for 1tau1l
    # variables = ['jets_number']
    # variables = ['tausT_leptonsTopMVA_chargeMulti']
    # variables = ['tausT_leptonsTopMVA_chargeMulti']
    variables = ['jets_1btag', 'jets_2btag', 'jets_3btag', 'jets_4btag', 'jets_5btag', 'jets_6btag']
    # variables = ['PV_npvsGood']
    # variables = ['eventCount']
    # variables = ['tausT_leptonsTMVA_chargeMulti']
    # variables = [ 'jets_HT', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', "jets_7pt", "jets_8pt" , 'jets_number',  "jets_bScore", "jets_rationHT_4toRest", "jets_leading2invariantMass", "jets_transMass", "jets_average_deltaR", "jets_4largestBscoreMulti", 'jets_bScoreMultiply' , 'jets_1btag']
    # variables = ['tausT_leptonsTMVA_chargeMulti','tausT_leptonsT_invariantMass', 'tausT_MHT', 'tausT_1pt', 'tausT_1eta', 'tausT_leptonsTopMVA_chargeMulti','bjetsM_HT', 'bjetsM_MHT', 'bjetsM_minDeltaR', 'bjetsM_invariantMass', 'bjetsM_2pt', 'nonbjetsM_num', 'bjetsM_num', 'bjetsM_1pt', 'muonsTopMVAT_1pt', 'elesTopMVAT_1pt', 'PV_npvsGood'] #for 1tau1l BDT input
    # variables = ['bjetsM_HT', 'bjetsM_MHT', 'bjetsM_minDeltaR', 'bjetsM_invariantMass', 'bjetsM_2pt', 'nonbjetsM_num', 'bjetsM_num', 'bjetsM_1pt']
    # variables = ['BDT']
    # regionList = ['1tau1lCR0']
    # regionList = ['1tau1lCR2']
    # regionList = ['1tau1lSR', '1tau1lCR0', '1tau1lCR1','1tau1lCR2', '1tau1lCR3']
    regionList = ['1tau1lCR0', '1tau1lCR2' ]
    # regionList = ['1tau1lSR']
    ifFR_sys = False
    plotName = 'dataVsMC'
  
    #1tau0l
    # variables = ['jets_bScore' ]
    # variables = ['bjetsM_num', 'jets_bScore']
    # variables = ['tausF_1jetPtFRWeight']
    # variables = [ 'tausF_prongNum', 'tausF_charge', 'tausF_1decayMode', 'tausL_1ptFRWeight', 'tausL_1etaAbsFRWeight' , 'tausF_1jetPtFRWeight', 'tausF_1eta', 'PV_npvs', 'tausF_1pt']  
    # variables = ['jets_HT', 'jets_bScore', 'jets_bScoreMultiply', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'bjetsM_invariantMass', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', 'jets_num', 'bjetsM_num', ] #1tau0l
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRNotGen']
    # regionList = ['1tau0lCR', '1tau0lCRGen', '1tau0lCRLTauNotT_Weighted', '1tau0lCRLTauNotTGen_Weighted']
    # regionList = ['1tau0lCRc', '1tau0lCRcGen', '1tau0lCRcLTauNotT_Weighted', '1tau0lCRcLTauNotTGen_Weighted']
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRLTauNotT_Weighted', '1tau0lVRLTauNotTGen_Weighted']
    # regionList = ['1tau0lCRb', '1tau0lCRbGen', '1tau0lCRbLTauNotT_Weighted', '1tau0lCRbLTauNotTGen_Weighted']
    # regionList = ['1tau0lSR', '1tau0lSRGen',  '1tau0lSRLTauNotT_Weighted', '1tau0lSRLTauNotTGen_Weighted']
    # ifFR_sys = True #???problem when turn this on
    # plotName = 'dataVsMC_fakeTauFromData'

    
    
    
    era = uf.getEraFromDir(inputDir)
    regionList = appendSYSRegions( ifFR_sys, regionList) 

    inputDirDic = uf.getInputDicNew( inputDir)
    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    #sumProcessPerVarSys[var][region][sumedProcess][isysVariation] = hist
    for ivar in variables:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar] = uf.getSummedHists( inputDirDic, regionList, ivar )       
    print( sumProcessPerVar )
    print( sumProcessPerVarSys )
    print('\n')

    # remove 'singleMu'
    sumProcessPerVar = removeSingleMu(sumProcessPerVar)


    legendOrder = [ 'qcd', 'tt', 'ttX', 'singleTop', 'VV', 'WJets']
    
    hasFakeTau = checkRegionGen(regionList)
    if hasFakeTau:
        print('has fake')
        for ivar in sumProcessPerVar:
            replaceBgWithGen( inputDirDic, sumProcessPerVar[ivar], ivar, regionList, 2, ifFR_sys, sumProcessPerVarSys[ivar]  )
            # replaceBgWithGen( inputDirDic, sumProcessPerVar[ivar], ivar, regionList, 1 )
        legendOrder.remove('qcd')
        legendOrder.insert(0, 'fakeTau')
        sumProcessPerVar[ivar][regionList[0]].pop('qcd')
    
    # writeTemplatesForCombine(sumProcessPerVar, inputDirDic['mc'], regionList[0]) 
    
    # remove qcd for 1tau1l 
    sumProcessPerVar, legendOrder = removeQCD(sumProcessPerVar, legendOrder)
    print( sumProcessPerVar )

    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir( plotDir)
    for variable in variables:
        if not hasFakeTau:
            for iRegion in regionList:       
                makeStackPlot(sumProcessPerVar[variable][iRegion], sumProcessPerVarSys[variable][iRegion], variable, iRegion, plotDir, legendOrder, False, plotName, era, True, 100 ) 
        else:
            # print(regionList)
            # sumProcessPerVar[variable][regionList[0]]['jetHT'].Print()
            makeStackPlot(sumProcessPerVar[variable][regionList[0]], sumProcessPerVarSys[variable][regionList[0]], variable, regionList[0], plotDir,legendOrder, True, plotName, era, True,1000)
 
def removeQCD(sumProcessPerVar, legendOrder):
    variables = list(sumProcessPerVar.keys()) 
    regionList = list(sumProcessPerVar[variables[0]].keys())
    for (i,ire) in enumerate( regionList):
        if '1tau1l' in ire:
            print('remove qcd for 1tau1l')
            for ivar in variables:
                # if i==0:
                #     legendOrder.remove('qcd')     
                if not 'qcd' in sumProcessPerVar[ivar][ire].keys(): continue
                sumProcessPerVar[ivar][ire].pop('qcd')
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
                


def appendSYSRegions( ifFR_sys, regionList) :
    if ifFR_sys:
        regionList.append(regionList[2]+'_up')
        regionList.append(regionList[2]+'_down')
        regionList.append(regionList[3]+'_up')
        regionList.append(regionList[3]+'_down')
    return regionList 
 
 
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
    setTDRStyle()
    canvasName = '{}_{}'.format( region, name )
    canvy = TCanvas( canvasName, canvasName, 1000,800)
    # canvy = TCanvas( canvasName, canvasName, 1000,1000)
    
    canvy.cd()
    if includeDataInStack: canvy.SetBottomMargin(0.35)#set margion for ratio plot

    colourPerSample = {
        'tttt':kBlue,
        # 'tt': kRed-2,
        'tt': TColor.GetColor("#f03b20"),
        'qcd': kOrange-2,
        # 'ttX': kPink+2,
        'ttX': TColor.GetColor("#fc9272"),
        'singleTop': TColor.GetColor("#91bfdb"),
        'VV': TColor.GetColor("#5ab4ac"),
        'WJets': TColor.GetColor("#998ec3"),
        # 'fakeTau': kOrange,
        'fakeTau': TColor.GetColor("#ffeda0"),
    }

    doSystmatic = False
    for ipro in systHists.keys():
        if systHists[ipro]:
            doSystmatic = True
    print( 'doSystmatic: ', doSystmatic )

    #here we get dataHist and add all MC for sumHist    
    keyList = list(nominal.keys()) #process list
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
            dataHist = nominal["jetHT"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            dataHist.SetLineColor(kBlack)
            continue
        if ifFakeTau and i=='qcd': 
            continue
        if i == 'tttt' or i=='singleMu':
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetLabelSize(0.01)
        # nominal[i].GetXaxis().SetTitle(name)
        sumHist.Add(nominal[i]) #sumHist is bg+signal
        #???need systsUp and systsDown calculation
        if doSystmatic and  systHists[i]:
            # tempUp,tempDown = getSystVariation_my(nominal[i],systHists[i] ) #for i process
            print('cal sys for: ', i)
            tempUp,tempDown = getSystVariation(nominal[i],systHists[i] )
            systsUp.Add(tempUp) #adding various processes, 
            systsDown.Add(tempDown)

    #add sytematic uncertainty
    systsUp, systsDown = addStatisticUncer( sumHist, systsUp, systsDown )

    #get the uncertainty for stack MC
    assymErrorPlot = getErrorPlot(sumHist,systsUp,systsDown)
    #systsUp and systsDown are the total bin up and down uncertainty, not n+-uncertainty
    assymErrorPlot.SetFillStyle(3013)
    assymErrorPlot.SetFillColor(14)



    #add bgs for stack
    legendOrder.reverse()
    for ipro in legendOrder:
        if not ipro in nominal.keys():
            print( 'this prcess not get: ', ipro )
            legendOrder.remove(ipro)
    stack = THStack( canvasName, canvasName )
    for entry in legendOrder:
        stack.Add(nominal[entry])
    legendOrder.reverse()
    # maxi = 1.2* sumHist.GetMaximum()
    if hasDataHist:
        if dataHist.GetMaximum()>0:
            maxi = 1.4* dataHist.GetMaximum()
        else:
            maxi = 1.4* sumHist.GetMaximum()
    else:
        maxi = 1.4* sumHist.GetMaximum()
    if maxi<=0 :
        print(name, ' variable empty')
        print('\n')
        return
    if (maxi-sumHist.GetBinContent(sumHist.GetNbinsX()))/maxi < 0.6:
        maxi = maxi*1.7
    stack.SetMaximum(maxi) #Set the minimum / maximum value for the Y axis (1-D histograms) or Z axis (2-D histograms)  By default the maximum / minimum value used in drawing is the maximum / minimum value of the histogram
    stack.Draw("hist")
    stack.GetXaxis().SetLabelSize(0.0)
    stack.GetYaxis().SetTitle("Events")
    stack.GetYaxis().SetTitleOffset(1.3)
    stack.GetYaxis().SetLabelSize(0.04)
    stack.GetYaxis().SetTitleSize(0.05)

    if includeDataInStack and hasDataHist:
        dataHist.Draw("e0 same")
    else:
        stack.GetXaxis().SetLabelSize(0.03)
        stack.GetXaxis().SetTitle(name)
        stack.GetXaxis().SetTitleSize(0.04)

    #scale tttt
    signal = nominal['tttt'].Clone()
    # signal.Scale(1000)
    signal.Scale(signalScale)
    # signal.SetLineColor(kMagenta)
    signal.SetLineColor(kBlue)
    signal.SetLineStyle(kSolid)
    signal.SetLineWidth(3)
    signal.SetFillStyle(0)
    # signal.SetFillColor(kMagenta)
    signal.Draw("SAME HIST ")
    
    
    assymErrorPlot.Draw("e2 SAME")

    if includeDataInStack:
        ratioCanvy = TPad("{0}_ratio".format(name),"{0}_ratio".format(name),0.0,0.0,1.0,1.0)
        # ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetFillColor(0)
        ratioCanvy.SetFillStyle(0)
        ratioCanvy.SetGridy(1)
        ratioCanvy.Draw()
        ratioCanvy.cd(0)
        SetOwnership(ratioCanvy,False)

        # if hasDataHist:
        # print( 'hist title: ', dataHist.GetTitle())
        if hasDataHist:
            sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
            sumHistoData.Sumw2()
            sumHistoData.Divide(sumHist)
        else:
            sumHistoData = sumHist.Clone() 
            sumHistoData.Reset()
        sumHistoData.GetYaxis().SetTitle("Data/pred.")
        sumHistoData.GetYaxis().SetTitleOffset(1.3)
        ratioCanvy.cd()
        SetOwnership(sumHistoData,False)
        sumHistoData.SetMinimum(0.5)
        # sumHistoData.SetMaximum(1.2)
        sumHistoData.SetMaximum(1.5)
        sumHistoData.GetXaxis().SetTitle(signal.GetTitle())
        sumHistoData.GetXaxis().SetTitleOffset(1.25)
        sumHistoData.GetXaxis().SetLabelSize(0.04)
        # sumHistoData.GetXaxis().SetTitleSize(0.05)
        sumHistoData.GetXaxis().SetTitleSize(0.06)
        sumHistoData.GetYaxis().SetNdivisions(6)
        sumHistoData.GetYaxis().SetTitleSize(0.05)
        sumHistoData.GetYaxis().SetLabelSize(0.03)
        sumHistoData.Draw("E1X0")
        assymErrorPlotRatio = getErrorPlot(sumHist,systsUp,systsDown,True)

        assymErrorPlotRatio.SetFillStyle(3013)
        assymErrorPlotRatio.SetFillColor(14) 
        assymErrorPlotRatio.Draw("e2 same")

    
    
    #legend
    #x1,y1,x2,y2 are the coordinates of the Legend in the current pad (in normalised coordinates by default)
    # leggy = TLegend(0.8,0.7,0.9,0.94)
    # leggy = TLegend(0.68,0.8,0.92,0.94)
    leggy = TLegend(0.6,0.75,0.92,0.94)
    leggy.SetNColumns(2) 
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    # if "data" in nominal.keys():
    if "jetHT" in nominal.keys():
        # leggy.AddEntry(nominal['data'],"Data","p")
        leggy.AddEntry(nominal['jetHT'],"Data","p")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")
    leggy.AddEntry(assymErrorPlot,"totalUncer","f")
    signalEntry = 'tttt*{}'.format(signalScale)
    # leggy.AddEntry( signal, 'tttt*1000', 'l')
    leggy.AddEntry( signal, signalEntry, 'l')
    leggy.Draw()
    
    #text above the plot
    addCMSTextToCan(canvy, 0.23, 0.35, 0.96, era)     

    canvy.SaveAs(outDir+"{}_{}_{}.png".format(region,name, savePost))
    print( 'done plotting data/mc plot for {}\n'.format(name))
    print('\n')


    


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
