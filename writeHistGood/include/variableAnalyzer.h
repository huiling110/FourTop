/**
 * @file variableAnalyzer.h
 * @brief Generates input variable histograms with full systematics
 *
 * Based on treeAnalyzer pattern but outputs variable histograms instead of BDT.
 * Uses SystematicManager for consistent systematic handling.
 * No MC fake tau separation (unlike treeAnalyzer).
 *
 * OUTPUT DIRECTORY: inputVarHists_{version}/ (NOT variableHists_ to avoid BDT conflict!)
 *
 * @author Huiling Hua
 * @date 2025-01-25
 */
#ifndef VARIABLEANALYZER_H
#define VARIABLEANALYZER_H

#include <iostream>
#include <vector>
#include <memory>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"

#include "histsForRegionsMap_class.h"
#include "functions.h"
#include "../../myLibrary/commenFunction.h"
#include "myEventClass.h"
#include "SystematicManager.h"

class variableAnalyzer {
public:
    variableAnalyzer(
        const TString inputDir,
        const TString process,
        TString outVersion = "v0",
        TString channel = "1tau1l",
        Bool_t isTest = kFALSE,
        Bool_t ifSys = kTRUE
    );
    ~variableAnalyzer();

    void Init();
    void LoopTree();
    void Terminate();

private:
    void fillHistVec(const TString& region, Bool_t ifBaseline, Double_t basicWeight);

    // Input/output
    TString m_inputDir;
    TString m_processName;
    TString m_histVersion;
    TString m_channel;
    Bool_t m_isTest;
    Bool_t m_ifSys;

    // Use unique_ptr for input file (RAII)
    std::unique_ptr<TFile> m_file;
    TTree* m_tree;
    TFile* m_outFile;  // Owned by ROOT

    // Event handling
    std::unique_ptr<event> e;

    // Era/data detection
    TString m_era;
    Bool_t m_isData;
    Bool_t m_isRun3;
    Bool_t m_isFakeLepton;
    Bool_t m_isFakeTau;
    Bool_t m_ifFakeTau = kTRUE;  // Use data-driven fake tau

    // Histograms - vector of all variables
    std::vector<std::shared_ptr<histForRegionsBase>> histsForRegion_vec;

    // Systematic manager
    std::unique_ptr<SystematicManager> m_systematicManager;

    // Theory SF factors (from genWeightSum)
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
