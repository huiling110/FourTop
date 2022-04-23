
#include "../tmva/autoTraining_correlation/sumBGsTogether_Nano.C"

// void drawTemplates( TH1D* & templates, TString outDir ){
void drawTemplates( TH1D* & templates, TString outDir,  TString iFile ){
    TString name = templates->GetName();
    TString title = templates->GetTitle();
    iFile.ReplaceAll( "TMVApp_", "");
    iFile.ReplaceAll(".root", "");
    templates->SetTitle( title+  "(" +   iFile     +")");
    cout<<"histTitle:"<<templates->GetTitle()<<"\n";
    TCanvas* c = new TCanvas( name, name, 800, 600 );
    templates->Draw();
    TString plotName =  outDir + iFile + "_" + name + ".png"; 
    // c->SaveAs( outDir+name+".png");
    c->SaveAs( plotName );
    cout<<c->GetName()<<"saved"<<"\n";
    delete c;
}


void checkTemplatesForCombine(
    // TString inputTemplateFileFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_11bins/";
    // TString inputTemplateFileFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_40bins/";
    TString inputTemplateFileFolder = "/publicfs/cms/user/huahuil/tauOfTTTT_NanoAOD/TMVAoutput/2016/v2Add2Variables_fromV9/1tau1l_v3/AppResults_resubmit_80bins/",
    TString iFile = "TMVApp_1tau1l_10var_forCombine.root"

){

    TString inputFile = inputTemplateFileFolder + iFile;
    TString outDir = inputTemplateFileFolder + "templatesPlots/";
    Bool_t isMVA = true;

    TFile *file = TFile::Open( inputFile );

    TH1D* tttt = getHist( "tttt", file, isMVA );
    tttt->Print();
    cout<<"Intergal tttt: "<<tttt->Integral()<<"\n";
    cout<<"bin num: "<<tttt->GetNbinsX()<<"\n";

    TH1D* ttbar_2l = getHist( "ttbar_2l", file, isMVA );
    ttbar_2l->Print();
    TH1D* QCD = getHist( "QCD", file, isMVA );
    QCD->Print();
    TH1D* data = getHist( "data_obs", file, isMVA );
    data->Print();

    TH1D* TT = getHist( "TT", file, isMVA );
    TH1D* TTX = getHist( "TTX", file, isMVA );
    TH1D* VV = getHist( "VV", file , isMVA );
    TH1D* SingleTop = getHist( "SingleTop", file, isMVA );


    drawTemplates( tttt, outDir, iFile );
    drawTemplates( TT, outDir, iFile );
    drawTemplates( TTX, outDir, iFile );
    drawTemplates( VV, outDir, iFile );
    drawTemplates( SingleTop, outDir, iFile );

    //draw s and b shape
    TString histPost = "_HT";
    if ( isMVA ) histPost = "_MVA_BDT";
    tttt->Scale(  1 / tttt->Integral() );
    tttt->SetLineColor(kRed);
    tttt->SetMaximum(0.15);
    // TH1D *allBgs = (TH1D *)input->Get("allBgs" + histPost );
    TH1D* allBgs = getHist( "allBgs", file, isMVA );
    allBgs->Scale(1 / allBgs->Integral());

    TCanvas *c1 = new TCanvas( "c1", "HT distribution");
    if ( isMVA ) c1->SetTitle( "BDT distribution" );
    tttt->Draw();
    allBgs->Draw("same");

    TString forOutFile = outDir + iFile;
    TString outFileName ;
    if (!isMVA){
        outFileName = forOutFile.ReplaceAll( ".root", "_HTshape.png");
    }else{
        outFileName = forOutFile.ReplaceAll( ".root", "_BDTshape.png");
    }
    c1->SaveAs( outFileName );







}