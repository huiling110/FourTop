import math
import os
# import sys
from array import array

import numpy as np
from ROOT import *
from ttttGlobleQuantity import (histoGramPerSample, lumiMap, samples,
                                samplesCrossSection, summedProcessList)

from plotForFakeRate import (getFRAndARNotTList, getFTFromLNotTData,
                             getInputDic, histDateMinusGenBG)
from setTDRStyle import setTDRStyle
from writeCSVforEY import getProcessScale, getSummedHists

colourPerSample = {
    'tttt':kPink-9,
    'tt': kRed-4,
    'qcd': kOrange-2,
    'ttX': kPink+2,
    'singleTop': kGreen-4,
    'VV': kGreen+2,
    # 'WJets': kOrange,
    # 'fakeTau': kBlue,
    'WJets': kBlue,
    'fakeTau': kOrange,
}



fakeTauYiled = {
    '1tau0lCR':  15569.67,
    '1tau0lVR': 11997.29, 
}


# includeDataInStack = False
includeDataInStack = True

def main():
    # era = '2016preVFP'
    # era = '2016postVFP'
    era = '2016'
    # era = '2018'

    # inVersion = 'v1baseline_v33TESnoJERCodeOptimzation'
    # inVersion = 'v1baseline_v36TESandJERByHuiling'
    # inVersion = 'v1baseline_v38TESandJERTauPt20_preselection'
    # inVersion = 'v2baselineAddingTauProng_v38TESandJERTauPt20_preselection'
    # inVersion = 'v0addMoreVariables_v39addTauBranches'
    inVersion = 'v1fixedTauVariables_v39addTauBranches'
    # histVersion = 'variableHists_v1variables'
    # histVersion = 'variableHists_v1variablesUsingMyclass'
    # histVersion = 'variableHists_v2addingPileupWeight'
    # histVersion = 'variableHists_v3pileUpAndNewRange'
    # histVersion = 'variableHists_v6forFakeRate3EtaRegions'
    # histVersion = 'variableHists_v7addFRWeightedRegions'
    # histVersion = 'variableHists_v8addFRWeightedRegionsNew'
    # histVersion = 'variableHists_v9addMoreVariables'
    # histVersion = 'variableHists_v10ExpandingTauPtRange'
    # histVersion = 'variableHists_v12moreVariables'
    histVersion = 'variableHists_v2forFRVariables_finerPtBin'
    # variables = [ 'jets_HT', 'jets_number', 'jets_bScore', 'jets_1pt','jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', 'jets_rationHT_4toRest', 'tausT_1pt', 'tausT_1eta', 'tausT_1phi', 'bjetsM_MHT', 'bjetsM_number', 'bjetsM_1pt', 'bjetsM_HT'  ]
    # variables = [ 'jets_HT', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', 'jets_num', 'bjetsM_num', 'bjetsM_1pt']
    # variables = [ 'tausF_1jetPtFRWeight', 'tausL_1etaAbsFRWeight', 'tausF_prongNum']
    # variables = [ 'tausF_charge', 'tausF_1decayMode', 'PV_npvs']
    variables = [ 'tausF_1jetPtFRWeight',]
    
    # variables = ['Met_pt']#???
    # variables = ['tausL_1ptFRWeight']
    # variables = ['tausF_1jetPt', 'tausL_1etaAbs']
    # regionList = [ '1tau0lSR', '1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']
    # regionList = ['1tau1lSR', '1tau1lCR0', '1tau1lCR1','1tau1lCR2', '1tau1lCR3']
    # regionList = ['1tau1lCR0', '1tau1lCR2' ]
    # regionList = ['1tau0lCR', '1tau0lVR', '1tau0lCR2', '1tau0lCR3', '1tau0lCR4']
    regionList = ['1tau0lCR', '1tau0lCRGen', '1tau0lCRNotGen', '1tau0lCRLTauNotT_Weighted', '1tau0lCRLTauNotTGen_Weighted']
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRNotGen', '1tau0lVRLTauNotT_Weighted', '1tau0lVRLTauNotTGen_Weighted']
    # regionList = ['1tau0lSR', '1tau0lSRGen', '1tau0lSRNotGen', '1tau0lSRLTauNotT_Weighted', '1tau0lSRLTauNotTGen_Weighted']
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRNotGen']
    # regionList = ['1tau0lCR', '1tau0lCRGen', '1tau0lCRNotGen']
   
    # plotName = 'dataVsMC_fakeTauFromData_FRWeighted'
    plotName = 'dataVsMC_fakeTauFromData'




    inputDirDic = getInputDic(inVersion, histVersion, era)
    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    for ivar in variables:
        sumProcessPerVar[ivar] = getSummedHists( inputDirDic, regionList, ivar )       
    print( sumProcessPerVar )


    # legendOrder = ['fakeTau', 'tttt', 'qcd', 'tt', 'ttX', 'singleTop', 'VV', 'WJets']
    legendOrder = [ 'qcd', 'tt', 'ttX', 'singleTop', 'VV', 'WJets']
    hasFakeTau = False
    for ire in regionList:
        if 'Gen' in ire:
            hasFakeTau = True
    if hasFakeTau:
        for ivar in sumProcessPerVar:
            replaceBgWithGen( inputDirDic, sumProcessPerVar[ivar], ivar, regionList, 2 )
            # replaceBgWithGen( inputDirDic, sumProcessPerVar[ivar], ivar, regionList, 1 )
        legendOrder.remove('qcd')
        legendOrder.insert(0, 'fakeTau')
            


    plotDir = inputDirDic['mc']+'results/'
    if not os.path.exists( plotDir ):
        os.mkdir( plotDir )
    sumProcessPerVarSys = {}
    for variable in variables:
        if not hasFakeTau:
            for iRegion in regionList:       
                makeStackPlot(sumProcessPerVar[variable][iRegion], sumProcessPerVarSys, variable, iRegion, plotDir, legendOrder, False, plotName ) 
        else:
            makeStackPlot(sumProcessPerVar[variable][regionList[0]], sumProcessPerVarSys, variable, regionList[0], plotDir,legendOrder, True, plotName)
            
            
    #     print( systs[variable])
        # makeStackPlot_mcOnly(nom[variable],systs[variable],variable,myRegion, plotDir, 'mcOnly' )
            # makeStackPlot( nom[variable], systs[variable], variable, myRegion,  plotDir, 'dataVsMC' )

def replaceBgWithGen(  inputDirDic, sumProcessIvar, var, regionList, ifGetFromMC=0):
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
            sumProcessIvar[regionList[0]]['fakeTau'].Add( sumProcessIvar[regionList[2]][ipro] ) 
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
        sumProcessIvar[regionList[0]]['fakeTau'] = histDateMinusGenBG( var, sumProcessIvar, regionList[3], regionList[4]) 
        # sumProcessIvar[regionList[0]]['fakeTau'] = sumProcessIvar[regionList[3]]['data']
    #fake tau come from data
    for ibin in range(sumProcessIvar[regionList[0]]['fakeTau'].GetNbinsX()):
        sumProcessIvar[regionList[0]]['fakeTau'].SetBinError(ibin+1, 0)
         
        
    print('checking data={}, fakeTau={} '.format(sumProcessIvar[regionList[0]]['data'].Integral(), sumProcessIvar[regionList[0]]['fakeTau'].Integral()))

 
 
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







def makeStackPlot(nominal,systHists,name,region,outDir, legendOrder, ifFakeTau, savePost = ""):
    '''
    nominal is a dic of distribution for all processes including data
    '''
    #name is variable name
    print( 'start plotting data/mc plot for {}'.format(name))
    setTDRStyle()
    canvasName = '{}_{}'.format( region, name )
    canvy = TCanvas( canvasName, canvasName, 1000,800)
    
    canvy.cd()
    if includeDataInStack: canvy.SetBottomMargin(0.3)


    doSystmatic = True
    if not systHists:
        print( 'systHist empty, not including systematic uncertainty\n')
        doSystmatic = False
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
    for i in nominal.keys():
        # i is i summed MC
        if i == "data":
            dataHist = nominal["data"]
            dataHist.SetMarkerStyle(20)
            dataHist.SetMarkerSize(1.2)
            dataHist.SetMarkerColor(kBlack)
            continue
        if ifFakeTau and i=='qcd': 
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        # nominal[i].GetXaxis().SetTitle(name)
        sumHist.Add(nominal[i]) #sumHist is bg+signal
        #???need systsUp and systsDown calculation
        if doSystmatic:
            tempUp,tempDown = getSystVariation_my(nominal[i],systHists[i] )
            # tempUp,tempDown = getSystVariation(nominal[i],systHists[i],i,region, doSystmatic )
            systsUp.Add(tempUp)
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
    stack = THStack( canvasName, canvasName )
    for entry in legendOrder:
        stack.Add(nominal[entry])
    legendOrder.reverse()


    maxi = stack.GetMaximum()
    if dataHist.GetMaximum() > stack. GetMaximum(): maxi = dataHist.GetMaximum()
    if (maxi-dataHist.GetBinContent(dataHist.GetNbinsX()))/maxi < 0.6:
        maxi = maxi*1.5
    stack.SetMaximum(maxi) #Set the minimum / maximum value for the Y axis (1-D histograms) or Z axis (2-D histograms)  By default the maximum / minimum value used in drawing is the maximum / minimum value of the histogram
    stack.Draw("hist")

    dataHist.Print()
    # if includeDataInStack: dataHist.Draw("e1x0 same")
    if includeDataInStack: dataHist.Draw("e0 same")

    #scale tttt
    # signal = nominal['tttt'].Clone()
    # signal.Scale(1000)
    # signal.SetLineColor(kBlue)
    # signal.SetLineStyle(kSolid)
    # signal.SetLineWidth(4)
    # signal.SetFillStyle(3335)
    # signal.SetFillColor(kBlue)
    # leggy.AddEntry( signal, 'tttt', 'l')
    # signal.Draw("SAME HIST ")
    
    
    assymErrorPlot.Draw("e2 SAME")

    if includeDataInStack:
        ratioCanvy = TPad("{0}_ratio".format(name),"{0}_ratio".format(name),0.0,0.0,1.0,1.0)
        ratioCanvy.SetTopMargin(0.7)
        ratioCanvy.SetFillColor(0)
        ratioCanvy.SetFillStyle(0)
        ratioCanvy.SetGridy(1)
        ratioCanvy.Draw()
        ratioCanvy.cd(0)
        SetOwnership(ratioCanvy,False)

        sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)

        sumHistoData.GetYaxis().SetTitle("Data/MC")
        sumHistoData.GetYaxis().SetTitleOffset(1.3)
        ratioCanvy.cd()
        SetOwnership(sumHistoData,False)
        sumHistoData.SetMinimum(0.8)
        sumHistoData.SetMaximum(1.2)
        sumHistoData.GetXaxis().SetTitle(name)
        sumHistoData.GetXaxis().SetTitleOffset(1.2)
        sumHistoData.GetXaxis().SetLabelSize(0.04)
        print( 'sumHistoData title: ', sumHistoData.GetXaxis().GetTitle() )
        sumHistoData.GetYaxis().SetNdivisions(6)
        sumHistoData.GetYaxis().SetTitleSize(0.03)
        sumHistoData.Draw("E1X0")
        assymErrorPlotRatio = getErrorPlot(sumHist,systsUp,systsDown,True)

        assymErrorPlotRatio.SetFillStyle(3013)
        assymErrorPlotRatio.SetFillColor(14) 
        assymErrorPlotRatio.Draw("e2 same")

    
    
    #legend
    #x1,y1,x2,y2 are the coordinates of the Legend in the current pad (in normalised coordinates by default)
    leggy = TLegend(0.8,0.6,0.95,0.9)
    leggy.SetFillStyle(1001)
    leggy.SetBorderSize(1)
    leggy.SetFillColor(0)
    leggy.SetLineColor(0)
    leggy.SetShadowColor(0)
    leggy.SetFillColor(kWhite)
    if "data" in nominal.keys():
        leggy.AddEntry(nominal['data'],"Data","p")
    for entry in legendOrder:
        leggy.AddEntry(nominal[entry],entry,"f")
    leggy.AddEntry(assymErrorPlot,"totalUncer","f")
    leggy.Draw()
    
    #copied from global     
    latex = TLatex()
    latex.SetNDC()
    latex.SetTextAlign(31)

    cmsTextFont = 61
    extraTextFont = 52

    latex2 = TLatex();
    latex2.SetNDC();
    latex2.SetTextSize(0.04);
    latex2.SetTextAlign(31);

    cmsText = "CMS"
    extraText = "Preliminary"
    
    latex.SetTextSize(0.04)
    latex.SetTextFont(cmsTextFont)
    latex.DrawLatex(0.23, 0.95, cmsText )
    
    latex.SetTextFont(extraTextFont)
    latex.SetTextSize(0.04*0.76)
    latex.DrawLatex(0.35, 0.95 , extraText )
    
    latex2.DrawLatex(0.95, 0.95, '35.9 fb^{-1}(13TeV) ' );

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
    # print(x)
    # print(y)
    # print(exl)
    # print(exh)
    # print(eyl)
    # print(eyh)
    errors = TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    return errors


def getSystVariation(nominalHist,systHists,sampleName,region):
    # to calculate the total sysHistUp and down
    #here the input nominalHist and systHists are for one summed process
    # systHists include 'up' and 'down' for varias sources, but it's just for one process
    #???the calculation seems wrong
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()
    
    for systHi in systHists.keys():
    #systHi is 'up' or 'down' for varias sources
    #so this is to sum the sytstmatic variation for sources of systematic uncertainty
        print( systHi )
        if "bTag" in systHi: continue
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist,-1)
        syst.Divide(nominalHist)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            # print( "{0}: {1:.1f} ({2:.1f} - {3:.1f})".format(i, 100*syst.GetBinContent(i),systHists[systHi].GetBinContent(i),nominalHist.GetBinContent(i)) )
            if "up" in syst.GetName():
                # print( 'sytHistUp: ', systHistUp.GetBinContent() )
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
    for i in range(1,systHistUp.GetXaxis().GetNbins()+1):
        systHistUp.SetBinContent(i,(math.sqrt(systHistUp.GetBinContent(i)))*nominalHist.GetBinContent(i))
        systHistDown.SetBinContent(i,(math.sqrt(systHistDown.GetBinContent(i)))*nominalHist.GetBinContent(i))

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
    #systHi is 'up' or 'down' for varias sources
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
        systsUp.SetBinContent(i, math.sqrt( systsUp.GetBinContent(i)*systsUp.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        systsDown.SetBinContent(i, math.sqrt( systsDown.GetBinContent(i)*systsDown.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
    return systsUp,systsDown



if __name__ == "__main__":
    main()
