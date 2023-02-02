#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <xgboost/c_api.h>
#include <xgboost/data.h>

// #include "../inputMap.h"

using namespace std;

#define safe_xgboost(call)                                                                             \
    {                                                                                                  \
        int err = (call);                                                                              \
        if (err != 0)                                                                                  \
        {                                                                                              \
            fprintf(stderr, "%s:%d: error in %s: %s\n", __FILE__, __LINE__, #call, XGBGetLastError()); \
            exit(1);                                                                                   \
        }                                                                                              \
    }

double TopLeptonEvaluate(std::map<string, float> &inputFeatures, string era, bool isMuon)
{
    const char *muonWeight = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin";
    std::cout << "leptonWeight: " << muonWeight << "\n";

    //

    // Float_t boosterVars[2][1][15];
    // Float_t boosterVars[2][1][13];
    float boosterVars[0][13];
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

    for (int i = 0; i < 13; i++)
    {
        std::cout << "inputFeatures: " << boosterVars[0][i] << "\n";
    }

    BoosterHandle booster;
    safe_xgboost(XGBoosterCreate(NULL, 0, &booster));
    safe_xgboost(XGBoosterLoadModel(booster, muonWeight));

    DMatrixHandle dtest;
    int nfeat = 13;
    XGDMatrixCreateFromMat(reinterpret_cast<float *>(boosterVars), 1, nfeat, NAN, &dtest);
    bst_ulong out_len;
    const float *f;
    // XGBoosterPredict(booster[0], dtest, 0, 0, &out_len, &f);
    XGBoosterPredict(booster, dtest, 0, 0, 0, &out_len, &f);

    XGDMatrixFree(dtest);
    XGBoosterFree(booster[0]);
    std::cout << "Top lepton score = " << f[0] << "\n";
    Double_t score = f[0];
    // Double_t score = (exp(f[0] * 2 * log(M_E)) - 1) / (exp(2 * log(M_E)) - 1) * 2 - 1;
    // std::cout << "Top lepton score = " << score << "\n";
    delete f;

    return score;
}

int main()
{
    std::map<TString, Float_t> inputFeatures = {
        // {"pt", Electron_pt[j]},
        // {"eta", Electron_eta[j]},
        // {"etNDauCharged", Electron_jetNDauCharged.At(j)},
        // {"miniPFRelIso_chg", Electron_miniPFRelIso_chg[j]},
        // {"miniPFRelIso_all", Electron_miniPFRelIso_all[j]},
        // {"jetPtRelv2", Electron_jetPtRelv2[j]},
        // {"jetPtRatio", jetPtRatio},
        // {"pfRelIso03_all", Electron_pfRelIso03_all[j]},
        // {"jetBTag", jetBTag},
        // {"sip3d", Electron_sip3d[j]},
        // {"dxy", Electron_dxy[j]},
        // {"dz", Electron_dz[j]},
        // {"mvaFall17V2noIso", Electron_mvaFall17V2noIso[j]}};
        {"pt", 50},
        {"eta", 1.5},
        {"jetNDauCharged", 5},
        {"miniPFRelIso_chg", 1.2},
        {"miniPFRelIso_all", 1.4},
        {"jetPtRelv2", 2.3},
        {"jetPtRatio", 2.4},
        {"pfRelIso03_all", 1.3},
        {"jetBTag", 0.5},
        {"sip3d", 0.004},
        {"dxy", 0.004},
        {"dz", 0.005},
        {"mvaFall17V2noIso", 0.8}};

    topMVAScore = TopLeptonEvaluate(inputFeatures, '2018', false);
}