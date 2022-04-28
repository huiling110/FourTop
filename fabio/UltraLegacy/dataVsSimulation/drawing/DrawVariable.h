#include <map>

using namespace std;

#include <map>

using namespace std;

map <string, double> lumi = {

    {"UL2016_preVFP", 19500.0},
    {"UL2016_postVFP", 16800.0},
    {"UL2017", 41480.0},
    {"UL2018", 59830.0},

};

map<string, map<string, string>> file = { //MAP OF INPUT FILES

    {"UL2016_preVFP", 
     {   //signal
         
         {"tttt", "tttt"},
         
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
         {"ttW+jets", "ttW"},   
         {"ttZ+jets", "ttZ"},   
         {"ttG+jets", "ttG"},   
         {"ttH_bb", "ttH_bb"},  
         {"ttH_nonbb", "ttH_nonbb"},    

         //single-top background 
         {"st_tchan", "st_tchan"},
         {"st_antitchan", "st_antitchan"},
         {"st_tW_top", "st_tW_top"},
         {"st_tW_antitop", "st_tW_antitop"},
         {"st_tZq", "st_tZq"},
         
         {"data_JetHT_eraB_v1", "jetHT_2016B_v1"},
         {"data_JetHT_eraB_v2", "jetHT_2016B_v2"},
         {"data_JetHT_eraC", "jetHT_2016C"},    
         {"data_JetHT_eraD", "jetHT_2016D"},
         {"data_JetHT_eraE", "jetHT_2016E"},
         {"data_JetHT_eraF_hipm", "jetHT_2016F_hipm"},
         
     }
    }, //UL2016_preVFP

    {"UL2016_postVFP", 
     {   //signal
         
         {"tttt", "tttt"},

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
         {"ttW+jets", "ttW"},   
         {"ttZ+jets", "ttZ"},   
         {"ttG+jets", "ttG"},   
         {"ttH_bb", "ttH_bb"},  
         {"ttH_nonbb", "ttH_nonbb"},    

         //single-top background 
         {"st_tchan", "st_tchan"},
         {"st_antitchan", "st_antitchan"},
         {"st_tW_top", "st_tW_top"},
         {"st_tW_antitop", "st_tW_antitop"},
         {"st_tZq", "st_tZq"},

         {"data_JetHT_eraF", "jetHT_2016F"},    
         {"data_JetHT_eraG", "jetHT_2016G"},    
         {"data_JetHT_eraH", "jetHT_2016H"},    
        
     }
    }, //UL2016_postVFP

};

map<string, map<string,float>> xsec = {
    
    {"UL2016_preVFP", 
     {   //signal
         
         {"tttt", 0.01197}, 

         //ttbar background    
         {"ttbar-FH", 377.96},
         {"ttbar-SL", 365.34},
         {"ttbar-DL", 88.29},

         //QCD background    
         {"QCD_HT200to300", 1560000.0},
         {"QCD_HT300to500", 323400.0},
         {"QCD_HT500to700", 30140.0},
         {"QCD_HT700to1000", 6310.0},
         {"QCD_HT1000to1500", 1118.0},
         {"QCD_HT1500to2000", 108.9},
         {"QCD_HT2000toInf", 20.2},

         //tt+X background   
         {"ttW+jets", 0.4611},    
         {"ttZ+jets", 0.5407},    
         {"ttG+jets", 3.757},    
         {"ttH_bb", 0.2897},   
         {"ttH_nonbb", 0.209},     

         //single-top background 
         {"st_tchan", 136.02},
         {"st_antitchan", 80.95},
         {"st_tW_top", 34.91}, //McM gives 115, must be wrong???
         {"st_tW_antitop", 34.91},
         {"st_tZq", 0.0758},

         {"data_JetHT_eraB_v1", 1.0},
         {"data_JetHT_eraB_v2", 1.0},
         {"data_JetHT_eraC", 1.0},    
         {"data_JetHT_eraD", 1.0},
         {"data_JetHT_eraE", 1.0},
         {"data_JetHT_eraF_hipm", 1.0},
         
     }
    }, //UL2016_preVFP

    {"UL2016_postVFP", 
     {   //signal
         
         {"tttt", 0.01197}, 

         //ttbar background    
         {"ttbar-FH", 377.96},
         {"ttbar-SL", 365.34},
         {"ttbar-DL", 88.29},

         //QCD background    
         {"QCD_HT200to300", 1560000.0},
         {"QCD_HT300to500", 323400.0},
         {"QCD_HT500to700", 30140.0},
         {"QCD_HT700to1000", 6310.0},
         {"QCD_HT1000to1500", 1118.0},
         {"QCD_HT1500to2000", 108.9},
         {"QCD_HT2000toInf", 20.2},

         //tt+X background   
         {"ttW+jets", 0.4611},    
         {"ttZ+jets", 0.5407},    
         {"ttG+jets", 3.757},    
         {"ttH_bb", 0.2897},   
         {"ttH_nonbb", 0.209},     

         //single-top background 
         {"st_tchan", 136.02},
         {"st_antitchan", 80.95},
         {"st_tW_top", 34.91}, //McM gives 115, must be wrong???
         {"st_tW_antitop", 34.91},
         {"st_tZq", 0.0758},

         {"data_singleMuon_eraF", 1.0},    
         {"data_singleMuon_eraG", 1.0},    
         {"data_singleMuon_eraH", 1.0},    
        
     }
    }, //UL2016_postVFP

    {"UL2018", 
     {   //signal
         
         {"tttt", 0.01197}, 

         //ttbar background    
         {"ttbar-FH", 377.96},
         {"ttbar-SL", 365.34},
         {"ttbar-DL", 88.29},

         //QCD background    
         {"QCD_HT200to300", 1560000.0},
         {"QCD_HT300to500", 323400.0},
         {"QCD_HT500to700", 30140.0},
         {"QCD_HT700to1000", 6310.0},
         {"QCD_HT1000to1500", 1118.0},
         {"QCD_HT1500to2000", 108.9},
         {"QCD_HT2000toInf", 20.2},

         //tt+X background   
         {"ttW+jets", 0.4611},    
         {"ttZ+jets", 0.5407},    
         {"ttG+jets", 3.757},    
         {"ttH_bb", 0.2897},   
         {"ttH_nonbb", 0.209},     

         //single-top background 
         {"st_tchan", 136.02},
         {"st_antitchan", 80.95},
         {"st_tW_top", 34.91}, //McM gives 115, must be wrong???
         {"st_tW_antitop", 34.91},
         {"st_tZq", 0.0758},

         {"data_singleMuon_eraB", 1.0},    
         {"data_singleMuon_eraC", 1.0},    
         {"data_singleMuon_eraD", 1.0},    
        
     }
    }, //UL2018

};

map <string, int> FR_yield = {

    {"UL2016_preVFP", 3251},
    {"UL2016_postVFP", 2388},
    {"UL2017", 1000000000},
    {"UL2018", 1000000000},

};
