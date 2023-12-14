import numpy as np
import array
import ROOT
 
import ttttGlobleQuantity as gq 
import usefulFunc as uf

# from plotForFakeRate import plotEfficiency, plotFROverlay

import plotBtagEff as pB

def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLTBugFixed_v56NoHLTButPre/mc/variableHists_v0_triggerSFNewRange/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v2baslineNoHLT_v57ovelapWithTausF/mc/variableHists_v3btagEffNewRegion/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet45/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40Mu35/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet45_binningB/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600BinA/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600BinB/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT600BinE/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinE/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/'
    
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(inputDir)
    
    #overlay of MC truth efficiency, MC reference efficiency and data reference efficiency
    # plotEfficiencyHLT(inputDirDic)
    plotEfficiencyHLT(inputDirDic, '1b')
    # plotEfficiencyHLT(inputDirDic, '2b')
    # plotEfficiencyHLT(inputDirDic, '3b')
    
    #plotSF
    # plotSF(inputDirDic, True)
    
    
   
def plotSF(inputDirDic, ifOnlyDraw=False):
    variableList = ['jetsHTAnd6pt']
    regionList = ['baseline1Muon1b', 'baseline1MuonAndHLT1b', 'baseline1Muon2b', 'baseline1MuonAndHLT2b','baseline1Muon3b', 'baseline1MuonAndHLT3b' ]
    
    # sumProcessPerVar = {}
    # sumProcessPerVarSys = {} 
    # for ivar in variableList:
    #     sumProcessPerVar[ivar], sumProcessPerVarSys[ivar]= uf.getSummedHists( inputDirDic, regionList, ivar )
    # print( sumProcessPerVar )
    sumProList = ['tt', 'singleMu']
    era = uf.getEraFromDir(inputDirDic['mc'])
    sumProcessPerVar = uf.getSumHist(inputDirDic, regionList, sumProList, variableList, era)
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
  
    bRegions = ['baseline1Muon1b', 'baseline1Muon2b', 'baseline1Muon3b']
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
    
        # plotName = plotDir + ibR + '_triggerSF.png'
        plotName = plotDir + ibR + '_triggerSF_new'
        plotSFSingle( dataEff1b,  ttEff1b, plotName, canTitle, ifOnlyDraw)
   
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
    
        
    pB.plot2D(dataEff1b, plotDir+dataEff1b.GetName()+'.png', canTitle, True, [0.65, 1.35])
    
    return dataEff1b
    
     
    
def plotSFSingle(de_2D, nu_2D, plotName, canTitle, ifOnlyDraw=False):
    de = de_2D.Clone()
    nu = nu_2D.Clone()
    de.Sumw2()
    nu.Sumw2()
    ratio = de.Clone()
    ratio.Divide(nu)
    ratioName = ratio.GetName().split('_')[0]+'_SF'
    ratio.SetName(ratioName)
    
    
    pB.plot2D(ratio, plotName, canTitle, True, [0.65, 1.35])
    
    # SFfileName = plotName.replace('.png', '.root')
    SFfileName = plotName + '.root'
    if not ifOnlyDraw:
        pB.saveHistToFile(ratio, SFfileName)
    
    
    
def plotEfficiencyHLT(inputDirDic, bjet = ''):
    regionList = ['baseline1Muon', 'baseline1MuonAndHLT', 'baseline', 'baselineAndHLT']
    for i in range(len(regionList)):
        regionList[i] = regionList[i]+bjet
    
    variableDic = {
        # 'jets_HT': np.array( [500., 550, 600, 650, 750, 850, 950, 1050, 1250, 1450, 1650, 1950, 2500] ),
        # 'bjetsM_num': np.array([ 0.5, 1.5, 2.5, 3.5, 5.5, 7.5]),
        # 'jets_6pt': np.array([40., 55., 70., 85., 115, 150]),
        'jets_num': np.array([ 5.5, 6.5, 7.5, 8.5, 9.5,12.5]),
        # 'jets_1pt': np.array([25., 55,  85, 145, 175, 235, 295, 355, 415, 490, 625]),
    }
    
    varList = list(variableDic.keys())     
    sumList = ['singleMu', 'tt', 'tttt']
    era = uf.getEraFromDir(inputDirDic['mc'])   
    sumProcessPerVar = uf.getSumHist(inputDirDic, regionList, sumList, varList, era )#sumProcessPerVar[ivar][region][sumPro]
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    
    for ivar in variableDic.keys():
        eff_ttTruth = plotEffHLT(ivar, variableDic[ivar], 'baseline'+bjet, 'baselineAndHLT'+bjet, sumProcessPerVar, 'ttTrueEff', 'tt', plotDir, 3)
        eff_ttRef = plotEffHLT(ivar, variableDic[ivar], 'baseline1Muon'+bjet, 'baseline1MuonAndHLT'+bjet, sumProcessPerVar,  'ttOrthEff', 'tt', plotDir, 3)
        eff_dataRef = plotEffHLT(ivar, variableDic[ivar], 'baseline1Muon'+bjet, 'baseline1MuonAndHLT'+bjet, sumProcessPerVar, 'dataOrthEff', 'data', plotDir, ifData=1)
        eff_tttt = plotEffHLT(ivar, variableDic[ivar], 'baseline'+bjet, 'baselineAndHLT'+bjet, sumProcessPerVar, 'ttttTrueEff', 'tttt',plotDir, 2)
    
        overlayList = [eff_ttTruth, eff_ttRef, eff_dataRef]
        legendList = ['tt: true efficiency', 'tt: orthogonal efficiency', 'data: orthogonal efficiency']
        overlayName = plotDir + 'HLTefficiencyOverlay_' + ivar  + bjet+'New2.png' 
        # pB.plotOverlay(overlayList, legendList, era, 'HLT efficiency',  overlayName, [0.5, 0.2, 0.9, 0.4],  [0, 1.2])
        uf.plotOverlay(overlayList, legendList, era, 'HLT efficiency',  overlayName, [0.5, 0.2, 0.9, 0.4],  [0, 1.2])
    
  
   
def group_third_layer(dictionary, grouping_dict): ##!!!seems not working
    #dictionary[ivar][ire][subPro] 
    grouped_dict = {}
    for key, value in dictionary.items(): #(1var:dic[ire])->(1re:dic[isub])->(1sub:hist)
        if isinstance(value, dict): #if value is a dictionary, can go into second layer
            #first layer: put dic[re] back into funtion->dic[subPro]->(sub:hist)=grouped_dict[sub]->Return to call from fist layer here
            grouped_subdict = group_third_layer(value, grouping_dict)
            if key in grouped_dict:
                grouped_dict[key].update(grouped_subdict)
            else:
                grouped_dict[key] = grouped_subdict
        else: #in the last layer, subPro: hist
            if key in grouping_dict:
                group_key = grouping_dict[key]
                if group_key not in grouped_dict:
                    grouped_dict[group_key] = {}
                if key in grouped_dict[group_key]:
                    grouped_dict[group_key][key].append(value)
                else:
                    grouped_dict[group_key][key] = [value]
            else:
                if key in grouped_dict:
                    grouped_dict[key].append(value)
                else:
                    grouped_dict[key] = [value]
    return grouped_dict   
    
# def sumSubPro(subHists):
#     sumHists = {}
#     for ivar in subHists.keys():
#         # sumHists[ivar]={}
#         for ire in subHists[ivar].keys():
#             # sumHist
#             for isubPro in subHists[ivar][ire].keys():
                
                
#     return sumHists
                                
        
    
       
       
    
    


def plotEffHLT(variable, binning,  regionDe, regionNu, sumProcessPerVar, plotName, legendName, plotDir, ifData=0): 
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
    eff_MCTrueth = MCTrueth_de.Clone()
    eff_MCTrueth.Reset()
    eff_MCTrueth.Divide(MCTrueth_nu, MCTrueth_de)
    eff_MCTrueth.SetName(plotName)
    
    plotName = plotDir + variable + plotName + '_testing2'
    era = uf.getEraFromDir(plotDir)
    # uf.plotEffTEff(MCTrueth_nu, MCTrueth_de, plotName, era)
    
    eff = uf.plotEffTEff(MCTrueth_nu, MCTrueth_de, plotName, era, legendName) 
    
    
    # return eff_MCTrueth
    return eff

    
if __name__=='__main__':
    main()