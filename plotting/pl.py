import math
from array import array
import csv

import usefulFunc as uf
# from ROOT import * #!!!Bad proctice, disables in latest ROOT versions
import ROOT
import setTDRStyle as st
import ttttGlobleQuantity as gq
import writeDatacard as wd

def main():
    ifVLL = ''
    ifLogy = True
    # ifLogy = False
    # ifStackSignal = False
    ifStackSignal = True
    ifPrintSB = True
    ifPrintSB = False
    # ifSystematic = True 
    ifSystematic = False  
    # ifFTau = False #!use qcd instead of fakeTau
    ifFTau = True #if use fakeTau bg and other bg with genTau requirement
    # ifMCFTau = True #!
    ifMCFTau = False #!
    ifblinding = False#!!!
    plotName = 'dataVsMC_v5'
    
    if ifMCFTau:
        plotName = f'{plotName}_MCFTau'
    if ifSystematic:
        plotName = f'{plotName}_sys'
    if not ifblinding:
        plotName = f'{plotName}_unblind'
   
    #!1tau2l 
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l_fakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_newCR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinC_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_fakeTauScaled/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l_fakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1NewFRBinA_tauFMorph_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_fakeTauScaled/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_tauF1_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_fakeTauScaled/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_fakeTauScaled/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_newFRBinATauFMorphBugFix_v94LepPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lNewCR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV17_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lV17_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnly/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v3BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v4BDT1tau2lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v5BDT1tau2l_tauFMorphFix/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v5BDT1tau2l_tauFMorphFix/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v5BDT1tau2l_tauFMorphFix/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94LepPreJetVetoHemOnlyV2/mc/variableHists_v5BDT1tau2l_tauFMorphFix/'
    channel = '1tau2l'
    variables = ['BDT']
    regionList = [ '1tau2lCR3', '1tau2lSR']
    # regionList = ['1tau2lCR3']


    #!1tau1l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v1DataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v1DataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_ptMorphed1tau1l/'
    # inputDir ='/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorph_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinATauFMorphBugFix_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly_backupV2/mc/variableHists_v0BDT1tau1l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeTV3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v1BDT1tau1lTestLeading7/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v1BDT1tau1lTestLeading7/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v1BDT1tau1lTestLeading7/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v1BDT1tau1lTestLeading7/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v1BDT1tau1lTestLeading7Remove1/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v1BDT1tau1lTestLeading7Remove2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v3BDT1tau1lV18_fakeTauDataDriven/'
    # channel = '1tau1l'
    # variables = ['BDT']
    # regionList = ['1tau1lSR', '1tau1lCR12']
    # regionList = ['1tau1lCR12']
  
    #!1tau0l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sys/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC_sysV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/mc/variableHists_v0DataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinC_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_newCR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_newFRBinA_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven_ptMorphed/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lFakeTauPtMorphedV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v1dataMC_fakeTauDataDriven/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0lV17/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v5BDT1tau0l_tauFMorphFix/'
    # channel = '1tau0l' 
    # variables = ['BDT']
    # regionList = ['1tau0lVR', '1tau0lCRMR']
    # regionList = ['1tau0lVR',  '1tau0lCRMR', '1tau0lSR']
    # regionList = ['1tau0lSR'] #!unblinding!




    
    era = uf.getEraFromDir(inputDir)
    print('era=', era)
    isRun3 = uf.isRun3(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    
    plotNormal(inputDirDic, variables, regionList, plotName, era, isRun3, ifFTau, ifVLL,  channel, ifLogy, ifPrintSB, ifStackSignal, ifSystematic, ifMCFTau, ifblinding)

   
def read_csv_as_lines(file_path, delimiter=','):
    """Read a CSV file with the specified delimiter and return a list of strings, each representing a line in the CSV."""
    lines = []
    try:
        with open(file_path, mode='r', newline='') as file:
            reader = csv.reader(file, delimiter=delimiter)
            for row in reader:
                # Join the row elements into a single string separated by the delimiter
                line = delimiter.join(row)
                lines.append(line)
    except Exception as e:
        print(f"Error reading CSV file: {e}")
        return None
    
    return lines


def getSumList(channel, ifFakeTau, ifVLL, ifMCFTau, ifCombine=False):
    #ifCombine: if combine, the ttX processes are split
    sumProList = gq.proChannelDic[channel] if not ifCombine else gq.proChannelDic_forCombine[channel]
    if ifVLL:
        sumProList.append(ifVLL)
    if not ifFakeTau:
        sumProList.remove('fakeTau')
        #add qcd to the front 
        sumProList.insert(0, 'qcd')
    # if ifMCFTau and (not ifCombine):
    if ifMCFTau :
        sumProList.insert(0, 'fakeTauMC')
    print('sum pro', sumProList) 
    return sumProList

def plotNormal(inputDirDic, variables, regionList, plotName, era, isRun3, ifFakeTau=False, ifVLL='',  channel='1tau1l',  ifLogy=False, ifPrintSB=False, ifStackSignal=False, ifDoSystmatic=False, ifMCFTau=False, ifBlind=True):
    sumProList = getSumList(channel, ifFakeTau, ifVLL, ifMCFTau)    
    sumProSys = getSysDicPL(sumProList, ifDoSystmatic, channel, era, True)    
    [print(ipro, ': ', sysL) for ipro, sysL in sumProSys.items()]
    sumProcessPerVar, sumProcessPerVarSys = uf.getSumHist(inputDirDic, regionList, sumProList, sumProSys, variables, era, isRun3 , False, ifMCFTau)#sumProcessPerVar[ivar][region][sumPro]
    
    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir( plotDir)
    for variable in variables:
        for iRegion in regionList:       
            makeStackPlotNew(sumProcessPerVar[variable][iRegion], sumProList, variable, iRegion, plotDir, False, plotName, era, True, 100, ifStackSignal, ifLogy, ifPrintSB, ifVLL, sumProcessPerVarSys[variable][iRegion], ifDoSystmatic, ifBlind) 
    
def getSysDicPL(inProcess, ifSys=False, channel='1tau1l', era='2018', ifCombine=False):
    #todo: add funcionality of getting systematics from datacard
    #!Lumi uncertainty to be added mannually
    if not ifSys:
        return {}
    sumProSys = {} 
    print('staring to get process systematic')
    # processes = gq.proChannelDic[channel][:] if not ifCombine else gq.proChannelDic_forCombine[channel][:]
    processes = inProcess[:] 
    print('processes in getSysDicPL(): ', processes) #?not 'jetHT' already
    if channel=='1tau2l':
        processes.remove('leptonSum')
    else:
        processes.remove('jetHT')
    proSys = wd.getSysDic(processes, channel, era, ifCombine)          
    print(proSys)
    
    for ipro in processes:
        sumProSys[ipro] = [] 
        for isys, sysList in proSys.items():
            print(isys, sysList)
            if sysList[1][ipro]==1:
                sumProSys[ipro].append(isys)
    
    return sumProSys
        
       
       
def plotFakeTau(inputDirDic, variables, regions, plotName, era, isRun3, ifFTau=False):
    if not ifFTau:
        print('not plotting for faketau\n')
        return 
    print('\n plot fake tau')
    
    sumProList = ['jetHT','tt', 'ttX', 'singleTop', 'WJets', 'tttt'] 
    sumPro = uf.getSumHist(inputDirDic, regions, sumProList, variables, era, isRun3 )#sumProcessPerVar[ivar][region][sumPro]
    for ivar in variables:
        for Iregion in regions:
            FRRegions = [Iregion+'Gen', Iregion+'LTauNotT_Weighted', Iregion+'LTauNotTGen_Weighted']
            sumProForFR = uf.getSumHist(inputDirDic, FRRegions, sumProList, variables, era, isRun3 )#sumProcessPerVar[ivar][region][sumPro]
            replaceGenMC(sumPro[ivar][Iregion], sumProForFR[ivar][Iregion+'Gen'])
            addFakeTau(sumPro[ivar][Iregion], sumProForFR[ivar][Iregion+'LTauNotT_Weighted'], sumProForFR[ivar], Iregion+'LTauNotTGen_Weighted')
            
            makeStackPlotNew(sumPro[ivar][Iregion], list(sumPro[ivar][Iregion].keys()), ivar, Iregion, inputDirDic['mc']+'results/', True, plotName+'_fakeTau', era, True, 100, False, False)
    # print(sumPro)    

    
def replaceGenMC(histsNorminal, histsFR):
    for iPro in histsNorminal:
        if iPro == 'jetHT': continue 
        histsNorminal[iPro] = histsFR[iPro]
    print('replace gen MC')
    
def addFakeTau(histsNorminal, histsLTauNotT, histsLTauNotTGen, genRegion):
    histsLTauNotTGenAll = uf.addBGHist(histsLTauNotTGen, genRegion) 
    fakeTau = (histsLTauNotT['jetHT'] - histsLTauNotTGenAll).Clone('fakeTau')
    histsNorminal['fakeTau'] = fakeTau  
    print('fake tau bg added \n') 
        


  

 
def removeQCD(sumProcessPerVar, legendOrder):
    variables = list(sumProcessPerVar.keys()) 
    regionList = list(sumProcessPerVar[variables[0]].keys())
    for (i,ire) in enumerate( regionList):
        if '1tau1l' in ire:
        # if '1tau1lSR' in ire:
            print('remove qcd for 1tau1l')
            for ivar in variables:
                # if i==0:
                #     legendOrder.remove('qcd')     
                if not 'qcd' in sumProcessPerVar[ivar][ire].keys(): continue
                sumProcessPerVar[ivar][ire].pop('qcd')
    if '1tau1l' in regionList:
        legendOrder.remove('qcd') 
    return sumProcessPerVar, legendOrder
 
    
    
 
def removeSingleMu(sumProcessPerVar):
    variables = list(sumProcessPerVar.keys())
    regionList = sumProcessPerVar[variables[0]].keys()
    for (i,ire) in enumerate( regionList):
        for ivar in variables:
            if 'singleMu' in sumProcessPerVar[ivar][ire].keys():
                sumProcessPerVar[ivar][ire].pop('singleMu')
    return sumProcessPerVar
            
def checkRegionGen(regionList):
    hasFakeTau = False
    for ire in regionList:
        if 'Gen' in ire:
            hasFakeTau = True
    return hasFakeTau
                

 
 
        
def checkHists( histsDict ):
    for ikey in histsDict.keys():
        print('iProcess: ', ikey )
        histsDict[ikey].Print()


def makeStackPlotNew(nominal, legendOrder, name, region, outDir, ifFakeTau, savePost = "", era='2016', includeDataInStack=True, signalScale = 100, ifStackSignal = False, ifLogy=False, ifPrint=False, ifVLL=False, sysHists={}, ifSystematic=False, ifBlinding=True, ifPostfit=False):
    '''
    nominal is a dic of distribution for all processes including data
    nominal: nominal[iprocess]
    sysHists: sysHists[iprocess]['prefiring_up']
    '''
    #name is variable name
    print( 'start plotting data/mc plot for {}'.format(name))
    myStyle = st.setMyStyle()
    myStyle.cd() #???not sure why the gStyle is not affecting the sedond pad
    
    canvasName = '{}_{}'.format( region, name )
    canvy = ROOT.TCanvas( canvasName, canvasName, 1000,1000)
    
    #it seems text size  is scaled to pad size
    upPad = ROOT.TPad('up', 'up', 0, 0., 1, 1)
    downPad = ROOT.TPad('down', 'down', 0., 0, 1, 1)
    upPad.SetBottomMargin(0.3)
    downPad.SetTopMargin(0.72)
    # downPad.SetBottomMargin(0.2)
    upPad.Draw()
    downPad.SetFillColor(0)
    downPad.SetFillStyle(0) #set the empty space to be empty, so that not cover the upPad
    downPad.SetGridy(1)
    downPad.Draw()
    
    upPad.cd() #???cd() pad causing stack to be not accessble???
    if ifLogy:
        upPad.SetLogy(1)
        name = name + '_logy'
    if ifVLL:
        name = name + '_VLL'

    ifBlind = True if 'SR' in region else False #!!!
    if not ifBlinding:
        ifBlind = False
    
    
    is1tau2l = True if ('1tau2l' in region) or ('baseline' in region) else False 
    dataHist, systsUp, systsDown, sumHist, stack, signal = getHists(nominal, legendOrder, ifBlind, False, ifStackSignal, ifVLL, sysHists, is1tau2l)

    setUpStack(canvy, stack, sumHist.GetMaximum(), signal.GetMaximum()*signalScale, ifLogy) 
    stack.Draw("hist")
    upPad.Update()
    upPad.Draw()
    
    printSBLastBin(sumHist, signal, upPad, ifPrint)
     
    #error bar for MC stack    
    systsUp, systsDown = addStatisticUncer( sumHist, systsUp, systsDown )#add sytematic uncertainty
    assymErrorPlot = getErrorPlot(sumHist,systsUp,systsDown)#systsUp and systsDown are the total bin up and down uncertainty, not n+-uncertainty
    assymErrorPlot.Draw("e2 SAME")

    if includeDataInStack and dataHist:
        dataHist.SetLineWidth(1)
        dataHist.SetMarkerSize(1.5)
        dataHist.Draw("e0 same")
    
    # if not ifLogy:    
    signal.Scale(signalScale)
    # signal.SetLineColor(kBlue)
    signal.SetLineStyle(ROOT.kSolid)
    signal.SetLineWidth(3)
    signal.SetFillStyle(0)
    signal.GetXaxis().SetLabelSize(0.0)
    signal.Draw("SAME HIST ")
    upPad.Update()

    downPad.cd()
    myStyle.cd()
    myStyle.SetOptTitle(0)
    sumHistoData = getHistToData( dataHist, sumHist)
    sumHistoData.Draw("E1X0")
    
    assymErrorPlotRatio = getErrorPlot(sumHist,systsUp,systsDown,True)
    # assymErrorPlotRatio.SetTitle("")
    assymErrorPlotRatio.Draw("e2 same")

    #legend
    leggy = addLegend(canvy, nominal, legendOrder, dataHist, assymErrorPlot, signal, signalScale, ifLogy, ifVLL, ifStackSignal, ifSystematic, ifPostfit)
    leggy.Draw()
    
    #text above the plot
    st.addCMSTextToPad(canvy, era)
    
    
    canvy.Update()
    canvy.SaveAs(outDir+"{}_{}_{}.png".format(region,name, savePost))
    canvy.SaveAs(outDir+"{}_{}_{}.pdf".format(region,name, savePost))
    myStyle.Reset()
    print( 'done plotting data/mc plot for {}\n'.format(name))
    print('\n')

def printSBLastBin(sumHist, signal, canvas, ifPrint=False):
    if not ifPrint: return
    canvas.cd()
    latex = ROOT.TLatex()
    latex.SetTextSize(0.03)
    latex.SetTextAlign(22)  # 
    
    sig = signal.GetBinContent(signal.GetNbinsX())
    bg = sumHist.GetBinContent(sumHist.GetNbinsX()) - sig
    
    latex.DrawLatex(signal.GetBinCenter(signal.GetNbinsX()), sig+bg+0.05, f"S={sig:.2f}, B={bg:.2f}")
    
    canvas.Update()
    canvas.Draw()

 
def addLegend(canvy, nominal, legendOrder, dataHist, assymErrorPlot, signal, signalScale, ifLogy=False, ifVLL='', ifStackSignal=False, ifDoSystmatic=False, ifPostfit=False):
    # x1,y1,x2,y2 are the coordinates of the Legend in the current pad (in normalised coordinates by default)
    canvy.cd()
    leggy = st.getMyLegend(0.18,0.75,0.89,0.90)
    # for ipro in nominal.keys():
    for ipro in legendOrder:
        # if ipro == 'jetHT' :
        if uf.isData(ipro):
            if dataHist:
                leggy.AddEntry(dataHist,"Data[{:.1f}]".format(getIntegral(dataHist)),"epl")
        elif  uf.isBG(ipro, ifVLL)==1:
            sigPro = 'tttt' if ipro == 'tttt' else ifVLL
            signalEntry = '{}*{}[{:.1f}*{}]'.format(sigPro,signalScale, getIntegral(nominal[sigPro]), signalScale)
            leggy.AddEntry( signal, signalEntry, 'l')
            # if ifLogy:
            if ifStackSignal:
                legText = '{}[{:.1f}]'.format(ipro, getIntegral(nominal[ipro]))
                leggy.AddEntry(nominal[ipro], legText,"f")
        else:
            legText = '{}[{:.1f}]'.format(ipro, getIntegral(nominal[ipro]))
            leggy.AddEntry(nominal[ipro], legText,"f")

    # Determine the uncertainty label based on flags
    if ifPostfit:
        sysLeggy = 'Postfit unc.'  # Postfit uncertainties include stat + all syst propagated through fit
    elif ifDoSystmatic:
        sysLeggy = 'Stat. + Syst. unc.'  # Pre-fit with systematics
    else:
        sysLeggy = 'Stat. unc.'  # Only statistical uncertainties

    leggy.AddEntry(assymErrorPlot, sysLeggy,"f")
    # leggy.AddEntry(assymErrorPlot,"Stat. unc","f")
    
    leggy.SetNColumns(2) 
    leggy.Draw()
    canvy.Update()
    return leggy
  
def getHistToData( dataHist, sumHist):
    if dataHist:
        sumHistoData = dataHist.Clone(dataHist.GetName()+"_ratio")
        sumHistoData.Sumw2()
        sumHistoData.Divide(sumHist)
    else:
        sumHistoData = sumHist.Clone() 
        sumHistoData.Reset()
    sumHistoData.GetYaxis().SetTitle("Data/pred.")
    # sumHistoData.GetYaxis().SetTitleOffset(1.3)
    sumHistoData.SetMinimum(0.45)
    # sumHistoData.SetMaximum(1.2)
    sumHistoData.SetMaximum(1.55)
    sumHistoData.GetXaxis().SetTitle(sumHist.GetTitle())
    sumHistoData.GetXaxis().SetTitleSize(0.05)
    sumHistoData.GetYaxis().SetNdivisions(6)
    # sumHistoData.GetYaxis().SetTitleSize(0.05)
    # sumHistoData.GetYaxis().SetLabelSize(0.04)
    sumHistoData.SetTitle("")
    return sumHistoData
   
def setUpStack(canvy, stack, sumMax, signalMax, ifLogy=False): 
    #set y axix maxi
    if sumMax > signalMax:
        maxi = 1.7* sumMax
    else:
        maxi = 1.7* signalMax  
    if maxi<=0 :
        # print(name, ' variable empty\n')
        return
    if ifLogy:
        maxi = 10*maxi
    stack.SetMaximum(maxi) #Set the minimum / maximum value for the Y axis (1-D histograms) or Z axis (2-D histograms)  By default the maximum / minimum value used in drawing is the maximum / minimum value of the histogram
    if ifLogy:
        stack.SetMinimum(0.5)
    stack.Draw("hist")
    stack.GetXaxis().SetLabelSize(0.0)
    stack.GetYaxis().SetTitle('Events')
    stack.GetYaxis().SetTitleOffset(1.2)
    stack.GetYaxis().SetTitleSize(0.05)
    
    canvy.Modified()
    canvy.Update()
   
   
   
   
    
def getLegend(nominal,  dataHist, assymErrorPlot, signal, signalScale, legendOrder):
    # x1,y1,x2,y2 are the coordinates of the Legend in the current pad (in normalised coordinates by default)
    leggy = TLegend(0.18,0.75,0.89,0.90)
    # if "jetHT" in nominal.keys():
    if "jetHT"  in nominal.keys() or ('leptonSum' in nominal.keys()):
        # nominal['jetHT'].SetMarkerSize(2)
        # leggy.AddEntry(nominal['jetHT'],"Data[{:.1f}]".format(getIntegral(nominal['jetHT'])),"ep")
        leggy.AddEntry(dataHist,"Data[{:.1f}]".format(getIntegral(dataHist)),"ep")
    for entry in legendOrder:
        legText = '{}[{:.1f}]'.format(entry, getIntegral(nominal[entry]))
        # leggy.AddEntry(nominal[entry],entry,"f")
        leggy.AddEntry(nominal[entry], legText,"f")
    leggy.AddEntry(assymErrorPlot,"Stat. unc","f")
    signalEntry = 'tttt*{}[{:.1f}]'.format(signalScale, getIntegral(nominal['tttt']))
    leggy.AddEntry( signal, signalEntry, 'l')
    return leggy
  
def getIntegral(histogram):
    integral = histogram.Integral(0, histogram.GetNbinsX() + 1, "overflow") 
    return integral
    

def ifDoSystmatic(systHists):
    doSystmatic = False
    for ipro in systHists.keys():
        if systHists[ipro]:
            doSystmatic = True
    print( 'doSystmatic: ', doSystmatic )
    return doSystmatic
    
def getHists(nominal,  legendOrder, ifBlind, doSystmatic=False, ifStackSignal = False, ifVLL = '', sysHists={}, if1tau2l=False):
    #here we get dataHist and add all MC for sumHist    
    keyList = list(nominal.keys()) #process list; nominal[iprocess]=hist
    colourPerSample = {
        'tttt':ROOT.kBlue,
        'VLLm600':ROOT.TColor.GetColor("#D10363"),
        # 'VLLm600':kMagenta,
        'VLLm800': ROOT.TColor.GetColor("#D10363"),
        'VLLm700': ROOT.TColor.GetColor("#D10363"),
        'tt': ROOT.TColor.GetColor("#f03b20"),
        'qcd': ROOT.TColor.GetColor("#ffeda0"),
        'ttX': ROOT.TColor.GetColor("#fc9272"),
        'singleTop': ROOT.TColor.GetColor("#91bfdb"),
        'VV': ROOT.TColor.GetColor("#edf8b1"),
        'WJets': ROOT.TColor.GetColor("#998ec3"),
        # 'fakeTau': ROOT.TColor.GetColor("#ffeda0"),
        'fakeTau': ROOT.TColor.GetColor("#fec44f"),
        'XGamma': ROOT.TColor.GetColor("#d73027"),
        'VVV': ROOT.TColor.GetColor("#4575b4"),
        'Higgs': ROOT.TColor.GetColor("#313695"),
        'DY': ROOT.TColor.GetColor("#313695"),
        'fakeLepton': ROOT.TColor.GetColor("#fec44f"),
        'Minor': ROOT.TColor.GetColor("#edf8b1"),
        'ttH': ROOT.TColor.GetColor("#f03b20"),
        'ttW': ROOT.TColor.GetColor("#f03b20"),
        'ttZ': ROOT.TColor.GetColor("#f03b20"),
        'ttG': ROOT.TColor.GetColor("#f03b20"),
        'fakeTauMC': ROOT.TColor.GetColor("#ffeda0"),
    }
    
    sumHist = nominal[keyList[0]].Clone()
    sumHist.Reset()
    systsUp = nominal[keyList[0]].Clone("systsUp")
    systsUp.Reset()
    systsDown = nominal[keyList[0]].Clone("systsDown")
    systsDown.Reset()
    dataHist = 0
    stack = ROOT.THStack( 'stack', 'stack' )
    legendOrder.reverse()
    for i in legendOrder:
        if uf.isData(i):
            if not ifBlind:
                dataHist = nominal["jetHT"].Clone() if not if1tau2l else nominal['leptonSum'].Clone()
                dataHist.SetMarkerStyle(20)
                dataHist.SetMarkerSize(1.2)
                dataHist.SetMarkerColor(ROOT.kBlack)
                dataHist.SetLineColor(ROOT.kBlack)
                dataHist.SetTitleSize(0.0)
            continue
        if uf.isBG(i, ifVLL)==3: continue
        if uf.isBG(i, ifVLL)==1 and (not ifStackSignal): continue
        
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(ROOT.kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetTitleSize(0.01)
        nominal[i].GetXaxis().SetLabelSize(0.0)
        nominal[i].GetYaxis().SetTitle('Events')
        sumHist.Add(nominal[i]) #!sumHist is all bg
        stack.Add(nominal[i])
        if sysHists:
            print('cal sys for: ', i)
            tempUp,tempDown = getSystVariation(nominal[i],sysHists[i] ) # get the qaudrature sum of the systematic uncertainty for each process
            systsUp.Add(tempUp) #adding various processes, 
            systsDown.Add(tempDown)
            
    legendOrder.reverse()
    
    #scale tttt
    if 'tttt' in nominal.keys() or ifVLL:
        if not ifVLL:
            signal = nominal['tttt'].Clone()
            signal.SetLineColor(colourPerSample['tttt'])
        else:
            # signal = nominal['VLLm600'].Clone()
            # signal.SetLineColor(colourPerSample['VLLm600'])
            signal = nominal[ifVLL].Clone()
            signal.SetLineColor(colourPerSample[ifVLL])
    else:
        signal = nominal['tt'].Clone()
        signal.Reset()
            
    return dataHist, systsUp, systsDown, sumHist, stack, signal 


def getErrorPlot(totalMC,systUp,systDown,isRatio = False):
    # for the data/mc ratio or the error bar in the stack for MC
    x = array('d',[])
    y = array('d',[])
    exl = array('d',[])
    exh = array('d',[])
    eyl = array('d',[])
    eyh = array('d',[])
    xAxis = systUp.GetXaxis()
    for i in range(1,xAxis.GetNbins()+1):
        x.append(xAxis.GetBinCenter(i)) # x is the x value
        if not isRatio: y.append(totalMC.GetBinContent(i))
        else: y.append(1.)
        exl.append(xAxis.GetBinCenter(i) - xAxis.GetBinLowEdge(i))
        exh.append(xAxis.GetBinLowEdge(i)+xAxis.GetBinWidth(i)-xAxis.GetBinCenter(i))
        if not isRatio:
            eyl.append(systDown.GetBinContent(i))
            eyh.append(systUp.GetBinContent(i))
        else:
            if not totalMC.GetBinContent(i)==0 :
                eyl.append(systDown.GetBinContent(i)/totalMC.GetBinContent(i))
                eyh.append(systUp.GetBinContent(i)/totalMC.GetBinContent(i))
            #???can you simply divide error like this? i think it's wrong
            else: 
                #???set to 0 by me
                eyl.append(0)
                eyh.append(0)
    errors = ROOT.TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    
    errors.SetFillStyle(3013)
    errors.SetFillColor(14)
    errors.GetXaxis().SetLabelSize(0.0)
    
    return errors


def getSystVariation(nominalHist,systHists):
    '''
    # to calculate the total sysHistUp and down for one process from variaus uncertainty source
    sysHistUp and systHistDown bincontent is the sigma_total for each bin from various sources
    '''
    #here the input nominalHist and systHists are for one summed process
    # systHists include 'up' and 'down' for varias sources, but it's just for one process
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()
    
    for systHi in systHists.keys():
    #so this is to sum the sytstmatic variation for sources of systematic uncertainty
        iSys = True
        syst = systHists[systHi].Clone()
        # print( 'sytHistUp: ', syst.GetName() )
        syst.Add(nominalHist,-1)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            if nominalHist.GetBinContent(i)<=0.: continue 
            if "Up" in syst.GetName():
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            if abs(syst.GetBinContent(i)/nominalHist.GetBinContent(i))>0.9:
                print('!!! sytematic variation too big: ', syst.GetName(), ' in bin i: ', i)

    return systHistUp,systHistDown


def getSystVariation_my(nominalHist,systHists):
    # to calculate the total sysHistUp and down
    #here the input nominalHist and systHists are for one summed process
    # systHists include 'up' and 'down' for varias sources, but it's just for one process
    #???the calculation seems wrong
    systHistUp = nominalHist.Clone("up")
    systHistDown = nominalHist.Clone("down")
    systHistUp.Reset()
    systHistDown.Reset()

    for systHi in systHists.keys():
    #systHi is 'up' or 'down' for varias sources for this process
    #so this is to sum the systematic variation for sources of systematic uncertainty
        print( systHi )
        if "bTag" in systHi: continue
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist,-1)
        syst.Divide(nominalHist)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            if "up" in syst.GetName():
                # print( 'sytHistUp: ', systHistUp.GetBinContent() )
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
    for i in range(1,systHistUp.GetXaxis().GetNbins()+1):
        systHistUp.SetBinContent(i,(math.sqrt(systHistUp.GetBinContent(i)))*nominalHist.GetBinContent(i))
        systHistDown.SetBinContent(i,(math.sqrt(systHistDown.GetBinContent(i)))*nominalHist.GetBinContent(i))
    return systHistUp,systHistDown


def addStatisticUncer(sumHist, systsUp, systsDown ):
    for i in range(1,sumHist.GetXaxis().GetNbins()+1):
        # systsUp.SetBinContent(i, math.sqrt( systsUp.GetBinContent(i)*systsUp.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        # systsDown.SetBinContent(i, math.sqrt( systsDown.GetBinContent(i)*systsDown.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        systsUp.SetBinContent(i, math.sqrt( systsUp.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
        systsDown.SetBinContent(i, math.sqrt( systsDown.GetBinContent(i) + sumHist.GetBinError(i)*sumHist.GetBinError(i) ) )
    return systsUp,systsDown



if __name__ == "__main__":
    main()
