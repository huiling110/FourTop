import numpy as np
import array
import ROOT

import usefulFunc as uf

from plotForFakeRate import plotEfficiency, plotFROverlay

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2baslineNoHLT_v52noHLTButPreSelection/mc/variableHists_v0triggerEff/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v0triggerEff/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v0triggerEffBugFixed/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v1triggerEffMuonSel/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v3MuonSelUpdatedNoJetHLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v4MuonSelUpdated/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v5addBjetToBaseline/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v6oneBjetToBaseline/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v7HLTRemove2btag/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v54noHLTButPre/mc/variableHists_v0triggerEff/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0triggerEff_NoBtagShapeWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v55ojectRemovalwithTightNoHLT/mc/variableHists_v1triigerEff_btagShapeWeight/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLT_v56NoHLTButPre/mc/variableHists_v1triigerEff_btagShapeWeight/'
    
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(inputDir)
    
    #overlay of MC truth efficiency, MC reference efficiency and data reference efficiency
    # plotEfficiencyHLT(inputDirDic)
    
    #plotSF
    plotSF(inputDirDic)
    
    
   
def plotSF(inputDirDic):
    # file = ROOT.TFile(inputDir+'tt') 
    # tt_1b = 
    variableList = ['jetsHTAnd6pt']
    regionList = ['baseline1Muon1b', 'baseline1MuonAndHLT1b', 'baseline1Muon2b', 'baseline1MuonAndHLT2b','baseline1Muon3b', 'baseline1MuonAndHLT3b' ]
    
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableList:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
  
    bRegions = ['baseline1Muon1b', 'baseline1Muon2b', 'baseline1Muon3b']
    # bRegions = ['baseline1Muon1b']
    regionTitleDic = {
        'baseline1Muon1b': 'b jets number = 1',
        'baseline1Muon2b': 'b jets number = 2',
        'baseline1Muon3b': '2 < b jets number < 8',
    }
    
    for ibR in bRegions:
        bRegions_nu = ibR.replace('1Muon', '1MuonAndHLT')
        print('regions: ', ibR, bRegions_nu)
        canTitle = regionTitleDic[ibR] 
        dataEff1b = getEffHist(sumProcessPerVar,  bRegions_nu, ibR, 'singleMu', plotDir, canTitle) 
        ttEff1b = getEffHist(sumProcessPerVar, bRegions_nu, ibR, 'tt', plotDir, canTitle) 
    
        plotName = plotDir + ibR + '_triggerSF.png'
        plotSFSingle( dataEff1b,  ttEff1b, plotName, canTitle)
   
def getEffHist(sumProcessPerVar, regionDe, regionNu, process, plotDir, canTitle):
    dataEff1b_de = sumProcessPerVar['jetsHTAnd6pt'][regionDe][process].Clone() 
    dataEff1b_nu = sumProcessPerVar['jetsHTAnd6pt'][regionNu][process].Clone() 
    # dataEff1b_de.Print()
    # dataEff1b_de.Print()
    dataEff1b = dataEff1b_de.Clone()
    # dataEff1b.Print()
    
    dataEff1b.Sumw2()
    dataEff1b.Divide(dataEff1b_nu)
    dataEff1b.SetName(dataEff1b.GetName()+'_eff')
    
        
    plot2D(dataEff1b, plotDir+dataEff1b.GetName()+'.png', canTitle, True)
    
    return dataEff1b
    
def plot2D(hist2D, plotName, canTitle, ifPlotEven=False):
    print('start plot 2D plot')
    can = ROOT.TCanvas('SF', 'SF', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    # ROOT.gStyle.SetOptTitle(0) #draw hist title
    ROOT.gStyle.SetPaintTextFormat(".2f")
    ROOT.gStyle.SetTitleSize(0.07, "X")#???not working
    ROOT.gStyle.SetTitleSize(0.07, "Y")
    # levels = [i*1 for i in range(30, 39)]
    # print('colors: ', levels)
    # print(int(ROOT.kRed)) 
    # palette = array.array('i', levels)
    # ROOT.gStyle.SetPalette(len(levels), palette)
    # ROOT.gStyle.SetPalette(ROOT.kCherry)
    # ROOT.gStyle.SetPalette(ROOT.kSunset)
    # ROOT.gStyle.SetPalette(ROOT.kGreenRedViolet)
    # ROOT.gStyle.SetPalette(ROOT.kSolar)
    # ROOT.gStyle.SetPalette(53)
    # ROOT.gStyle.SetPalette(55)
    # ROOT.gStyle.SetPalette(56)
    # ROOT.gStyle.SetPalette(57) #default
    # ROOT.gStyle.SetPalette(69)
    ROOT.gStyle.SetPalette(70)
    

    
    if ifPlotEven:
        xbin_edges = hist2D.GetXaxis().GetXbins() 
        ybin_edges = hist2D.GetYaxis().GetXbins() 
        for x in range(1, hist2D.GetNbinsX()+1):
            hist2D.GetXaxis().SetBinLabel(x, str(xbin_edges[x-1]) + '-'+ str(xbin_edges[x]) )
        for y in range(1, hist2D.GetNbinsY()+1):
            # hist2D.GetYaxis().SetBinLabel(y, str(xbin_edges[y-1]) + '-'+ str(xbin_edges[y])  )
            hist2D.GetYaxis().SetBinLabel(y, str(ybin_edges[y-1]) + '-'+ str(ybin_edges[y])  )
        hist2D_even = ROOT.TH2D(hist2D.GetName(), hist2D.GetTitle(), len(xbin_edges)-1, 0, len(xbin_edges)-1, len(ybin_edges)-1, 0, len(ybin_edges)-1) 
        for x in range(1, hist2D_even.GetNbinsX()+1):
            hist2D_even.GetXaxis().SetBinLabel(x, hist2D.GetXaxis().GetBinLabel(x)) 
            for y in range(1, hist2D_even.GetNbinsY()+1):
                hist2D_even.SetBinContent(x,y, hist2D.GetBinContent(x,y))
                hist2D_even.SetBinError(x,y, hist2D.GetBinError(x,y))
                if x==1:
                    hist2D_even.GetYaxis().SetBinLabel(y, hist2D.GetYaxis().GetBinLabel(y)) 
        hist2D_even.Print()
    
    if not ifPlotEven:
        histToDraw = hist2D
    else:
        histToDraw = hist2D_even
        
    histTitle = histToDraw.GetTitle() 
    xtitle = histToDraw.GetTitle().split(":")[0]
    ytitle = histToDraw.GetTitle().split(":")[1]
    histToDraw.GetXaxis().SetTitle(xtitle)
    histToDraw.GetYaxis().SetTitle(ytitle)
    histToDraw.GetYaxis().SetTitleSize(0.05)
    histToDraw.GetXaxis().SetTitleSize(0.05)
    histToDraw.GetXaxis().SetTitleOffset(1.0)
    histToDraw.GetXaxis().SetTickLength(0.02)
    # histToDraw.GetXaxis().SetLabelAngle(45)
    # histToDraw.GetXaxis().SetLabelSize(0.02)
    histToDraw.SetMinimum(0.65)
    histToDraw.SetMaximum(1.35)
    histToDraw.LabelsOption("v") 
    histToDraw.Draw("colzetext")
    histToDraw.SetTitle(canTitle)
    # histToDraw.SetContour(10)
    
    
     
    can.SetLeftMargin(0.20)
    can.SetRightMargin(0.15)
    can.SetBottomMargin(0.20) 
    # can.SetTopMargin(0.2) 
    # can.SetTitle(canTitle)
    can.Draw("g")
    can.SaveAs(plotName)
    hist2D.SetTitle(histTitle)
     
    
def plotSFSingle(de_2D, nu_2D, plotName, canTitle):
    de = de_2D.Clone()
    nu = nu_2D.Clone()
    de.Sumw2()
    nu.Sumw2()
    ratio = de.Clone()
    ratio.Divide(nu)
    ratioName = ratio.GetName().split('_')[0]+'_SF'
    ratio.SetName(ratioName)
    
    plot2D(ratio, plotName, canTitle, True)
    
    SFfileName = plotName.replace('.png', '.root')
    file = ROOT.TFile(SFfileName, 'recreate') 
    ratio.SetDirectory(file)
    ratio.Write()
    file.Write()
    file.Close()
    print('trigger SF file here: ', file.GetName())
    
    
    
def plotEfficiencyHLT(inputDirDic):
    variableList = ['jets_HT', 'bjetsM_num', 'jets_6pt', 'jets_number', 'jets_1pt']
    regionList = ['baseline1Muon', 'baseline1MuonAndHLT', 'baseline', 'baselineAndHLT']
    
    variableDic = {
        'jets_HT': np.array( [500., 550, 600, 650, 750, 850, 950, 1050, 1250, 1450, 1650, 1950, 2500] ),
        'bjetsM_num': np.array([-0.5, 0.5, 1.5, 2.5, 3.5, 5.5, 7.5]),
        'jets_6pt': np.array([25.0, 40, 55, 70, 85, 115, 145]),
        'jets_number': np.array([-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5,12.5]),
        'jets_1pt': np.array([25.0, 55,  85, 145, 175, 235, 295, 355, 415, 490, 625]),
    }
    # variableDic = {
    #     'bjetsM_num': np.array([-0.5, 0.5, 1.5, 2.5, 3.5, 5.5, 7.5]),
    # }
    
    # variableDic = {
    #     'jets_6pt': np.array([25.0, 40, 55, 70, 85, 115, 145])
    # }
    # variableDic = {
    #     'jets_number': np.array([-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5,12.5])
    # } 
    
    # variableDic = {
    #     'jets_1pt': np.array([25.0, 55,  85, 145, 175, 235, 295, 355, 415, 490, 625])
    # }
    
    
     
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableList:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(plotDir)   
    # eff_ttTruth = plotEffHLT(variableDic, 'baseline', 'baselineAndHLT', sumProcessPerVar, 'ttTruthEff', plotDir, 3)
    # eff_ttTruth = plotEffHLT('jets_number', variableDic['jets_number'], 'baseline', 'baselineAndHLT', sumProcessPerVar, 'ttTruthEff', plotDir, 3)
    for ivar in variableDic.keys():
        eff_ttTruth = plotEffHLT(ivar, variableDic[ivar], 'baseline', 'baselineAndHLT', sumProcessPerVar, 'ttTruthEff', plotDir, 3)
        eff_ttRef = plotEffHLT(ivar, variableDic[ivar], 'baseline1Muon', 'baseline1MuonAndHLT', sumProcessPerVar,  'ttRefEff', plotDir, 3)
        eff_dataRef = plotEffHLT(ivar, variableDic[ivar], 'baseline1Muon', 'baseline1MuonAndHLT', sumProcessPerVar, 'dataRefEff', plotDir, ifData=1)
        eff_tttt = plotEffHLT(ivar, variableDic[ivar], 'baseline', 'baselineAndHLT', sumProcessPerVar, 'ttttHLTEff', plotDir, 2)
    
        eff_ttRef.Print()
        overlayList = [eff_ttTruth, eff_ttRef, eff_dataRef]
        legendList = ['tt truth eff', 'tt reference eff', 'data reference eff']
        # variable = list(variableDic.keys())[0]
        overlayName = plotDir + 'HLTefficiencyOverlay_' + ivar  + '.png' 
        plotFROverlay(overlayList, legendList, era, 'HLT efficiency',  overlayName)
    
   
   
    
    


# def plotEffHLT(variableDic,  regionDe, regionNu, sumProcessPerVar, plotName, plotDir, ifData=0): 
def plotEffHLT(variable, binning,  regionDe, regionNu, sumProcessPerVar, plotName, plotDir, ifData=0): 
    if  ifData==0:
        print('plot for all bg')
        MCTrueth_de = uf.addBGHist(sumProcessPerVar[variable], regionDe, includeQCD=True)
        MCTrueth_nu = uf.addBGHist(sumProcessPerVar[variable], regionNu, includeQCD=True)
    elif ifData==1:
        print('plot for data')
        MCTrueth_de = sumProcessPerVar[variable][regionDe]['singleMu'].Clone()
        MCTrueth_nu = sumProcessPerVar[variable][regionNu]['singleMu'].Clone()
        MCTrueth_de.SetName(regionDe)
        MCTrueth_nu.SetName(regionNu)
    elif ifData==2:
        print('plot for tttt')
        MCTrueth_de = sumProcessPerVar[variable][regionDe]['tttt'].Clone()
        MCTrueth_nu = sumProcessPerVar[variable][regionNu]['tttt'].Clone()
        MCTrueth_de.SetName(regionDe)
        MCTrueth_nu.SetName(regionNu)
    elif ifData==3:
        print('plot for tt')
        MCTrueth_de = sumProcessPerVar[variable][regionDe]['tt'].Clone()
        MCTrueth_nu = sumProcessPerVar[variable][regionNu]['tt'].Clone()
        MCTrueth_de.SetName(regionDe)
        MCTrueth_nu.SetName(regionNu)
        
    if len( binning ) >0:
        binLowEges = binning
        MCTrueth_de = MCTrueth_de.Rebin(len(binLowEges)-1, '', binLowEges)
        MCTrueth_nu = MCTrueth_nu.Rebin(len(binLowEges)-1, '', binLowEges)
    MCTrueth_de.Print()
    MCTrueth_nu.Print()
    eff_MCTrueth = MCTrueth_de.Clone()
    eff_MCTrueth.Reset()
    eff_MCTrueth.Divide(MCTrueth_nu, MCTrueth_de)
    # eff_MCTrueth.SetName('eff_MCTrueth')
    eff_MCTrueth.SetName(plotName)
    # eff_MCTrueth.SetTitle('efficiency')
    eff_MCTrueth.Print()
    plotName = plotDir + variable + plotName + '.png'
    era = uf.getEraFromDir(plotDir)
    plotEfficiency(MCTrueth_nu, MCTrueth_de, eff_MCTrueth, plotName, era, False)
    return eff_MCTrueth

    
if __name__=='__main__':
    main()