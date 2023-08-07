
import ROOT
import usefulFunc as uf
from plotForFakeRate import plotEfficiency, plotFROverlay

import plotBtagEff as pb
import setTDRStyle as st

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v9addBtagWeight_v42fixedChargeType/mc/variableHists_v3forBTagR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/variableHists_v6_btagRMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v8btagRMeasureWith1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3HLTWeightUpdatedBugFixed_v56NoHLTButPre/mc/variableHists_v6_btagRMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineNoBCutHLTWeightUpdated_v57ovelapWithTausF/mc/variableHists_v1_btagRMeasure/'
    
    # inputFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5newBtagEff_v60fixeJetBtagBug/mc/variableHists_v6forBtagRMeasure/ttbar_0l.root'
    inputFile = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v1btagRCal/ttbar_0l.root'

    era = uf.getEraFromDir(inputFile)
    jets_numList = pb.getHistFromFile(inputFile, ['jets_num_de', 'jets_num_nu'])
    print(jets_numList)
    
    btagR = pb.getEff(jets_numList[1], jets_numList[0]) #de before, nu: after; before/after
    btagR.SetName('btagR')
    
    
    inputDir = inputFile.rsplit('/',1)[0]
    plotDir = inputDir+'/results/'
    uf.checkMakeDir(plotDir)
    plotName = plotDir+'bShapeR.png'
    plotEff(jets_numList[1], jets_numList[0], btagR, ['before btag SF', 'after btag SF', 'b tag r'], plotName, era, False, 'B tag shape R')
    
    outFile = plotDir+'bShapeR.root'
    pb.saveHistToFile(btagR, outFile )
    
    
    # plotNa
    # era = uf.getEraFromDir(inputDir)
    # inputDirDic = uf.getInputDicNew( inputDir)
    # variable = 'jets_number'
    
    # plotBtagR(variable, inputDirDic,era)
    
    # plotBtagROverlay(variable, era, inputDirDic)
    
 #more generic than that of plotForFakeRate   
def plotEff(h_numeritor, h_dinominator, h_eff, legendL, plotName, era = '2016', ifFixMax=True, rightTitle='efficiency'):
    myStyle = st.setMyStyle()
    myStyle.SetPadRightMargin(0.12)
    myStyle.SetPadLeftMargin(0.12)
    myStyle.SetPadTopMargin(0.12)
    myStyle.cd()
    can = ROOT.TCanvas('efficiency', 'efficiency', 1000, 800)
    ROOT.gStyle.SetOptStat(ROOT.kFALSE)
    ROOT.gStyle.SetOptTitle(0)

    h_dinominator.GetYaxis().SetRangeUser(h_numeritor.GetMinimum()*0.9, h_dinominator.GetMaximum()*1.5)
    h_dinominator.GetYaxis().SetTitle('Events')
    h_dinominator.GetYaxis().SetTitleSize(0.05)
    h_dinominator.GetYaxis().SetLabelSize(0.03)
    h_dinominator.GetYaxis().SetTitleOffset(1.1)
    h_dinominator.GetXaxis().SetTitle(h_dinominator.GetTitle())
    h_dinominator.GetXaxis().SetTitleSize(0.05)
    h_dinominator.SetLineWidth(3)
    h_dinominator.SetLineColorAlpha(ROOT.kOrange+1, 0.8)
    
    h_dinominator.Draw()
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


    legend = ROOT.TLegend(0.5,0.68,0.88,0.88)
    # legend.AddEntry(h_dinominator, "denominator: "+ h_dinominator.GetName())
    # legend.AddEntry(h_numeritor, "numeritor: "+ h_numeritor.GetName())
    # legend.AddEntry(h_efficiency, h_efficiency.GetName())
    legend.AddEntry(h_dinominator, legendL[0])
    legend.AddEntry(h_numeritor, legendL[1])
    legend.AddEntry(h_efficiency, legendL[2])
    legend.Draw()
    
    st.addCMSTextToCan(can, 0.23, 0.41, 0.88 ,0.89, era)     

    can.SaveAs(plotName)
        
    
    
def plotBtagROverlay(variable, era, inputDirDic):
    regionList = ['1tau1lNoB', '1tau1lNoBBtagWeight', '1tau0lNoB', '1tau0lNoBBtagWeight']
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    sumProcessPerVar[variable], sumProcessPerVarSys[variable] = uf.getSummedHists( inputDirDic, regionList, variable )       
    print( sumProcessPerVar )
   
    r1 = getRatio( sumProcessPerVar, variable, regionList[1], regionList[0]) 
    r2 = getRatio( sumProcessPerVar, variable, regionList[3], regionList[2]) 
    Rlist = [r1, r2]
    plotName = inputDirDic['mc']+ 'results/'+ 'ROverLay.png'
    plotFROverlay(Rlist, ['1tau1lNoB', '1tau0lNoB'], era, 'btag R', plotName)


def getRatio( sumProcessPerVar, variable, deRegion, nuRegion, name='btagR'):
    h_de = sumProcessPerVar[variable][deRegion]['tt'].Clone()
    h_nu = sumProcessPerVar[variable][nuRegion]['tt'].Clone()
    h_de.SetName(deRegion)
    h_nu.SetName(nuRegion)
    h_eff = h_de.Clone()
    h_eff.Reset()
    h_eff.Divide(h_nu, h_de)
    h_eff.SetName(name)
    h_eff.Print()
    return h_eff
        
    
def plotBtagR(variable, inputDirDic,era):
    # regionList = ['baseline1Tau', 'baseline1TauBTagWeight']
    # regionList = ['1tau1lNoB', '1tau1lNoBBtagWeight']
    # regionList = ['1tau0lNoB', '1tau0lNoBBtagWeight']
    regionList = ['1tauNoB', '1tauNoBTagWeight']
    
    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    sumProcessPerVar[variable], sumProcessPerVarSys[variable] = uf.getSummedHists( inputDirDic, regionList, variable )       
    print( sumProcessPerVar )
    
    # h_de = sumProcessPerVar[variable]['1tau1lNoBBtagWeight']['tt'].Clone()
    # h_nu = sumProcessPerVar[variable]['1tau1lNoB']['tt'].Clone()
    h_de = sumProcessPerVar[variable][regionList[1]]['tt'].Clone()
    h_nu = sumProcessPerVar[variable][regionList[0]]['tt'].Clone()
    h_de.SetName(regionList[1])
    h_nu.SetName(regionList[0])
    h_eff = h_de.Clone()
    h_eff.Reset()
    h_eff.Divide(h_nu, h_de)
    h_eff.SetName('btagR')
    h_eff.Print()
    
   
   
    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir(plotDir)
    plotName = plotDir + regionList[0] +'bTagR.png' 
    plotEfficiency(h_nu, h_de, h_eff, plotName, era, False, 'b tag R')
    
    
    
    outFileName = plotDir + regionList[0]+'btagR.root' 
    outFile = ROOT.TFile( outFileName, "RECREATE") 
    h_eff.SetDirectory(outFile)
    h_eff.Write() 
    outFile.Close()
    print('btagR file writen here: ', outFileName)

    
    
    
    
if __name__ == "__main__":
    main()
