#include "../include/bjetVarMaker.h"
#include "../include/variablesFunctions.h"

BjetVarMaker::BjetVarMaker(TTree *outTree, TString objName, Int_t type, UChar_t JESVariation, UChar_t JESType) : ObjVarMaker(outTree, objName, type), m_JESType{JESType}, m_JESVariation{JESVariation}
{
    std::cout << "Initialize BjetVarMaker class..................................\n";
    std::cout << "objName=" << objName << "  type=" << type << "\n";
    std::cout << "m_JESType=" << static_cast<int>(m_JESType) << "  m_JESVariation=" << static_cast<int>(m_JESVariation) << "\n";    

    outTree->Branch(objName + "_MHT", &bjets_MHT);
    outTree->Branch(objName + "_HT", &bjets_HT);
    outTree->Branch(objName + "_invariantMass", &bjets_invariantMass);
    outTree->Branch(objName + "_transMass", &bjets_transMass);
    outTree->Branch(objName + "_minDeltaR", &bjets_minDeltaR);

    outTree->Branch(objName + "_2leptons2_stransMass", &bjets_2leptons2_stransMass);
    outTree->Branch(objName + "_2tauT1lep1_stransMass", &bjets_2tauT1lep1_stransMass);
    outTree->Branch(objName + "_2tauF1lep1_stransMass", &bjets_2tauF1lep1_stransMass);
    outTree->Branch(objName + "_2MET_stransMass", &bjets_2MET_stransMass);
    outTree->Branch(objName + "_leptons_minDeltaR", &bjets_leptons_minDeltaR);
    outTree->Branch(objName + "_tausT_minDeltaR", &bjets_tausT_minDeltaR);
    outTree->Branch(objName + "_tausF_minDeltaR", &bjets_tausF_minDeltaR);
    outTree->Branch(objName + "_2pt", &bjets_2pt);
    outTree->Branch(objName + "_3pt", &bjets_3pt);

    std::cout << "Done initilization........\n";
    std::cout << "\n";
};

void BjetVarMaker::setupLorentzObjs(const EventForMV *e, JESVariation& jesVariation)
{//!!!class should be better initialized rather than like this
    // overide base ObjValMaker
        switch (m_type)
        {
        case 0:
            getLorentzVec(e->bjetsM_pt, e->bjetsM_eta, e->bjetsM_phi, e->bjetsM_mass,  objsLorentz);
            break;
        case 1:
            getLorentzVec(e->bjetsL_pt, e->bjetsL_eta, e->bjetsL_phi, e->bjetsL_mass,objsLorentz);
            break;
        case 2:
            getLorentzVec(e->bjetsT_pt, e->bjetsT_eta, e->bjetsT_phi, e->bjetsT_mass,  objsLorentz);
            break;
        // case 3:
        //     getLorentzVec(e->bjetsPNM_pt, e->bjetsPNM_eta, e->bjetsPNM_phi, e->bjetsPNM_mass,  objsLorentz);
        //     break;
        // case 4:
        //     getLorentzVec(e->bjetsPTM_pt, e->bjetsPTM_eta, e->bjetsPTM_phi, e->bjetsPTM_mass,  objsLorentz);
        //     break;
        // case 5: 
        //     getLorentzVec(e->bjetsPTT_pt, e->bjetsPTT_eta, e->bjetsPTT_phi, e->bjetsPTT_mass,  objsLorentz);
        //     break;
        default:
            std::cout<<"Error: BjetVarMaker::setupLorentzObjs() type not found\n";
            break;
        }
        jesVariation.applyJESVariation(objsLorentz);

}

void BjetVarMaker::makeVariables(EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector> &leptons, const std::vector<ROOT::Math::PtEtaPhiMVector> &tausT, const std::vector<ROOT::Math::PtEtaPhiMVector> &tausF, JESVariation& jesVariation, const Double_t MET_pt, const Double_t MET_phi)
//!need to use MET from jetVarMaker to make sure that JES variation propagates to MET
{
    ObjVarMaker::reportEntry("BjetVarMaker::makeVariables()");
    clearBranch();
    setupLorentzObjs(e, jesVariation); //!!! crucial to overide base class!!!
    ObjVarMaker::basicVariables();

    bjets_MHT = HTcalculator(objsLorentz);
    bjets_HT = MHTcalculator(objsLorentz);
    bjets_invariantMass = InvariantMassCalculator(objsLorentz);
    bjets_transMass = TransMassCal(objsLorentz);
    bjets_minDeltaR = MinDeltaRSingleCal(objsLorentz);

    if(objsLorentz.size()>1 ){
        ROOT::Math::PtEtaPhiMVector bjets2 = objsLorentz.at(0) + objsLorentz.at(1);
        if(leptons.size()>1){
            ROOT::Math::PtEtaPhiMVector leptons2 = leptons.at(0) + leptons.at(1);
            // bjets_2leptons2_stransMass = calculateMT2(bjets2, leptons2, *e->MET_pt_, *e->MET_phi_);
            bjets_2leptons2_stransMass = calculateMT2(bjets2, leptons2, MET_pt, MET_phi);
        }
        if(tausT.size()>0 && leptons.size()>0){
            ROOT::Math::PtEtaPhiMVector tauLep = tausT.at(0) + leptons.at(0);
            bjets_2tauT1lep1_stransMass = calculateMT2(bjets2, tauLep, MET_pt, MET_phi);
        }
        if(tausF.size()>0 && leptons.size()>0){
            ROOT::Math::PtEtaPhiMVector tauLep = tausF.at(0) + leptons.at(0);
            bjets_2tauF1lep1_stransMass = calculateMT2(bjets2, tauLep, MET_pt, MET_phi);
        }
        bjets_2MET_stransMass = calculateMT2(objsLorentz.at(0), objsLorentz.at(1), MET_pt, MET_phi);
    }

    bjets_leptons_minDeltaR = MinDeltaRCal(objsLorentz, leptons);
    bjets_tausT_minDeltaR = MinDeltaRCal(objsLorentz, tausT);
    bjets_tausF_minDeltaR = MinDeltaRCal(objsLorentz, tausF);

    bjets_2pt = objsLorentz.size()>1? objsLorentz.at(1).Pt(): -99.;
    bjets_3pt = objsLorentz.size()>2? objsLorentz.at(2).Pt(): -99.;
};

void BjetVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    bjets_MHT = -99;
    bjets_HT = -99;
    bjets_invariantMass = -99;
    bjets_transMass = -99;
    bjets_minDeltaR = -99.;

    bjets_2leptons2_stransMass = -99.;
    bjets_2tauT1lep1_stransMass = -99.;
    bjets_2tauF1lep1_stransMass = -99.;
    bjets_2MET_stransMass = -99.;
    bjets_leptons_minDeltaR = -99.;
    bjets_tausT_minDeltaR = -99.;
    bjets_tausF_minDeltaR = -99.;
    bjets_2pt = -99.;
    bjets_3pt = -99.;
};

Int_t BjetVarMaker::getJet_num()
{
    return muons_num;
};
 
BjetVarMaker::~BjetVarMaker()
{
    std::cout << "Done BjetVarMaker class......................\n";
    std::cout << "\n";
};