
import ROOT
import usefulFunc as uf
from plotForFakeRate import plotEfficiency, plotFROverlay


def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v9addBtagWeight_v42fixedChargeType/mc/variableHists_v3forBTagR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2aadTopLepWeight_v49FixedPileUpJERAndTES/mc/variableHists_v6_btagRMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v0btagRCal/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3HLTWeightUpdated_v55ojectRemovalwithTightNoHLT/mc/variableHists_v8btagRMeasureWith1tau0l/'

    # plotNa
    era = uf.getEraFromDir(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    variable = 'jets_number'
    
    # plotBtagR(variable)
    
    plotBtagROverlay(variable, era, inputDirDic)
    
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
        
    
def plotBtagR(variable, inputDir):
    # regionList = ['baseline1Tau', 'baseline1TauBTagWeight']
    # regionList = ['1tau1lNoB', '1tau1lNoBBtagWeight']
    regionList = ['1tau0lNoB', '1tau0lNoBBtagWeight']
    
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
