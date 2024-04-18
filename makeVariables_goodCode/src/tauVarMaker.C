#include <map>

#include "../include/tauVarMaker.h"
#include "../include/variablesFunctions.h"

TauVarMaker::TauVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived TauVarMaker........\n";

    outTree->Branch(objName + "_MHT", &taus_MHT);
    outTree->Branch(objName + "_HT", &taus_HT);
    outTree->Branch(objName + "_invariantMass", &taus_invariantMass);
    outTree->Branch(objName + "_minDeltaR", &taus_minDeltaR);
    outTree->Branch(objName + "_genTauNum", &taus_genTauNum);
    outTree->Branch(objName + "_leptonsT_transMass", &taus_leptonsT_transMass); 
    outTree->Branch(objName + "_leptonsT_invariantMass", &taus_leptonsT_invariantMass);
    outTree->Branch(objName + "_leptonsTMVA_minDeltaR", &taus_leptonsTMVA_minDeltaR);
    outTree->Branch(objName + "_leptonsTopMVA_chargeMulti", &taus_leptonsTopMVA_chargeMulti);
    outTree->Branch(objName + "_prongNum", &taus_prongNum);
    outTree->Branch(objName + "_1decayMode", &taus_1decayMode);
    outTree->Branch(objName + "_1lepton1_charge", &taus_1lepton1_charge);
    outTree->Branch(objName + "_1jetPt", &taus_1jetPt);
    outTree->Branch(objName + "_1jetEtaAbs", &taus_1jetEtaAbs);
    outTree->Branch(objName + "_1charge", &taus_1charge);
    outTree->Branch(objName + "_1neutralIso", &taus_1neutralIso);
    outTree->Branch(objName + "_1genFlavour", &taus_1genFlavour);

    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void TauVarMaker::makeVariables(const EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector>& muonsLorentz, const std::vector<ROOT::Math::PtEtaPhiMVector>& elesLorentz )
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!

    ObjVarMaker::basicVariables();

    taus_MHT = MHTcalculator(objsLorentz); // 900;return the pt sum of,vetctor sum
    taus_HT = HTcalculator(objsLorentz);
    taus_invariantMass = InvariantMassCalculator(objsLorentz);
    // taus_minDeltaR = MinDeltaRSingleCal(objsLorentz);//!!!

    // std::vector<ROOT::Math::PtEtaPhiMVector> muonTopMVAT;
    // getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, muonTopMVAT);
    // std::vector<ROOT::Math::PtEtaPhiMVector> eleTopMVAT;
    // getLorentzVec(e->elesTopMVAT_pt, e->elesTopMVAT_eta, e->elesTopMVAT_phi, e->elesTopMVAT_mass, eleTopMVAT);
    std::vector<ROOT::Math::PtEtaPhiMVector> leptonsMVAT(muonsLorentz.begin(), muonsLorentz.end());
    leptonsMVAT.insert(leptonsMVAT.end(), elesLorentz.begin(), elesLorentz.end());
    taus_leptonsT_invariantMass = InvariantMass2SysCal(objsLorentz, leptonsMVAT);

    switch (m_type)
    {//!!!todo: better make each object a compact object
    case 0:
        tauVariables(e->tausT_jetPt, e->tausT_jetEta, e->tausT_genPartFlav, e->tausT_decayMode, e->tausT_charge, e->elesMVAT_charge, e->muonsT_charge);
        break;
    case 1:
        tauVariables(e->tausF_jetPt, e->tausF_jetEta, e->tausF_genPartFlav, e->tausF_decayMode, e->tausF_charge, e->elesMVAT_charge, e->muonsT_charge);
        break;
    case 2:
        tauVariables(e->tausL_jetPt, e->tausL_jetEta, e->tausL_genPartFlav, e->tausL_decayMode, e->tausL_charge, e->elesMVAT_charge, e->muonsT_charge);
        break;
    case 3:
        tauVariables(e->tausTT_jetPt, e->tausTT_jetEta, e->tausTT_genPartFlav, e->tausTT_decayMode, e->tausTT_charge, e->elesMVAT_charge, e->muonsT_charge);
        break;
    case 4:
        tauVariables(e->tausTTT_jetPt, e->tausTTT_jetEta, e->tausTTT_genPartFlav, e->tausTTT_decayMode, e->tausTTT_charge, e->elesMVAT_charge, e->muonsT_charge);
        break;
    case 5:
        tauVariables(e->tausM_jetPt, e->tausM_jetEta, e->tausM_genPartFlav, e->tausM_decayMode, e->tausM_charge, e->elesMVAT_charge, e->muonsT_charge);
        break;
    default:
        break;
    }
}

// void TauVarMaker::tauVariables(const TTreeReaderArray<Double_t>& tau_jetPt, const TTreeReaderArray<Double_t>& tau_jetEta, const TTreeReaderArray<UChar_t>& tau_genPartFlav, const TTreeReaderArray<Int_t>& tau_decayMode, const TTreeReaderArray<Int_t>& tau_charge, const TTreeReaderArray<Int_t>& ele_charge, const TTreeReaderArray<Int_t>& muon_charge){
void TauVarMaker::tauVariables(const TTreeReaderArray<Double_t>& tau_jetPt, const TTreeReaderArray<Double_t>& tau_jetEta, const TTreeReaderArray<UChar_t>& tau_genPartFlav, const TTreeReaderArray<Int_t>& tau_decayMode, const TTreeReaderArray<Int_t>& tau_charge, const TTreeReaderArray<Int_t>& ele_charge, const TTreeReaderArray<Int_t>& muon_charge){
    if (tau_jetPt.GetSize() > 0)
    {
        taus_1jetPt = tau_jetPt.At(0);
        taus_1jetEtaAbs = tau_jetEta.At(0);
        taus_genTauNum = calGenTauNum(tau_genPartFlav); //!!!
        taus_prongNum = getTauProng(tau_decayMode);
        taus_1genFlavour = tau_genPartFlav.At(0);
        taus_1decayMode = tau_decayMode.At(0);
        // taus_1lepton1_charge = chargeMulCalNew(tau_charge, e->elesMVAT_charge, e->muonsT_charge);
        taus_1lepton1_charge = chargeMulCalNew(tau_charge, ele_charge, muon_charge);
    }

} 

void TauVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    taus_MHT = -99;
    taus_HT = -99;
    taus_invariantMass = -99;
    taus_minDeltaR = -99;
    taus_genTauNum = -99;
    taus_leptonsTopMVA_chargeMulti = -99;
    taus_prongNum = -99;

    taus_1jetPt = -99;
    taus_1jetEtaAbs = -99;
    taus_1genFlavour = -99;
    taus_1decayMode = -99;
    taus_1lepton1_charge = -99;
}

void TauVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // overide base ObjValMaker
    switch (m_type)
    {
    case 0:
        getLorentzVec(e->tausT_pt, e->tausT_eta, e->tausT_phi, e->tausT_mass, objsLorentz);
        break;
    case 1:
        getLorentzVec(e->tausF_pt, e->tausF_eta, e->tausF_phi, e->tausF_mass, objsLorentz);
        break;
    case 2:
        getLorentzVec(e->tausL_pt, e->tausL_eta, e->tausL_phi, e->tausL_mass, objsLorentz);
        break;
    case 3:
        getLorentzVec(e->tausTT_pt, e->tausTT_eta, e->tausTT_phi, e->tausTT_mass, objsLorentz);
        break;
    case 4:
        getLorentzVec(e->tausTTT_pt, e->tausTTT_eta, e->tausTTT_phi, e->tausTTT_mass, objsLorentz);
        break;
    case 5:
        getLorentzVec(e->tausM_pt, e->tausM_eta, e->tausM_phi, e->tausM_mass, objsLorentz);
        break;
    default:
        std::cout<<"!!!tau type not wrong!<<\n";
        break;

    }

};

TauVarMaker::~TauVarMaker(){};