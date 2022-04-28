//#include "DrawVariable.cpp"
#include "DrawVariable_merge2016.cpp"

void DrawVariablesAll(bool PRINT) {

    //DrawVariable_merge2016("UL2016", "jets_HT","1tau0L_VR",false,1,500,300,1500,"H_{T} [GeV]",false,505,PRINT);
    
    //event variables
    //DrawVariable("UL2016_preVFP", "jets_HT","1tau0L_CR",false,1,500,300,1500,"H_{T} [GeV]",false,505,PRINT);
    //DrawVariable("UL2016_postVFP", "jets_HT","1tau0L_CR",false,1,500,300,1500,"H_{T} [GeV]",false,505,PRINT);
//    DrawVariable("UL2016_preVFP", "jets_HT","1tau0L_VR",false,1,500,300,1500,"H_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_HT","1tau0L_SR",false,1,500,300,1500,"H_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_HT","1tau3L",false,1,10,300,1500,"H_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_HT","2tau0L",false,1,500,300,1500,"H_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_HT","2tau2L",false,1,50,300,1500,"H_{T} [GeV]",false,505,PRINT);
//     
//     //1tau0L
    DrawVariable_merge2016("UL2016_preVFP", "taus_1pt","1tau0L",false,2,500,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
    DrawVariable_merge2016("UL2016_preVFP", "jets_HT","1tau0L_VR",false,1,500,0,200,"H_{T} [GeV]",false,505,PRINT);
    //DrawVariable_merge2016("UL2016_preVFP", "jets_HT","1tau0L_CR",false,1,500,0,200,"H_{T} [GeV]",false,505,PRINT);
    //DrawVariable("UL2016_postVFP", "taus_1pt","1tau0L",false,2,500,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_number","1tau0L",false,1,500,7,15,"Jet multiplicity",false,505,PRINT);
//     DrawVariable("bjetsM_number","1tau0L",false,1,500,1,10,"b jet multiplicity",false,505,PRINT);
//     DrawVariable("jets_bScore","1tau0L",false,4,500,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("bjetsM_1score","1tau0L",false,2,500,0,1,"b tag score of leading b tagged jet",false,505,PRINT);
//     DrawVariable("bjetsM_2score","1tau0L",false,2,500,0,1,"b tag score of second-leading b tagged jet",false,505,PRINT);
//     DrawVariable("jets_aplanarity","1tau0L",false,2,500,0,1,"Aplanarity",false,505,PRINT);
//     DrawVariable("jets_sphericity","1tau0L",false,2,500,0,1,"Sphericity",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","1tau0L",false,2,500,0,20,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("jets_transMass","1tau0L",false,8,500,0,2500,"Transverse mass of  jets [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_minDeltaR","1tau0L",false,2,500,0,5,"min #DeltaR (b jet, b jet)",false,505,PRINT);
//     
//     //1tau1L
//      DrawVariable("UL2016_preVFP", "taus_1pt","1tau1L",false,2,100,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_bScore","1tau1L",false,2,100,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("jets_7pt","1tau1L",false,1,100,0,120,"7th jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("toptagger_HT","1tau1L",false,4,100,250,1000,"Resolved tops H_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_6pt","1tau1L",false,1,100,0,120,"6th jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_invariantMass","1tau1L",false,2,100,0,1500,"Invariant mass of b tagged jets [GeV]",false,505,PRINT);
//     DrawVariable("jets_transMass","1tau1L",false,4,100,400,2000,"Transverse mass of  jets [GeV]",false,505,PRINT);
//     DrawVariable("nonbjetsM_4pt","1tau1L",false,1,100,0,200,"4th non-b jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","1tau1L",false,2,100,0,20,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("bjetsM_minDeltaR","1tau1L",false,1,100,0,5,"min #DeltaR (b jet, b jet)",false,505,PRINT);
//     DrawVariable("toptagger_3pt","1tau1L",false,1,100,0,450,"3rd resolved top p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("toptagger_MHT","1tau1L",false,2,100,0,500,"Resolved tops p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("leptonsMVAL_number","1tau1L",false,1,100,0,10,"Number of loose leptons",false,505,PRINT);
//     
//     //1tau2L
//    DrawVariable("taus_1pt","1tau2L",false,2,25,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_bScore","1tau2L",false,2,25,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("bjetsM_3pt","1tau2L",false,1,25,0,120,"3rd b tagged jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_number","1tau2L",false,1,25,0,15,"Jet multiplicity",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","1tau2L",false,2,25,0,20,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("toptagger_transMass","1tau2L",false,2,25,0,1000,"Transverse mass of resolved tops [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_invariantMass","1tau2L",false,2,25,0,1500,"Invariant mass of b tagged jets [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_minDeltaR","1tau2L",false,2,25,0,5,"min #DeltaR (b jet, b jet)",false,505,PRINT);
//     DrawVariable("bjetsM_4pt","1tau2L",false,1,25,0,120,"4th b tagged jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_HT","1tau2L",false,1,25,0,1000,"H_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_4pt","1tau2L",false,1,25,0,120,"4th jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("toptagger_1pt","1tau2L",false,1,25,80,450,"1st resolved top p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_aplanarity","1tau2L",false,1,25,0,0.4,"Aplanarity",false,505,PRINT);
//     DrawVariable("jets_tausF_minDeltaR","1tau2L",false,1,25,0,10,"min #DeltaR (jet, #tau_{F})",false,505,PRINT);
//     DrawVariable("tausF_MHT","1tau2L",false,1,25,0,150,"Fakeable taus p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_minDeltaR","1tau2L",false,1,25,0,10,"min #DeltaR (jet, jet)",false,505,PRINT);
//     
//     //1tau3L
//     DrawVariable("taus_1pt","1tau3L",false,2,25,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_bScore","1tau3L",false,2,25,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("jets_number","1tau3L",false,1,25,0,15,"Jet multiplicity",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","1tau3L",false,2,25,0,20,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("jets_1pt","1tau3L",false,2,25,0,400,"1st jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_aplanarity","1tau3L",false,1,25,0,0.4,"Aplanarity",false,505,PRINT);
//     DrawVariable("jets_minDeltaR","1tau3L",false,1,25,0,10,"min #DeltaR (jet, jet)",false,505,PRINT);
//     
//     //2tau0L
//     DrawVariable("taus_1pt","2tau0L",false,2,100,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_bScore","2tau0L",false,2,100,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("jets_number","2tau0L",false,1,100,0,15,"Jet multiplicity",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","2tau0L",false,2,100,0,20,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("jets_1pt","2tau0L",false,2,100,0,400,"1st jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_aplanarity","2tau0L",false,1,100,0,0.4,"Aplanarity",false,505,PRINT);
//     DrawVariable("jets_minDeltaR","2tau0L",false,1,100,0,10,"min #DeltaR (jet, jet)",false,505,PRINT);
//     
//     //2tau1L
//     DrawVariable("taus_1pt","2tau1L",false,2,50,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_HTDividedByMET","2tau1L",false,1,50,0,40,"H_{T}/MET",false,505,PRINT);
//     DrawVariable("tausT_MHT","2tau1L",false,1,50,0,150,"Tight taus p_{T}",false,505,PRINT);
//     DrawVariable("jets_bScore","2tau1L",false,2,50,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("jets_6pt","2tau1L",false,1,50,0,120,"6th jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_minDeltaR","2tau1L",false,1,50,0,10,"min #DeltaR (b jet, b jet)",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","2tau1L",false,4,50,0,30,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("toptagger_invariantMass","2tau1L",false,2,50,0,1000,"Invariant mass of resolved tops [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_invariantMass","2tau1L",false,2,50,0,1000,"Invariant mass of b tagged jets [GeV]",false,505,PRINT);
//     DrawVariable("jets_4pt","2tau1L",false,1,50,0,120,"4th jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("toptagger_1pt","2tau1L",false,2,50,80,450,"1st resolved top p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_tausF_minDeltaR","2tau1L",false,1,50,0,10,"min #DeltaR (jet, #tau_{F})",false,505,PRINT);
//     DrawVariable("jets_minDeltaR","2tau1L",false,1,50,0,10,"min #DeltaR (jet, jet)",false,505,PRINT);
//     DrawVariable("jets_average_DeltaR","2tau1L",false,1,50,0,5,"Average #DeltaR (jet, jet)",false,505,PRINT);
//     DrawVariable("tausL_HT","2tau1L",false,1,50,0,200,"Loose taus H_{T} [GeV]",false,505,PRINT);
//     
//     //2tau2L
//     DrawVariable("taus_1pt","2tau2L",false,2,25,0,200,"Leading #tau p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_bScore","2tau2L",false,2,25,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("jets_number","2tau2L",false,1,25,0,15,"Jet multiplicity",false,505,PRINT);
//     DrawVariable("jets_ratioHT_4toRest","2tau2L",false,2,25,0,20,"H_{T} ratio 4toRest",false,505,PRINT);
//     DrawVariable("jets_1pt","2tau2L",false,2,25,0,400,"1st jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("jets_aplanarity","2tau2L",false,1,25,0,0.4,"Aplanarity",false,505,PRINT);
//     DrawVariable("jets_minDeltaR","2tau2L",false,1,25,0,10,"min #DeltaR (jet, jet)",false,505,PRINT);
       //2tauXL
//     DrawVariable("jets_bScore","2tauXL",false,2,25,0,5,"Sum of b tag score for all jets",false,505,PRINT);
//     DrawVariable("jets_4largestBScoreSum","2tauXL",false,2,25,0,5,"Sum of 4 largest b tag scores",false,505,PRINT);
//     DrawVariable("leptonsMVAL_transMass","2tauXL",false,1,25,0,500,"Transverse mass of loose leptons [GeV]",false,505,PRINT); //range to be fixed in script generating histograms, too wide
//     DrawVariable("jets_number","2tauXL",false,1,25,0,10,"Transverse mass of loose leptons [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_invariantMass","2tauXL",false,2,25,0,800,"Invariant mass of b tagged jets [GeV]",false,505,PRINT);
//     DrawVariable("tausL_leptonsT_invariantMass","2tauXL",false,2,25,0,800,"Invariant mass of loose taus and tight leptons [GeV]",false,505,PRINT);
//     DrawVariable("jets_transMass","2tauXL",false,8,25,0,2500,"Transverse mass of jets [GeV]",false,505,PRINT);
//     DrawVariable("jets_6pt","2tauXL",false,1,25,0,120,"6th jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("toptagger_transMass","2tauXL",false,2,25,0,1000,"Transverse mass of resolved tops [GeV]",false,505,PRINT);
//     DrawVariable("bjetsM_minDeltaR","2tauXL",false,2,25,0,5,"min #DeltaR (b jet, b jet)",false,505,PRINT);
//     DrawVariable("nonbjetsM_4pt","2tauXL",false,1,25,0,200,"4th non-b jet p_{T} [GeV]",false,505,PRINT);
//     DrawVariable("Met_pt","2tauXL",false,1,25,0,500,"MET [GeV]",false,505,PRINT);
    
}






