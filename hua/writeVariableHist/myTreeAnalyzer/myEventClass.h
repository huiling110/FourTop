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
    myBranch<Double_t> jets_HT{"jets_HT"};
    myBranch<Double_t> jets_6pt{"jets_6pt"};

private:
    TTree *m_tree;
    std::map<TString, myBranch<Int_t> *> m_variableMap = {
        {tausT_number.n(), &tausT_number},
        {jets_number.n(), &jets_number},
        {bjetsM_num.n(), &bjetsM_num},
    };
    std::map<TString, myBranch<Double_t> *> m_variableMapDou = {
        {jets_HT.n(), &jets_HT},
        {jets_6pt.n(), &jets_6pt},
    };
};
#endif