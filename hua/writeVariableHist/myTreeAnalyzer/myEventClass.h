// I will just have some class to begin with. doesn't need to be perfect, always room to improve:)
// maybe have a base class with only value as member variables to save memory
#ifndef MYEVENTCLASS_H
#define MYEVENTCLASS_H
#include <variant>
#include <map>
#include <cassert>

#include "TString.h"
#include "TTree.h"

template <typename T>
class myBranch
{
public:
    myBranch(TString branchName) : m_branchName{branchName}
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
    myBranch<Int_t> jets_number{"jets_number"};
    myBranch<Int_t> bjetsM_num{"bjetsM_num"};
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
    myBranch<Double_t> tausT_leptonsT_invariantMass{"tausT_leptonsT_invariantMass"};
    myBranch<Double_t> tausT_1pt{"tausT_1pt"};
    // myBranch<Double_t>{""};

private:
    TTree *m_tree;
    std::map<TString, std::variant<myBranch<Int_t> *, myBranch<Double_t> *>> m_variableMap = {
        {tausT_number.n(), &tausT_number},
        {jets_number.n(), &jets_number},
        {bjetsM_num.n(), &bjetsM_num},
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
        {tausT_leptonsT_invariantMass.n(), &tausT_leptonsT_invariantMass},
        {tausT_1pt.n(), &tausT_1pt},
    };
};
#endif