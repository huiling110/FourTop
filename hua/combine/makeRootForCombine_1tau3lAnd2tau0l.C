/**
 * @author Huiling Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-11-22 22:54:06
 * @modify date 2021-11-22 22:54:06
 * @desc [description]
 */

#include "/workfs2/cms/huahuil/4topCode/CMSSW_10_2_20_UL/src/FourTop/hua/EYandSP_usingClass_v3.h"


void makeRootForCombine_1tau3lAnd2tau0l(
    Int_t channel = 8
){

    //output file for combine
    TString outputName = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/1tau3l_HT/11bins/dataDriven_1tau3l_forCombine.root";
    TCut channelCut = ES1tau3l;
    if( channel == 8 ){
        outputName = "/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/TMVAOutput/v46_v3addBtagHLTweights/2tau0l_HT/11bins/dataDriven_2tau0l_forCombine.root";
        channelCut = ES2tau0l;
    }
    TFile *output = new TFile( outputName, "RECREATE" );

    //HT distribution from other processes other than QCD
    Int_t binNum = 11;
    Double_t binMin = 400;
    Double_t binMax = 1500;
    
    TH1D* TT = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 1, 4, "TT_HT");
    TT->Print();
    TT->Write();

    TH1D* TTX = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 4, 8, "TTX_HT" );
    // ttX->Print();

    TH1D* VV = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 8, 13, "VV_HT" );

    TH1D* VVV = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 13, 21, "VVV_HT" );

    TH1D* WJets = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 21, 22, "WJets_HT" );

    TH1D* DYJets = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 22, 23, "DYJets_HT" );
    TH1D*  SingleTop = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 23, 27, "SingleTop_HT" );

    TH1D*  TX= addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 27, 30, "TX_HT" );

    //data_obs
    TH1D*  TTTT = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 0, 1, "TTTT_HT" );
    TH1D* data_obs = addHistChannel( channelCut, weight, "jets_HT", binNum, binMin, binMax, 0, 30, "data_obs_HT" );


    output->Write();
    output->Close();

    





}

