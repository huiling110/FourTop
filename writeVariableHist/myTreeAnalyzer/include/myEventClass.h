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
    myBranch(TString branchName="") : m_branchName{branchName}
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
        for (auto it = m_variableMap.begin(); it != m_variableMap.end(); ++it)
        {
            if (std::holds_alternative<myBranch<Int_t> *>(it->second))
            {
                myBranch<Int_t> *bra = std::get<myBranch<Int_t> *>(it->second);
                m_tree->SetBranchAddress(bra->n(), bra->a());
            }
            else
            {
                myBranch<Double_t> *bra = std::get<myBranch<Double_t> *>(it->second);
                m_tree->SetBranchAddress(bra->n(), bra->a());
            };
        };
        // for (auto it = m_variableMap.begin(); it != m_variableMap.end(); ++it)
        // {
        //     m_tree->SetBranchAddress(it->second->n(), it->second->a());
        // };
        // for (auto it = m_variableMapDou.begin(); it != m_variableMapDou.end(); ++it)
        // {
        //     m_tree->SetBranchAddress(it->second->n(), it->second->a());
        // };
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
    myBranch<Int_t> tausT_number{"tausT_number"};
    myBranch<Int_t> tausF_genTauNum{"tausF_genTauNum"};
    myBranch<Int_t> tausT_genTauNum{"tausT_genTauNum"};
    myBranch<Int_t> jets_number{"jets_number"};
    myBranch<Int_t> bjetsM_num{"bjetsM_num"};
    myBranch<Int_t> bjetsT_num{"bjetsT_num"};
    myBranch<Int_t> elesTopMVAT_number{"elesTopMVAT_number"};
    myBranch<Int_t> muonsTopMVAT_number{"muonsTopMVAT_number"};
    myBranch<Double_t> jets_HT{"jets_HT"};
    myBranch<Double_t> jets_6pt{"jets_6pt"};
    myBranch<Double_t> EVENT_genWeight{"EVENT_genWeight"};
    myBranch<Double_t> EVENT_prefireWeight{"EVENT_prefireWeight"};
    myBranch<Double_t> PUweight_{"PUweight_"};
    myBranch<Double_t> HLT_weight{"HLT_weight"};
    myBranch<Double_t> tauT_IDSF_weight_new{"tauT_IDSF_weight_new"};
    myBranch<Double_t> elesTopMVAT_weight{"elesTopMVAT_weight"};
    myBranch<Double_t> musTopMVAT_weight{"musTopMVAT_weight"};
    myBranch<Double_t> btagShape_weight{"btagShape_weight"};
    myBranch<Double_t> btagShapeR{"btagShapeR"};
    // branches for MVA
    myBranch<Int_t> tausT_leptonsTopMVA_chargeMulti{"tausT_leptonsTopMVA_chargeMulti"};
    myBranch<Double_t> jets_bScore{"jets_bScore"};
    myBranch<Double_t> jets_5pt{"jets_5pt"};
    myBranch<Double_t> jets_7pt{"jets_7pt"};
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
    // myBranch<Double_t>{""};
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

private:
    TTree *m_tree;
    std::map<TString, std::variant<myBranch<Int_t> *, myBranch<Double_t> *>> m_variableMap = {
        {tausT_number.n(), &tausT_number},
        {tausF_genTauNum.n(), &tausF_genTauNum},
        {tausT_genTauNum.n(), &tausT_genTauNum},
        {jets_number.n(), &jets_number},
        {bjetsM_num.n(), &bjetsM_num},
        {bjetsT_num.n(), &bjetsT_num},
        {elesTopMVAT_number.n(), &elesTopMVAT_number},
        {muonsTopMVAT_number.n(), &muonsTopMVAT_number},
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

        {jets_bScore.n(), &jets_bScore},
        {jets_5pt.n(), &jets_5pt},
        {jets_7pt.n(), &jets_7pt},
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