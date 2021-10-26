#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "TCanvas.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TString.h>
#include <TCanvas.h>
#include <TEfficiency.h>
#include <TLatex.h>
#include <TROOT.h>
#include <iostream>
#include <TSystem.h>
#include <TROOT.h>
#include<iomanip>
#include<fstream>
#include<stdio.h>
#include<THStack.h>
#include "/home/fabio/CMS/ttH/newTraining/analysis_2018/higgsMassRange70to270/CMS_lumi.C"
#include "DrawTrigEff.h"


void DrawTrigEff(TString path, TString VAR, TString CAT, bool LOG, bool plot_sig_only, TFile *outputfile, bool PRINT) {

gROOT->ForceStyle();  
gStyle->SetPaintTextFormat("1.3g"); 

TH1F * h;
TEfficiency  *MC;
TEfficiency  *MC_truth;
TEfficiency  *SIG;
TEfficiency  *SIG_truth;
TEfficiency * DATA;
TFile * inputfile;
TH1F * HT;
TH1F * njets;

inputfile = TFile::Open(path);

HT = (TH1F*)inputfile->Get("h_HT_signal");
njets = (TH1F*)inputfile->Get("h_njets_signal");

map<string, float>::iterator xsec_it = xsec.begin();
std::string data = "data";
std::string tttt = "tttt";
bool MC_is_read = false;
bool DATA_is_read = false;

while (xsec_it != xsec.end()) {
    
    if (xsec_it->first.find(tttt) !=std::string::npos) {//get TEfficiency objects for signal only in order to plot them
        
        std::string str_e("e_"+VAR+"_"+CAT+"_");
        str_e.append(xsec_it->first);
        std::string str_et("e_"+VAR+"_"+CAT+"_truth_");
        str_et.append(xsec_it->first);
        SIG = (TEfficiency*)inputfile->Get(str_e.c_str());
        SIG_truth = (TEfficiency*)inputfile->Get(str_et.c_str());
        
    }
    
    if (xsec_it == xsec.begin()) {
        
        if (!(xsec_it->first.find(data) !=std::string::npos)) {
            MC_is_read = true;
            std::string str_h("h_"+VAR+"_"+CAT+"_");
            str_h.append(xsec_it->first);
            h = (TH1F*)inputfile->Get(str_h.c_str());
            std::string str_e("e_"+VAR+"_"+CAT+"_");
            str_e.append(xsec_it->first);
            std::string str_et("e_"+VAR+"_"+CAT+"_truth_");
            str_et.append(xsec_it->first);
            MC = (TEfficiency*)inputfile->Get(str_e.c_str());
            MC_truth = (TEfficiency*)inputfile->Get(str_et.c_str());
            
            
            TH1F * totalWeight;
            std::string str_w("totalWeight_");
            str_w.append(xsec_it->first);
            totalWeight = (TH1F*)inputfile->Get(str_w.c_str());
            MC->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
            MC_truth->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
            delete totalWeight;
        }//end if MC
        
        else {
            DATA_is_read = true;
            std::string str_h("h_"+VAR+"_"+CAT+"_");
            str_h.append(xsec_it->first);
            h = (TH1F*)inputfile->Get(str_h.c_str());
            std::string str_e("e_"+VAR+"_"+CAT+"_");
            str_e.append(xsec_it->first);
            DATA = (TEfficiency*)inputfile->Get(str_e.c_str());
        }//end if DATA
        
        
    }//end at the beginning of loop
    
    else {
        
        if (!(xsec_it->first.find(data) !=std::string::npos)) {
            
            if (!MC_is_read) {
                MC_is_read = true;
                std::string str_h("h_"+VAR+"_"+CAT+"_");
                str_h.append(xsec_it->first);
                h = (TH1F*)inputfile->Get(str_h.c_str());
                std::string str_e("e_"+VAR+"_"+CAT+"_");
                str_e.append(xsec_it->first);
                std::string str_et("e_"+VAR+"_"+CAT+"_truth_");
                str_et.append(xsec_it->first);
                MC = (TEfficiency*)inputfile->Get(str_e.c_str());
                MC_truth = (TEfficiency*)inputfile->Get(str_et.c_str());
                
                
                TH1F * totalWeight;
                std::string str_w("totalWeight_");
                str_w.append(xsec_it->first);
                totalWeight = (TH1F*)inputfile->Get(str_w.c_str());
                MC->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
                MC_truth->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
                delete totalWeight;
            }//end if first MC file
            
            else {
                TEfficiency * eMC;
                TEfficiency * eMCt;
                std::string str_e("e_"+VAR+"_"+CAT+"_");
                str_e.append(xsec_it->first);
                std::string str_et("e_"+VAR+"_"+CAT+"_truth_");
                str_et.append(xsec_it->first);
                eMC = (TEfficiency*)inputfile->Get(str_e.c_str());
                eMCt = (TEfficiency*)inputfile->Get(str_et.c_str());
                
                TH1F * totalWeight;
                std::string str_w("totalWeight_");
                str_w.append(xsec_it->first);
                totalWeight = (TH1F*)inputfile->Get(str_w.c_str());
                eMC->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
                eMCt->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
                MC->Add(*eMC);
                MC_truth->Add(*eMCt);
                delete totalWeight;
                delete eMC;
                delete eMCt;
            }//end if not first MC file
            
        }//end if is MC
        
        else {
            
            if(!DATA_is_read) {
                DATA_is_read = true;
                std::string str_h("h_"+VAR+"_"+CAT+"_");
                str_h.append(xsec_it->first);
                h = (TH1F*)inputfile->Get(str_h.c_str());
                std::string str_e("e_"+VAR+"_"+CAT+"_");
                str_e.append(xsec_it->first);
                DATA = (TEfficiency*)inputfile->Get(str_e.c_str());
            }//end if first DATA file
            
            else {
                TEfficiency * eData;
                std::string str_e("e_"+VAR+"_"+CAT+"_");
                str_e.append(xsec_it->first);
                eData = (TEfficiency*)inputfile->Get(str_e.c_str());
                eData->SetWeight(1.0);
                DATA->Add(*eData);
            }//end if not first DATA file
            
        }//end if DATA
    }//end not at beginning of loop
    xsec_it++;
}//end loop over processes

TLegend * legend = new TLegend(0.40,0.28,0.50,0.48, "", "NDC"); 
legend->SetFillColor(0);
legend->SetBorderSize(0);
legend->SetTextFont(42);
legend->SetTextSize(0.035);
if (!plot_sig_only){
    legend->AddEntry(MC, "MC (ref: HLT_IsoMu24 || 27)", "l");
    legend->AddEntry(MC_truth, "MC (truth)", "l");
}
else {
    
    legend->AddEntry(SIG, "t#bar{t}t#bar{t} (ref: HLT_IsoMu24 || 27)", "l");
    legend->AddEntry(SIG_truth, "t#bar{t}t#bar{t} (truth)", "l");
}
if (!plot_sig_only) legend->AddEntry(DATA, "2016 data (ref: HLT_IsoMu24 || 27)", "p");
if (VAR == "HT" && !plot_sig_only) legend->AddEntry(HT, "t#bar{t}t#bar{t}", "l");

TCanvas* can;
if (!plot_sig_only) can= new TCanvas(VAR+"_"+CAT,VAR+"_"+CAT, 900, 600);
else can= new TCanvas(VAR+"_"+CAT+"_signal",VAR+"_"+CAT+"_signal", 900, 600);
if(!plot_sig_only) {
    can->SetRightMargin(0.15);
    can->SetBottomMargin(0.25);
}

if (VAR == "HT") {
    
    MC->SetTitle("; H_{T,j} [GeV]; Efficiency / binwidth [GeV]");
    SIG->SetTitle("; H_{T,j} [GeV]; Efficiency / binwidth [GeV]");
    
}

if (VAR == "njets") {
    
    MC->SetTitle("; Jet multiplicity; Efficiency / 1 bin");
    SIG->SetTitle("; Jet multiplicity; Efficiency / 1 bin");
} 

TF1 *F0;
if (!plot_sig_only) {
MC->SetLineColor(kGreen-3);
MC->SetLineWidth(3);
//MC->SetMinimum(0.0);
//MC->SetMaximum(2.0);
MC->Draw("");
gPad->Update();
MC->GetPaintedGraph()->GetXaxis()->SetTitleOffset(2.2);
MC->GetPaintedGraph()->GetXaxis()->SetLabelOffset(0.13);
MC->GetPaintedGraph()->SetMinimum(0.0);
MC->GetPaintedGraph()->SetMaximum(1.1);
if (VAR == "HT") MC->GetPaintedGraph()->GetXaxis()->SetLimits(0, 1500);
if (VAR == "njets") MC->GetPaintedGraph()->GetXaxis()->SetLimits(0, 15);

MC_truth->SetLineColor(kRed);
MC_truth->SetLineWidth(2);
MC_truth->Draw("same");
gPad->Update();
MC_truth->GetPaintedGraph()->GetXaxis()->SetTitleOffset(2.2);
MC_truth->GetPaintedGraph()->GetXaxis()->SetLabelOffset(0.13);
if (VAR == "HT") MC_truth->GetPaintedGraph()->GetXaxis()->SetLimits(0, 1500);
if (VAR == "njets") MC_truth->GetPaintedGraph()->GetXaxis()->SetLimits(0, 15);

DATA->SetMarkerStyle(20);
DATA->Draw("same");
gPad->Update();
DATA->GetPaintedGraph()->GetXaxis()->SetTitleOffset(2.2);
DATA->GetPaintedGraph()->GetXaxis()->SetLabelOffset(0.13);
if (VAR == "HT") DATA->GetPaintedGraph()->GetXaxis()->SetLimits(0, 1500);
if (VAR == "njets") DATA->GetPaintedGraph()->GetXaxis()->SetLimits(0, 15);

if (VAR == "HT") {
    
    TLine *line = new TLine(0,1.0,1500,1.0);
    line->SetLineColor(kBlack);
    line->SetLineWidth(1);
    line->SetLineStyle(kDashed);
    line->Draw();
    gPad->Update();
    
}

if (VAR == "njets") {
    
    TLine *line = new TLine(0,1.0,15,1.0);
    line->SetLineColor(kBlack);
    line->SetLineWidth(1);
    line->SetLineStyle(kDashed);
    line->Draw();
    gPad->Update();
    
}

if (VAR == "HT") {
    
//     HT->Scale(1/HT->Integral());
    Float_t rightmax = 1.1*HT->GetMaximum();
    Float_t scale = gPad->GetUymax()/rightmax;
    HT->Scale(scale);
    HT->SetLineColor(kBlue);
    HT->SetLineWidth(1);
    HT->Draw("histosame");
    
    TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(), 0, rightmax, 505, "+L");
    axis->SetLineColor(kBlue);
    axis->SetTextColor(kBlue);
    axis->SetLabelColor(kBlue);
    axis->Draw();
    
}
/*
if (VAR == "njets") {
    
//     njets->Scale(1/HT->Integral());
    Float_t rightmax = 1.1*njets->GetMaximum();
    Float_t scale = gPad->GetUymax()/rightmax;
    njets->Scale(scale);
    njets->SetLineColor(kBlue);
    njets->SetLineWidth(2);
    njets->Draw("histosame");
    
    TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(), 0, rightmax, 505, "+L");
    axis->SetLineColor(kBlue);
    axis->SetTextColor(kBlue);
    axis->SetLabelColor(kBlue);
    axis->Draw();
    
}
// */

int nbins = h->GetSize() - 2;
Float_t xmin = h->GetXaxis()->GetXmin();
Float_t xmax = h->GetXaxis()->GetXmax();
Float_t width;
const TArrayD * bin_edges;
Float_t binwidth[nbins];
Float_t histobins[nbins+1]; 

if (VAR == "HT") {
    
bin_edges = h->GetXaxis()->GetXbins();

for (int i = 0; i < nbins+1; i++) {
    
    if (i < nbins) binwidth[i] = bin_edges->At(i+1) - bin_edges->At(i);
    histobins[i] = bin_edges->At(i);

}    

}

if (VAR == "njets") {
    
width = (xmax - xmin)/nbins;

for (int i = 0; i < nbins+1; i++) {
    
    if (i < nbins) binwidth[i] = width;
    histobins[i] = width*i;
    
}
    
}


Float_t px[nbins]; 
Float_t py[nbins];
Float_t exl[nbins];
Float_t exr[nbins];
Float_t eyl[nbins];
Float_t eyh[nbins];

TH1F * hRatio = new TH1F("hRatio", "", nbins, histobins);

for (int i = 0; i < nbins; i++){
    
    if (VAR == "HT") px[i] = bin_edges->At(i+1) - (bin_edges->At(i+1) - bin_edges->At(i))/2.0;
    if (VAR == "njets") px[i] = binwidth[i]/2 + binwidth[i]*i;
    exl[i] = binwidth[i]/2;
    exr[i] = binwidth[i]/2;
    
   if(MC->GetEfficiency(i+1) != 0) {
       
       py[i] =  DATA->GetEfficiency(i+1)/MC->GetEfficiency(i+1);
       
       hRatio->SetBinContent(i+1, DATA->GetEfficiency(i+1)/MC->GetEfficiency(i+1));
//        cout << hRatio->GetBinContent(i+1) << endl;
       
       eyl[i] = 1.0*( MC->GetEfficiencyErrorLow(i+1)/MC->GetEfficiency(i+1) + DATA->GetEfficiencyErrorLow(i+1)/DATA->GetEfficiency(i+1) ) * DATA->GetEfficiency(i+1)/MC->GetEfficiency(i+1);
       
       eyh[i] = 1.0*( MC->GetEfficiencyErrorUp(i+1)/MC->GetEfficiency(i+1) + DATA->GetEfficiencyErrorUp(i+1)/DATA->GetEfficiency(i+1) ) * DATA->GetEfficiency(i+1)/MC->GetEfficiency(i+1);
    }
   
    else {
       
        py[i] = 0;
        hRatio->SetBinContent(i+1, 0);
        eyl[i] = 0;
        eyh[i] = 0;
            
    }
    
    
}

TGraphAsymmErrors* Ratio = new TGraphAsymmErrors(nbins, px, py, exl, exr, eyl, eyh);
  
//in order for the TGraph to appear like a histogram (without the lines connecting each bin content) draw a histogram under the TGraph and then plot the TGraph
    TPad *pad = new TPad("pad","pad",0.,0.,1.,1.);
    pad->SetTopMargin(0.77);
    pad->SetRightMargin(0.15);
    pad->SetFillColor(0);
    pad->SetFillStyle(0);
    pad->Draw();
    gPad->Update();
    pad->cd(0);
    pad->SetGridy();
    hRatio->SetYTitle("data/MC");
    hRatio->GetXaxis()->SetLabelSize(0.0);
    hRatio->GetYaxis()->SetTitleSize(0.03);
    hRatio->GetYaxis()->SetLabelSize(0.03);
    if (VAR == "HT") hRatio->GetXaxis()->SetRangeUser(0, 1500);
    if (VAR == "njets") hRatio->GetXaxis()->SetRangeUser(0, 15);
    hRatio->GetYaxis()->SetRangeUser(0.4, 1.6);
    hRatio->GetYaxis()->SetNdivisions(505);
    hRatio->Draw("p");
    Ratio->Draw("p");
    if (VAR == "HT") F0 = new TF1("F0","[0]+ x*[1]",400,1500);
    if (VAR == "njets") F0 = new TF1("F0","[0] + x*[1]",4,15);
//     TF1 *F1 = new TF1("F1","[0] + x*[1]",400,1500);
//     TF1 *F2 = new TF1("F2","[0] + x*[1] + x*x*[2]",400,1500);
//     TF1 *F3 = new TF1("F3","[0] + x*[1] + x*x*[2] + x*x*x*[3]",0,1500);
    Ratio->Fit("F0", "R");
    gPad->Update();
}

else {
    
    SIG->SetLineColor(kGreen-3);
    SIG->SetLineWidth(3);
    //SIG->SetMinimum(0.0);
    //SIG->SetMaximum(2.0);
    SIG->Draw("");
    gPad->Update();
//     SIG->GetPaintedGraph()->GetXaxis()->SetTitleOffset(2.2);
//     SIG->GetPaintedGraph()->GetXaxis()->SetLabelOffset(0.13);
    SIG->GetPaintedGraph()->SetMinimum(0.0);
    SIG->GetPaintedGraph()->SetMaximum(1.1);
    if (VAR == "HT") SIG->GetPaintedGraph()->GetXaxis()->SetLimits(0, 1500);
    if (VAR == "njets") SIG->GetPaintedGraph()->GetXaxis()->SetLimits(0, 15);

    SIG_truth->SetLineColor(kRed);
    SIG_truth->SetLineWidth(2);
    SIG_truth->Draw("same");
    gPad->Update();
/*    SIG_truth->GetPaintedGraph()->GetXaxis()->SetTitleOffset(2.2);
    SIG_truth->GetPaintedGraph()->GetXaxis()->SetLabelOffset(0.13)*/;
    if (VAR == "HT") SIG_truth->GetPaintedGraph()->GetXaxis()->SetLimits(0, 1500);
    if (VAR == "njets") SIG_truth->GetPaintedGraph()->GetXaxis()->SetLimits(0, 15);  
    
    if (VAR == "HT") {
    
    TLine *line = new TLine(0,1.0,1500,1.0);
    line->SetLineColor(kBlack);
    line->SetLineWidth(1);
    line->SetLineStyle(kDashed);
    line->Draw();
    gPad->Update();
    
}

if (VAR == "njets") {
    
    TLine *line = new TLine(0,1.0,15,1.0);
    line->SetLineColor(kBlack);
    line->SetLineWidth(1);
    line->SetLineStyle(kDashed);
    line->Draw();
    gPad->Update();
    
}
    
}

if (LOG == true) gPad->SetLogy();

legend->Draw();

if (PRINT) {//save plots
    can->SaveAs("plots/vsHTj_TEfficiency_fullBkgAndData_2jetspresel/e_"+VAR+"_"+CAT+".png"); 
  }
  
outputfile->cd();

if (VAR == "HT" && CAT == "nocat" && !plot_sig_only) {
      
    F0->Write("SF_HT_"+CAT);
    DATA->Write("e_HT_nocat_DATA");
    MC->Write("e_HT_nocat_MC");  
}

if (VAR == "njets" && CAT == "nocat" && !plot_sig_only) {
      
    F0->Write("SF_njets_"+CAT);
    DATA->Write("e_njets_nocat_DATA");
    MC->Write("e_njets_nocat_MC");
      
}
//     outputfile->Close();
}
 
