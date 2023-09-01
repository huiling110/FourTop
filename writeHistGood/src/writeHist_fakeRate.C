
#include "../include/writeHist_fakeRate.h"
#include "../include/inputFileMap.h"
#include "../include/commenSelectionAndWeight.h"


Double_t calFRWeight(const Double_t taus_1pt, const Double_t taus_1eta, const Double_t taus_1prongNum, TH2D *FR_TH2D_1prong, TH2D *FR_TH2D_3prong, Double_t &FRWeight_up, Double_t &FRWeight_down)
{
    // might need error handling for this
    // Double_t FRWeight = 1.0; // the defaul t value for FRWeight should not be 1!!!
    // set the default FRWeight to the last bin
    TH2D *FR_TH2D;
    if (taus_1prongNum == 1)
    {
        FR_TH2D = FR_TH2D_1prong;
    }
    else
    {
        FR_TH2D = FR_TH2D_3prong;
    }
    Int_t binxNum = FR_TH2D->GetNbinsX();
    Int_t binyNum = FR_TH2D->GetNbinsY();
    Double_t FR = FR_TH2D->GetBinContent(binxNum, binyNum);
    Double_t FR_sigma = FR_TH2D->GetBinError(binxNum, binyNum);
    if (taus_1pt > 20.0 && taus_1pt <= 300.0)
    {

        Int_t binx = FR_TH2D->GetXaxis()->FindBin(taus_1pt);
        Int_t biny = FR_TH2D->GetYaxis()->FindBin(std::abs(taus_1eta)); // FineBin: If x is underflow or overflow, attempt to extend the axis if TAxis::kCanExtend is true. Otherwise, return 0 or fNbins+1.
        FR = FR_TH2D->GetBinContent(binx, biny);                        // not clear for underflow or overflow bin which binContent retrieves from ROOT documentation
        FR_sigma = FR_TH2D->GetBinError(binx, biny);
        //???need better error handling
        // if (FR < 0.000001)
        // {
        // std::cout << "taupt=" << taus_1pt << "; tauEta=" << taus_1eta << "\n";
        // std::exit(1);
        // }
    }
    Double_t FRWeight = FR / (1 - FR);
    FRWeight_up = FRWeight + FR_sigma / std::pow((1 - FR), 2);
    FRWeight_down = FRWeight - FR_sigma / std::pow((1 - FR), 2);
    return FRWeight;
}

void pushBackHiscVec( std::vector<std::shared_ptr<histForRegionsBase>>& histsForRegion_vec, const std::vector<TString>& regionsForVariables, TString m_processName, event* e){
    histsForRegion_vec.clear();

    using SP_d = std::shared_ptr<histsForRegionsMap<Double_t>>;
    using SP_i = std::shared_ptr<histsForRegionsMap<Int_t>>;

    std::shared_ptr<histsForRegionsMap<Double_t>> jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_bScore_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", m_processName, 10, 0, 4.5, regionsForVariables, &(e->jets_bScore));
    SP_d jets_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_HT", "HT(GeV)", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_HT));
    SP_d jets_6pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6pt", "p_{T}^{6th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_6pt));
    // SP_d jets_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1pt", "p_{T}^{1st jet}(GeV)", m_processName, 10, 40, 700, regionsForVariables, &(e->jets_1pt));
    SP_d jets_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2pt", "p_{T}^{2nd jet}(GeV)", m_processName, 10, 40, 600, regionsForVariables, &(e->jets_2pt));
    SP_d jets_3pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3pt", "p_{T}^{3th jet}(GeV)", m_processName, 10, 40, 140, regionsForVariables, &(e->jets_3pt));
    SP_d jets_4pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4pt", "p_{T}^{4th jet}(GeV)", m_processName, 10, 40, 300, regionsForVariables, &(e->jets_4pt));
    SP_d jets_5pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5pt", "p_{T}^{5th jet}(GeV)", m_processName, 10, 40, 160, regionsForVariables, &(e->jets_5pt));
    SP_d jets_7pt_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_7pt", "p_{T}^{7th jet}(GeV)", m_processName, 10, 40, 145, regionsForVariables, &(e->jets_7pt));

    SP_d jets_rationHT_4toRest_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_rationHT_4toRest", "HT^{4 leaading jets}/HT^{rest of jets}", m_processName, 10, 0, 12, regionsForVariables, &(e->jets_rationHT_4toRest));
    // SP_d jets_leading2invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_leading2invariantMass", "m^{2 leading jets}", m_processName, 10, 100, 1000, regionsForVariables, &(e->jets_leading2invariantMass));
    SP_d jets_transMass_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_transMass", "m_{T}^{jets}", m_processName, 10, 500, 1800, regionsForVariables, &(e->jets_transMass));
    SP_d jets_avaregeDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_average_deltaR", "average(#Delta R)^{jets}", m_processName, 10, 1.2, 3.2, regionsForVariables, &(e->jets_average_deltaR));
    // SP_d jets_4largestBscoreMulti_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4largestBscoreMulti", "#sqrt{#prod_{i=4 highest} bscore_{i}^{jet}}", m_processName, 10, 0, 0.3, regionsForVariables, &(e->jets_4largestBscoreMulti));
    SP_d jets_1btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_1btag", "btag^{1st jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_1btag));
    SP_d jets_2btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_2btag", "btag^{2nd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_2btag));
    SP_d jets_3btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_3btag", " btag^{3rd jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_3btag));
    SP_d jets_4btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_4btag", "btag^{4th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_4btag));
    SP_d jets_5btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_5btag", "btag^{5th jet}",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_5btag));
    SP_d jets_6btag_class = std::make_shared<histsForRegionsMap<Double_t>>("jets_6btag", "6th jet btag",m_processName, 40, 0, 1, regionsForVariables, &(e->jets_6btag));
    // SP_d = std::make_shared<histsForRegionsMap<Double_t>>("", 10));

    SP_d MET_pt_class = std::make_shared<histsForRegionsMap<Double_t>>("MET_pt", "MET", m_processName, 10, 0, 500, regionsForVariables, &(e->MET_pt));
    SP_d bjetsM_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_HT", "HT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_MHT", "MHT^{b jets}", m_processName, 10, 25, 700, regionsForVariables, &(e->bjetsM_HT));
    SP_d bjetsM_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_invariantMass", "m^{b jets}", m_processName, 10, 0, 1000, regionsForVariables, &(e->bjetsM_invariantMass));
    SP_d bjetsM_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_1pt", "p_{T}^{1st bjet}", m_processName, 10, 25, 600, regionsForVariables, &(e->bjetsM_1pt));
    SP_d bjetsM_2pt_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_2pt", "p_{T}^{2nd bjet}", m_processName, 10, 25, 500, regionsForVariables, &(e->bjetsM_2pt));
    SP_d bjetsM_minDeltaR_class = std::make_shared<histsForRegionsMap<Double_t>>("bjetsM_minDeltaR", "min(#Delta R_{b jets})", m_processName, 6, 0, 5, regionsForVariables, &(e->bjetsM_minDeltaR));
    SP_d tausT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1pt", "p_{T}^{1st #tau}", m_processName, 10, 20, 200, regionsForVariables, &(e->tausT_1pt));
    SP_d tausT_1eta_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1eta", "#eta_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1eta));
    SP_d tausT_1phi_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_1phi", "#phi_{#tau}", m_processName, 10, 0, 3, regionsForVariables, &(e->tausT_1phi));
    SP_d tausT_HT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_HT", "HT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_HT));
    SP_d tausT_MHT_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_MHT", "MHT_{#tau}(GeV)", m_processName, 10, 25, 300, regionsForVariables, &(e->tausT_MHT));
    SP_d tausT_leptonsT_invariantMass_class = std::make_shared<histsForRegionsMap<Double_t>>("tausT_leptonsT_invariantMass", "m_{#tau and lep}(GeV)", m_processName, 10, 0, 500, regionsForVariables, &(e->tausT_leptonsT_invariantMass));

    SP_d muonsTopMVAT_1t_class = std::make_shared<histsForRegionsMap<Double_t>>("muonsTopMVAT_1pt", "p_{T}^{#mu}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->muonsTopMVAT_1pt));
    SP_d elesTopMVAT_1pt_class = std::make_shared<histsForRegionsMap<Double_t>>("elesTopMVAT_1pt", "p_{T}^{e}(GeV)", m_processName, 10, 0, 140, regionsForVariables, &(e->elesTopMVAT_1pt));


    SP_i jets_num_class = std::make_shared<histsForRegionsMap<Int_t>>("jets_num", "n^{jet}", m_processName, 7, 5.5, 12.5, regionsForVariables, &(e->jets_num));
    SP_i bjetsM_num_class = std::make_shared<histsForRegionsMap<Int_t>>("bjetsM_num", "n^{b jet}", m_processName, 8, -0.5, 7.5, regionsForVariables, &(e->bjetsM_num));
    SP_i tausT_leptonsTopMVA_chargeMulti_class = std::make_shared<histsForRegionsMap<Int_t>>("tausT_leptonsTopMVA_chargeMulti", "charge^{#tau}*charge^{lep}",m_processName, 3, -1.5, 1.5, regionsForVariables,  &(e->tausT_leptonsTopMVA_chargeMulti));

    //I guess jets_1pt_class goes out range and destroyed after this function
    histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_bScore_class);
    histsForRegion_vec.push_back(jets_num_class);
    histsForRegion_vec.push_back(jets_HT_class);
    histsForRegion_vec.push_back(jets_6pt_class);
    // histsForRegion_vec.push_back(jets_1pt_class);
    histsForRegion_vec.push_back(jets_2pt_class);
    histsForRegion_vec.push_back(jets_3pt_class);
    histsForRegion_vec.push_back(jets_4pt_class);
    histsForRegion_vec.push_back(jets_5pt_class);
    histsForRegion_vec.push_back(jets_7pt_class);
    histsForRegion_vec.push_back(jets_rationHT_4toRest_class);
    // histsForRegion_vec.push_back(jets_leading2invariantMass_class);
    histsForRegion_vec.push_back(jets_transMass_class);
    histsForRegion_vec.push_back(jets_avaregeDeltaR_class);
    // histsForRegion_vec.push_back(jets_4largestBscoreMulti_class);
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
    // histsForRegion_vec.push_back();


    histsForRegion_vec.push_back(bjetsM_num_class);
    histsForRegion_vec.push_back(tausT_leptonsTopMVA_chargeMulti_class);

}


void WH_fakeRate::Init(){
    std::cout << "Start to initilation....................................................\n";

    // FR weighted
    //???make this not vector index but clear name for regions
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
        // FR uncertainty variation
        "1tau0lCRLTauNotT_Weighted_up",      // 15
        "1tau0lCRLTauNotT_Weighted_down",    // 16
        "1tau0lCRLTauNotTGen_Weighted_up",   //
        "1tau0lCRLTauNotTGen_Weighted_down", //
        "1tau0lVRLTauNotT_Weighted_up",      // 19
        "1tau0lVRLTauNotT_Weighted_down",    //
        "1tau0lVRLTauNotTGen_Weighted_up",   //
        "1tau0lVRLTauNotTGen_Weighted_down", //
        "1tau0lSRLTauNotT_Weighted_up",      // 23
        "1tau0lSRLTauNotT_Weighted_down",    // 24
        "1tau0lSRLTauNotTGen_Weighted_up",   // 25
        "1tau0lSRLTauNotTGen_Weighted_down", // 26
        //
        "1tau0lCRc", // 27
        "1tau0lCRcGen",
        "1tau0lCRcLTauNotT_Weighted",    // 29
        "1tau0lCRcLTauNotTGen_Weighted", // 30

    };
    pushBackHiscVec(histsForRegion_vec, regionsForFRWeighting, m_processName, e);

    //get FR hists
    TFile *FRFile = new TFile(WH::FRfileMap.at(m_era).at(0).Data(), "READ");
    FR_hist = (TH2D *)FRFile->Get("fakeRate2D");
    TFile *FRFile_3prong = new TFile(WH::FRfileMap.at(m_era).at(1).Data(), "READ");
    FR_hist_3prong = (TH2D *)FRFile_3prong->Get("fakeRate2D");
    printf("Reading FR file:%s \n", FRFile->GetName());


    std::cout << "Initialization done\n\n";
}


void WH_fakeRate::LoopTree(UInt_t entry){
    Long64_t allEvent = m_tree->GetEntries();
    if (entry > 0)
    {
        allEvent = entry;
    }
    std::cout << "looping over trees of " << allEvent << "\n";

    for (UInt_t i = 0; i < allEvent; i++)
    {
        m_tree->GetEntry(i);

        if (!(baselineSelection(e)))
        {
            continue;
        }

    }

    Double_t FRWeight_up, FRWeight_down;
    Double_t FRWeight = 1.0;
    if (!m_ifMeasurement)
    {
        FRWeight = calFRWeight(*tausF_1jetPt, *tausF_1eta, *tausF_prongNum, FR_hist, FR_hist_3prong, FRWeight_up, FRWeight_down);
    }




    std::cout << "end of event loop\n\n";

}


WH_fakeRate::~WH_fakeRate(){
    m_file->Close();
    m_outFile->Close();
}