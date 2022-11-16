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

#endif