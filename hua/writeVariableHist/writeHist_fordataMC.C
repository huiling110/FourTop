#define writeHist_fordataMC_cxx
// The class definition in writeHist_fordataMC.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//

#include <TH2.h>
#include <TStyle.h>

#include <assert.h>
#include <cmath>
// #include <filesystem>

#include "../src_cpp/usefulFuction.h"
#include "../src_cpp/lumiAndCrossSection.h"
#include "writeHist_fordataMC.h"
#include "SFfileMap.h"

//???repeated in MV
Double_t calBtagR(Int_t jets_number, TH1D *btagRHist)
{
    Double_t r = 1.0;
    if (jets_number >= btagRHist->GetXaxis()->GetXmin() && jets_number <= btagRHist->GetXaxis()->GetXmax())
    {
        Int_t binx = btagRHist->GetXaxis()->FindBin(jets_number);
        r = btagRHist->GetBinContent(binx);
    }
    return r;
}

// Double_t 2dSFExtrac(Double_t x, Double_t y, TH2D *sfHist)
// {
// }

void writeHist_fordataMC::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
    if (isRegion)
    {
        eventCount_hists[vectorIndex]->Fill(.0, weight);
    }
}

void writeHist_fordataMC::fillHistsVectorMyclass(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
    if (isRegion)
    {
        for (UInt_t i = 0; i < vectorOfVariableRegions.size(); i++)
        {
            vectorOfVariableRegions[i].fillHistVec(vectorIndex, weight);
        }
        for (UInt_t i = 0; i < vectorOfVariableRegionsDouble.size(); i++)
        {
            vectorOfVariableRegionsDouble[i].fillHistVec(vectorIndex, weight);
        }
    }
}

void push_backHists(TString variable, Int_t binNum, Double_t minBin, Double_t maxBin, std::vector<TH1D *> &histsVariable, TString m_processName, std::vector<TString> &regions)
{
    for (UInt_t i = 0; i < regions.size(); i++)
    {
        TString iHistName = regions[i] + "_" + m_processName + "_" + variable;
        TH1D *temp = new TH1D(iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin);
        histsVariable.push_back(temp);
    }
}

void writeHist_fordataMC::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void writeHist_fordataMC::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    std::cout << "option in writeHist_fordataMC: " << option << "\n";

    // this part could be in a function for multiple uses
    // better structure my project so that these commen functionality go to one include dir
    std::vector<TString> optionVect;
    getOption(option, optionVect);
    // for (UInt_t i = 0; i < optionVect.size(); i++)
    // {
    // 	std::cout << optionVect[i] << "\n";
    // }
    m_genWeightSum = std::stod(optionVect[0].Data());
    std::cout << "m_genWeightSum: " << m_genWeightSum << "\n";
    //???maybe there is lose of accuracy due to convertion
    m_outputFolder = optionVect[1];
    m_processName = optionVect[2];
    m_isData = std::stoi(optionVect[3].Data());
    std::cout << "m_isData: " << m_isData << "\n";
    m_version = optionVect[4];
    std::cout << "m_verion: " << m_version << "\n";
    m_era = optionVect[5];
    std::cout << "m_era: " << m_era << "\n";

    // namespace fs = std::filesystem;
    // if ( !fs::exists((m_outputFolder+"variableHists"+ "_"+m_version+"/").Data() )){
    // 	fs::create_directory( (m_outputFolder+"variableHists"+ "_"+m_version+"/").Data());
    // }
    outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");

    std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCRc", "1tau0lCRb", "1tau0lCRa", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3", "baseline"};
    push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForVariables);

    vectorOfVariableRegions.clear();
    // histsForRegions eventCount_class{"eventCount", 2, -1.0, 1.0};
    histsForRegions<Int_t> jets_number_class{"jets_number", "n^{jet}", 7, 5.5, 12.5, jets_number};
    histsForRegions<Int_t> bjetsM_number_class{"bjetsM_num", "n^{b jet}", 8, -0.5, 7.5, bjetsM_num};
    histsForRegions<Int_t> tausT_leptonsTMVA_chargeMulti_class{"tausT_leptonsTMVA_chargeMulti", "muliplity of tau and lepton charge", 3, -1.5, 1.5, tausT_leptonsTMVA_chargeMulti};
    histsForRegions<Int_t> tausT_leptonsTopMVA_chargeMulti_class{"tausT_leptonsTopMVA_chargeMulti", "charge^{#tau}*charge^{lep}", 3, -1.5, 1.5, tausT_leptonsTopMVA_chargeMulti};
    // tausT_leptonsTopMVA_chargeMulti
    histsForRegions<Int_t> nonbjetsM_num_class{"nonbjetsM_num", "n^{non b jet}", 11, -0.5, 10.5, nonbjetsM_num};
    histsForRegions<Int_t> PV_npvsGood_class{"PV_npvsGood", "n^{vertex}", 10, 0, 50, PV_npvsGood};
    histsForRegions<Int_t> PV_npvs_class{"PV_npvs", "number of vertexes", 10, 0, 50, PV_npvs};
    // vectorOfVariableRegions.push_back();
    vectorOfVariableRegions.push_back(jets_number_class);
    vectorOfVariableRegions.push_back(bjetsM_number_class);
    vectorOfVariableRegions.push_back(tausT_leptonsTMVA_chargeMulti_class);
    vectorOfVariableRegions.push_back(tausT_leptonsTopMVA_chargeMulti_class);
    vectorOfVariableRegions.push_back(nonbjetsM_num_class);
    vectorOfVariableRegions.push_back(PV_npvsGood_class);
    vectorOfVariableRegions.push_back(PV_npvs_class);

    histsForRegions<Double_t> jets_HT_class{"jets_HT", "HT(GeV)", 10, 500, 1800, jets_HT};
    histsForRegions<Double_t> jets_bScore_class{"jets_bScore", "#sum_{i=all jets} score_{i}^{b tag}", 10, 0, 4.5, jets_bScore};
    histsForRegions<Double_t> jets_1pt_class{"jets_1pt", "p_{T}^{1st jet}(GeV)", 10, 40, 700, jets_1pt};
    histsForRegions<Double_t> jets_2pt_class{"jets_2pt", "p_{T}^{2nd jet}(GeV)", 10, 40, 600, jets_2pt};
    histsForRegions<Double_t> jets_3pt_class{"jets_3pt", "p_{T}^{3rd jet}(GeV)", 10, 40, 500, jets_3pt};
    histsForRegions<Double_t> jets_4pt_class{"jets_4pt", "p_{T}^{4th jet}(GeV)", 10, 40, 300, jets_4pt};
    histsForRegions<Double_t> jets_5pt_class{"jets_5pt", "p_{T}^{5th jet}(GeV)", 10, 40, 160, jets_5pt};
    histsForRegions<Double_t> jets_6pt_class{"jets_6pt", "p_{T}^{6th jet}(GeV)", 10, 40, 140, jets_6pt};
    histsForRegions<Double_t> jets_7pt_class{"jets_7pt", "p_{T}^{7th jet}(GeV)", 8, 25, 145, jets_7pt};
    histsForRegions<Double_t> jets_8pt_class{"jets_8pt", "p_{T}^{8th jet}(GeV)", 8, 25, 145, jets_8pt};
    histsForRegions<Double_t> jets_bScoreMultiply_class{"jets_bScoreMultiply", "#prod_{i=all jets} score_{i}^{b tag}", 10, 0, 0.3, jets_bScoreMultiply};
    histsForRegions<Double_t> jets_rationHT_4toRest_class{"jets_rationHT_4toRest", "HT^{4 leaading jets}/HT^{rest of jets}", 10, 0, 12, jets_rationHT_4toRest};
    histsForRegions<Double_t> jets_leading2invariantMass_class{"jets_leading2invariantMass", "m^{2 leading jets}", 10, 100, 1000, jets_leading2invariantMass};
    histsForRegions<Double_t> jets_transMass_class{"jets_transMass", "m_{T}^{jets}", 10, 500, 1800, jets_transMass};
    histsForRegions<Double_t> jets_avaregeDeltaR_class{"jets_average_deltaR", "average(#Delta R)^{jets}", 10, 1.2, 3.2, jets_average_deltaR};
    histsForRegions<Double_t> jets_4largestBscoreMulti_class{"jets_4largestBscoreMulti", "#sqrt{#prod_{i=4 highest} bscore_{i}^{jet}}", 10, 0, 0.3, jets_4largestBscoreMulti};
    histsForRegions<Double_t> jets_1btag_class{"jets_1btag", "btag^{1st jet}", 40, 0, 1, jets_1btag};
    histsForRegions<Double_t> jets_2btag_class{"jets_2btag", "btag^{2nd jet}", 40, 0, 1, jets_2btag};
    histsForRegions<Double_t> jets_3btag_class{"jets_3btag", " btag^{3rd jet}", 40, 0, 1, jets_3btag};
    histsForRegions<Double_t> jets_4btag_class{"jets_4btag", "btag^{4th jet}", 40, 0, 1, jets_4btag};
    histsForRegions<Double_t> jets_5btag_class{"jets_5btag", "btag^{5th jet}", 40, 0, 1, jets_5btag};
    histsForRegions<Double_t> jets_6btag_class{"jets_6btag", "6th jet btag", 40, 0, 1, jets_6btag};
    // histsForRegions<Double_t>{"", 10};

    histsForRegions<Double_t> MET_pt_class{"MET_pt", "MET", 10, 0, 500, MET_pt};
    histsForRegions<Double_t> bjetsM_HT_class{"bjetsM_HT", "HT^{b jets}", 10, 25, 700, bjetsM_HT};
    histsForRegions<Double_t> bjetsM_MHT_class{"bjetsM_MHT", "MHT^{b jets}", 10, 25, 700, bjetsM_HT};
    histsForRegions<Double_t> bjetsM_invariantMass_class{"bjetsM_invariantMass", "m^{b jets}", 10, 0, 1000, bjetsM_invariantMass};
    histsForRegions<Double_t> bjetsM_1pt_class{"bjetsM_1pt", "p_{T}^{1st bjet}", 10, 25, 600, bjetsM_1pt};
    histsForRegions<Double_t> bjetsM_2pt_class{"bjetsM_2pt", "p_{T}^{2nd bjet}", 10, 25, 500, bjetsM_2pt};
    histsForRegions<Double_t> bjetsM_minDeltaR_class{"bjetsM_minDeltaR", "min(#Delta R_{b jets})", 6, 0, 5, bjetsM_minDeltaR};
    histsForRegions<Double_t> tausT_1pt_class{"tausT_1pt", "p_{T}^{1st #tau", 10, 20, 200, tausT_1pt};
    histsForRegions<Double_t> tausT_1eta_class{"tausT_1eta", "#eta_{#tau}", 10, 0, 3, tausT_1eta};
    histsForRegions<Double_t> tausT_1phi_class{"tausT_1phi", "#phi_{#tau}", 10, 0, 3, tausT_1phi};
    histsForRegions<Double_t> tausT_HT_class{"tausT_HT", "HT_{#tau}(GeV)", 10, 25, 300, tausT_HT};
    histsForRegions<Double_t> tausT_MHT_class{"tausT_MHT", "MHT_{#tau}(GeV)", 10, 25, 300, tausT_MHT};
    histsForRegions<Double_t> tausT_leptonsT_invariantMass_class{"tausT_leptonsT_invariantMass", "m_{#tau and lep}(GeV)", 10, 0, 500, tausT_leptonsT_invariantMass};

    histsForRegions<Double_t> muonsTopMVAT_1t_class{"muonsTopMVAT_1pt", "p_{T}^{#mu}(GeV)", 10, 0, 140, muonsTopMVAT_1pt};
    histsForRegions<Double_t> elesTopMVAT_1pt_class{"elesTopMVAT_1pt", "p_{T}^{e}(GeV)", 10, 0, 140, elesTopMVAT_1pt};

    vectorOfVariableRegionsDouble.push_back(jets_1pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_2pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_3pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_4pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_5pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_6pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_HT_class);
    vectorOfVariableRegionsDouble.push_back(jets_bScore_class);
    vectorOfVariableRegionsDouble.push_back(jets_rationHT_4toRest_class);
    vectorOfVariableRegionsDouble.push_back(jets_leading2invariantMass_class);
    vectorOfVariableRegionsDouble.push_back(MET_pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_transMass_class);
    vectorOfVariableRegionsDouble.push_back(jets_avaregeDeltaR_class);
    vectorOfVariableRegionsDouble.push_back(jets_7pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_8pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_4largestBscoreMulti_class);
    vectorOfVariableRegionsDouble.push_back(bjetsM_HT_class);
    vectorOfVariableRegionsDouble.push_back(bjetsM_MHT_class);
    vectorOfVariableRegionsDouble.push_back(bjetsM_invariantMass_class);
    vectorOfVariableRegionsDouble.push_back(tausT_1pt_class);
    vectorOfVariableRegionsDouble.push_back(tausT_1eta_class);
    vectorOfVariableRegionsDouble.push_back(tausT_1phi_class);
    vectorOfVariableRegionsDouble.push_back(bjetsM_1pt_class);
    vectorOfVariableRegionsDouble.push_back(bjetsM_2pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_bScoreMultiply_class);
    vectorOfVariableRegionsDouble.push_back(tausT_HT_class);
    vectorOfVariableRegionsDouble.push_back(tausT_MHT_class);
    vectorOfVariableRegionsDouble.push_back(tausT_leptonsT_invariantMass_class);
    vectorOfVariableRegionsDouble.push_back(bjetsM_minDeltaR_class);
    // vectorOfVariableRegionsDouble.push_back();
    vectorOfVariableRegionsDouble.push_back(muonsTopMVAT_1t_class);
    vectorOfVariableRegionsDouble.push_back(elesTopMVAT_1pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_1btag_class);
    vectorOfVariableRegionsDouble.push_back(jets_2btag_class);
    vectorOfVariableRegionsDouble.push_back(jets_3btag_class);
    vectorOfVariableRegionsDouble.push_back(jets_4btag_class);
    vectorOfVariableRegionsDouble.push_back(jets_5btag_class);
    vectorOfVariableRegionsDouble.push_back(jets_6btag_class);
    // vectorOfVariableRegionsDouble.push_back();
    // vectorOfVariableRegionsDouble.push_back();

    for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegions.size(); ihistvec++)
    {
        vectorOfVariableRegions[ihistvec].initializeRegions(regionsForVariables, m_processName);
    }
    for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegionsDouble.size(); ihistvec++)
    {
        vectorOfVariableRegionsDouble[ihistvec].initializeRegions(regionsForVariables, m_processName);
    }

    //
    btagRHist = getHistogramFromFile(btagR_map[m_era], "btagR");
    std::cout << "b tag R file used: " << btagR_map[m_era] << "\n";
}

Bool_t writeHist_fordataMC::Process(Long64_t entry)
{
    fReader.SetLocalEntry(entry);

    // baseline selection
    Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0 & *bjetsM_num >= 1;
    if (!baseline)
    {
        return kFALSE;
    }
    // HLT
    // Bool_t ifHLT = kTRUE;
    // if (m_era.CompareTo("2016") == 0)
    // {
    //     if (entry == 0)
    //     {
    //         std::cout << "HLT selection for 2016\n";
    //     }
    //     ifHLT = *HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || *HLT_PFJet450 == 1; // 2016
    // }
    // else if (m_era.CompareTo("2018") == 0)
    // {
    //     if (entry == 0)
    //     {
    //         std::cout << "HLT selection for 2018";
    //     }
    //     ifHLT = *HLT_PFHT430_SixPFJet40_PFBTagCSV_1p5 == 1 || *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 == 1 || *HLT_PFHT430_SixPFJet40_PFBTagDeepCSV_1p5 == 1 || *HLT_PFHT380_SixPFJet32_DoublePFBTagDeepCSV_2p2 == 1 || *HLT_PFHT450_SixPFJet36_PFBTagDeepCSV_1p59 == 1 || *HLT_PFHT400_SixPFJet32_DoublePFBTagDeepCSV_2p94 == 1 || *HLT_PFJet500 == 1;
    // }
    // if (!(ifHLT))
    // {
    //     return kFALSE;
    // }

    Double_t btagR = calBtagR(*jets_number, btagRHist);
    Double_t basicWeight = 1.0;
    //???should not even fill data with 1.0 because it is not excactly 1 in computer
    if (!m_isData)
    {
        // basicWeight = (*EVENT_genWeight);
        // basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight);
        // basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_);
        // basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_) * (*tauT_IDSF_weight_new) * (*elesTopMVAT_weight) * (*musTopMVAT_weight);
        // basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_) * (*HLT_weight) * (*tauT_IDSF_weight_new) * (*elesTopMVAT_weight) * (*musTopMVAT_weight) * (*btagShape_weight) * btagR;
        basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_) * (*HLT_weight) * (*tauT_IDSF_weight_new) * (*elesTopMVAT_weight) * (*musTopMVAT_weight) * (*btagShape_weight) * (*btagShapeR);
    }

    Int_t lepNum = *elesTopMVAT_number + *muonsTopMVAT_number;
    // Int_t lepNum = *leptonsMVAT_number;

    // 1tau0l SR
    if (!m_isData)
    {
        // be blind for data in signal region
        Bool_t is1tau0lSR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
        Bool_t is1tau1lSR = *tausT_number == 1 && lepNum == 1 && *jets_number >= 7 && *bjetsM_num >= 2;
        fillHistsVectorMyclass(is1tau0lSR, 0, basicWeight);
        fillHistsVectorMyclass(is1tau1lSR, 6, basicWeight);
        fillHistsVector(is1tau0lSR, 0, basicWeight);
        fillHistsVector(is1tau1lSR, 6, basicWeight);
        fillHistsVector(baseline, 11, basicWeight);
    }

    // 1tau0l CR
    Bool_t is1tau0lCR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 0;
    Bool_t is1tau0lVR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num == 1;
    Bool_t is1tau0lCRc = *tausT_number == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num >= 2;
    Bool_t is1tau0lCRb = *tausT_number == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 1;
    Bool_t is1tau0lCRa = *tausT_number == 1 && lepNum == 0 && *jets_number < 8 && *bjetsM_num == 0;
    fillHistsVectorMyclass(is1tau0lCR, 1, basicWeight);
    fillHistsVectorMyclass(is1tau0lVR, 2, basicWeight);
    fillHistsVectorMyclass(is1tau0lCRc, 3, basicWeight);
    fillHistsVectorMyclass(is1tau0lCRb, 4, basicWeight);
    fillHistsVectorMyclass(is1tau0lCRa, 5, basicWeight);
    fillHistsVectorMyclass(baseline, 11, basicWeight);
    fillHistsVector(is1tau0lCR, 1, basicWeight);
    fillHistsVector(is1tau0lVR, 2, basicWeight);
    fillHistsVector(is1tau0lCRc, 3, basicWeight);
    fillHistsVector(is1tau0lCRb, 4, basicWeight);
    fillHistsVector(is1tau0lCRa, 5, basicWeight);

    // 1tau1lCR
    // Bool_t is1tau1lCR0 = *tausT_number == 1 && lepNum == 1 && *jets_number >= 7 && *bjetsM_num == 1;
    Bool_t is1tau1lCR0 = *tausT_number == 1 && lepNum == 1 && *jets_number >= 6 && *bjetsM_num == 1; // CR1 in slides
    Bool_t is1tau1lCR1 = *tausT_number == 1 && lepNum == 1 && *jets_number >= 7 && *bjetsM_num == 0;
    Bool_t is1tau1lCR2 = *tausT_number == 1 && lepNum == 1 && *jets_number == 6 && *bjetsM_num >= 2;
    // Bool_t is1tau1lCR3 = *tausT_number == 1 && lepNum == 1 && *jets_number == 6 && *bjetsM_num < 2;
    Bool_t is1tau1lCR3 = *tausT_number == 1 && lepNum == 1 && *jets_number == 6 && *bjetsM_num == 1;
    fillHistsVectorMyclass(is1tau1lCR3, 10, basicWeight);
    fillHistsVectorMyclass(is1tau1lCR0, 7, basicWeight);
    fillHistsVectorMyclass(is1tau1lCR1, 8, basicWeight);
    fillHistsVectorMyclass(is1tau1lCR2, 9, basicWeight);
    fillHistsVector(is1tau1lCR3, 10, basicWeight);
    fillHistsVector(is1tau1lCR0, 7, basicWeight);
    fillHistsVector(is1tau1lCR1, 8, basicWeight);
    fillHistsVector(is1tau1lCR2, 9, basicWeight);

    return kTRUE;
}

void writeHist_fordataMC::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
}

void writeHist_fordataMC::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    // #include "lumiAndCrossSection.h"
    Double_t processScale = 1.0;
    if (!m_isData)
    {
        std::cout << m_processName << ": " << lumiMap[m_era] << " " << crossSectionMap[m_processName] << " " << m_genWeightSum << "\n";
        processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / m_genWeightSum);
    }

    if (!m_isData)
    {

        for (UInt_t j = 0; j < eventCount_hists.size(); j++)
        {

            std::cout << j << "\n";
            eventCount_hists[j]->Scale(processScale);
            eventCount_hists[j]->Print();
        }

        for (UInt_t ihists = 0; ihists < vectorOfVariableRegions.size(); ihists++)
        {
            vectorOfVariableRegions[ihists].histsScale(processScale);
        }
        for (UInt_t ihists = 0; ihists < vectorOfVariableRegionsDouble.size(); ihists++)
        {
            vectorOfVariableRegionsDouble[ihists].histsScale(processScale);
        }
    }
    Info("Terminate", "outputFile here:%s", outputFile->GetName());
    outputFile->Write();
    outputFile->Close();
}