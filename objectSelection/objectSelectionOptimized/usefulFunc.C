#include "usefulFunc.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>

#include <TString.h>
#include "TObjString.h"
#include <TObjArray.h>

Bool_t getIsData(TString inputDir)
{
    Bool_t isData;
    if (inputDir.Contains("mc"))
    {
        isData = kFALSE;
    }
    else
    {
        isData = kTRUE;
    }
    return isData;
}

TString getEra(TString inputDir)
{
    TString era;
    if (inputDir.Contains("2017"))
    {
        era = "2017";
    }
    else if (inputDir.Contains("2018"))
    {
        era = "2018";
    }
    else if (inputDir.Contains("2016APV"))
    {
        era = "2016preVFP";
    }
    else if (inputDir.Contains("2016"))
    {
        era = "2016postVFP";
    }
    else
    {
        std::cout << "ERROR!!! get era not success!!!\n";
    }
    return era;
}

// https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM
void readJSON(const Bool_t isdata, const TString jsonInFile, std::map<Int_t, std::vector<UInt_t>> &_goodLumis)
{
    if (isdata)
    { // deal with Lumi JSONs only if reading data
        //    TString jsonInFile = GoldenJSONs[era];
        if (jsonInFile)
        {
            std::cout << "Reading JSON file " << jsonInFile << std::endl;
            std::ifstream cfgfile(jsonInFile);
            if (!cfgfile.good())
            {
                std::cout << "File " << jsonInFile << " is not a correct file - please check JSON file strings in configuration file.\nExiting." << std::endl;
                exit(8);
            }
            std::string JSON = "";
            std::string readLine;
            bool firstline = true;
            while (getline(cfgfile, readLine))
            { // read all lines from JSON file
                std::stringstream ss(readLine);
                std::string line = ss.str();
                if (!firstline && line != "}")
                    line.erase(0, 1); // erase first charater: in golden JSONs each line starts with two spaces, but we want just one separating good runs; also, save last curly bracket
                JSON.append(line);
                if (firstline)
                    firstline = false;
            }
            TString processString = JSON;
            TString segment;
            Ssiz_t from = 2;
            while (processString.Tokenize(segment, from, ", \""))
            {
                // JSON file has a layout like this: "284029": [[1, 112]], "284035": [[1, 369]], etc
                // So first tokenize with respect to the string ', "' which separates each run+lumi block
                // You get tokens in the form 284029": [[1, 112]]
                TObjArray *mapItem = segment.Tokenize("\"");
                // Now tokenize with respect to the string '"'
                // You get two-element tokens with 1st being '284029' and second being ': [[1, 112]]'
                Int_t key = (((TObjString *)(mapItem->At(0)))->String()).Atoi();
                TString value = ((TObjString *)(mapItem->At(1)))->String();
                TObjArray *values = value.Tokenize("[], :}");
                // Finally tokenize the second element to remove everything which is not an integer
                // You get the good lumi sections
                // std::vector<Int_t> valueVec;
                std::vector<UInt_t> valueVec;
                for (Int_t i = 0; i < values->GetEntries(); i++)
                {
                    valueVec.push_back((((TObjString *)(values->At(i)))->String()).Atoi());
                }
                _goodLumis[key] = valueVec;
            }
        } // end if JSON file
    }
}

Double_t TopLeptonEvaluate(std::map<TString, Float_t> &inputFeatures, const BoosterHandle &booster)
{

    float boosterVars[1][13];
    boosterVars[0][0] = inputFeatures["pt"];
    boosterVars[0][1] = inputFeatures["eta"];
    boosterVars[0][2] = inputFeatures["jetNDauCharged"];
    boosterVars[0][3] = inputFeatures["miniPFRelIso_chg"];
    boosterVars[0][4] = inputFeatures["miniPFRelIso_all"] - inputFeatures["miniPFRelIso_chg"];
    boosterVars[0][5] = inputFeatures["jetPtRelv2"];
    boosterVars[0][6] = inputFeatures["jetPtRatio"];
    boosterVars[0][7] = inputFeatures["pfRelIso03_all"];
    boosterVars[0][8] = inputFeatures["jetBTag"];
    boosterVars[0][9] = inputFeatures["sip3d"];
    boosterVars[0][10] = TMath::Log(TMath::Abs(inputFeatures["dxy"]));
    boosterVars[0][11] = TMath::Log(TMath::Abs(inputFeatures["dz"]));
    boosterVars[0][12] = inputFeatures["mvaFall17V2noIso"];

    // for (Int_t i = 0; i < 13; i++)
    // {
    //     std::cout << "inputFeatures: " << boosterVars[0][i] << "\n";
    // }

    // BoosterHandle booster;
    // XGBoosterCreate(NULL, 0, &booster);
    // XGBoosterLoadModel(booster, muonWeight.Data());

    DMatrixHandle dtest;
    int nfeat = 13;
    XGDMatrixCreateFromMat(reinterpret_cast<float *>(boosterVars[0]), 1, nfeat, NAN, &dtest);
    bst_ulong out_len;
    const float *f;
    XGBoosterPredict(booster, dtest, 0, 0, &out_len, &f);
    // XGBoosterPredict(booster[0], dtest, 0, 0, 0, &out_len, &f);
    XGDMatrixFree(dtest);
    // XGBoosterFree(booster);
    // std::cout << "Top lepton score = " << f[0] << "\n";
    Double_t score = f[0];

    return score;
}
