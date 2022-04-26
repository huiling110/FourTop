/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-11-22 22:54:06
 * @modify date 2021-11-22 22:54:06
 * @desc [description]
 */

#include "../EYandSP_usingClass_v3.h"

#include "checkTemplatesForCombine.C"

void makeRootForCombine_2tau1l(
    const TString channel = "2tau0l",
    TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v4modifiedMinDeltaR_fromV9/2tau0l_HT/"
){


    //output file for combine
    // TString outputName = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/HT_2tau1l_forCombine.root";
    TString outputName = outDir + "HT_" + channel + "_forCombine.root";
    TFile *output = new TFile( outputName, "RECREATE" );


    
    Int_t binNum = 11;
    Double_t binMin = 400;
    Double_t binMax = 1500;
    //!!!addHistChannel has no Lumi
    TH1D* TT = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");
    TT->Scale(lumiMap[era_g]);
    TT->Print();

    // TT->Write();
    TH1D* TTX = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 4, 9, "TTX_HT" );
    TTX->Scale(lumiMap[era_g]);

    TH1D* VV = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 9, 12, "VV_HT" );
    VV->Scale(lumiMap[era_g]);

    TH1D*  SingleTop = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 12, 15, "SingleTop_HT" );
    SingleTop->Scale(lumiMap[era_g]);

    TH1D* QCD = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 15, 24, "QCD_HT" );
    QCD->Scale(lumiMap[era_g]);

    TH1D*  TTTT = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 0, 1, "TTTT_HT" );
    TTTT->Scale(lumiMap[era_g]);
    TH1D* data_obs = addHistChannel( channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 0, 24, "data_obs_HT" );
    data_obs->Scale(lumiMap[era_g]);
    TH1D *allBgs = addHistChannel(channelCutMap[channel], basicWeight, "jets_HT", binNum, binMin, binMax, 1, 24, "allBgs_HT");
    allBgs->Scale(lumiMap[era_g]);
    // cout << "allBGs before QCD = " << allBgs->Integral();
    // allBgs->SetDefaultSumw2();
    // allBgs->Add(my_QCD_HT);
    // cout << "allBGs after QCD = " << allBgs->Integral();



    // TString outFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/2tau1l_HT/templatesPlots/";
    TString outFolder = outDir + "templatesPlots/";
    drawTemplates( TT, outFolder, channel );
    drawTemplates( TTX, outFolder , channel);
    drawTemplates( VV, outFolder, channel );
    drawTemplates( SingleTop, outFolder, channel );
    drawTemplates( TTTT, outFolder, channel );
    drawTemplates( QCD, outFolder, channel );



    output->Write();
    output->Close();


}

