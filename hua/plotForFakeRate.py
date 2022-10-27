
from math import sqrt
from unicodedata import east_asian_width

import numpy as np
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import summedProcessList

from setTDRStyle import setTDRStyle
from writeCSVforEY import getSummedHists


def main():
    era = '2016' 
    # inVersion = 'v2baselineAddingTauProng_v38TESandJERTauPt20_preselection'
    inVersion = 'v0addMoreVariables_v39addTauBranches'
    # histVersion = 'variableHists_v6forFakeRate3EtaRegions'
    # histVersion = 'variableHists_v10ExpandingTauPtRange'
    # histVersion = 'variableHists_v0forFakeRate'
    # histVersion = 'variableHists_v1forFRSwitchToTauJetPt'
    # histVersion = 'variableHists_v1forFRSwitchToTauJetPt_1prong'
    # histVersion = 'variableHists_v1forFRSwitchToTauJetPt_3prong'
    histVersion = 'variableHists_v2forFRVariables'
    
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/'
    # version = 'v6forFakeRate3EtaRegions'
   
    # ptBins = np.array( [20.0, 40.0, 60.0, 80.0, 120.0,  300.0] )
    ptBins = np.array( [20.0, 30, 40.0, 50, 70.0, 90.0, 120.0,  300.0] )
    variableDic = {
        # 'tausL_1pt': ptBins,
        'tausF_1jetPt': ptBins,
    }
  
    inputDirDic = getInputDic(inVersion, histVersion, era) 
        
    
    # isVR = True
    isVR = False
    FR_ptInEtaList, tauPtEtaListAR = getFRAndARNotTList(inputDirDic, variableDic, isVR, True)
    
    # writeFRToFile( FR_ptInEtaList, inputDirDic, ptBins )
    
    
    #application in AR
    # getFTFromLNotTData(FR_ptInEtaList, tauPtEtaListAR)
            
    

def writeFRToFile( FR_ptInEtaList, inputDirDic, ptBins):
    etaBins = np.array([0, 0.8,1.6,2.3])
    
    # outFileName = inputDirDic['mc'] + 'results/fakeRateInPtEta_sumGenBG.root'
    outFileName = inputDirDic['mc'] + 'results/fakeRateInPtEta_sumGenBG_newBin.root'
    outFile = ROOT.TFile( outFileName, "RECREATE") 
    fakeRate2D = ROOT.TH2D('fakeRate2D', 'fake rate in pt eta',  len(ptBins)-1, ptBins, len(etaBins)-1, etaBins )
    for ixbin in range(len(ptBins)-1):
        for iybin in range(len(etaBins)-1):
            iFR =  FR_ptInEtaList[iybin].GetBinContent(ixbin+1) #if the sum of squares of weights has been defined (via Sumw2), this function returns the sqrt(sum of w2). otherwise it returns the sqrt(contents) for this bin.
            iFRerror =  FR_ptInEtaList[iybin].GetBinError(ixbin+1)
            fakeRate2D.SetBinContent(ixbin+1, iybin+1, iFR)
            fakeRate2D.SetBinError(ixbin+1, iybin+1, iFRerror)
    
    outFile.Write()
    outFile.Close()
    print('fake rate file here: ', outFile.GetName())
    
    
 


def getFTFromLNotTData(FR_ptInEtaList, tauPtEtaListAR, ifPtBin=True):    
    fakeTauBG = 0.0
    fakeTauError = 0.0
    FTFromData = ROOT.TH1D()
    if ifPtBin:
        FTFromData = tauPtEtaListAR[0].Clone()
        FTFromData.Reset()
    else:
        etaBins = np.array([0, 0.8,1.6,2.3])
        FTFromData = ROOT.TH1D('fake tau from data', 'fake tau from data', 3, etaBins )
    FTFromData.Sumw2()
   
    for ipt in range(len(tauPtEtaListAR)):
        iEtaFT, iEtaFTErr, iFT_hist = calFTPerEta( tauPtEtaListAR[ipt], FR_ptInEtaList[ipt])
        fakeTauBG = fakeTauBG+iEtaFT
        fakeTauError = fakeTauError + iEtaFTErr
        if ifPtBin: 
            FTFromData.Add(iFT_hist)
        else:
            FTFromData.SetBinContent(ipt+1, iEtaFT)
            # FTFromData.SetBinError(ipt+1, iEtaFTErr)
            FTFromData.SetBinError(ipt+1, sqrt(iEtaFTErr) ) #???
    
        
    print('fake tau in AR:{} error: {}, '.format( fakeTauBG, sqrt(fakeTauError) ) )
    print('fake tau from hist ', FTFromData.Integral())
    return FTFromData
    
def calFTPerEta( tauptAR, FR):
    FT = 0.0
    FTErr = 0.0
    distribution = tauptAR.Clone()
    distribution.Reset()
    # distribution.Sumw2()
    for ibin in range(1,tauptAR.GetNbinsX()+1):
        iN_LnotT = tauptAR.GetBinContent(ibin)
        iFR = FR.GetBinContent(ibin)
        ifakeTau = iN_LnotT*(iFR/(1-iFR))
        FT=FT+ifakeTau
        
        iFRErr = FR.GetBinError(ibin)
        iNErr = ( pow(iN_LnotT, 2)/pow(1-iFR, 4) )*iFRErr + pow(iFR/(1-iFR), 2)*tauptAR.GetBinError(ibin)
        FTErr = FTErr+iNErr
        # print('iFR={} ,iFRErr={} , iFT={}, iNErr={}'.format( iFR, iFRErr, FT, iNErr) )
        
        distribution.SetBinContent( ibin, ifakeTau )
        distribution.SetBinError(ibin, sqrt( iNErr) )#???
    return FT, FTErr, distribution
            
    
def getSumProcessVarEta( inputDirDic, ieta, variableDic, isVR=True):
    # inputDirDic = getInputDic( inVersion, histVersion, era)

    regionList = ["1tau0lCRGen", '1tau0lCR', '1tau0lCRLTauGen', "1tau0lCRLTau", "1tau0lVRLTauNotT", "1tau0lVRLTauNotTGen"]
    if not isVR:
        regionList[4] = '1tau0lCRLTauNotT'
        regionList[5] = '1tau0lCRLTauNotTGen'
    

    #sumProcessPerVar[var][region][sumedProcess] = hist
    # etaList = ['_Eta1', '_Eta2', '_Eta3']
    for ire in range(len(regionList)):
        regionList[ire] = regionList[ire] + ieta
    sumProcessPerVar = {}
    for ivar in variableDic.keys():
        sumProcessPerVar[ivar] = getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
    
    return sumProcessPerVar, inputDirDic, regionList
       
def getInputDic( inVersion, histVersion, era):
    inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/' + era +'/'
    inputDirDic = {
        'mc': inputDirBase + inVersion + '/mc/' + histVersion + '/',
        'data': inputDirBase + inVersion + '/data/' + histVersion + '/',
    }
    return inputDirDic
        
    
    
    
def plotPtInEta(  sumProcessPerVar, inputDirDic, regionList, variableDic, etaRegion , ifPlot = True):

        
    # h_CR_dataSubBG, h_CRLTau_dataSubBG = getHistForFakeRate( list(variableDic.keys())[0], sumProcessPerVar)
    h_CR_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys())[0]], '1tau0lCR'+etaRegion, '1tau0lCRGen'+etaRegion)
    h_CRLTau_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys())[0]], '1tau0lCRLTau'+etaRegion, '1tau0lCRLTauGen'+etaRegion)
    # h_VRLTauNotT_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys()[0]], '1tau0lVRLTauNotT'+etaRegion)
    h_VRLTauNotT_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys())[0]], regionList[4], regionList[5]) #tausL_1pt in VRLNotT
    #what if it's jets_HT; jets_HT in eta region; could not work because we can't know taupt in bin


    binLowEges = variableDic[list(variableDic.keys())[0]]
    h_CR_dataSubBG_rebin =  h_CR_dataSubBG.Rebin(len(binLowEges)-1, 'h_CR_dataSubBG_rebin', binLowEges  ) 
    h_CRLTau_dataSubBG_rebin = h_CRLTau_dataSubBG.Rebin(len(binLowEges)-1, 'CRLTau', binLowEges )
    h_VRLTauNotT_dataSubBG_rebin = h_VRLTauNotT_dataSubBG.Rebin(len(binLowEges)-1, regionList[4], binLowEges)

    h_fakeRateCR = h_CR_dataSubBG_rebin.Clone()
    h_fakeRateCR.Reset()
    h_fakeRateCR.Sumw2()
    h_fakeRateCR.Divide(h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin)
    h_fakeRateCR.SetName('fakeRate')

    if ifPlot:
        plotDir = inputDirDic['mc'] + 'results/' 
        uf.checkMakeDir( plotDir )
        # plotName = plotDir + list(variableDic.keys())[0] +etaRegion+ '_FR_sumGenBg.png'
        plotName = plotDir + list(variableDic.keys())[0] +etaRegion+ '_FR_sumGenBg_better.png'
        plotEfficiency( h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin, h_fakeRateCR, plotName )
   
    h_fakeRateCR.Print() 
    return h_fakeRateCR, h_VRLTauNotT_dataSubBG_rebin
    
    
def getFRAndARNotTList( inputDirDic, variableDic, isVR, ifPlot=True):
    etaList = ['_Eta1', '_Eta2', '_Eta3']
    FR_ptInEtaList = []
    tauPtEtaListAR = []
    for ieta in etaList:
        sumProcessPerVar, inputDirDic, regionList  = getSumProcessVarEta( inputDirDic, ieta, variableDic, isVR )
        ietaPt, ietaVR =  plotPtInEta( sumProcessPerVar, inputDirDic, regionList,  variableDic , ieta, ifPlot)
        FR_ptInEtaList.append(ietaPt)
        tauPtEtaListAR.append(ietaVR)
    return FR_ptInEtaList, tauPtEtaListAR





def getHistForFakeRate( var, sumProcessPerVar, etaRegion ):
    h_CR_data = sumProcessPerVar[var]['1tau0lCR'+etaRegion]['data'] 
    h_CR_data.Print()
    h_CR_bgGenTau = addBGHist(sumProcessPerVar, var, '1tau0lCRGen'+etaRegion)
    h_CR_bgGenTau.Print() 
    h_CR_dataSubBG = h_CR_data - h_CR_bgGenTau
    h_CR_dataSubBG.Print()

    h_CRLTau_data = sumProcessPerVar[var]['1tau0lCRLTau'+etaRegion]['data'] 
    h_CRLTau_bgGenTau = addBGHist(sumProcessPerVar, var, '1tau0lCRLTauGen'+etaRegion)
    h_CRLTau_dataSubBG = h_CRLTau_data - h_CRLTau_bgGenTau
    
    h_VR_data = sumProcessPerVar[var]['1tau0lVRLTauNotT'+etaRegion]['data']

    return h_CR_dataSubBG, h_CRLTau_dataSubBG

def histDateMinusGenBG(var, sumProcessIVar, region, genRegion):
    h_data = sumProcessIVar[region]['data']
    h_data.Sumw2()
    h_bgGen = addBGHist(sumProcessIVar, var, genRegion) #???no requiring gen here???
    h_dataMBG = h_data - h_bgGen
    return h_dataMBG



def plotEfficiency(h_numeritor, h_dinominator, h_eff, plotName):
    setTDRStyle()
    can = ROOT.TCanvas('efficiency', 'efficiency', 800, 600)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)

    # h_dinominator.SetTitle("FR ")
    h_dinominator.SetLineColor(ROOT.kOrange)
    h_dinominator.GetYaxis().SetRangeUser(h_numeritor.GetMinimum()*0.9, h_dinominator.GetMaximum()*1.1)
    h_dinominator.Draw()
    h_numeritor.SetLineColor(ROOT.kMagenta-4)
    h_numeritor.Draw('same')
    can.Update()

    h_efficiency = h_eff.Clone()
    rightmax = 1.1*h_efficiency.GetMaximum();
    scale = ROOT.gPad.GetUymax()/rightmax;
    h_efficiency.SetLineColor(ROOT.kRed)
    h_efficiency.SetLineWidth(2)
    h_efficiency.Scale(scale) #!!!need to consider this scaling effect on uncertainty
    h_efficiency.GetXaxis().SetTitle('tau mother jet pt')
    h_efficiency.Draw("same")
    
    axis = ROOT.TGaxis(ROOT.gPad.GetUxmax(),ROOT.gPad.GetUymin(),
        ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymax(),0,rightmax,510,"+L")
    axis.SetLineColor(ROOT.kRed)
    axis.SetLabelColor(ROOT.kRed)
    axis.Draw()


    legend = ROOT.TLegend(0.6,0.7,0.9,0.9)
    legend.AddEntry(h_dinominator, "denominator: FTau-genMC")
    legend.AddEntry(h_numeritor, "numeritor: TTau-genMC")
    legend.AddEntry(h_efficiency, "FR")
    legend.Draw()

    can.SaveAs(plotName)



def addBGHist(sumProcessIVar, var, region):
    sumHist = sumProcessIVar[region][summedProcessList[0]]
    sumHist.Reset()
    sumHist.Sumw2()
    sumHist.SetName(region+ '_bgSum_' + var )
    for ipro in summedProcessList:
        # if ipro=='data' or ipro=='tttt': continue
        if ipro=='data' or ipro=='qcd' or ipro=='tttt': continue
        sumHist.Add( sumProcessIVar[region][ipro])
    return sumHist




if __name__=='__main__':
    main()
