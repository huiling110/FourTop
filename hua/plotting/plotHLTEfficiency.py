import numpy as np
import ROOT

import usefulFunc as uf

from plotForFakeRate import plotEfficiency 

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
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baslineNoHLTMuonTriggerAdded_v52noHLTButPreSelection/mc/variableHists_v8add2DHist/'
    
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(inputDir)
    
    plotEfficiencyHLT(inputDirDic)
    
    #plotSF
    # plotSF(inputDirDic)
    
    
    #overlay of MC truth efficiency, MC reference efficiency and data reference efficiency
   
def plotSF(inputDirDic):
    # file = ROOT.TFile(inputDir+'tt') 
    # tt_1b = 
    variableList = ['jetsHTAnd6pt']
    regionList = ['baseline1Muon1b', 'baseline1MuonAndHLT1b', ]
    
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableList:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
   
    dataEff1b = getEffHist(sumProcessPerVar, 'baseline1Muon1b', 'baseline1MuonAndHLT1b', 'singleMu', plotDir) 
    ttEff1b = getEffHist(sumProcessPerVar, 'baseline1Muon1b', 'baseline1MuonAndHLT1b', 'tt', plotDir) 
   
    plotName = plotDir + 'HLTSF_1b.png'
    # plotSFSingle( ttEff1b, dataEff1b, plotName)
   
def getEffHist(sumProcessPerVar, regionDe, regionNu, process, plotDir):
    dataEff1b_de = sumProcessPerVar['jetsHTAnd6pt'][regionDe][process].Clone() 
    dataEff1b_nu = sumProcessPerVar['jetsHTAnd6pt'][regionNu][process].Clone() 
    # dataEff1b_de.Print()
    # dataEff1b_de.Print()
    dataEff1b = dataEff1b_de.Clone()
    # dataEff1b.Print()
    
    dataEff1b.Sumw2()
    dataEff1b.Divide(dataEff1b_nu)
    dataEff1b.SetName(dataEff1b.GetName()+'_eff')
        
    plot2D(dataEff1b, plotDir+dataEff1b.GetName()+'.png')
    
    return dataEff1b
    
def plot2D(hist2D, plotName):
    can = ROOT.TCanvas('SF', 'SF', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)
    ROOT.gStyle.SetPaintTextFormat(".2f")
    ROOT.gStyle.SetTitleSize(0.07, "X")#???not working
    ROOT.gStyle.SetTitleSize(0.07, "Y")
   
    xtitle = hist2D.GetTitle().split(":")[0]
    ytitle = hist2D.GetTitle().split(":")[1]
    hist2D.GetXaxis().SetTitle(xtitle)
    hist2D.GetYaxis().SetTitle(ytitle)
    hist2D.GetYaxis().SetTitleSize(0.05)
    hist2D.GetXaxis().SetTitleSize(0.05)
    hist2D.LabelsOption("v") 
    # hist2D.SetMarkerSize(0.01)
    hist2D.Draw("colzetext")
     
    can.SetLeftMargin(0.15)
    can.SetBottomMargin(0.15) 
    can.Draw()
    can.SaveAs(plotName)
     
    
def plotSFSingle(de_2D, nu_2D, plotName):
    de = de_2D.Clone()
    nu = nu_2D.Clone()
    de.Sumw2()
    nu.Sumw2()
    ratio = de.Clone()
    ratio.Divide(nu)
    
    can = ROOT.TCanvas('SF', 'SF', 1000, 800)
    # ratio.Draw("colz")
    ratio.Draw("colztext")
    can.Draw() 
    can.SaveAs(plotName)
    
    
    
    
def plotEfficiencyHLT(inputDirDic):
    variableList = ['jets_HT', 'bjetsM_num', 'jets_6pt', 'jets_number', 'jets_1pt']
    regionList = ['baseline1Muon', 'baseline1MuonAndHLT', 'baseline', 'baselineAndHLT']
    
    # variableDic = {
    #     'jets_HT': np.array( [500., 550, 600, 650, 750, 850, 950, 1050, 1250, 1450, 1650, 1950, 2500] ),
    # }
    # variableDic = {
    #     'bjetsM_num': np.array([-0.5, 0.5, 1.5, 2.5, 3.5, 5.5, 7.5]),
    # }
    
    # variableDic = {
    #     'jets_6pt': np.array([25.0, 40, 55, 70, 85, 115, 145])
    # }
    # variableDic = {
    #     'jets_number': np.array([-0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5, 6.5, 7.5, 8.5, 9.5,12.5])
    # } 
    
    variableDic = {
        'jets_1pt': np.array([25.0, 55,  85, 145, 175, 235, 295, 355, 415, 490, 625])
    }
    
    
     
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableList:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    plotEffHLT(variableDic, 'baseline', 'baselineAndHLT', sumProcessPerVar, 'MCTruthEff', plotDir)
    plotEffHLT(variableDic, 'baseline', 'baselineAndHLT', sumProcessPerVar, 'ttTruthEff', plotDir, 3)
    plotEffHLT(variableDic, 'baseline1Muon', 'baseline1MuonAndHLT', sumProcessPerVar,  'MCRefEff', plotDir)
    plotEffHLT(variableDic, 'baseline1Muon', 'baseline1MuonAndHLT', sumProcessPerVar,  'ttRefEff', plotDir, 3)
    plotEffHLT(variableDic, 'baseline1Muon', 'baseline1MuonAndHLT', sumProcessPerVar, 'dataRefEff', plotDir, ifData=1)
    plotEffHLT(variableDic, 'baseline', 'baselineAndHLT', sumProcessPerVar, 'ttttHLTEff', plotDir, 2)

    
   
   
    
    


def plotEffHLT(variableDic,  regionDe, regionNu, sumProcessPerVar, plotName, plotDir, ifData=0): 
    if  ifData==0:
        print('plot for all bg')
        MCTrueth_de = uf.addBGHist(sumProcessPerVar[list(variableDic.keys())[0]], regionDe, includeQCD=True)
        MCTrueth_nu = uf.addBGHist(sumProcessPerVar[list(variableDic.keys())[0]], regionNu, includeQCD=True)
    elif ifData==1:
        print('plot for data')
        MCTrueth_de = sumProcessPerVar[list(variableDic.keys())[0]][regionDe]['singleMu'].Clone()
        MCTrueth_nu = sumProcessPerVar[list(variableDic.keys())[0]][regionNu]['singleMu'].Clone()
        MCTrueth_de.SetName(regionDe)
        MCTrueth_nu.SetName(regionNu)
    elif ifData==2:
        print('plot for tttt')
        MCTrueth_de = sumProcessPerVar[list(variableDic.keys())[0]][regionDe]['tttt'].Clone()
        MCTrueth_nu = sumProcessPerVar[list(variableDic.keys())[0]][regionNu]['tttt'].Clone()
        MCTrueth_de.SetName(regionDe)
        MCTrueth_nu.SetName(regionNu)
    elif ifData==3:
        print('plot for tt')
        MCTrueth_de = sumProcessPerVar[list(variableDic.keys())[0]][regionDe]['tt'].Clone()
        MCTrueth_nu = sumProcessPerVar[list(variableDic.keys())[0]][regionNu]['tt'].Clone()
        MCTrueth_de.SetName(regionDe)
        MCTrueth_nu.SetName(regionNu)
        
    if len( variableDic[list(variableDic.keys())[0]] ) >0:
        binLowEges = variableDic[list(variableDic.keys())[0]]
        MCTrueth_de = MCTrueth_de.Rebin(len(binLowEges)-1, '', binLowEges)
        MCTrueth_nu = MCTrueth_nu.Rebin(len(binLowEges)-1, '', binLowEges)
    MCTrueth_de.Print()
    MCTrueth_nu.Print()
    eff_MCTrueth = MCTrueth_de.Clone()
    eff_MCTrueth.Reset()
    eff_MCTrueth.Divide(MCTrueth_nu, MCTrueth_de)
    # eff_MCTrueth.SetName('eff_MCTrueth')
    eff_MCTrueth.SetName(plotName)
    eff_MCTrueth.SetTitle('efficiency')
    eff_MCTrueth.Print()
    plotName = plotDir + list(variableDic.keys())[0] + plotName + '.png'
    era = uf.getEraFromDir(plotDir)
    plotEfficiency(MCTrueth_nu, MCTrueth_de, eff_MCTrueth, plotName, era, False)

    
if __name__=='__main__':
    main()