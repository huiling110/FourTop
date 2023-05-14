// I will just have some class to begin with. doesn't need to be perfect, always room to improve:)
// maybe have a base class with only value as member variables to save memory
#ifndef MYEVENTCLASS_H
#define MYEVENTCLASS_H

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
        std::cout << "initialize event class by SetBranchAddress()\n";
        for (auto it = m_variableMap.begin(); it != m_variableMap.end(); ++it)
        {
            m_tree->SetBranchAddress(it->second->n(), it->second->a());
        };
        for (auto it = m_variableMapDou.begin(); it != m_variableMapDou.end(); ++it)
        {
            m_tree->SetBranchAddress(it->second->n(), it->second->a());
        };
    }
    ~event()
    {
        delete m_tree;
    }

    myBranch<Int_t> tausT_number{"tausT_number"};
    myBranch<Int_t> jets_number{"jets_number"};
    myBranch<Int_t> bjetsM_num{"bjetsM_num"};
    myBranch<Int_t> elesTopMVAT_number{"elesTopMVAT_number"};
    myBranch<Int_t> muonsTopMVAT_number{"muonsTopMVAT_number"};
    myBranch<Int_t> tausT_leptonsTopMVA_chargeMulti{"tausT_leptonsTopMVA_chargeMulti"};
    myBranch<Double_t> jets_HT{"jets_HT"};
    myBranch<Double_t> jets_6pt{"jets_6pt"};
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
    std::map<TString, myBranch<Int_t> *> m_variableMap = {
        {tausT_number.n(), &tausT_number},
        {jets_number.n(), &jets_number},
        {bjetsM_num.n(), &bjetsM_num},
        {elesTopMVAT_number.n(), &elesTopMVAT_number},
        {muonsTopMVAT_number.n(), &muonsTopMVAT_number},
        {tausT_leptonsTopMVA_chargeMulti.n(), &tausT_leptonsTopMVA_chargeMulti},
    };
    std::map<TString, myBranch<Double_t> *> m_variableMapDou = {
        {jets_HT.n(), &jets_HT},
        {jets_6pt.n(), &jets_6pt},
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