#include <fstream>
#include "../include/functions.h"

namespace WH
{


//put in myLib
Double_t getGenSum(TString inputFile)
{
    Double_t genWeightSumInitial = 1.0;
    TFile *m_file = new TFile(inputFile, "READ");
    TTree *Runs = (TTree *)m_file->Get("Runs");
    Double_t igen;
    Runs->SetBranchAddress("genEventSumw", &igen);
    genWeightSumInitial = 0.0;
    for (int iEntry = 0; Runs->LoadTree(iEntry) >= 0; ++iEntry)
    {
        Runs->GetEntry(iEntry);
        genWeightSumInitial += igen;
    }
    m_file->Close();
    std::cout << "genWeightSumInitial: " << genWeightSumInitial << "\n";
    return genWeightSumInitial;
}

void initializeHistVec(const std::vector<TString>& regionsForVariables, std::vector<std::shared_ptr<histForRegionsBase>>& histsForRegion_vec , TString m_processName,  event* e ){
    //all the variables of interest
    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;

    SP_d jets_rationHT_4toRest_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_rationHT_4toRest", "HT^{4 leaading jets}/HT^{rest of jets}", m_processName, 10, 0, 12, regionsForVariables, &(e->jets_rationHT_4toRest));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 20, 35, 1800, regionsForVariables, &(e->jets_HT));
    SP_d jets_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_MHT", "MHT(GeV)", m_processName, 20, 350, 1800, regionsForVariables, &(e->jets_MHT));
    SP_d jets_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_transMass", "m_{T}^{jets}", m_processName, 10, 350, 1800, regionsForVariables, &(e->jets_transMass));
    SP_d jets_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_minDeltaR", "min(#Delta R_{i,j})", m_processName, 10, 0, 2, regionsForVariables, &(e->jets_minDeltaR));
    SP_d jets_bScore_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 4.5, regionsForVariables, &(e->jets_bScore));
    SP_d jets_avaregeDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_average_deltaR", "average(#Delta R)^{jets}", m_processName, 10, 1.2, 3.2, regionsForVariables, &(e->jets_average_deltaR));
    SP_d jets_4largestBscoreSum_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreSum", "#sum_{i=4 highest} bscore_{i}^{jet}}", m_processName, 10, 0, 4, regionsForVariables, &(e->jets_4largestBscoreMulti));
    SP_d jets_4largestBscoreMulti_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreMulti", "#sqrt{#prod_{i=4 highest} bscore_{i}^{jet}}", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_4largestBscoreMulti));
    SP_d jets_HTDivideMET_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HTDivideMET", "HT/MET", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_HTDivideMET));
    SP_d jets_METDivideHT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_METDivideHT", "MET/HT", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_METDivideHT));
    SP_d jets_sphericity_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_sphericity", "sphericity", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_sphericity));
    SP_d jets_aplanarity_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_aplanarity", "aplanarity", m_processName, 10, 0, 0.5, regionsForVariables, &(e->jets_aplanarity));
    SP_d jets_tausT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_tausT_invariantMass", "m^{#tau and jet}", m_processName, 10, 0, 1000, regionsForVariables, &(e->jets_tausT_invariantMass));

    SP_d jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 40, 25, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 20, 25, 175, regionsForVariables, &(e->jets_6pt));
    SP_d jets_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2pt", "p_{T}^{2nd jet}(GeV)", m_processName, 40, 25, 600, regionsForVariables, &(e->jets_2pt));
    SP_d jets_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3pt", "p_{T}^{3th jet}(GeV)", m_processName, 40, 25, 140, regionsForVariables, &(e->jets_3pt));
    SP_d jets_4pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4pt", "p_{T}^{4th jet}(GeV)", m_processName, 40, 25, 300, regionsForVariables, &(e->jets_4pt));
    SP_d jets_5pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5pt", "p_{T}^{5th jet}(GeV)", m_processName, 40, 25, 160, regionsForVariables, &(e->jets_5pt));
    SP_d jets_7pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_7pt", "p_{T}^{7th jet}(GeV)", m_processName, 40, 25, 145, regionsForVariables, &(e->jets_7pt));

    SP_d jets_1btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1btag", "btag^{1st jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_1btag));
    SP_d jets_2btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2btag", "btag^{2nd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_2btag));
    SP_d jets_3btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3btag", " btag^{3rd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_3btag));
    SP_d jets_4btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4btag", "btag^{4th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_4btag));
    SP_d jets_5btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5btag", "btag^{5th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_5btag));
    SP_d jets_6btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6btag", "6th jet btag",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_6btag));

    SP_d MET_pt_class = std::make_shared<histsForRegionsMap<Double_t>>("MET_pt", "MET", m_processName, 10, 0, 500, regionsForVariables, &(e->MET_pt));

    SP_d bjetsM_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_HT", "HT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_MHT", "MHT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_invariantMass", "m^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_invariantMass));
    SP_d bjetsM_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_transMass", "m_{T}^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_transMass));
    SP_d bjetsM_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_minDeltaR", "min(#Delta R_{b jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsM_minDeltaR));
    SP_d bjetsM_2leptons2_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2leptons2_stransMass", "m_{T2}^{2 leptons and 2 b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_2leptons2_stransMass));
    SP_d bjetsM_2tau1lep1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2tau1lep1_stransMass", "m_{T2}^{#tau and lep and 2 b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_2tau1lep1_stransMass));
    SP_d bjetsM_2MET_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2MET_stransMass", "m_{T2}^{MET and 2 b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_2MET_stransMass));
    SP_d bjetsM_leptons_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_lepptons_minDeltaR", "min(#Delta R_{b jets and lep})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsM_leptons_minDeltaR));
    SP_d bjetsM_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_1pt", "p_{T}^{1st bjet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsM_1pt));
    SP_d bjetsM_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsM_2pt));//!!need to create in MV 
    SP_d bjetsM_taus_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_taus_minDeltaR", "min(#Delta R_{b jets and #tau})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsM_taus_minDeltaR));

    SP_d bjetsT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_HT", "HT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsT_HT));
    SP_d bjetsT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_MHT", "MHT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsT_HT));
    SP_d bjetsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_invariantMass", "m^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_invariantMass));
    SP_d bjetsT_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_transMass", "m_{T}^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_transMass));
    SP_d bjetsT_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_minDeltaR", "min(#Delta R_{b jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsT_minDeltaR));
    SP_d bjetsT_2leptons2_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2leptons2_stransMass", "m_{T2}^{2 leptons and 2 b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_2leptons2_stransMass));
    SP_d bjetsT_2tau1lep1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2tau1lep1_stransMass", "m_{T2}^{#tau and lep and 2 b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_2tau1lep1_stransMass));
    SP_d bjetsT_2MET_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2MET_stransMass", "m_{T2}^{MET and 2 b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_2MET_stransMass));
    SP_d bjetsT_leptons_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_lepptons_minDeltaR", "min(#Delta R_{b jets and lep})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsT_leptons_minDeltaR));
    SP_d bjetsT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_1pt", "p_{T}^{1st bjet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsT_1pt));
    SP_d bjetsT_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsT_2pt));//!!need to create in MV 
    SP_d bjetsT_taus_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_taus_minDeltaR", "min(#Delta R_{b jets and #tau})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsT_taus_minDeltaR));


    SP_d tausT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1pt", "p_{T}^{1st #tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausT_1pt));
    SP_d tausT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1eta", "#eta_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1eta));
    SP_d tausT_1phi_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1phi", "#phi_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1phi));
    SP_d tausT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_HT", "HT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_HT));
    SP_d tausT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_MHT", "MHT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_MHT));
    SP_d tausT_leptonsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_leptonsT_invariantMass", "m_{#tau and lep}(GeV)", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_leptonsT_invariantMass));
    SP_d tausT_1lepton1_deltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1lepton1_deltaR", "#Delta R_{#tau and lep}", m_processName, 10, 0, 5, regionsForVariables, &(e->tausT_1lepton1_deltaR));
    SP_d tausT_1Met_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1Met_transMass", "m_{T}^{#tau and MET}", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_1Met_transMass));
    SP_d tausT_1lepton1Met1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1lepton1Met1_stransMass", "m_{T2}^{#tau and lep and MET}", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_1lepton1Met1_stransMass));

    SP_d tausF_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1pt", "p_{T}^{1st fakeble#tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausF_1pt));
    SP_d tausF_1jetEtaAbs_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1jetEtaAbs", "#eta^{tau's mother jet}", m_processName, 10, -2.3, 2.3, regionsForVariables, &(e->tausF_1jetEtaAbs));
    SP_d tausF_1jetPt_class = std::make_shared<histsForRegionsMap<Double_t>>( "tausF_1jetPt", "p_{T}^{tau's mother jet}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausF_1jetPt));

    SP_d tausTT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausTT_1pt", "p_{T}^{1st TT#tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausTT_1pt));

    SP_d muonsTopMVAT_1t_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_1pt", "p_{T}^{#mu}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->muonsTopMVAT_1pt));
    SP_d elesTopMVAT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_1pt", "p_{T}^{e}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->elesTopMVAT_1pt));


    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 9, 4.5, 13.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsM_num));
    SP_i bjetsT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsT_num", "n^{Tb-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsT_num));
    SP_i bjetsPTM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsPTM_num", "n^{b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsPTM_num));
    SP_i bjetsPTT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsPTT_num", "n^{Tb-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsPTT_num));
    SP_i tausT_leptonsTopMVA_chargeMulti_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_leptonsTopMVA_chargeMulti", "charge^{#tau}*charge^{lep}",m_processName, 3, -1.5, 1.5, regionsForVariables,  &(e->tausT_leptonsTopMVA_chargeMulti));
    SP_i PV_npvsGood_class = std::make_shared<histsForRegionsMap<Int_t>>("PV_npvsGood", "n^{PV}", m_processName, 10, 0, 60, regionsForVariables, &(e->PV_npvsGood));

    SP_i tausT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_num", "n^{T#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausT_num));
    SP_i tausTT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_num", "n^{TT#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausTT_num));
    SP_i tausTTT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTTT_num", "n^{TTT#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausTTT_num));
    SP_i tausF_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_num", "n^{F#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausF_num));
    SP_i tausM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("tausM_num", "n^{M#tau}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->tausM_num));
    SP_i tausT_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1genFlavour", "gen flavour^{T#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausT_1genFlavour));
    SP_i tausF_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1genFlavour", "gen flavour^{F#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausF_1genFlavour));
    SP_i tausTT_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1genFlavour", "gen flavour^{TT#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausTT_1genFlavour));
    SP_i tausTTT_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTTT_1genFlavour", "gen flavour^{TTT#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausTTT_1genFlavour));
    SP_i tausM_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausM_1genFlavour", "gen flavour^{M#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausM_1genFlavour));
    SP_i tausT_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1decayMode", "decay mode^{T#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausT_1decayMode));
    SP_i tausF_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1decayMode", "decay mode^{F#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausF_1decayMode));
    SP_i tausTT_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1decayMode", "decay mode^{TT#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausTT_1decayMode));
    SP_i tausTT_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1lepton1_charge", "charge^{TT#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausTT_1lepton1_charge));
    SP_i tausTTT_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTTT_1lepton1_charge", "charge^{TTT#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausTTT_1lepton1_charge));
    SP_i tausT_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1lepton1_charge", "charge^{T#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausT_1lepton1_charge));
    SP_i tausM_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausM_1lepton1_charge", "charge^{M#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausM_1lepton1_charge));
    SP_i tausF_prongNum_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1prong", "n^{F#tau prong}", m_processName, 10, 0, 10, regionsForVariables, &(e->tausF_prongNum));
    SP_i tausT_prongNum_class = std::make_shared<histsForRegionsMap<Int_t>>("taust_1prong", "n^{T#tau prong}", m_processName, 10, 0, 10, regionsForVariables, &(e->tausT_prongNum));

    histsForRegion_vec.push_back(jets_bScore_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    histsForRegion_vec.push_back(jets_2pt_class);
    histsForRegion_vec.push_back(jets_3pt_class);
    histsForRegion_vec.push_back(jets_4pt_class);
    histsForRegion_vec.push_back(jets_5pt_class);
    histsForRegion_vec.push_back(jets_7pt_class);
    histsForRegion_vec.push_back(jets_rationHT_4toRest_class);
    histsForRegion_vec.push_back(jets_transMass_class);
    histsForRegion_vec.push_back(jets_avaregeDeltaR_class);
    histsForRegion_vec.push_back(jets_minDeltaR_class);
    histsForRegion_vec.push_back(jets_4largestBscoreSum_class);
    histsForRegion_vec.push_back(jets_4largestBscoreMulti_class);
    histsForRegion_vec.push_back(jets_HTDivideMET_class);
    histsForRegion_vec.push_back(jets_METDivideHT_class);
    histsForRegion_vec.push_back(jets_sphericity_class);
    histsForRegion_vec.push_back(jets_aplanarity_class);
    histsForRegion_vec.push_back(jets_tausT_invariantMass_class);


    histsForRegion_vec.push_back(jets_1btag_class);
    histsForRegion_vec.push_back(jets_2btag_class);
    histsForRegion_vec.push_back(jets_3btag_class);
    histsForRegion_vec.push_back(jets_4btag_class);
    histsForRegion_vec.push_back(jets_5btag_class);
    histsForRegion_vec.push_back(jets_6btag_class);

    histsForRegion_vec.push_back(MET_pt_class);

    histsForRegion_vec.push_back(bjetsM_HT_class);
    histsForRegion_vec.push_back(bjetsM_MHT_class);
    histsForRegion_vec.push_back(bjetsM_invariantMass_class);
    histsForRegion_vec.push_back(bjetsM_1pt_class);
    histsForRegion_vec.push_back(bjetsM_2pt_class);
    histsForRegion_vec.push_back(bjetsM_minDeltaR_class);
    histsForRegion_vec.push_back(bjetsM_transMass_class);
    histsForRegion_vec.push_back(bjetsM_2leptons2_stransMass_class);
    histsForRegion_vec.push_back(bjetsM_2tau1lep1_stransMass_class);
    histsForRegion_vec.push_back(bjetsM_2MET_stransMass_class);
    histsForRegion_vec.push_back(bjetsM_leptons_minDeltaR_class);
 
    histsForRegion_vec.push_back(bjetsT_HT_class);
    histsForRegion_vec.push_back(bjetsT_MHT_class);
    histsForRegion_vec.push_back(bjetsT_invariantMass_class);
    histsForRegion_vec.push_back(bjetsT_1pt_class);
    histsForRegion_vec.push_back(bjetsT_2pt_class);
    histsForRegion_vec.push_back(bjetsT_minDeltaR_class);
    histsForRegion_vec.push_back(bjetsT_transMass_class);
    histsForRegion_vec.push_back(bjetsT_2leptons2_stransMass_class);
    histsForRegion_vec.push_back(bjetsT_2tau1lep1_stransMass_class);
    histsForRegion_vec.push_back(bjetsT_2MET_stransMass_class);
    histsForRegion_vec.push_back(bjetsT_leptons_minDeltaR_class);

    histsForRegion_vec.push_back(tausT_1pt_class);
    histsForRegion_vec.push_back(tausT_1eta_class);
    histsForRegion_vec.push_back(tausT_1phi_class);
    histsForRegion_vec.push_back(tausT_HT_class);
    histsForRegion_vec.push_back(tausT_MHT_class);
    histsForRegion_vec.push_back(tausT_leptonsT_invariantMass_class);
    histsForRegion_vec.push_back(tausT_1lepton1_deltaR_class);
    histsForRegion_vec.push_back(tausT_1Met_transMass_class);
    histsForRegion_vec.push_back(tausT_1lepton1Met1_stransMass_class);
    histsForRegion_vec.push_back(tausF_1pt_class);
    histsForRegion_vec.push_back(tausF_1jetEtaAbs_class);
    histsForRegion_vec.push_back(tausF_1jetPt_class);


    histsForRegion_vec.push_back(tausTT_1pt_class);

    histsForRegion_vec.push_back(muonsTopMVAT_1t_class);
    histsForRegion_vec.push_back(elesTopMVAT_1pt_class);

    histsForRegion_vec.push_back(bjetsM_num_class);
    histsForRegion_vec.push_back(bjetsT_num_class);
    histsForRegion_vec.push_back(bjetsPTM_num_class);
    histsForRegion_vec.push_back(bjetsPTT_num_class);
    histsForRegion_vec.push_back(tausT_leptonsTopMVA_chargeMulti_class);
    histsForRegion_vec.push_back(PV_npvsGood_class);
    histsForRegion_vec.push_back(tausT_num_class);
    histsForRegion_vec.push_back(tausTT_num_class);
    histsForRegion_vec.push_back(tausTTT_num_class);
    histsForRegion_vec.push_back(tausF_num_class);
    histsForRegion_vec.push_back(tausM_num_class);
    histsForRegion_vec.push_back(tausT_1genFlavour_class);
    histsForRegion_vec.push_back(tausF_1genFlavour_class);
    histsForRegion_vec.push_back(tausTT_1genFlavour_class);
    histsForRegion_vec.push_back(tausTTT_1genFlavour_class);
    histsForRegion_vec.push_back(tausM_1genFlavour_class);
    histsForRegion_vec.push_back(tausT_1decayMode_class);
    histsForRegion_vec.push_back(tausF_1decayMode_class);
    histsForRegion_vec.push_back(tausTT_1decayMode_class);
    histsForRegion_vec.push_back(tausTT_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausTTT_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausT_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausM_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausF_prongNum_class);
    histsForRegion_vec.push_back(tausT_prongNum_class);
}

void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::map<TString, Float_t> &varForReaderMap, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    std::ifstream fin(variableListCsv);
    std::string line;
    TString ivariable;
    variablesName.clear();
    variablesOriginAll.clear();
    variablesForReader.clear();
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
            std::cout << "ivariable =" << ivariable << "\n";
            variablesName.push_back(ivariable);
            variablesForReader.push_back(0.0); // tree reader can only read float
            varForReaderMap[ivariable] = 0.0;
            if (ivariable.Contains("number") || ivariable.Contains("num") || ivariable.Contains("charge"))
            {
                std::cout << "int ivariable =" << ivariable << "\n";
                variablesOriginAll.push_back(0);
            }
            else
            {
                variablesOriginAll.push_back(0.0);
            }
        }
    }
    fin.close();
};

void histRegionVectFill(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData)
{
    // for (UInt_t i = 0; i < histForRegion_vec.size(); i++)
    // {
    //     histForRegion_vec[i]->fillHistVec(region, weight, isRegion, isData);
    // }
    for (auto &obj : histForRegion_vec)
    {
        obj->fillHistVec(region, weight, isRegion, isData);
    }
}

void histRegionsVectSetDir(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, TFile *&file)
{
    for (auto &obj : histForRegion_vec)
    {
        obj->setDir(file);
    }
}
void histRegionsVectScale(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Double_t scale)
{
    for (auto &obj : histForRegion_vec)
    {
        obj->scale(scale);
    }
}

void fillDeNu(Bool_t ifPass, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight)
{
    de->Fill(var, weight);
    if (ifPass)
    {
        nu->Fill(var, weight);
    }
}
void fillDeNu(Bool_t ifPassNu, Bool_t ifPassDe, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight)
{
    if (ifPassDe)
    {
        de->Fill(var, weight);
    }
    if (ifPassNu&&ifPassDe)
    {
        nu->Fill(var, weight);
    }
}
void fillDeNu(Bool_t ifPass, TH2D *&de, TH2D *&nu, Double_t varX, Double_t varY, Double_t weight, const Bool_t isData)
{
    if( !isData){
        de->Fill(varX, varY, weight);
        if (ifPass)
        {
            nu->Fill(varX, varY, weight);
        }
    }else{
        de->Fill(varX, varY);
        if (ifPass)
        {
            nu->Fill(varX, varY);
        }
    }
}

TString getProcessName(const TString processName, Bool_t isRun3){
    TString processNameNew = processName;
    if (isRun3){
        //check if processNameNew ends with '1'
        if (processNameNew.EndsWith("1")){
            processNameNew = processNameNew(0, processNameNew.Length()-1);
        }
    }
    return processNameNew;
};

 std::array<TString, 8> processWithExt = {
    "TTto4Q",
    "TTto2L2Nu",
    "TTtoLNu2Q",
    "QCD_PT-2400to3200",
    "QCD_PT-300to470",
    "QCD_PT-3200",
    "QCD_PT-470to600",
    "QCD_PT-600to800",
};
}