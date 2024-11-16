#ifndef TREEANALYZER_H
#define TREEANALYZER_H

#include <iostream>
#include <vector>
#include <variant>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1D.h"
#include "TMVA/Reader.h"

#include "histsForRegionsMap_class.h"
#include "functions.h"
#include "../../myLibrary/commenFunction.h"

#include "myEventClass.h"

class treeAnalyzer
{
public:
    treeAnalyzer(const TString inputDir, const TString process, TString outVersion = "v0", TString channel="1tau1l", Bool_t isTest = kTRUE) : m_inputDir{inputDir}, m_processName{process}, m_channel{channel}, m_isTest{isTest}
    {
        m_file = new TFile(m_inputDir + m_processName + ".root", "READ"); //???what is this initialization
        if (!m_file || m_file->IsZombie())
        {
            std::cout << "Error: could not open file!" << m_file->GetName() << std::endl;
        }
        else
        {
            std::cout << "input file: " << m_file->GetName() << "\n";
            m_tree = (TTree *)m_file->Get("newtree");
        }

        m_era = TTTT::getEra2(m_inputDir);
        m_isData = TTTT::getIsData(m_inputDir);
        m_isRun3 = TTTT::isRun3(m_era);
        std::cout << "m_era=" << m_era <<" m_isRun3="<<m_isRun3<< " m_isData=" << m_isData << "  m_isTest=" << m_isTest << "\n";
        m_isFakeLepton = m_processName.Contains("fakeLepton");
        m_isFakeTau = m_processName.Contains("fakeTau");
        std::cout << "m_isFakeLepton=" << m_isFakeLepton << " m_isFakeTau=" << m_isFakeTau << "\n";

        std::cout << "m_processName: " << m_processName <<"  m_channel: "<<m_channel<< "\n";
        m_outFile = new TFile(m_inputDir + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");

        e = new event(m_tree);
    };
    ~treeAnalyzer();

    void Init();
    void LoopTree();
    // void sysRegionsFill(Double_t bdtScore, Double_t basicWeight, Bool_t SR1tau1l, Bool_t CR11tau1l, Bool_t CR21tau1l);
    void sysRegionsFill(Double_t bdtScore, Double_t basicWeight, Bool_t SR1tau1l, TString region);
    void Terminate();

private:
    TString m_inputDir;
    TString m_processName;
    TString m_channel;
    Bool_t m_isTest = kTRUE;
    TTree *m_tree;
    TFile *m_file;
    TString m_era = "2016";
    Bool_t m_isData = kFALSE;
    Bool_t m_isRun3 = kFALSE;
    TString m_outputFolder;
    TFile *m_outFile;
    TH1D *cutFlowHist = new TH1D("cutFlow", "cutFlow", 3, 0, 3);
    event *e;
    Bool_t m_isFakeLepton = kFALSE;
    Bool_t m_isFakeTau = kFALSE;

    // for TMVA reader
    TMVA::Reader *reader = new TMVA::Reader("!Color:!Silent");
    std::vector<TString> variablesName{};
    std::vector<Float_t> variablesForReader;
    std::map<TString, Float_t> varForReaderMap;
    std::vector<std::variant<Int_t, Double_t>> variablesOriginAll;

    // hists regions
    // histsForRegionsMap<Double_t> SR1tau1lSys; // calls for default constructor
    histForRegionsBase SR1tau1lSys; // calls for default constructor

    Double_t m_scaleRe_normUp_SF = 1.0;
    Double_t m_scaleRe_normDown_SF = 1.0;
    Double_t m_scaleFa_normUp_SF = 1.0;
    Double_t m_scaleFa_normDown_SF = 1.0;
    Double_t m_pdf_normUp_SF = 1.0;
    Double_t m_pdf_normDown_SF = 1.0;
    Double_t m_pdfAlphaS_normUp_SF = 1.0;
    Double_t m_pdfAlphaS_normDown_SF = 1.0;
    Double_t m_PSWeightISR_normUp_SF = 1.0;
    Double_t m_PSWeightISR_normDown_SF = 1.0;
    Double_t m_PSWeightFSR_normUp_SF = 1.0;
    Double_t m_PSWeightFSR_normDown_SF = 1.0;
};

#endif      