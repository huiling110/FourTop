/*************************************************************************
	> File Name: GetEntry.cpp
	> Author: 
	> Mail: 
	> Created Time: Mon Jul  6 22:14:45 2020
 ************************************************************************/
#include "EventSelection_4top_v1.h"
#include<iostream>

void GetEntry(){
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
  //fileName.push_back("QCD_HT200to300.root");   //6
  //fileName.push_back("QCD_HT300to500.root");   //7
  //fileName.push_back("QCD_HT500to700.root");   //8
  //fileName.push_back("QCD_HT700to1000.root");   //9
  //fileName.push_back("QCD_HT1000to1500.root");   //10
  //fileName.push_back("QCD_HT1500to2000.root");   //11
  //fileName.push_back("QCD_HT2000toIn.root");   //12
  //fileName.push_back("TTJets.root");   //13
  fileName.push_back("TT.root");   //14
  //fileName.push_back("TTWJetsToQQ.root");   //15
  //fileName.push_back("TTZToQQ.root");   //16
  //fileName.push_back("TTTT.root");   //17
  for(unsigned int Nfiles=0; Nfiles<fileName.size(); Nfiles++){
    string FILEprov = "/publicfs/cms/user/huahuil/FourTop/2016v1/"+fileName[Nfiles];    
    const char *FILE = FILEprov.c_str();
    TFile *file = TFile::Open(FILE);
    Tree = (TTree*)file->Get(openTree);
    //Tree1 = (TTree*)file->Get(openTree1);

   Int_t Pnentries = (Int_t)Tree->GetEntries("eventnumnegative==1"); cout<<fileName[Nfiles]<<":  Positive:"<<Pnentries<<"  ";
   Int_t Nnentries = (Int_t)Tree->GetEntries("eventnumnegative==-1"); cout<<"Negtive:"<<Nnentries<<"  ;"<<endl;
   //Int_t nentries = (Int_t)Tree1->GetEntries(); cout<<"entries:"<<nentries<<";  "<<endl;

  }

}
