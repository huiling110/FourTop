
import plotForFakeRate as fr
import ROOT
import usefulFunc as uf
from writeCSVforEY import addBGHist, getSummedHists


def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v9addBtagWeight_v42fixedChargeType/mc/variableHists_v3forBTagR/'

    # plotNa
    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    variable = 'jets_number'
    regionList = ['baseline1Tau', 'baseline1TauBTagWeight']
    
    #sumProcessPerVar[var][region][sumedProcess] = hist
    sumProcessPerVar = {}
    sumProcessPerVarSys = {}
    sumProcessPerVar[variable], sumProcessPerVarSys[variable] = getSummedHists( inputDirDic, regionList, variable )       
    print( sumProcessPerVar )
    
    h_before = addBGHist(sumProcessPerVar[variable], variable, 'baseline1Tau', True) 
    h_after = addBGHist(sumProcessPerVar[variable], variable, 'baseline1TauBTagWeight', True) 
    h_eff = h_before.Clone()
    h_eff.Reset()
    h_eff.Sumw2()
    h_eff.Divide(h_before, h_after)
    h_eff.SetName("btagR")
    # h_eff.Divide(h_after, h_before)
   
   
    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir(plotDir)
    plotName = plotDir + 'bTagR.png' 
    fr.plotEfficiency(h_before, h_after, h_eff, plotName, era)
    
    print(h_eff.GetBinContent(1))
    print(h_eff.GetBinContent(2))
    print(h_eff.GetBinContent(3))
    print(h_eff.GetBinContent(4))
    print(h_eff.GetBinContent(5))
    print(h_eff.GetBinContent(6))
    
    
    outFileName = plotDir + 'btagR.root' 
    outFile = ROOT.TFile( outFileName, "RECREATE") 
    h_eff.SetDirectory(outFile)
    h_eff.Write() 
    # outFile.Write()
    outFile.Close()
    print('btagR file writen here: ', outFileName)

    
    
    
    
if __name__ == "__main__":
    main()
