#ifndef INPUTMAP_H
#define INPUTMAP_H

#include "TString.h"
#include <map>
#include <string>

extern std::map<TString, std::array<TString, 3>> corr_SF_map;

extern std::map<TString, std::array<TString, 4>> json_map;

extern std::map<TString, std::array<TString, 5>> jesTagMC;
extern std::map<TString, std::array<TString, 6>> jesTagData;
extern std::map<TString, TString> jesTagDataRuns;

extern std::map<TString, std::array<TString, 3>> eleScaleSmear;

extern std::map<TString, TString> GoldenJSONs;

extern std::map<TString, std::array<TString, 2>> oldFileMap;

extern std::map<TString, std::array<TString, 4>> pileUpFileMap;

extern std::map<TString, std::array<TString, 2>> TopMVALeptonMap;

extern std::map<TString, double> DeepJetL;

extern std::map<TString, double> DeepJetM;

extern std::map<TString, double> DeepJetT;

extern std::map<TString, double> DeepCSVL;

extern std::map<TString, double> DeepCSVM;

extern std::map<TString, double> DeepCSVT;

extern std::map<TString, std::array<Double_t, 2>> particleNetBMT;
extern std::map<TString, std::array<Double_t, 2>> robustParticleTransformerMT;

#endif