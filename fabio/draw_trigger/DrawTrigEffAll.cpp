#include "DrawTrigEff.cpp"
#include "DrawTrigEff2D.cpp"

void DrawTrigEffAll(bool PRINT) {
    
TFile *outputfile = new TFile( "TriggerSF_1D.root", "RECREATE" );
    
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_2jetsinpresel.root", "HT", "nocat", false, true, outputfile, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_2jetsinpresel_reducebinsnjets.root", "HT", "nocat", false, false, outputfile, PRINT);
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_2jetsinpresel.root", "HT", "nocat_njets", false, PRINT);
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_2jetsinpresel.root", "HT", "nocat_njets_mupt25", false, PRINT);
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_2jetsinpresel.root", "HT", "nocat_njets_mupt25_jetpt35", false, false, outputfile, PRINT);
    DrawTrigEff2D("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450.root", "njetsvsHT", "nocat", false, PRINT);
    /*DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "1tau0L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "1tau1L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "1tau2L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "1tau3L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "2tau0L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "2tau1L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "2tau2L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "1tauML", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "HT", "2tauML", false, PRINT);
    */
    
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450_expandHTRange.root", "njets", "nocat", false, false, outputfile, PRINT);
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450.root", "njets", "nocat_HT", false, PRINT);
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450.root", "njets", "nocat_HT_mupt25", false, PRINT);
//     DrawTrigEff("trigEff_vs_HTj_perprocess_output_withDATA_addHLT_PFJet450.root", "njets", "nocat_HT_mupt25_jetpt35", false, PRINT);
    /*DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "nocat_HT", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "nocat_HT_mupt25", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "1tau0L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "1tau1L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "1tau2L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "1tau3L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "2tau0L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "2tau1L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "2tau2L", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "1tauML", false, PRINT);
    DrawTrigEff("trigEff_vs_HTj_perprocess_output.root", "trigEff_vs_HTj_perprocess_DATAoutput.root", "njets", "2tauML", false, PRINT);*/
    
outputfile->Close();
delete outputfile;

}
