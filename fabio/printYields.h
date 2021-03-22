#include <map>

using namespace std;

double LUMI2016 = 35900.0;

map<string, float> xsec = {
    
//signal
{"tttt", 0.01197},

//ttbar background    
{"ttbar-FH", 373.0},
{"ttbar-SL", 367.0},
{"ttbar-DL", 90.6},
{"ttbar-incl", 830.7},
    
//tt+X background
{"ttG-SL", 5.058},
{"ttG-DL", 1.506},
{"ttW+jets", 0.2014},
//{"ttZ+jets", 0.6559},
{"ttH", 0.3372},

//diboson background
{"WZ", 2.343},
{"WW", 63.21},
{"ZZ", 1.016},
{"WG+jets", 1.269},
{"ZG+jets", 0.1319},

//triboson background
{"WWW", 0.2086},
{"WWZ", 0.1651},
//{"WWG", 0.2147},
{"ZZZ", 0.01398},
{"WZZ", 0.05565},
{"WZG", 0.04123},
{"WGG", 1.819},
{"ZGG+jets", 0.3717},

//W+jets background
//{"W+jets", 50300.0},

//DY background
{"DY", 1983.0},

//single-top backgroun
{"tZq", 0.07358},
{"tW_antitop", 38.06},
{"tW_top", 38.09},
//{"tG+jets", 2.967},
{"tHW", 0.1467},
{"THq", 0.8816},

//Higgs background
{"VHToNonbb", 2.137},
//{"ZHToTauTau", 0.7524},
{"ZHTobb", 0.07523},
//{"GluGluHTo4L", 2.999},
{"GluGluHTobb", 32.10},
{"GluGluHToGG", 31.98}, // cross section for ggH(bb) and ggH(gammgamma) comparable, how is this possible?
{"GluGluHToMuMu", 29.99}, // same holds for ggH(mumu)
{"GluGluHToTauTau", 30.52}, // same holds for ggH(tautau)
{"GluGluHTo2L2Nu", 30.52}, // same
{"GluGluHToLNuqq", 29.99},
{"VBFHTo2L2Nu", 3.769},
{"VBFHToMuMu", 0.000823}, //there's no such a big difference in xsec between ggH(mumu) and VBF(mumu) production mechanisms 
{"VBFHToGG", 3.992},

};

map <string, TH1F> scaledYield;

TH1F tttt, ttbar, ttbar_FH, ttbar_SL, ttbar_DL, ttbar_incl, ttX, VV, VVV, WJets, DY, ST, H, total_bkg;
