#include <map>

using namespace std;

double LUMI2016 = 35900.0;

map<string, float> xsec = {
//4tops signal
{"tttt", 0.01197},
    
//ttbar background                                                                                                                                                                              
{"ttbar-FH", 373.0},
{"ttbar-SL", 367.0},
{"ttbar-DL", 90.6},

//QCD background                                                                                                                                                                                                                                                                                            
{"QCD_HT300to500", 347700.0},
{"QCD_HT500to700", 32100.0},
{"QCD_HT700to1000", 6831.0},
{"QCD_HT1000to1500", 1207.0},
{"QCD_HT1500to2000", 119.9},
{"QCD_HT2000toInf", 25.24},

//tt+X background                                                                                                                                                                                                                                                                                                    
{"ttW+jets", 0.2014},
{"ttZ+jets", 0.6559},
{"ttG+jets", 3.697},
{"ttH", 0.3372},

{"data_singleMuon_eraB_0", 1.0},
{"data_singleMuon_eraB_1", 1.0},
{"data_singleMuon_eraC_0", 1.0},
{"data_singleMuon_eraD_0", 1.0},
{"data_singleMuon_eraE_0", 1.0},
{"data_singleMuon_eraF_0", 1.0},
{"data_singleMuon_eraH_0", 1.0},
{"data_singleMuon_eraH_1", 1.0},
    
};
