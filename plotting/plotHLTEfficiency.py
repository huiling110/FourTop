import numpy as np
import array
import ROOT
 
import ttttGlobleQuantity as gq 
import usefulFunc as uf


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
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64noHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3NotHLTPre/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3NotHLTPre/mc/variableHists_v0_HLTSFMeasureAddNoMu/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v73NoHLTTauFHT400/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v73NoHLTTauFHT400/mc/variableHists_v0_HLTSFMeasure/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineBtagUpdated_V75NoHLTNoTauBjet2Jet6/mc/variableHists_v0HLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineBtagUpdatedHT350_v75NoHLTTauFHT300Bjet2Jet5/mc/variableHists_v0HLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v0HLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v0HLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v1HLT_6thjetPt34/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v4HLT_4bDifBinningDifB/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450Jet6pt32_v75NoHLTNoTauHT400Jet6pt30/mc/variableHists_v4HLT_4bDifBinningDifBBinC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v77ForHLT/mc/variableHists_v0HLT_HT480Jet6pt37/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v77ForHLT/mc/variableHists_v1HLT_varyingCutOnBjetBinD/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v77ForHLT/mc/variableHists_v0HLTMeasure/'
   
    
    isRun3 = uf.isRun3(inputDir)
    inputDirDic = uf.getDirDic(inputDir)
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    era = uf.getEraFromDir(inputDir)
    
    #overlay of MC truth efficiency, MC reference efficiency and data reference efficiency
    # plotEfficiencyHLT(inputDirDic, '', isRun3)
    # plotEfficiencyHLT(inputDirDic, '2b', isRun3)
    # plotEfficiencyHLT(inputDirDic, '3b', isRun3)
    plotEfficiencyHLT(inputDirDic, '4b', isRun3)
    
    #plotSF
    # plotSF(inputDirDic, False, isRun3)
    
    
   
def plotSF(inputDirDic, ifOnlyDraw=False, isRun3=False):
    variableList = ['jetsHTAnd6pt']
    # regionList = ['baseline1Muon1b', 'baseline1MuonAndHLT1b', 'baseline1Muon2b', 'baseline1MuonAndHLT2b','baseline1Muon3b', 'baseline1MuonAndHLT3b', 'baseline1b', 'baselineAndHLT1b', 'baseline2b', 'baselineAndHLT2b', 'baseline3b', 'baselineAndHLT3b' ]
    # regionList = ['baseline1Muon1b', 'baseline1MuonAndHLT1b', 'baseline1Muon2b', 'baseline1MuonAndHLT2b','baseline1Muon3b', 'baseline1MuonAndHLT3b' ]#!1b=4b
    regionList = ['baseline1Muon4b', 'baseline1MuonAndHLT4b', 'baseline1Muon2b', 'baseline1MuonAndHLT2b','baseline1Muon3b', 'baseline1MuonAndHLT3b' ]#!1b=4b
    # regionList = [ 'baseline1Muon2b', 'baseline1MuonAndHLT2b','baseline1Muon3b', 'baseline1MuonAndHLT3b' ]
    
    if not isRun3:
        sumProList = ['tt', 'singleMu']
    else:
        sumProList = ['TT', 'singleMu']
    
    era = uf.getEraFromDir(inputDirDic['mc'])
    sumProcessPerVar = uf.getSumHist(inputDirDic, regionList, sumProList, variableList, era, isRun3)
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
  
    bRegions = ['baseline1Muon4b', 'baseline1Muon2b', 'baseline1Muon3b']
    # bRegions = [ 'baseline1Muon2b', 'baseline1Muon3b']
    regionTitleDic = {
        'baseline1Muon4b': 'b jets number > 3',
        'baseline1Muon2b': 'b jets number = 2',
        # 'baseline1Muon3b': '2 < b jets number < 8',
        'baseline1Muon3b': 'b jets number = 3',
    }
    
    for ibR in bRegions:
        bRegions_nu = ibR.replace('1Muon', '1MuonAndHLT')
        # bRegion_nu_MC = ibR.replace('1Muon', 'AndHLT')
        # bRegion_de_MC = ibR.replace('1Muon', '')
        print('regions: ', ibR, bRegions_nu)
        canTitle = regionTitleDic[ibR] 
        dataEff1b = getEffHist(sumProcessPerVar,  bRegions_nu, ibR, 'singleMu', plotDir, canTitle ) 
        ttEff1b = getEffHist(sumProcessPerVar, bRegions_nu, ibR, 'tt', plotDir, canTitle) 
        # ttEff1b_true = getEffHist(sumProcessPerVar, bRegion_nu_MC, bRegion_de_MC, 'tt', plotDir, canTitle) #!MC true
    
        plotName = plotDir + ibR + '_triggerSF_v0'
        plotSFSingle( dataEff1b,  ttEff1b, plotName, canTitle, ifOnlyDraw)
   
def getEffHist(sumProcessPerVar, regionDe, regionNu, process, plotDir, canTitle):
    dataEff1b_de = sumProcessPerVar['jetsHTAnd6pt'][regionDe][process].Clone() 
    dataEff1b_nu = sumProcessPerVar['jetsHTAnd6pt'][regionNu][process].Clone() 
    dataEff1b = dataEff1b_de.Clone()
    
    dataEff1b.Sumw2()
    dataEff1b.Divide(dataEff1b_nu)
    # dataEff1b.SetName(dataEff1b.GetName()+'_effMCtrue')
    dataEff1b.SetName(dataEff1b.GetName()+'_eff')
        
    # pB.plot2D(dataEff1b, plotDir+dataEff1b.GetName(), canTitle, True, [0.65, 1.35])
    pB.plot2D(dataEff1b, plotDir+dataEff1b.GetName(), canTitle, True, [0.3, 1.0])
    
    return dataEff1b
    
     
    
def plotSFSingle(de_2D, nu_2D, plotName, canTitle, ifOnlyDraw=False):
    de = de_2D.Clone()
    nu = nu_2D.Clone()
    de.Sumw2()
    nu.Sumw2()
    ratio = de.Clone()
    ratio.Divide(nu)
    ratioName = 'singleMu_SF'
    ratio.SetName(ratioName)
    # pB.plot2D(ratio, plotName, canTitle, True, [0.65, 1.35])
    pB.plot2D(ratio, plotName, canTitle, True, [0.5, 1.35])
    
    SFfileName = plotName + '.root'
    if not ifOnlyDraw:
        pB.saveHistToFile(ratio, SFfileName)
    
    
    
def plotEfficiencyHLT(inputDirDic, bjet = '', isRun3 = False):
    # regionList = ['baseline1Muon', 'baseline1Muon_HLT', 'baseline', 'baseline_HLT']
    # regionList = [f"baseline1Muon{bjet}", f"baseline1Muon{bjet}_HLT", f"baseline{bjet}", f"baseline{bjet}_HLT"]
    regionList = [f"baseline1Muon{bjet}", f"baseline1Muon{bjet}_HLT", f"baseline{bjet}", f"baseline{bjet}_HLT", f"baselineMuTri{bjet}", f"baselineMuTri{bjet}_HLT"]
    
    variableDic = {
        'jets_HT': np.array( [400., 448, 520, 640, 760, 1000,  1240,  1600, 2800] ),
        'bjetsM_num': np.array([ 0.5, 1.5, 2.5, 3.5, 5.5, 7.5]),
        'jets_6pt': np.array([30, 35, 40, 45, 55., 70., 85., 115, 150]),
        'jets_num': np.array([ 5.5, 6.5, 7.5, 8.5, 9.5,12.5]),
        'jets_1pt': np.array([25., 55,  85, 145, 175, 235, 295, 355, 415, 490, 625]),
    }
    
    varList = list(variableDic.keys())     
    sumList = ['singleMu', 'tt', 'tttt']
    era = uf.getEraFromDir(inputDirDic['mc'])   
    sumProcessPerVar = uf.getSumHist(inputDirDic, regionList, sumList, varList, era, isRun3 )#sumProcessPerVar[ivar][region][sumPro]
   
    plotDir = inputDirDic['mc'] + 'results/'
    uf.checkMakeDir(plotDir)
    
    for ivar in variableDic.keys():
        eff_ttTruth = plotEffHLT(ivar, variableDic[ivar], f"baseline{bjet}", f"baseline{bjet}_HLT", sumProcessPerVar, f"ttTrueEff{bjet}", 'tt', plotDir, 'tt')
        eff_ttRef = plotEffHLT(ivar, variableDic[ivar], f"baseline1Muon{bjet}", f"baseline1Muon{bjet}_HLT", sumProcessPerVar,  f"ttOrthEff{bjet}", 'tt', plotDir, 'tt')
        eff_dataRef = plotEffHLT(ivar, variableDic[ivar], f"baseline1Muon{bjet}", f"baseline1Muon{bjet}_HLT", sumProcessPerVar, f"dataOrthEff{bjet}", 'data', plotDir, 'singleMu')
        eff_tttt = plotEffHLT(ivar, variableDic[ivar], f"baseline{bjet}", f"baseline{bjet}_HLT", sumProcessPerVar, f"ttttTrueEff{bjet}", 'tttt',plotDir, 'tttt')
    
        overlayList = [eff_ttTruth, eff_ttRef, eff_dataRef]
        legendList = [ 'tt: true', 'tt: orthogonal', 'data: orthogonal' ]
        overlayName = plotDir + 'HLTefficiencyOverlay_' + ivar  + bjet+'_v0' 
        uf.plotOverlay(overlayList, legendList, era, 'HLT efficiency',  overlayName, 'AP', [0.4, 0.3, 0.9, 0.5],  [0, 1.2])

        eff_ttMuTri = plotEffHLT(ivar, variableDic[ivar], f"baselineMuTri{bjet}", f"baselineMuTri{bjet}_HLT", sumProcessPerVar, f"ttMuTriTrueEff{bjet}", 'tt', plotDir, 'tt')
        overlayList2 = [eff_ttTruth, eff_ttRef, eff_ttMuTri]
        legendList2 = [ 'tt: true', 'tt: muTri+muOffline', 'tt: muTri']   
        uf.plotOverlay(overlayList2, legendList2, era, 'HLT efficiency',  overlayName+'_muTri', 'AP', [0.4, 0.3, 0.9, 0.5],  [0, 1.2])
  
   
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
                                
        
    
       
       
    
    


def plotEffHLT(variable, binning,  regionDe, regionNu, sumProcessPerVar, plotName, legendName, plotDir, sumPro): 
    MCTrueth_de = sumProcessPerVar[variable][regionDe][sumPro].Clone()
    MCTrueth_nu = sumProcessPerVar[variable][regionNu][sumPro].Clone()
        
    if len( binning ) >0:
        binLowEges = binning
        MCTrueth_de = MCTrueth_de.Rebin(len(binLowEges)-1, '', binLowEges)
        MCTrueth_nu = MCTrueth_nu.Rebin(len(binLowEges)-1, '', binLowEges)
    
    plotName = plotDir + variable + plotName + '_v0'
    era = uf.getEraFromDir(plotDir)
    
    eff = uf.plotEffTEff(MCTrueth_nu, MCTrueth_de, plotName, era, legendName) 
    print(eff.GetName())
    
    
    # return eff_MCTrueth
    return eff

    
if __name__=='__main__':
    main()