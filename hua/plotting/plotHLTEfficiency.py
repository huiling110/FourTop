import numpy as np

import usefulFunc as uf

from plotForFakeRate import plotEfficiency 

def main():
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v2baslineNoHLT_v52noHLTButPreSelection/mc/variableHists_v0triggerEff/'
    variableList = ['jets_HT']
    regionList = ['baseline1Muon', 'baseline1MuonAndHLT', 'baseline', 'baselineAndHLT']
    
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(inputDir)
     
    sumProcessPerVar = {}
    sumProcessPerVarSys = {} 
    for ivar in variableList:
        sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    print( sumProcessPerVar )
    
    #MC truth efficiency
    ptBins = np.array( [500., 550, 600, 650, 750, 850, 950, 1050, 1250, 1450, 1650, 1950, 2250, 2500] )
    variableDic = {
        'jets_HT': ptBins,
    }
    plotName = plotDir + 'MCTruthEffwithQCD.png'
    plotEffHLT(variableDic, 'baseline', 'baselineAndHLT', sumProcessPerVar, plotName)
    
     
    
    #MC reference efficiency
    
    
    #overlay of MC truth efficiency, MC reference efficiency and data reference efficiency


def plotEffHLT(variableDic,  regionDe, regionNu, sumProcessPerVar, plotName): 
    MCTrueth_de = uf.addBGHist(sumProcessPerVar[list(variableDic.keys())[0]], list(variableDic.keys())[0], 'baseline', includeQCD=True)
    MCTrueth_nu = uf.addBGHist(sumProcessPerVar[list(variableDic.keys())[0]], list(variableDic.keys())[0], 'baselineAndHLT', includeQCD=True)
    binLowEges = variableDic[list(variableDic.keys())[0]]
    MCTrueth_de = MCTrueth_de.Rebin(len(binLowEges)-1, '', binLowEges)
    MCTrueth_nu = MCTrueth_nu.Rebin(len(binLowEges)-1, '', binLowEges)
    eff_MCTrueth = MCTrueth_de.Clone()
    eff_MCTrueth.Reset()
    eff_MCTrueth.Divide(MCTrueth_nu, MCTrueth_de)
    eff_MCTrueth.SetName('eff_MCTrueth')
    eff_MCTrueth.SetTitle('efficiency')
    eff_MCTrueth.Print()
    plotEfficiency(MCTrueth_nu, MCTrueth_de, eff_MCTrueth, plotName, '2016postVFP', False)

    
if __name__=='__main__':
    main()