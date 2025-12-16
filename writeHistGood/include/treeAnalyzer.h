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
#include "SystematicManager.h"

class treeAnalyzer
{
public:
    treeAnalyzer(const TString inputDir, const TString process, TString outVersion = "v0", TString channel="1tau1l", Bool_t isTest = kTRUE, Bool_t ifSys=kTRUE) : m_inputDir{inputDir}, m_processName{process}, m_histVersion{outVersion}, m_channel{channel}, m_isTest{isTest}, m_ifSys{ifSys}
    {
        if (!m_file || m_file->IsZombie())
        {
            throw std::runtime_error("Error: could not open file: " + std::string(m_file->GetName()));
        }

        std::cout << "input file: " << m_file->GetName() << "\n";
        m_tree = (TTree *)m_file->Get("newtree");

        if (!m_tree) {
            throw std::runtime_error("Error: could not get tree 'newtree' from file");
        }

        m_era = TTTT::getEra2(m_inputDir);
        m_isData = TTTT::getIsData(m_inputDir);
        m_isRun3 = TTTT::isRun3(m_era);
        std::cout << "m_era=" << m_era <<" m_isRun3="<<m_isRun3<< " m_isData=" << m_isData << "  m_isTest=" << m_isTest << "\n";
        m_isFakeLepton = m_processName.Contains("fakeLepton");
        m_isFakeTau = m_processName.Contains("fakeTau");
        std::cout << "m_isFakeLepton=" << m_isFakeLepton << " m_isFakeTau=" << m_isFakeTau << "\n";
        std::cout<<"m_ifFakeTau="<<m_ifFakeTau<<"\n";
        std::cout<<"m_ifSys="<<m_ifSys<<"\n";

        if(m_channel=="1tau0l"){
            m_ifMCFakeTau = kFALSE;
        }
        std::cout<<"m_ifMCFakeTau="<<m_ifMCFakeTau<<"\n";

        std::cout << "m_processName: " << m_processName <<"  m_channel: "<<m_channel<< "\n";
        m_outFile = new TFile(m_inputDir + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");
        if (!m_outFile || m_outFile->IsZombie()) {
            throw std::runtime_error("Error: could not create output file");
        }

        cutFlowHist = std::make_unique<TH1D>("cutFlow", "cutFlow", 3, 0, 3);
        reader = std::make_unique<TMVA::Reader>("!Color:!Silent");
        e = std::make_unique<event>(m_tree);
        m_systematicManager = std::make_unique<SystematicManager>(m_era);
    };
    ~treeAnalyzer();

    void Init();
    void LoopTree();
    // void sysRegionsFill(Double_t bdtScore, Double_t basicWeight, Bool_t SR1tau1l, TString region);
    void sysRegionsFill(Double_t bdtScore, Double_t basicWeight, Bool_t SR1tau1l, TString region, histForRegionsBase &SR1tau1lSysF);
    void Terminate();

private:
    TString m_inputDir;
    TString m_processName;
    TString m_histVersion;
    TString m_channel;
    Bool_t m_isTest = kTRUE;
    TTree *m_tree;
    // TFile *m_file;
    // std::unique_ptr<TFile> *m_file;  // RAII for ownership
    // std::unique_ptr<TFile> ;
    std::unique_ptr<TFile> m_file = std::make_unique<TFile>(m_inputDir + m_processName + ".root", "READ"); // RAII for ownership

    TString m_era = "2016";
    Bool_t m_isData = kFALSE;
    Bool_t m_isRun3 = kFALSE;
    TString m_outputFolder;
    TFile *m_outFile;  // Owned by ROOT, will be handled by ROOT's cleanup
    std::unique_ptr<TH1D> cutFlowHist;
    std::unique_ptr<event> e;
    Bool_t m_isFakeLepton = kFALSE;
    Bool_t m_isFakeTau = kFALSE;
    Bool_t m_ifFakeTau = kTRUE;//!!!
    // Bool_t m_ifFakeTau = kFALSE;//!!!
    Bool_t m_ifMCFakeTau = kTRUE;//!!! create seperate MC fake tau hists for bg
    Bool_t m_ifSys = kTRUE;

    // for TMVA reader
    std::unique_ptr<TMVA::Reader> reader;
    std::vector<TString> variablesName{};
    std::vector<Float_t> variablesForReader;
    std::map<TString, Float_t> varForReaderMap;
    std::vector<std::variant<Int_t, Double_t>> variablesOriginAll;

    // hists regions
    histForRegionsBase SR1tau1lSys; // calls for default constructor
    histForRegionsBase SR1tau1lSys_MCFT;
    histForRegionsBase SR1tau1lSys_NotMCFT;

    // Systematic variations manager
    std::unique_ptr<SystematicManager> m_systematicManager;

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