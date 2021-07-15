#include "EYandSP_usingClass_v2.h"

#include "TH1.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TH1D.h"
#include "THStack.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TLegend.h"
#include <iostream>
#include "TROOT.h"
#include "TMath.h"
#include "TString.h"
#include "TCut.h"
#include "TStopwatch.h"

void getAllHitos( vector<TH1D*> &allHistos, TH1D* &background_SR, TString variable, Int_t bin, Double_t mini, Double_t maxi, TCut weight, TCut channelcut );


void EYandSP_usingClass_v2(){ 
    TStopwatch t;
    t.Start();

    Bool_t ifSP = false;
    // Bool_t ifSP = true;
    Bool_t ifDraw = false;
    // Bool_t ifDraw = true;
    // Bool_t ifEY = false;
    Bool_t ifEY = true;

  using namespace std; 

//  bool SYST = false;

  vector<TString> variablelist;                vector<Int_t> bin;      vector<Double_t> Min;      vector<Double_t> Max;     vector<TString> axis;
//variablelist is plots we want to show   
//?is there a more clever way to push_back all in a loop?

  variablelist.push_back("jets_number");      bin.push_back(40);     Min.push_back(0);    Max.push_back(40);    axis.push_back("Number of jets");
 



  //apply selection cuts here
//step4
      //
const TCut ES1tau0l = "tausT_number==1 && leptonsMVAT_number==0 &&  jets_number>=8 && bjetsM_num>=2";
const TCut ES1tau1e = "tausT_number==1 && elesMVAT_number==1 && leptonsMVAT_number==1 &&  jets_number>=6 && bjetsM_num>=2";
const TCut ES1tau1m = "tausT_number==1 && muonsT_number==1 && leptonsMVAT_number==1&& jets_number>=6 && bjetsM_num>=2";
const TCut ES1tau2os = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  &&  jets_number>=4 && bjetsM_num>=2";
const TCut ES1tau2ss = "tausT_number==1 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jets_number>=4 && bjetsM_num>=2";
const TCut ES1tau3l = "tausT_number==1 && leptonsMVAT_number==3 &&  jets_number>=2 && bjetsM_num>=2";
const TCut ES2tau0l = "tausT_number==2 && leptonsMVAT_number==0 &&  jets_number>=6 && bjetsM_num>=2";
const TCut ES2tau1e = "tausT_number==2 && elesMVAT_number==1 && leptonsMVAT_number==1 && jets_number>=4 && bjetsM_num>=2";
const TCut ES2tau1m = "tausT_number==2 && muonsT_number==1 && leptonsMVAT_number==1 &&  jets_number>=4 && bjetsM_num>=2";
const TCut ES2tau2os = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2OS==1  && jets_number>=2 && bjetsM_num>=2";
const TCut ES2tau2ss = "tausT_number==2 && leptonsMVAT_number==2 && leptonsMVAT_2SS==1 &&  jets_number>=2 && bjetsM_num>=2";
const TCut weight = "EVENT_genWeight*EVENT_prefireWeight*PUWeight";

vector<string> channelName = { "1Tau0L", "1Tau1E", "1Tau1Mu", "1Tau2OS", "1Tau2SS", "1Tau3L","2Tau0L", "2Tau1E", "2Tau1Mu", "2Tau2OS", "2Tau2SS"   };
vector<TCut>   channelCut   = { ES1tau0l, ES1tau1e,  ES1tau1m, ES1tau2os, ES1tau2ss, ES1tau3l, ES2tau0l, ES2tau1e, ES2tau1m, ES2tau2os, ES2tau2ss };

TCut MetFilters = "Flag_goodVertices==1 && Flag_globalSuperTightHalo2016Filter==1 && Flag_HBHENoiseFilter==1 && Flag_HBHENoiseIsoFilter==1 && Flag_EcalDeadCellTriggerPrimitiveFilter==1 && Flag_BadPFMuonFilter==1";
TCut trigger = "HLT_PFHT450_SixJet40_BTagCSV_p056==1 || HLT_PFHT400_SixJet30_DoubleBTagCSV_p056==1";




vector<TH1D*> allHistos;
TH1D* background_SR;

for (UInt_t  cha=0; cha<channelName.size(); cha++){
// for (UInt_t  cha=0; cha<1; cha++){
    TString postfix = channelName[cha] + ".png";
    cout<<channelName[cha]<<endl;
    std::map<Double_t, TString> mymap;

    for(UInt_t i=0; i<1; i++){
    // for(UInt_t i=0; i<variablelist.size(); i++){
          // const char *plot = variablelist[i];
  	    TString plot = variablelist[i];

        getAllHitos( allHistos, background_SR, plot, bin[i], Min[i], Max[i], weight, channelCut[i] );

        if ( i ==0 && ifEY ){
            cout<<"Raw entries:"<<endl;
            cout<<"TTTT         = "<<allHistos[0]->GetEntries()  <<endl;
            // cout<<"TTTT         = "<<TTTT_h->GetEntries()  <<endl;
            // cout<<"TT           = "<<TTTo2L2Nu_h->GetEntries()+TTToHadronic_h->GetEntries()+TTToSemiLeptonic_h->GetEntries()<<endl;
            // cout<<"TTX          = "<<TTGJets_h->GetEntries()+ ttZJets_h->GetEntries()+ ttWJets_h->GetEntries()<<endl;
            // cout<<"single top   = "<<tZq_ll_h->GetEntries()+ tZq_nunu_h->GetEntries()+ ST_tW_antitop_h->GetEntries()+ ST_tW_top_h->GetEntries()<<endl;
            // cout<<"TX           = "<<TGJets_h->GetEntries()+ THW_h->GetEntries()+ THQ_h->GetEntries()<<endl;
            // cout<<"DYJets       = "<<DYJetsToTauTau_h->GetEntries()<<endl;
            // cout<<"VV           = "<<WZ_h->GetEntries()+ WW_h->GetEntries()+ ZZ_h->GetEntries()+ WGJets_h->GetEntries()+ ZGJetsToLLG_h->GetEntries()<<endl;
            // cout<<"VVV          = "<<WWW_h->GetEntries()+ WWZ_h->GetEntries()+ WWG_h->GetEntries()+ ZZZ_h->GetEntries()+ WZZ_h->GetEntries()+ WZG_h->GetEntries()+ WGG_h->GetEntries()+ ZGGJets_h->GetEntries()<<endl;
            // cout<<"QCD          = "<<QCD_HT200to300_h->GetEntries()+ QCD_HT300to500_h->GetEntries()+ QCD_HT500to700_h->GetEntries()+ QCD_HT700to1000_h->GetEntries()+ QCD_HT1000to1500_h->GetEntries()+ QCD_HT1500to2000_h->GetEntries()+ QCD_HT2000toInf_h->GetEntries()<<endl;

            cout<<"Total BKG    = "<<background_SR->GetEntries()<<endl;
            cout<<"\n";
        }

        if ( i ==0 && ifEY ){
            //does Integral include weight?//I think they do
            cout<<"Weighted:"<<endl;
            // cout<<"TTTT         = "<<TTTT_h->Integral()<<endl;
            // cout<<"TT           = "<<TTTo2L2Nu_h->Integral()+TTToHadronic_h->Integral()+TTToSemiLeptonic_h->Integral()<<endl;
            // cout<<"TTX          = "<<TTGJets_h->Integral()+ ttZJets_h->Integral()+ ttWJets_h->Integral()<<endl;
            // cout<<"single top   = "<<tZq_ll_h->Integral()+ tZq_nunu_h->Integral()+ ST_tW_antitop_h->Integral()+ ST_tW_top_h->Integral()<<endl;
            // cout<<"TX           = "<<TGJets_h->Integral()+ THW_h->Integral()+ THQ_h->Integral()<<endl;
            // cout<<"DYJets       = "<<DYJetsToTauTau_h->Integral()<<endl;
            // cout<<"VV           = "<<WZ_h->Integral()+ WW_h->Integral()+ ZZ_h->Integral()+ WGJets_h->Integral()+ ZGJetsToLLG_h->Integral()<<endl;
            // cout<<"VVV          = "<<WWW_h->Integral()+ WWZ_h->Integral()+ WWG_h->Integral()+ ZZZ_h->Integral()+ WZZ_h->Integral()+ WZG_h->Integral()+ WGG_h->Integral()+ ZGGJets_h->Integral()<<endl;
            // cout<<"QCD          = "<<QCD_HT200to300_h->Integral()+ QCD_HT300to500_h->Integral()+ QCD_HT500to700_h->Integral()+ QCD_HT700to1000_h->Integral()+ QCD_HT1000to1500_h->Integral()+ QCD_HT1500to2000_h->Integral()+ QCD_HT2000toInf_h->Integral()<<endl;
//
            cout<<"Total BKG    = "<<background_SR->Integral()<<endl;
            cout<<"\n";
        }

        if ( i ==0 && ifEY ){
            cout<<"Event yield:"<<endl;
            // cout<<"TTTT         = "<<TTTT_h->Integral()*LUMI* TTTT.getScale()<<endl;
            // cout<<"TT           = "<<TTTo2L2Nu_h->Integral()*LUMI*TTTo2L2Nu.getScale()+ TTToHadronic_h->Integral()*LUMI*TTToHadronic.getScale()+ TTToSemiLeptonic_h->Integral()*LUMI*TTToSemiLeptonic.getScale()<<endl;
            // cout<<"TTX          = "<<TTGJets_h->Integral()*LUMI*TTGJets.getScale()+ ttZJets_h->Integral()*LUMI*ttZJets.getScale()+ ttWJets_h->Integral()*LUMI*ttWJets.getScale()<<endl;
            // cout<<"single top   = "<<tZq_ll_h->Integral()*LUMI*tZq_ll.getScale()+ tZq_nunu_h->Integral()*LUMI*tZq_nunu.getScale()+ ST_tW_antitop_h->Integral()*LUMI*ST_tW_antitop.getScale()+ ST_tW_top_h->Integral()*LUMI*ST_tW_top.getScale()<<endl;
            // cout<<"TX           = "<<TGJets_h->Integral()*LUMI*TGJets.getScale()+ THW_h->Integral()*LUMI*THW.getScale()+ THQ_h->Integral()*LUMI*THQ.getScale()<<endl;
            // cout<<"DYJets       = "<<DYJetsToTauTau_h->Integral()*LUMI*DYJetsToTauTau.getScale()<<endl;
            // cout<<"VV           = "<<WZ_h->Integral()*LUMI*WZ.getScale()+ WW_h->Integral()*LUMI*WW.getScale()+ ZZ_h->Integral()*LUMI*ZZ.getScale()+ WGJets_h->Integral()*LUMI*WGJets.getScale()+ ZGJetsToLLG_h->Integral()*LUMI*ZGJetsToLLG.getScale()<<endl;
            // cout<<"VVV          = "<<WWW_h->Integral()*LUMI*WWW.getScale()+ WWZ_h->Integral()*LUMI*WWZ.getScale()+ WWG_h->Integral()*LUMI*WWG.getScale()+ ZZZ_h->Integral()*LUMI*ZZZ.getScale()+ WZZ_h->Integral()*LUMI*WZZ.getScale()+ WZG_h->Integral()*LUMI*WZG.getScale()+ WGG_h->Integral()*LUMI*WGG.getScale()+ ZGGJets_h->Integral()*LUMI*ZGGJets.getScale()<<endl;
            // cout<<"QCD          = "<<QCD_HT200to300_h->Integral()*LUMI*QCD_HT200to300.getScale()+ QCD_HT300to500_h->Integral()*LUMI*QCD_HT300to500.getScale()+ QCD_HT500to700_h->Integral()*LUMI*QCD_HT500to700.getScale()+ QCD_HT700to1000_h->Integral()*LUMI*QCD_HT700to1000.getScale()+ QCD_HT1000to1500_h->Integral()*LUMI*QCD_HT1000to1500.getScale()+ QCD_HT1500to2000_h->Integral()*LUMI*QCD_HT1500to2000.getScale()+ QCD_HT2000toInf_h->Integral()*LUMI*QCD_HT2000toInf.getScale()<<endl;

            cout<<"Total BKG    = "<<background_SR->Integral()<<endl;
            cout<<"\n";
        }
        //
        

       
        if ( ifDraw ){
            TCanvas* c1 = new TCanvas("c1","c1",0,0,600,600);
            TPad *c1_2 = new TPad("c1_2", "newpad",0.02,0.10,0.99,0.90);// bottom left point(),
            c1_2->Draw();
            c1_2->cd();

            background_SR->SetLineWidth(2);
            background_SR->SetLineColor(kBlue); 
            background_SR->SetMinimum(0);
            background_SR->SetMaximum(1.5 * background_SR->GetMaximum());
            background_SR->GetYaxis()->SetTitleSize(0.050);
            background_SR->GetXaxis()->SetTitleSize(0.050);
            background_SR->GetYaxis()->SetLabelSize(0.040);
            background_SR->GetXaxis()->SetLabelSize(0.040); 
            background_SR->SetTitle("");
            background_SR->GetYaxis()->SetTitle("Events");
            background_SR->GetXaxis()->SetTitle(axis[i]);
            background_SR->GetYaxis()->SetTitleOffset(1.00);
            background_SR->GetXaxis()->SetTitleOffset(0.85);//Set distance between the axis and the axis title
            background_SR->DrawNormalized("hist", 1);
            // background_SR->Draw("hist");
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


            //定义图中各个线和直方图的颜色
            TLegend *pl2 = new TLegend(0.65,0.60,0.91,0.91);
            pl2->SetTextSize(0.045); 
            pl2->SetFillColor(0);
          //  TLegendEntry *ple2 = pl2->AddEntry(data_SR, "data",  "L"); 
            TLegendEntry *ple2 = pl2->AddEntry(allHistos[0], "TTTT",  "L"); 
            pl2->Draw();
           
     
            TString NAME = variablelist[i];
            c1->SaveAs("/publicfs/cms/user/huahuil/TauOfTTTT/2016v1/plotsAndResults/test/"+NAME+postfix);
            
            cout<<"Finished "<<NAME+postfix<<endl;
            c1->Draw();

        } 



        //?for different range we have different sp, how to deal with this?
        if ( ifSP ){
            Double_t sp = separationPower(allHistos[0], background_SR);
            cout<<variablelist[i]<<" separation power"<<sp<<endl;
            std::cout << '\n';
            if(i==(variablelist.size()-1)) cout<<channelName[cha]<<endl;
            mymap.insert(std::make_pair(sp, variablelist[i]));
        }
        cout<<plot<<"done"<<endl;

        for(UInt_t j = 0; j < allHistos.size(); j++){
             delete (allHistos[j]);
        }

        delete background_SR;//put delete in the last
  }//end of loop of all variables



    if ( ifSP ){
        for (auto rit = mymap.crbegin(); rit != mymap.crend(); ++rit){
            std::cout <<  rit->second << " = "<< rit->first << endl;
            // std::cout << '\n';
        }
    }

	//how do we exactly include SYST in our histograms?

}//end of loop of all channels
    

    t.Stop();
    t.Print();
}


void getAllHitos( vector<TH1D*> &allHistos, TH1D* &background_SR, TString variable, Int_t bin, Double_t mini, Double_t maxi, TCut weight, TCut channelcut ){
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
    background_SR = new TH1D("BG", variable, bin, mini, maxi);

    TString hname ;
    Double_t scale;
    Double_t sumGenWeights = -99;
    for(UInt_t j = 0; j < allHistos.size(); j++){
    // for(UInt_t j = 0; j < 1; j++){
    // for(UInt_t j = 0; j < 4; j++){
        hname = allHistos[j]->GetName();
        
        // allProcesses[j].getEventTree()->Project hname, plot, weight);
        // allProcesses[j].getEventTree()->Project( hname, plot, weight*MetFilters);
        // allProcesses[j].getEventTree()->Project( hname, plot, weight*(MetFilters+trigger));
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
        // if(j > 0) background_SR->Add((allHistos[j]),1);
        if(j > 0) background_SR->Add((allHistos[j]),scale);
    }

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
