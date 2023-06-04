#ifndef JETSEL_H
#define JETSEL_H

#include <random>

#include "eventReader_nano.h"
#include "usefulFunc.h"
#include "inputMap.h"
#include "correction.h"

class JetSel
{
public:
    JetSel(TTree *outTree, const TString era, const Int_t tauWP = 3);
    ~JetSel();
    void Select(eventForNano *e, const Bool_t isData, const std::vector<Double_t> &lepEtaVec, const std::vector<Double_t> &lepPhiVec, std::vector<Double_t> &tauEtaVec, const std::vector<Double_t> &tauPhiVec, const Bool_t deepJet, const Bool_t ifJER, const Int_t sysJEC);
    void calJER_SF(eventForNano *e, const Bool_t isData);

    void calTauSF_new(const eventForNano *e, const Bool_t isData);
    void clearBranch();
    std::vector<Double_t> &getEtaVec();
    std::vector<Double_t> &getPhiVec();

private:
    Int_t m_jetType = 0;
    TString m_era;
    std::unique_ptr<correction::CorrectionSet> cset_jerSF;
    std::vector<Double_t> JER_SF_new;
    std::vector<Double_t> jets_JESuncer;
    std::mt19937 m_random_generator;

    // output branches
    std::vector<Double_t> jets_pt;
    std::vector<Double_t> jets_eta;
    std::vector<Double_t> jets_phi;
    std::vector<Double_t> jets_mass;
};

#endif
