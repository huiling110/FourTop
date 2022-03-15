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

#define NBINSX 9
#define NBINSY 8



void DrawTrigEff2D(string YEAR, TString VAR, TString CAT, bool LOG, bool PRINT) {

gROOT->ForceStyle();  
gStyle->SetPaintTextFormat("1.3g"); 
gROOT->SetBatch(kTRUE);
TH2F * h;
TEfficiency  *MC;
TEfficiency  *MC_truth;
TEfficiency * DATA;
TFile * inputfile;

inputfile = TFile::Open(TString(input[YEAR]));

map<string, float>::iterator xsec_it = xsec[YEAR].begin();
std::string data = "data";
bool MC_is_read = false;
bool DATA_is_read = false;

 while (xsec_it != xsec[YEAR].end()) {
     
     if (xsec_it == xsec[YEAR].begin()) {
        
        if (!(xsec_it->first.find(data) !=std::string::npos)) {
            MC_is_read = true;
            std::string str_h("h_"+VAR+"_"+CAT+"_");
            str_h.append(xsec_it->first);
            h = (TH2F*)inputfile->Get(str_h.c_str());
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
            MC->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
            MC_truth->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
            delete totalWeight;
        }//end if MC
        
        else {
            DATA_is_read = true;
            std::string str_h("h_"+VAR+"_"+CAT+"_");
            str_h.append(xsec_it->first);
            h = (TH2F*)inputfile->Get(str_h.c_str());
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
                h = (TH2F*)inputfile->Get(str_h.c_str());
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
                MC->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
                MC_truth->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
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
                eMC->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
                eMCt->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
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
                h = (TH2F*)inputfile->Get(str_h.c_str());
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


  
TCanvas* can= new TCanvas(VAR+"_"+CAT+"_MCref",VAR+"_"+CAT+"_MCref", 900, 600);
can->SetRightMargin(0.15);
MC->Draw("coltextz");
gPad->Update();


TCanvas* can2= new TCanvas(VAR+"_"+CAT+"_MCtruth",VAR+"_"+CAT+"_MCtruth", 900, 600);
can2->SetRightMargin(0.15);
MC_truth->Draw("coltextz");
gPad->Update();

Float_t binsX[NBINSX+1] = {0, 100, 200, 300, 400, 500, 600, 800, 1100, 1500};
//Float_t binsY[NBINSY+1] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
Float_t binsY[NBINSY+1] = {2, 4, 5, 6, 7, 8, 9, 11, 13};

TH2F * hRatio = new TH2F ("hRatio", "hRatio", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY + 1; biny++) {
        
        float bincontent = MC->GetEfficiency(binx + (NBINSX+2)*biny)/MC_truth->GetEfficiency(binx + (NBINSX+2)*biny);
        if (!(isnan(bincontent))) hRatio->SetBinContent(binx, biny, bincontent);
        else continue;
        
        
    }
}

TH2F * hErrors = new TH2F ("hErrors", "hErrors", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY + 1; biny++) {
        
        float errorRef = sqrt(pow(MC->GetEfficiencyErrorUp(binx + (NBINSX+2)*biny), 2) + pow(MC->GetEfficiencyErrorLow(binx + (NBINSX+2)*biny),2));
        float errorTruth = sqrt(pow(MC_truth->GetEfficiencyErrorUp(binx + (NBINSX+2)*biny), 2) + pow(MC_truth->GetEfficiencyErrorLow(binx + (NBINSX+2)*biny),2));
        
        float bincontent = (errorRef/MC->GetEfficiency(binx + (NBINSX+2)*biny) + errorTruth/MC_truth->GetEfficiency(binx + (NBINSX+2)*biny)) * MC->GetEfficiency(binx + (NBINSX+2)*biny)/MC_truth->GetEfficiency(binx + (NBINSX+2)*biny);
        if (!(isnan(bincontent))) hErrors->SetBinContent(binx, biny, bincontent);
        else continue;
        
        
    }
}

TCanvas* can3= new TCanvas(VAR+"_"+CAT+"_ratioMCrefMCtruth",VAR+"_"+CAT+"_ratioMCrefMCtruth", 900, 600);
can3->SetRightMargin(0.15);

hRatio->SetXTitle("H_{T,j} [GeV]");
hRatio->SetYTitle("Jet multiplicity");
hRatio->Draw("coltextz");

TCanvas* can4= new TCanvas(VAR+"_"+CAT+"_ratioMCrefMCtrutherrors",VAR+"_"+CAT+"_ratioMCrefMCtrutherrors", 900, 600);
can4->SetRightMargin(0.15);

hErrors->SetXTitle("H_{T,j} [GeV]");
hErrors->SetYTitle("Jet multiplicity");
hErrors->Draw("coltextz");

TCanvas* can5= new TCanvas(VAR+"_"+CAT+"_DATA",VAR+"_"+CAT+"_DATA", 900, 600);
can5->SetRightMargin(0.15);
DATA->Draw("coltextz");

TH2F * hRatioDATAMC = new TH2F ("hRatioDATAMC", "hRatioDATAMC", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY + 1; biny++) {
        
        float bincontent = DATA->GetEfficiency(binx + (NBINSX+2)*biny)/MC->GetEfficiency(binx + (NBINSX+2)*biny);
        if (!(isnan(bincontent))) hRatioDATAMC->SetBinContent(binx, biny, bincontent);
        else continue;
        
        
    }
}

TH2F * hErrorsDATA = new TH2F ("hErrorsDATA", "hErrorsDATA", NBINSX, binsX, NBINSY, binsY);
TH2F * hErrorsMC = new TH2F ("hErrorsMC", "hErrorsMC", NBINSX, binsX, NBINSY, binsY);
TH2F * hErrorsDATAMC = new TH2F ("hErrorsDATAMC", "hErrorsDATAMC", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY +1; biny++) {
        
        //take the biggest uncertainty...
        float errorDATA = std::max(DATA->GetEfficiencyErrorUp(binx + (NBINSX+2)*biny), DATA->GetEfficiencyErrorLow(binx + (NBINSX+2)*biny));
        //...unless it's bigger than the efficiency value itself
        if (DATA->GetEfficiency(binx + (NBINSX+2)*biny) - errorDATA < 0) errorDATA = std::min(DATA->GetEfficiencyErrorUp(binx + (NBINSX+2)*biny), DATA->GetEfficiencyErrorLow(binx + (NBINSX+2)*biny));

        //take the biggest uncertainty...
        float errorMC = std::max(MC->GetEfficiencyErrorUp(binx + (NBINSX+2)*biny), MC->GetEfficiencyErrorLow(binx + (NBINSX+2)*biny));
        //...unless it's bigger than the efficiency value itself
        if (MC->GetEfficiency(binx + (NBINSX+2)*biny) - errorMC < 0) errorMC = std::min(MC->GetEfficiencyErrorUp(binx + (NBINSX+2)*biny), MC->GetEfficiencyErrorLow(binx + (NBINSX+2)*biny));

        float bincontent = (errorDATA/DATA->GetEfficiency(binx + (NBINSX+2)*biny) + errorMC/MC->GetEfficiency(binx + (NBINSX+2)*biny)) * DATA->GetEfficiency(binx + (NBINSX+2)*biny)/MC->GetEfficiency(binx + (NBINSX+2)*biny);

        if(!isnan(errorDATA) && !(DATA->GetEfficiency(binx + (NBINSX+2)*biny) == 0))/*if (!(isnan(bincontent)))*/ hErrorsDATA->SetBinContent(binx, biny, errorDATA); //when data effciency is 0, error is 1, exclude these cases
        if(!isnan(errorMC))/*if (!(isnan(bincontent)))*/ hErrorsMC->SetBinContent(binx, biny, errorMC);
        
        
        if (!(isnan(bincontent))) {
            
            hErrorsDATAMC->SetBinContent(binx, biny, bincontent);
            hRatioDATAMC->SetBinError(binx, biny, bincontent);
        }
        else continue;
        
        
    }
}

TCanvas* can6= new TCanvas(VAR+"_"+CAT+"_errorsDATA",VAR+"_"+CAT+"_errorsDATA", 900, 600);
can6->SetRightMargin(0.15);
hErrorsDATA->SetXTitle("H_{T,j} [GeV]");
hErrorsDATA->SetYTitle("Jet multiplicity");
hErrorsDATA->Draw("coltextz");

TCanvas* can7= new TCanvas(VAR+"_"+CAT+"_errorsMC",VAR+"_"+CAT+"_errorsMC", 900, 600);
can7->SetRightMargin(0.15);
hErrorsMC->SetXTitle("H_{T,j} [GeV]");
hErrorsMC->SetYTitle("Jet multiplicity");
hErrorsMC->Draw("coltextz");

TCanvas* can8= new TCanvas(VAR+"_"+CAT+"_ratioDATAMC",VAR+"_"+CAT+"_ratioDATAMC", 900, 600);
can8->SetRightMargin(0.15);
hRatioDATAMC->SetXTitle("H_{T,j} [GeV]");
hRatioDATAMC->SetYTitle("Jet multiplicity");
hRatioDATAMC->Draw("coltextz");

TCanvas* can9= new TCanvas(VAR+"_"+CAT+"_ratioDATAMCerrors",VAR+"_"+CAT+"_ratioDATAMCerrors", 900, 600);
can9->SetRightMargin(0.15);

hErrorsDATAMC->SetXTitle("H_{T,j} [GeV]");
hErrorsDATAMC->SetYTitle("Jet multiplicity");
hErrorsDATAMC->Draw("coltextz");


if (PRINT) {//save plots
    can->SaveAs("plots_PFJet500/"+TString(YEAR)+"/e_"+VAR+"_"+CAT+"_MC_"+TString(YEAR)+".png");
    can2->SaveAs("plots_PFJet500/"+TString(YEAR)+"/e_"+VAR+"_"+CAT+"_MCtruth_"+TString(YEAR)+".png");
    can3->SaveAs("plots_PFJet500/"+TString(YEAR)+"/ratioMCrefMCtruth_"+VAR+"_"+CAT+"_"+TString(YEAR)+".png");
    can4->SaveAs("plots_PFJet500/"+TString(YEAR)+"/ratioMCrefMCtruthErrors_"+VAR+"_"+CAT+"_"+TString(YEAR)+".png");
    can5->SaveAs("plots_PFJet500/"+TString(YEAR)+"/e_"+VAR+"_"+CAT+"_DATA_"+TString(YEAR)+".png");
    can6->SaveAs("plots_PFJet500/"+TString(YEAR)+"/e_"+VAR+"_"+CAT+"_DATAerrors_"+TString(YEAR)+".png");
    can7->SaveAs("plots_PFJet500/"+TString(YEAR)+"/e_"+VAR+"_"+CAT+"_MCerrors_"+TString(YEAR)+".png");
    can8->SaveAs("plots_PFJet500/"+TString(YEAR)+"/ratioDATAMC_"+TString(YEAR)+".png");
    can9->SaveAs("plots_PFJet500/"+TString(YEAR)+"/ratioDATAMCerrors"+TString(YEAR)+".png");
  }
 
 TFile *outputfile = new TFile( "TriggerSF_2D_"+TString(YEAR)+".root", "RECREATE" );
 hRatioDATAMC->Write("SF_njetsVsHT_"+TString(YEAR));
 hErrorsDATAMC->Write("SF_njetsVsHTerrors_"+TString(YEAR));
 outputfile->Close();
 
}
 
 
