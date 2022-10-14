import numpy as np
import ROOT
import usefulFunc as uf
from ttttGlobleQuantity import summedProcessList

from writeCSVforEY import getSummedHists


def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/'
    version = 'v4forFakeRate_eta0-06'
    inputDirDic ={
        # 'mc': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/mc/variableHists_v4forFakeRate/',
        # 'data': '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v1baseline_v38TESandJERTauPt20_preselection/data/variableHists_v4forFakeRate/'
        'mc': inputDir + 'mc/variableHists_' + version + '/',
        'data': inputDir + 'data/variableHists_' + version + '/'
    } 

    # variableList = ['tausL_1pt', 'tausL_1etaAbs']
    regionList = ["1tau0lCRGen", '1tau0lCR', '1tau0lCRLTauGen', "1tau0lCRLTau",  "1tau0lVRLTau"]
    variableList = ['tausL_1pt']
    sumProcessPerVar = {}
    #sumProcessPerVar[var][region][sumedProcess] = hist
    for ivar in variableList:
        sumProcessPerVar[ivar] = getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )

    plotVarDic = {
        # 'tausL_1pt': [20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 90.0, 110.0, 140.0, 220.0],
        'tausL_1pt': [20.0,  40.0,  60.0, 80.0, 100.0, 120.0, 140.0, 160.0, 180.0, 200.0, 220.0],
        # 'tausL_1eta': [ 0, 0.3, 0.6, 0.9, 1.2, 1.5, 1.8, 2.1, 2.4]
        }
    h_CR_dataSubBG, h_CRLTau_dataSubBG = getHistForFakeRate( list(plotVarDic.keys())[0], sumProcessPerVar)



    # binLowEges = np.array( [20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 90.0, 110.0, 140.0, 220.0])
    binLowEges = np.array( plotVarDic[list(plotVarDic.keys())[0]])
    h_CR_dataSubBG_rebin =  h_CR_dataSubBG.Rebin(len(binLowEges)-1, 'h_CR_dataSubBG_rebin', binLowEges  ) 
    h_CRLTau_dataSubBG_rebin = h_CRLTau_dataSubBG.Rebin(len(binLowEges)-1, 'CRLTau', binLowEges )

    h_fakeRateCR = h_CR_dataSubBG_rebin.Clone()
    h_fakeRateCR.Reset()
    h_fakeRateCR.Sumw2()
    h_fakeRateCR.Divide(h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin)

    plotDir = inputDirDic['mc'] + 'results/' 
    uf.checkMakeDir( plotDir )
    plotName = plotDir + list(plotVarDic.keys())[0] + '_FR.png'
    plotEfficiency( h_CR_dataSubBG_rebin, h_CRLTau_dataSubBG_rebin, h_fakeRateCR, plotName )






def getHistForFakeRate( var, sumProcessPerVar ):
    h_CR_data = sumProcessPerVar[var]['1tau0lCR']['data'] 
    h_CR_data.Print()
    h_CR_bgGenTau = addBGHist(sumProcessPerVar, var, '1tau0lCRGen')
    h_CR_bgGenTau.Print() 
    h_CR_dataSubBG = h_CR_data - h_CR_bgGenTau
    # h_CR_dataSubBG = h_CR_data.Add(h_CR_bgGenTau, -1).Clone()
    h_CR_dataSubBG.Print()

    h_CRLTau_data = sumProcessPerVar[var]['1tau0lCRLTau']['data'] 
    h_CRLTau_bgGenTau = addBGHist(sumProcessPerVar, var, '1tau0lCRLTauGen')
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
