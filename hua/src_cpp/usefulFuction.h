#ifndef USEFULFUNCTION_H
#define USEFULFUNCTION_H

#include <string>
#include <iostream>

#include "TString.h"
#include "TTree.h"
#include "TFile.h"

void getOption(TString option, std::vector<TString> &optionVec)
{
    optionVec.clear();
    while (option.Contains(":"))
    {
        TString ioption = option(0, option.First(":"));
        option.Remove(0, option.First(":") + 1);
        optionVec.push_back(ioption);
    }
}

Double_t getGenSum(TString inputFile)
{
    Double_t genWeightSumInitial = 1.0;
    TFile *m_file = new TFile(inputFile, "READ");
    // if (!isData)
    // {
    TTree *Runs = (TTree *)m_file->Get("Runs");
    Double_t igen;
    Runs->SetBranchAddress("genEventSumw", &igen);
    genWeightSumInitial = 0.0;
    for (int iEntry = 0; Runs->LoadTree(iEntry) >= 0; ++iEntry)
    {
        Runs->GetEntry(iEntry);
        genWeightSumInitial += igen;
    }
    // }
    m_file->Close();
    std::cout << "genWeightSumInitial: " << genWeightSumInitial << "\n";
    return genWeightSumInitial;
}

// template <typename T>
// T *getHistogramFromFile(TString filename, TString histname)
TH1D *getHistogramFromFile(TString filename, const char *histname)
{
    TFile *file = TFile::Open(filename);
    if (!file || file->IsZombie())
    {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return nullptr;
    }
    TH1D *hist = (TH1D *)(file->Get(histname));
    if (!hist)
    {
        std::cerr << "Error: could not retrieve histogram " << histname << " from file " << filename << std::endl;
        file->Close();
        return nullptr;
    }
    hist->SetDirectory(nullptr); // detach histogram from file to prevent it from being deleted
    file->Close();
    return hist;
}

#endif