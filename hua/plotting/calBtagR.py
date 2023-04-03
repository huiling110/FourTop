
import ROOT
import usefulFunc as uf
from plotForFakeRate import plotEfficiency


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v9addBtagWeight_v42fixedChargeType/mc/variableHists_v3forBTagR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/variableHists_v6_btagRMeasure/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/'

    # plotNa
    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    variable = 'jets_number'
    # regionList = ['baseline1Tau', 'baseline1TauBTagWeight']
    regionList = ['1tau1lNoB', '1tau1lNoBBtagWeight']
    
    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    sumProcessPerVar[variable], sumProcessPerVarSys[variable] = uf.getSummedHists( inputDirDic, regionList, variable )       
    print( sumProcessPerVar )
    
    h_de = sumProcessPerVar[variable]['1tau1lNoBBtagWeight']['tt'].Clone()
    h_nu = sumProcessPerVar[variable]['1tau1lNoB']['tt'].Clone()
    h_eff = h_de.Clone()
    h_eff.Reset()
    h_eff.Divide(h_nu, h_de)
    h_eff.Print()
    
   
   
    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir(plotDir)
    plotName = plotDir + 'bTagR.png' 
    plotEfficiency(h_nu, h_de, h_eff, plotName, era, False)
    
    # print(h_eff.GetBinContent(1))
    # print(h_eff.GetBinContent(2))
    # print(h_eff.GetBinContent(3))
    # print(h_eff.GetBinContent(4))
    # print(h_eff.GetBinContent(5))
    # print(h_eff.GetBinContent(6))
    
    
    # outFileName = plotDir + 'btagR.root' 
    # outFile = ROOT.TFile( outFileName, "RECREATE") 
    # h_eff.SetDirectory(outFile)
    # h_eff.Write() 
    # outFile.Close()
    # print('btagR file writen here: ', outFileName)

    
    
    
    
if __name__ == "__main__":
    main()
