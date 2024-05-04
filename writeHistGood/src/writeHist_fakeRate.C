
#include "../include/writeHist_fakeRate.h"
#include "../include/inputFileMap.h"
#include "../include/commenSelectionAndWeight.h"
#include "../../myLibrary/commenFunction.h"
#include "../include/functions.h"
#include "../../src_cpp/lumiAndCrossSection.h"

#include <vector>

Bool_t getFRandError(const std::vector<EtaProngGraph>& graphs, Double_t eta, int tauProng, Double_t pt, Double_t& fr, Double_t& errLow, Double_t& errHigh) {
    for (const auto& graph : graphs) {
        if (graph.isInEtaRange(eta) && graph.tauProng == tauProng) {
            int n = graph.graph->GetN();
            Double_t x, y;
            graph.graph->GetPoint(0, x, y); // Get the first point
            Double_t minX = x - graph.graph->GetErrorXlow(0);
            graph.graph->GetPoint(n-1, x, y); // Get the last point
            Double_t maxX = x + graph.graph->GetErrorXhigh(n-1);

            int index = -1; // Index of the point to use

            // Check if pt is out of range
            if (pt < minX) {
                // Use the first bin
                index = 0;
            } else if (pt > maxX) {
                // Use the last bin
                index = n - 1;
            } else {
                // pt is within range, find the correct bin
                for (int i = 0; i < n; ++i) {
                    graph.graph->GetPoint(i, x, y);
                    if (pt >= x - graph.graph->GetErrorXlow(i) && pt <= x + graph.graph->GetErrorXhigh(i)) {
                        index = i; // Correct bin found
                        break;
                    }
                }
            }

            if (index != -1) {
                // Retrieve the FR and its errors for the determined bin
                graph.graph->GetPoint(index, x, y);
                fr = y;
                errLow = graph.graph->GetErrorYlow(index);
                errHigh = graph.graph->GetErrorYhigh(index);
                return kTRUE;
            } else {
                // This else part is technically not needed as index will always be set
                // but is kept for logical completeness and future-proofing.
                return kFALSE;
            }
        }
    }
    return kFALSE;
}


Double_t calFRWeight(const Double_t taus_1pt, const Double_t taus_1eta, const Int_t taus_1prongNum, TH2D *FR_TH2D_1prong, TH2D *FR_TH2D_3prong, Double_t &FRWeight_up, Double_t &FRWeight_down)
{
    // might need error handling for this
    // Double_t FRWeight = 1.0; // the defaul t value for FRWeight should not be 1!!!
    // set the default FRWeight to the last bin
    TH2D *FR_TH2D;
    switch (taus_1prongNum)
    {
    case 1:
        FR_TH2D = FR_TH2D_1prong;
        break;
    case 2:
        FR_TH2D = FR_TH2D_3prong;
        break;
    case 3:
        FR_TH2D = FR_TH2D_3prong;
        break;
    default:
        //what to do with events with 0 or more taus_1prongNum
        std::cout<<"BAD!!! FR have to applied to events with fake tau!!!\n";
        break;
    }

    Double_t FR = TTTT::get2DSF(taus_1pt, std::abs(taus_1eta), FR_TH2D, 0);
    Double_t FR_sigma = TTTT::get2DSF(taus_1pt, std::abs(taus_1eta), FR_TH2D, 5);
    if (FR > 0.5)
    {
        FR = 0.1;
        FR_sigma = 0.1;
    }

    Double_t FRWeight = FR / (1 - FR);
    FRWeight_up = FRWeight + FR_sigma / std::pow((1 - FR), 2);
    FRWeight_down = FRWeight - FR_sigma / std::pow((1 - FR), 2);
    return FRWeight;
};

void pushBackHiscVec(std::vector<std::shared_ptr<histForRegionsBase>> &histsForRegion_vec, const std::vector<TString> &regionsForVariables, TString m_processName, event *e)
{
    histsForRegion_vec.clear();

    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;

    std::shared_ptr<histsForRegionsMap<Double_t>> jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_bScore_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 5., regionsForVariables, &(e->jets_bScore));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_HT));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_6pt));
    SP_d jets_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2pt", "p_{T}^{2nd jet}(GeV)", m_processName, 10, 40, 600, regionsForVariables, &(e->jets_2pt));
    SP_d jets_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3pt", "p_{T}^{3th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_3pt));
    SP_d jets_4pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4pt", "p_{T}^{4th jet}(GeV)", m_processName, 10, 40, 300, regionsForVariables, &(e->jets_4pt));
    SP_d jets_5pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5pt", "p_{T}^{5th jet}(GeV)", m_processName, 10, 40, 160, regionsForVariables, &(e->jets_5pt));
    SP_d jets_7pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_7pt", "p_{T}^{7th jet}(GeV)", m_processName, 10, 40, 145, regionsForVariables, &(e->jets_7pt));

    SP_d jets_rationHT_4toRest_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_rationHT_4toRest", "HT^{4 leaading jets}/HT^{rest of jets}", m_processName, 10, 0, 12, regionsForVariables, &(e->jets_rationHT_4toRest));
    SP_d jets_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_transMass", "m_{T}^{jets}", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_transMass));
    SP_d jets_avaregeDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_average_deltaR", "average(#Delta R)^{jets}", m_processName, 10, 1.2, 3.2, regionsForVariables, &(e->jets_average_deltaR));
    SP_d jets_1btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1btag", "btag^{1st jet}", m_processName, 40, 0, 1, regionsForVariables, &(e->jets_1btag));
    SP_d jets_2btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2btag", "btag^{2nd jet}", m_processName, 40, 0, 1, regionsForVariables, &(e->jets_2btag));
    SP_d jets_3btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3btag", " btag^{3rd jet}", m_processName, 40, 0, 1, regionsForVariables, &(e->jets_3btag));
    SP_d jets_4btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4btag", "btag^{4th jet}", m_processName, 40, 0, 1, regionsForVariables, &(e->jets_4btag));
    SP_d jets_5btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5btag", "btag^{5th jet}", m_processName, 40, 0, 1, regionsForVariables, &(e->jets_5btag));
    SP_d jets_6btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6btag", "6th jet btag", m_processName, 40, 0, 1, regionsForVariables, &(e->jets_6btag));
    SP_d jets_4largestBscoreSum_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreSum", "sum of 4 largest jets b score", m_processName, 30, 0.6,  4, regionsForVariables, &(e->jets_4largestBscoreSum));
    SP_d jets_4largestBscoreMulti_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreMulti", "jets_4largestBscoreMulti", m_processName, 30, 0, 1, regionsForVariables, &(e->jets_4largestBscoreMulti));

    SP_d MET_pt_class = std::make_shared<histsForRegionsMap<Double_t>>("MET_pt", "MET", m_processName, 10, 0, 500, regionsForVariables, &(e->MET_pt));
    SP_d bjetsM_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_HT", "HT^{b jets}", m_processName, 10, 0, 900, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_MHT", "MHT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_invariantMass", "m^{b jets}", m_processName, 10, 0, 1200, regionsForVariables, &(e->bjetsM_invariantMass));
    SP_d bjetsM_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_1pt", "p_{T}^{1st bjet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsM_1pt));
    SP_d bjetsM_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsM_2pt));
    SP_d bjetsM_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_minDeltaR", "min(#Delta R_{b jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsM_minDeltaR));
    SP_d tausT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1pt", "p_{T}^{1st #tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausT_1pt));
    SP_d tausT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1eta", "#eta_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1eta));
    SP_d tausT_1phi_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1phi", "#phi_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1phi));
    SP_d tausT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_HT", "HT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_HT));
    SP_d tausT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_MHT", "MHT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_MHT));
    SP_d tausT_leptonsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_leptonsT_invariantMass", "m_{#tau and lep}(GeV)", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_leptonsT_invariantMass));
    SP_d tausF_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1eta", "#eta^{ #tau}", m_processName, 24, -2.4, 2.4, regionsForVariables, &(e->tausF_1eta));
    SP_d tausF_1jetPtFR_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1jetPtFRWeight", " #tau's mother jet  p_{T}(GeV)", m_processName, 28, 20, 300, regionsForVariables, &(e->tausF_1jetPt));
    SP_d  tausF_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausF_1pt", "p_{T}^{ #tau}(GeV)", m_processName, 20, 20, 100, regionsForVariables, &(e->tausF_1pt));

    SP_d muonsTopMVAT_1t_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_1pt", "p_{T}^{#mu}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->muonsTopMVAT_1pt));
    SP_d elesTopMVAT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_1pt", "p_{T}^{e}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->elesTopMVAT_1pt));

    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 7, 5.5, 12.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsM_num));
    SP_i tausT_leptonsTopMVA_chargeMulti_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_leptonsTopMVA_chargeMulti", "charge^{#tau}*charge^{lep}", m_processName, 3, -1.5, 1.5, regionsForVariables, &(e->tausT_leptonsTopMVA_chargeMulti));
    SP_i tausF_prongNum_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_prongNum", " #tau prong", m_processName, 3, 1, 4, regionsForVariables, &(e->tausF_prongNum));
    SP_i tausF_charge_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_charge", " #tau charge", m_processName, 2, -2, 2, regionsForVariables, &(e->tausF_1charge));
    SP_i tausF_1decayMode_class = std::make_shared<histsForRegionsMap<Int_t>>("tausF_1decayMode", " #tau decay mode", m_processName, 12, 0, 12, regionsForVariables, &(e->tausF_1decayMode));

    // I guess jets_1pt_class goes out range and destroyed after this function
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_bScore_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    histsForRegion_vec.push_back(jets_2pt_class);
    histsForRegion_vec.push_back(jets_3pt_class);
    histsForRegion_vec.push_back(jets_4pt_class);
    histsForRegion_vec.push_back(jets_5pt_class);
    histsForRegion_vec.push_back(jets_7pt_class);
    histsForRegion_vec.push_back(jets_rationHT_4toRest_class);
    histsForRegion_vec.push_back(jets_transMass_class);
    histsForRegion_vec.push_back(jets_avaregeDeltaR_class);
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
    histsForRegion_vec.push_back(tausT_1pt_class);
    histsForRegion_vec.push_back(tausT_1eta_class);
    histsForRegion_vec.push_back(tausT_1phi_class);
    histsForRegion_vec.push_back(tausT_HT_class);
    histsForRegion_vec.push_back(tausT_MHT_class);
    histsForRegion_vec.push_back(tausT_leptonsT_invariantMass_class);
    histsForRegion_vec.push_back(muonsTopMVAT_1t_class);
    histsForRegion_vec.push_back(elesTopMVAT_1pt_class);
    histsForRegion_vec.push_back(bjetsM_num_class);
    histsForRegion_vec.push_back(tausT_leptonsTopMVA_chargeMulti_class);
}

void WH_fakeRate::Init()
{
    std::cout << "Start to initilation....................................................\n";
/*
    // FR weighted
    std::vector<TString> regionsForFRWeighting = {
        // regions nessary for plotting data/MC
        "1tau0lCR", // 0
        "1tau0lCRGen",
        "1tau0lCRNotGen", // 2
        // for FakeRate weighting
        "1tau0lVRLTauNotT_Weighted",    // 3
        "1tau0lCRLTauNotT_Weighted",    // 4
        "1tau0lVRLTauNotTGen_Weighted", // 5
        "1tau0lCRLTauNotTGen_Weighted", // 6
        //
        "1tau0lVR", // 7
        "1tau0lVRGen",
        "1tau0lVRNotGen",
        //
        "1tau0lSR", // 10
        "1tau0lSRGen",
        "1tau0lSRNotGen",
        "1tau0lSRLTauNotT_Weighted",    // 13
        "1tau0lSRLTauNotTGen_Weighted", // 14
        //
        "1tau0lCRc", // 27
        "1tau0lCRcGen",
        "1tau0lCRcLTauNotT_Weighted",    // 29
        "1tau0lCRcLTauNotTGen_Weighted", // 30
        // CRb
        "1tau0lCRb", // 27
        "1tau0lCRbGen",
        "1tau0lCRbLTauNotT_Weighted",    // 29
        "1tau0lCRbLTauNotTGen_Weighted", // 30
        // FR uncertainty variation
        "1tau0lVRLTauNotT_Weighted_up",       // 19
        "1tau0lVRLTauNotT_Weighted_down",     //
        "1tau0lVRLTauNotTGen_Weighted_up",    //
        "1tau0lVRLTauNotTGen_Weighted_down",  //
        "1tau0lSRLTauNotT_Weighted_up",       // 23
        "1tau0lSRLTauNotT_Weighted_down",     // 24
        "1tau0lSRLTauNotTGen_Weighted_up",    // 25
        "1tau0lSRLTauNotTGen_Weighted_down",  // 26
        "1tau0lCRcLTauNotT_Weighted_up",      // 15
        "1tau0lCRcLTauNotT_Weighted_down",    // 16
        "1tau0lCRcLTauNotTGen_Weighted_up",   //
        "1tau0lCRcLTauNotTGen_Weighted_down", //
        "1tau0lCRbLTauNotT_Weighted_up",      // 15
        "1tau0lCRbLTauNotT_Weighted_down",    // 16
        "1tau0lCRbLTauNotTGen_Weighted_up",   //
        "1tau0lCRbLTauNotTGen_Weighted_down", //

    };
    pushBackHiscVec(histsForRegion_vec, regionsForFRWeighting, m_processName, e);

    // get FR hists
    TFile *FRFile = new TFile(WH::FRfileMap.at(m_era).at(0).Data(), "READ");
    FR_hist = (TH2D *)FRFile->Get("fakeRate2D");
    TFile *FRFile_3prong = new TFile(WH::FRfileMap.at(m_era).at(1).Data(), "READ");
    FR_hist_3prong = (TH2D *)FRFile_3prong->Get("fakeRate2D");
    printf("Reading FR file 1prong: %s \n", FRFile->GetName());
    printf("Reading FR file 3prong: %s \n", FRFile_3prong->GetName());

*/
    //regions for measuring FR
    if(m_ifMeasure){

        std::vector<TString> regionsEtaDivided = {
        "1tau0lCRLTau_Eta1", 
        "1tau0lCRLTau_Eta2",
        "1tau0lCRLTau_Eta3",
        "1tau0lCRLTauGen_Eta1", 
        "1tau0lCRLTauGen_Eta2",
        "1tau0lCRLTauGen_Eta3",
        "1tau0lCR_Eta1", // 6
        "1tau0lCR_Eta2",
        "1tau0lCR_Eta3",
        "1tau0lCRGen_Eta1", // 9
        "1tau0lCRGen_Eta2",
        "1tau0lCRGen_Eta3",
        // FR measurment in MR
        "1tau0lMRLTau_Eta1", // 20
        "1tau0lMRLTau_Eta2",
        "1tau0lMRLTau_Eta3",    // 22
        "1tau0lMRLTauGen_Eta1", // 23
        "1tau0lMRLTauGen_Eta2", // 24
        "1tau0lMRLTauGen_Eta3",
        "1tau0lMR_Eta1", // 26
        "1tau0lMR_Eta2",
        "1tau0lMR_Eta3",    // 28
        "1tau0lMRGen_Eta1", //
        "1tau0lMRGen_Eta2", // 30
        "1tau0lMRGen_Eta3", //
        // for measuring FR in VR
        "1tau0lVRLTau_Eta1", // 44
        "1tau0lVRLTau_Eta2",
        "1tau0lVRLTau_Eta3", // 46
        "1tau0lVRLTauGen_Eta1",
        "1tau0lVRLTauGen_Eta2", // 48
        "1tau0lVRLTauGen_Eta3",
        "1tau0lVR_Eta1", // 50
        "1tau0lVR_Eta2",
        "1tau0lVR_Eta3", // 52
        "1tau0lVRGen_Eta1",
        "1tau0lVRGen_Eta2", // 54
        "1tau0lVRGen_Eta3",
        };
        tausF_1jetPt_class = histsForRegionsMap<Double_t>("tausF_1jetPt", "pT^{#tau's mother jet}(GeV)", m_processName, 28, 20, 300, regionsEtaDivided, &(e->tausF_1jetPt));
        tausF_1jetPt_class.setDir(m_outFile);

    }else{
        std::vector<TString> regionsForApplyingFR = {
            "1tau0lMRLTauNotT_Weighted",  
            "1tau0lMRLTauNotTGen_Weighted",
            "1tau0lMRGen",
            "1tau0lMR",
            "1tau0lVRLTauNotT_Weighted",
            "1tau0lVRLTauNotTGen_Weighted",
            "1tau0lVRGen",
            "1tau0lVR",
            "1tau0lCRLTauNotT_Weighted",
            "1tau0lCRLTauNotTGen_Weighted",
            "1tau0lCRGen",
            "1tau0lCR",
            "1tau0lSRLTauNotT_Weighted",
            "1tau0lSRLTauNotTGen_Weighted",
            "1tau0lSRGen",
            "1tau0lSR",
        };
        WH::initializeHistVec( regionsForApplyingFR, histsForRegion_vec, m_processName, e);
        WH::histRegionsVectSetDir(histsForRegion_vec, m_outFile);

        //get FR
        TFile* file=new TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0FR_measure1prong/results/fakeRateInPtEta.root", "READ"); 
        TFile* file3Prong=new TFile("/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/forMVA/2018/v0baselineHT450_v75OverlapRemovalFTau/mc/variableHists_v0FR_measure3prong/results/fakeRateInPtEta.root", "READ"); 
        // Assuming these graphs are already created and stored in the ROOT file
        m_graphs.emplace_back(0.0, 0.8, 1, dynamic_cast<TGraphAsymmErrors*>(file->Get("fakeRate_Eta1")));
        m_graphs.emplace_back(0.8, 1.5, 1, dynamic_cast<TGraphAsymmErrors*>(file->Get("fakeRate_Eta2")));
        m_graphs.emplace_back(1.5, 2.3, 1, dynamic_cast<TGraphAsymmErrors*>(file->Get("fakeRate_Eta3")));
        m_graphs.emplace_back(0.0, 0.8, 3, dynamic_cast<TGraphAsymmErrors*>(file3Prong->Get("fakeRate_Eta1")));
        m_graphs.emplace_back(0.8, 1.5, 3, dynamic_cast<TGraphAsymmErrors*>(file3Prong->Get("fakeRate_Eta2")));
        m_graphs.emplace_back(1.5, 2.3, 3, dynamic_cast<TGraphAsymmErrors*>(file3Prong->Get("fakeRate_Eta3")));
    }

     std::cout<< "Initialization done\n\n";
}

void WH_fakeRate::LoopTree(UInt_t entry)
{
    Long64_t allEvent = m_tree->GetEntries();
    if (entry > 0)
    {
        allEvent = entry;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e, m_isRun3)))
        {
            continue;
        }

        // event weight
        Double_t basicWeight = baseWeightCal(e, i, m_isRun3, m_isData, kTRUE);//!!!
        // Double_t basicWeight = e->EVENT_genWeight.v() *e->EVENT_prefireWeight.v() * e->PUweight_.v(); 
        
        Bool_t isTauLNum = (e->tausF_num.v() == 1);
        Bool_t isTauLNumGen = (e->tausF_genTauNum.v() == 1);
        Bool_t isTauTNumGen = (e->tausT_genTauNum.v() == 1);
        // Int_t tausTNum = e->tausTT_num.v();//!
        Int_t tausTNum = e->tausT_num.v();//!!
        Int_t jetsNum = e->jets_num.v();
        Int_t bjetsNum = e->bjetsM_num.v();
        Int_t lepNum = e->elesTopMVAT_num.v() + e->muonsTopMVAT_num.v();
        // 1tau0lMR
        Bool_t is1tau0lMR = tausTNum == 1  && jetsNum >= 8 && bjetsNum == 2; 
        Bool_t is1tau0lMRLTau = isTauLNum && jetsNum >= 8 && bjetsNum == 2;
        //1tau0lVR
        Bool_t is1tau0lVR = tausTNum==1 && lepNum == 0 && jetsNum < 8 && bjetsNum >=3;
        Bool_t is1tau0lVRLTau = isTauLNum && lepNum == 0 && jetsNum < 8 && bjetsNum >=3;
        //1tau0lCR
        Bool_t is1tau0lCR = tausTNum==1 && lepNum == 0 && jetsNum < 8 && bjetsNum ==2;
        Bool_t is1tau0lCRLTau = isTauLNum && lepNum == 0 && jetsNum < 8 && bjetsNum ==2;
        //1tau0lSR
        Bool_t is1tau0lSR = SR1tau1lSel(e, 1, m_isRun3);
        Bool_t is1tau0lSRLTau = isTauLNum && lepNum == 0 && jetsNum >= 8 && bjetsNum >=3;

        Double_t tausF_1jetEtaAbs = std::abs(e->tausF_1eta.v());
        if(m_ifMeasure){
            // if (!(e->tausF_prongNum.v() == 1)){//!!!
            if (!(e->tausF_prongNum.v() == 2 || e->tausF_prongNum.v()==3)){//!!!
                continue;
            }

            // Double_t tausF_1jetEtaAbs = TMath::Abs(e->tausF_1eta.v());//function strange
            Bool_t isEta1 = 0 < tausF_1jetEtaAbs && tausF_1jetEtaAbs <= 0.8;
            Bool_t isEta2 = 0.8 < tausF_1jetEtaAbs && tausF_1jetEtaAbs <= 1.5;
            Bool_t isEta3 = 1.5 < tausF_1jetEtaAbs && tausF_1jetEtaAbs <= 2.3; //!2.5 for run 3
            if(m_isData){
                tausF_1jetPt_class.fillHistVec("1tau0lMRLTau_Eta1", basicWeight, is1tau0lMRLTau &&  isEta1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRLTau_Eta2", basicWeight, is1tau0lMRLTau &&  isEta2, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRLTau_Eta3", basicWeight, is1tau0lMRLTau &&  isEta3, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMR_Eta1", basicWeight, is1tau0lMR &&  isEta1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMR_Eta2", basicWeight, is1tau0lMR &&  isEta2, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMR_Eta3", basicWeight, is1tau0lMR &&  isEta3, m_isData);
                //VR
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_Eta1", basicWeight, is1tau0lVRLTau &&  isEta1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_Eta2", basicWeight, is1tau0lVRLTau &&  isEta2, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTau_Eta3", basicWeight, is1tau0lVRLTau &&  isEta3, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_Eta1", basicWeight, is1tau0lVR &&  isEta1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_Eta2", basicWeight, is1tau0lVR &&  isEta2, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVR_Eta3", basicWeight, is1tau0lVR &&  isEta3, m_isData);
                //CR
                tausF_1jetPt_class.fillHistVec("1tau0lCRLTau_Eta1", basicWeight, is1tau0lCRLTau &&  isEta1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRLTau_Eta2", basicWeight, is1tau0lCRLTau &&  isEta2, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRLTau_Eta3", basicWeight, is1tau0lCRLTau &&  isEta3, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCR_Eta1", basicWeight, is1tau0lCR &&  isEta1, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCR_Eta2", basicWeight, is1tau0lCR &&  isEta2, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCR_Eta3", basicWeight, is1tau0lCR &&  isEta3, m_isData);
            }else{
                tausF_1jetPt_class.fillHistVec("1tau0lMRLTauGen_Eta1", basicWeight, is1tau0lMRLTau && isEta1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRLTauGen_Eta2", basicWeight, is1tau0lMRLTau &&  isEta2 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRLTauGen_Eta3", basicWeight, is1tau0lMRLTau &&  isEta3 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRGen_Eta1", basicWeight, is1tau0lMR && isEta1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRGen_Eta2", basicWeight, is1tau0lMR && isEta2 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lMRGen_Eta3", basicWeight, is1tau0lMR && isEta3 && isTauTNumGen, m_isData);
                //VR
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_Eta1", basicWeight, is1tau0lVRLTau &&  isEta1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_Eta2", basicWeight, is1tau0lVRLTau &&  isEta2 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRLTauGen_Eta3", basicWeight, is1tau0lVRLTau &&  isEta3 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_Eta1", basicWeight, is1tau0lVR && isEta1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_Eta2", basicWeight, is1tau0lVR && isEta2 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lVRGen_Eta3", basicWeight, is1tau0lVR && isEta3 && isTauTNumGen, m_isData);
                //CR
                tausF_1jetPt_class.fillHistVec("1tau0lCRLTauGen_Eta1", basicWeight, is1tau0lCRLTau &&  isEta1 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRLTauGen_Eta2", basicWeight, is1tau0lCRLTau &&  isEta2 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRLTauGen_Eta3", basicWeight, is1tau0lCRLTau &&  isEta3 && isTauLNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRGen_Eta1", basicWeight, is1tau0lCR && isEta1 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRGen_Eta2", basicWeight, is1tau0lCR && isEta2 && isTauTNumGen, m_isData);
                tausF_1jetPt_class.fillHistVec("1tau0lCRGen_Eta3", basicWeight, is1tau0lCR && isEta3 && isTauTNumGen, m_isData);
            }
        }else{//FR application 
            Double_t FRWeight, FRWeight_up, FRWeight_down; 
            Int_t tauProng = !(e->tausF_prongNum.v()==1)? 3 : e->tausF_prongNum.v(); //!!!seems lots of tausF has taus Prong 4 or 6
            Bool_t ifFR = getFRandError(m_graphs, tausF_1jetEtaAbs, tauProng, e->tausF_1jetPt.v(), FRWeight, FRWeight_up, FRWeight_down);
            // std::cout<<"FRWeight="<<FRWeight<<" FRWeight_up="<<FRWeight_up<<" FRWeight_down="<<FRWeight_down<<"\n";
            // std::cout << "tauProng=" << tauProng << "\n";
            FRWeight = FRWeight / (1. - FRWeight);
            std::cout << "FRWeight=" << FRWeight << "\n";
            if (!ifFR)
            {
                std::cout<<"!!!FR not get<<\n";
                std::cout<<"eta="<<tausF_1jetEtaAbs<<" prong="<<tauProng<<" pt="<<e->tausF_1jetPt.v()<<"\n";
            }
            Bool_t notTauT = e->tausT_num.v() == 0;
            Bool_t genTau = e->tausF_genTauNum.v() == 1;
            if(m_isData){
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lMRLTau && notTauT &&lepNum == 0, "1tau0lMRLTauNotT_Weighted", FRWeight, !m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lCRLTau && notTauT &&lepNum == 0, "1tau0lCRLTauNotT_Weighted", FRWeight, !m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lVRLTau && notTauT &&lepNum == 0, "1tau0lVRLTauNotT_Weighted", FRWeight, !m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lSRLTau && notTauT &&lepNum == 0, "1tau0lSRLTauNotT_Weighted", FRWeight, !m_isData);
            }else{
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lMRLTau && notTauT && genTau&&lepNum == 0, "1tau0lMRLTauNotTGen_Weighted", basicWeight*FRWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lCRLTau && notTauT && genTau&&lepNum == 0, "1tau0lCRLTauNotTGen_Weighted", basicWeight*FRWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lVRLTau && notTauT && genTau&&lepNum == 0, "1tau0lVRLTauNotTGen_Weighted", basicWeight*FRWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lSRLTau && notTauT && genTau&&lepNum == 0, "1tau0lSRLTauNotTGen_Weighted", basicWeight*FRWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lMR&&lepNum==0 && genTau, "1tau0lMRGen", basicWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR && genTau, "1tau0lVRGen", basicWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR && genTau, "1tau0lCRGen", basicWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lSR && genTau, "1tau0lSRGen", basicWeight, m_isData);
                WH::histRegionVectFill(histsForRegion_vec, is1tau0lSR, "1tau0lSR", basicWeight, m_isData);//!blinded in SR
            }
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lMR&&lepNum==0, "1tau0lMR", basicWeight, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lVR, "1tau0lVR", basicWeight, m_isData);
            WH::histRegionVectFill(histsForRegion_vec, is1tau0lCR, "1tau0lCR", basicWeight, m_isData);
        }


    }
    std::cout << "end of event loop\n\n";
}

void WH_fakeRate::Terminate()
{
    std::cout << "Termintate: ..........................................\n";
    if (!m_isData)
    {
        Double_t genWeightSum = TTTT::getGenSum(m_inputDir + m_processName + ".root");
        Double_t processScale = ((TTTT::lumiMap.at(m_era) * TTTT::crossSectionMap.at(m_processName)) / genWeightSum);
        std::cout << "m_processName=" << m_processName << " lumi=" << TTTT::lumiMap.at(m_era) << " crossSection=" << TTTT::crossSectionMap.at(m_processName) << "\n";
        // WH::histRegionsVectScale(histsForRegion_vec, processScale);
        tausF_1jetPt_class.scale(processScale);
        tausF_1jetPt_class.print();

        WH::histRegionsVectScale(histsForRegion_vec, processScale);
    };
    for (UInt_t i = 0; i < histsForRegion_vec.size(); i++)
    {
        if (i > 0)
        {
            continue;
        }
        histsForRegion_vec.at(i)->print();
    }

    m_outFile->Write();
    std::cout << "outputFile here: " << m_outFile->GetName() << "\n";
}

WH_fakeRate::~WH_fakeRate()
{
    m_file->Close();
    m_outFile->Close();
}