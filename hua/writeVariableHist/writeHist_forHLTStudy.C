#define writeHist_forHLT_cxx
// The class definition in writeHist_forHLT.h has been generated automatically
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
#include "writeHist_forHLT.h"

void writeHist_forHLT::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
    if (isRegion)
    {
        eventCount_hists[vectorIndex]->Fill(.0, weight);
    }
}

void writeHist_forHLT::fillHistsVectorMyclass(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
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
    // std::array<TString, 11> regions = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3"};
    // chain.Add(inputFile + "outTree_4.root");
    for (UInt_t i = 0; i < regions.size(); i++)
    {
        TString iHistName = regions[i] + "_" + m_processName + "_" + variable;
        TH1D *temp = new TH1D(iHistName.Data(), iHistName.Data(), binNum, minBin, maxBin);
        histsVariable.push_back(temp);
    }
}

void writeHist_forHLT::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void writeHist_forHLT::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    std::cout << "option in writeHist_forHLT: " << option << "\n";

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
    correlationHist = new TH2D("noSelection_correlation", "correlation of jet multiplicity and b jet multiplicity", 15, -0.5, 14.5, 8, -0.5, 7.5);

    // std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3", "baseline"};
    std::vector<TString>
        regionsForVariables = {
            "noSelection",
            "1tau",
            "1tau1l",
            "1tau0l",
        };
    push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForVariables);

    histsForRegions<Int_t> jets_number_class{"jets_number", "number of jets", 13, -0.5, 12.5, jets_number};
    histsForRegions<Int_t> bjetsM_number_class{"bjetsM_num", "number of b jets", 8, -0.5, 7.5, bjetsM_num};
    vectorOfVariableRegions.clear();
    vectorOfVariableRegions.push_back(jets_number_class);
    vectorOfVariableRegions.push_back(bjetsM_number_class);

    histsForRegions<Double_t> jets_1pt_class{"jets_1pt", "leading jet pt", 40, 25, 625, jets_1pt};
    histsForRegions<Double_t> jets_2pt_class{"jets_2pt", "second jet pt", 34, 25, 535, jets_2pt};
    histsForRegions<Double_t> jets_3pt_class{"jets_3pt", "third jet pt", 33, 25, 520, jets_3pt};
    histsForRegions<Double_t> jets_4pt_class{"jets_4pt", "fourth jet pt", 20, 25, 325, jets_4pt};
    histsForRegions<Double_t> jets_5pt_class{"jets_5pt", "fifth jet pt", 14, 25, 235, jets_5pt};
    histsForRegions<Double_t> jets_6pt_class{"jets_6pt", "sixth jet pt", 8, 25, 145, jets_6pt};
    histsForRegions<Double_t> jets_7pt_class{"jets_7pt", "seventh jet pt", 8, 25, 145, jets_7pt};
    histsForRegions<Double_t> jets_8pt_class{"jets_8pt", "eighth jet pt", 8, 25, 145, jets_8pt};
    histsForRegions<Double_t> jets_HT_class{"jets_HT", "HT", 40, 0, 1800, jets_HT};
    histsForRegions<Double_t> jets_bScore_class{"jets_bScore", "sum of b tag score", 30, 0, 5, jets_bScore};
    histsForRegions<Double_t> jets_rationHT_4toRest_class{"jets_rationHT_4toRest", "HT of 4 largest jet pt/HT of all jets", 30, 0, 10, jets_rationHT_4toRest};
    histsForRegions<Double_t> jets_leading2invariantMass_class{"jets_leading2invariantMass", "invariant mass of 2 largest jets", 30, 100, 1000, jets_leading2invariantMass};
    histsForRegions<Double_t> jets_transMass_class{"jets_transMass", "trans mass of jets", 30, 500, 1800, jets_transMass};
    histsForRegions<Double_t> jets_avaregeDeltaR_class{"jets_average_deltaR", "average delta R of jets", 30, 1.2, 3.2, jets_average_deltaR};
    histsForRegions<Double_t> jets_4largestBscoreMulti_class{"jets_4largestBscoreMulti", "square root of the multiplicity of 4 lorgest jets b score", 30, 0, 1, jets_4largestBscoreMulti};
    histsForRegions<Double_t> jets_bScoreMultiply_class{"jets_bScoreMultiply", "square root of b score multiplicity of jets", 30, 0, 1, jets_bScoreMultiply};
    histsForRegions<Double_t> jets_1btag_class{"jets_1btag", "leading jet btag", 40, 0, 1, jets_1btag};
    histsForRegions<Double_t> jets_2btag_class{"jets_2btag", "2rd jet btag", 40, 0, 1, jets_2btag};
    histsForRegions<Double_t> jets_3btag_class{"jets_3btag", "3rd jet btag", 40, 0, 1, jets_3btag};
    histsForRegions<Double_t> jets_4btag_class{"jets_4btag", "4th jet btag", 40, 0, 1, jets_4btag};
    histsForRegions<Double_t> jets_5btag_class{"jets_5btag", "5th jet btag", 40, 0, 1, jets_5btag};
    histsForRegions<Double_t> jets_6btag_class{"jets_6btag", "6th jet btag", 40, 0, 1, jets_6btag};
    // histsForRegions<Double_t>{"", 30};

    histsForRegions<Double_t> MET_pt_class{"MET_pt", "MET", 30, 0, 500, MET_pt};
    histsForRegions<Double_t> bjetsM_HT_class{"bjetsM_HT", "HT of b jets", 30, 25, 500, bjetsM_HT};
    histsForRegions<Double_t> bjetsM_MHT_class{"bjetsM_MHT", "MHT of b jets", 30, 25, 300, bjetsM_HT};
    histsForRegions<Double_t> bjetsM_invariantMass_class{"bjetsM_invariantMass", "invarant mass of medium b jets", 30, 25, 100, bjetsM_invariantMass};
    histsForRegions<Double_t> bjetsM_1pt_class{"bjetsM_1pt", "leading b jets pt", 30, 25, 300, bjetsM_1pt};
    histsForRegions<Double_t> bjetsM_2pt_class{"bjetsM_2pt", "second b jets pt", 30, 25, 350, bjetsM_2pt};
    histsForRegions<Double_t> bjetsM_minDeltaR_class{"bjetsM_minDeltaR", "minimum delta R of b jets", 30, 0, 4, bjetsM_minDeltaR};
    histsForRegions<Double_t> tausT_1pt_class{"tausT_1pt", "leading tau pt", 20, 20, 200, tausT_1pt};
    histsForRegions<Double_t> tausT_1eta_class{"tausT_1eta", "leading tau eta", 30, 0, 3, tausT_1eta};
    histsForRegions<Double_t> tausT_1phi_class{"tausT_1phi", "leading tau eta", 30, 0, 3, tausT_1phi};
    histsForRegions<Double_t> tausT_HT_class{"tausT_HT", "HT of tight tau", 30, 20, 300, tausT_HT};
    histsForRegions<Double_t> tausT_MHT_class{"tausT_MHT", "MHT of tight tau", 30, 25, 300, tausT_MHT};
    histsForRegions<Double_t> tausT_leptonsT_invariantMass_class{"tausT_leptonsT_invariantMass", "invariant mass of tau and lepton", 30, 0, 500, tausT_leptonsT_invariantMass};

    histsForRegions<Double_t> muonsTopMVAT_1t_class{"muonsTopMVAT_1pt", "leading muon pt", 14, 0, 140, muonsTopMVAT_1pt};
    histsForRegions<Double_t> elesTopMVAT_1pt_class{"elesTopMVAT_1pt", "leading electron pt", 14, 0, 140, elesTopMVAT_1pt};

    vectorOfVariableRegionsDouble.clear();
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
}

Bool_t writeHist_forHLT::Process(Long64_t entry)
{
    fReader.SetLocalEntry(entry);

    // baseline selection
    Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0;
    if (!baseline)
    {
        return kFALSE;
    }
    // HLT
    // if (!(*HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || *HLT_PFJet450 == 1))
    // if (!(*HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || *HLT_PFJet450 == 1))
    // if (*HLT_PFJet450 == 1)
    // {
    //     return kFALSE;
    // }
    // Bool_t PFJet450 = *HLT_PFJet450;

    Double_t basicWeight = 1.0;
    //???should not even fill data with 1.0 because it is not excactly 1 in computer
    if (!m_isData)
    {
        basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_);
    }
    // std::cout << "basicWeight=" << basicWeight << " ";

    // correlation hist
    correlationHist->Fill(*jets_number, *bjetsM_num, basicWeight);

    Int_t lepNum = *elesTopMVAT_number + *muonsTopMVAT_number;
    // Int_t lepNum = *leptonsMVAT_number;
    Bool_t is1tau = *tausT_number == 1;
    Bool_t is1tau1l = is1tau && lepNum == 1;
    Bool_t is1tau0l = is1tau && lepNum == 0;

    // 1tau0l SR
    if (!m_isData)
    {
        // be blind for data in signal region
        Bool_t is1tau0lSR = *tausT_number == 1 && lepNum == 0 && *jets_number >= 8 && *bjetsM_num >= 2;
        Bool_t is1tau1lSR = *tausT_number == 1 && lepNum == 1 && *jets_number >= 7 && *bjetsM_num >= 2;
        // fillHistsVectorMyclass(is1tau0lSR, 0, basicWeight);
        // fillHistsVector(is1tau0lSR, 0, basicWeight);
        fillHistsVectorMyclass(kTRUE, 0, basicWeight);
        fillHistsVectorMyclass(is1tau, 1, basicWeight);
        fillHistsVectorMyclass(is1tau1l, 2, basicWeight);
        fillHistsVectorMyclass(is1tau0l, 3, basicWeight);
        fillHistsVector(kTRUE, 0, basicWeight);
    }

    return kTRUE;
}

void writeHist_forHLT::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
}

void writeHist_forHLT::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    Double_t processScale = 1.0;
    if (!m_isData)
    {
        std::cout << m_processName << ": " << lumiMap[m_era] << " " << crossSectionMap[m_processName] << " " << m_genWeightSum << "\n";
        processScale = ((lumiMap[m_era] * crossSectionMap[m_processName]) / m_genWeightSum);
    }
    correlationHist->Scale(processScale);

    if (!m_isData)
    {

        for (UInt_t j = 0; j < eventCount_hists.size(); j++)
        {

            std::cout << j << "\n";
            // eventCount_hists[j]->Scale(processScale);
            eventCount_hists[j]->Print();
        }

        // for (UInt_t ihists = 0; ihists < vectorOfVariableRegionsDouble.size(); ihists++)
        // {
        //     vectorOfVariableRegionsDouble[ihists].histsScale(processScale);
        // }
    }
    Info("Terminate", "outputFile here:%s", outputFile->GetName());
    outputFile->Write();
    outputFile->Close();
}