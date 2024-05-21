
import math
from array import array
import numpy as np

import usefulFunc as uf
from ROOT import *
import setTDRStyle as st



def main():
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v2_btagCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v1FR_application/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v0_BDT1tau1lCRs/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v6baseline_v56preselection/mc/variableHists_v0BDT_SR30Bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4baselineBtagRUpdated_v57ovelapWithTausF/mc/variableHists_v0BDT_SR30Bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6baseline_v56NoHLTButPre/mc/variableHists_v0BDT_SR30Bins/'
    
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v0Testing/mc/variableHists_v0allRegions/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v1newCrab/mc/variableHists_v0allRegions/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0NewMV_v1newCrab/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewMV_v59newOScode/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v5newBtagEff_v60fixeJetBtagBug/mc/variableHists_v5OldBtagR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v6updatedBtagR_v60fixeJetBtagBug/mc/variableHists_v7newBtagRApp/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v0btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v3btagWeightGood_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v1btagWPWeightUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v2btagWPCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v1traingWithBtagWP/'
    
    #Run3
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v0preSel/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v0preSel/mc/variableHists_v1dataMC/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022/v0baseline_v0preSel/mc/variableHists_v2SR1tau1l/' #!copied tttt.root from 2016
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1btagWPandRUpdated_v61fixesLepRemovalBug/mc/variableHists_v0dataMC_btagWPsf/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt45/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt40/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt42/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v64noHLTSel/mc/variableHists_v0dataMC_jets6pt42/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1fixedTauProng_v63smallFixJER/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSF_v64PreAndHLTSel/mc/variableHists_v2dataMC_HT600HLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinD_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT600HLTSFBinD/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSF_v64PreAndHLTSel/mc/variableHists_v2dataMC_HT600/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFBinE_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT600HLTSFBinE/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT500BinE_v64PreAndHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinE/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT550HLTSFBinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT550HLTSFBinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0_HLTSFMeasure_6thJet40HT550BinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v1dataMC_noHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v3dataMC_HT550HLTSFBinF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0NewHLTSFHT550BinF_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016/v0baseline_v64PreAndHLTSel/mc/variableHists_v0BasicSystematic_20bins/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75AddTauTTTTNoHTCut/mc/variableHists_v0dataMC1tau1l_pileupSF_HT350/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75AddTauTTTTNoHTCut/mc/variableHists_v0dataMC_basicWeight_new1tau0l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_basicWeight/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75OverlapRemovalFTau/mc/variableHists_v2dataMC_basicWeight_1tau1lBjet2/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75OverlapRemovalFTau/mc/variableHists_v3dataMC_basicWeight_1tau1lBjet3Jet6HT400/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT350_v75OverlapRemovalFTau/mc/variableHists_v3dataMC_basicWeight_1tau1lBjet3Jet6HT400Jet6pt30/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineNewHLTWeight_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_basicWeight_HT450Jet6pt32TauM/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v1dataMC_allCorrectionButHLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_V0Basictraining/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_V0Basictraining_bin3/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v3dataMC_allCorrection_Test1tau0lHT550/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v1FR_application_jetEta/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450AddTauProng_v75OverlapRemovalFTau/mc/variableHists_v1FR_application_jetEtaTauF1/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v3baselineAddFRWeight_v75OverlapRemovalFTau/mc/variableHists_v5dataMC_allCorrection_UsingFakeTau/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v76For1tau2l/mc/variableHists_v1dataMC_allCorrectionButHLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baseline_v76For1tau2l/mc/variableHists_v0BDT1tau2l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v75OverlapRemovalFTau/mc/variableHists_v0Basictraining/'#1tau1l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v75OverlapRemovalFTau/mc/variableHists_v0Basictraining1tau1l/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v75OverlapRemovalFTau/mc/variableHists_v0Basictraining1tau1l_bin3CR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroNewTriSF_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroNewTriSF_v75OverlapRemovalFTau/mc/variableHists_v1dataMC_allCorrectionButHLT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroNewTriSFBinN_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/'
    inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHardroNewTri4BBinY_v75OverlapRemovalFTau/mc/variableHists_v0dataMC_allCorrection/'
    
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3HLTPre/mc/variableHists_v1dataMC_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3HLTPre/mc/variableHists_v2dataMC_pileupBtagSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3HLTPre/mc/variableHists_v3dataMC_pileupBtagHLTSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3HLTPre/mc/variableHists_v0dataMC_noCorrectionNewTTBR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v3HLTPre/mc/variableHists_v3dataMC_pileupBtagHLTSFNewTTBR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baselineBtagWeightFix_v3HLTPre/mc/variableHists_v0dataMC_noCorrectionNewTTBR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baselineBtagWeightFix_v3HLTPre/mc/variableHists_v2dataMC_pileupBtagSFNewTTBR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022postEE/v0baseline_v4HLTPreNoEnergyScale/mc/variableHists_v0dataMC_noCorrectionNewTTBR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v4HLTPreNoEnergyScale/mc/variableHists_v0dataMC_noCorrection/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v4HLTPreNoEnergyScale/mc/variableHists_v1dataMC_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v5HLTPreJetVetoMap/mc/variableHists_v1dataMC_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v5HLTPreJetVetoMap/mc/variableHists_v1dataMC_pileupSFNewTTBR/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baselineTauIDSFUpdated_v5HLTPreJetVetoMap/mc/variableHists_v2dataMC_pileupTauIDSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v6AllEnergyScale/mc/variableHists_v2dataMC_pileupTauIDSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v6AllEnergyScale/mc/variableHists_v3dataMC_pileupTauIDBtagWPSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v6AllEnergyScale/mc/variableHists_v2dataMC_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v7tauSelFix/mc/variableHists_v3dataMC_pileupTauIDBtagWPSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v7tauSelFix/mc/variableHists_v4dataMC_pileupBtagWPSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baselineTauGenFlavour_v7tauSelFix/mc/variableHists_v3dataMC_pileupTauIDBtagWPSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v8OldTauIDNoTES/mc/variableHists_v4dataMC_pileupBtagWPSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v9addTauTT/mc/variableHists_v4dataMC_pileupBtagWPSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v1TauSFNew_v9addTauTT/mc/variableHists_v5dataMC_pileupTauTTIDBtagWPSF_tauTT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline_v10addBjetPTT/mc/variableHists_v5dataMC_pileupTauTTIDBtagWPSF_tauTT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline6thJet30_v11overlapRemovalTausT/mc/variableHists_v5dataMC_pileupTauTTIDBtagWPSF_tauTT/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0baseline6thJet30_v11overlapRemovalTausT/mc/variableHists_v6dataMC_pileupTauTTIDBtagWPSF_6thJet30/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0NoSel_v13BetterHLTSel/mc/variableHists_v0_looseBaseline_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0NoSel_v13BetterHLTSel/mc/variableHists_v1_looseBaselineBtag2_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0NoSel_v13BetterHLTSel/mc/variableHists_v2_looseBaselineBtag2TTau_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0NoSel_v13BetterHLTSel/mc/variableHists_v3_looseBaselineBtag2TTauHT450_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0NoSel_v13BetterHLTSel/mc/variableHists_v4_looseBaselineBtag2TTauHT500_pileupSF/'
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2022preEE/v0NoSel_v13BetterHLTSel/mc/variableHists_v5_looseBaselineBtag2TTauHT500Jet6_pileupSF/'

    # variables = ['jets_num']
    variables = ['jets_num', 'jets_HT', 'jets_5pt', 'jets_4pt', 'jets_6pt', 'jets_7pt', 'bjetsM_num', 'bjetsM_HT', 'tausT_1decayMode', 'tausT_1pt', 'tausT_1lepton1_charge', 'tausT_1genFlavour']
    # variables = ['jets_HT', 'jets_6pt',  'jets_5pt','jets_4pt', 'jets_num', 'bjetsM_num', 'bjetsT_num', 'tausT_num', 'tausTT_num', 'tausTTT_num','tausM_num', 'tausTT_1lepton1_charge', 'tausTTT_1lepton1_charge', 'tausT_1lepton1_charge', 'tausM_1lepton1_charge', 'tausM_1genFlavour', 'tausT_1genFlavour', 'tausTT_1genFlavour']#1tau1l SR, basic variables
    # variables = ['bjetsM_minDeltaR', 'tausT_1lepton1_deltaR', 'jets_sphericity', 'jets_centrality', 'bjetsM_leptons_minDeltaR', 'jets_rationHT_4toRest', 'jets_minDeltaR', 'jets_METDivideHT', 'jets_average_deltaR', 'jets_aplanarity', 'bjetsM_tausT_minDeltaR', 'bjetsM_3pt', 'bjetsM_invariantMass' ] #BDT input
    # variables = ['jets_HT', 'jets_6pt',  'jets_5pt','jets_num',  'bjetsM_num', 'bjetsT_num', 'tausT_num', 'tausTT_num', 'tausTTT_num','tausT_1genFlavour', 'tausTT_1genFlavour', 'tausTTT_1genFlavour']#1tau0l region 
    # variables = ['jets_HT', 'jets_6pt',  'jets_5pt','jets_num', 'bjetsPTM_num', 'bjetsPTT_num', 'bjetsM_num', 'bjetsT_num', 'tausT_num', 'tausTT_num', 'tausM_num', 'tausTT_1lepton1_charge', 'tausTTT_1lepton1_charge', 'tausT_1lepton1_charge', 'tausM_1lepton1_charge', 'tausM_1genFlavour', 'tausT_1genFlavour', 'tausTT_1genFlavour']
    # variables = ['jets_HT', 'jets_6pt',  'jets_5pt','jets_num', 'bjetsPTM_num', 'bjetsPTT_num', 'bjetsM_num', 'bjetsT_num', 'tausT_num', 'tausTT_num', 'tausM_num',  'tausM_1genFlavour', 'tausT_1genFlavour', 'tausTT_1genFlavour', 'tausT_leptons_charge']#1tau2l
    # variables = ['jets_6pt', 'jets_num', 'bjetsM_num', 'jets_HT']
    # variables = [ 'jets_HT', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', "jets_7pt", 'jets_num',  "jets_bScore", "jets_rationHT_4toRest", "jets_transMass", "jets_average_deltaR", 'jets_1btag', 'jets_2btag', 'jets_3btag', 'jets_4btag', 'jets_5btag', 'jets_6btag', 'PV_npvsGood']
    # variables = [ 'bjetsM_HT', 'bjetsM_MHT', 'bjetsM_minDeltaR', 'bjetsM_invariantMass', 'bjetsM_2pt', 'bjetsM_num', 'bjetsM_1pt', 'muonsTopMVAT_1pt', 'elesTopMVAT_1pt', 'bjetsPTM_num', 'bjetsPTT_num'] #for 1tau1l BDT input
    # variables = ['tausT_num', 'tausF_num', 'tausTT_num', 'tausT_1pt', 'tausF_1pt', 'tausTT_1pt', 'tausT_1decayMode', 'tausF_1decayMode', 'tausTT_1decayMode', 'tausT_1genFlavour', 'tausTT_1genFlavour', 'tausF_1genFlavour', 'tausT_leptonsTopMVA_chargeMulti','tausT_leptonsT_invariantMass', 'tausT_1eta', 'tausTT_1lepton1_charge', 'tausTTT_1lepton1_charge']
    
    # variabless = ['jets_HT', 'jets_MHT', 'jets_invariantMass', 'jets_transMass', 'jets_average_deltaR', 'jets_minDeltaR', 'jets_centrality', 'jets_bScore', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'jets_HTDivideMET', 'jets_']
    regionList = ['1tau1lCR1', '1tau1lCR2']
    # regionList = ['1tau1lCR1', '1tau1lCR2', '1tau1lSR']
    # regionList = ['1tau1lSR']
    # regionList = ['1tau1lSRTest']
    # regionList = ['1tau1lSRTest', '1tau1lCR2']
    # regionList = ['1tau0lSRTest']
    # regionList = ['1tau2lSR']
    # variables = ['BDT']
    # regionList = ['1tau0lSR', '1tau0lMR', '1tau0lVR', '1tau0lCR']
    plotName = 'dataVsMC_v2'
    ifFTau = False
  
    #1tau0l
    # inputDir = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v4cut1tau0l_v75OverlapRemovalFTau/mc/variableHists_v0BDT1tau0l_3bins/'
    # variables = ['tausT_1pt']
    # variables = ['jets_5pt', 'jets_7pt' , 'bjetsM_HT', 'bjetsT_num', 'bjetsT_MHT', 'jets_bScore', 'jets_4largestBscoreSum']
    # variables = ['jets_num', 'jets_HT',  'jets_6pt', 'bjetsM_num', 'tausF_1decayMode',  'tausF_1jetPt', 'tausF_1jetEtaAbs', 'tausF_1prongNum', 'tausF_num']
    # variables = [ 'tausF_prongNum', 'tausF_charge', 'tausF_1decayMode', 'tausL_1ptFRWeight', 'tausL_1etaAbsFRWeight' , 'tausF_1jetPtFRWeight', 'tausF_1eta', 'PV_npvs', 'tausF_1pt', 'jets_HT', 'jets_bScore', 'jets_bScoreMultiply', 'jets_4largestBscoreSum', 'jets_4largestBscoreMulti', 'bjetsM_invariantMass', 'jets_1pt', 'jets_2pt','jets_3pt', 'jets_4pt', 'jets_5pt', 'jets_6pt', 'jets_num', 'bjetsM_num']  
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRNotGen']
    # regionList = ['1tau0lCR', '1tau0lCRGen', '1tau0lCRLTauNotT_Weighted', '1tau0lCRLTauNotTGen_Weighted']
    # regionList = ['1tau0lVR', '1tau0lVRGen', '1tau0lVRLTauNotT_Weighted', '1tau0lVRLTauNotTGen_Weighted'] # new MR
    # regionList = ['1tau0lCRb', '1tau0lCRbGen', '1tau0lCRbLTauNotT_Weighted', '1tau0lCRbLTauNotTGen_Weighted'] # new CR
    # regionList = ['1tau0lCRc', '1tau0lCRcGen', '1tau0lCRcLTauNotT_Weighted', '1tau0lCRcLTauNotTGen_Weighted'] # new VR
    # regionList = ['1tau0lSR', '1tau0lSRGen',  '1tau0lSRLTauNotT_Weighted', '1tau0lSRLTauNotTGen_Weighted']
    # regionList = ['1tau0lCR']
    # regionList = ['1tau0lSR']
    # variables = ['BDT']
    # regionList = ['1tau0lVR', '1tau0lMR', '1tau0lCR', '1tau0lSR']
    # ifFTau = True #if use fakeTau bg and other bg with genTau requirement
    # plotName = 'dataVsMC_fakeTauFromData'

    
    era = uf.getEraFromDir(inputDir)
    print('era=', era)
    isRun3 = uf.isRun3(inputDir)
    inputDirDic = uf.getInputDicNew( inputDir)
    uf.checkMakeDir( inputDirDic['mc']+'results/')
    
    plotNormal(inputDirDic, variables, regionList, plotName, era, isRun3, ifFTau)

    # plotFakeTau(inputDirDic, variables, regionList, plotName, era, isRun3, ifFTau) # for using fakeTau 2 hists application 
   
def plotNormal(inputDirDic, variables, regionList, plotName, era, isRun3, ifFakeTau=False):
    sumProList = ['jetHT','tt', 'ttX', 'singleTop', 'WJets', 'tttt'] #1tau1l
    # sumProList = ['jetHT','qcd','tt', 'ttX', 'singleTop', 'WJets', 'tttt'] 
    # sumProList = ['jetHT','tt', 'tttt'] # run3 1tau1l for now 
    # sumProList = ['jetHT','tt',  'qcd', 'tttt'] # run3 1tau1l for now 
    if ifFakeTau:
        sumProList = ['jetHT', 'fakeTau', 'tt', 'ttX', 'singleTop', 'WJets', 'tttt']
        plotName = plotName + 'fakeTau'
    sumProcessPerVar = uf.getSumHist(inputDirDic, regionList, sumProList, variables, era, isRun3 )#sumProcessPerVar[ivar][region][sumPro]

    plotDir = inputDirDic['mc']+'results/'
    uf.checkMakeDir( plotDir)
    for variable in variables:
        for iRegion in regionList:       
            makeStackPlotNew(sumProcessPerVar[variable][iRegion], sumProList, variable, iRegion, plotDir, False, plotName, era, True, 100 ) 
            # makeStackPlotNew(sumProcessPerVar[variable][iRegion], sumProList, variable, iRegion, plotDir, False, plotName, era, True, 10) 
            # makeStackPlotNew(sumProcessPerVar[variable][iRegion], sumProList, variable, iRegion, plotDir, False, plotName, era, True, 1000 ) 
            # makeStackPlotNew(sumProcessPerVar[variable][iRegion], sumProList, variable, iRegion, plotDir, False, plotName, era, True, 10, True, True) 
    
   
       
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
                

#moved to 1tau0l plotting
# def appendSYSRegions( ifFR_sys, regionList) :
#     if ifFR_sys:
#         regionList.append(regionList[2]+'_up')
#         regionList.append(regionList[2]+'_down')
#         regionList.append(regionList[3]+'_up')
#         regionList.append(regionList[3]+'_down')
#     return regionList 
 
 
        
def checkHists( histsDict ):
    for ikey in histsDict.keys():
        print('iProcess: ', ikey )
        histsDict[ikey].Print()


def makeStackPlotNew(nominal, legendOrder, name, region, outDir, ifFakeTau, savePost = "", era='2016', includeDataInStack=True, signalScale = 1000, ifStackSignal = False, ifLogy=False, ifPrint=False):
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
    canvy = TCanvas( canvasName, canvasName, 1000,1000)
    
    #it seems text size  is scaled to pad size
    upPad = TPad('up', 'up', 0, 0., 1, 1)
    downPad = TPad('down', 'down', 0., 0, 1, 1)
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

    ifBlind = True if 'SR' in region else False #!!!
    dataHist, systsUp, systsDown, sumHist, stack, signal = getHists(nominal, legendOrder, ifBlind, False, ifStackSignal)

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
    signal.SetLineColor(kBlue)
    signal.SetLineStyle(kSolid)
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
    leggy = addLegend(canvy, nominal, legendOrder, dataHist, assymErrorPlot, signal, signalScale, ifLogy)
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
    latex = TLatex()
    latex.SetTextSize(0.03)
    latex.SetTextAlign(22)  # 
    
    sig = signal.GetBinContent(signal.GetNbinsX())
    bg = sumHist.GetBinContent(sumHist.GetNbinsX())
    
    latex.DrawLatex(signal.GetBinCenter(signal.GetNbinsX()), sig+bg+0.05, f"S={sig:.2f}, B={bg-sig:.2f}")
    
    canvas.Update()
    canvas.Draw()

 
def addLegend(canvy, nominal, legendOrder, dataHist, assymErrorPlot, signal, signalScale, ifLogy=False):
    # x1,y1,x2,y2 are the coordinates of the Legend in the current pad (in normalised coordinates by default)
    canvy.cd()
    leggy = st.getMyLegend(0.18,0.75,0.89,0.90)
    # for ipro in nominal.keys():
    for ipro in legendOrder:
        if ipro == 'jetHT' :
            if dataHist:
                leggy.AddEntry(dataHist,"Data[{:.1f}]".format(getIntegral(dataHist)),"epl")
        elif ipro == 'tttt':
            signalEntry = 'tttt*{}[{:.1f}*{}]'.format(signalScale, getIntegral(nominal['tttt']), signalScale)
            leggy.AddEntry( signal, signalEntry, 'l')
            if ifLogy:
                legText = '{}[{:.1f}]'.format(ipro, getIntegral(nominal[ipro]))
                leggy.AddEntry(nominal[ipro], legText,"f")
        else:
            legText = '{}[{:.1f}]'.format(ipro, getIntegral(nominal[ipro]))
            leggy.AddEntry(nominal[ipro], legText,"f")
        
    leggy.AddEntry(assymErrorPlot,"Stat. unc","f")
    
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
    sumHistoData.SetMinimum(0.5)
    # sumHistoData.SetMaximum(1.2)
    sumHistoData.SetMaximum(1.5)
    # sumHistoData.GetXaxis().SetTitle(dataHist.GetTitle())
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
    if "jetHT" in nominal.keys():
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
    
def getHists(nominal,  legendOrder, ifBlind, doSystmatic, ifStackSignal = False):
    #here we get dataHist and add all MC for sumHist    
    keyList = list(nominal.keys()) #process list; nominal[iprocess]=hist
    colourPerSample = {
        'tttt':kBlue,
        'tt': TColor.GetColor("#f03b20"),
        'qcd': TColor.GetColor("#ffeda0"),
        'ttX': TColor.GetColor("#fc9272"),
        'singleTop': TColor.GetColor("#91bfdb"),
        'VV': TColor.GetColor("#edf8b1"),
        'WJets': TColor.GetColor("#998ec3"),
        # 'fakeTau': TColor.GetColor("#ffeda0"),
        'fakeTau': TColor.GetColor("#fec44f"),
    }
    
    sumHist = nominal[keyList[0]].Clone()
    sumHist.Reset()
    systsUp = nominal[keyList[0]].Clone("systsUp")
    systsUp.Reset()
    systsDown = nominal[keyList[0]].Clone("systsDown")
    systsDown.Reset()
    dataHist = 0
    stack = THStack( 'stack', 'stack' )
    legendOrder.reverse()
    for i in legendOrder:
        # i is i summed MC
        if i == 'jetHT':
            if not ifBlind:
                dataHist = nominal["jetHT"].Clone()
                dataHist.SetMarkerStyle(20)
                dataHist.SetMarkerSize(1.2)
                dataHist.SetMarkerColor(kBlack)
                dataHist.SetLineColor(kBlack)
                dataHist.SetTitleSize(0.0)
            continue
        # if i == 'tttt' or i=='singleMu':
        if i == 'singleMu':
            continue
        if i == 'tttt' and (not ifStackSignal):
            continue
        nominal[i].SetFillColor(colourPerSample[i])
        nominal[i].SetLineColor(kBlack)
        nominal[i].SetLineWidth(1)
        nominal[i].GetXaxis().SetTitleSize(0.01)
        nominal[i].GetXaxis().SetLabelSize(0.0)
        nominal[i].GetYaxis().SetTitle('Events')
        sumHist.Add(nominal[i]) #sumHist is all bg
        stack.Add(nominal[i])
        # if doSystmatic and  systHists[i]:
        #     print('cal sys for: ', i)
        #     tempUp,tempDown = getSystVariation(nominal[i],systHists[i] )
        #     systsUp.Add(tempUp) #adding various processes, 
        #     systsDown.Add(tempDown)
            
    legendOrder.reverse()
    
    #scale tttt
    if 'tttt' in nominal.keys():
        signal = nominal['tttt'].Clone()
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
    errors = TGraphAsymmErrors(xAxis.GetNbins(),x,y,exl,exh,eyl,eyh)
    
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
    #systHi is 'up' or 'down' for varias sources
    #so this is to sum the sytstmatic variation for sources of systematic uncertainty
        print( 'doing sytematic calculation for: ',systHi )
        # if "bTag" in systHi: continue
        syst = systHists[systHi].Clone()
        syst.Add(nominalHist,-1)
        # syst.Divide(nominalHist)
        for i in range(1,syst.GetXaxis().GetNbins()+1):
            if "up" in syst.GetName():
                # print( 'sytHistUp: ', systHistUp.GetBinContent() )
                systHistUp.SetBinContent(i,systHistUp.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
            else:
                systHistDown.SetBinContent(i,systHistDown.GetBinContent(i)+(syst.GetBinContent(i) * syst.GetBinContent(i)))
    # for i in range(1,systHistUp.GetXaxis().GetNbins()+1):
        # systHistUp.SetBinContent(i,(math.sqrt(systHistUp.GetBinContent(i)))*nominalHist.GetBinContent(i))
        # systHistDown.SetBinContent(i,(math.sqrt(systHistDown.GetBinContent(i)))*nominalHist.GetBinContent(i))
        #no need to divide and multiply

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
