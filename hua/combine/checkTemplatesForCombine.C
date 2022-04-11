
#include "../tmva/autoTraining_correlation/sumBGsTogether_Nano.C"

void drawTemplates( TH1D* & templates, TString outDir ){
    TString name = templates->GetName();
    TCanvas* c = new TCanvas( name, name, 800, 600 );
    templates->Draw();
    c->SaveAs( outDir+name+".png");
    cout<<c->GetName()<<"saved"<<"\n";
    delete c;
}


void checkTemplatesForCombine(){
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v2/AppResults_11bins/templatePlots/";
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9//1tau1l_v2/AppResults_11bins/TMVApp_1tau1l_11var_forCombine.root";
    TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v2/AppResults_changeBDTrange_11bins/TMVApp_1tau1l_10var_forCombine.root";
    TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v2/AppResults_changeBDTrange_11bins/templatesPlots/";

    TFile *file = TFile::Open( inputFile );

    TH1D* tttt = getHist( "tttt", file );
    tttt->Print();
    cout<<"Intergal tttt: "<<tttt->Integral()<<"\n";
    cout<<"bin num: "<<tttt->GetNbinsX()<<"\n";
    drawTemplates( tttt, outDir );

    TH1D* ttbar_2l = getHist( "ttbar_2l", file );
    ttbar_2l->Print();
    TH1D* QCD = getHist( "QCD", file );
    QCD->Print();
    TH1D* data = getHist( "data_obs", file );
    data->Print();

    TH1D* TT = getHist( "TT", file );
    TH1D* TTX = getHist( "TTX", file );
    TH1D* VV = getHist( "VV", file );
    TH1D* SingleTop = getHist( "SingleTop", file );
    drawTemplates( TT, outDir );
    drawTemplates( TTX, outDir );
    drawTemplates( VV, outDir );
    drawTemplates( SingleTop, outDir );







}