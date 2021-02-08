/*************************************************************************
	> File Name: GetEntry.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul  6 22:14:45 2020
 ************************************************************************/
#include "EventSelection_4top_v1.h"
#include<iostream>

void GetEntry(const string inputfile){
    gStyle->SetCanvasColor(0);
    gStyle->SetFrameBorderMode(0);//?
    gStyle->SetOptStat("rme");
    gStyle->SetPalette(1,0);
    gStyle->SetTitleX(0.50);
    gStyle->SetTitleY(0.96);
    gStyle->SetPaintTextFormat(".2f");


  using namespace std;
//  char openTree1[500];   sprintf(openTree1, "TNT/BOOM");
  char openTree[500];   sprintf(openTree, "TNT/evtree");
  vector<string> fileName;
  //fileName.push_back("TTJets.root");   //13
  fileName.push_back(inputfile);   
  //fileName.push_back("TTTT_TuneCUETP8M2T4_13TeV-amcatnlo-pythia8.root");   
  for(unsigned int Nfiles=0; Nfiles<fileName.size(); Nfiles++){
//    string FILEprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/"+fileName[Nfiles];    
    string FILEprov = "/publicfs/cms/data/TopQuark/FourTop/v002/mc/2016/"+fileName[Nfiles];    
    const char *FILE = FILEprov.c_str();
    TFile *file = TFile::Open(FILE);
    Tree = (TTree*)file->Get(openTree);
    //Tree1 = (TTree*)file->Get(openTree1);

   Int_t Pnentries = (Int_t)Tree->GetEntries("eventnumnegative==1"); cout<<fileName[Nfiles]<<":  Positive:"<<Pnentries<<"  ";
   Int_t Nnentries = (Int_t)Tree->GetEntries("eventnumnegative==-1"); cout<<"Negtive:"<<Nnentries<<"  ;"<<endl;
   //Int_t nentries = (Int_t)Tree1->GetEntries(); cout<<"entries:"<<nentries<<";  "<<endl;

  }

}
