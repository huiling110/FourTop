#ifndef WH_FAKERATE_H
#define WH_FAKERATE_H

#include <iostream>
#include <vector>
#include <variant>
#include <memory>
#include <TGraphAsymmErrors.h>

#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH1D.h"

#include "histsForRegionsMap_class.h"
#include "functions.h"
#include "../../myLibrary/commenFunction.h"

#include "myEventClass.h"

// Define a struct to hold the graph, its eta boundaries, and tau prong
struct EtaProngGraph {
    Double_t etaMin;
    Double_t etaMax;
    int tauProng;
    TGraphAsymmErrors* graph;
    
    EtaProngGraph(Double_t min, Double_t max, int prong, TGraphAsymmErrors* g)
        : etaMin(min), etaMax(max), tauProng(prong), graph(g) {}
    
    // Check if an eta value falls within this graph's eta range
    Bool_t isInEtaRange(Double_t eta) const {
        return eta >= etaMin && eta < etaMax;
    }
};

class WH_fakeRate
{
public:
    WH_fakeRate(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE) : m_inputDir{inputDir}, m_processName{process},  m_isTest{isTest}
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
        std::cout << "m_era=" << m_era << " m_isData=" << m_isData << "  m_isTest=" << m_isTest <<"  m_isRun3="<<m_isRun3<< "\n";

        std::cout << "m_processName: " << m_processName  << "\n";
        m_outFile = new TFile(m_inputDir + "variableHists" + "_" + outVersion + "/" + m_processName + ".root", "RECREATE");

        e = new event(m_tree);
        std::cout<<"m_ifMeasure="<<m_ifMeasure<<"\n";
        std::cout << "done initializing\n\n";
    };
    ~WH_fakeRate();

    void Init();
    void LoopTree(UInt_t entry);
    void Terminate();

private:
    TString m_inputDir;
    TString m_processName;
    Bool_t m_isTest = kTRUE;
    TTree *m_tree;
    TFile *m_file;
    TString m_era = "2016";
    Bool_t m_isRun3 = kFALSE;
    Bool_t m_isData = kFALSE;
    TString m_outputFolder;
    TFile *m_outFile;
    event *e;

    // hists regions
    // histsForRegionsMap<Double_t> jets_HT_class; // calls for default constructor
    // std::vector<histsForRegionsMap>


    //FR measurement
    // const Bool_t m_ifMeasure = kFALSE;
    const Bool_t m_ifMeasure = kTRUE;
    histsForRegionsMap<Double_t> tausF_1jetPt_class;//for FR measurement
    std::vector<std::shared_ptr<histForRegionsBase>> histsForRegion_vec;//for FR application

    std::vector<EtaProngGraph> m_graphs;



};

#endif