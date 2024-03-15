#ifndef WRITEHIST_BTAGEFF_H
#define WRITEHIST_BTAGEFF_H

#include <iterator>

#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TH2D.h>

#include "myEventClass.h"

class WriteHist_btagEff
{
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

    Double_t bins[9] = {25., 50., 70., 100., 140., 200., 300., 600., 1000};
    Double_t binsEta[3] = {0, 1.5, 2.4};
    TH2D *m_h2D_jets_ptEta_b = new TH2D("jets_ptEta_genB", "p_{T}^{jet}(GeV):|#eta|", std::size(bins) - 1, bins, std::size(binsEta) - 1, binsEta); // maybe should have the same binnig as that of SF provided by BTV
    TH2D *m_h2D_jets_ptEta_c = new TH2D("jets_ptEta_genC", "p_{T}^{jet}(GeV):|#eta|", std::size(bins) - 1, bins, std::size(binsEta) - 1, binsEta); // maybe should have the same binnig as that of SF provided by BTV
    TH2D *m_h2D_jets_ptEta_l = new TH2D("jets_ptEta_genL", "p_{T}^{jet}(GeV):|#eta|", std::size(bins) - 1, bins, std::size(binsEta) - 1, binsEta); // maybe should have the same binnig as that of SF provided by BTV
    TH2D *m_h2D_jets_ptEta_b_nu = new TH2D("jets_ptEta_genB_nu", "jets_ptEta_genB_nu", std::size(bins) - 1, bins, std::size(binsEta) - 1, binsEta);
    TH2D *m_h2D_jets_ptEta_c_nu = new TH2D("jets_ptEta_genC_nu", "jets_ptEta_genC_nu", std::size(bins) - 1, bins, std::size(binsEta) - 1, binsEta);
    TH2D *m_h2D_jets_ptEta_l_nu = new TH2D("jets_ptEta_genL_nu", "jets_ptEta_genL_nu", std::size(bins) - 1, bins, std::size(binsEta) - 1, binsEta);

    // TH1D *de_jetsPt_eta1_b = new TH1D("b_jets_ptEta1_de", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *nu_jetsPt_eta1_b = new TH1D("b_jets_ptEta1_nu", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *de_jetsPt_eta2_b = new TH1D("b_jets_ptEta2_de", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *nu_jetsPt_eta2_b = new TH1D("b_jets_ptEta2_nu", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *de_jetsPt_eta1_c = new TH1D("c_jets_ptEta1_de", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *nu_jetsPt_eta1_c = new TH1D("c_jets_ptEta1_nu", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *de_jetsPt_eta2_c = new TH1D("c_jets_ptEta2_de", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *nu_jetsPt_eta2_c = new TH1D("c_jets_ptEta2_nu", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *de_jetsPt_eta1_l = new TH1D("l_jets_ptEta1_de", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *nu_jetsPt_eta1_l = new TH1D("l_jets_ptEta1_nu", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *de_jetsPt_eta2_l = new TH1D("l_jets_ptEta2_de", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    // TH1D *nu_jetsPt_eta2_l = new TH1D("l_jets_ptEta2_nu", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);

    //update the hist name for getting hist in a unified way
    TH1D *de_jetsPt_eta1_b = new TH1D( m_processName +"_b_Eta1_de_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *nu_jetsPt_eta1_b = new TH1D(m_processName + "_b_Eta1_nu_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *de_jetsPt_eta2_b = new TH1D(m_processName + "_b_Eta2_de_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *nu_jetsPt_eta2_b = new TH1D(m_processName + "_b_Eta2_nu_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *de_jetsPt_eta1_c = new TH1D(m_processName + "_c_Eta1_de_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *nu_jetsPt_eta1_c = new TH1D(m_processName + "_c_Eta1_nu_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *de_jetsPt_eta2_c = new TH1D(m_processName + "_c_Eta2_de_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *nu_jetsPt_eta2_c = new TH1D(m_processName + "_c_Eta2_nu_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *de_jetsPt_eta1_l = new TH1D(m_processName + "_l_Eta1_de_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *nu_jetsPt_eta1_l = new TH1D(m_processName + "_l_Eta1_nu_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *de_jetsPt_eta2_l = new TH1D(m_processName + "_l_Eta2_de_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);
    TH1D *nu_jetsPt_eta2_l = new TH1D(m_processName + "_l_Eta2_nu_jets_pt", "p_{T}^{jet}(GeV)", std::size(bins) - 1, bins);

public:
    WriteHist_btagEff(const TString inputDir, const TString process, TString outVersion = "v0", Bool_t isTest = kTRUE);
    ~WriteHist_btagEff();
    void Init();
    void LoopTree(UInt_t entry);
    void Terminate();
};

#endif