#include <iostream>

#include "treeAnalyzer.h"
#include "../SFfileMap.h"
#include "functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"
#include "commenSelectionAndWeight.C"

void treeAnalyzer::Init()
{
    std::cout << "start to initilation....................................................\n";
    cutFlowHist->SetDirectory(m_outFile);
    // book MVA reader
    TString variableList = BDTTrainingMap[m_era].at(0);
    readVariableList(variableList, variablesName, variablesForReader, varForReaderMap, variablesOriginAll);
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
    TString weightfile = BDTTrainingMap[m_era].at(1) + "TMVAClassification" + TString("_") + "BDT" + TString(".weights.xml");
    reader->BookMVA(methodName, weightfile);

    // regions for hists
    std::vector<TString> sysRegions = {
        "SR",
        "CMS_pileup_" + m_era + "Up",
        "CMS_pileup_" + m_era + "Down",
        "CMS_prefiring_" + m_era + "Up",
        "CMS_prefiring_" + m_era + "Down",
        "CMS_eff_t_vsJet" + m_era + "Up",
        "CMS_eff_t_vsJet" + m_era + "Down",
        "CMS_eff_t_vsMu" + m_era + "Up",
        "CMS_eff_t_vsMu" + m_era + "Down",
        "CMS_eff_t_vsEle" + m_era + "Up",
        "CMS_eff_t_vsEle" + m_era + "Down",
        "CMS_tttt_eff_e_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_e_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Up",   // our TOP MVA Lepton SF uncertainty
        "CMS_tttt_eff_m_" + m_era + "Down", // our TOP MVA Lepton SF uncertainty
        "CMS_btag_shape_jes" + m_era + "Up",
        "CMS_btag_shape_jes" + m_era + "Down",
        "CMS_btag_shape_hf" + m_era + "Up",
        "CMS_btag_shape_hf" + m_era + "Down",
        "CMS_btag_shape_lf" + m_era + "Up",
        "CMS_btag_shape_lf" + m_era + "Down",
        "CMS_btag_shape_hfstats1" + m_era + "Up",
        "CMS_btag_shape_hfstats1" + m_era + "Down",
        "CMS_btag_shape_hfstats2" + m_era + "Up",
        "CMS_btag_shape_hfstats2" + m_era + "Down",
        "CMS_btag_shape_lfstats1" + m_era + "Up",
        "CMS_btag_shape_lfstats1" + m_era + "Down",
        "CMS_btag_shape_lfstats2" + m_era + "Up",
        "CMS_btag_shape_lfstats2" + m_era + "Down",
        "CMS_btag_shape_cferr1" + m_era + "Up",
        "CMS_btag_shape_cferr1" + m_era + "Down",
        "CMS_btag_shape_cferr2" + m_era + "Up",
        "CMS_btag_shape_cferr2" + m_era + "Down",
        "CMS_tttt_eff_hlt_stats" + m_era + "Up",
        "CMS_tttt_eff_hlt_stats" + m_era + "Down",
    };
    // SR1tau1lSys = histsForRegionsMap("BDT", "BDT score", m_processName, 20, -0.28, 0.4, sysRegions);
    SR1tau1lSys = histsForRegionsMap("BDT", "BDT score", m_processName, 30, -0.28, 0.4, sysRegions);
    // SR1tau1lSys.print();
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
        allEvent = 1000;
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

        if (!(SR1tau1lSel(e)))
        {
            continue;
        }
        cutFlowHist->Fill(2);

        // convert branch value to float for reader
        for (auto it = varForReaderMap.begin(); it != varForReaderMap.end(); ++it)
        {
            Float_t ivar;
            // std::cout<<"ivar: "<<it->first<<"\n";
            std::variant<Int_t, Double_t> branch = e->getByName(it->first);
            if (std::holds_alternative<Int_t>(branch))
            {
                ivar = static_cast<Float_t>(std::get<Int_t>(branch));
            }
            else
            {
                ivar = static_cast<Float_t>(std::get<Double_t>(branch));
            }
            varForReaderMap[it->first] = ivar;
        }

        Double_t bdtScore = reader->EvaluateMVA("BDT method");
        // std::cout << "bdtScore=" << bdtScore << "\n";

        Bool_t SR1tau1l = SR1tau1lSel(e);
        Double_t basicWeight = baseWeightCal(e);
        // std::cout << "basicWeight = " << basicWeight << "\n";

        // // filling hists
        SR1tau1lSys.fillHistVec("SR", bdtScore, basicWeight, SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Up", bdtScore, (basicWeight / e->PUweight_.v()) * e->PUweight_up_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_prefiring_" + m_era + "Up", bdtScore, (basicWeight / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_pileup_" + m_era + "Down", bdtScore, (basicWeight / e->PUweight_.v()) * e->PUweight_down_.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_prefiring_" + m_era + "Down", bdtScore, (basicWeight / e->EVENT_prefireWeight.v()) * e->EVENT_prefireWeight_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsJet" + m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsJet" + m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsjet_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsMu" + m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsMu" + m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsmu_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsEle" + m_era + "Up", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_eff_t_vsEle" + m_era + "Down", bdtScore, (basicWeight / e->tauT_IDSF_weight_new.v()) * e->tauT_IDSF_weight_new_vsele_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_e_" + m_era + "Up", bdtScore, (basicWeight / e->elesTopMVAT_weight.v()) * e->elesTopMVAT_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_e_" + m_era + "Down", bdtScore, (basicWeight / e->elesTopMVAT_weight.v()) * e->elesTopMVAT_weight_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_m_" + m_era + "Up", bdtScore, (basicWeight / e->musTopMVAT_weight.v()) * e->musTopMVAT_weight_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_tttt_eff_m_" + m_era + "Down", bdtScore, (basicWeight / e->musTopMVAT_weight.v()) * e->musTopMVAT_weight_down.v(), SR1tau1l, m_isData);
        //

        SR1tau1lSys.fillHistVec("CMS_btag_shape_jes" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_jes_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_jes" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_jes_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hf" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hf_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hf" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hf_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lf" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lf_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lf" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lf_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats1" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats1" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats2" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_hfstats2" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_hfstats2_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats1" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats1" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats2" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_lfstats2" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_lfstats2_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr1" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr1" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr1_down.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr2" + m_era + "Up", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_up.v(), SR1tau1l, m_isData);
        SR1tau1lSys.fillHistVec("CMS_btag_shape_cferr2" + m_era + "Down", bdtScore, (basicWeight / e->btagShape_weight.v()) * e->btagShape_weight_cferr2_down.v(), SR1tau1l, m_isData);
        //!!!temparory workaround, need to fix the HLT_weight==0 in MV step
        if (e->HLT_weight.v() == 0)
        {
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats" + m_era + "Up", bdtScore, 1, SR1tau1l, m_isData);
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats" + m_era + "Down", bdtScore, 1, SR1tau1l, m_isData);
        }
        else
        {
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats" + m_era + "Up", bdtScore, (basicWeight / e->HLT_weight.v()) * e->HLT_weight_stats_up.v(), SR1tau1l, m_isData);
            SR1tau1lSys.fillHistVec("CMS_tttt_eff_hlt_stats" + m_era + "Down", bdtScore, (basicWeight / e->HLT_weight.v()) * e->HLT_weight_stats_down.v(), SR1tau1l, m_isData);
        }
    }
    std::cout << "end of event loop\n";
    std::cout << "\n";
};

void treeAnalyzer::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    Double_t genWeightSum = getGenSum(m_inputDir + m_processName + ".root");
    Double_t processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / genWeightSum);
    if (!m_isData)
    {
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