#include "functions.h"

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
