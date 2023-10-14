
from math import sqrt

import numpy as np
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import summedProcessList

from setTDRStyle import addCMSTextToCan, setTDRStyle
from writeCSVforEY import  histDateMinusGenBG




def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v3FR_measure_2prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v5FR_measure3EtaBins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v5FR_measure3EtaBins_1prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0LepLAdded_v46addPOGIDL/mc/variableHists_v5FR_measure3EtaBins_1prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v51TESNewLepObjectRemovalCorrected/mc/variableHists_v0FR_measure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v51TESNewLepObjectRemovalCorrected/mc/variableHists_v0FR_measure_3prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v0FR_measureVR_1prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v0FR_measureVR_3prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v5updateHLTSF_v52noHLTButPreSelection/mc/variableHists_v0FR_measureVR_3prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/mc/variableHists_v0FR_measureVR_1prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/mc/variableHists_v0FR_measureVR_1prong_Add/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v57ovelapWithTausF/mc/variableHists_v0FR_measureVR_3prong/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v0FR_measureVR_3prong/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v0FR_measureVR_3prong/'
    
   
    ptBins = np.array( [20.0, 30, 40.0, 50, 70.0, 90.0, 120.0,  300.0] )
    variableDic = {
        # 'tausL_1pt': ptBins,
        'tausF_1jetPt': ptBins,
        # 'tausF_1jetEtaAbs' : etaBins 
    }
    
    etaBins = np.array([0, 0.8, 1.5, 2.3])
    
  
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    era = uf.getEraFromDir(inputDir)
        
    # isVR = True
    isVR = False
    
    #measure FR in CR
    FR_ptInEtaList, inoUse = getFRAndARNotTList( inputDirDic, variableDic, etaBins, isVR, True, era, 'VR' )
    writeFRToFile( FR_ptInEtaList, inputDirDic, ptBins, etaBins )
    
    plotOverlay_FR(inputDirDic, variableDic, etaBins,isVR, era)
    plotOverlay_FR(inputDirDic, variableDic, etaBins,isVR, era, False)
   
def plotOverlay_FR(inputDirDic, variableDic, etaBins,isVR, era, isJet=True): 
    FR_EtaListDic = {}
    FR_EtaListDic['1Eta'] = []
    FR_EtaListDic['2Eta'] = []
    FR_EtaListDic['3Eta'] = []
    # CRnames = ['CRa',  'CRc'] # for bjet
    # CRnames = ['CRa',  'CRb', 'CRc'] # for bjet
    # CRnames = ['CR', 'CRa'] # for jet
    if isJet:
        CRnames = ['CRb', 'VR'] # for jet
        legendList = ['<8 jets', '>=8 jets']
        plotUncer = False
    else:
        # CRnames = ['CRc', 'CRb'] # for bjet; new 'VR' and 'CR'
        CRnames = ['CRb', 'CRc'] # for bjet; new 'VR' and 'CR'
        legendList = [ '=1 bjet', '>=2 bjets']
        plotUncer = True
    for iCR in CRnames:
        iFR_EtaList, inoUse = getFRAndARNotTList( inputDirDic, variableDic, etaBins, isVR, True, era, iCR )
        FR_EtaListDic['1Eta'].append(iFR_EtaList[0])
        FR_EtaListDic['2Eta'].append(iFR_EtaList[1])
        FR_EtaListDic['3Eta'].append(iFR_EtaList[2])
    
    plotDir = inputDirDic['mc'] + 'results/'
    for iEta in ['1Eta', '2Eta', '3Eta']:
        # overLayName = plotDir + 'overlay_' + iEta +'.png'
        overLayName = plotDir + 'overlay' + CRnames[0]+CRnames[1] + iEta +'.png'
        # plotFROverlay( FR_EtaListDic[iEta], legendList, era, "FR", overLayName, False, [0, 0.35] )
        plotFROverlay( FR_EtaListDic[iEta], legendList, era, "FR", overLayName, plotUncer, [0, 0.35] )
   
    
    
            
def plotFROverlay(FRInRegionList, legendList,  era, yTitle,  plotName, ifUncerBand=False, yRange=[]):
    print('start to plot overlay..........\n')
    # can = ROOT.TCanvas('FR overlay', 'FR_overlay', 800, 600)
    can = ROOT.TCanvas('FR overlay', 'FR_overlay', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)
    # ROOT.gStyle.SetTitleSize(0.07, "X")#not working
    # ROOT.gStyle.SetTitleSize(0.05, "Y")
    
    FRInRegionList[0].GetYaxis().SetRangeUser(FRInRegionList[0].GetMinimum()*0.6, FRInRegionList[0].GetMaximum()*1.5)
    FRInRegionList[0].GetYaxis().SetTitle(yTitle)
    FRInRegionList[0].GetYaxis().SetTitleSize(0.05)
    FRInRegionList[0].GetYaxis().SetLabelSize(0.035)
    FRInRegionList[0].GetYaxis().SetTitleOffset(1.0)
    FRInRegionList[0].GetXaxis().SetTitle(FRInRegionList[0].GetTitle())
    FRInRegionList[0].GetXaxis().SetTitleSize(0.05)
    FRInRegionList[0].SetLineColor(ROOT.kOrange)
    FRInRegionList[0].SetLineWidth(3)
    FRInRegionList[0].SetMarkerStyle(45)
    FRInRegionList[0].SetMarkerSize(2)
    FRInRegionList[0].SetMarkerColor(ROOT.kOrange)
    if len(yRange)>1:
        FRInRegionList[0].GetYaxis().SetRangeUser(yRange[0], yRange[1])
    
    FRInRegionList[0].Draw()
    print(FRInRegionList[0].GetName())
    
    FRInRegionList[1].SetLineColor(ROOT.kRed)
    FRInRegionList[1].SetLineWidth(3)
    FRInRegionList[1].SetMarkerStyle(94)
    FRInRegionList[1].SetMarkerSize(2)
    FRInRegionList[1].SetMarkerColor(ROOT.kRed )
    FRInRegionList[1].Draw('same')
    
    # if len(CRnames)>2:
    if len(FRInRegionList)>2:
        FRInRegionList[2].SetLineColor(ROOT.kMagenta)
        FRInRegionList[2].SetLineWidth(3)
        FRInRegionList[2].SetMarkerStyle(22)
        FRInRegionList[2].SetMarkerSize(2)
        FRInRegionList[2].SetMarkerColor(ROOT.kMagenta )
        FRInRegionList[2].Draw('same')
    
    #add uncertainty band for FR1
    if ifUncerBand:
        uncert = FRInRegionList[0].Clone()
        uncertValue = 0.10
        for ibin in range(1, FRInRegionList[0].GetNbinsX()+1):
            uncert.SetBinError(ibin, uncert.GetBinContent(ibin)*uncertValue)
        uncert.SetFillStyle(3013)
        uncert.SetFillColor(ROOT.kOrange)
        uncert.Draw('same e2')
   
    legend = ROOT.TLegend(0.55,0.7,0.9,0.9)
    for (i,iLe) in enumerate(legendList):
        legend.AddEntry(FRInRegionList[i], iLe)
            
   
    if ifUncerBand: 
        uncerEntry = '{} % uncertainty'.format(uncertValue*100)    
        legend.AddEntry(uncert, uncerEntry)
    legend.Draw()
    
    addCMSTextToCan(can, 0.18, 0.3, 0.92, era)
    
    can.SaveAs( plotName )
    print( yTitle, ' overlay plot here:', plotName )    
    
        

def writeFRToFile( FR_ptInEtaList, inputDirDic, ptBins, etaBins):
    # etaBins = np.array([0, 0.8,1.6,2.4])
    # etaBins = np.array([0, 1.5,2.4])
    
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
            
    
def getSumProcessVarEta( inputDirDic, ieta, variableDic, isVR=True, ifGetLNotT=True, FRMeasureRegion='CR'):

    regionList = ["1tau0lCRGen", '1tau0lCR', '1tau0lCRLTauGen', "1tau0lCRLTau"]
    for (i,ire) in enumerate(regionList):
        ire = ire.replace('CR', FRMeasureRegion)
        regionList[i] = ire
    
    if ifGetLNotT:
        regionList.append( '1tau0lVRLTauNotT' )
        regionList.append( '1tau0lVRLTauNotTGen' )
        if not isVR:
            regionList[4] = '1tau0lCRLTauNotT'
            regionList[5] = '1tau0lCRLTauNotTGen'
    

    #sumProcessPerVar[var][region][sumedProcess] = hist
    for ire in range(len(regionList)):
        regionList[ire] = regionList[ire] + ieta
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableDic.keys():
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
    
    return sumProcessPerVar, inputDirDic, regionList
       
# def getInputDic( inVersion, histVersion, era):
#     inputDirBase = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/' + era +'/'
#     inputDirDic = {
#         'mc': inputDirBase + inVersion + '/mc/' + histVersion + '/',
#         'data': inputDirBase + inVersion + '/data/' + histVersion + '/',
#     }
#     return inputDirDic
        
    
    
    
def plotPtInEta(  sumProcessPerVar, inputDirDic, regionList, variableDic, etaRegion , ifPlot = True, era = '2016', isDataMC=False):
    print('starting to plot FR for ieta', )
    h_CR_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys())[0]], regionList[1], regionList[0], isDataMC)
    h_CRLTau_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys())[0]], regionList[3], regionList[2], isDataMC)

    binLowEges = variableDic[list(variableDic.keys())[0]]
    # h_CR_dataSubBG_rebin =  h_CR_dataSubBG.Rebin(len(binLowEges)-1, 'h_CR_dataSubBG_rebin', binLowEges  ) 
    h_CR_dataSubBG_rebin =  h_CR_dataSubBG.Rebin(len(binLowEges)-1, regionList[1], binLowEges  ) 
    # h_CRLTau_dataSubBG_rebin = h_CRLTau_dataSubBG.Rebin(len(binLowEges)-1, 'CRLTau', binLowEges )
    h_CRLTau_dataSubBG_rebin = h_CRLTau_dataSubBG.Rebin(len(binLowEges)-1, regionList[3], binLowEges )
    if len(regionList)>4:
        h_VRLTauNotT_dataSubBG = histDateMinusGenBG(list(variableDic.keys())[0], sumProcessPerVar[list(variableDic.keys())[0]], regionList[4], regionList[5], isDataMC) #tausL_1pt in VRLNotT
        h_VRLTauNotT_dataSubBG_rebin = h_VRLTauNotT_dataSubBG.Rebin(len(binLowEges)-1, regionList[4], binLowEges)
    else:
        h_VRLTauNotT_dataSubBG_rebin = h_CR_dataSubBG_rebin.Clone()
        h_VRLTauNotT_dataSubBG_rebin.Reset()

    h_fakeRateCR = h_CR_dataSubBG_rebin.Clone()
    h_fakeRateCR.Reset()
    h_fakeRateCR.Sumw2()
    h_fakeRateCR.Divide(h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin)
    h_fakeRateCR.SetName('FR_' + regionList[1] )
    
    

    if ifPlot:
        plotDir = inputDirDic['mc'] + 'results/' 
        uf.checkMakeDir( plotDir )
        if not isDataMC:
            plotName = plotDir + list(variableDic.keys())[0] +etaRegion+'_'+regionList[1]+ '_FR_sumGenBg_better.png'
        else:
            plotName = plotDir + list(variableDic.keys())[0] +etaRegion+ '_FR_sumGenBg_better_totalMCAsData.png'
        plotEfficiency( h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin, h_fakeRateCR, plotName, era , True, 'fake rate')
   
    # h_fakeRateCR.Print() 
    return h_fakeRateCR, h_VRLTauNotT_dataSubBG_rebin
    
    
def getFRAndARNotTList( inputDirDic, variableDic, etaBins, isVR,  ifPlot=True, era='2016', FRMeasureRegion='CR'):
    # etaBins = np.array([0, 0.8, 1.5, 2.3])
    etaList = []
    for i in range(1, len(etaBins)):
        etaList.append('_Eta'+str(i))
    FR_ptInEtaList = []
    tauPtEtaListAR = []
    for ieta in etaList:
        sumProcessPerVar, inputDirDic, regionList  = getSumProcessVarEta( inputDirDic, ieta, variableDic, isVR, False, FRMeasureRegion )
        ietaPt, ietaVR =  plotPtInEta( sumProcessPerVar, inputDirDic, regionList,  variableDic , ieta, ifPlot, era)
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



#!!!making it more generic 
#!!!in usefulFunc
def plotEfficiency(h_numeritor, h_dinominator, h_eff, plotName, era = '2016', ifFixMax=True, rightTitle='efficiency'):
    # setTDRStyle()#???not sure why no content line
    # can = ROOT.TCanvas('efficiency', 'efficiency', 800, 600)
    can = ROOT.TCanvas('efficiency', 'efficiency', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)

    # h_dinominator.SetLineColor(ROOT.kOrange)
    h_dinominator.GetYaxis().SetRangeUser(h_numeritor.GetMinimum()*0.9, h_dinominator.GetMaximum()*1.5)
    h_dinominator.GetYaxis().SetTitle('Events')
    h_dinominator.GetYaxis().SetTitleSize(0.05)
    h_dinominator.GetYaxis().SetLabelSize(0.03)
    h_dinominator.GetYaxis().SetTitleOffset(1.1)
    # h_dinominator.GetXaxis().SetTitle('pt of tau mother jet')
    h_dinominator.GetXaxis().SetTitle(h_dinominator.GetTitle())
    h_dinominator.GetXaxis().SetTitleSize(0.05)
    h_dinominator.SetLineWidth(3)
    h_dinominator.SetLineColorAlpha(ROOT.kOrange+1, 0.8)
    # h_dinominator.SetLineStyle(2)
    
    h_dinominator.Draw()
    # h_numeritor.SetLineColor(ROOT.kMagenta-4)
    # h_numeritor.SetLineColor(ROOT.kBlue)
    h_numeritor.SetLineColorAlpha(ROOT.kGreen, 0.5)
    h_numeritor.SetLineWidth(3)
    # h_numeritor.SetLineStyle(8)
    h_numeritor.Draw('same')
    can.Update()

    h_efficiency = h_eff.Clone()
    if ifFixMax:
        rightmax = .35
        # rightmax = .2
    else:
        rightmax = 1.7*h_efficiency.GetMaximum();
    scale = ROOT.gPad.GetUymax()/rightmax;
    h_efficiency.SetLineColor(ROOT.kRed)
    h_efficiency.SetLineWidth(4)
    # h_efficiency.SetMarkerStyle(3)
    h_efficiency.SetLineStyle(1)
    h_efficiency.Scale(scale) #!!!need to consider this scaling effect on uncertainty
    h_efficiency.Draw("same")
    
    #print
    # for i in range(1,h_efficiency.GetNbinsX()+1):
    #     print( i, 'bin: ', h_dinominator.GetBinContent(), h_dinominator.GetBinError(), h_numeritor.GetBinContent(), h_numeritor.GetBinContent())
    
    axis = ROOT.TGaxis(ROOT.gPad.GetUxmax(),ROOT.gPad.GetUymin(), ROOT.gPad.GetUxmax(), ROOT.gPad.GetUymax(),0,rightmax,510,"+L")
    # axis.SetRangeUser(0, rightmax*1.4)
    axis.SetLineColor(ROOT.kRed)
    axis.SetLabelColor(ROOT.kRed)
    # axis.SetTitle('fake rate')
    # axis.SetTitle('efficiency')
    axis.SetTitle(rightTitle)
    axis.SetTitleSize(0.05)
    axis.SetTitleColor(ROOT.kRed)
    # axis.SetRangeUser(0, 0.4)
    axis.Draw()


    # legend = ROOT.TLegend(0.4,0.7,0.9,0.9)
    legend = ROOT.TLegend(0.35,0.68,0.9,0.9)
    legend.AddEntry(h_dinominator, "denominator: "+ h_dinominator.GetName())
    legend.AddEntry(h_numeritor, "numeritor: "+ h_numeritor.GetName())
    legend.AddEntry(h_efficiency, h_efficiency.GetName())
    legend.Draw()
    
    # addCMSTextToCan(can, 0.21, 0.33, 0.91, era)     

    can.SaveAs(plotName)







if __name__=='__main__':
    main()
