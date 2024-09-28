// I will just have some class to begin with. doesn't need to be perfect, always room to improve:)
// maybe have a base class with only value as member variables to save memory
#ifndef MYEVENTCLASS_H
#define MYEVENTCLASS_H
#include <variant>
#include <map>
#include <cassert>
#include <iostream>

#include "TString.h"
#include "TTree.h"

template <typename T>
class myBranch
{
public:
    myBranch(TString branchName = "") : m_branchName{branchName}
    {
    }
    T v()
    {
        return m_branchValue;
    }
    T *a()
    {
        return &m_branchValue;
    }
    TString n()
    {
        return m_branchName;
    }

private:
    TString m_branchName;
    T m_branchValue;
};


class event
{
    // be able to access branch value with string
    // can directly access memeber variable too
public:
    event(TTree *tree) : m_tree{tree}
    { // how to loop through all member variables?
        std::cout << "event: initialize event class by SetBranchAddress()\n";
        m_tree->SetBranchStatus("*", 0);
        for (auto it = m_variableMap.begin(); it != m_variableMap.end(); ++it)
        {
            if (std::holds_alternative<myBranch<Int_t> *>(it->second))
            {
                myBranch<Int_t> *bra = std::get<myBranch<Int_t> *>(it->second);
                m_tree->SetBranchStatus(bra->n(), 1);
                m_tree->SetBranchAddress(bra->n(), bra->a());
            }
            else if (std::holds_alternative<myBranch<Double_t> *>(it->second))
            {
                myBranch<Double_t> *bra = std::get<myBranch<Double_t> *>(it->second);
                m_tree->SetBranchStatus(bra->n(), 1);
                m_tree->SetBranchAddress(bra->n(), bra->a());
            }
            else if (std::holds_alternative<myBranch<Bool_t> *>(it->second))
            {
                myBranch<Bool_t> *bra = std::get<myBranch<Bool_t> *>(it->second);
                m_tree->SetBranchStatus(bra->n(), 1);
                m_tree->SetBranchAddress(bra->n(), bra->a());
            }
        };

        m_tree->SetBranchStatus("jets_pt_", 1);
        m_tree->SetBranchStatus("jets_eta_", 1);
        m_tree->SetBranchStatus("jets_btags_", 1);
        m_tree->SetBranchStatus("jets_btagsPT_", 1);
        m_tree->SetBranchStatus("jets_flavour_", 1);
        m_tree->SetBranchAddress("jets_pt_", &jets_pt_);
        m_tree->SetBranchAddress("jets_eta_", &jets_eta_);
        m_tree->SetBranchAddress("jets_btags_", &jets_btags_);
        m_tree->SetBranchAddress("jets_btagsPT_", &jets_btagsPT_);
        m_tree->SetBranchAddress("jets_flavour_", &jets_flavour_);

        if(m_tree->GetListOfBranches()->FindObject("FR_weight_final")){
            m_tree->SetBranchStatus("FR_weight_final", 1);
            m_tree->SetBranchAddress("FR_weight_final", &FR_weight_final);
            m_tree->SetBranchStatus("FR_weight_final_up", 1);
            m_tree->SetBranchAddress("FR_weight_final_up", &FR_weight_final_up);
            m_tree->SetBranchStatus("FR_weight_final_down", 1);
            m_tree->SetBranchAddress("FR_weight_final_down", &FR_weight_final_down);
        }


        std::cout << "Done initializing event class \n";
    };
    ~event()
    {
        delete m_tree;
    };
    std::variant<Int_t, Double_t, Bool_t> getByName(TString branchName)
    {
        assert(m_variableMap.count(branchName));
        //  if (!(m_variableMap.count(branchName)))
        // {
        //     std::cout << "BAD!!!  branch doesn't exist in the event class object yet\n";
        // }
        std::variant<Int_t, Double_t, Bool_t> a;
        if (std::holds_alternative<myBranch<Int_t> *>(m_variableMap[branchName]))
        {
            a = (std::get<myBranch<Int_t> *>(m_variableMap[branchName]))->v();
        }
        else if (std::holds_alternative<myBranch<Double_t> *>(m_variableMap[branchName]))
        {
            a = (std::get<myBranch<Double_t> *>(m_variableMap[branchName]))->v();
        }else if (std::holds_alternative<myBranch<Bool_t> *>(m_variableMap[branchName]))
        {
            a = (std::get<myBranch<Bool_t> *>(m_variableMap[branchName]))->v();
        }
        return a;
    };
    // branches for selection and weight
    myBranch<Int_t> elesTopMVAT_num{"elesTopMVAT_num"};
    myBranch<Int_t> muonsTopMVAT_num{"muonsTopMVAT_num"};
    myBranch<Int_t> elesMVAT_num{"elesMVAT_num"};
    myBranch<Int_t> muonsT_num{"muonsT_num"};
    myBranch<Double_t> muonsT_1pt{"muonsT_1pt"};
    myBranch<Double_t> elesMVAT_1pt{"elesMVAT_1pt"};
    myBranch<Double_t> lepTopMVAT_1pt{"lepTopMVAT_1pt"};
    myBranch<Double_t> lepTopMVAT_2pt{"lepTopMVAT_2pt"};
    myBranch<Int_t> elesTopMVAF_num{"elesTopMVAF_num"};
    myBranch<Int_t> muonsTopMVAF_num{"muonsTopMVAF_num"};
    myBranch<Bool_t> elesTopMVAF_1isTightPrompt{"elesTopMVAF_1isTightPrompt"};
    myBranch<Bool_t> elesTopMVAF_2isTightPrompt{"elesTopMVAF_2isTightPrompt"};
    myBranch<Bool_t> muonsTopMVAF_1isTightPrompt{"muonsTopMVAF_1isTightPrompt"};
    myBranch<Bool_t> muonsTopMVAF_2isTightPrompt{"muonsTopMVAF_2isTightPrompt"};
    myBranch<Bool_t> elesTopMVAF_1isTight{"elesTopMVAF_1isTight"};
    myBranch<Bool_t> elesTopMVAF_2isTight{"elesTopMVAF_2isTight"};
    myBranch<Bool_t> muonsTopMVAF_1isTight{"muonsTopMVAF_1isTight"};
    myBranch<Bool_t> muonsTopMVAF_2isTight{"muonsTopMVAF_2isTight"};
    myBranch<Bool_t> lepTopMVAF_isAR{"lepTopMVAF_isAR"};
    myBranch<Int_t> lepTopMVAF_num{"lepTopMVAF_num"};
    // myBranch<Double_t> lepTopMVAF_FRweight{"lepTopMVAF_FRweight"};

    myBranch<Double_t> EVENT_genWeight{"EVENT_genWeight"};
    myBranch<Double_t> EVENT_prefireWeight{"EVENT_prefireWeight"};
    myBranch<Double_t> PUweight_{"PUweight_"};
    myBranch<Double_t> HLT_weight{"HLT_weight"};
    myBranch<Double_t> tauT_IDSF_weight_new{"tauT_IDSF_weight_new"};
    myBranch<Double_t> tauTT_IDSF_weight_new{"tauTT_IDSF_weight_new"};
    myBranch<Double_t> elesTopMVAT_weight{"elesTopMVAT_weight"};
    myBranch<Double_t> musTopMVAT_weight{"musTopMVAT_weight"};
    myBranch<Double_t> btagShape_weight{"btagShape_weight"};
    myBranch<Double_t> btagShapeR{"btagShapeR"};
    myBranch<Double_t> btagWPMedium_weight{"btagWPMedium_weight"};
    myBranch<Double_t> btagWPMedium_weight_up{"btagWPMedium_weight_up"};
    myBranch<Double_t> btagWPMedium_weight_down{"btagWPMedium_weight_down"};
    myBranch<Double_t> btagWPMT_weight{"btagWPMT_weight"};
    myBranch<Double_t> btagWPMT_weight_up{"btagWPMT_weight_up"};
    myBranch<Double_t> btagWPMT_weight_down{"btagWPMT_weight_down"};
    myBranch<Double_t> eleMVAT_IDSF_weight{"eleMVAT_IDSF_weight"};
    //
    myBranch<Double_t> pdfWeight_up_{"pdfWeight_up_"};
    myBranch<Double_t> pdfWeight_down_{"pdfWeight_down_"};
    myBranch<Double_t> pdfWeightAlphaS_up_{"pdfWeightAlphaS_up_"};
    myBranch<Double_t> pdfWeightAlphaS_down_{"pdfWeightAlphaS_down_"};
    myBranch<Double_t> scaleWeight_up_{"scaleWeight_up_"};
    myBranch<Double_t> scaleWeight_down_{"scaleWeight_down_"};
    myBranch<Double_t> scaleWeightRe_up_{"scaleWeightRe_up_"};
    myBranch<Double_t> scaleWeightRe_down_{"scaleWeightRe_down_"};
    myBranch<Double_t> scaleWeightFa_up_{"scaleWeightFa_up_"};
    myBranch<Double_t> scaleWeightFa_down_{"scaleWeightFa_down_"};

    myBranch<Int_t> jets_num{"jets_num"};
    myBranch<Double_t> jets_rationHT_4toRest{"jets_rationHT_4toRest"};
    myBranch<Double_t> jets_MHT{"jets_MHT"};
    myBranch<Double_t> jets_HT{"jets_HT"};
    myBranch<Double_t> jets_invariantMass{"jets_invariantMass"};
    myBranch<Double_t> jets_transMass{"jets_transMass"};
    myBranch<Double_t> jets_minDeltaR{"jets_minDeltaR"};
    myBranch<Double_t> jets_centrality{"jets_centrality"};
    myBranch<Double_t> jets_bScore{"jets_bScore"};
    myBranch<Double_t> jets_average_deltaR{"jets_average_deltaR"};
    myBranch<Double_t> jets_4largestBscoreSum{"jets_4largestBscoreSum"};
    myBranch<Double_t> jets_4largestBscoreMulti{"jets_4largestBscoreMulti"};
    myBranch<Double_t> jets_HTDivideMET{"jets_HTDivideMET"};
    myBranch<Double_t> jets_METDivideHT{"jets_METDivideHT"}; 
    myBranch<Double_t> jets_sphericity{"jets_sphericity"}; 
    myBranch<Double_t> jets_aplanarity{"jets_aplanarity"};
    myBranch<Double_t> jets_tausT_invariantMass{"jets_tausT_invariantMass"};
    myBranch<Double_t> jets_tausT_minDeltaR{"jets_tausT_minDeltaR"};

    myBranch<Double_t> jets_1pt{"jets_1pt"};
    myBranch<Double_t> jets_2pt{"jets_2pt"};
    myBranch<Double_t> jets_3pt{"jets_3pt"};
    myBranch<Double_t> jets_4pt{"jets_4pt"};
    myBranch<Double_t> jets_5pt{"jets_5pt"};
    myBranch<Double_t> jets_6pt{"jets_6pt"};
    myBranch<Double_t> jets_7pt{"jets_7pt"};
    myBranch<Double_t> jets_8pt{"jets_8pt"};
    myBranch<Double_t> jets_9pt{"jets_9pt"};
    myBranch<Double_t> jets_1btag{"jets_1btag"};
    myBranch<Double_t> jets_2btag{"jets_2btag"};
    myBranch<Double_t> jets_3btag{"jets_3btag"};
    myBranch<Double_t> jets_4btag{"jets_4btag"};
    myBranch<Double_t> jets_5btag{"jets_5btag"};
    myBranch<Double_t> jets_6btag{"jets_6btag"};
    myBranch<Double_t> jets_7btag{"jets_7btag"};
    myBranch<Double_t> jets_8btag{"jets_8btag"};

    myBranch<Double_t> MET_pt{"MET_pt"};

    myBranch<Int_t> bjetsM_num{"bjetsM_num"};
    myBranch<Int_t> bjetsT_num{"bjetsT_num"};
    myBranch<Int_t> bjetsPNM_num{"bjetsPNM_num"};
    myBranch<Int_t> bjetsPTM_num{"bjetsPTM_num"};
    myBranch<Int_t> bjetsPTT_num{"bjetsPTT_num"};

    myBranch<Double_t> bjetsM_invariantMass{"bjetsM_invariantMass"};
    myBranch<Double_t> bjetsM_HT{"bjetsM_HT"};
    myBranch<Double_t> bjetsM_MHT{"bjetsM_MHT"};
    myBranch<Double_t> bjetsM_transMass{"bjetsM_transMass"};
    myBranch<Double_t> bjetsM_minDeltaR{"bjetsM_minDeltaR"};
    myBranch<Double_t> bjetsM_2leptons2_stransMass{"bjetsM_2leptons2_stransMass"};
    myBranch<Double_t> bjetsM_2tauT1lep1_stransMass{"bjetsM_2tauT1lep1_stransMass"};
    myBranch<Double_t> bjetsM_2tauF1lep1_stransMass{"bjetsM_2tauF1lep1_stransMass"};
    myBranch<Double_t> bjetsM_2MET_stransMass{"bjetsM_2MET_stransMass"};
    myBranch<Double_t> bjetsM_leptons_minDeltaR{"bjetsM_leptons_minDeltaR"};
    myBranch<Double_t> bjetsM_tausT_minDeltaR{"bjetsM_tausT_minDeltaR"};
    myBranch<Double_t> bjetsM_tausF_minDeltaR{"bjetsM_tausF_minDeltaR"};
    myBranch<Double_t> bjetsM_1pt{"bjetsM_1pt"};
    myBranch<Double_t> bjetsM_2pt{"bjetsM_2pt"};
    myBranch<Double_t> bjetsM_3pt{"bjetsM_3pt"};

    myBranch<Double_t> bjetsT_invariantMass{"bjetsT_invariantMass"};
    myBranch<Double_t> bjetsT_HT{"bjetsT_HT"};
    myBranch<Double_t> bjetsT_MHT{"bjetsT_MHT"};
    myBranch<Double_t> bjetsT_transMass{"bjetsT_transMass"};
    myBranch<Double_t> bjetsT_minDeltaR{"bjetsT_minDeltaR"};
    myBranch<Double_t> bjetsT_2leptons2_stransMass{"bjetsT_2leptons2_stransMass"};
    myBranch<Double_t> bjetsT_2tauT1lep1_stransMass{"bjetsT_2tauT1lep1_stransMass"};
    myBranch<Double_t> bjetsT_2tauF1lep1_stransMass{"bjetsT_2tauF1lep1_stransMass"};
    myBranch<Double_t> bjetsT_2MET_stransMass{"bjetsT_2MET_stransMass"};
    myBranch<Double_t> bjetsT_leptons_minDeltaR{"bjetsT_leptons_minDeltaR"};
    myBranch<Double_t> bjetsT_tausT_minDeltaR{"bjetsT_tausT_minDeltaR"};
    myBranch<Double_t> bjetsT_tausF_minDeltaR{"bjetsT_tausF_minDeltaR"};
    myBranch<Double_t> bjetsT_1pt{"bjetsT_1pt"};
    myBranch<Double_t> bjetsT_2pt{"bjetsT_2pt"};
    myBranch<Double_t> bjetsT_3pt{"bjetsT_3pt"};


    myBranch<Int_t> tausT_num{"tausT_num"};
    myBranch<Int_t> tausTT_num{"tausTT_num"};
    myBranch<Int_t> tausTTT_num{"tausTTT_num"};
    myBranch<Int_t> tausM_num{"tausM_num"};
    myBranch<Int_t> tausF_genTauNum{"tausF_genTauNum"};
    myBranch<Int_t> tausT_genTauNum{"tausT_genTauNum"};

    myBranch<Double_t> tausT_HT{"tausT_HT"};
    myBranch<Double_t> tausT_MHT{"tausT_MHT"};
    myBranch<Double_t> tausT_invariantMass{"tausT_invariantMass"};
    myBranch<Double_t> tausT_1lepton1_deltaR{"tausT_1lepton1_deltaR"};
    myBranch<Double_t> tausT_1Met_transMass{"tausT_1Met_transMass"};
    myBranch<Double_t> tausT_1lepton1Met1_stransMass{"tausT_1lepton1Met1_stransMass"};
    myBranch<Double_t> tausT_leptonsT_invariantMass{"tausT_leptonsT_invariantMass"};
    myBranch<Double_t> tausT_leptonsTMVA_minDeltaR{"tausT_leptonsTMVA_minDeltaR"};
    myBranch<Double_t> tausT_leptonsT_transMass{"tausT_leptonsT_transMass"};
    myBranch<Int_t> tausT_1charge{"tausT_1charge"};
    myBranch<Double_t> tausT_1pt{"tausT_1pt"};
    myBranch<Double_t> tausT_1eta{"tausT_1eta"};
    myBranch<Double_t> tausT_1phi{"tausT_1phi"};
    myBranch<Int_t> tausT_1genFlavour{"tausT_1genFlavour"};
    myBranch<Int_t> tausT_prongNum{"tausT_prongNum"};
    myBranch<Int_t> tausT_1lepton1_charge{"tausT_1lepton1_charge"};
    myBranch<Int_t> tausT_leptons_charge{"tausT_leptons_charge"};

    myBranch<Double_t> tausTT_HT{"tausTT_HT"};
    myBranch<Double_t> tausTT_MHT{"tausTT_MHT"};
    myBranch<Double_t> tausTT_invariantMass{"tausTT_invariantMass"};
    myBranch<Double_t> tausTT_1lepton1_deltaR{"tausTT_1lepton1_deltaR"};
    myBranch<Double_t> tausTT_1Met_transMass{"tausTT_1Met_transMass"};
    myBranch<Double_t> tausTT_1lepton1Met1_stransMass{"tausTT_1lepton1Met1_stransMass"};
    myBranch<Double_t> tausTT_leptonsT_invariantMass{"tausTT_leptonsT_invariantMass"};
    myBranch<Double_t> tausTT_leptonsTMVA_minDeltaR{"tausTT_leptonsTMVA_minDeltaR"};
    myBranch<Double_t> tausTT_leptonsT_transMass{"tausTT_leptonsT_transMass"};
    myBranch<Int_t> tausTT_1charge{"tausTT_1charge"};
    myBranch<Int_t> tausTT_1genFlavour{"tausTT_1genFlavour"};
    myBranch<Int_t> tausTT_1decayMode{"tausTT_1decayMode"};
    myBranch<Int_t> tausTT_1lepton1_charge{"tausTT_1lepton1_charge"};
    myBranch<Double_t> tausTT_1pt{"tausTT_1pt"};
    myBranch<Double_t> tausTT_1eta{"tausTT_1eta"};
    myBranch<Double_t> tausTT_1phi{"tausTT_1phi"};


    myBranch<Int_t> tausTTT_1genFlavour{"tausTTT_1genFlavour"};
    myBranch<Int_t> tausTTT_1lepton1_charge{"tausTTT_1lepton1_charge"};

    myBranch<Double_t> muonsTopMVAT_1pt{"muonsTopMVAT_1pt"};
    myBranch<Double_t> elesTopMVAT_1pt{"elesTopMVAT_1pt"};
    myBranch<Double_t> elesTopMVAT_1eta{"elesTopMVAT_1eta"};

    // branches for fakeTau;
    myBranch<Int_t> tausF_prongNum{"tausF_prongNum"};
    myBranch<Double_t> tausF_1jetPt{"tausF_1jetPt"};
    myBranch<Double_t> tausF_1eta{"tausF_1eta"};
    myBranch<Double_t> tausF_1jetEtaAbs{"tausF_1jetEtaAbs"};
    myBranch<Int_t> tausF_num{"tausF_num"};
    myBranch<Int_t> tausF_1charge{"tausF_1charge"};
    myBranch<Double_t> tausF_1pt{"tausF_1pt"};
    myBranch<Int_t> tausF_1genFlavour{"tausF_1genFlavour"};
    myBranch<Int_t> tausF_1decayMode{"tausF_1decayMode"};
    myBranch<Int_t> tausF_1prongNum{"tausF_1prongNum"};
    myBranch<Double_t> tausF_1Met_transMass{"tausF_1Met_transMass"};
    myBranch<Double_t> tausF_invariantMass{"tausF_invariantMass"};
    myBranch<Double_t> tausF_jet_invariantMass{"tausF_jet_invariantMass"};
    myBranch<Double_t> tausF_jet1_Met_transMass{"tausF_jet1_Met_transMass"};

    myBranch<Int_t> tausM_1genFlavour{"tausM_1genFlavour"};
    myBranch<Int_t> tausT_1decayMode{"tausT_1decayMode"};
    myBranch<Int_t> tausM_1lepton1_charge{"tausM_1lepton1_charge"};
    myBranch<Int_t> tausT_leptonsTopMVA_chargeMulti{"tausT_leptonsTopMVA_chargeMulti"};

    // weight variations
    myBranch<Double_t> EVENT_prefireWeight_up{"EVENT_prefireWeight_up"};
    myBranch<Double_t> PUweight_up_{"PUweight_up_"};
    myBranch<Double_t> HLT_weight_stats_up{"HLT_weight_stats_up"};
    myBranch<Double_t> tauT_IDSF_weight_new_vsjet_up{"tauT_IDSF_weight_new_vsjet_up"};
    myBranch<Double_t> elesTopMVAT_weight_up{"elesTopMVAT_weight_up"};
    myBranch<Double_t> musTopMVAT_weight_up{"musTopMVAT_weight_up"};
    myBranch<Double_t> tauT_IDSF_weight_new_vsmu_up{"tauT_IDSF_weight_new_vsmu_up"};
    myBranch<Double_t> tauT_IDSF_weight_new_vsele_up{"tauT_IDSF_weight_new_vsele_up"};
    myBranch<Double_t> btagShape_weight_jes_up{"btagShape_weight_jes_up"};
    myBranch<Double_t> btagShape_weight_hf_up{"btagShape_weight_hf_up"};
    myBranch<Double_t> btagShape_weight_lf_up{"btagShape_weight_lf_up"};
    myBranch<Double_t> btagShape_weight_hfstats1_up{"btagShape_weight_hfstats1_up"};
    myBranch<Double_t> btagShape_weight_hfstats2_up{"btagShape_weight_hfstats2_up"};
    myBranch<Double_t> btagShape_weight_lfstats1_up{"btagShape_weight_lfstats1_up"};
    myBranch<Double_t> btagShape_weight_lfstats2_up{"btagShape_weight_lfstats2_up"};
    myBranch<Double_t> btagShape_weight_cferr1_up{"btagShape_weight_cferr1_up"};
    myBranch<Double_t> btagShape_weight_cferr2_up{"btagShape_weight_cferr2_up"};
    myBranch<Double_t> EVENT_prefireWeight_down{"EVENT_prefireWeight_down"};
    myBranch<Double_t> PUweight_down_{"PUweight_down_"};
    myBranch<Double_t> HLT_weight_stats_down{"HLT_weight_stats_down"};
    myBranch<Double_t> tauT_IDSF_weight_new_vsjet_down{"tauT_IDSF_weight_new_vsjet_down"};
    myBranch<Double_t> elesTopMVAT_weight_down{"elesTopMVAT_weight_down"};
    myBranch<Double_t> musTopMVAT_weight_down{"musTopMVAT_weight_down"};
    myBranch<Double_t> tauT_IDSF_weight_new_vsmu_down{"tauT_IDSF_weight_new_vsmu_down"};
    myBranch<Double_t> tauT_IDSF_weight_new_vsele_down{"tauT_IDSF_weight_new_vsele_down"};
    myBranch<Double_t> btagShape_weight_jes_down{"btagShape_weight_jes_down"};
    myBranch<Double_t> btagShape_weight_hf_down{"btagShape_weight_hf_down"};
    myBranch<Double_t> btagShape_weight_lf_down{"btagShape_weight_lf_down"};
    myBranch<Double_t> btagShape_weight_hfstats1_down{"btagShape_weight_hfstats1_down"};
    myBranch<Double_t> btagShape_weight_hfstats2_down{"btagShape_weight_hfstats2_down"};
    myBranch<Double_t> btagShape_weight_lfstats1_down{"btagShape_weight_lfstats1_down"};
    myBranch<Double_t> btagShape_weight_lfstats2_down{"btagShape_weight_lfstats2_down"};
    myBranch<Double_t> btagShape_weight_cferr1_down{"btagShape_weight_cferr1_down"};
    myBranch<Double_t> btagShape_weight_cferr2_down{"btagShape_weight_cferr2_down"};

    //for HLT efficiency
    myBranch<Bool_t> HLT_PFHT450_SixJet40_BTagCSV_p056{"HLT_PFHT450_SixJet40_BTagCSV_p056"};
    myBranch<Bool_t> HLT_PFHT400_SixJet30_DoubleBTagCSV_p056{"HLT_PFHT400_SixJet30_DoubleBTagCSV_p056"};
    myBranch<Bool_t> HLT_PFJet450{"HLT_PFJet450"};
    myBranch<Bool_t> HLT_IsoMu24{"HLT_IsoMu24"};
    myBranch<Bool_t> HLT_IsoMu27{"HLT_IsoMu27"};

    myBranch<Bool_t> HLT_PFJet500{"HLT_PFJet500"};
    myBranch<Bool_t> HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5{"HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5"};
    myBranch<Bool_t> HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2{"HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2"};
    myBranch<Bool_t> HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5{"HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5"};
    myBranch<Bool_t> HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59{"HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59"};
    myBranch<Bool_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94{"HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94"};
    myBranch<Bool_t> HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5{"HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5"};
    //  2017
    myBranch<Bool_t> HLT_PFHT430_SixJet40_BTagCSV_p080{"HLT_PFHT430_SixJet40_BTagCSV_p080"};
    myBranch<Bool_t> HLT_PFHT380_SixJet32_DoubleBTagCSV_p075{"HLT_PFHT380_SixJet32_DoubleBTagCSV_p075"};
    myBranch<Bool_t> HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2{"HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2"};
    myBranch<Bool_t> HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0{"HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0"};
    myBranch<Bool_t> HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07{"HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07"};
    myBranch<Bool_t> HLT_PFHT1050{"HLT_PFHT1050"};
    // 2022
    myBranch<Bool_t> HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59{"HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59"};
    myBranch<Bool_t> HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94{"HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94"};

    myBranch<Int_t> PV_npvsGood{"PV_npvsGood"};

    //for btag eff study
    std::vector<Double_t>* jets_pt_=nullptr;//???not sure why it has to be a pointer to read branch
    std::vector<Double_t>* jets_eta_=nullptr;
    std::vector<Double_t>* jets_btags_=nullptr;
    std::vector<Double_t>* jets_btagsPT_=nullptr;
    std::vector<Double_t>* jets_flavour_=nullptr;

    //for fakeTau
    Double_t FR_weight_final;
    Double_t FR_weight_final_up;
    Double_t FR_weight_final_down;

private:
    TTree *m_tree;
    std::map<TString, std::variant<myBranch<Int_t> *, myBranch<Double_t> *, myBranch<Bool_t> *>> m_variableMap = {
        {tausT_num.n(), &tausT_num},
        {tausTT_num.n(), &tausTT_num},
        {tausTTT_num.n(), &tausTTT_num},
        {tausM_num.n(), &tausM_num},
        {tausF_genTauNum.n(), &tausF_genTauNum},
        {tausT_genTauNum.n(), &tausT_genTauNum},
        {bjetsM_num.n(), &bjetsM_num},
        {bjetsT_num.n(), &bjetsT_num},
        {bjetsPNM_num.n(), &bjetsPNM_num},
        {bjetsPTM_num.n(), &bjetsPTM_num},
        {bjetsPTT_num.n(), &bjetsPTT_num},
        {elesTopMVAT_num.n(), &elesTopMVAT_num},
        {muonsTopMVAT_num.n(), &muonsTopMVAT_num},
        {elesMVAT_num.n(), &elesMVAT_num},
        {muonsT_num.n(), &muonsT_num},
        {muonsT_1pt.n(), &muonsT_1pt},
        {elesMVAT_1pt.n(), &elesMVAT_1pt},
        {lepTopMVAT_1pt.n(), &lepTopMVAT_1pt},
        {lepTopMVAT_2pt.n(), &lepTopMVAT_2pt},
        {elesTopMVAF_num.n(), &elesTopMVAF_num},
        {muonsTopMVAF_num.n(), &muonsTopMVAF_num},
        {elesTopMVAF_1isTightPrompt.n(), &elesTopMVAF_1isTightPrompt},
        {elesTopMVAF_2isTightPrompt.n(), &elesTopMVAF_2isTightPrompt},
        {muonsTopMVAF_1isTightPrompt.n(), &muonsTopMVAF_1isTightPrompt},
        {muonsTopMVAF_2isTightPrompt.n(), &muonsTopMVAF_2isTightPrompt},
        {elesTopMVAF_1isTight.n(), &elesTopMVAF_1isTight},
        {elesTopMVAF_2isTight.n(), &elesTopMVAF_2isTight},
        {muonsTopMVAF_1isTight.n(), &muonsTopMVAF_1isTight},
        {muonsTopMVAF_2isTight.n(), &muonsTopMVAF_2isTight},
        {lepTopMVAF_isAR.n(), &lepTopMVAF_isAR},
        {lepTopMVAF_num.n(), &lepTopMVAF_num},




        {tausT_leptonsTopMVA_chargeMulti.n(), &tausT_leptonsTopMVA_chargeMulti},
        {EVENT_genWeight.n(), &EVENT_genWeight},
        {EVENT_prefireWeight.n(), &EVENT_prefireWeight},
        {PUweight_.n(), &PUweight_},
        {HLT_weight.n(), &HLT_weight},
        {tauT_IDSF_weight_new.n(), &tauT_IDSF_weight_new},
        {tauTT_IDSF_weight_new.n(), &tauTT_IDSF_weight_new},
        {elesTopMVAT_weight.n(), &elesTopMVAT_weight},
        {musTopMVAT_weight.n(), &musTopMVAT_weight},
        {btagShape_weight.n(), &btagShape_weight},
        {btagShapeR.n(), &btagShapeR},
        {btagWPMedium_weight.n(), &btagWPMedium_weight},
        {btagWPMedium_weight_up.n(), &btagWPMedium_weight_up},
        {btagWPMedium_weight_down.n(), &btagWPMedium_weight_down},
        {btagWPMT_weight.n(), &btagWPMT_weight},
        {btagWPMT_weight_up.n(), &btagWPMT_weight_up},
        {btagWPMT_weight_down.n(), &btagWPMT_weight_down},
        {eleMVAT_IDSF_weight.n(), &eleMVAT_IDSF_weight},

        {pdfWeight_up_.n(), &pdfWeight_up_},
        {pdfWeight_down_.n(), &pdfWeight_down_},
        {pdfWeightAlphaS_up_.n(), &pdfWeightAlphaS_up_},
        {pdfWeightAlphaS_down_.n(), &pdfWeightAlphaS_down_},
        {scaleWeight_up_.n(), &scaleWeight_up_},
        {scaleWeight_down_.n(), &scaleWeight_down_},
        {scaleWeightRe_up_.n(), &scaleWeightRe_up_},
        {scaleWeightRe_down_.n(), &scaleWeightRe_down_},
        {scaleWeightFa_up_.n(), &scaleWeightFa_up_},
        {scaleWeightFa_down_.n(), &scaleWeightFa_down_},

    {jets_num.n(), &jets_num},
    {jets_rationHT_4toRest.n(), &jets_rationHT_4toRest},
    {jets_MHT.n(), &jets_MHT},
    {jets_HT.n(), &jets_HT},
    {jets_invariantMass.n(), &jets_invariantMass},
    {jets_transMass.n(), &jets_transMass},
    {jets_minDeltaR.n(), &jets_minDeltaR},
    {jets_centrality.n(), &jets_centrality},
    {jets_bScore.n(), &jets_bScore},
    {jets_average_deltaR.n(), &jets_average_deltaR},
    {jets_4largestBscoreSum.n(), &jets_4largestBscoreSum},
    {jets_4largestBscoreMulti.n(), &jets_4largestBscoreMulti},
    {jets_HTDivideMET.n(), &jets_HTDivideMET},
    {jets_METDivideHT.n(), &jets_METDivideHT}, 
    {jets_sphericity.n(), &jets_sphericity}, 
    {jets_aplanarity.n(), &jets_aplanarity},
    {jets_tausT_invariantMass.n(), &jets_tausT_invariantMass},
    {jets_tausT_minDeltaR.n(), &jets_tausT_minDeltaR},
    {jets_1pt.n(), &jets_1pt},
    {jets_2pt.n(), &jets_2pt},
    {jets_3pt.n(), &jets_3pt},
    {jets_4pt.n(), &jets_4pt},
    {jets_5pt.n(), &jets_5pt},
    {jets_6pt.n(), &jets_6pt},
    {jets_7pt.n(), &jets_7pt},
    {jets_8pt.n(), &jets_8pt},
    {jets_9pt.n(), &jets_9pt},
    {jets_1btag.n(), &jets_1btag},
    {jets_2btag.n(), &jets_2btag},
    {jets_3btag.n(), &jets_3btag},
    {jets_4btag.n(), &jets_4btag},
    {jets_5btag.n(), &jets_5btag},
    {jets_6btag.n(), &jets_6btag},
    {jets_7btag.n(), &jets_7btag},
    {jets_8btag.n(), &jets_8btag},

        {MET_pt.n(), &MET_pt},

        {bjetsM_invariantMass.n(), &bjetsM_invariantMass},
        {bjetsM_HT.n(), &bjetsM_HT},
        {bjetsM_MHT.n(), &bjetsM_MHT},
        {bjetsM_transMass.n(), &bjetsM_transMass},
        {bjetsM_minDeltaR.n(), &bjetsM_minDeltaR},
        {bjetsM_2leptons2_stransMass.n(), &bjetsM_2leptons2_stransMass},
        {bjetsM_2tauT1lep1_stransMass.n(), &bjetsM_2tauT1lep1_stransMass},
        {bjetsM_2tauF1lep1_stransMass.n(), &bjetsM_2tauF1lep1_stransMass},
        {bjetsM_2MET_stransMass.n(), &bjetsM_2MET_stransMass},
        {bjetsM_leptons_minDeltaR.n(), &bjetsM_leptons_minDeltaR},
        {bjetsM_tausT_minDeltaR.n(), &bjetsM_tausT_minDeltaR},
        {bjetsM_tausF_minDeltaR.n(), &bjetsM_tausF_minDeltaR},
        {bjetsM_1pt.n(), &bjetsM_1pt},
        {bjetsM_2pt.n(), &bjetsM_2pt},
        {bjetsM_3pt.n(), &bjetsM_3pt},

        {bjetsT_invariantMass.n(), &bjetsT_invariantMass},
        {bjetsT_HT.n(), &bjetsT_HT},
        {bjetsT_MHT.n(), &bjetsT_MHT},
        {bjetsT_transMass.n(), &bjetsT_transMass},
        {bjetsT_minDeltaR.n(), &bjetsT_minDeltaR},
        {bjetsT_2leptons2_stransMass.n(), &bjetsT_2leptons2_stransMass},
        {bjetsT_2tauT1lep1_stransMass.n(), &bjetsT_2tauT1lep1_stransMass},
        {bjetsT_2tauF1lep1_stransMass.n(), &bjetsT_2tauF1lep1_stransMass},
        {bjetsT_2MET_stransMass.n(), &bjetsT_2MET_stransMass},
        {bjetsT_leptons_minDeltaR.n(), &bjetsT_leptons_minDeltaR},
        {bjetsT_tausT_minDeltaR.n(), &bjetsT_tausT_minDeltaR},
        {bjetsT_tausF_minDeltaR.n(), &bjetsT_tausF_minDeltaR},
        {bjetsT_1pt.n(), &bjetsT_1pt},
        {bjetsT_2pt.n(), &bjetsT_2pt},
        {bjetsT_3pt.n(), &bjetsT_3pt},

        {tausT_1pt.n(), &tausT_1pt},
        {tausT_1eta.n(), &tausT_1eta},
        {tausT_1phi.n(), &tausT_1phi},
        {tausT_HT.n(), &tausT_HT},
        {tausT_MHT.n(), &tausT_MHT},
        {tausT_invariantMass.n(), &tausT_invariantMass},
        {tausT_1lepton1_deltaR.n(), &tausT_1lepton1_deltaR},
        {tausT_1Met_transMass.n(), &tausT_1Met_transMass},
        {tausT_1lepton1Met1_stransMass.n(), &tausT_1lepton1Met1_stransMass},
        {tausT_leptonsT_invariantMass.n(), &tausT_leptonsT_invariantMass},
        {tausT_leptonsTMVA_minDeltaR.n(), &tausT_leptonsTMVA_minDeltaR},
        {tausT_leptonsT_transMass.n(), &tausT_leptonsT_transMass},
        {tausT_1charge.n(), &tausT_1charge},
        {tausT_1lepton1_charge.n(), &tausT_1lepton1_charge},
        {tausT_leptons_charge.n(), &tausT_leptons_charge},

        {tausTT_1pt.n(), &tausTT_1pt},
        {tausTT_1eta.n(), &tausTT_1eta},
        {tausTT_1phi.n(), &tausTT_1phi},
        {tausTT_HT.n(), &tausTT_HT},
        {tausTT_MHT.n(), &tausTT_MHT},
        {tausTT_invariantMass.n(), &tausTT_invariantMass},
        {tausTT_1lepton1_deltaR.n(), &tausTT_1lepton1_deltaR},
        {tausTT_1Met_transMass.n(), &tausTT_1Met_transMass},
        {tausTT_1lepton1Met1_stransMass.n(), &tausTT_1lepton1Met1_stransMass},
        {tausTT_leptonsT_invariantMass.n(), &tausTT_leptonsT_invariantMass},
        {tausTT_leptonsTMVA_minDeltaR.n(), &tausTT_leptonsTMVA_minDeltaR},
        {tausTT_leptonsT_transMass.n(), &tausTT_leptonsT_transMass},
        {tausTT_1charge.n(), &tausTT_1charge},




        {muonsTopMVAT_1pt.n(), &muonsTopMVAT_1pt},
        {elesTopMVAT_1pt.n(), &elesTopMVAT_1pt},
        {elesTopMVAT_1eta.n(), &elesTopMVAT_1eta},

        {tausF_num.n(), &tausF_num},
        {tausF_prongNum.n(), &tausF_prongNum},
        {tausF_1jetPt.n(), &tausF_1jetPt},
        {tausF_1eta.n(), &tausF_1eta},
        {tausF_1jetEtaAbs.n(), &tausF_1jetEtaAbs},
        {tausF_1charge.n(), &tausF_1charge},
        {tausF_1decayMode.n(), &tausF_1decayMode},
        {tausF_1prongNum.n(), &tausF_1prongNum},
        {tausF_1Met_transMass.n(), &tausF_1Met_transMass},
        {tausF_invariantMass.n(), &tausF_invariantMass},
        {tausF_jet_invariantMass.n(), &tausF_jet_invariantMass},
        {tausF_jet1_Met_transMass.n(), &tausF_jet1_Met_transMass},

        {tausT_1decayMode.n(), &tausT_1decayMode},
        {tausTT_1decayMode.n(), &tausTT_1decayMode},
        {tausTT_1lepton1_charge.n(), &tausTT_1lepton1_charge},
        {tausTTT_1lepton1_charge.n(), &tausTTT_1lepton1_charge},
        {tausM_1lepton1_charge.n(), &tausM_1lepton1_charge},
        {tausF_1pt.n(), &tausF_1pt},

        {tausT_1genFlavour.n(), &tausT_1genFlavour},
        {tausT_prongNum.n(), &tausT_prongNum},
        {tausF_1genFlavour.n(), &tausF_1genFlavour},
        {tausTT_1genFlavour.n(), &tausTT_1genFlavour},
        {tausTTT_1genFlavour.n(), &tausTTT_1genFlavour},
        {tausM_1genFlavour.n(), &tausM_1genFlavour},

        {EVENT_prefireWeight_up.n(), &EVENT_prefireWeight_up},
        {PUweight_up_.n(), &PUweight_up_},
        {HLT_weight_stats_up.n(), &HLT_weight_stats_up},
        {tauT_IDSF_weight_new_vsjet_up.n(), &tauT_IDSF_weight_new_vsjet_up},
        {elesTopMVAT_weight_up.n(), &elesTopMVAT_weight_up},
        {musTopMVAT_weight_up.n(), &musTopMVAT_weight_up},
        {tauT_IDSF_weight_new_vsmu_up.n(), &tauT_IDSF_weight_new_vsmu_up},
        {tauT_IDSF_weight_new_vsele_up.n(), &tauT_IDSF_weight_new_vsele_up},
        {btagShape_weight_jes_up.n(), &btagShape_weight_jes_up},
        {btagShape_weight_hf_up.n(), &btagShape_weight_hf_up},
        {btagShape_weight_lf_up.n(), &btagShape_weight_lf_up},
        {btagShape_weight_hfstats1_up.n(), &btagShape_weight_hfstats1_up},
        {btagShape_weight_hfstats2_up.n(), &btagShape_weight_hfstats2_up},
        {btagShape_weight_lfstats1_up.n(), &btagShape_weight_lfstats1_up},
        {btagShape_weight_lfstats2_up.n(), &btagShape_weight_lfstats2_up},
        {btagShape_weight_cferr1_up.n(), &btagShape_weight_cferr1_up},
        {btagShape_weight_cferr2_up.n(), &btagShape_weight_cferr2_up},

        {EVENT_prefireWeight_down.n(), &EVENT_prefireWeight_down},
        {PUweight_down_.n(), &PUweight_down_},
        {HLT_weight_stats_down.n(), &HLT_weight_stats_down},
        {tauT_IDSF_weight_new_vsjet_down.n(), &tauT_IDSF_weight_new_vsjet_down},
        {elesTopMVAT_weight_down.n(), &elesTopMVAT_weight_down},
        {musTopMVAT_weight_down.n(), &musTopMVAT_weight_down},
        {tauT_IDSF_weight_new_vsmu_down.n(), &tauT_IDSF_weight_new_vsmu_down},
        {tauT_IDSF_weight_new_vsele_down.n(), &tauT_IDSF_weight_new_vsele_down},
        {btagShape_weight_jes_down.n(), &btagShape_weight_jes_down},
        {btagShape_weight_hf_down.n(), &btagShape_weight_hf_down},
        {btagShape_weight_lf_down.n(), &btagShape_weight_lf_down},
        {btagShape_weight_hfstats1_down.n(), &btagShape_weight_hfstats1_down},
        {btagShape_weight_hfstats2_down.n(), &btagShape_weight_hfstats2_down},
        {btagShape_weight_lfstats1_down.n(), &btagShape_weight_lfstats1_down},
        {btagShape_weight_lfstats2_down.n(), &btagShape_weight_lfstats2_down},
        {btagShape_weight_cferr1_down.n(), &btagShape_weight_cferr1_down},
        {btagShape_weight_cferr2_down.n(), &btagShape_weight_cferr2_down},

        {HLT_PFHT450_SixJet40_BTagCSV_p056.n(), &HLT_PFHT450_SixJet40_BTagCSV_p056},
        {HLT_PFHT400_SixJet30_DoubleBTagCSV_p056.n(), &HLT_PFHT400_SixJet30_DoubleBTagCSV_p056},
        {HLT_PFJet450.n(), &HLT_PFJet450},
        {HLT_IsoMu24.n(), &HLT_IsoMu24},
        {HLT_IsoMu27.n(), &HLT_IsoMu27},

        {HLT_PFJet500.n(), &HLT_PFJet500},
        {HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5.n(), &HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5},
        {HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2.n(), &HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2},
        {HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5.n(), &HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5},
        {HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59.n(), &HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59},
        {HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94.n(), &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94},
        {HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5.n(), &HLT_PFHT330PT30_QuadPFJet_75_60_45_40_TriplePFBTagDeepCSV_4p5},
        //  2017
        {HLT_PFHT430_SixJet40_BTagCSV_p080.n(), &HLT_PFHT430_SixJet40_BTagCSV_p080},
        {HLT_PFHT380_SixJet32_DoubleBTagCSV_p075.n(), &HLT_PFHT380_SixJet32_DoubleBTagCSV_p075},
        {HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2.n(), &HLT_PFHT380_SixPFJet32_DoublePFBTagCSV_2p2},
        {HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59.n(), &HLT_PFHT450_SixPFJet36_PFBTagDeepJet_1p59},
        {HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94.n(), &HLT_PFHT400_SixPFJet32_DoublePFBTagDeepJet_2p94},
        {HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0.n(), &HLT_PFHT300PT30_QuadPFJet_75_60_45_40_TriplePFBTagCSV_3p0},
        {HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07.n(), &HLT_HT300PT30_QuadJet_75_60_45_40_TripeCSV_p07},
        {HLT_PFHT1050.n(), &HLT_PFHT1050},

        {PV_npvsGood.n(), &PV_npvsGood},
    };



};
#endif