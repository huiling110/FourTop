#define writeHist_forBtagRCal_cxx
// The class definition in writeHist_forBtagRCal.h has been generated automatically
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
#include "writeHist_forBtagRCal.h"

void writeHist_forBtagRCal::fillHistsVector(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
    if (isRegion)
    {
        eventCount_hists[vectorIndex]->Fill(.0, weight);
    }
}

void writeHist_forBtagRCal::fillHistsVectorMyclass(Bool_t isRegion, UInt_t vectorIndex, Double_t weight)
{
    if (isRegion)
    {
        for (UInt_t i = 0; i < vectorOfVariableRegions.size(); i++)
        {
            vectorOfVariableRegions[i].fillHistVec(vectorIndex, weight);
        }
        // for (UInt_t i = 0; i < vectorOfVariableRegionsDouble.size(); i++)
        // {
        // 	vectorOfVariableRegionsDouble[i].fillHistVec(vectorIndex, weight);
        // }
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

void writeHist_forBtagRCal::Begin(TTree * /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
}

void writeHist_forBtagRCal::SlaveBegin(TTree * /*tree*/)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).

    TString option = GetOption();
    std::cout << "option in writeHist_forBtagRCal: " << option << "\n";

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
    outputFile = new TFile(m_outputFolder + "variableHists" + "_" + m_version + "/" + m_processName + ".root", "RECREATE");

    std::vector<TString> regionsForVariables = {"1tauNoB", "1tauNoBTagWeight", "1tau1lNoB", "1tau1lNoBBtagWeight", "1tau0lNoB", "1tau0lNoBBtagWeight"};
    push_backHists("eventCount", 2, -1, 1, eventCount_hists, m_processName, regionsForVariables);

    vectorOfVariableRegions.clear();
    // histsForRegions eventCount_class{"eventCount", 2, -1.0, 1.0};
    histsForRegions<Int_t> jets_number_class{"jets_number", "number of jets", 6, 6, 12, jets_number};
    // vectorOfVariableRegions.push_back();
    vectorOfVariableRegions.push_back(jets_number_class);
    // vectorOfVariableRegions.push_back(nonbjetsM_num_class);

    for (UInt_t ihistvec = 0; ihistvec < vectorOfVariableRegions.size(); ihistvec++)
    {
        vectorOfVariableRegions[ihistvec].initializeRegions(regionsForVariables, m_processName);
    }
}

Bool_t writeHist_forBtagRCal::Process(Long64_t entry)
{
    fReader.SetLocalEntry(entry);

    Double_t basicWeight = 1.0;
    if (!m_isData)
    {
        basicWeight = (*EVENT_prefireWeight) * (*EVENT_genWeight) * (*PUweight_) * (*HLT_weight) * (*tauT_IDSF_weight_new) * (*elesTopMVAT_weight) * (*musTopMVAT_weight);
    }

    Bool_t baselineNoB = *jets_number >= 6 && *jets_6pt > 40.0 && *jets_HT > 500.0;
    if (!baselineNoB)
    {
        return kFALSE;
    }

    if (!m_isData)
    {
        // be blind for data in signal region
        // Bool_t isBTagRegion = *tausT_number >= 1 && *jets_number >= 6;
        Bool_t isBTagRegion = *tausT_number == 1 && *jets_number >= 6;
        // Bool_t SR1tau1lNoB = (*tausT_number >= 1) && (*elesTopMVAT_number + *muonsTopMVAT_number == 1) && (*jets_number >= 6);
        // Bool_t SR1tau0lNoB = (*tausT_number >= 1) && (*elesTopMVAT_number + *muonsTopMVAT_number == 0) && (*jets_number >= 6);
        Bool_t SR1tau1lNoB = (*tausT_number == 1) && (*elesTopMVAT_number + *muonsTopMVAT_number == 1) && (*jets_number >= 6);
        Bool_t SR1tau0lNoB = (*tausT_number == 1) && (*elesTopMVAT_number + *muonsTopMVAT_number == 0) && (*jets_number >= 6);
        fillHistsVectorMyclass(isBTagRegion, 0, basicWeight);
        fillHistsVectorMyclass(isBTagRegion, 1, basicWeight * (*btagShape_weight));
        fillHistsVectorMyclass(SR1tau1lNoB, 2, basicWeight);
        fillHistsVectorMyclass(SR1tau1lNoB, 3, basicWeight * (*btagShape_weight));
        fillHistsVectorMyclass(SR1tau0lNoB, 4, basicWeight);
        fillHistsVectorMyclass(SR1tau0lNoB, 5, basicWeight * (*btagShape_weight));
        fillHistsVector(isBTagRegion, 0, basicWeight);
        fillHistsVector(isBTagRegion, 1, basicWeight * (*btagShape_weight));
        fillHistsVector(SR1tau1lNoB, 2, basicWeight);
        fillHistsVector(SR1tau1lNoB, 3, basicWeight * (*btagShape_weight));
        fillHistsVector(SR1tau0lNoB, 4, basicWeight);
        fillHistsVector(SR1tau0lNoB, 5, basicWeight * (*btagShape_weight));
    }

    return kTRUE;
}

void writeHist_forBtagRCal::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
}

void writeHist_forBtagRCal::Terminate()
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
            vectorOfVariableRegions[ihists].histsPrint();
        }
    }
    Info("Terminate", "outputFile here:%s", outputFile->GetName());
    outputFile->Write();
    outputFile->Close();
}