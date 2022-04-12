/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-11-22 22:54:06
 * @modify date 2021-11-22 22:54:06
 * @desc [description]
 */

#include "../EYandSP_usingClass_v3.h"

#include "checkTemplatesForCombine.C"

void makeRootForCombine_2tau1l(){


    //output file for combine
    TString outputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/HT_2tau1l_forCombine.root";
    TFile *output = new TFile( outputName, "RECREATE" );


    
    Int_t binNum = 11;
    Double_t binMin = 400;
    Double_t binMax = 1500;
    // TH1D* TT = addHistChannel( ES2tau1l, weight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");//!!addHistChannel has no Lumi
    TH1D* TT = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");
    TT->Scale(lumiMap[era_g]);
    TT->Print();

    // TT->Write();
    TH1D* TTX = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 4, 9, "TTX_HT" );
    TTX->Scale(lumiMap[era_g]);

    TH1D* VV = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 9, 12, "VV_HT" );
    VV->Scale(lumiMap[era_g]);

    TH1D*  SingleTop = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 12, 15, "SingleTop_HT" );
    SingleTop->Scale(lumiMap[era_g]);

    TH1D* QCD = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 15, 24, "QCD_HT" );
    QCD->Scale(lumiMap[era_g]);

    TH1D*  TTTT = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 0, 1, "TTTT_HT" );
    TTTT->Scale(lumiMap[era_g]);
    TH1D* data_obs = addHistChannel( ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 0, 24, "data_obs_HT" );
    data_obs->Scale(lumiMap[era_g]);
    TH1D *allBgs = addHistChannel(ES2tau1l, basicWeight, "jets_HT", binNum, binMin, binMax, 1, 24, "allBgs_HT");
    allBgs->Scale(lumiMap[era_g]);
    // cout << "allBGs before QCD = " << allBgs->Integral();
    // allBgs->SetDefaultSumw2();
    // allBgs->Add(my_QCD_HT);
    // cout << "allBGs after QCD = " << allBgs->Integral();



    TString outFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/templatesPlots/";
    drawTemplates( TT, outFolder );
    drawTemplates( TTX, outFolder );
    drawTemplates( VV, outFolder );
    drawTemplates( SingleTop, outFolder );
    drawTemplates( TTTT, outFolder );
    drawTemplates( QCD, outFolder );



    output->Write();
    output->Close();


}

