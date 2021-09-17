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
#define NBINSY 9



void DrawTrigEff2D(TString path, TString VAR, TString CAT, bool LOG, bool PRINT) {

gROOT->ForceStyle();  
gStyle->SetPaintTextFormat("1.3g"); 

TH2F * h;
TEfficiency  *MC;
TEfficiency  *MC_truth;
TEfficiency * DATA;
TFile * inputfile;

inputfile = TFile::Open(path);

map<string, float>::iterator xsec_it = xsec.begin();
std::string data = "data";
bool MC_is_read = false;
bool DATA_is_read = false;

while (xsec_it != xsec.end()) {
    
    if (xsec_it == xsec.begin()) {
        
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
            
            
            TH2F * totalWeight;
            std::string str_w("totalWeight_");
            str_w.append(xsec_it->first);
            totalWeight = (TH2F*)inputfile->Get(str_w.c_str());
            MC->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
            MC_truth->SetWeight(xsec_it->second*LUMI2016/totalWeight->Integral());
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
                
                
                TH2F * totalWeight;
                std::string str_w("totalWeight_");
                str_w.append(xsec_it->first);
                totalWeight = (TH2F*)inputfile->Get(str_w.c_str());
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
                
                TH2F * totalWeight;
                std::string str_w("totalWeight_");
                str_w.append(xsec_it->first);
                totalWeight = (TH2F*)inputfile->Get(str_w.c_str());
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
Float_t binsY[NBINSY+1] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

TH2F * hRatio = new TH2F ("hRatio", "hRatio", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY + 1; biny++) {
        
        float bincontent = MC->GetEfficiency(binx + 11*biny)/MC_truth->GetEfficiency(binx + 11*biny);
        if (!(isnan(bincontent))) hRatio->SetBinContent(binx, biny, bincontent);
        else continue;
        
        
    }
}

TH2F * hErrors = new TH2F ("hErrors", "hErrors", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY + 1; biny++) {
        
        float errorRef = sqrt(pow(MC->GetEfficiencyErrorUp(binx + 11*biny), 2) + pow(MC->GetEfficiencyErrorLow(binx + 11*biny),2));
        float errorTruth = sqrt(pow(MC_truth->GetEfficiencyErrorUp(binx + 11*biny), 2) + pow(MC_truth->GetEfficiencyErrorLow(binx + 11*biny),2));
        
        float bincontent = (errorRef/MC->GetEfficiency(binx + 11*biny) + errorTruth/MC_truth->GetEfficiency(binx + 11*biny)) * MC->GetEfficiency(binx + 11*biny)/MC_truth->GetEfficiency(binx + 11*biny);
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
        
        float bincontent = DATA->GetEfficiency(binx + 11*biny)/MC->GetEfficiency(binx + 11*biny);
        if (!(isnan(bincontent))) hRatioDATAMC->SetBinContent(binx, biny, bincontent);
        else continue;
        
        
    }
}

TH2F * hErrorsDATA = new TH2F ("hErrorsDATA", "hErrorsDATA", NBINSX, binsX, NBINSY, binsY);
TH2F * hErrorsMC = new TH2F ("hErrorsMC", "hErrorsMC", NBINSX, binsX, NBINSY, binsY);
TH2F * hErrorsDATAMC = new TH2F ("hErrorsDATAMC", "hErrorsDATAMC", NBINSX, binsX, NBINSY, binsY);

for (int binx = 1; binx < NBINSX + 1; binx++) {
    
    for (int biny = 1; biny < NBINSY +1; biny++) {
        
        float errorDATA = std::max(DATA->GetEfficiencyErrorUp(binx + 11*biny), DATA->GetEfficiencyErrorLow(binx + 11*biny));
//         errorDATA = (DATA->GetEfficiencyErrorUp(binx + 11*biny)+ DATA->GetEfficiencyErrorLow(binx + 11*biny))/2.0;
        float errorMC = std::max(MC->GetEfficiencyErrorUp(binx + 11*biny), MC->GetEfficiencyErrorLow(binx + 11*biny));
//         errorMC = (MC->GetEfficiencyErrorUp(binx + 11*biny), MC->GetEfficiencyErrorLow(binx + 11*biny))/2.0;
        float bincontent = (errorDATA/DATA->GetEfficiency(binx + 11*biny) + errorMC/MC->GetEfficiency(binx + 11*biny)) * DATA->GetEfficiency(binx + 11*biny)/MC->GetEfficiency(binx + 11*biny);
        /*if(!isnan(errorDATA))*/if (!(isnan(bincontent))) hErrorsDATA->SetBinContent(binx, biny, errorDATA);
        /*if(!isnan(errorMC))*/ if (!(isnan(bincontent)))hErrorsMC->SetBinContent(binx, biny, errorMC);
        
        
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
    can->SaveAs("plots/vsHTj_TEfficiency_fullBkgAndData_2jetspresel/e_"+VAR+"_"+CAT+".png"); 
    can8->SaveAs("plots/vsHTj_TEfficiency_fullBkgAndData_2jetspresel/ratioDATAMC.png");
    can9->SaveAs("plots/vsHTj_TEfficiency_fullBkgAndData_2jetspresel/ratioDATAMCerrors.png");
  }
 
TFile *outputfile = new TFile( "TriggerSF_2D.root", "RECREATE" );
hRatioDATAMC->Write("SF_njetsVsHT");
hErrorsDATAMC->Write("SF_njetsVsHTerrors");
outputfile->Close();
 
}
 
 
