from tkinter import Variable

import numpy as np
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import summedProcessList

from writeCSVforEY import getSummedHists


def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/'
   
   
     
    
    
    FR_ptInEtaList = []
    version = 'v5forFakeRateEtaDivided'
    # versions = ['v4forFakeRate_eta0-06', 'v4forFakeRate_eta06-12', 'v4forFakeRate_eta12-18', 'v4forFakeRate_eta18-24']
    # for version in versions:``
    ptBins = np.array( [20.0, 40.0, 60.0, 80.0, 120.0,  220.0] )
    variableDic = {
        'tausL_1pt': ptBins,
    }
    # etaList = ['_Eta1', '_Eta2', '_Eta3', '_Eta4']
    etaList = ['_Eta1']
    for ieta in etaList:
        ietaPt =  plotPtInEta( version, inputDir, variableDic , ieta, False)
        FR_ptInEtaList.append(ietaPt)
    print(FR_ptInEtaList)
    
    
    etaBins = np.array( [0.0, 0.6, 1.2, 1.8, 2.4] )
    fakeRate2D = ROOT.TH2D('fakeRate2D', 'fake rate in pt eta',  len(ptBins)-1, ptBins, len(etaBins)-1, etaBins )
    
    
    #application in AR
    
    
    
    
def plotPtInEta( version, inputDir, variableDic, etaRegion , isAR=False):
    
    inputDirDic ={
        'mc': inputDir + 'mc/variableHists_' + version + '/',
        'data': inputDir + 'data/variableHists_' + version + '/'
    } 

    regionList = ["1tau0lCRGen", '1tau0lCR', '1tau0lCRLTauGen', "1tau0lCRLTau"]
    for ire in range(len(regionList)):
        regionList[ire] = regionList[ire] + etaRegion

    sumProcessPerVar = {}
    #sumProcessPerVar[var][region][sumedProcess] = hist
    for ivar in variableDic.keys():
        sumProcessPerVar[ivar] = getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )

    # for ivar in variableDic.keys():
        
    # h_CR_dataSubBG, h_CRLTau_dataSubBG = getHistForFakeRate( list(variableDic.keys())[0], sumProcessPerVar)
    h_CR_dataSubBG, h_CRLTau_dataSubBG = getHistForFakeRate( ivar, sumProcessPerVar, etaRegion)

    binLowEges = variableDic[list(variableDic.keys())[0]]
    h_CR_dataSubBG_rebin =  h_CR_dataSubBG.Rebin(len(binLowEges)-1, 'h_CR_dataSubBG_rebin', binLowEges  ) 
    h_CRLTau_dataSubBG_rebin = h_CRLTau_dataSubBG.Rebin(len(binLowEges)-1, 'CRLTau', binLowEges )

    h_fakeRateCR = h_CR_dataSubBG_rebin.Clone()
    h_fakeRateCR.Reset()
    h_fakeRateCR.Sumw2()
    h_fakeRateCR.Divide(h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin)
    h_fakeRateCR.SetName('fakeRate_'+version)

    plotDir = inputDirDic['mc'] + 'results/' 
    uf.checkMakeDir( plotDir )
    plotName = plotDir + list(variableDic.keys())[0] +etaRegion+ '_FR.png'
    plotEfficiency( h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin, h_fakeRateCR, plotName )
    
    return h_fakeRateCR
    
    






def getHistForFakeRate( var, sumProcessPerVar, etaRegion ):
    h_CR_data = sumProcessPerVar[var]['1tau0lCR'+etaRegion]['data'] 
    h_CR_data.Print()
    h_CR_bgGenTau = addBGHist(sumProcessPerVar, var, '1tau0lCRGen'+etaRegion)
    h_CR_bgGenTau.Print() 
    h_CR_dataSubBG = h_CR_data - h_CR_bgGenTau
    # h_CR_dataSubBG = h_CR_data.Add(h_CR_bgGenTau, -1).Clone()
    h_CR_dataSubBG.Print()

    h_CRLTau_data = sumProcessPerVar[var]['1tau0lCRLTau'+etaRegion]['data'] 
    h_CRLTau_bgGenTau = addBGHist(sumProcessPerVar, var, '1tau0lCRLTauGen'+etaRegion)
    h_CRLTau_dataSubBG = h_CRLTau_data - h_CRLTau_bgGenTau

    return h_CR_dataSubBG, h_CRLTau_dataSubBG





def plotEfficiency(h_numeritor, h_dinominator, h_efficiency, plotName):
    can = ROOT.TCanvas('efficiency', 'efficiency', 800, 600)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)

    h_dinominator.SetLineColor(ROOT.kBlue+4)
    h_dinominator.GetYaxis().SetRangeUser(h_numeritor.GetMinimum()*0.9, h_dinominator.GetMaximum()*1.1)
    h_dinominator.Draw()
    h_numeritor.Draw('same')
    can.Update()

    rightmax = 1.1*h_efficiency.GetMaximum();
    scale = ROOT.gPad.GetUymax()/rightmax;
    h_efficiency.SetLineColor(ROOT.kRed)
    h_efficiency.Scale(scale) #!!!need to consider this scaling effect on uncertainty
    h_efficiency.Draw("same")
    
    axis = ROOT.TGaxis(ROOT.gPad.GetUxmax(),ROOT.gPad.GetUymin(),
        ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymax(),0,rightmax,510,"+L")
    axis.SetLineColor(ROOT.kRed)
    axis.SetLabelColor(ROOT.kRed)
    axis.Draw()


    can.SaveAs(plotName)



def addBGHist(sumProcessPerVar, var, region):
    sumHist = sumProcessPerVar[var][region][summedProcessList[0]]
    sumHist.Reset()
    sumHist.Sumw2()
    sumHist.SetName(region+ '_bgSum_' + var )
    for ipro in summedProcessList:
        if ipro=='data' or ipro=='tttt': continue
        sumHist.Add( sumProcessPerVar[var][region][ipro])
    return sumHist




if __name__=='__main__':
    main()
