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
    outTree->Branch(objName + "_leptonsT_transMass", &taus_leptonsT_transMass); 
    outTree->Branch(objName + "_leptonsT_invariantMass", &taus_leptonsT_invariantMass);
    outTree->Branch(objName + "_leptonsTMVA_minDeltaR", &taus_leptonsTMVA_minDeltaR);
    outTree->Branch(objName + "_leptonsTopMVA_chargeMulti", &taus_leptonsTopMVA_chargeMulti);
    outTree->Branch(objName + "_1lepton1_charge", &taus_1lepton1_charge);
    outTree->Branch(objName + "_leptons_charge", &taus_leptons_charge);
    outTree->Branch(objName + "_1charge", &taus_1charge);
    outTree->Branch(objName + "_1neutralIso", &taus_1neutralIso);

    outTree->Branch(objName + "_1lepton1_deltaR", &taus_1lepton1_deltaR);
    outTree->Branch(objName + "_1Met_transMass", &taus_1Met_transMass);
    outTree->Branch(objName + "_1lepton1Met1_stransMass", &taus_1lepton1Met1_stransMass);

    outTree->Branch(objName + "_jet_invariantMass", &taus_jet_invariantMass);
    outTree->Branch(objName + "_jet1_Met_transMass", &taus_jet1_Met_transMass);

    // outTree->Branch("leptons_2charge", &leptons_2charge);

    //Variables for tau FR 
    outTree->Branch(objName + "_genTauNum", &taus_genTauNum);
    outTree->Branch(objName + "_1genFlavour", &taus_1genFlavour);
    // outTree->Branch(objName + "_prongNum", &taus_prongNum); //!not good variable
    outTree->Branch(objName + "_1decayMode", &taus_1decayMode);
    outTree->Branch(objName + "_1prongNum", &taus_1prongNum);
    outTree->Branch(objName + "_1jetEtaAbs", &taus_1jetEtaAbs);

    if(m_type==1){
    outTree->Branch(objName + "_1jetEta", &taus_1jetEtaAbs);
        outTree->Branch(objName + "_1jetPt", &taus_1jetPt);
        outTree->Branch("tausF_1isTight", &tausF_1isTight);
        // outTree->Branch("tausF_1isTightPrompt", &tausF_1isTightPrompt);
        outTree->Branch(objName + "_1jetMass", &taus_1jetMass);
        outTree->Branch(objName + "_1jetPhi", &taus_1jetPhi);
    }



    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void TauVarMaker::makeVariables( EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector>& leptonsMVAT)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!

    ObjVarMaker::basicVariables();

    taus_MHT = MHTcalculator(objsLorentz); // 900;return the pt sum of,vetctor sum
    taus_HT = HTcalculator(objsLorentz);
    taus_invariantMass = InvariantMassCalculator(objsLorentz);
    taus_leptonsT_invariantMass = InvariantMass2SysCal(objsLorentz, leptonsMVAT);

    taus_1lepton1_deltaR = deltaR_Leading(objsLorentz, leptonsMVAT);
    taus_1Met_transMass = objsLorentz.size() > 0 ? calculateTransverseMass(objsLorentz.at(0), *e->MET_pt_, *e->MET_phi_) : -99.; // to provide information about top decaying into tau and neutrino
    taus_1lepton1Met1_stransMass = (objsLorentz.size()>0 && leptonsMVAT.size()>0 )? calculateMT2(objsLorentz.at(0), leptonsMVAT.at(0), *e->MET_pt_, *e->MET_phi_): -99.;//an event variable used to bound the masses of an unseen pair of particles which are presumed to have decayed semi-invisibly into particles which were seen. 

    // lepTOPMVAs_2invariantMass = InvariantMassCalculator(leptonsMVAT);

    //for tauF variables
    if(m_type==1){
        tausF_1isTight = e->tausF_isTight.GetSize() > 0 ? e->tausF_isTight.At(0) : kFALSE;   
        // if(!m_isData && e->tausF_genPartFlav.GetSize() > 0){
        //     tausF_1isTightPrompt = tausF_1isTight && e->tausF_genPartFlav.At(0) == 5;
        // }
    }

    switch (m_type)
    {//!!!todo: better make each object a compact object
    case 0:
        tauVariables(e->tausT_jetPt, e->tausT_jetEta, e->tausT_jetPhi, e->tausT_jetMass, e->tausT_genPartFlav, e->tausT_decayMode, e->tausT_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    case 1:
        tauVariables(e->tausF_jetPt, e->tausF_jetEta, e->tausF_jetPhi, e->tausF_jetMass, e->tausF_genPartFlav, e->tausF_decayMode, e->tausF_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    case 2:
        tauVariables(e->tausL_jetPt, e->tausL_jetEta, e->tausL_jetPhi, e->tausL_jetMass, e->tausL_genPartFlav, e->tausL_decayMode, e->tausL_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    case 3:
        tauVariables(e->tausTT_jetPt, e->tausTT_jetEta, e->tausTT_jetPhi, e->tausTT_jetMass, e->tausTT_genPartFlav, e->tausTT_decayMode, e->tausTT_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    case 4:
        tauVariables(e->tausTTT_jetPt, e->tausTTT_jetEta, e->tausTTT_jetPhi, e->tausTTT_jetMass, e->tausTTT_genPartFlav, e->tausTTT_decayMode, e->tausTTT_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    case 5:
        tauVariables(e->tausM_jetPt, e->tausM_jetEta, e->tausM_jetPhi, e->tausM_jetMass, e->tausM_genPartFlav, e->tausM_decayMode, e->tausM_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    case 6:
        tauVariables(e->tausTTTT_jetPt, e->tausTTTT_jetEta, e->tausTTTT_jetPhi, e->tausTTTT_jetMass, e->tausTTTT_genPartFlav, e->tausTTTT_decayMode, e->tausTTTT_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
        break;
    // case 9:
    //     tauVariables(e->tausF_jetPt, e->tausF_jetEta, e->tausF_jetPhi, e->tausF_jetMass, e->tausF_genPartFlav, e->tausF_decayMode, e->tausF_charge, e->elesTopMVAT_charge, e->muonsTopMVAT_charge, *e->MET_pt_, *e->MET_phi_);
    default:
        break;
    }
}

void TauVarMaker::tauVariables(const TTreeReaderArray<Double_t>& tau_jetPt, const TTreeReaderArray<Double_t>& tau_jetEta, const TTreeReaderArray<Double_t>& tau_jetPhi, const TTreeReaderArray<Double_t>& tau_jetMass, const TTreeReaderArray<UChar_t>& tau_genPartFlav, const TTreeReaderArray<Int_t>& tau_decayMode, const TTreeReaderArray<Int_t>& tau_charge, const TTreeReaderArray<Int_t>& ele_charge, const TTreeReaderArray<Int_t>& muon_charge, Double_t MET_pt, Double_t MET_phi){
    if (tau_jetPt.GetSize() > 0)
    {
        taus_1jetPt = tau_jetPt.At(0);
        taus_1jetEtaAbs = tau_jetEta.At(0);
        taus_1jetMass = tau_jetMass.At(0);
        taus_1jetPhi = tau_jetPhi.At(0);

        taus_genTauNum = calGenTauNum(tau_genPartFlav); //!!!
        taus_1genFlavour = tau_genPartFlav.At(0);
        taus_1decayMode = tau_decayMode.At(0);
        taus_1prongNum = (tau_decayMode.At(0)/5) + 1;
        taus_leptons_charge = chargeMulCalNew(tau_charge, ele_charge, muon_charge);
        // taus_1lepton1_charge = (ele_charge.GetSize()+muon_charge.GetSize() ==1 && tau_charge.GetSize()==1) ? chargeMulCalNew(tau_charge, muon_charge, muon_charge) : -99;
        taus_1lepton1_charge = chargeMulCalNew(tau_charge, ele_charge, muon_charge);


        std::vector<ROOT::Math::PtEtaPhiMVector> tauJets;
        getLorentzVec(tau_jetPt, tau_jetEta, tau_jetPhi, tau_jetMass, tauJets);
        taus_jet_invariantMass = InvariantMassCalculator(tauJets);
        taus_jet1_Met_transMass = tauJets.size() > 0 ? calculateTransverseMass(tauJets.at(0), MET_pt, MET_phi) : -99.;
        
        //!!!This branch gets overwritten with multiple instances of the class
        // leptons_2charge = ele_charge.GetSize() + muon_charge.GetSize()==2 ? chargeMulCalNew(ele_charge, muon_charge) : -99;


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
    // taus_prongNum = -99;

    taus_1jetPt = -99;
    taus_1jetEtaAbs = -99;
    taus_1jetMass = -99;
    taus_1jetPhi = -99;

    taus_1genFlavour = -99;
    taus_1decayMode = -99;
    taus_1prongNum = -99;
    taus_1lepton1_charge = -99;
    taus_leptons_charge = -99;

    taus_1lepton1_deltaR = -99;
    taus_1Met_transMass = -99;
    taus_1lepton1Met1_stransMass = -99.;
    taus_jet_invariantMass = -99;
    taus_jet1_Met_transMass = -99.;
    // leptons_2charge = -99;

    tausF_1isTight = kFALSE;
    // tausF_1isTightPrompt = kFALSE;
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
    case 6:
        getLorentzVec(e->tausTTTT_pt, e->tausTTTT_eta, e->tausTTTT_phi, e->tausTTTT_mass, objsLorentz);
        break;
    case 9: //!!!Morph tauF pt for fakeTau only
        getLorentzVec(e->tausF_pt, e->tausF_eta, e->tausF_phi, e->tausF_mass, objsLorentz);
        for (auto &obj : objsLorentz)
        {
            Double_t originalPt = obj.Pt();
            Double_t originalM = obj.M();
            // f"tausF_1pt *((-{33.24302} * TMath::Exp(-{0.30112} * tausF_1pt)) + {1.08058})"
            Double_t morphedPt = originalPt * ((-33.24302 * TMath::Exp(-0.30112 * originalPt)) + 1.08058);

            Double_t pTSF = morphedPt / originalPt;
            

            //propagate the pt change to mass 
             // Calculate pz from eta
            // // double theta = 2.0 * atan(exp(-eta));
            // double theta = 2.0 * atan(exp(-obj.Eta()));
            // double pz = morphedPt / tan(theta);
            // Double_t px = morphedPt * cos(obj.Phi());
            // Double_t py = morphedPt * sin(obj.Phi());
            // // Calculate the new energy taking the corrected pt into account
            // double energy = sqrt(morphedPt * morphedPt + pz * pz + obj.M() * obj.M());
            
            // obj = ROOT::Math::PxPyPzE4D<double>(px, py, pz, energy);
            obj = ROOT::Math::LorentzVector<ROOT::Math::PtEtaPhiM4D<double>>(morphedPt, obj.Eta(), obj.Phi(), obj.M()*pTSF);
            // obj.SetPtEtaPhiM(morphedPt, obj.Eta(), obj.Phi(), obj.M());
            // std::cout << "Morphed tauF pt from " << originalPt << " to " << morphedPt << "\n";
            std::cout << "Morphed tauF pt from " << originalPt << " to " << obj.Pt() << "\n";
            std::cout << "Morphed tauF mass from << " << originalM << " to " << obj.M() << "\n";
        }

        break;
    default:
        std::cout<<"!!!tau type not wrong!<<\n";
        break;

    }

};

Int_t TauVarMaker::getTauGenNum(){
    return taus_genTauNum;
}

TauVarMaker::~TauVarMaker(){};