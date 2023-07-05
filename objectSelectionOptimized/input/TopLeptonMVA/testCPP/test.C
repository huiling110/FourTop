#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <cmath>

// #include </cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/include/xgboost/c_api.h>
#include </cvmfs/cms.cern.ch/slc7_amd64_gcc700/external/py2-xgboost/0.80-ikaegh/lib/python2.7/site-packages/xgboost/include/xgboost/c_api.h>
// #include </cvmfs/cms.cern.ch/slc7_amd64_gcc900/external/xgboost/1.3.3/include/xgboost/data.h>

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

double TopLeptonEvaluate(std::map<std::string, float> &inputFeatures, bool isMuon)
{
    BoosterHandle booster;
    const char *muonWeight = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights_new/el_TOPUL18_XGB.weights.bin";
    // const char *muonWeight = "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/objectSelection/TopLeptonMVA/mvaWeights/el_TOPUL18_XGB.weights.bin";
    // std::cout << "leptonWeight: " << muonWeight << "\n";

    //

    // Float_t boosterVars[2][1][15];
    // Float_t boosterVars[2][1][13];
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
    boosterVars[0][10] = std::log(std::abs(inputFeatures["dxy"]));
    boosterVars[0][11] = std::log(std::abs(inputFeatures["dz"]));
    boosterVars[0][12] = inputFeatures["mvaFall17V2noIso"];

    for (int i = 0; i < 13; i++)
    {
        std::cout << "inputFeatures: " << boosterVars[0][i] << "\n";
    }

    safe_xgboost(XGBoosterCreate(NULL, 0, &booster));
    safe_xgboost(XGBoosterLoadModel(booster, muonWeight));

    DMatrixHandle dtest;
    int nfeat = 13;
    // XGDMatrixCreateFromMat(reinterpret_cast<float *>(boosterVars), 1, nfeat, NAN, &dtest);
    // XGDMatrixCreateFromMat((float *)(boosterVars), 1, nfeat, NAN, &dtest);
    safe_xgboost(XGDMatrixCreateFromMat((float *)(boosterVars), 1, nfeat, -1, &dtest));

    bst_ulong out_len;
    const float *f;
    safe_xgboost(XGBoosterPredict(booster, dtest, 0, 0, &out_len, &f));
    // XGBoosterPredict(booster, dtest, 0, 0, 0, &out_len, &f);

    XGDMatrixFree(dtest);
    XGBoosterFree(booster);
    std::cout << "Top lepton score = " << f[0] << "\n";
    double score = f[0];
    // Double_t score = (exp(f[0] * 2 * log(M_E)) - 1) / (exp(2 * log(M_E)) - 1) * 2 - 1;
    std::cout << "Top lepton score = " << score << "\n";
    delete f;

    return score;
}

int main()
{
    std::map<std::string, float> inputFeatures = {
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

    TopLeptonEvaluate(inputFeatures, false);
}