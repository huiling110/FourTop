#include <map>

using namespace std;

string MUOSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/fabio/UltraLegacy/scale_factors/muons/";
map<string, string> MUOSF_files = { //MAP OF INPUT MUO SCALE FACTOR FILES                                                                                                                                                            

    {"UL2016_preVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_preVFP_ID.root"},
    {"UL2016_postVFP", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2016_UL_postVFP_ID.root"},
    {"UL2017", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2017_UL_ID.root"},
    {"UL2018", MUOSF_dir + "Efficiencies_muon_generalTracks_Z_Run2018_UL_ID.root"},

};

string EGammaSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/fabio/UltraLegacy/scale_factors/electrons/";
map<string, string> EGammaSF_files = { //MAP OF INPUT EGamma SCALE FACTOR FILES                                                                                                                                                            

    {"UL2016_preVFP", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_preVFP_EGM2D.root"},
    {"UL2016_postVFP", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_postVFP_EGM2D.root"},
    {"UL2017", EGammaSF_dir + "egammaEffi.txt_EGM2D_MVA90noIso_UL17.root"},
    {"UL2018", EGammaSF_dir + "egammaEffi.txt_Ele_wp90noiso_EGM2D.root"},

};

string BTVSF_dir = "/publicfs/cms/user/fabioiemmi/CMSSW_10_6_27/src/FourTop/fabio/UltraLegacy/scale_factors/btagging/";
map<string, string> BTVSF_files = { //MAP OF INPUT BTV SCALE FACTOR FILES

    {"UL2016_preVFP", BTVSF_dir + "reshaping_deepJet_106XUL16preVFP_v2_dropLines.csv"},
    {"UL2016_postVFP", BTVSF_dir + "reshaping_deepJet_106XUL16postVFP_v3_dropLines.csv"},
    {"UL2017", BTVSF_dir + "reshaping_deepJet_106XUL17_v3_dropLines.csv"},
    {"UL2018", BTVSF_dir + "reshaping_deepJet_106XUL18_v2_dropLines.csv"},

};

std::map<TString, double> DeepJetM = { //std::map of medium WPs for DeepJet

    {"UL2016_postVFP", 0.2489},
    {"UL2016_preVFP", 0.2598},
    {"UL2017", 0.3040},
    {"UL2018", 0.2783},

};

map<string, map<string, string>> file = { //MAP OF INPUT FILES

    {"UL2016_preVFP", 
     {   //signal
         
         {"tttt", "tttt"}, //broken

         //ttbar background    
         {"ttbar-FH", "ttbar_0l"},//broken
         {"ttbar-SL", "ttbar_1l"},
         {"ttbar-DL", "ttbar_2l"},

         //QCD background    
         {"QCD_HT200to300", "qcd_200to300"},
         {"QCD_HT300to500", "qcd_300to500"},
         {"QCD_HT500to700", "qcd_500to700"},
         {"QCD_HT700to1000", "qcd_700to1000"},
         {"QCD_HT1000to1500", "qcd_1000to1500"},
         {"QCD_HT1500to2000", "qcd_1500to2000"},
         {"QCD_HT2000toInf", "qcd_2000toInf"},

         //tt+X background   
         {"ttW+jets", "ttW"}, //broken   
         {"ttZ+jets", "ttZ"}, //broken   
         {"ttG+jets", "ttG"}, //broken   
         {"ttH_bb", "ttH_bb"}, //broken  
         {"ttH_nonbb", "ttH_nonbb"}, //broken    

         //single-top background 
         {"st_tchan", "st_tchan"},
         {"st_antitchan", "st_antitchan"},
         {"st_tW_top", "st_tW_top"},
         {"st_tW_antitop", "st_tW_antitop"},
         {"st_tZq", "st_tZq"},
         
     }
    }, //UL2016_preVFP

    {"UL2016_postVFP", 
     {   //signal
         
         {"tttt", "tttt"}, //broken

         //ttbar background    
         {"ttbar-FH", "ttbar_0l"},//broken
         {"ttbar-SL", "ttbar_1l"},
         {"ttbar-DL", "ttbar_2l"},

         //QCD background    
         {"QCD_HT200to300", "qcd_200to300"},
         {"QCD_HT300to500", "qcd_300to500"},
         {"QCD_HT500to700", "qcd_500to700"},
         {"QCD_HT700to1000", "qcd_700to1000"},
         {"QCD_HT1000to1500", "qcd_1000to1500"},
         {"QCD_HT1500to2000", "qcd_1500to2000"},
         {"QCD_HT2000toInf", "qcd_2000toInf"},

         //tt+X background   
         {"ttW+jets", "ttW"}, //broken   
         {"ttZ+jets", "ttZ"}, //broken   
         {"ttG+jets", "ttG"}, //broken   
         {"ttH_bb", "ttH_bb"}, //broken  
         {"ttH_nonbb", "ttH_nonbb"}, //broken    

         //single-top background 
         {"st_tchan", "st_tchan"},
         {"st_antitchan", "st_antitchan"},
         {"st_tW_top", "st_tW_top"},
         {"st_tW_antitop", "st_tW_antitop"},
         {"st_tZq", "st_tZq"},

     }
    }, //UL2016_postVFP

};

void writeTEfficiency(TH1F* hBef, TH1F* hAFt, TString name);
void writeTEfficiency2D(TH2F* hBef, TH2F* hAFt, TString name);
