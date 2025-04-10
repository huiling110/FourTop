#include <fstream>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include "../include/functions.h"
namespace WH
{
void initializeHistVec(const std::vector<TString>& regionsForVariables, std::vector<std::shared_ptr<histForRegionsBase>>& histsForRegion_vec , TString m_processName,  event* e ){
    //all the variables of interest
    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;

    SP_d jets_rationHT_4toRest_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_rationHT_4toRest", "HT^{4 leaading jets}/HT^{rest of jets}", m_processName, 10, 0, 12, regionsForVariables, &(e->jets_rationHT_4toRest));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 10, 200, 1800, regionsForVariables, &(e->jets_HT));
    SP_d jets_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_MHT", "MHT(GeV)", m_processName, 20, 200, 1800, regionsForVariables, &(e->jets_MHT));
    SP_d jets_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_transMass", "m_{T}^{jets}", m_processName, 10, 200, 1800, regionsForVariables, &(e->jets_transMass));
    SP_d jets_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_minDeltaR", "min(#Delta R_{i,j}(jets))", m_processName, 10, 0, 2, regionsForVariables, &(e->jets_minDeltaR));
    SP_d jets_bScore_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 4.5, regionsForVariables, &(e->jets_bScore));
    SP_d jets_avaregeDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_average_deltaR", "average(#Delta R)^{jets}", m_processName, 10, 1.2, 3.2, regionsForVariables, &(e->jets_average_deltaR));
    SP_d jets_4largestBscoreSum_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreSum", "#sum_{i=4 highest} bscore_{i}^{jet}}", m_processName, 10, 0, 4, regionsForVariables, &(e->jets_4largestBscoreMulti));
    SP_d jets_4largestBscoreMulti_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreMulti", "#sqrt{#prod_{i=4 highest} bscore_{i}^{jet}}", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_4largestBscoreMulti));
    SP_d jets_HTDivideMET_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HTDivideMET", "HT/MET", m_processName, 10, 0, 12, regionsForVariables, &(e->jets_HTDivideMET));
    SP_d jets_METDivideHT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_METDivideHT", "MET/HT", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_METDivideHT));
    SP_d jets_sphericity_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_sphericity", "sphericity", m_processName, 10, 0, 1, regionsForVariables, &(e->jets_sphericity));
    SP_d jets_aplanarity_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_aplanarity", "aplanarity", m_processName, 10, 0, 0.5, regionsForVariables, &(e->jets_aplanarity));
    SP_d jets_tausT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_tausT_invariantMass", "m^{#tau and jet}", m_processName, 10, 4, 2000, regionsForVariables, &(e->jets_tausT_invariantMass));
    SP_d jets_centrality_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_centrality", "centrality", m_processName, 10, 0, 1.3, regionsForVariables, &(e->jets_centrality));
    // SP_d jets_tausF_invariantMass_c

    SP_d jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 25, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 10, 38, 175, regionsForVariables, &(e->jets_6pt));
    SP_d jets_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2pt", "p_{T}^{2nd jet}(GeV)", m_processName, 10, 25, 600, regionsForVariables, &(e->jets_2pt));
    SP_d jets_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3pt", "p_{T}^{3th jet}(GeV)", m_processName, 10, 25, 600, regionsForVariables, &(e->jets_3pt));
    SP_d jets_4pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4pt", "p_{T}^{4th jet}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->jets_4pt));
    SP_d jets_5pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5pt", "p_{T}^{5th jet}(GeV)", m_processName, 10, 25, 150, regionsForVariables, &(e->jets_5pt));
    SP_d jets_7pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_7pt", "p_{T}^{7th jet}(GeV)", m_processName, 10, 25, 145, regionsForVariables, &(e->jets_7pt));

    SP_d jets_1btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1btag", "btag^{1st jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_1btag));
    SP_d jets_2btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2btag", "btag^{2nd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_2btag));
    SP_d jets_3btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3btag", " btag^{3rd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_3btag));
    SP_d jets_4btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4btag", "btag^{4th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_4btag));
    SP_d jets_5btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5btag", "btag^{5th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_5btag));
    SP_d jets_6btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6btag", "6th jet btag",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_6btag));
    SP_d jets_7btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_7btag", "7th jet btag",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_7btag));
    SP_d jets_8btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_8btag", "8th jet btag",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_8btag));
    SP_d MET_pt_class = std::make_shared<histsForRegionsMap<Double_t>>("MET_pt", "MET", m_processName, 10, 0, 350, regionsForVariables, &(e->MET_pt));

    SP_d bjetsM_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_HT", "HT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_MHT", "MHT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_invariantMass", "m^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_invariantMass));
    SP_d bjetsM_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_transMass", "m_{T}^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_transMass));
    SP_d bjetsM_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_minDeltaR", "min(#Delta R_{b jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsM_minDeltaR));
    SP_d bjetsM_2leptons2_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2leptons2_stransMass", "m_{T2}^{2 leptons and 2 b jets}", m_processName, 10, 0, 400, regionsForVariables, &(e->bjetsM_2leptons2_stransMass));
    SP_d bjetsM_2tau1lep1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2tauT1lep1_stransMass", "m_{T2}^{#tau and lep and 2 b jets}", m_processName, 10, 0, 400, regionsForVariables, &(e->bjetsM_2tauT1lep1_stransMass));
    SP_d bjetsM_2MET_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2MET_stransMass", "m_{T2}^{MET and 2 b jets}", m_processName, 10, 0, 400, regionsForVariables, &(e->bjetsM_2MET_stransMass));
    SP_d bjetsM_leptons_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_leptons_minDeltaR", "min(#Delta R_{b jets and lep})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsM_leptons_minDeltaR));
    SP_d bjetsM_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_1pt", "p_{T}^{1st bjet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsM_1pt));
    SP_d bjetsM_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsM_2pt)); 
    SP_d bjetsM_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_3pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsM_3pt)); 
    SP_d bjetsM_tausF_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_tausF_minDeltaR", "min(#Delta R_{b jets and F#tau})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsM_tausF_minDeltaR));
    SP_d bjetsM_tausT_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_tausT_minDeltaR", "min(#Delta R_{b jets and T#tau})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsM_tausT_minDeltaR));

    SP_d bjetsT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_HT", "HT^{tight b-jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsT_HT));
    SP_d bjetsT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_MHT", "MHT^{tight b-jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsT_HT));
    SP_d bjetsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_invariantMass", "m^{tight b-jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_invariantMass));
    SP_d bjetsT_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_transMass", "m_{T}^{tight b-jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_transMass));
    SP_d bjetsT_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_minDeltaR", "min(#Delta R_{tight b-jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsT_minDeltaR));
    SP_d bjetsT_2leptons2_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2leptons2_stransMass", "m_{T2}^{2 leptons and 2 tight b-jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsT_2leptons2_stransMass));
    SP_d bjetsT_2tau1lep1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2tau1lep1_stransMass", "m_{T2}^{#tau and lep and 2 T b-jets}", m_processName, 10, 0, 400, regionsForVariables, &(e->bjetsM_2tauT1lep1_stransMass));//!
    SP_d bjetsT_2MET_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2MET_stransMass", "m_{T2}^{MET and 2 T b-jets}", m_processName, 10, 0, 400, regionsForVariables, &(e->bjetsT_2MET_stransMass));
    SP_d bjetsT_leptons_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_leptons_minDeltaR", "min(#Delta R_{T b-jets and lep})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsT_leptons_minDeltaR));
    SP_d bjetsT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_1pt", "p_{T}^{1st T b-jet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsT_1pt));
    SP_d bjetsT_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_2pt", "p_{T}^{2nd T b-jet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsT_2pt));
    SP_d bjetsT_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_3pt", "p_{T}^{3rd T b-jet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsT_3pt));//!!need to create in MV 
    SP_d bjetsT_tausT_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsT_tausT_minDeltaR", "min(#Delta R_{T b-jets and #tau})", m_processName, 10, 0, 5, regionsForVariables, &(e->bjetsT_tausT_minDeltaR));


    SP_d tausT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1pt", "p_{T}^{1st #tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausT_1pt));
    SP_d tausT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1eta", "#eta_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1eta));
    SP_d tausT_1phi_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1phi", "#phi_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1phi));
    SP_d tausT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_HT", "HT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_HT));
    SP_d tausT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_MHT", "MHT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_MHT));
    SP_d tausT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_invariantMass", "m^{#tau}", m_processName, 10, 0, 5, regionsForVariables, &(e->tausT_invariantMass));
    SP_d tausT_leptonsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_leptonsT_invariantMass", "m_{#tau and lep}(GeV)", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_leptonsT_invariantMass));
    SP_d tausT_1lepton1_deltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1lepton1_deltaR", "#Delta R_{#tau and lep}", m_processName, 10, 0, 5, regionsForVariables, &(e->tausT_1lepton1_deltaR));
    SP_d tausT_1Met_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1Met_transMass", "m_{T}^{#tau and MET}", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_1Met_transMass));
    SP_d tausT_1lepton1Met1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1lepton1Met1_stransMass", "m_{T2}^{#tau and lep and MET}", m_processName, 10, 0, 250, regionsForVariables, &(e->tausT_1lepton1Met1_stransMass));

    // SP_d tausF_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1pt", "p_{T}^{1st fakeble#tau}", m_processName, 40, 20, 100, regionsForVariables, &(e->tausF_1pt)); //!Finer binning for fitting 
    SP_d tausF_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1pt", "p_{T}^{1st fakeble#tau}", m_processName, 10, 20, 150, regionsForVariables, &(e->tausF_1pt)); //!This is tauT in in FT region.
    SP_d tausF_1jetEta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1jetEta", "#eta^{tau's mother jet}", m_processName, 10, -2.4, 2.4, regionsForVariables, &(e->tausF_1jetEta));
    SP_d tausF_1jetPt_class = std::make_shared<histsForRegionsMap<Double_t>>( "tausF_1jetPt", "p_{T}^{#tau's mother jet}", m_processName, 20, 0, 200, regionsForVariables, &(e->tausF_1jetPt));
    SP_d tausF_1Met_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1Met_transMass", "m_{T}^{#tau and MET}", m_processName, 10, 0, 250, regionsForVariables, &(e->tausF_1Met_transMass));
    SP_d tausF_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_invariantMass", "m^{#tau}", m_processName, 10, 0, 4, regionsForVariables, &(e->tausF_invariantMass));
    SP_d tausF_jet1_Met_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_jet1_Met_transMass", "m_{T}^{#tau's mother jet and MET}", m_processName, 10, 0, 250, regionsForVariables, &(e->tausF_jet1_Met_transMass));
    SP_d tausF_jet_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_jet_invariantMass", "m^{#tau's mother jet}", m_processName, 10, 0, 50, regionsForVariables, &(e->tausF_jet_invariantMass));
    SP_d tausTT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausTT_1pt", "p_{T}^{1st TT#tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausTT_1pt));
    SP_d tausF_1lepton1Met1_stransMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1lepton1Met1_stransMass", "m_{T2}^{#tau F and lep and MET}", m_processName, 10, 0, 250, regionsForVariables, &(e->tausF_1lepton1Met1_stransMass));
    SP_d tausF_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1eta", "#eta_{F#tau}", m_processName, 10, 0, 2.5, regionsForVariables, &(e->tausF_1eta));
    SP_d tausT_1jetEtaAbs_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1jetEtaAbs", "|#eta^{T#tau's mother jet}|", m_processName, 10, 0, 2.5, regionsForVariables, &(e->tausT_1jetEtaAbs));
// tausT_leptonsT_invariantMass

    SP_d muonsTopMVAT_1t_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_1pt", "p_{T}^{#mu}(GeV)", m_processName, 10, 0, 200, regionsForVariables, &(e->muonsTopMVAT_1pt));
    SP_d muonsTopMVAT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_1eta", "#eta^{#mu}", m_processName, 10, -2.5, 2.5, regionsForVariables, &(e->muonsTopMVAT_1eta));
    SP_d elesTopMVAT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_1pt", "p_{T}^{e}(GeV)", m_processName, 10, 0, 200, regionsForVariables, &(e->elesTopMVAT_1pt));
    SP_d elesTopMVAT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_1eta", "#eta^{e}", m_processName, 10, -2.5, 2.5, regionsForVariables, &(e->elesTopMVAT_1eta));
    SP_d elesTopMVAT_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_2pt", "p_{T}^{2nd e}(GeV)", m_processName, 10, 0, 160, regionsForVariables, &(e->elesTopMVAT_2pt));
    SP_d muonsTopMVAT_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_2pt", "p_{T}^{2nd #mu}(GeV)", m_processName, 10, 0, 160, regionsForVariables, &(e->muonsTopMVAT_2pt));
    SP_d elesTopMVAT_2eta_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_2eta", "#eta^{2nd e}", m_processName, 10, -2.5, 2.5, regionsForVariables, &(e->elesTopMVAT_2eta));
    SP_d muonsTopMVAT_2eta_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_2eta", "#eta^{2nd #mu}", m_processName, 10, -2.5, 2.5, regionsForVariables, &(e->muonsTopMVAT_2eta));
    SP_d lepTopMVAT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("lepTopMVAT_1pt", "p_{T}^{1st l}(GeV)", m_processName, 10, 0, 200, regionsForVariables, &(e->lepTopMVAT_1pt));
    SP_d lepTopMVAT_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("lepTopMVAT_2pt", "p_{T}^{2nd l}(GeV)", m_processName, 10, 0, 160, regionsForVariables, &(e->lepTopMVAT_2pt));
    SP_i leptons_2charge_class = std::make_shared<histsForRegionsMap<Int_t>>("leptons_2charge", "charge^{lep}*charge^{lep}", m_processName, 3, -1.5, 1.5, regionsForVariables, &(e->leptons_2charge));//!prob
    SP_d lepTopMVAT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("lepTopMVAT_1eta", "#eta^{1st l}", m_processName, 10, -2.5, 2.5, regionsForVariables, &(e->lepTopMVAT_1eta));
    SP_d lepTopMVAT_2eta_class = std::make_shared<histsForRegionsMap<Double_t>>("lepTopMVAT_2eta", "#eta^{2nd l}", m_processName, 10, -2.5, 2.5, regionsForVariables, &(e->lepTopMVAT_2eta));
    SP_d lepTopMVAT_1phi_class = std::make_shared<histsForRegionsMap<Double_t>>("lepTopMVAT_1phi", "#phi^{1st l}", m_processName, 10, -3.2, 3.2, regionsForVariables, &(e->lepTopMVAT_1phi));
    SP_d lepTopMVAT_2invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("lepTopMVAT_2invariantMass", "m^{2nd l}", m_processName, 10, 0, 200, regionsForVariables, &(e->lepTopMVAT_2invariantMass));
    SP_i lepTopMVAF_num_class = std::make_shared<histsForRegionsMap<Int_t>>("lepTopMVAF_num", "n^{F lep}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->lepTopMVAF_num));
    SP_i lepTopMVAT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("lepTopMVAT_num", "n^{T lep}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->lepTopMVAT_num));
    SP_i elesTopMVAT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("elesTopMVAT_num", "n^{T e}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->elesTopMVAT_num));
    SP_i muonsTopMVAT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("muonsTopMVAT_num", "n^{T #mu}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->muonsTopMVAT_num));
    SP_i elesTopMVAF_num_class = std::make_shared<histsForRegionsMap<Int_t>>("elesTopMVAF_num", "n^{F e}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->elesTopMVAF_num));
    SP_i muonsTopMVAF_num_class = std::make_shared<histsForRegionsMap<Int_t>>("muonsTopMVAF_num", "n^{F #mu}", m_processName, 5, -0.5, 4.5, regionsForVariables, &(e->muonsTopMVAF_num));


    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 12, 1.5, 13.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsM_num));
    SP_i bjetsT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsT_num", "n^{T b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsT_num));
    SP_i bjetsPTM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsPTM_num", "n^{b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsPTM_num));
    SP_i bjetsPTT_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsPTT_num", "n^{T b-jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsPTT_num));
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
    SP_i tausM_1genFlavour_class = std::make_shared<histsForRegionsMap<Int_t>>("tausM_1genFlavour", "gen flavour^{M#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausM_1genFlavour));
    SP_i tausT_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1decayMode", "decay mode^{T#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausT_1decayMode));
    SP_i tausF_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1decayMode", "decay mode^{#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausF_1decayMode));
    SP_i tausTT_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1decayMode", "decay mode^{TT#tau}", m_processName, 12, -0.5, 11.5, regionsForVariables, &(e->tausTT_1decayMode));
    SP_i tausTT_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTT_1lepton1_charge", "charge^{TT#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausTT_1lepton1_charge));
    SP_i tausTTT_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausTTT_1lepton1_charge", "charge^{TTT#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausTTT_1lepton1_charge));
    SP_i tausT_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_1lepton1_charge", "charge^{T#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausT_1lepton1_charge));
    SP_i tausM_1lepton1_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausM_1lepton1_charge", "charge^{M#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausM_1lepton1_charge));
    SP_i tausT_leptons_charge_class = std::make_shared<histsForRegionsMap<Int_t>>( "tausT_leptons_charge", "charge^{T#tau}*charge^{lep}", m_processName, 3, -1.5, 1.5, regionsForVariables, &(e->tausT_leptons_charge));
    SP_i tausF_1prongNum_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1prongNum", "n^{#tau prong}", m_processName, 10, 0, 10, regionsForVariables, &(e->tausF_1prongNum));
    SP_i tausF_leptons_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_leptons_charge", "charge^{F#tau}*charge^{lep}", m_processName, 2, -1.5, 1.5, regionsForVariables, &(e->tausF_leptons_charge));


    histsForRegion_vec.push_back(jets_bScore_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_MHT_class);
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
    histsForRegion_vec.push_back(jets_centrality_class);


    histsForRegion_vec.push_back(jets_1btag_class);
    histsForRegion_vec.push_back(jets_2btag_class);
    histsForRegion_vec.push_back(jets_3btag_class);
    histsForRegion_vec.push_back(jets_4btag_class);
    histsForRegion_vec.push_back(jets_5btag_class);
    histsForRegion_vec.push_back(jets_6btag_class);
    histsForRegion_vec.push_back(jets_7btag_class);
    histsForRegion_vec.push_back(jets_8btag_class);

    histsForRegion_vec.push_back(MET_pt_class);

    histsForRegion_vec.push_back(bjetsM_HT_class);
    histsForRegion_vec.push_back(bjetsM_MHT_class);
    histsForRegion_vec.push_back(bjetsM_invariantMass_class);
    histsForRegion_vec.push_back(bjetsM_1pt_class);
    histsForRegion_vec.push_back(bjetsM_2pt_class);
    histsForRegion_vec.push_back(bjetsM_3pt_class);
    histsForRegion_vec.push_back(bjetsM_minDeltaR_class);
    histsForRegion_vec.push_back(bjetsM_transMass_class);
    histsForRegion_vec.push_back(bjetsM_2leptons2_stransMass_class);
    histsForRegion_vec.push_back(bjetsM_2tau1lep1_stransMass_class);
    histsForRegion_vec.push_back(bjetsM_2MET_stransMass_class);
    histsForRegion_vec.push_back(bjetsM_leptons_minDeltaR_class);
    histsForRegion_vec.push_back(bjetsM_tausF_minDeltaR_class);
    histsForRegion_vec.push_back(bjetsM_tausT_minDeltaR_class);
 
    histsForRegion_vec.push_back(bjetsT_HT_class);
    histsForRegion_vec.push_back(bjetsT_MHT_class);
    histsForRegion_vec.push_back(bjetsT_invariantMass_class);
    histsForRegion_vec.push_back(bjetsT_1pt_class);
    histsForRegion_vec.push_back(bjetsT_2pt_class);
    histsForRegion_vec.push_back(bjetsT_3pt_class);
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
    histsForRegion_vec.push_back(tausT_invariantMass_class);
    histsForRegion_vec.push_back(tausT_leptonsT_invariantMass_class);
    histsForRegion_vec.push_back(tausT_1lepton1_deltaR_class);
    histsForRegion_vec.push_back(tausT_1Met_transMass_class);
    histsForRegion_vec.push_back(tausT_1lepton1Met1_stransMass_class);
    histsForRegion_vec.push_back(tausF_1pt_class);
    histsForRegion_vec.push_back(tausF_1jetEta_class);
    histsForRegion_vec.push_back(tausF_1jetPt_class);
    histsForRegion_vec.push_back(tausF_1Met_transMass_class);
    histsForRegion_vec.push_back(tausF_invariantMass_class);
    histsForRegion_vec.push_back(tausF_jet1_Met_transMass_class);
    histsForRegion_vec.push_back(tausF_jet_invariantMass_class);


    histsForRegion_vec.push_back(tausTT_1pt_class);
    histsForRegion_vec.push_back(tausF_1lepton1Met1_stransMass_class);
    histsForRegion_vec.push_back(tausF_1eta_class);
    histsForRegion_vec.push_back(tausT_1jetEtaAbs_class);

    histsForRegion_vec.push_back(muonsTopMVAT_1t_class);
    histsForRegion_vec.push_back(muonsTopMVAT_1eta_class);
    histsForRegion_vec.push_back(elesTopMVAT_1pt_class);
    histsForRegion_vec.push_back(elesTopMVAT_1eta_class);
    histsForRegion_vec.push_back(elesTopMVAT_2pt_class);
    histsForRegion_vec.push_back(muonsTopMVAT_2pt_class);
    histsForRegion_vec.push_back(elesTopMVAT_2eta_class);
    histsForRegion_vec.push_back(muonsTopMVAT_2eta_class);
    histsForRegion_vec.push_back(lepTopMVAT_1pt_class);
    histsForRegion_vec.push_back(lepTopMVAT_2pt_class);
    histsForRegion_vec.push_back(leptons_2charge_class);
    histsForRegion_vec.push_back(lepTopMVAT_1eta_class);
    histsForRegion_vec.push_back(lepTopMVAT_2eta_class);
    histsForRegion_vec.push_back(lepTopMVAT_1phi_class);
    histsForRegion_vec.push_back(lepTopMVAT_2invariantMass_class);
    histsForRegion_vec.push_back(lepTopMVAF_num_class);
    histsForRegion_vec.push_back(lepTopMVAT_num_class);
    histsForRegion_vec.push_back(elesTopMVAT_num_class);
    histsForRegion_vec.push_back(muonsTopMVAT_num_class);
    histsForRegion_vec.push_back(elesTopMVAF_num_class);
    histsForRegion_vec.push_back(muonsTopMVAF_num_class);

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
    histsForRegion_vec.push_back(tausM_1genFlavour_class);
    histsForRegion_vec.push_back(tausT_1decayMode_class);
    histsForRegion_vec.push_back(tausF_1decayMode_class);
    histsForRegion_vec.push_back(tausTT_1decayMode_class);
    histsForRegion_vec.push_back(tausTT_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausTTT_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausT_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausM_1lepton1_charge_class);
    histsForRegion_vec.push_back(tausT_leptons_charge_class);
    histsForRegion_vec.push_back(tausF_1prongNum_class);
    histsForRegion_vec.push_back(tausF_leptons_charge_class);
}

void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::map<TString, Float_t> &varForReaderMap, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    // std::ifstream fin(variableListCsv);
    std::ifstream fin(variableListCsv.Data());
    std::string line;
    TString ivariable;
    variablesName.clear();
    variablesOriginAll.clear();
    variablesForReader.clear();
    varForReaderMap.clear();
    while (getline(fin, line))
    {
        line.erase(line.find_last_not_of(" \n\r\t")+1);
        if (line.empty()) {
            continue; // Skip empty lines
        }

        ivariable = line;
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
    fin.close();
};

// void histRegionVectFill(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData)
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

// void getChannelSys(std::vector<TString>& sysRegions, TString region, TString era, Bool_t isFaketau, Bool_t isFakeLep){
void getChannelSys(std::vector<TString>& sysRegions, TString region, TString era, Bool_t isFaketau, Bool_t isFakeLep, TString process){
//https://gitlab.cern.ch/cms-analysis/general/systematics/-/blob/master/systematics_master.yml
    sysRegions.push_back(region);
    // sysRegions.push_back("isMCFTau_" + region);
    // sysRegions.push_back("isNotMCFTau_" + region);

    if(!(isFaketau || isFakeLep)){
        
    sysRegions.push_back(region + "_CMS_pileupUp");// 100% correlated
    sysRegions.push_back(region + "_CMS_pileupDown");
    sysRegions.push_back(region + "_CMS_l1_ecal_prefiring_" + era + "Up");
    sysRegions.push_back(region + "_CMS_l1_ecal_prefiring_" + era + "Down");

    sysRegions.push_back(region + "_CMS_eff_t_vsJet_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsMu_" + era + "Up"); // uncorrelated between eras, statistical uncertainty dominates
    sysRegions.push_back(region + "_CMS_eff_t_vsMu_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsEle_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsEle_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm0_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm0_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm1_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm1_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm10_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm10_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm11_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat1_dm11_" + era + "Down");

    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm0_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm0_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm1_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm1_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm10_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm10_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm11_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_stat2_dm11_" + era + "Down");

    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_allerasUp");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_allerasDown");

    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_" +era + "Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm0_" + era +"Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm0_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm1_" + era +"Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm1_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm10_" + era +"Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm10_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm11_" + era +"Up");
    sysRegions.push_back(region + "_CMS_eff_t_vsJet_syst_dm11_" + era + "Down"); 

    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_e_systUp");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_e_systDown");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_m_systUp");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_m_systDown");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_m_stat_" + era + "Up");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_m_stat_" + era + "Down");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_e_stat_" + era + "Up");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_e_stat_" + era + "Down");
    sysRegions.push_back(region + "_CMS_eff_e_reco_" + era + "Up");
    sysRegions.push_back(region + "_CMS_eff_e_reco_" + era + "Down");

    sysRegions.push_back(region + "_CMS_btag_shape_jesUp");
    sysRegions.push_back(region + "_CMS_btag_shape_jesDown");
    sysRegions.push_back(region + "_CMS_btag_shape_hfUp");
    sysRegions.push_back(region + "_CMS_btag_shape_hfDown");
    sysRegions.push_back(region + "_CMS_btag_shape_lfUp");
    sysRegions.push_back(region + "_CMS_btag_shape_lfDown");
    sysRegions.push_back(region + "_CMS_btag_shape_hfstats1_" + era + "Up");
    sysRegions.push_back(region + "_CMS_btag_shape_hfstats1_" + era + "Down");
    sysRegions.push_back(region + "_CMS_btag_shape_hfstats2_" + era + "Up");
    sysRegions.push_back(region + "_CMS_btag_shape_hfstats2_" + era + "Down");
    sysRegions.push_back(region + "_CMS_btag_shape_lfstats1_" + era + "Up");
    sysRegions.push_back(region + "_CMS_btag_shape_lfstats1_" + era + "Down");
    sysRegions.push_back(region + "_CMS_btag_shape_lfstats2_" + era + "Up");
    sysRegions.push_back(region + "_CMS_btag_shape_lfstats2_" + era + "Down");
    sysRegions.push_back(region + "_CMS_btag_shape_cferr1Up");
    sysRegions.push_back(region + "_CMS_btag_shape_cferr1Down");
    sysRegions.push_back(region + "_CMS_btag_shape_cferr2Up");
    sysRegions.push_back(region + "_CMS_btag_shape_cferr2Down");


    sysRegions.push_back(region + "_CMS_tttt(tau)_eff_hlt_stats_" + era + "Up");
    sysRegions.push_back(region + "_CMS_tttt(tau)_eff_hlt_stats_" + era + "Down");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_hltLep_" + era + "Up");
    sysRegions.push_back(region + "_CMS_tttt(SS)_eff_hltLep_" + era + "Down");

    // update to naming convention 
    sysRegions.push_back(region + "_CMS_btag_fixedWP_comb_bc_correlatedUp");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_comb_bc_correlatedDown");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_comb_bc_uncorrelated_"+era + "Up");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_comb_bc_uncorrelated_"+era + "Down");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_incl_light_correlatedUp");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_incl_light_correlatedDown");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_incl_light_uncorrelated_"+era + "Up");
    sysRegions.push_back(region + "_CMS_btag_fixedWP_incl_light_uncorrelated_"+era + "Down");


    sysRegions.push_back(region + "_pdfUp");
    sysRegions.push_back(region + "_pdfDown");
    sysRegions.push_back(region + "_pdf_alphasUp");
    sysRegions.push_back(region + "_pdf_alphasDown");
    sysRegions.push_back(region + "_QCDscale_ren_"+process+"Up"); //! un-correlated between processes
    sysRegions.push_back(region + "_QCDscale_ren_"+process+"Down");
    sysRegions.push_back(region + "_QCDscale_fac_"+process+"Up");
    sysRegions.push_back(region + "_QCDscale_fac_"+process+"Down");

    sysRegions.push_back(region + "_ps_isr_"+process+"Up");
    sysRegions.push_back(region + "_ps_isr_"+process+"Down");
    sysRegions.push_back(region + "_ps_fsrUp");
    sysRegions.push_back(region + "_ps_fsrDown");

    }else if(isFaketau){
        sysRegions.push_back(region + "_CMS_fake_t_" + era + "Up");
        sysRegions.push_back(region + "_CMS_fake_t_" + era + "Down");
    }
}

Double_t calQCDScaleNor(const TString inputFile, UInt_t index){
    //Re_up: 7; Re_down: 1; Fa_up: 5; Fa_down: 3
    //!LHEScaleSumw: sum of genEventWeight * LHESacleWeight[i]/ genEventSumw 
    //?does the sum of genEventWeight of just one sample or all samples?
    //I think it's per sample
    TFile *file = TFile::Open(inputFile);
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    TTreeReader reader("Runs", file); // Replace "tree_name" with the actual name of your TTree
    TTreeReaderArray<double> LHEScaleSumw(reader, "LHEScaleSumw");
    TTreeReaderValue<Double_t> genEventSumw(reader, "genEventSumw");

    Double_t sumGen = 0.;
    Double_t sumGenScale = 0;
    while (reader.Next())
    {
        // for (size_t j = 0; j < LHEScaleSumw.GetSize(); ++j) {
        //     std::cout << LHEScaleSumw[index] << " ";
        // }
        sumGen += *genEventSumw;
        sumGenScale += LHEScaleSumw[index]*(*genEventSumw);
    }
    // std::cout<<"sumGen = "<<sumGen<<" sumGenScale = "<<sumGenScale<<"\n";
    file->Close();
    return sumGen/sumGenScale;
}

Double_t calPDFScaleNor(const TString inputFile, UInt_t index){
    TFile *file = TFile::Open(inputFile);
    if (!file || file->IsZombie()) {
        std::cerr << "Error opening file!" << std::endl;
        return 1;
    }

    TTreeReader reader("Runs", file); // Replace "tree_name" with the actual name of your TTree
    TTreeReaderArray<Double_t> LHEPdfSumw(reader, "LHEPdfSumw");//Sum of genEventWeight * LHEPdfWeight[i], divided by genEventSumw
    TTreeReaderValue<Double_t> genEventSumw(reader, "genEventSumw");
    TTreeReaderValue<Double_t> LHEPdfSumwUp(reader, "LHEPdfSumwUp");//Sum of genEventWeight * LHEPdfWeightUp
    TTreeReaderValue<Double_t> LHEPdfSumwDown(reader, "LHEPdfSumwDown");//Sum of genEventWeight * LHEPdfWeightDown
    TTreeReaderValue<Double_t> PSWeightISRSumwUp(reader, "m_PSWeightISRSumwUp");//Sum of genEventWeight * PSWeightUp
    TTreeReaderValue<Double_t> PSWeightISRSumwDown(reader, "m_PSWeightISRSumwDown");//Sum of genEventWeight * PSWeightDown
    TTreeReaderValue<Double_t> PSWeightFSRSumwUp(reader, "m_PSWeightFSRSumwUp");//Sum of genEventWeight * PSWeightUp
    TTreeReaderValue<Double_t> PSWeightFSRSumwDown(reader, "m_PSWeightFSRSumwDown");//Sum of genEventWeight * PSWeightDown

    Double_t sumGen = 0.;
    Double_t sumGenScale = 0;
    while (reader.Next())
    {
        sumGen += *genEventSumw;
        switch (index)
        {
        case 0://pdf alpha s up, 101: uncertainty up
            // sumGenScale += (1.+LHEPdfSumw[101])*(*genEventSumw);
            sumGenScale += (LHEPdfSumw[101])*(*genEventSumw); //!!!It seems here it's the SF rather than uncertainty as in LHEPdfWeight branch
            // std::cout<<"LHEPdfSumw[101] = "<<LHEPdfSumw[101]<<"\n";
            break;
        case 1://pdf alpha s down, 102: uncertainty down
            sumGenScale += (LHEPdfSumw[102])*(*genEventSumw);
            break;
        case 2: 
            //i event: uncer = sqrt(1 + (LHEPdfWeight[1] - LHEPdfWeight[0])^2 + ... + (LHEPdfWeight[100] - LHEPdfWeight[0])^2)
            sumGenScale += *LHEPdfSumwUp;
            break;
        case 3:
            sumGenScale += *LHEPdfSumwDown;
            break;
        case 4:
            sumGenScale += *PSWeightISRSumwUp;
            break;
        case 5:
            sumGenScale += *PSWeightISRSumwDown;
            break;
        case 6:
            sumGenScale += *PSWeightFSRSumwUp;
            break;
        case 7:
            sumGenScale += *PSWeightFSRSumwDown;
            break;

        default:
            break;
        }
    }
    Double_t scale = std::abs(sumGenScale)>1e-10? sumGen/sumGenScale:1;

    file->Close();
    return scale;
}






};



