
#include "../tmva/autoTraining_correlation/sumBGsTogether_Nano.C"

void checkTemplatesForCombine(){
    TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v1_fromV9/1tau1l_v1/AppResults_11bins/TMVApp_1tau1l_10var_forCombine.root";
    TFile *file = TFile::Open( inputFile );

    TH1D* tttt = getHist( "tttt", file );
    tttt->Print();
    cout<<"Intergal tttt: "<<tttt->Integral()<<"\n";

    TH1D* ttbar_2l = getHist( "ttbar_2l", file );
    ttbar_2l->Print();



}