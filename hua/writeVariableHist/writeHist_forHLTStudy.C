#define writeHist_forHLTStudy_cxx
// The class definition in writeHist_forHLTStudy.h has been generated automatically
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
#include "writeHist_forHLTStudy.h"

void writeHist_forHLTStudy::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
    if (isRegion)
    {
        eventCount_hists[vectorIndex]->Fill(.0, weight);
    }
}

void writeHist_forHLTStudy::fillHistsVectorMyclass(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
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

void writeHist_forHLTStudy::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void writeHist_forHLTStudy::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    std::cout << "option in writeHist_forHLTStudy: " << option << "\n";

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

    // std::vector<TString> regionsForVariables = {"1tau0lSR", "1tau0lCR", "1tau0lVR", "1tau0lCR2", "1tau0lCR3", "1tau0lCR4", "1tau1lSR", "1tau1lCR0", "1tau1lCR1", "1tau1lCR2", "1tau1lCR3", "baseline"};
    std::vector<TString>
        regionsForVariables = {
            "baseline1Muon",
            "baseline1MuonAndHLT",
            "baseline",       // for MC true efficiency
            "baselineAndHLT", // for MC true efficiency
        };
    push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForVariables);

    histsForRegions<Int_t> jets_number_class{"jets_number", "number of jets", 13, -0.5, 12.5, jets_number};
    histsForRegions<Int_t> bjetsM_number_class{"bjetsM_num", "number of b jets", 8, -0.5, 7.5, bjetsM_num};
    vectorOfVariableRegions.clear();
    vectorOfVariableRegions.push_back(jets_number_class);
    vectorOfVariableRegions.push_back(bjetsM_number_class);

    histsForRegions<Double_t> jets_1pt_class{"jets_1pt", "leading jet pt", 40, 25, 625, jets_1pt};
    histsForRegions<Double_t> jets_6pt_class{"jets_6pt", "sixth jet pt", 8, 25, 145, jets_6pt};
    histsForRegions<Double_t> jets_HT_class{"jets_HT", "HT", 40, 500, 2500, jets_HT};
    // histsForRegions<Double_t>{"", 30};

    vectorOfVariableRegionsDouble.clear();
    vectorOfVariableRegionsDouble.push_back(jets_1pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_6pt_class);
    vectorOfVariableRegionsDouble.push_back(jets_HT_class);
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

    // 2D for SF
    Double_t xbins[] = {500, 550, 600, 750, 800, 900, 1000, 1200, 1400, 1800, 2500};
    Double_t ybins[] = {40, 55, 70, 85, 115, 145};
    b1HT6pt_de = new TH2D("baseline1Muon1b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b1HT6pt_nu = new TH2D("baseline1MuonAndHLT1b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b2HT6pt_de = new TH2D("baseline1Muon2b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b2HT6pt_nu = new TH2D("baseline1MuonAndHLT2b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b3HT6pt_de = new TH2D("baseline1Muon3b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
    b3HT6pt_nu = new TH2D("baseline1MuonAndHLT3b_" + m_processName + "_jetsHTAnd6pt", "HT:6th jet pt", sizeof(xbins) / sizeof(Double_t) - 1, xbins, sizeof(ybins) / sizeof(Double_t) - 1, ybins);
}

Bool_t writeHist_forHLTStudy::Process(Long64_t entry)
{
    fReader.SetLocalEntry(entry);

    // baseline selection
    // Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0;
    // Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0 && *bjetsM_num >= 2;
    Bool_t baseline = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0 && *bjetsM_num >= 1;
    if (!baseline)
    {
        return kFALSE;
    }

    // Bool_t is1muon = *muonsTopMVAT_number >= 1;
    // Bool_t is1muon = *HLT_IsoMu24 == 1; // 2016
    // Bool_t is1muon = *HLT_IsoMu27 == 1;                                                                                            // 2017 and 2018
    Bool_t is1muon = *HLT_IsoMu24 == 1 && *muonsTopMVAT_number == 1 && *muonsTopMVAT_1pt >= 30.;                                   // 2016
    Bool_t ifHLT = *HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1 || *HLT_PFJet450 == 1; // 2016
    // Bool_t ifHLT = *HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFHT400_SixJet30_DoubleBTagCSV_p056 == 1; // 2016
    // Bool_t ifHLT = *HLT_PFHT450_SixJet40_BTagCSV_p056 == 1 || *HLT_PFJet450 == 1; // 2016

    Double_t basicWeight = 1.0;
    //???should not even fill data with 1.0 because it is not excactly 1 in computer
    // std::cout << "basicWeight=" << basicWeight << " ";
    if (!m_isData)
    {
        basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_);
    }

    fillHistsVectorMyclass(baseline && is1muon, 0, basicWeight);
    fillHistsVectorMyclass(baseline && is1muon && ifHLT, 1, basicWeight);
    fillHistsVectorMyclass(baseline, 2, basicWeight);
    fillHistsVectorMyclass(baseline && ifHLT, 3, basicWeight);

    fillHistsVector(baseline && is1muon, 0, basicWeight);
    fillHistsVector(baseline && is1muon && ifHLT, 1, basicWeight);
    fillHistsVector(baseline, 2, basicWeight);
    fillHistsVector(baseline && ifHLT, 3, basicWeight);

    // 2D
    if (baseline && is1muon)
    {
        if (*bjetsM_num == 1)
        {
            b1HT6pt_de->Fill(*jets_HT, *jets_6pt);
        }
        if (*bjetsM_num == 2)
        {
            b2HT6pt_de->Fill(*jets_HT, *jets_6pt);
        }
        if (*bjetsM_num >= 3 && *bjetsM_num <= 7)
        {
            b3HT6pt_de->Fill(*jets_HT, *jets_6pt);
        }
    }
    if (baseline && is1muon && ifHLT)
    {
        if (*bjetsM_num == 1)
        {
            b1HT6pt_nu->Fill(*jets_HT, *jets_6pt);
        }
        if (*bjetsM_num == 2)
        {
            b2HT6pt_nu->Fill(*jets_HT, *jets_6pt);
        }
        if (*bjetsM_num >= 3 && *bjetsM_num <= 7)
        {
            b3HT6pt_nu->Fill(*jets_HT, *jets_6pt);
        }
    }

    return kTRUE;
}

void writeHist_forHLTStudy::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
}

void writeHist_forHLTStudy::Terminate()
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

    if (!m_isData)
    {

        for (UInt_t j = 0; j < eventCount_hists.size(); j++)
        {

            std::cout << j << "\n";
            eventCount_hists[j]->Scale(processScale);
            eventCount_hists[j]->Print();
        }

        for (UInt_t ihists = 0; ihists < vectorOfVariableRegionsDouble.size(); ihists++)
        {
            vectorOfVariableRegionsDouble[ihists].histsScale(processScale);
        }

        for (UInt_t ihists = 0; ihists < vectorOfVariableRegions.size(); ihists++)
        {
            vectorOfVariableRegions[ihists].histsScale(processScale);
        }

        b1HT6pt_de->Scale(processScale);
        b1HT6pt_nu->Scale(processScale);
        b2HT6pt_de->Scale(processScale);
        b2HT6pt_nu->Scale(processScale);
        b3HT6pt_de->Scale(processScale);
        b3HT6pt_nu->Scale(processScale);
    }
    Info("Terminate", "outputFile here:%s", outputFile->GetName());
    outputFile->Write();
    outputFile->Close();
}