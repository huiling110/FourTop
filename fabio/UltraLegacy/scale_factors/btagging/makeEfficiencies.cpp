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

#include "makeEfficiencies.h"
#include "../../tools/debug.cpp"

#define NBINSX 3
#define NBINSY 8



void makeEfficiencies (string YEAR) {
Double_t * binsX = new Double_t[NBINSX+1];
 binsX[0] = 0.0;
 binsX[1] = 0.8;
 binsX[2] = 1.6;
 binsX[3] = 2.4;
Double_t * binsY = new Double_t[NBINSY+1];
 binsY[0] = 20;
 binsY[1] = 30;
 binsY[2] = 50;
 binsY[3] = 70;
 binsY[4] = 100;
 binsY[5] = 140;
 binsY[6] = 300;
 binsY[7] = 600;
 binsY[8] = 1000;

TEfficiency btagEff_b_tttt("btagEff_b_tttt", "btagEff_b_tttt", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_c_tttt("btagEff_c_tttt", "btagEff_c_tttt", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_udsg_tttt("btagEff_udsg_tttt", "btagEff_udsg_tttt", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_b_ttbar("btagEff_b_ttbar", "btagEff_b_ttbar", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_c_ttbar("btagEff_c_ttbar", "btagEff_c_ttbar", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_udsg_ttbar("btagEff_udsg_ttbar", "btagEff_udsg_ttbar", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_b_QCD("btagEff_b_QCD", "btagEff_b_QCD", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_c_QCD("btagEff_c_QCD", "btagEff_c_QCD", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_udsg_QCD("btagEff_udsg_QCD", "btagEff_udsg_QCD", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_b_ttX("btagEff_b_ttX", "btagEff_b_ttX", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_c_ttX("btagEff_c_ttX", "btagEff_c_ttX", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_udsg_ttX("btagEff_udsg_ttX", "btagEff_udsg_ttX", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_b_ST("btagEff_b_ST", "btagEff_b_ST", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_c_ST("btagEff_c_ST", "btagEff_c_ST", NBINSX,binsX,NBINSY,binsY);
TEfficiency btagEff_udsg_ST("btagEff_udsg_ST", "btagEff_udsg_ST", NBINSX,binsX,NBINSY,binsY);
TFile *inputfile;

inputfile = TFile::Open(TString(input[YEAR]));

map<string, float>::iterator xsec_it = xsec[YEAR].begin();
std::string data = "data";
bool tttt_is_read = false;
bool ttbar_is_read = false;
bool QCD_is_read = false;
bool ttX_is_read = false;
bool ST_is_read = false;
 while (xsec_it != xsec[YEAR].end()) {
     
     if (xsec_it == xsec[YEAR].begin()) {
        
         if (xsec_it->first.find("tttt") !=std::string::npos) loadTEfficiency(inputfile, YEAR, tttt_is_read, xsec_it, btagEff_b_tttt, btagEff_c_tttt, btagEff_udsg_tttt);
         if (xsec_it->first.find("ttbar") !=std::string::npos) loadTEfficiency(inputfile, YEAR, ttbar_is_read, xsec_it, btagEff_b_ttbar, btagEff_c_ttbar, btagEff_udsg_ttbar);
         if (xsec_it->first.find("QCD") !=std::string::npos) loadTEfficiency(inputfile, YEAR, QCD_is_read, xsec_it, btagEff_b_QCD, btagEff_c_QCD, btagEff_udsg_QCD);
         if (xsec_it->first.find("+jets") !=std::string::npos || xsec_it->first.find("ttH") !=std::string::npos) loadTEfficiency(inputfile, YEAR, ttX_is_read, xsec_it, btagEff_b_ttX, btagEff_c_ttX, btagEff_udsg_ttX);
         if (xsec_it->first.find("st_") !=std::string::npos) loadTEfficiency(inputfile, YEAR, ST_is_read, xsec_it, btagEff_b_ST, btagEff_c_ST, btagEff_udsg_ST);
         
    }//end at the beginning of loop
     
    else {
        
        if (xsec_it->first.find("tttt") !=std::string::npos) {
            
            if (!tttt_is_read) loadTEfficiency(inputfile, YEAR, tttt_is_read, xsec_it, btagEff_b_tttt, btagEff_c_tttt, btagEff_udsg_tttt);
            else addTEfficiency(inputfile, YEAR, xsec_it, btagEff_b_tttt, btagEff_c_tttt, btagEff_udsg_tttt);
            
        }
        
        if (xsec_it->first.find("ttbar") !=std::string::npos) {
            
            if (!ttbar_is_read) loadTEfficiency(inputfile, YEAR, ttbar_is_read, xsec_it, btagEff_b_ttbar, btagEff_c_ttbar, btagEff_udsg_ttbar);
            else addTEfficiency(inputfile, YEAR, xsec_it, btagEff_b_ttbar, btagEff_c_ttbar, btagEff_udsg_ttbar);
            
        }
        
        if (xsec_it->first.find("QCD") !=std::string::npos) {
            
            if (!QCD_is_read) loadTEfficiency(inputfile, YEAR, QCD_is_read, xsec_it, btagEff_b_QCD, btagEff_c_QCD, btagEff_udsg_QCD);
            else addTEfficiency(inputfile, YEAR, xsec_it, btagEff_b_QCD, btagEff_c_QCD, btagEff_udsg_QCD);
            
        }
        
        if (xsec_it->first.find("+jets") !=std::string::npos || xsec_it->first.find("ttH")  !=std::string::npos) {
            
            if (!ttX_is_read) loadTEfficiency(inputfile, YEAR, ttX_is_read, xsec_it, btagEff_b_ttX, btagEff_c_ttX, btagEff_udsg_ttX);
            else addTEfficiency(inputfile, YEAR, xsec_it, btagEff_b_ttX, btagEff_c_ttX, btagEff_udsg_ttX);
            
        }
        if (xsec_it->first.find("st_") !=std::string::npos) {
            
            if (!ST_is_read) loadTEfficiency(inputfile, YEAR, ST_is_read, xsec_it, btagEff_b_ST, btagEff_c_ST, btagEff_udsg_ST);
            else addTEfficiency(inputfile, YEAR, xsec_it, btagEff_b_ST, btagEff_c_ST, btagEff_udsg_ST);
            
        }
    
    }//end not first process

 xsec_it++;  

 }//end loop over processes
 
 TFile * outputfile = new TFile("btagEfficiencies_"+TString(YEAR)+".root", "RECREATE");
 btagEff_b_tttt.Write();
 btagEff_c_tttt.Write();
 btagEff_udsg_tttt.Write();
 btagEff_b_ttbar.Write();
 btagEff_c_ttbar.Write();
 btagEff_udsg_ttbar.Write();
 btagEff_b_QCD.Write();
 btagEff_c_QCD.Write();
 btagEff_udsg_QCD.Write();
 btagEff_b_ttX.Write();
 btagEff_c_ttX.Write();
 btagEff_udsg_ttX.Write();
 btagEff_b_ST.Write();
 btagEff_c_ST.Write();
 btagEff_udsg_ST.Write();
 outputfile->Close();
 delete outputfile;

}
//functions
void loadTEfficiency (TFile * inputfile, string YEAR, bool &process_is_read, map<string, float>::iterator xsec_it, TEfficiency &btagEff_b, TEfficiency &btagEff_c, TEfficiency &btagEff_udsg) {
   
        process_is_read = true;
        std::string str_e_b("btagEff_b_");
        str_e_b.append(xsec_it->first);
        std::string str_e_c("btagEff_c_");
        str_e_c.append(xsec_it->first);
        std::string str_e_udsg("btagEff_udsg_");
        str_e_udsg.append(xsec_it->first);
        btagEff_b = *(TEfficiency*)inputfile->Get(str_e_b.c_str());
        btagEff_c = *(TEfficiency*)inputfile->Get(str_e_c.c_str());
        btagEff_udsg = *(TEfficiency*)inputfile->Get(str_e_udsg.c_str());
            
        TH1F * totalWeight;
        std::string str_w("totalWeight_");
        str_w.append(xsec_it->first);
        totalWeight = (TH1F*)inputfile->Get(str_w.c_str());
        btagEff_b.SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
        btagEff_c.SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
        btagEff_udsg.SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
        delete totalWeight;
}

void addTEfficiency(TFile * inputfile, string YEAR, map<string, float>::iterator xsec_it, TEfficiency &btagEff_b, TEfficiency &btagEff_c, TEfficiency &btagEff_udsg) {

    TEfficiency *add_eff_b;
    TEfficiency *add_eff_c;
    TEfficiency *add_eff_udsg;
    std::string str_e_b("btagEff_b_");
    str_e_b.append(xsec_it->first);
    std::string str_e_c("btagEff_c_");
    str_e_c.append(xsec_it->first);
    std::string str_e_udsg("btagEff_udsg_");
    str_e_udsg.append(xsec_it->first);
    add_eff_b = (TEfficiency*)inputfile->Get(str_e_b.c_str());
    add_eff_c = (TEfficiency*)inputfile->Get(str_e_c.c_str());
    add_eff_udsg = (TEfficiency*)inputfile->Get(str_e_udsg.c_str());
    TH1F * totalWeight;
    std::string str_w("totalWeight_");
    str_w.append(xsec_it->first);
    totalWeight = (TH1F*)inputfile->Get(str_w.c_str());
    add_eff_b->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
    add_eff_c->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
    add_eff_udsg->SetWeight(xsec_it->second*lumi[YEAR]/totalWeight->Integral());
    btagEff_b.Add(*add_eff_b);
    btagEff_c.Add(*add_eff_c);
    btagEff_udsg.Add(*add_eff_udsg);
    delete add_eff_b;
    delete add_eff_c;
    delete add_eff_udsg;
}
