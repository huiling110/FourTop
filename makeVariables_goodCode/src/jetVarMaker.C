#include <map>

#include "../include/jetVarMaker.h"
#include "../include/variablesFunctions.h"

JetVarMaker::JetVarMaker(TTree *outTree, TString objName, Int_t type) : ObjVarMaker{outTree, objName, type}
{
    std::cout << "Initialzing the derived JetVarMaker........\n";

    outTree->Branch(objName + "_rationHT_4toRest", &jets_rationHT_4toRest);
    outTree->Branch(objName + "_MHT", &jets_MHT);
    outTree->Branch(objName + "_HT", &jets_HT);
    outTree->Branch(objName + "_invariantMass", &jets_invariantMass);
    outTree->Branch(objName + "_transMass", &jets_transMass);
    outTree->Branch(objName + "_minDeltaR", &jets_minDeltaR);
    outTree->Branch(objName + "_bScore", &jets_bScore);
    outTree->Branch(objName + "_bScoreMultiply", &jets_bScoreMultiply);
    outTree->Branch(objName + "_average_deltaR", &jets_average_deltaR);
    outTree->Branch(objName + "_4largestBscoreSum", &jets_4largestBscoreSum);
    outTree->Branch(objName + "_4largestBscoreMulti);", &jets_4largestBscoreMulti);
    outTree->Branch(objName + "_HTDividedByMet);", &jets_HTDividedByMet);
    outTree->Branch(objName + "_MetDividedByHT", &jets_MetDividedByHT);
    outTree->Branch(objName + "_MHTDividedByMet);", &jets_MHTDividedByMet);
    outTree->Branch(objName + "_spherilty", &jets_spherilty);
    outTree->Branch(objName + "_aplanarity", &jets_aplanarity);
    outTree->Branch(objName + "_1btag", &jets_1btag);
    outTree->Branch(objName + "_2btag", &jets_2btag);
    outTree->Branch(objName + "_3btag", &jets_3btag);
    outTree->Branch(objName + "_4btag", &jets_4btag);
    outTree->Branch(objName + "_5btag", &jets_5btag);
    outTree->Branch(objName + "_6btag", &jets_6btag);
    outTree->Branch(objName + "_7btag", &jets_7btag);
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
    outTree->Branch(objName + "_pt", &jets_10pt);
    outTree->Branch(objName + "_eta", &jets_10eta);
    outTree->Branch(objName + "_phi", &jets_10phi);
    outTree->Branch(objName + "_11pt", &jets_11pt);
    outTree->Branch(objName + "_11eta", &jets_11eta);
    outTree->Branch(objName + "_11phi", &jets_11phi);

    outTree->Branch(objName + "_leptonsMVAT_minDeltaR);", &jets_leptonsMVAT_minDeltaR);
    outTree->Branch(objName + "_tausF_minDeltaR", &jets_tausF_minDeltaR);
    outTree->Branch(objName + "_tausT_minDeltaR", &jets_tausT_minDeltaR);
    outTree->Branch(objName + "_tausT_invariantMass", &jets_tausT_invariantMass);

    std::cout << "Done initialization.............\n";
    std::cout << "\n";
};

void JetVarMaker::makeVariables(const EventForMV *e)
{
    // for derived class, I also need the function to be a exetention, what to do?
    // Answer: write the same function in derived class and then call the base part with base::function()
    //!!!need to sort the jet pt after JEC

    clearBranch();

    setupLorentzObjs(e); //!!! crucial to overide base class!!!

    ObjVarMaker::basicVariables();

    jets_MHT = MHTcalculator(objsLorentz); // 900;return the pt sum of,vetctor sum
    jets_HT = HTcalculator(objsLorentz);
    jets_invariantMass = InvariantMassCalculator(objsLorentz);

    getJetLeadingVars(e, 2, jets_2pt, jets_2eta, jets_2phi, jets_2btag);
    getJetLeadingVars(e, 3, jets_3pt, jets_3eta, jets_3phi, jets_3btag);
    getJetLeadingVars(e, 4, jets_4pt, jets_4eta, jets_4phi, jets_4btag);
    getJetLeadingVars(e, 5, jets_5pt, jets_5eta, jets_5phi, jets_5btag);
    getJetLeadingVars(e, 6, jets_6pt, jets_6eta, jets_6phi, jets_6btag);
    getJetLeadingVars(e, 7, jets_7pt, jets_7eta, jets_7phi, jets_7btag);
    // if (muons_num > 4)
    // {
    //     jets_5pt = objsLorentz[4].Pt();
    //     jets_5eta = fabs(objsLorentz[4].Eta());
    //     jets_5phi = fabs(objsLorentz[4].Phi());
    //     if(m_type==0){
    //         jets_5btag = e->jets_btags.At(4);
    //     }
    // }
    // if (muons_num > 5)
    // {
    //     jets_6pt = objsLorentz[5].Pt();
    //     jets_6eta = fabs(objsLorentz[5].Eta());
    //     jets_6phi = fabs(objsLorentz[5].Phi());
    //     if(m_type==0){
    //         jets_6btag = e->jets_btags.At(5);
    //     }
    // }
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
    UInt_t objNum = 0;
    switch (m_type)
    {
    case 0:
        objNum = e->jets_pt.GetSize();
        break;
    case 1:
        objNum = e->jetsT_pt.GetSize();
        break;
    case 2:
        objNum = e->bjetsM_pt.GetSize();
        break;
    case 3:
        objNum = e->bjetsL_pt.GetSize();
        break;
    case 4:
        objNum = e->bjetsT_pt.GetSize();
        break;
    }

    for (UInt_t i = 0; i < objNum; i++)
    {
        ROOT::Math::PtEtaPhiMVector muLorentz{-99, -99, -99, -99};
        switch (m_type)
        {
        case 0:
            muLorentz = {e->jets_pt[i], e->jets_eta[i], e->jets_phi[i], e->jets_mass[i]};
            break;
        case 1:
            muLorentz = {e->jetsT_pt[i], e->jetsT_eta[i], e->jetsT_phi[i], e->jetsT_mass[i]};
            break;
        case 2:
            muLorentz = {e->bjetsM_pt[i], e->bjetsM_eta[i], e->bjetsM_phi[i], e->bjetsM_mass[i]};
            break;
        case 3:
            muLorentz = {e->bjetsL_pt[i], e->bjetsL_eta[i], e->bjetsL_phi[i], e->bjetsL_mass[i]};
            break;
        case 4:
            muLorentz = {e->bjetsT_pt[i], e->bjetsT_eta[i], e->bjetsT_phi[i], e->bjetsT_mass[i]};
            break;
        }
        objsLorentz.push_back(muLorentz);
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
    jets_bScore = -99;
    jets_bScoreMultiply = -99;
    jets_average_deltaR = -99;
    jets_4largestBscoreSum = -99;
    jets_4largestBscoreMulti = -99;
    jets_HTDividedByMet = -99;
    jets_MetDividedByHT = -99;
    jets_MHTDividedByMet = -99;
    jets_spherilty = -99.0;
    jets_aplanarity = -99.0;
    jets_1btag = -99.0;
    jets_2btag = -99.0;
    jets_3btag = -99.0;
    jets_4btag = -99.0;
    jets_5btag = -99.0;
    jets_6btag = -99.0;
    jets_7btag = -99.0;
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
    jets_10pt = -99.0;
    jets_10eta = -99.0;
    jets_10phi = -99.0;
    jets_11pt = -99.0;
    jets_11eta = -99.0;
    jets_11phi = -99.0;

    jets_leptonsMVAT_minDeltaR = -99;
    jets_tausF_minDeltaR = -99;
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