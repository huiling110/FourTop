#ifndef PROCESSCLASS_H
#define PROCESSCLASS_H
 
#include "../../../myLibrary/commenFunction.h"
#include "../../../src_cpp/lumiAndCrossSection.h"

class Process
{
public:
    Process(const TString filePath)
    {
        m_file = new TFile(filePath);
        m_tree = (TTree *)m_file->Get("newtree");

        //to be put in myLibrary
        TObjArray *tokens = filePath.Tokenize("/");
        TString fileName = ((TObjString *)tokens->Last())->GetString();
        m_name = fileName.Remove(fileName.Last('.'), fileName.Length() - fileName.Last('.'));
        std::cout << "fileName=" << m_name << "\n";
        tokens->Delete();

        m_era = TTTT::getEra2(filePath);
        // m_isBG = TTTT::isBG(m_name);
    }
    ~Process()
    {
        // m_file->Close();
        // delete m_file;
    }
    TTree *getTree()
    {
        return m_tree;
    }

    TString getName()
    {
        return m_name;
    }

    Double_t getScale(){
        Double_t genWeightSum = TTTT::getGenSum(m_file->GetName());
        Double_t processScale = ((TTTT::lumiMap.at(m_era)* TTTT::crossSectionMap.at(m_name)) / genWeightSum);
        return processScale;
    }

    Bool_t isbg(Bool_t ifVLL){
        return TTTT::isBG(m_name, ifVLL);
    }

private:
    TFile *m_file;
    TTree *m_tree;
    TString m_name;
    TString m_era;
    // Bool_t m_isBG;
};

#endif
