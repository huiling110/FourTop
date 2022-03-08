/**
 * @author Huiliing Hua
 * @email huahl@ihep.ac.cn
 * @create date 2021-11-17 01:00:03
 * @modify date 2022-03-03 22:57:51
 * @desc [description]
 */


#include "EYandSP_usingClass_v3.h"

#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"
#include "THStack.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TLegend.h"
#include <iostream>
#include "TStopwatch.h"
#include "TPaveText.h"



void getAllHitos( vector<TH1D*> &allHistos, TH1D* &h_background, TString variable, Int_t bin, Double_t mini, Double_t maxi, TCut weight, TCut channelcut );
void printEventYield( const vector<TH1D*> &allHistos, const TH1D* h_background );
void drawHistos( const vector<TH1D*> &allHistos, const TH1D* h_background );
void addTextToPT( Int_t type, TPaveText* &pt, TH1D* &bgs );
void drawEventYield( const vector<TH1D*> &groupedBgsAndSignal, const TString EYplotDir, TString channel, const Double_t lumi, TString era );
void plotChannelDis( const vector<TH1D*> groupedBgsAndSignal, TString plotDir );
 

void EYandSP_usingClass_v3(){ 
    TStopwatch t;
    t.Start();

    Double_t lumi =  gLUMI_2016preVFP;
    TString era = "2016preVFP";
    TString EYplotDir = baseDir + "results/";


    vector<TString> variablelist;                vector<Int_t> bin;      vector<Double_t> Min;      vector<Double_t> Max;     vector<TString> axis;
    variablelist.push_back("jets_number");      bin.push_back(40);     Min.push_back(0);    Max.push_back(40);    axis.push_back("Number of jets");
 
  //apply selection cuts here
    vector<string> channelName = { "1Tau0L", "1Tau1E", "1Tau1Mu", "1Tau1L", "1Tau2OS", "1Tau2SS", "1Tau3L","2Tau0L", "2Tau1E", "2Tau1Mu", "2Tau2OS", "2Tau2SS" , "1Tau2L", "2Tau1L", "2Tau2L"  };
    vector<TCut>   channelCut   = { ES1tau0l, ES1tau1e,  ES1tau1m, ES1tau1l, ES1tau2os, ES1tau2ss, ES1tau3l, ES2tau0l, ES2tau1e, ES2tau1m, ES2tau2os, ES2tau2ss , ES1tau2l, ES2tau1l, ES2tau2l};


    vector<TH1D*>  groupedBgsAndSignal;

    //testing
    TH1D* ttttH = allProcesses[0].getChannelHist( ES1tau1e  ,weight, variablelist[0], bin[0], Min[0], Max[0] );
    ttttH->Print();


// for (UInt_t  cha=0; cha<channelName.size(); cha++){
for (UInt_t  cha=3; cha<4;cha++){
// for (UInt_t  cha=0; cha<1; cha++){
    cout<<channelName[cha]<<endl;
    // std::map<Double_t, TString> mymap;

    //loop variableList
    for(UInt_t i=0; i<1; i++){
    // for(UInt_t i=0; i<variablelist.size(); i++){
  	    TString iVariable = variablelist[i];
        // h_bg = getBackHist( allProcesses, channelCut[cha], weight );
        // cout<<"new bg: "<<h_bg->GetEntries();


        // getBgsAndSignalHist_Nano( groupedBgsAndSignal, channelCut[cha], weight, iVariable, bin[i], Min[i], Max[i] );
        getBgsAndSignalHist_Nano( groupedBgsAndSignal, channelCut[cha], basicWeight, iVariable, bin[i], Min[i], Max[i] );

        drawEventYield(  groupedBgsAndSignal, EYplotDir, channelName[cha], lumi, era );

        // plotChannelDis( groupedBgsAndSignal, EYplotDir );

        for( UInt_t p=0; p<groupedBgsAndSignal.size(); p++){
            groupedBgsAndSignal[p]->Print();
            cout<<"integral: "<<groupedBgsAndSignal[p]->Integral()<<"\n";
            cout<<"entries: "<<groupedBgsAndSignal[p]->GetEntries()<<"\n";
            delete groupedBgsAndSignal[p];
        }




/*

        //?for different range we have different sp, how to deal with this?
        if ( ifSP ){
            Double_t sp = separationPower(allHistos[0], h_background);
            cout<<variablelist[i]<<" separation power"<<sp<<endl;
            std::cout << '\n';
            if(i==(variablelist.size()-1)) cout<<channelName[cha]<<endl;
            mymap.insert(std::make_pair(sp, variablelist[i]));
        }
        cout<<plot<<"done"<<endl;

        for(UInt_t j = 0; j < allHistos.size(); j++){
             delete (allHistos[j]);
        }

        delete h_background;//put delete in the last
        delete h_bg;

        */
    }//end of loop of all variables



    // if ( ifSP ){
    //     for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit){
    //         std::cout <<  rit->second << " = "<< rit->first << endl;
    //     }
    // }


}//end of loop of all channels
    

    t.Stop();
    t.Print();
}








void plotChannelDis( const vector<TH1D*> groupedBgsAndSignal, TString plotDir ){
    TFile* plotFile = new TFile( plotDir+"dis.root", "RECREATE" );
    for ( UInt_t i=0; i<groupedBgsAndSignal.size(); i++ ){
        groupedBgsAndSignal[i]->Write();
    }
    // cout<<"writen file: "<<
    plotFile->Close();

}

void getAllHitos( vector<TH1D*> &allHistos, TH1D* &h_background, TString variable, Int_t bin, Double_t mini, Double_t maxi, TCut weight, TCut channelcut ){
    TH1D* TTTT_h ;//1
    TH1D* TTTo2L2Nu_h ; TH1D* TTToHadronic_h ; TH1D* TTToSemiLeptonic_h ;
    TH1D* TTGJets_h ;TH1D* ttZJets_h ; TH1D* ttWJets_h ;TH1D* ttH_h ; 
    TH1D* WZ_h ; TH1D* WW_h ; TH1D* ZZ_h ;TH1D* WGJets_h ;TH1D* ZGJetsToLLG_h ;//6
    TH1D* WWW_h ; TH1D* WWZ_h ; TH1D* WWG_h ; TH1D* ZZZ_h ; TH1D* WZZ_h ; TH1D* WZG_h ; TH1D* WGG_h ; TH1D* ZGGJets_h ;//8
    TH1D* WJetsToLNu_h ; TH1D* DYJetsToTauTau_h ;//2
    TH1D* tZq_ll_h ;TH1D* tZq_nunu_h;  TH1D* ST_tW_antitop_h ; TH1D* ST_tW_top_h ; TH1D* TGJets_h ;TH1D* THW_h ; TH1D* THQ_h ;//6
    TH1D* QCD_HT200to300_h; TH1D* QCD_HT300to500_h; TH1D* QCD_HT500to700_h; TH1D* QCD_HT700to1000_h;  TH1D* QCD_HT1000to1500_h; TH1D* QCD_HT1500to2000_h; TH1D* QCD_HT2000toInf_h;
    TH1D* VHToNonbb_h ; TH1D* ZHToTauTau_h ; TH1D* ZH_HToBB_ZToLL_h ; TH1D* GluGluHToZZTo4L_h ; TH1D* GluGluHToBB_h ; TH1D* GluGluHToGG_h ; TH1D* GluGluHToMuMu_h ; TH1D* GluGluHToTauTau_h ; TH1D* GluGluHToWWTo2L2Nu_h ; TH1D* GluGluHToWWToLNuQQ_h ; TH1D* VBFHToWWTo2L2Nu_h ; TH1D* VBFHToTauTau_h ; TH1D* VBFHToMuMu_h ; TH1D* VBFHToGG_h ; 

     TTTT_h = new TH1D("TTTT", variable,bin,mini,maxi);//1
     TTTo2L2Nu_h = new TH1D( "TTTo2L2Nu", variable,bin,mini,maxi);  TTToHadronic_h = new TH1D( "TTToHadronic",variable,bin,mini,maxi);  TTToSemiLeptonic_h = new TH1D( "TTToSemiLeptonic",variable,bin,mini,maxi);
     TTGJets_h = new TH1D( "TTGJets",variable,bin,mini,maxi); ttZJets_h = new TH1D( "ttZJets",variable,bin,mini,maxi);  ttWJets_h = new TH1D( "ttWJets",variable,bin,mini,maxi); ttH_h = new TH1D( "ttH",variable,bin,mini,maxi); /* ttbb_h = new TH1D( "ttbb",variable,bin,mini,maxi);*/ //6
     WZ_h = new TH1D( "WZ",variable,bin,mini,maxi);  WW_h = new TH1D( "WW",variable,bin,mini,maxi);  ZZ_h = new TH1D( "ZZ",variable,bin,mini,maxi); WGJets_h = new TH1D( "WGJets",variable,bin,mini,maxi); ZGJetsToLLG_h = new TH1D( "ZGJetsToLLG",variable,bin,mini,maxi);//6
     WWW_h = new TH1D( "WWW",variable,bin,mini,maxi);  WWZ_h = new TH1D( "WWZ",variable,bin,mini,maxi);  WWG_h = new TH1D( "WWG",variable,bin,mini,maxi);  ZZZ_h = new TH1D( "ZZZ",variable,bin,mini,maxi);  WZZ_h = new TH1D( "WZZ",variable,bin,mini,maxi);  WZG_h = new TH1D( "WZG",variable,bin,mini,maxi);  WGG_h = new TH1D( "WGG",variable,bin,mini,maxi);  ZGGJets_h = new TH1D( "ZGGJets",variable,bin,mini,maxi);//8
     WJetsToLNu_h = new TH1D( "WJetsToLNu",variable,bin,mini,maxi);  DYJetsToTauTau_h = new TH1D( "DYJetsToTauTau",variable,bin,mini,maxi);//2
     tZq_ll_h = new TH1D( "tZq_ll",variable,bin,mini,maxi);  tZq_nunu_h =  new TH1D( "tZq_nunu", variable,bin,mini,maxi); ST_tW_antitop_h = new TH1D( "ST_tW_antitop",variable,bin,mini,maxi);  ST_tW_top_h = new TH1D( "ST_tW_top",variable,bin,mini,maxi);  TGJets_h = new TH1D( "TGJets",variable,bin,mini,maxi); THW_h = new TH1D( "THW",variable,bin,mini,maxi);  THQ_h = new TH1D( "THQ",variable,bin,mini,maxi);//6
     QCD_HT200to300_h = new TH1D( "QCD_HT200to300",variable,bin,mini,maxi); QCD_HT300to500_h = new TH1D( "QCD_HT300to500",variable,bin,mini,maxi); QCD_HT500to700_h = new TH1D( "QCD_HT500to700",variable,bin,mini,maxi); QCD_HT700to1000_h = new TH1D( "QCD_HT700to1000",variable,bin,mini,maxi); QCD_HT1000to1500_h = new TH1D( "QCD_HT1000to1500",variable,bin,mini,maxi); QCD_HT1500to2000_h = new TH1D( "QCD_HT1500to2000",variable,bin,mini,maxi); QCD_HT2000toInf_h = new TH1D( "QCD_HT2000toInf",variable,bin,mini,maxi);

    allHistos.clear();
    allHistos = {
        TTTT_h, //0
        TTTo2L2Nu_h, TTToHadronic_h, TTToSemiLeptonic_h, //3
        TTGJets_h, ttZJets_h,ttWJets_h, ttH_h, //7
        WZ_h, WW_h, ZZ_h, WGJets_h, ZGJetsToLLG_h, //12
        WWW_h, WWZ_h, WWG_h, ZZZ_h, WZZ_h, WZG_h, WGG_h, ZGGJets_h,//20
        WJetsToLNu_h, DYJetsToTauTau_h,//22
        tZq_ll_h, tZq_nunu_h, ST_tW_antitop_h, ST_tW_top_h,//26
        TGJets_h, THW_h, THQ_h, //29
        QCD_HT200to300_h, QCD_HT300to500_h, QCD_HT500to700_h, QCD_HT700to1000_h, QCD_HT1000to1500_h, QCD_HT1500to2000_h, QCD_HT2000toInf_h,
    };

    // TH1::SetDefaultSumw2();// TH1::Sumw2 to force the storage and computation of the sum of the square of weights per bin.umw2 has been called, the error per bin is computed as the sqrt(sum of squares of weights), otherwise the error is set equal to the sqrt(bin content)
    h_background = new TH1D("BG", variable, bin, mini, maxi);

    TString hname ;
    Double_t scale;
    Double_t sumGenWeights = -99;
    for(UInt_t j = 0; j < allHistos.size(); j++){
    // for(UInt_t j = 0; j < 1; j++){
    // for(UInt_t j = 0; j < 4; j++){
        hname = allHistos[j]->GetName();
        
        // allProcesses[j].getEventTree()->Project( hname, plot, weight*(channelCut[cha]+MetFilters+trigger));
        // allProcesses[j].getEventTree()->Project( hname, variable, weight*(channelCut[cha]));
        allProcesses[j].getEventTree()->Project( hname, variable, weight*(channelcut));
        // allHistos[j]->Print();
        // if ( i==0 ){
            // cout<<allHistos[j]->GetName()<<":"<<endl;
            // cout<<allHistos[j]->GetName()<<":"<<"  ";
            // cout<<"raw entries = "<<allHistos[j]->GetEntries()<<"  ";
            // cout<<"weighted = "<<allHistos[j]->Integral()<<"  ";
        // }
        sumGenWeights = allProcesses[j].getGenWeightSum();
        scale = LUMI* allProcesses[j].getSigma()/sumGenWeights;
        // allHistos[j]->Scale(scale);
        // if ( i ==0){
            // cout<<"sumGenWeights = "<<sumGenWeights<<"  ";
            // cout<<"event yield = "<<allHistos[j]->Integral()<<endl;
            // cout<<"\n";
        // }
        // if(j > 0) h_background->Add((allHistos[j]),1);
        if(j > 0) h_background->Add((allHistos[j]),scale);
    }

}


void printEventYield( const vector<TH1D*> &allHistos, const TH1D* h_background ){
    cout<<"Raw entries:"<<endl;
    cout<<"TTTT         = "<<allHistos[0]->GetEntries()  <<endl;

    cout<<"Total BKG    = "<<h_background->GetEntries()<<endl;
    cout<<"\n";

    //does Integral include weight?//I think they do
    cout<<"Weighted:"<<endl;
    cout<<"TTTT         = "<<allHistos[0]->Integral()<<endl;
//
    cout<<"Total BKG    = "<<h_background->Integral()<<endl;
    cout<<"\n";

    cout<<"Event yield:"<<endl;
    cout<<"TTTT         = "<<allHistos[0]->Integral()*LUMI* allProcesses[0].getScale()<<endl;
    cout<<"scale = "<<allProcesses[0].getScale()*LUMI<<endl;

    cout<<"Total BKG    = "<<h_background->Integral()<<endl;
    cout<<"\n";
}


void addTextToPT( Int_t sumType, TPaveText* &pt, TString processName, const vector<TH1D*> &allHistos, Int_t startIndex, Int_t subprocessNum ,  vector<Process> &allProcesses  ){
    Double_t EY = 0;
    for ( Int_t start=startIndex; start<(startIndex+subprocessNum); start++ ){
        if ( sumType==0 ) EY = EY + allHistos[start]->GetEntries();
        if ( sumType==1 ) EY = EY + allHistos[start]->Integral();
        if ( sumType==2 ) EY = EY + ( LUMI*allHistos[start]->Integral()*allProcesses[start].getScale() );
    }
    TString entries;
    entries.Form( processName + "  = %f", EY );
    // pt->AddText( entries );
    TText *t1 = pt->AddText( entries );
    // t1->SetTextAlign(11);
    t1->SetTextAlign(12);
    // t1->SetTextSize( 0.1);
    t1->SetTextSize( 0.055);

}



void addTextToPT( Int_t type, TPaveText* &pt, const TH1D* bgs, const Double_t lumi ){
    Double_t EY = -99;
    if( type ==0 ) EY = bgs->GetEntries();
    if( type ==1 ) EY = bgs->Integral()*lumi;
    // if( type ==2 ) EY = bgs->Integral()*LUMI;

    TString entries;
    TString bgsName = bgs->GetName();
    TString processName = bgsName.Remove( bgsName.First("_"), bgsName.Sizeof() );
    entries.Form( processName + "  = %f", EY );
    TText *t1 = pt->AddText( entries );
    t1->SetTextAlign(12);
    t1->SetTextSize( 0.055);
    cout<<"entry: "<<entries<<"\n";
}

void drawEventYield( const vector<TH1D*> &groupedBgsAndSignal, const TString EYplotDir, TString channel, const Double_t lumi, TString era ){

    TCanvas *c = new TCanvas("c", "c");
    c->SetCanvasSize(300, 1000);
    c->SetWindowSize(400, 700);

    TPaveText *pt = new TPaveText(.05,.99,.95,.72, "NDC");// the position relative to cavas, first is the left down point
    TText* tt1 = pt->AddText( era +": " + channel ); tt1->SetTextSize( 0.065);
    TText* t0 = pt->AddText( " raw entries:"); t0->SetTextAlign(11); t0->SetTextSize( 0.055);
    for( UInt_t i = 0; i<groupedBgsAndSignal.size(); i++){
        // addTextToPT( 0, pt, groupedBgsAndSignal[i], lumi );
        addTextToPT( 0, pt, groupedBgsAndSignal[i], lumiMap[era]);
    }
    pt->Draw();


    TPaveText *pt2 = new TPaveText(.05,.69,.95,.42, "NDC");
    TText* tt2 = pt2->AddText( channel ); tt2->SetTextSize( 0.065);
    TText* t20 = pt2->AddText( "scaled to LUMI:"); t20->SetTextAlign(11); t20->SetTextSize( 0.055);
    for( UInt_t j = 0; j<groupedBgsAndSignal.size(); j++){
        addTextToPT( 1, pt2, groupedBgsAndSignal[j], lumiMap[era] );
    }
    pt2->Draw();

    // TPaveText *pt3 = new TPaveText(.05,.39,.95,.12, "NDC");
    // TText* tt3 = pt3->AddText( channel ); tt3->SetTextSize( 0.065);
    // TText* t3 = pt3->AddText( "scaled to LUMI:"); t3->SetTextAlign(11); t3->SetTextSize( 0.055);
    // for( UInt_t j = 0; j<groupedBgsAndSignal.size(); j++){
    //     addTextToPT( 2, pt3, groupedBgsAndSignal[j] );
    // }
    // pt3->Draw();



    c->SaveAs( EYplotDir+"EY_"+ era +"_" + channel+"_new.png");

}

void drawHistos( const vector<TH1D*> &allHistos, TH1D* h_background , TString variable){

    TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);
    TPad *c1_2 = new TPad("c1_2", "newpad",0.02,0.10,0.99,0.90);// bottom left point(),
    c1_2->Draw();
    c1_2->cd();

    h_background->SetLineWidth(2);
    h_background->SetLineColor(kBlue); 
    h_background->SetMinimum(0);
    h_background->SetMaximum(1.5 * h_background->GetMaximum());
    h_background->GetYaxis()->SetTitleSize(0.050);
    h_background->GetXaxis()->SetTitleSize(0.050);
    h_background->GetYaxis()->SetLabelSize(0.040);
    h_background->GetXaxis()->SetLabelSize(0.040); 
    h_background->SetTitle("");
    h_background->GetYaxis()->SetTitle("Events");
    // h_background->GetXaxis()->SetTitle(axis[i]);
    h_background->GetYaxis()->SetTitleOffset(1.00);
    h_background->GetXaxis()->SetTitleOffset(0.85);//Set distance between the axis and the axis title
    h_background->DrawNormalized("hist", 1);
    // h_background->Draw("hist");
    allHistos[0]->SetLineWidth(2);
    allHistos[0]->SetLineColor(2);
//        allHistos[0]->SetLineColor(kViolet-2); 
   // allHistos[0]->Draw("samehisto");
    allHistos[0]->DrawNormalized("samehist", 1);
    // allHistos[0]->Draw("samehist");


    TPad *pad = new TPad("pad","pad",0.01,0.01,0.99,0.99);
    gPad->RedrawAxis();
    TString channelText = "";
    Double_t channelTextFont   = 42;
    Double_t channelTextSize   = 0.06;
    TString cmsText     = "CMS";
    Double_t cmsTextFont   = 61;  // default is helvetic-bold
    bool writeExtraText = true;
    TString extraText   = "MC";
    //TString extraText   = "";
    Double_t extraTextFont = 52;  // default is helvetica-italics
    // text sizes and text offsets with respect to the top frame in unit of the top margin size
    Double_t lumiTextSize     = 0.6;
    Double_t lumiTextOffset   = 0.2;
    Double_t cmsTextSize      = 0.75;
    Double_t cmsTextOffset    = 0.1;  // only used in outOfFrame version
    Double_t relPosX    = 0.045;
    Double_t relPosY    = 0.035;
    Double_t relExtraDY = 1.2;
    // ratio of "CMS" and extra text size
    Double_t extraOverCmsTextSize  = 0.76;
    TString lumi_13TeV;
    lumi_13TeV = "35.9fb^{-1}";
    TString lumiText;
    lumiText += lumi_13TeV;
    lumiText += " (2016, 13 TeV)";
    Double_t t = pad->GetTopMargin();
    Double_t b = pad->GetBottomMargin();
    Double_t r = pad->GetRightMargin();
    Double_t l = pad->GetLeftMargin();
    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);    
    Double_t extraTextSize = extraOverCmsTextSize*cmsTextSize;
    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(lumiTextSize*t);    
    latex.DrawLatex(1-r+0.06,0.94,lumiText);
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11); 
    latex.SetTextSize(cmsTextSize*t);    
    latex.DrawLatex(l+0.01, 0.94,cmsText);
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.DrawLatex(l+0.12, 0.94, extraText); 
    latex.SetTextFont(channelTextFont);
    latex.SetTextSize(channelTextSize);


    //����ͼ�и����ߺ�ֱ��ͼ����ɫ
    TLegend *pl2 = new TLegend(0.65,0.60,0.91,0.91);
    pl2->SetTextSize(0.045); 
    pl2->SetFillColor(0);
  //  TLegendEntry *ple2 = pl2->AddEntry(data_SR, "data",  "L"); 
    TLegendEntry *ple2 = pl2->AddEntry(allHistos[0], "TTTT",  "L"); 
    pl2->Draw();
   

    // TString NAME = variablelist[i];
    // TString postfix = channelName[cha] + ".png";
    // c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/plotsAndResults/test/"+ NAME+postfix);
    
    // cout<<"Finished "<<NAME+postfix<<endl;
    c1->Draw();
}

Double_t separationPower(TH1D* h1, TH1D* h2){
    Double_t norm = 1;
    // h1->Print();
    // h2->Print();
    h1->Scale(norm/h1->Integral());
    h2->Scale(norm/h2->Integral());
  Int_t nbins=h1->GetXaxis()->GetNbins();
//  cout<<nbins<<endl;
  Double_t s=0;
//  Double_t width=h1->GetBinWidth(1);
  for(Int_t i=1;i<nbins+1;i++){
//  for(Int_t i=0;i<nbins;i++){
      if(h1->GetBinContent(i)+h2->GetBinContent(i)!=0)
//      s+=0.5*TMath::Power((h1->GetBinContent(i)-h2->GetBinContent(i))/width,2)/(h1->GetBinContent(i)+h2->GetBinContent(i))*width*width;
      s+=0.5*TMath::Power((h1->GetBinContent(i)-h2->GetBinContent(i)),2)/(h1->GetBinContent(i)+h2->GetBinContent(i));
      //?it seems you do not use width at all.
  }
  return s;
}
