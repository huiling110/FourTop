#include <map>

using namespace std;

map <string, double> lumi = {

    {"UL2016_preVFP", 19500.0},
    {"UL2016_postVFP", 16800.0},
    {"UL2017", 41480.0},
    {"UL2018", 59830.0},
    //{"UL2018", 45347.0},

};

map <string, double> lumi_sec = {

    {"data_singleMuon_eraB", 6785.0},    
    {"data_singleMuon_eraC", 6612.0},    
    {"data_singleMuon_eraD", 31950.0},

};

map <string, string> input = {

    {"UL2016_preVFP", "../trigEff_output_UL2016_preVFP.root"},
    {"UL2016_postVFP", "../trigEff_output_UL2016_postVFP.root"},
    {"UL2017", "trigEff_output_UL2017.root"},
    //{"UL2018", "tryNewTriggers_UL2018_addHLT_PFJet500.root"},
    //{"UL2018", "trigEff_output_UL2018_bjetsMediumInPresel.root"},
    {"UL2018", "trigEff_output_UL2018_3bjetsLinPresel.root"},
    //{"UL2018", "trigEff_output_UL2018_triggersWithNoBtag.root"},

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
         //{"ttW+jets", 0.4611}, buggy?!?    
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

         {"data_singleMuon_eraB_v1", 1.0},
         {"data_singleMuon_eraB_v2", 1.0},
         {"data_singleMuon_eraC", 1.0},    
         {"data_singleMuon_eraD", 1.0},
         {"data_singleMuon_eraE", 1.0},
         {"data_singleMuon_eraF_hipm", 1.0},
         
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
