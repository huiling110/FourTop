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
    JetSel(TTree *outTree, const TString era, const TString processName, const Bool_t isRun3=kFALSE, const Bool_t isData=kFALSE,  const Int_t jetType = 0, const UChar_t JESSys = 0, UChar_t JERSys = 0);

    ~JetSel();

    void Select(eventForNano *e, const Bool_t isData, const std::vector<Double_t> &muEtaVec, const std::vector<Double_t> &muPhiVec, const std::vector<Double_t> &eEtaVec, const std::vector<Double_t> &ePhiVec, const std::vector<Double_t> &tauEtaVec, const std::vector<Double_t> &tauPhiVec, const Bool_t deepJet);

    void calJER_SF(eventForNano *e, const Bool_t isData, const Int_t sys=0);
    // void calJES_SF(const eventForNano *e, const Int_t sys);
    Double_t calJES_SF(Double_t area, Double_t eta, Double_t pt, Double_t pho);
    Double_t calJER_SF_new(Double_t pt, Double_t eta, Double_t phi, Double_t mass, Double_t rho, TTreeReaderArray<Float_t> &genEta, TTreeReaderArray<Float_t> &genPhi, TTreeReaderArray<Float_t> &genPt);

    // void calTauSF_new(const eventForNano *e, const Bool_t isData);
    void clearBranch();
    std::vector<Double_t> &getEtaVec();
    std::vector<Double_t> &getPhiVec();
    Int_t getSize();
    Double_t getHT();
    Double_t get6thPt();
    Bool_t jetVetoMap(Double_t eta, Double_t phi);

private:
    Int_t m_jetType = 0;
    TString m_era;
    const TString m_processName;
    const Bool_t m_isRun3;
    const Bool_t m_isData;
    const UChar_t m_JESSys = 0;
    const UChar_t m_JERSys = 0;
    // const Int_t m_JESSysUncerType = 0;
    std::unique_ptr<correction::CorrectionSet> cset_jerSF;
    std::unique_ptr<correction::CorrectionSet> cset_jetVeto;
    std::vector<Double_t> JER_SF_new;
    // std::vector<Double_t> JES_SF;
    // std::vector<Double_t> jets_JESuncer;
    std::mt19937 m_random_generator;

    // output branches
    std::vector<Double_t> jets_pt;
    std::vector<Double_t> jets_eta;
    std::vector<Double_t> jets_phi;
    std::vector<Double_t> jets_mass;
    std::vector<Int_t> jets_flavour;
    std::vector<Double_t> jets_btags;
    // std::vector<Double_t> jets_btagsPT;
    // std::vector<Double_t> jets_btagsPN;

    // std::vector<Double_t> jets_JESSFUp_AbsoluteMPFBias_AK4PFchs;
    // std::vector<Double_t> jets_JESSFDown_AbsoluteMPFBias_AK4PFchs;
    // std::vector<std::array<Double_t, 27>> jets_JES_uncer;//!!!why do you have to calculate JES uncertainty here? You could totoally do it in later steps when you need it

};

#endif
