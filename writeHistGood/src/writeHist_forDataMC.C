/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2023-06-06 21:01:27
 * @modify date 2023-06-23 23:19:32
 * @desc [description]
 */
#include <iostream>

#include "../include/writeHist_forDataMC.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/commenSelectionAndWeight.h"
// #include "../include/histsForRegionsMap_value.h"

void WH_forDataMC::Init()
{
    std::cout << "Start to initilation....................................................\n";

    // regions for hists
    // std::vector<TString> regionsForVariables = {"1tau0lSR",  "1tau0lVR", "1tau0lCR", "1tau0lMR",  "1tau0lCRMR","1tau1lCR1", "1tau1lCR2", "1tau1lSR", "baseline", "1tau1lCR3", "1tau1lCR12", "1tau2lSR", "1tau2lCR3"};
    // std::vector<TString> regionsForVariables = {"1tau0lSR",  "1tau0lVR", "1tau0lCR", "1tau0lMR",  "1tau0lCRMR","1tau1lCR1", "1tau1lCR2", "1tau1lSR", "baseline", "1tau1lCR12", "1tau2lSR", "1tau2lCR3"};
    std::vector<TString> regionsForVariables;
    if(m_is1tau2l){
        regionsForVariables = {"1tau2lSR", "1tau2lCR3"};
    }else{
        regionsForVariables = {"1tau0lSR",  "1tau0lVR", "1tau0lCRMR", "1tau1lSR", "1tau1lCR12"};
    }

    //regions for FR uncertainty for 1tau0l
    if(m_ifSys){
        std::vector<TString> sysRegions_sys;
        for(auto region: regionsForVariables){
            WH::getChannelSys(sysRegions_sys, region, m_era);
        }
        WH::initializeHistVec(sysRegions_sys, histsForRegion_vec, m_processName, e);
    }else{
        WH::initializeHistVec(regionsForVariables, histsForRegion_vec, m_processName, e);
    }

    WH::histRegionsVectSetDir(histsForRegion_vec, m_outFile);

    if(m_ifSys){
        if(m_isFakeLepton || m_isFakeTau || m_isData){
            m_scaleRe_normUp_SF = 1;
            m_scaleRe_normDown_SF = 1;
            m_scaleFa_normUp_SF = 1;
            m_scaleFa_normDown_SF = 1;
            m_pdfAlphaS_normUp_SF = 1;
            m_pdfAlphaS_normDown_SF = 1;
        }else{
            m_scaleRe_normUp_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 7);
            m_scaleRe_normDown_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 1);
            m_scaleFa_normUp_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 5);
            m_scaleFa_normDown_SF = WH::calQCDScaleNor(m_inputDir + m_processName + ".root", 3);
            m_pdfAlphaS_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 0);//!inf big for singleTop process
            m_pdfAlphaS_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 1);
            m_pdf_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 2);
            m_pdf_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 3);
            m_PSWeightISR_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 4);
            m_PSWeightISR_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 5);
            m_PSWeightFSR_normUp_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 6);
            m_PSWeightFSR_normDown_SF = WH::calPDFScaleNor(m_inputDir + m_processName + ".root", 7);
        }
    }


    std::cout << "Done initializing\n";
    std::cout << "\n";
}

void WH_forDataMC::LoopTree(UInt_t entry)
{
    Long64_t allEvent = m_tree->GetEntries();
    std::cout << "Start to loop tree of entries: "<<allEvent<<"\n";
    if (entry > 0)
    {
        allEvent = entry;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        const Bool_t ifBaseline = baselineSelection(e, m_isRun3, m_is1tau2l); 
        if (!ifBaseline)
        {
            continue;
        }

        // Double_t    basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight_new.v() * e->musTopMVAT_weight_new.v()* e->btagWPMT_weight.v() *e->elesTopMVAT_reoSF_weight.v();//!!!without HLT weight
        const Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData, 0, m_isFakeTau, m_isFakeLepton);//!1tau1l
        const Double_t eventWeight_1tau2l = baseWeightCal(e, i, m_isRun3, m_isData, 2, m_isFakeTau, m_isFakeLepton);
        const Double_t eventWeight_1tau0l = baseWeightCal(e, i, m_isRun3, m_isData, 1, m_isFakeTau, m_isFakeLepton);//!1tau0l
        //!!!Some FR_weight_final == inf for fakeTau_MC, temporary fix here
        // if (std::isnan(eventWeight_1tau0l)|| std::isinf(eventWeight_1tau0l)){
        //     std::cout<<"!!!! FR_weight_final is NAN\n";
        //     continue;
        // }

        // if(std::isinf(e->btagWPMT_weight.v()) || std::isnan(e->btagWPMT_weight.v())){
        //     std::cout<<"btagWPMT_weight="<<e->btagWPMT_weight.v()<<"\n";
        // }//!!!todo: handle this in MV

        // SR
        if (!m_isData)
        {   
            if(!m_is1tau2l){
                Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
                Bool_t is1tau1lSR = SR1tau1lSel(e, 0, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE); //!m_isData = isMC
                // WH::histRegionVectFill(histsForRegion_vec, is1tau0lSR, "1tau0lSR", eventWeight_1tau0l, m_isData);
                // WH::histRegionVectFill(histsForRegion_vec, is1tau1lSR, "1tau1lSR", basicWeight, m_isData);
                // WH::histRegionVectFill(histsForRegion_vec, is1tau2lSRTest, "1tau2lSR", eventWeight_1tau2l, m_isData);
                fillHistVec("1tau0lSR", is1tau0lSR, eventWeight_1tau0l);
                fillHistVec("1tau1lSR", is1tau1lSR, basicWeight);
            }else{
                Bool_t is1tau2lSRTest = SR1tau1lSel(e, 2, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData);
                fillHistVec("1tau2lSR", is1tau2lSRTest, eventWeight_1tau2l);
            }
        }

        if(!m_is1tau2l){
        // 1tau0l CR
        Bool_t is1tau0lMR = SR1tau1lSel(e, 7, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
        Bool_t is1tau0lVR = SR1tau1lSel(e, 8, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
        Bool_t is1tau0lCR = SR1tau1lSel(e, 9, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, m_ifFakeTau);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau0lMR, "1tau0lMR", eventWeight_1tau0l, m_isData);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lVR", eventWeight_1tau0l, m_isData);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR, "1tau0lCR", eventWeight_1tau0l, m_isData);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR||is1tau0lMR, "1tau0lCRMR", eventWeight_1tau0l, m_isData);
        // fillHistVec("1tau0lMR", is1tau0lMR, eventWeight_1tau0l);
        fillHistVec("1tau0lVR", is1tau0lVR, eventWeight_1tau0l);
        // fillHistVec("1tau0lCR", is1tau0lCR, eventWeight_1tau0l);
        fillHistVec("1tau0lCRMR", is1tau0lCR||is1tau0lMR, eventWeight_1tau0l);

        // 1tau1lCR
        Bool_t is1tau1lCR1 = SR1tau1lSel(e, 5, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData); 
        Bool_t is1tau1lCR2 = SR1tau1lSel(e, 4, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData); 
        // WH::histRegionVectFill(histsForRegion_vec, is1tau1lCR1, "1tau1lCR1", basicWeight, m_isData);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau1lCR2, "1tau1lCR2", basicWeight, m_isData);
        //1tau1lCR1+CR2
        // Bool_t is1tau0lSRTest = SR1tau1lSel(e, 3, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE); 
        Bool_t is1tau1lCR12 = SR1tau1lSel(e, 3, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE); 
        // WH::histRegionVectFill(histsForRegion_vec, is1tau0lSRTest, "1tau1lCR12", basicWeight, m_isData);
        Bool_t is1tau1lSRL = SR1tau1lSel(e, 11, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau1lSRL, "1tau1lCR3", basicWeight, m_isData);
        fillHistVec("1tau1lCR12", is1tau1lCR12, basicWeight);

        }else{

        //1tau2l CR3
        Bool_t is1tau2lCR3 = SR1tau1lSel(e, 12, m_isRun3, m_isFakeTau, m_isFakeLepton, !m_isData, kFALSE);
        // WH::histRegionVectFill(histsForRegion_vec, is1tau2lCR3, "1tau2lCR3", eventWeight_1tau2l, m_isData);
        fillHistVec("1tau2lCR3", is1tau2lCR3, eventWeight_1tau2l);
        }

    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void WH_forDataMC::fillHistVec(TString region, Bool_t ifBaseline, Double_t basicWeight){
    // WH::histRegionVectFill(histsForRegion_vec, ifBaseline, "baseline", basicWeight, m_isData);
    WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region, basicWeight, m_isData);
    if(m_ifSys){
        if(!(m_isFakeLepton|| m_isFakeTau || m_isData)){

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_pileupUp", (basicWeight/e->PUweight_.v())*e->PUweight_up_.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_pileupDown", (basicWeight/e->PUweight_.v())*e->PUweight_down_.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_prefiring_" + m_era + "Up", (basicWeight/e->EVENT_prefireWeight.v())*e->EVENT_prefireWeight_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_prefiring_" + m_era + "Down", (basicWeight/e->EVENT_prefireWeight.v())*e->EVENT_prefireWeight_down.v(), m_isData);

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_vsjet_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_vsjet_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsMu_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_vsmu_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsMu_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_vsmu_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsEle_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_vsele_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsEle_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_vsele_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm0_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm0_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm0_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm0_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm1_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm1_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm1_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm1_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm10_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm10_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm10_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm10_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm11_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm11_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat1_dm11_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat1_dm11_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm0_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm0_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm0_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm0_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm1_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm1_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm1_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm1_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm10_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm10_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm10_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm10_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm11_" + m_era + "Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm11_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_stat2_dm11_" + m_era + "Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_stat2_dm11_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_allerasUp", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_alleras_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_allerasDown", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_alleras_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_"+m_era+"Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_"+m_era+"Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm0_"+m_era+"Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm0_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm0_"+m_era+"Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm0_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm1_"+m_era+"Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm1_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm1_"+m_era+"Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm1_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm10_"+m_era+"Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm10_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm10_"+m_era+"Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm10_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm11_"+m_era+"Up", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm11_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_t_vsJet_syst_dm11_"+m_era+"Down", (basicWeight/e->tauT_IDSF_weight_new.v())*e->tauT_IDSF_weight_new_syst_era_dm11_down.v(), m_isData);

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_e_systUp", (basicWeight/e->elesTopMVAT_weight_new.v())*e->elesTopMVAT_weight_sys_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_e_systDown", (basicWeight/e->elesTopMVAT_weight_new.v())*e->elesTopMVAT_weight_sys_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_m_systUp", (basicWeight/e->musTopMVAT_weight_new.v())*e->musTopMVAT_weight_sys_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_m_systDown", (basicWeight/e->musTopMVAT_weight_new.v())*e->musTopMVAT_weight_sys_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_m_stat_"+m_era+"Up", (basicWeight/e->musTopMVAT_weight_new.v())*e->musTopMVAT_weight_stat_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_m_stat_"+m_era+"Down", (basicWeight/e->musTopMVAT_weight_new.v())*e->musTopMVAT_weight_stat_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_e_stat_"+m_era+"Up", (basicWeight/e->elesTopMVAT_weight_new.v())*e->elesTopMVAT_weight_stat_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_e_stat_"+m_era+"Down", (basicWeight/e->elesTopMVAT_weight_new.v())*e->elesTopMVAT_weight_stat_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_e_Reco_"+m_era+"Up", (basicWeight/e->elesTopMVAT_reoSF_weight.v())*e->elesTopMVAT_reoSF_weight_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_e_Reco_"+m_era+"Down", (basicWeight/e->elesTopMVAT_reoSF_weight.v())*e->elesTopMVAT_reoSF_weight_down.v(), m_isData);

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_jesUp", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_jes_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_jesDown", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_jes_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_hfUp", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_hf_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_hfDown", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_hf_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_lfUp", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_lf_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_lfDown", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_lf_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_hfstats1_"+m_era+"Up", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_hfstats1_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_hfstats1_"+m_era+"Down", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_hfstats1_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_hfstats2_"+m_era+"Up", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_hfstats2_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_hfstats2_"+m_era+"Down", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_hfstats2_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_lfstats1_"+m_era+"Up", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_lfstats1_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_lfstats1_"+m_era+"Down", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_lfstats1_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_lfstats2_"+m_era+"Up", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_lfstats2_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_lfstats2_"+m_era+"Down", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_lfstats2_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_cferr1Up", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_cferr1_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_cferr1Down", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_cferr1_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_cferr2Up", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_cferr2_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_btag_shape_cferr2Down", (basicWeight/e->btagShape_weight.v())*e->btagShape_weight_cferr2_down.v(), m_isData);

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_bWPM_"+m_era+"Up", (basicWeight/e->btagWPMedium_weight.v())*e->btagWPMedium_weight_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_bWPM_"+m_era+"Down", (basicWeight/e->btagWPMedium_weight.v())*e->btagWPMedium_weight_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_bWPMT_correlatedUp", (basicWeight/e->btagWPMT_weight.v())*e->btagWPMT_weight_correlated_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_bWPMT_correlatedDown", (basicWeight/e->btagWPMT_weight.v())*e->btagWPMT_weight_correlated_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_bWPMT_uncorrelated_"+m_era+"Up", (basicWeight/e->btagWPMT_weight.v())*e->btagWPMT_weight_uncorrelated_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_eff_bWPMT_uncorrelated_"+m_era+"Down", (basicWeight/e->btagWPMT_weight.v())*e->btagWPMT_weight_uncorrelated_down.v(), m_isData); 

        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_hlt_stats_"+m_era+"Up", (basicWeight/e->HLT_weight.v())*e->HLT_weight_stats_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_hlt_stats_"+m_era+"Down", (basicWeight/e->HLT_weight.v())*e->HLT_weight_stats_down.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_hltLep_"+m_era+"Up", (basicWeight/e->triggerSFLep_weight.v())*e->triggerSFLep_weight_up.v(), m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tttt_eff_hltLep_"+m_era+"Down", (basicWeight/e->triggerSFLep_weight.v())*e->triggerSFLep_weight_down.v(), m_isData);

        //theoretical uncertainties
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_QCDscale_Re_normalisedUp", basicWeight*e->scaleWeightRe_up_.v()*m_scaleRe_normUp_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_QCDscale_Re_normalisedDown", basicWeight*e->scaleWeightRe_down_.v()*m_scaleRe_normDown_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_QCDscale_Fa_normalisedUp", basicWeight*e->scaleWeightFa_up_.v()*m_scaleFa_normUp_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_QCDscale_Fa_normalisedDown", basicWeight*e->scaleWeightFa_down_.v()*m_scaleFa_normDown_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_pdfAlphaS_normalisedUp", basicWeight*e->pdfWeightAlphaS_up_.v()*m_pdfAlphaS_normUp_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_pdfAlphaS_normalisedDown", basicWeight*e->pdfWeightAlphaS_down_.v()*m_pdfAlphaS_normDown_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_pdf_normalisedUp", basicWeight*e->pdfWeight_up_.v()*m_pdf_normUp_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_pdf_normalisedDown", basicWeight*e->pdfWeight_down_.v()*m_pdf_normDown_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_ISR_normalisedUp", basicWeight*e->PSWeightISR_up_.v()*m_PSWeightISR_normUp_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_ISR_normalisedDown", basicWeight*e->PSWeightISR_down_.v()*m_PSWeightISR_normDown_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_FSR_normalisedUp", basicWeight*e->PSWeightFSR_up_.v()*m_PSWeightFSR_normUp_SF, m_isData);
        WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_FSR_normalisedDown", basicWeight*e->PSWeightFSR_down_.v()*m_PSWeightFSR_normDown_SF, m_isData); 

        }else if(m_isFakeTau){
            WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tau_FR_" + m_era + "Up", e->FR_weight_final_up, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, ifBaseline, region+"_CMS_tau_FR_" + m_era + "Down", e->FR_weight_final_down, m_isData);
        }



    }
}

void WH_forDataMC::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    if(!m_isData && !m_isFakeTau && !m_isFakeLepton){
            Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
            TString processName = WH::getProcessName(m_processName, m_isRun3);
            std::cout<<"newProcessName="<<processName<<"\n";

            if(std::find(WH::processWithExt.begin(), WH::processWithExt.end(), processName) != WH::processWithExt.end()){
                genWeightSum = TTTT::getGenSum(m_inputDir + processName + "1.root") + TTTT::getGenSum(m_inputDir+processName+".root");
            }
            std::cout << "genWeightSum=" << genWeightSum << "\n";

            Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at( processName)) / genWeightSum);
            std::cout<<"processScale="<<processScale<<"\n";
            std::cout<<"m_processName="<<m_processName<<" lumi="<<TTTT::lumiMap.at(m_era)<<" crossSection="<<TTTT::crossSectionMap.at(processName)<<"\n";
            WH::histRegionsVectScale(histsForRegion_vec, processScale);
        // }
    };
    for(UInt_t i=0; i<histsForRegion_vec.size(); i++){
        if(i>0){
            continue;
        }
        histsForRegion_vec.at(i)->print();
    }

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

WH_forDataMC::~WH_forDataMC()
{
    // code to free any dynamically allocated resources
    m_file->Close();
    m_outFile->Close();
}