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



void printEventYield( const std::vector<TH1D*> &allHistos, const TH1D* h_background );
void drawHistos( const std::vector<TH1D*> &allHistos, const TH1D* h_background );
void addTextToPT( Int_t type, TPaveText* &pt, TH1D* &bgs );
void drawEventYield( const std::vector<TH1D*> &groupedBgsAndSignal, const TString EYplotDir, TString channel, const Double_t lumi, TString era );
void writeHistToFile( const std::vector<TH1D*> groupedBgsAndSignal, TString plotDir, TString channelName );
 

void EYandSP_usingClass_v3(){ 
    TStopwatch t;
    t.Start();

    // TString era = "2016preVFP";
    TString era = "2016postVFP";
    TString EYplotDir = baseDir_2016post + "results/";
    // TString EYplotDir = baseDir_2016pre + "results_tighter/";
    // TString EYplotDir = baseDir_2016pre + "results/";


    std::vector<TString> variablelist;                std::vector<Int_t> bin;      std::vector<Double_t> Min;      std::vector<Double_t> Max;     std::vector<TString> axis;
    variablelist.push_back("jets_number");      bin.push_back(40);     Min.push_back(0);    Max.push_back(40);    axis.push_back("Number of jets");

    std::vector<TH1D*>  groupedBgsAndSignal;



    TFile* plotFile = new TFile( EYplotDir+"DisForEY.root", "RECREATE" );
for ( auto const& cha : channelCutMap  ){
// for ( auto cha=channelCutMap.begin(); cha!=channelCutMap.end(); ++cha  ){
    // std::cout<<cha->first<<":"<<cha->second<<"\n";
    std::cout<<cha.first<<":"<<cha.second<<"\n";

    // if ( cha.first=="1tau1e" ) break;

    //loop variableList
    for(UInt_t i=0; i<1; i++){
    // for(UInt_t i=0; i<variablelist.size(); i++){
  	    TString iVariable = variablelist[i];


        // getBgsAndSignalHist_Nano( groupedBgsAndSignal, channelCut[cha], basicWeight, iVariable, bin[i], Min[i], Max[i] );
        getBgsAndSignalHist_Nano( groupedBgsAndSignal, cha.second, cha.first, basicWeight, iVariable, bin[i], Min[i], Max[i] );
        writeHistToFile( groupedBgsAndSignal, EYplotDir , cha.first);

        // drawEventYield(  groupedBgsAndSignal, EYplotDir, cha.first, lumi, era );
        drawEventYield(  groupedBgsAndSignal, EYplotDir, cha.first, lumiMap[era], era );


        // for( UInt_t p=0; p<groupedBgsAndSignal.size(); p++){
        //     groupedBgsAndSignal[p]->Print();
        //     cout<<"integral: "<<groupedBgsAndSignal[p]->Integral()<<"\n";
        //     cout<<"entries: "<<groupedBgsAndSignal[p]->GetEntries()<<"\n";
        //     delete groupedBgsAndSignal[p];
        // }




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


        */
    }//end of loop of all variables

    groupedBgsAndSignal.clear();

    // if ( ifSP ){
    //     for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit){
    //         std::cout <<  rit->second << " = "<< rit->first << endl;
    //     }
    // }


}//end of loop of all channels
    std::cout<<"writen output file: "<<plotFile->GetName()<<"\n";
    plotFile->Close();
    

    t.Stop();
    t.Print();
}








void writeHistToFile( const std::vector<TH1D*> groupedBgsAndSignal, TString plotDir, TString channelName ){
    // gSystem->Exec("mkdir " + plotDir);
    // TFile* plotFile = new TFile( plotDir+"DisForEY_"+ channelName + ".root", "RECREATE" );
    for ( UInt_t i=0; i<groupedBgsAndSignal.size(); i++ ){
        groupedBgsAndSignal[i]->Write();
    }

}



void addTextToPT( Int_t sumType, TPaveText* &pt, TString processName, const std::vector<TH1D*> &allHistos, Int_t startIndex, Int_t subprocessNum ,  std::vector<Process> &allProcesses  ){
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
    bgsName.Remove( 0, bgsName.First("_")+1 );
    TString processName = bgsName.Remove( bgsName.First("_"), bgsName.Sizeof() );
    entries.Form( processName + "  = %f", EY );
    TText *t1 = pt->AddText( entries );
    t1->SetTextAlign(12);
    t1->SetTextSize( 0.055);
    // cout<<"entry: "<<entries<<"\n";
}

void drawEventYield( const std::vector<TH1D*> &groupedBgsAndSignal, const TString EYplotDir, TString channel, const Double_t lumi, TString era ){

    TCanvas *c = new TCanvas("c", "c");
    c->SetCanvasSize(300, 1000);
    c->SetWindowSize(400, 700);

    TPaveText *pt = new TPaveText(.05,.90,.95,.55, "NDC");// the position relative to cavas, first is the left down point
    TText* tt1 = pt->AddText( era +": " + channel ); tt1->SetTextSize( 0.065);
    TText* t0 = pt->AddText( " raw entries:"); t0->SetTextAlign(11); t0->SetTextSize( 0.055);
    for( UInt_t i = 0; i<groupedBgsAndSignal.size(); i++){
        // addTextToPT( 0, pt, groupedBgsAndSignal[i], lumi );
        addTextToPT( 0, pt, groupedBgsAndSignal[i], lumiMap[era]);
    }
    pt->Draw();


    TPaveText *pt2 = new TPaveText(.05,.45,.95,.1, "NDC");
    TText* tt2 = pt2->AddText( era +": " +  channel ); tt2->SetTextSize( 0.065);
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



    c->SaveAs( EYplotDir+"EY_"+ era +"_" + channel+".png");
    std::cout<<"plots here: "<<EYplotDir+"EY_"+ era +"_" + channel+".png"<<"\n";

}

void drawHistos( const std::vector<TH1D*> &allHistos, TH1D* h_background , TString variable){

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
