
#include "../tmva/autoTraining_correlation/sumBGsTogether_Nano.C"

// void drawTemplates( TH1D* & templates, TString outDir ){
void drawTemplates( TH1D* & templates, TString inputFile ){
    TString name = templates->GetName();
    TCanvas* c = new TCanvas( name, name, 800, 600 );
    templates->Draw();
    inputFile.ReplaceAll(".root", "");
    TString plotName =  inputFile + name + ".png"; 
    // c->SaveAs( outDir+name+".png");
    c->SaveAs( plotName );
    cout<<c->GetName()<<"saved"<<"\n";
    delete c;
}


void checkTemplatesForCombine(){
    TString inputTemplateFileFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_11bins/";
    TString iFile = "TMVApp_1tau1l_10var_forCombine.root";
    TString inputFile = inputTemplateFileFolder + iFile;
    TString outDir = inputTemplateFileFolder + "templatesPlots/";
    // TString inputFile = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_11bins/TMVApp_1tau1l_10var_forCombine.root";
    // TString outDir = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_11bins/templatesPlots/";

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
    drawTemplates( TT, inputFile );
    drawTemplates( TTX, inputFile );
    drawTemplates( VV, inputFile );
    drawTemplates( SingleTop, inputFile );

    //draw s and b shape
    TH1D* allBgs = TT.Clone();
    allBgs







}