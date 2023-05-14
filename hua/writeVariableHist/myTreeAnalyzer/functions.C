#include <fstream>
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

TString getEra(TString inputDir)
{
    TString era = "2016";
    if (inputDir.Contains("2016"))
    {
        era = "2016";
    }
    else if (inputDir.Contains("2017"))
    {
        era = "2017";
    }
    else if (inputDir.Contains("2018"))
    {
        era = "2018";
    }
    else
    {
        std::cout << "no valid era got!!!\n";
    }
    return era;
};

Bool_t getIsData(TString inputDir)
{
    Bool_t isData = kFALSE;
    if (inputDir.Contains("/data/"))
    {
        isData = kTRUE;
    }
    return isData;
};

void readVariableList(TString variableListCsv, std::vector<TString> &variablesName, std::vector<Float_t> &variablesForReader, std::map<TString, Float_t> &varForReaderMap, std::vector<std::variant<Int_t, Double_t>> &variablesOriginAll)
{
    std::cout << "reading varibleList: " << variableListCsv << "\n";
    std::ifstream fin(variableListCsv);
    std::string line;
    TString ivariable;
    variablesName.clear();
    variablesOriginAll.clear();
    variablesForReader.clear();
    while (getline(fin, line))
    {
        ivariable = line;
        if (line.size() > 0)
        {
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
    }
    fin.close();
};