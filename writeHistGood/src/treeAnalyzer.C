/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2023-06-06 21:01:27
 * @modify date 2023-06-06 21:01:27
 * @desc [description]
 */
#include <iostream>

#include "../include/treeAnalyzer.h"
#include "../include/inputFileMap.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "../include/commenSelectionAndWeight.h"

void treeAnalyzer::Init()
{
    std::cout << "Start to initilation....................................................\n";
    std::cout<<"m_channel: "<<m_channel<<"m_isRun3: "<<m_isRun3<<"\n";
    cutFlowHist->SetDirectory(m_outFile);

    // regions for hists
    std::vector<TString> sysRegions = {
        m_channel + "SR",
        "CMS_pileup_" + m_era + "Up",
        "CMS_pileup_" + m_era + "Down",
        "CMS_prefiring_" + m_era + "Up",
        "CMS_prefiring_" + m_era + "Down",
        "CMS_eff_t_vsJet_" + m_era + "Up",
        "CMS_eff_t_vsJet_" + m_era + "Down",
        "CMS_eff_t_vsMu_" + m_era + "Up",
        "CMS_eff_t_vsMu_" + m_era + "Down",
        "CMS_eff_t_vsEle_" + m_era + "Up",
        "CMS_eff_t_vsEle_" + m_era + "Down",
        "CMS_tttt_eff_e_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_e_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_btag_shape_jes_" + m_era + "Up",
        "CMS_btag_shape_jes_" + m_era + "Down",
        "CMS_btag_shape_hf_" + m_era + "Up",
        "CMS_btag_shape_hf_" + m_era + "Down",
        "CMS_btag_shape_lf_" + m_era + "Up",
        "CMS_btag_shape_lf_" + m_era + "Down",
        "CMS_btag_shape_hfstats1_" + m_era + "Up",
        "CMS_btag_shape_hfstats1_" + m_era + "Down",
        "CMS_btag_shape_hfstats2_" + m_era + "Up",
        "CMS_btag_shape_hfstats2_" + m_era + "Down",
        "CMS_btag_shape_lfstats1_" + m_era + "Up",
        "CMS_btag_shape_lfstats1_" + m_era + "Down",
        "CMS_btag_shape_lfstats2_" + m_era + "Up",
        "CMS_btag_shape_lfstats2_" + m_era + "Down",
        "CMS_btag_shape_cferr1_" + m_era + "Up",
        "CMS_btag_shape_cferr1_" + m_era + "Down",
        "CMS_btag_shape_cferr2_" + m_era + "Up",
        "CMS_btag_shape_cferr2_" + m_era + "Down",
        "CMS_tttt_eff_hlt_stats_" + m_era + "Up",
        "CMS_tttt_eff_hlt_stats_" + m_era + "Down",
        "CMS_eff_bWPM_" + m_era + "Up",
        "CMS_eff_bWPM_" + m_era + "Down",
        "pdf_" + m_era + "Up",
        "pdf_" + m_era + "Down",
        "pdfAlphaS_" + m_era + "Up",
        "pdfAlphaS_" + m_era + "Down",
        "QCDscale_Re_" + m_era + "Up",
        "QCDscale_Re_" + m_era + "Down",
        "QCDscale_Fa_" + m_era + "Up",
        "QCDscale_Fa_" + m_era + "Down",
    };


    // if(m_channel==0){
    if(m_channel=="1tau1l"){
        std::cout << "initializing for 1tau1l\n";
        // binning[] = {0.28, -0.1, -0.08, -0.06, -0.04, -0.02, 0., 0.02, 0.04, 0, 07, 0.1, 0.15, 0, 4};//!!!trials for later
        // SR1tau1lSys = histsForRegionsMap("BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions);
        // SR1tau1lSys = histsForRegionsMap("BDT", "BDT score", m_processName, 30, -0.28, 0.4, sysRegions);
        // SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions);
        SR1tau1lSys = histForRegionsBase("BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions);

        // book MVA reader
        TString variableList = WH::BDTTrainingMap.at(m_era).at(0);
        WH::readVariableList(variableList, variablesName, variablesForReader, varForReaderMap, variablesOriginAll);
        // std::cout << " " << variablesForReader.size() << " " << variablesOriginAll.size() << "\n";
        if (variablesName.size() == variablesForReader.size())
        {
            for (UInt_t i = 0; i < variablesName.size(); i++)
            {
                reader->AddVariable(variablesName[i], &varForReaderMap[variablesName[i]]);
            }
        }
        else
        {
            std::cout << "BAD!!! variableName vector not same size of varForReaderMap\n ";
        }
        // for map, the variables will be reordered according to their keys, not safe to add with map

        TString methodName = "BDT" + TString(" method");
        TString weightfile = WH::BDTTrainingMap.at(m_era).at(1) + "TMVAClassification" + TString("_") + "BDT" + TString(".weights.xml");
        reader->BookMVA(methodName, weightfile);
    // }else if(m_channel==1){
    }else if(m_channel=="1tau0l"){
        std::cout << "1tau0l \n";
        SR1tau1lSys = histForRegionsBase("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 5., sysRegions);
        // SR1tau1lSys = histForRegionsBase("bjetsM_HT", "HT^{b-jet}", m_processName, 10, 0, 900, sysRegions); //!testing
        // SR1tau1lSys = histForRegionsBase("bjetsM_invariantMass", "m^{b jets}", m_processName, 10, 0, 1200, sysRegions );

    }else{
        std::cout << "WARNING!! channel not spefified\n";
    }

    SR1tau1lSys.setDir(m_outFile);

    std::cout << "done initializing\n";
    std::cout << "\n";
}

void treeAnalyzer::LoopTree()
{
    std::cout << "start to loop tree\n";
    Long64_t allEvent = m_tree->GetEntries();
    if (m_isTest)
    {
        allEvent = 50000;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);
        cutFlowHist->Fill(0);

        if (!(baselineSelection(e)))
        {
            continue;
        }
        cutFlowHist->Fill(1);

        std::map<TString, Int_t> channelMap = {//!!!this coding is bullshit
            {"1tau1l", 0},
            {"1tau0l", 1},
        };
        Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData, channelMap.at(m_channel)==0 );//!!!caution, for 1tau1l b-tag WP correction

        Bool_t channelSel = SR1tau1lSel(e, channelMap.at(m_channel), m_isRun3);
        // if(m_channel==1 ){
        if(channelMap.at(m_channel)==1 ){
            // if(!m_isData && m_processName.CompareTo("tttt")!=0 ){//no genTau for tttt
                channelSel = channelSel && (e->tausT_genTauNum.v() == 1); 
            // }
        }
        //!testing
        // if(!(e->bjetsM_num.v()>=3)){
            // continue;
        // }

        if (!(channelSel))
        {
            continue;
        }
        cutFlowHist->Fill(2);

        // convert branch value to float for reader
        for (auto it = varForReaderMap.begin(); it != varForReaderMap.end(); ++it)
        {
            Float_t ivar;
            // std::cout<<"ivar: "<<it->first<<"\n";
            std::variant<Int_t, Double_t, Bool_t> branch = e->getByName(it->first);
            if (std::holds_alternative<Int_t>(branch))
            {
                ivar = static_cast<Float_t>(std::get<Int_t>(branch));
            }
            else if (std::holds_alternative<Double_t>(branch))
            {
                ivar = static_cast<Float_t>(std::get<Double_t>(branch));
            }
            varForReaderMap[it->first] = ivar;
        }

        Double_t bdtScore = -99;
        if(channelMap.at(m_channel)==0){
             bdtScore = reader->EvaluateMVA("BDT method");
        }else if(channelMap.at(m_channel)==1){
             bdtScore = e->jets_bScore.v();
            //  bdtScore = e->bjetsM_HT.v();
            // bdtScore = e->bjetsM_invariantMass.v();
        }
        // std::cout << "bdtScore=" << bdtScore << "\n";

        Bool_t SR1tau1l = channelSel;
        //!!!have to output weight; make weight an input
        // Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData);//!!!caution, for 1tau1l b-tag WP correction
        // Double_t basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagWPMedium_weight.v();
        // Double_t    basicWeight = e->EVENT_genWeight.v() * e->EVENT_prefireWeight.v() * e->PUweight_.v() * e->HLT_weight.v() * e->tauT_IDSF_weight_new.v() * e->elesTopMVAT_weight.v() * e->musTopMVAT_weight.v() * e->btagShape_weight.v() * e->btagShapeR.v();//!!! for 1tau0l b_score, have to use btagShape

        // Double_t basicWeight = e->EVENT_genWeight.v();
        // std::cout << "basicWeight = " << basicWeight << "\n";

        // // filling hists
        SR1tau1lSys.fillHistVec(m_channel+"SR", bdtScore, basicWeight, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Up", bdtScore, (basicWeight / e->PUweight_.v()) * e->PUweight_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_prefiring_" + m_era + "Up", bdtScore, (basicWeight / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Down", bdtScore, (basicWeight / e->PUweight_.v()) * e->PUweight_down_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_prefiring_" + m_era + "Down", bdtScore, (basicWeight / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsJet_" + m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsJet_" + m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsMu_" + m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsMu_" + m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsEle_" + m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsEle_" + m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_e_" + m_era + "Up", bdtScore, (basicWeight / e->elesTopMVAT_weight.v()) * e->elesTopMVAT_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_e_" + m_era + "Down", bdtScore, (basicWeight / e->elesTopMVAT_weight.v()) * e->elesTopMVAT_weight_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_m_" + m_era + "Up", bdtScore, (basicWeight / e->musTopMVAT_weight.v()) * e->musTopMVAT_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_m_" + m_era + "Down", bdtScore, (basicWeight / e->musTopMVAT_weight.v()) * e->musTopMVAT_weight_down.v(), SR1tau1l, m_isData);
        //

        SR1tau1lSys.fillHistVec("CMS_btag_shape_jes_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_jes_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_jes_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_jes_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hf_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hf_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hf_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hf_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lf_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lf_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lf_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lf_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats1_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats1_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats2_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats2_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats1_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats1_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats2_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats2_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr1_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr1_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr2_" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr2_" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_down.v(), SR1tau1l, m_isData);
        //!!!temporarily for b WPM
        SR1tau1lSys.fillHistVec("CMS_eff_bWPM_" + m_era + "Up", bdtScore, (basicWeight / e->btagWPMedium_weight.v()) * e->btagWPMedium_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_bWPM_" + m_era + "Down", bdtScore, (basicWeight / e->btagWPMedium_weight.v()) * e->btagWPMedium_weight_down.v(), SR1tau1l, m_isData);


        //!!!temparory workaround, need to fix the HLT_weight==0 in MV step
        if (e->HLT_weight.v() == 0)
        {
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats_" + m_era + "Up", bdtScore, 1, SR1tau1l, m_isData);
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats_" + m_era + "Down", bdtScore, 1, SR1tau1l, m_isData);
        }
        else
        {
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats_" + m_era + "Up", bdtScore, (basicWeight / e->HLT_weight.v()) * e->HLT_weight_stats_up.v(), SR1tau1l, m_isData);
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats_" + m_era + "Down", bdtScore, (basicWeight / e->HLT_weight.v()) * e->HLT_weight_stats_down.v(), SR1tau1l, m_isData);
        }

        //theorectical uncertainties
        SR1tau1lSys.fillHistVec("pdf_" + m_era + "Up", bdtScore, basicWeight* e->pdfWeight_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("pdf_" + m_era + "Down", bdtScore, basicWeight* e->pdfWeight_down_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("pdfAlphaS_" + m_era + "Up", bdtScore, basicWeight* e->pdfWeightAlphaS_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("pdfAlphaS_" + m_era + "Down", bdtScore, basicWeight* e->pdfWeightAlphaS_down_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("QCDscale_Re_" + m_era + "Up", bdtScore, basicWeight* e->scaleWeightRe_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("QCDscale_Re_" + m_era + "Down", bdtScore, basicWeight* e->scaleWeightRe_down_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("QCDscale_Fa_" + m_era + "Up", bdtScore, basicWeight* e->scaleWeightFa_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("QCDscale_Fa_" + m_era + "Down", bdtScore, basicWeight* e->scaleWeightFa_down_.v(), SR1tau1l, m_isData);

    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void treeAnalyzer::Terminate()
{
    std::cout << "Termintate: ..........................................\n";

    if (!m_isData)
    {
        Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
        const Double_t processScale = ((TTTT::lumiMap.at(m_era)* TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        SR1tau1lSys.scale(processScale);
    };
    SR1tau1lSys.print();

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

treeAnalyzer::~treeAnalyzer()
{
    // code to free any dynamically allocated resources
    m_file->Close();
    m_outFile->Close();
    // delete m_tree;
    // delete m_file;
    // delete m_outFile;
}