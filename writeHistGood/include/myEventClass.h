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
            else
            {
                myBranch<Double_t> *bra = std::get<myBranch<Double_t> *>(it->second);
                // std::cout << bra->n() << "\n";
                m_tree->SetBranchStatus(bra->n(), 1);
                m_tree->SetBranchAddress(bra->n(), bra->a());
            };
        };

        m_tree->SetBranchStatus("jets_pt_", 1);
        m_tree->SetBranchStatus("jets_eta_", 1);
        m_tree->SetBranchStatus("jets_btags_", 1);
        m_tree->SetBranchStatus("jets_flavour_", 1);
        m_tree->SetBranchAddress("jets_pt_", &jets_pt_);
        m_tree->SetBranchAddress("jets_eta_", &jets_eta_);
        m_tree->SetBranchAddress("jets_btags_", &jets_btags_);
        m_tree->SetBranchAddress("jets_flavour_", &jets_flavour_);


        std::cout << "Done initializing event class \n";
    };
    ~event()
    {
        delete m_tree;
    };
    std::variant<Int_t, Double_t> getByName(TString branchName)
    {
        assert(m_variableMap.count(branchName));
        //  if (!(m_variableMap.count(branchName)))
        // {
        //     std::cout << "BAD!!!  branch doesn't exist in the event class object yet\n";
        // }
        std::variant<Int_t, Double_t> a;
        if (std::holds_alternative<myBranch<Int_t> *>(m_variableMap[branchName]))
        {
            a = (std::get<myBranch<Int_t> *>(m_variableMap[branchName]))->v();
        }
        else
        {
            a = (std::get<myBranch<Double_t> *>(m_variableMap[branchName]))->v();
        }
        return a;
    };
    // branches for selection and weight
    myBranch<Int_t> tausT_num{"tausT_num"};
    myBranch<Int_t> tausF_genTauNum{"tausF_genTauNum"};
    myBranch<Int_t> tausT_genTauNum{"tausT_genTauNum"};
    myBranch<Int_t> jets_num{"jets_num"};
    myBranch<Int_t> bjetsM_num{"bjetsM_num"};
    myBranch<Int_t> bjetsT_num{"bjetsT_num"};
    myBranch<Int_t> elesTopMVAT_num{"elesTopMVAT_num"};
    myBranch<Int_t> muonsTopMVAT_num{"muonsTopMVAT_num"};
    myBranch<Int_t> elesMVAT_num{"elesMVAT_num"};
    myBranch<Int_t> muonsT_num{"muonsT_num"};
    myBranch<Double_t> jets_HT{"jets_HT"};
    myBranch<Double_t> EVENT_genWeight{"EVENT_genWeight"};
    myBranch<Double_t> EVENT_prefireWeight{"EVENT_prefireWeight"};
    myBranch<Double_t> PUweight_{"PUweight_"};
    myBranch<Double_t> HLT_weight{"HLT_weight"};
    myBranch<Double_t> tauT_IDSF_weight_new{"tauT_IDSF_weight_new"};
    myBranch<Double_t> elesTopMVAT_weight{"elesTopMVAT_weight"};
    myBranch<Double_t> musTopMVAT_weight{"musTopMVAT_weight"};
    myBranch<Double_t> btagShape_weight{"btagShape_weight"};
    myBranch<Double_t> btagShapeR{"btagShapeR"};
    myBranch<Double_t> btagWPMedium_weight{"btagWPMedium_weight"};
    myBranch<Double_t> btagWPMedium_weight_up{"btagWPMedium_weight_up"};
    myBranch<Double_t> btagWPMedium_weight_down{"btagWPMedium_weight_down"};
    // branches for MVA
    myBranch<Int_t> tausT_leptonsTopMVA_chargeMulti{"tausT_leptonsTopMVA_chargeMulti"};
    myBranch<Double_t> jets_bScore{"jets_bScore"};
    myBranch<Double_t> jets_rationHT_4toRest{"jets_rationHT_4toRest"};
    myBranch<Double_t> jets_1btag{"jets_1btag"};
    myBranch<Double_t> jets_transMass{"jets_transMass"};
    myBranch<Double_t> jets_average_deltaR{"jets_average_deltaR"};
    myBranch<Double_t> bjetsM_invariantMass{"bjetsM_invariantMass"};
    myBranch<Double_t> bjetsM_minDeltaR{"bjetsM_minDeltaR"};
    myBranch<Double_t> bjetsM_2pt{"bjetsM_2pt"};
    myBranch<Double_t> bjetsM_HT{"bjetsM_HT"};
    myBranch<Double_t> bjetsT_HT{"bjetsT_HT"};
    myBranch<Double_t> tausT_leptonsT_invariantMass{"tausT_leptonsT_invariantMass"};
    myBranch<Double_t> tausT_1pt{"tausT_1pt"};
    myBranch<Double_t> jets_1pt{"jets_1pt"};
    myBranch<Double_t> jets_2pt{"jets_2pt"};
    myBranch<Double_t> jets_3pt{"jets_3pt"};
    myBranch<Double_t> jets_4pt{"jets_4pt"};
    myBranch<Double_t> jets_5pt{"jets_5pt"};
    myBranch<Double_t> jets_6pt{"jets_6pt"};
    myBranch<Double_t> jets_7pt{"jets_7pt"};
    // myBranch<Double_t> jets_leading2invariantMass{"jets_leading2invariantMass"};//not in tree
    // myBranch<Double_t> jets_4largestBscoreMulti{"jets_4largestBscoreMulti"};
    myBranch<Double_t> jets_2btag{"jets_2btag"};
    myBranch<Double_t> jets_3btag{"jets_3btag"};
    myBranch<Double_t> jets_4btag{"jets_4btag"};
    myBranch<Double_t> jets_5btag{"jets_5btag"};
    myBranch<Double_t> jets_6btag{"jets_6btag"};
    myBranch<Double_t> MET_pt{"MET_pt"};
    myBranch<Double_t> bjetsM_MHT{"bjetsM_MHT"};
    myBranch<Double_t> bjetsM_1pt{"bjetsM_1pt"};
    myBranch<Double_t> tausT_1eta{"tausT_1eta"};
    myBranch<Double_t> tausT_1phi{"tausT_1phi"};
    myBranch<Double_t> tausT_HT{"tausT_HT"};
    myBranch<Double_t> tausT_MHT{"tausT_MHT"};
    myBranch<Double_t> muonsTopMVAT_1pt{"muonsTopMVAT_1pt"};
    myBranch<Double_t> elesTopMVAT_1pt{"elesTopMVAT_1pt"};
    // myBranch<Double_t>{""};

    // branches for fakeTau;
    myBranch<Int_t> tausF_prongNum{"tausF_prongNum"};
    myBranch<Double_t> tausF_1jetPt{"tausF_1jetPt"};
    myBranch<Double_t> tausF_1eta{"tausF_1eta"};
    myBranch<Int_t> tausF_num{"tausF_num"};

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


    //for btag eff study
    std::vector<Double_t>* jets_pt_=nullptr;//???not sure why it has to be a pointer to read branch
    std::vector<Double_t>* jets_eta_=nullptr;
    std::vector<Double_t>* jets_btags_=nullptr;
    std::vector<Double_t>* jets_flavour_=nullptr;


private:
    TTree *m_tree;
    std::map<TString, std::variant<myBranch<Int_t> *, myBranch<Double_t> *>> m_variableMap = {
        {tausT_num.n(), &tausT_num},
        {tausF_genTauNum.n(), &tausF_genTauNum},
        {tausT_genTauNum.n(), &tausT_genTauNum},
        {jets_num.n(), &jets_num},
        {bjetsM_num.n(), &bjetsM_num},
        {bjetsT_num.n(), &bjetsT_num},
        {elesTopMVAT_num.n(), &elesTopMVAT_num},
        {muonsTopMVAT_num.n(), &muonsTopMVAT_num},
        {elesMVAT_num.n(), &elesMVAT_num},
        {muonsT_num.n(), &muonsT_num},
        {tausT_leptonsTopMVA_chargeMulti.n(), &tausT_leptonsTopMVA_chargeMulti},
        {jets_HT.n(), &jets_HT},
        {jets_6pt.n(), &jets_6pt},
        {EVENT_genWeight.n(), &EVENT_genWeight},
        {EVENT_prefireWeight.n(), &EVENT_prefireWeight},
        {PUweight_.n(), &PUweight_},
        {HLT_weight.n(), &HLT_weight},
        {tauT_IDSF_weight_new.n(), &tauT_IDSF_weight_new},
        {elesTopMVAT_weight.n(), &elesTopMVAT_weight},
        {musTopMVAT_weight.n(), &musTopMVAT_weight},
        {btagShape_weight.n(), &btagShape_weight},
        {btagShapeR.n(), &btagShapeR},
        {btagWPMedium_weight.n(), &btagWPMedium_weight},
        {btagWPMedium_weight_up.n(), &btagWPMedium_weight_up},
        {btagWPMedium_weight_down.n(), &btagWPMedium_weight_down},

        {jets_bScore.n(), &jets_bScore},
        {jets_rationHT_4toRest.n(), &jets_rationHT_4toRest},
        {jets_1btag.n(), &jets_1btag},
        {jets_transMass.n(), &jets_transMass},
        {jets_average_deltaR.n(), &jets_average_deltaR},
        {bjetsM_invariantMass.n(), &bjetsM_invariantMass},
        {bjetsM_minDeltaR.n(), &bjetsM_minDeltaR},
        {bjetsM_2pt.n(), &bjetsM_2pt},
        {bjetsM_HT.n(), &bjetsM_HT},
        {bjetsT_HT.n(), &bjetsT_HT},
        {tausT_leptonsT_invariantMass.n(), &tausT_leptonsT_invariantMass},
        {tausT_1pt.n(), &tausT_1pt},
        {jets_1pt.n(), &jets_1pt},
        {jets_2pt.n(), &jets_2pt},
        {jets_3pt.n(), &jets_3pt},
        {jets_4pt.n(), &jets_4pt},
        {jets_5pt.n(), &jets_5pt},
        {jets_6pt.n(), &jets_6pt},
        {jets_7pt.n(), &jets_7pt},
        // {jets_leading2invariantMass.n(), &jets_leading2invariantMass},
        // {jets_4largestBscoreMulti.n(), &jets_4largestBscoreMulti},
        {jets_2btag.n(), &jets_2btag},
        {jets_3btag.n(), &jets_3btag},
        {jets_4btag.n(), &jets_4btag},
        {jets_5btag.n(), &jets_5btag},
        {jets_6btag.n(), &jets_6btag},
        {MET_pt.n(), &MET_pt},
        {bjetsM_MHT.n(), &bjetsM_MHT},
        {bjetsM_1pt.n(), &bjetsM_1pt},
        {tausT_1eta.n(), &tausT_1eta},
        {tausT_1phi.n(), &tausT_1phi},
        {tausT_HT.n(), &tausT_HT},
        {tausT_MHT.n(), &tausT_MHT},
        {muonsTopMVAT_1pt.n(), &muonsTopMVAT_1pt},
        {elesTopMVAT_1pt.n(), &elesTopMVAT_1pt},

        {tausF_prongNum.n(), &tausF_prongNum},
        {tausF_1jetPt.n(), &tausF_1jetPt},
        {tausF_1eta.n(), &tausF_1eta},
        {tausF_num.n(), &tausF_num},

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
    };



};
#endif