#include <fstream>
#include "../include/functions.h"

//put in myLib
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

// void histRegionVectFill(std::vector<histForRegionsBase*>& histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData ){
void histRegionVectFill(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Bool_t isRegion, TString region, Double_t weight, Bool_t isData)
{
    // for (UInt_t i = 0; i < histForRegion_vec.size(); i++)
    // {
    //     histForRegion_vec[i]->fillHistVec(region, weight, isRegion, isData);
    // }
    for (auto &obj : histForRegion_vec)
    {
        obj->fillHistVec(region, weight, isRegion, isData);
    }
}

void histRegionsVectSetDir(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, TFile *&file)
{
    for (auto &obj : histForRegion_vec)
    {
        obj->setDir(file);
    }
}
void histRegionsVectScale(std::vector<std::shared_ptr<histForRegionsBase>> &histForRegion_vec, Double_t scale)
{
    for (auto &obj : histForRegion_vec)
    {
        obj->scale(scale);
    }
}

void fillDeNu(Bool_t ifPass, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight)
{
    de->Fill(var, weight);
    if (ifPass)
    {
        nu->Fill(var, weight);
    }
}
void fillDeNu(Bool_t ifPassNu, Bool_t ifPassDe, TH1D *&de, TH1D *&nu, Double_t var, Double_t weight)
{
    if (ifPassDe)
    {
        de->Fill(var, weight);
    }
    if (ifPassNu&&ifPassDe)
    {
        nu->Fill(var, weight);
    }
}
void fillDeNu(Bool_t ifPass, TH2D *&de, TH2D *&nu, Double_t varX, Double_t varY, Double_t weight, const Bool_t isData)
{
    if( !isData){
        de->Fill(varX, varY, weight);
        if (ifPass)
        {
            nu->Fill(varX, varY, weight);
        }
    }else{
        de->Fill(varX, varY);
        if (ifPass)
        {
            nu->Fill(varX, varY);
        }
    }
}