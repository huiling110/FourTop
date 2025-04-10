import os
import ROOT
import usefulFunc as uf
import ttttGlobleQuantity as gq

MCSys = {
    #sys: [isCorrelated, whichProces, channelBits, isCorrelatedProcess] ; whichProcess=0: mc; whichProcess=1: fakeTau, whichProcess=2: fakeLepton
    #!Channlebits information for each channel, bit 100:1tau1l; bit 010:1tau0l; bit 001: 1tau2l
    #: if the systematic is correlated between processes
    'CMS_pileup': [True, 0, 0b111 , True],
    # 'CMS_prefiring': [False, 0, 0b111, True],
    'CMS_l1_ecal_prefiring': [False, 0, 0b111, True],
    
    'CMS_tttt_tau_eff_hlt_stats': [False, 0, 0b110, True],
    'CMS_tttt_SS_eff_hltLep': [False, 0, 0b001, True],
    
    'CMS_eff_t_vsMu': [False, 0, 0b111, True], #uncorrelated
    'CMS_eff_t_vsEle': [False, 0, 0b111, True], #need to add era to the name
    'CMS_eff_t_vsJet_stat1_dm0': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat1_dm1': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat1_dm10': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat1_dm11': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat2_dm0': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat2_dm1': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat2_dm10': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_stat2_dm11': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_syst_alleras': [True, 0, 0b111, True],
    'CMS_eff_t_vsJet_syst': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_syst_dm0': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_syst_dm1': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_syst_dm10': [False, 0, 0b111, True],
    'CMS_eff_t_vsJet_syst_dm11': [False, 0, 0b111, True],
    
    'CMS_tttt_SS_eff_e_syst': [True, 0, 0b101, True],
    'CMS_tttt_SS_eff_m_syst': [True, 0, 0b101, True],
    'CMS_tttt_SS_eff_e_stat': [False, 0, 0b101, True],
    'CMS_tttt_SS_eff_m_stat': [False, 0, 0b101, True],
    'CMS_eff_e_reco': [False, 0, 0b101, True],
    
    #!btagWP for 1tau1l and 1tau2l
    'CMS_btag_fixedWP_comb_bc_correlated': [True, 0, 0b101, True],
    'CMS_btag_fixedWP_comb_bc_uncorrelated': [False, 0, 0b101, True],
    # 'CMS_btag_fixedWP_incl_light_correlated': [True, 0, 0b101, True], #!!!
    # 'CMS_btag_fixedWP_incl_light_uncorrelated': [False, 0, 0b101, True],
    
    #btagShape information, only in 1tau0l
    'CMS_btag_shape_hf': [True, 0, 0b010, True], 
    'CMS_btag_shape_lf': [True, 0, 0b010, True],
    'CMS_btag_shape_cferr1': [True, 0, 0b010, True],
    'CMS_btag_shape_cferr2': [True, 0, 0b010, True],
    'CMS_btag_shape_hfstats1': [False, 0, 0b010, True],
    'CMS_btag_shape_hfstats2': [False, 0, 0b010, True],
    'CMS_btag_shape_lfstats1': [False, 0, 0b010, True],
    'CMS_btag_shape_lfstats2': [False, 0, 0b010, True],
   
    # 'CMS_tau_FR': [False, 1, 0b010, True],
    'CMS_fake_t': [False, 1, 0b010, True], #!considering FR for 1tau0l
    # 'CMS_tau_FR': [False, 1, 0b111, True],#!Considering FR for 1tau1l and 1tau2l too
    
    'pdf_alphas': [True, 0, 0b111, True], #!not considering for singleTop 
    'pdf': [True, 0, 0b111, True],
    'QCDscale_ren': [True, 0, 0b111, False],   #!not in data/MC
    'QCDscale_fac': [True, 0, 0b111, False],  
    'ps_isr': [True, 0, 0b111, False],
    'ps_fsr': [True, 0, 0b111, True],
   
    #JES https://docs.google.com/spreadsheets/d/1JZfk78_9SD225bcUuTWVo4i02vwI5FfeVKH-dwzUdhM/edit?gid=1345121349#gid=1345121349 
    # "CMS_JES_AbsoluteMPFBias_AK4PFchs": [True, 0, 0b111, True], 
    # "CMS_JES_AbsoluteScale_AK4PFchs": [True, 0, 0b111, True],
    # "CMS_JES_AbsoluteStat_AK4PFchs": [False, 0, 0b111, True],
    # "CMS_JES_FlavorQCD_AK4PFchs": [True, 0, 0b111, True],
    # "CMS_JES_Fragmentation_AK4PFchs": [True, 0, 0b111, True], 
    # "CMS_JES_PileUpDataMC_AK4PFchs": [True, 0, 0b111, True],
    # "CMS_JES_PileUpPtBB_AK4PFchs": [True, 0, 0b111, True],
    # "CMS_JES_PileUpPtEC1_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_PileUpPtEC2_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_PileUpPtHF_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_PileUpPtRef_AK4PFchs": [ True, 0, 0b111, True],
    # "CMS_JES_RelativeFSR_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_RelativeJEREC1_AK4PFchs":  [False, 0, 0b111, True],
    # "CMS_JES_RelativeJEREC2_AK4PFchs": [False, 0, 0b111, True],
    # "CMS_JES_RelativeJERHF_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_RelativePtBB_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_RelativePtEC1_AK4PFchs": [False, 0, 0b111, True],
    # "CMS_JES_RelativePtEC2_AK4PFchs": [False, 0, 0b111, True],
    # "CMS_JES_RelativePtHF_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_RelativeBal_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_RelativeSample_AK4PFchs":  [False, 0, 0b111, True],
    # "CMS_JES_RelativeStatEC_AK4PFchs":  [False, 0, 0b111, True],
    # "CMS_JES_RelativeStatFSR_AK4PFchs":  [False, 0, 0b111, True],
    # "CMS_JES_RelativeStatHF_AK4PFchs":  [False, 0, 0b111, True],
    # "CMS_JES_SinglePionECAL_AK4PFchs":  [True, 0, 0b111, True],
    # "CMS_JES_SinglePionHCAL_AK4PFchs": [True, 0, 0b111, True],
    # "CMS_JES_TimePtEta_AK4PFchs": [True, 0, 0b111, True],
 
    # "CMS_JER": [False, 0, 0b111 , True],
 
    # 'CMS_tau_TES_dm0': [False, 0, 0b111, True],
    # 'CMS_tau_TES_dm1': [False, 0, 0b111, True],
    # 'CMS_tau_TES_dm10': [False, 0, 0b111, True],
    # 'CMS_tau_TES_dm11': [False, 0, 0b111, True],
    
    # 'CMS_MET_unclusteredEnergy': [False, 0, 0b111, True],
    # 'CMS_e_scale': [False, 0, 0b001, True],
    
}


# outVersion = 'v3BasicAndJES'
# outVersion = 'v4BasicAndJESJER'
# outVersion = 'v6AllSys'
outVersion = 'v0basic'
# outVersion = 'v6AllSysWithFR'

def main():
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadroV2_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v90MuonESHadroPre/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v91TESAddedHadroPre/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v93HadroPreJetVetoPileupID/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1l/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/templatesForCombine1tau1l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lFakeTau/combine/templatesForCombine1tau1l.root'
    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v1baselineHadroBtagWeightAdded_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau1lAddMCFakeT/combine/templatesForCombine1tau1l_new.root'
    channel = '1tau1l'
   
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v86HadroPreSelWithTTWTTZNLO/mc/variableHists_v2BDT1tau0lBinC/combine/templatesForCombine1tau0l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHardro_v88PSWeightFixedHadroPre/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
    # channel = '1tau0l'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineHadro_v94HadroPreJetVetoHemOnly/mc/variableHists_v0BDT1tau0l/combine/templatesForCombine1tau0l.root'

    #!!!1tau2l
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87LepPreSel_GammaRemovalBugFixed/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87addPdfPSWeightSum/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v87addPdfPSWeightSum/mc/variableHists_v0BDT1tau2l_newMCSample/combine/templatesForCombine1tau2l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l_newMCSample/combine/templatesForCombine1tau2l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
#    inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v88PSWeightFixedLepPre/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # inputTemplate ='/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLepTriggerSF_v91TESAddedLepPre/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2l/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2017/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016preVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/templatesForCombine1tau2l.root'
    # inputTemplate = '/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2016postVFP/v0baselineLep_v94LepPreJetVetoHemOnly/mc/variableHists_v0BDT1tau2lFakeTau/combine/templatesForCombine1tau2l.root'
    # channel = '1tau2l'



   
   
    inputDir = os.path.dirname(inputTemplate) 
    outDir = f"{inputDir}/datacardSys_{outVersion}/"
    uf.checkMakeDir(outDir)
    outCard = f"{outDir}datacard_{channel}.txt"
    era = uf.getEraFromDir(inputTemplate) 
    
    processes = gq.proChannelDic_forCombine[channel]
    if channel== '1tau2l':
        processes.remove('leptonSum')
        processes.remove('Minor')
        # if era == '2016postVFP':
        #     processes.remove('singleTop')#!!!
    else: 
        processes.remove('jetHT')  
    print(processes)
    
    remove0Process(processes, inputTemplate, channel)
    
    era = uf.getEraFromDir(inputTemplate) 
    sysDic = getSysDic(processes, channel, era) 
    print(sysDic, '\n')
    #sysDic
    
    addLumi(sysDic, era, processes)
    addProcessNormalization(sysDic, processes)#!to be done
    
    for i, iv in sysDic.items():
        print(i, iv)
        
    write_shape_datacard(outCard, inputTemplate, channel, processes,  sysDic, era) 
    
    
def remove0Process(processes, inputTemplate, channel):
    rootFile = ROOT.TFile(inputTemplate, "READ")
    for ipro in processes:
        histName = f"{ipro}_{channel}SR_BDT"
        hist = rootFile.Get(histName)
        if hist == None:
            print('hist is None:', histName)
        else: 
            if hist.Integral() < 0.00000001:
                print(f"remove {ipro} process")
                processes.remove(ipro) 
    
    rootFile.Close() 
   
def addProcessNormalization(sysDic, processes):
    proNormalDic = {
       'tttt':  0.1,
       'tt': 0.05,#https://twiki.cern.ch/twiki/bin/view/LHCPhysics/TtbarNNLO
    #    'ttX' : 0.11,
       'singleTop': 0.2,
       'WJets': 0.1,
       'Minor': 0.2, 
       'ttZ': 0.119,
       'ttW': 0.102,
       'ttH': 0.084,
    #    'ttG': 0.005,
        
    }
    for ipro, inorm in proNormalDic.items():
        sysDic[f"norm_{ipro}"] = []
        sysDic[f"norm_{ipro}"].append("lnN")
        proDic = {}
        for ipro2 in processes:
            if ipro2 == ipro:
                proDic[ipro2] = 1+inorm
            else:
                proDic[ipro2] = 0
        sysDic[f"norm_{ipro}"].append(proDic)
    
    #add FR uncertainty for fakeLepton 
    sysDic['norm_fakeLepton_sys'] = []
    sysDic['norm_fakeLepton_sys'].append("lnN")
    sysDic['norm_fakeLepton_stats'] = []
    sysDic['norm_fakeLepton_stats'].append("lnN")
    proDic = {}
    for ipro in processes:
        if ipro == 'fakeLepton':
            proDic[ipro] = 1.2
        else:
            proDic[ipro] = 0
    sysDic['norm_fakeLepton_sys'].append(proDic)
    sysDic['norm_fakeLepton_stats'].append(proDic)
            
    
                
                

def addLumi(sysDic, era, processes):
    sysDic['lumi_13TeV'] = [] # correlated 3 years
    sysDic[f'lumi_13TeV_{era}'] = []
    sysDic['lumi_13TeV_20172018'] = []
    sysDic['lumi_13TeV'].append("lnN")
    sysDic[f'lumi_13TeV_{era}'].append("lnN")
    sysDic['lumi_13TeV_20172018'].append("lnN")
     
    lumiMap = {
        #[uncorrelated, correlated 3 years, correlated 2017 and 2018]
        '2016preVFP': [1.01, 1.006, 0] , '2016postVFP': [1.01, 1.006, 0], '2017': [1.02, 1.009, 1.006], '2018': [1.015, 1.02, 1.002]}
    iDicCorrelated = {}
    iDicUncorrelated = {}
    iDic20172018 = {}
    for ipro in processes:
        if ipro == 'fakeTau' or ipro == 'fakeLepton': 
            iDicCorrelated[ipro] = 0 
            iDicUncorrelated[ipro] = 0
            iDic20172018[ipro] = 0
        else:
            iDicCorrelated[ipro] = lumiMap[era][1]
            iDicUncorrelated[ipro] = lumiMap[era][0]
            iDic20172018[ipro] = lumiMap[era][2] 
    
    sysDic['lumi_13TeV'].append(iDicCorrelated)
    sysDic[f'lumi_13TeV_{era}'].append(iDicUncorrelated)
    sysDic['lumi_13TeV_20172018'].append(iDic20172018)        
            
             
              

def getSysDic(processes, channel, era, ifForPlot=False):
    #return: pdf_normalised ['shape', {'tt': 1, 'ttX': 1, 'fakeLepton': 0, 'singleTop': 1, 'Minor': 1, 'tttt': 1}]
    #ifForPlot: not decorrelate systematic for different processes
    sysDic = {}
    for sys, sysList in MCSys.items():
        # sysName = sys if sysList[0] else f"{sys}_{era}"
        sysPre = sys if sysList[0] else f"{sys}_{era}"
        if not sysList[3] and sysList[1]==0: #!if systematic is correlated between processes
            if ifForPlot:
                sysName = [sysPre]
            else:
                sysName = [f"{sysPre}_{ipro}" for ipro in processes if not 'fake' in ipro]
        else:
            sysName = [sysPre]
        for isys in sysName:
            sysDic[isys] = []
            sysDic[isys].append("shape")
            proSysDic = getProSysDic(isys, sysList, processes, channel, ifForPlot)
            sysDic[isys].append(proSysDic)
            
    return  sysDic
     
def getProSysDic(sys, sysList, processes, channe='1tau1l', ifCombine=False):
    #return porSys: {'tt': 1, 'ttX': 1, 'fakeLepton': 0, 'singleTop': 1, 'Minor': 1, 'tttt': 1}
    if channe=='1tau1l':
        channeMask = 0b100
    elif channe=='1tau0l':
        channeMask = 0b010
    elif channe=='1tau2l':
        channeMask = 0b001
    
    proSys = {}
    for ipro in processes:
        if uf.isData(ipro) : continue
            
        if ipro=='fakeTau':
            proSys[ipro] = 1 if sysList[1]==1 and ((sysList[2]&channeMask) !=0) else 0
        elif ipro=='fakeLepton':
            proSys[ipro] = 1 if sysList[1]==2 and ((sysList[2]&channeMask) !=0) else 0
        elif ipro=='Minor' :#!!!not considering anys systematic for Minor processes
            proSys[ipro] = 0
        else: 
            if not sysList[3] : # process uncorrelated systematic
                if not ifCombine:
                    proName = sys.split('_')[-1]
                    proSys[ipro] = 1 if sysList[1]==0 and (sysList[2] &(channeMask)!=0) and ipro == proName else 0
                else:
                    proSys[ipro] = 1 if sysList[1]==0 and (sysList[2] &(channeMask)!=0) else 0
            else:
                proSys[ipro] = 1 if sysList[1]==0 and (sysList[2] &(channeMask)!=0) else 0
            if ipro=='singleTop' and (sys=='pdfAlphaS_normalised' or sys=='pdf_normalised' or sys=='QCDscale_Re_normalised' or sys=='QCDscale_Fa_normalised' or sys=='ISR_normalised' or sys=='FSR_normalised'):
                proSys[ipro] = 0
            if ipro=='singleTop' and (channe=='1tau2l'):
                proSys[ipro] = 0 
        
        #set 
             
    return proSys            
             
   
def write_shape_datacard(output_file, root_file, channel_name, processes,  systematics, era='2018'):
    """
    Write a shape datacard for CMS Combine.

    Parameters:
    - output_file: Name of the text file to write the datacard to.
    - root_file: Name of the ROOT file containing histograms.
    - channel_name: Name of the analysis channel.
    - processes: List of process names (e.g., ["signal", "background1", "background2"]).
    - rates: List of initial expected rates for each process.
    - systematics: Dictionary of systematic uncertainties structured as:
      { "uncertainty_name": (type, { "process_name": ("up_modifier", "down_modifier") }) }
      Example: { "lumi": ("lnN", {"background1": (1.10, 0.90) }) }
    """

    num_processes = len(processes)
    # signal_index = -1  # Assuming the first process is the signal
    signal_index = processes.index('tttt')
    
    process_col_width = 52
    value_col_width = 22
    channelNameName = f"SR{channel_name}_{era}"
    
    rates = f"rate".ljust(process_col_width)
    proString = f"process".ljust(process_col_width)
    binString = f"bin".ljust(process_col_width)
    lines = [
        "imax 1  number of channels",
        "jmax {}  number of background processes".format(num_processes - 1),
        "kmax *  number of nuisance parameters (sources of systematic uncertainties)",
        "---------------",
        f"shapes * {channelNameName} {root_file} $PROCESS_{channel_name}SR_BDT $PROCESS_{channel_name}SR_$SYSTEMATIC_BDT",
        "---------------",
        f"bin         {channelNameName}",
        "observation -1",
        "---------------",
        f"{binString}{''.join([channelNameName.ljust(value_col_width) for _ in range(num_processes)])}",
        f"{proString}{''.join([proc.ljust(value_col_width) for proc in processes])}",
        f"{proString}{''.join([str(signal_index-i).ljust(value_col_width) for i in range(num_processes)])}",
        f"{rates}{''.join(['-1'.ljust(value_col_width) for i in range(num_processes)])}" ,
        
        "---------------"
    ]

    for unc_name, (unc_type, uncertainties) in systematics.items():
        line = f"{unc_name} {unc_type}".ljust(process_col_width)
        ilist = []
        for proc in processes:
           iuncer = uncertainties[proc] if not uncertainties[proc]==0 else '-'
        #    print(type(iuncer))
           ilist.append(f"{iuncer}".ljust(value_col_width))
        line += " ".join(
            ilist
            # f"{uncertainties[proc][0]:.3f}/{uncertainties[proc][1]:.3f}" if proc in uncertainties else "-"
            # for proc in processes
            # f"{uncertainties[proc]}" if proc in uncertainties else "-"
            # for proc in processes
        )
        # print(line)
        lines.append(line)
        
    # Add MC statistical uncertainties
    lines.append("---------------")
    lines.append(f"{channelNameName} autoMCStats 10 0 1")

    # Write to file
    with open(output_file, 'w') as f:
        for line in lines:
            f.write(line + "\n")
    print(f"Datacard written to {output_file}")

if __name__=='__main__':
    main()