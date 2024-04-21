#include <vector>
#include <cmath>
#include <iostream>
#include "../include/topVarMaker.h"
// Alias for clarity
using LorentzVector = ROOT::Math::PtEtaPhiMVector;

// Function to reconstruct multiple hadronic tops
std::vector<LorentzVector> reconstructHadronicTops(const std::vector<LorentzVector>& jets, const std::vector<LorentzVector>& bjets) {
    std::vector<LorentzVector> tops;

    // Loop over all jet combinations to find W -> qq' candidates
    for (size_t i = 0; i < jets.size(); ++i) {
        for (size_t j = i + 1; j < jets.size(); ++j) {
            LorentzVector Wcandidate = jets[i] + jets[j];
            // Check if W candidate mass is close to the W boson mass (~80.4 GeV)
            if (std::abs(Wcandidate.M() - 80.4) < 30) { // Allowing some window around the W mass
                // Now loop over bjets to form the top candidates
                for (const auto& bjet : bjets) {
                    LorentzVector topCandidate = Wcandidate + bjet;
                    // Collect if this is a reasonable top candidate
                    if (std::abs(topCandidate.M() - 173.0) < 30) { // Allowing some window around the top mass
                        tops.push_back(topCandidate);
                    }
                }
            }
        }
    }

    return tops;
}

// Function to reconstruct multiple leptonic tops given multiple b-jets and leptons
std::vector<LorentzVector> reconstructLeptonicTops(const std::vector<LorentzVector>& bjets, const std::vector<LorentzVector>& leptons, const LorentzVector& MET) {
    std::vector<LorentzVector> tops;

    // Assume the neutrino pz is 0 (simplification)
    LorentzVector neutrino(MET.Px(), MET.Py(), 0, MET.Pt()); // MET is treated as pt

    // Loop over all combinations of bjets and leptons
    for (const auto& bjet : bjets) {
        for (const auto& lepton : leptons) {
            LorentzVector topCandidate = lepton + neutrino + bjet;
            // Collect if this is a reasonable top candidate
            // Here, we might want to apply some selection criteria, e.g., mass window
            if (std::abs(topCandidate.M() - 173.0) < 30) { // Allowing some window around the top mass
                tops.push_back(topCandidate);
            }
        }
    }

    return tops;
}


TopVarMaker::TopVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker(outTree, objName, type)
{
    std::cout<<"Initialize TopVarMaker class..................................\n";
    std::cout<<"objName="<<objName<<"  type="<<type<<"\n";
    outTree->Branch(objName+"_MHT", &tops_MHT);
    outTree->Branch(objName+"_HT", &tops_HT);
    outTree->Branch(objName+"_invariantMass", &tops_invariantMass);

    std::cout<<"Done initilization........\n";
}

void TopVarMaker::makeVariables(EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector> &jets, std::vector<ROOT::Math::PtEtaPhiMVector> &bjets, const std::vector<ROOT::Math::PtEtaPhiMVector> &leptons, const std::vector<ROOT::Math::PtEtaPhiMVector> &taus)
{
    ObjVarMaker::reportEntry("TopVarMaker::makeVariables()");
    
    std::vector<LorentzVector> tops_hardronic = reconstructHadronicTops(jets, bjets);
    // std::vector<LorentzVector> tops_leptonic = reconstructLeptonicTops(bjets, leptons, e->MET);
};
