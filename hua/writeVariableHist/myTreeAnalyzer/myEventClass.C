// I will just have some class to begin with. doesn't need to be perfect, always room to improve:)
// maybe have a base class with only value as member variables to save memory
#include "TString.h"
#include "TTree.h"

class myBranch
{
public:
    myBranch(TString branchName) : m_branchName{branchName}
    {
    }
    Int_t v()
    {
        return m_branchValue;
    }
    Int_t *a()
    {
        return &m_branchValue;
    }
    TString n()
    {
        return m_branchName;
    }

private:
    TString m_branchName;
    Int_t m_branchValue;
};

class event
{
    // be able to access branch value with string
    // can directly access memeber variable too
public:
    event(TTree *tree) : m_tree{tree}
    { // how to loop through all member variables?
        m_tree->SetBranchAddress(tausT_number.n(), tausT_number.a());
        m_tree->SetBranchAddress(jets_number.n(), jets_number.a());
    }
    ~event()
    {
        delete m_tree;
    }

    // setBranchAddress()
    // {
    // }
    // addBranch(TString branchName)
    // {
    // }
    // Int_t tausT_number;

    myBranch tausT_number{"tausT_number"};
    myBranch jets_number{"jets_number"};

private:
    TTree *m_tree;
    std::map<TString, myBranch *> m_variableLookupTable = {
        {tausT_number.n(), &tausT_number},
        {jets_number.n(), &jets_number},
    };
    // std::vector<myBranch *> = {
    //     &m_tausT_number,
    //     &m_jets_number,
    // }
};