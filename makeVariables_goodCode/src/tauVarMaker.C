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
    outTree->Branch(objName + "_1jetPt", &taus_1jetPt);
    outTree->Branch(objName + "_1jetEtaAbs", &taus_1jetEtaAbs);
    outTree->Branch(objName + "_1charge", &taus_1charge);
    outTree->Branch(objName + "_1neutralIso", &taus_1neutralIso);
    outTree->Branch(objName + "_1genFlavour", &taus_1genFlavour);

    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void TauVarMaker::makeVariables(const EventForMV *e)
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

    std::vector<ROOT::Math::PtEtaPhiMVector> muonTopMVAT;
    getLorentzVec(e->muonsTopMVAT_pt, e->muonsTopMVAT_eta, e->muonsTopMVAT_phi, e->muonsTopMVAT_mass, muonTopMVAT);
    std::vector<ROOT::Math::PtEtaPhiMVector> eleTopMVAT;
    getLorentzVec(e->elesTopMVAT_pt, e->elesTopMVAT_eta, e->elesTopMVAT_phi, e->elesTopMVAT_mass, eleTopMVAT);
    std::vector<ROOT::Math::PtEtaPhiMVector> leptonsMVAT(muonTopMVAT.begin(), muonTopMVAT.end());
    leptonsMVAT.insert(leptonsMVAT.end(), eleTopMVAT.begin(), eleTopMVAT.end());
    taus_leptonsT_invariantMass = InvariantMass2SysCal(objsLorentz, leptonsMVAT);

    taus_leptonsTopMVA_chargeMulti = chargeMulCal(e->tausT_charge, e->Muon_charge_, e->muonsTopMVAT_index, e->Electron_charge_, e->elesTopMVAT_index);

    switch (m_type)
    {
    case 0:
        if (e->tausT_jetPt.GetSize() > 0)
        {
            taus_1jetPt = e->tausT_jetPt.At(0);
            taus_1jetEtaAbs = e->tausT_jetEta.At(0);
            taus_genTauNum = calGenTauNum(e->tausT_genPartFlav); //!!!
            taus_prongNum = getTauProng(e->tausT_decayMode);
            taus_1genFlavour = e->tausT_genPartFlav.At(0);
            taus_1decayMode = e->tausT_decayMode.At(0);
        }
        break;
    case 1:
        if (e->tausF_jetPt.GetSize() > 0)
        {
            taus_1jetPt = e->tausF_jetPt.At(0);
            taus_1jetEtaAbs = e->tausF_jetEta.At(0);
            taus_genTauNum = calGenTauNum(e->tausF_genPartFlav); //!!!
            taus_prongNum = getTauProng(e->tausF_decayMode);
            taus_1genFlavour = e->tausF_genPartFlav.At(0);
            taus_1decayMode = e->tausF_decayMode.At(0);
        }
        break;
    case 2:
        if (e->tausL_jetPt.GetSize() > 0)
        {
            taus_1jetPt = e->tausL_jetPt.At(0);
            taus_1jetEtaAbs = e->tausL_jetEta.At(0);
            taus_genTauNum = calGenTauNum(e->tausL_genPartFlav); //!!!
            taus_prongNum = getTauProng(e->tausL_decayMode);
            taus_1genFlavour = e->tausL_genPartFlav.At(0);
            taus_1decayMode = e->tausL_decayMode.At(0);
        }
        break;
    case 3:
        if (e->tausTT_jetPt.GetSize() > 0)
        {
            taus_1jetPt = e->tausTT_jetPt.At(0);
            taus_1jetEtaAbs = e->tausTT_jetEta.At(0);
            taus_genTauNum = calGenTauNum(e->tausTT_genPartFlav); //!!!
            taus_prongNum = getTauProng(e->tausTT_decayMode);
            taus_1genFlavour = e->tausTT_genPartFlav.At(0);
            taus_1decayMode = e->tausTT_decayMode.At(0);
        }
        break;


    default:
        break;
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
    default:
        std::cout<<"!!!tau type not wrong!<<\n";
        break;

    }

};

TauVarMaker::~TauVarMaker(){};