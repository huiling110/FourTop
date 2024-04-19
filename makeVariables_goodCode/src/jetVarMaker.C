#include <map>

#include "../include/jetVarMaker.h"
#include "../include/variablesFunctions.h"

JetVarMaker::JetVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived JetVarMaker........\n";
    std::cout<<"m_type"<<m_type<<"\n";

    outTree->Branch(objName + "_rationHT_4toRest", &jets_rationHT_4toRest);
    outTree->Branch(objName + "_MHT", &jets_MHT);
    outTree->Branch(objName + "_HT", &jets_HT);
    outTree->Branch(objName + "_invariantMass", &jets_invariantMass);
    outTree->Branch(objName + "_transMass", &jets_transMass);
    outTree->Branch(objName + "_minDeltaR", &jets_minDeltaR);
    outTree->Branch(objName + "_centrality", &jets_centrality);
    outTree->Branch(objName + "_bScore", &jets_bScore);
    outTree->Branch(objName + "_average_deltaR", &jets_average_deltaR);
    outTree->Branch(objName + "_4largestBscoreSum", &jets_4largestBscoreSum);
    outTree->Branch(objName + "_4largestBscoreMulti", &jets_4largestBscoreMulti);
    outTree->Branch(objName + "_HTDivideMET", &jets_HTDivideMET);
    outTree->Branch(objName + "_METDivideHT", &jets_METDivideHT);
    outTree->Branch(objName + "_sphericity", &jets_sphericity);
    outTree->Branch(objName + "_aplanarity", &jets_aplanarity);
    outTree->Branch(objName + "_1btag", &jets_1btag);
    outTree->Branch(objName + "_2btag", &jets_2btag);
    outTree->Branch(objName + "_3btag", &jets_3btag);
    outTree->Branch(objName + "_4btag", &jets_4btag);
    outTree->Branch(objName + "_5btag", &jets_5btag);
    outTree->Branch(objName + "_6btag", &jets_6btag);
    outTree->Branch(objName + "_7btag", &jets_7btag);
    outTree->Branch(objName + "_8btag", &jets_8btag);
    outTree->Branch(objName + "_9btag", &jets_9btag);
    outTree->Branch(objName + "_2pt", &jets_2pt);
    outTree->Branch(objName + "_2eta", &jets_2eta);
    outTree->Branch(objName + "_2phi", &jets_2phi);
    outTree->Branch(objName + "_3pt", &jets_3pt);
    outTree->Branch(objName + "_3eta", &jets_3eta);
    outTree->Branch(objName + "_3phi", &jets_3phi);
    outTree->Branch(objName + "_4pt", &jets_4pt);
    outTree->Branch(objName + "_4eta", &jets_4eta);
    outTree->Branch(objName + "_4phi", &jets_4phi);
    outTree->Branch(objName + "_5pt", &jets_5pt);
    outTree->Branch(objName + "_5eta", &jets_5eta);
    outTree->Branch(objName + "_5phi", &jets_5phi);
    outTree->Branch(objName + "_6pt", &jets_6pt);
    outTree->Branch(objName + "_6eta", &jets_6eta);
    outTree->Branch(objName + "_6phi", &jets_6phi);
    outTree->Branch(objName + "_7pt", &jets_7pt);
    outTree->Branch(objName + "_7eta", &jets_7eta);
    outTree->Branch(objName + "_7phi", &jets_7phi);
    outTree->Branch(objName + "_8pt", &jets_8pt);
    outTree->Branch(objName + "_8eta", &jets_8eta);
    outTree->Branch(objName + "_8phi", &jets_8phi);
    outTree->Branch(objName + "_9pt", &jets_9pt);
    outTree->Branch(objName + "_9eta", &jets_9eta);
    outTree->Branch(objName + "_9phi", &jets_9phi);

    outTree->Branch(objName + "_leptonsMVAT_minDeltaR);", &jets_leptonsMVAT_minDeltaR);
    outTree->Branch(objName + "_tausT_minDeltaR", &jets_tausT_minDeltaR);
    outTree->Branch(objName + "_tausT_invariantMass", &jets_tausT_invariantMass);

    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void JetVarMaker::makeVariables( EventForMV *e, const std::vector<ROOT::Math::PtEtaPhiMVector>& taus)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()
    //!!!need to sort the jet pt after JEC
    ObjVarMaker::reportEntry("JetVarMaker::makeVariables()");

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!

    ObjVarMaker::basicVariables();

    jets_MHT = MHTcalculator(objsLorentz); // 900;return the pt sum of,vetctor sum
    jets_HT = HTcalculator(objsLorentz);
    jets_invariantMass = InvariantMassCalculator(objsLorentz);
    jets_transMass = TransMassCal(objsLorentz);
    jets_minDeltaR = MinDeltaRSingleCal(objsLorentz);
    jets_centrality = jets_HT / jets_invariantMass;
    jets_average_deltaR = AverageDeltaRCal(objsLorentz);

    jets_4largestBscoreSum = bscoreSumOf4largestCal(e->jets_btags);//!!!code needs to be reconstructed 
    jets_4largestBscoreMulti = bscoreMultiOf4largestCal(e->jets_btags);
    jets_bScore = BScoreAllJetsCal((e->jets_btags)); // sum of btags
    jets_rationHT_4toRest = rationHT_4toRestCal(objsLorentz);

    // It provides a measure of how much an event is confined to a plane, with higher values indicating events that are more isotropic (spread out in all directions) and lower values suggesting events that are planar or two-dimensional. Aplanarity is derived from the sphericity tensor, similar to the sphericity calculation.
    TVectorD eigenValues = calculateEigenvalues(objsLorentz);
    jets_sphericity = calculateSphericityFromEigenvalues(eigenValues);
    jets_aplanarity = calculateAplanarityFromEigenvalues(eigenValues);

    jets_METDivideHT = *e->MET_pt_ / jets_HT;
    jets_HTDivideMET = jets_MHT / *e->MET_pt_;
    // jets_leptonsMVAT_minDeltaR = MinDeltaRCal(jets, leptonsMVAT);
    // jets_tausT_minDeltaR = MinDeltaRCal(jets, tausT);
    jets_tausT_invariantMass = InvariantMass2SysCal(objsLorentz, taus);

    if(muons_num>1 && m_type==0){
        jets_1btag = e->jets_btags.At(0);
    }
    getJetLeadingVars(e, 1, jets_2pt, jets_2eta, jets_2phi, jets_2btag);
    getJetLeadingVars(e, 2, jets_3pt, jets_3eta, jets_3phi, jets_3btag);
    getJetLeadingVars(e, 3, jets_4pt, jets_4eta, jets_4phi, jets_4btag);
    getJetLeadingVars(e, 4, jets_5pt, jets_5eta, jets_5phi, jets_5btag);
    getJetLeadingVars(e, 5, jets_6pt, jets_6eta, jets_6phi, jets_6btag);
    getJetLeadingVars(e, 6, jets_7pt, jets_7eta, jets_7phi, jets_7btag);
    getJetLeadingVars(e, 7, jets_8pt, jets_8eta, jets_8phi, jets_8btag);
    getJetLeadingVars(e, 8, jets_9pt, jets_9eta, jets_9phi, jets_9btag);

}

void JetVarMaker::getJetLeadingVars(const EventForMV *e, const Int_t jetRank, Double_t& jets_pt, Double_t& jets_eta, Double_t& jets_phi, Double_t& jets_btag){
    if (muons_num > jetRank)
    {
        jets_pt = objsLorentz[jetRank].Pt();
        jets_eta = fabs(objsLorentz[jetRank].Eta());
        jets_phi = fabs(objsLorentz[jetRank].Phi());
        if(m_type==0){
            jets_btag = e->jets_btags.At(jetRank);
        }
    }
}

void JetVarMaker::setupLorentzObjs(const EventForMV *e)
{
    // overide base ObjValMaker
    // UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        getLorentzVec(e->jets_pt, e->jets_eta, e->jets_phi, e->jets_mass, objsLorentz);
        break;
    // case 1:
    //     getLorentzVec(e->jetsT_pt, e->jetsT_eta, e->jetsT_phi, e->jetsT_mass, objsLorentz);
    //     break;
    }

};

void JetVarMaker::clearBranch()
{
    ObjVarMaker::clearBranch();
    jets_rationHT_4toRest = -99;
    jets_MHT = -99;
    jets_HT = -99;
    jets_invariantMass = -99;
    jets_transMass = -99;
    jets_minDeltaR = -99;
    jets_centrality = -99.;
    jets_bScore = -99;
    jets_average_deltaR = -99;
    jets_4largestBscoreSum = -99;
    jets_4largestBscoreMulti = -99;
    jets_HTDivideMET = -99;
    jets_METDivideHT = -99;
    jets_sphericity = -99.;
    jets_aplanarity = -99.0;
    jets_1btag = -99.0;
    jets_2btag = -99.0;
    jets_3btag = -99.0;
    jets_4btag = -99.0;
    jets_5btag = -99.0;
    jets_6btag = -99.0;
    jets_7btag = -99.0;
    jets_8btag = -99.0;
    jets_9btag = -99.0;
    jets_2pt = -99.0;
    jets_2eta = -99.0;
    jets_2phi = -99.0;
    jets_3pt = -99.0;
    jets_3eta = -99.0;
    jets_3phi = -99.0;
    jets_4pt = -99.0;
    jets_4eta = -99.0;
    jets_4phi = -99.0;
    jets_5pt = -99.0;
    jets_5eta = -99.0;
    jets_5phi = -99.0;
    jets_6pt = -99.0;
    jets_6eta = -99.0;
    jets_6phi = -99.0;
    jets_7pt = -99.0;
    jets_7eta = -99.0;
    jets_7phi = -99.0;
    jets_8pt = -99.0;
    jets_8eta = -99.0;
    jets_8phi = -99.0;
    jets_9pt = -99.0;
    jets_9eta = -99.0;
    jets_9phi = -99.0;

    jets_leptonsMVAT_minDeltaR = -99;
    jets_tausT_minDeltaR = -99.0;
    jets_tausT_invariantMass = -99.0;
}

Double_t JetVarMaker::getHT()
{
    return jets_HT;
};

Double_t JetVarMaker::getJet_6pt()
{
    return jets_6pt;
}

Int_t JetVarMaker::getJet_num()
{
    return muons_num;
}

JetVarMaker::~JetVarMaker(){};